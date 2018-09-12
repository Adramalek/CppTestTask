// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию источника мета-данных

#pragma once

#include "ikernelapi.h"
#include "iobject.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      
      #define EXPORT_SYSTEM_OBJECT(Class) extern "C" { KERNEL_EXPORT IObject * CreateInstance(IKernelApi * api) { return new Class(api); } }
      #define EXPORT_SYSTEM_OBJECT_SINGLETON(Class) extern "C" { SmartPointer<Class> g_Instance; KERNEL_EXPORT IObject * CreateInstance(IKernelApi * api) { if (!g_Instance.p) g_Instance <<= new Class(api); return g_Instance.Copy(); } }

      #define EXPORT_PROTOCOL(Namespace) extern "C" { KERNEL_EXPORT IObject * CreateInstance(IKernelApi * /*api*/) { return NULL; } }

      // Тип порождающей функции
      typedef IObject * TCreateInstance(IKernelApi * api);
      // Тип порождающей функции
      typedef IObject * TCreateInstanceEx(IKernelApi * api, const char * szMachine);

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller