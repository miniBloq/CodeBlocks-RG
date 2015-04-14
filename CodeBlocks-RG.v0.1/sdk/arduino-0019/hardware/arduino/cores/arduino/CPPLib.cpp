
extern "C"
{
	//#include "avr/io.h"
	#include "stdlib.h"
}

#include "CPPLib.h"

void __cxa_pure_virtual()
{
    //abort();
}


//Must be overloaded in order to use virtual destructors:
void operator delete (void *ptr) throw ()
{
    //I know: The "if" is not necessary, according to the standard.
    //But it's just one more line of code, and I sleep better with it:
    if (ptr)
        free (ptr);
}


void operator delete[] (void *ptr) throw ()
{
    ::operator delete (ptr);
}


void *operator new (size_t size) throw()
{
    return malloc(size);
}


void *operator new[] (size_t size) throw()
{
    return ::operator new(size);
}
