#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

enum ERROR_CODE {
	ERR_OK = 0,
	ERR_TOO_FEW_ARGS,
	ERR_SAME_IN_OUT_FILES,
	ERR_CANT_OPEN_INFILE,
	ERR_CANT_OPEN_OUTFILE,
	ERR_CANT_READ_INPUT,
	ERR_CANT_WRITE_OUTPUT,
	ERR_CANT_CLOSE_INFILE,
	ERR_CANT_CLOSE_OUTFILE,
	ERR_CANT_DELETE_OUTFILE,
	ERR_CANT_DELETE_INFILE
};

int main(int argc, char* argv[]) {

	if (argc < 3) {
		fprintf(stderr, "Not enough arguments, must be at least 2 of them!\n");
		return ERR_TOO_FEW_ARGS;		
	}
	
	const char* infile_name = argv[1];
	const char* outfile_name = argv[2];
	
	if (strcmp(infile_name, outfile_name) == 0) {
		fprintf(stderr, "Input and output files must be different!\n");
		return ERR_SAME_IN_OUT_FILES;		
	}

	FILE* infile = fopen(infile_name, "r");
	if (infile == NULL) {
		perror("Cannot open the input file");
		return ERR_CANT_OPEN_INFILE;
	}
	FILE* outfile = fopen(outfile_name, "w");
	if (outfile == NULL) {
		perror("Cannot open the output file");
		if (fclose(infile) != 0) {
			perror("Cannot close the input file");
			return ERR_CANT_CLOSE_INFILE;
		}
		return ERR_CANT_OPEN_OUTFILE;
	}
	
	errno = 0;
	int c = fgetc(infile);
	while (c != EOF) {
		if (fputc(c, outfile) == EOF) {
			perror("Cannot write to the output file");
			if (fclose(infile) != 0) {
				perror("Cannot close the input file");
				return ERR_CANT_CLOSE_INFILE;
			}
			if (fclose(outfile) != 0) {
				perror("Cannot close the output file");
				return ERR_CANT_CLOSE_OUTFILE;
			}
			if (remove(outfile_name) != 0) {
				perror("Cannot delete the output file");
				return ERR_CANT_DELETE_OUTFILE;
			}
			return ERR_CANT_WRITE_OUTPUT;
		}
		c = fgetc(infile);
	}
	
	if (ferror(infile) != 0) {
		perror("Cannot read from the input file");
		if (fclose(outfile) != 0) {
			perror("Cannot close the output file");
			if (fclose(infile) != 0) {
				perror("Cannot close the input file");
				return ERR_CANT_CLOSE_INFILE;
			}
			return ERR_CANT_CLOSE_OUTFILE;
		}
		if (fclose(infile) != 0) {
			perror("Cannot close the input file");
			if (remove(outfile_name) != 0) {
				perror("Cannot delete the output file");
				return ERR_CANT_DELETE_OUTFILE;
			}
			return ERR_CANT_CLOSE_INFILE;
		}
		if (remove(outfile_name) != 0) {
			perror("Cannot delete the output file");
			return ERR_CANT_DELETE_OUTFILE;
		}
		return ERR_CANT_READ_INPUT;
	}
	
	if (fclose(outfile) != 0) {
		perror("Cannot close the output file");
		if (fclose(infile) != 0) {
			perror("Cannot close the input file");
			return ERR_CANT_CLOSE_INFILE;
		}
		return ERR_CANT_CLOSE_OUTFILE;
	}
	if (fclose(infile) != 0) {
		perror("Cannot close the input file");
		if (remove(outfile_name) != 0) {
			perror("Cannot delete the output file");
			return ERR_CANT_DELETE_OUTFILE;
		}
		return ERR_CANT_CLOSE_INFILE;
	}
	if (remove(infile_name) != 0) {
		perror("Cannot delete the input file");
		return ERR_CANT_DELETE_INFILE;
	}
	
	return ERR_OK;

}