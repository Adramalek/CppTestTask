#pragma once

#include "kernel/exportable.h"
#include "kernel/ikernelapi.h"
#include "kernel/iobject.h"
#include "ExtensionLoadResult.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// Интерфейс загрузчика модулей-расширений микро-ядра
      /// </summary>
      interface IExtension : public IExportable
      {
      public:

        /// <summary>
        /// Загружает модуль
        /// </summary>
        virtual ExtensionLoadResult Load(const std::string & root, IKernelApi * api) = 0;

        /// <summary>
        /// Создает экземпляр объекта системы
        /// </summary>
        virtual IObject * CreateInstance(IKernelApi * api) = 0;
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller