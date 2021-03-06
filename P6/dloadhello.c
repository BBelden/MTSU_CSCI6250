#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*hello_function)(void);

int main (int argc,char *argv[]) 
{
	if (argc != 2) 
	{
		printf("p6 arg\n");
		exit(-1);
	}

	void *library;
	hello_function hello;
	const char *error;

	// library = dlopen("./libhello.so", RTLD_LAZY);  /*  ./ obviates need for LD_LIBRARY_PATH */
	library = dlopen("libhello.so", RTLD_LAZY);
	if (library == NULL)
	{
		fprintf(stderr, "Could not open libhello.so: %s\n", dlerror());
		exit(1);
	}

	/* while in this case we know that the print_hello symbol
	* should never be null, that is not true for looking up
	* arbitrary symbols.  So we demonstrate checking dlerror()'s
	* return code instead of dlsym()'s.
	*/
	dlerror();    /* clear errors */
	hello = dlsym(library, "print_hello");
	error = dlerror();
	if (error)
	{
		fprintf(stderr, "Could not find print_hello: %s\n", error);
		exit(1);
	}

	(*hello)();
	dlclose(library);
	return(0);
}
