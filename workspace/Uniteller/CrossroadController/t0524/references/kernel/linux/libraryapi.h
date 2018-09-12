#pragma once
#include <dlfcn.h>

typedef void * HINSTANCE;

#define LoadLibraryA(filename) dlopen(filename, RTLD_LAZY)
#define FreeLibrary(handle) dlclose(handle)
#define GetProcAddress(handle, symbol) dlsym(handle, symbol)



