#include <ncurses.h>
#include <sys/stat.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#define DX 3

int main(int argc, char *argv[]) 
{

        FILE *fd;
        WINDOW *win;
        int H, W, index, sz, n, m, c, ch;
        bool done;
        char *buf, *curr;
        char **strings;
        size_t len;
        struct stat info;

        if (argc < 2) {
                printf("Please give the file name as the only argument.\n");
                return -1;
        }

        fd = fopen(argv[1], "r");
        if (fd == NULL) {
                printf("Cannot open the file.\n");
                return -1;
        }

        stat(argv[1], &info);
        len = info.st_size;
        buf = malloc(len+2);
        buf[0] = '\n';
        index = 1;
        sz = 0;
        while ((ch = fgetc(fd)) != EOF) {
                buf[index++] = ch;
                if (ch == '\n') sz++;
        }
        fclose(fd);
        if (buf[len] != '\n') {
                buf[len+1] = '\n';
                sz++;
        }
        strings = calloc(sz+1, sizeof(char*));
        curr = buf;
        for (index = 0; index < sz+1 ; ++index) {
                curr[0] = '\0';
                strings[index] = curr + 1;
                curr = strchr(curr + 1, '\n');
        }

        setlocale(LC_ALL, "");

        initscr(); //initialize the screen, launch ncurses
        noecho(); //what we type does not show on screen
        cbreak(); //multiple activation
        printw(argv[1]); //output on the screen
        refresh(); //renew the whole screen (not just the window) to make the writings appear

        H = LINES-2*DX;
        W = COLS-2*DX;
        win = newwin(H, W, DX, DX); //open the window with given size and position
        keypad(win, TRUE); //keys are not interpreted as escape-sequenses
        scrollok (win, TRUE); //window scrolling turned on
        n = 0; m = 0;
        done = FALSE;
        do {
                werase(win);
                for (index = 0; index < H-2 && index + n < sz; ++index)
                        mvwprintw(win, index+1, 1, "%4d: %s\n", index+n, m > strlen(strings[index + n]) ? "" : strings[index+n] + m);
                box(win, 0, 0); //frame around the window
                wrefresh(win);
                c = wgetch(win);
                switch (c) {
                        case 27: done = TRUE; break;
                        case ' ':
                        case KEY_DOWN: n = n < sz-1 ? n+1 : n; break;
                        case KEY_NPAGE: n = n < sz-H+1 ? n+H-2 : sz-1; break;
                        case KEY_PPAGE: n = n > H-1 ? n-H+2 : 0; break;
                        case KEY_UP: n = n > 0 ? n-1 : n; break;
                        case KEY_RIGHT: m++; break;
                        case KEY_LEFT: m = m>0 ? m-1 : 0; break;
                }
        } while(!done);

        endwin();
        return 0;

}