// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит внешний интерфейс динамической библиотеки Uniteller.Framework.Kernel.dll 

#pragma once
#include "ikernelapi.h"

#ifndef __GNUG__
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
#define KERNEL_API __declspec(dllexport)
#else
#define KERNEL_API __declspec(dllimport)
#endif
#else
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
#define KERNEL_API 
#else
#define KERNEL_API 
#endif
#endif

using Uniteller::Framework::Kernel::IKernelApi;


extern "C"
{
  #ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
  KERNEL_API IKernelApi * LoadKernelApi();
  KERNEL_API void UnloadKernelApi();
  #else
  #endif

}
