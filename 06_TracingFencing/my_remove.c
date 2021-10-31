#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(const char*);

int remove(const char* filename) {

	remove_type trueremove;
	
	trueremove = (remove_type)dlsym(RTLD_NEXT, "remove");
	
	if (strstr(filename, "PROTECT") == NULL)
		return trueremove(filename);

	return 0;

}