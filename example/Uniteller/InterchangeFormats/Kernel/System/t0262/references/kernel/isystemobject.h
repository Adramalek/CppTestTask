// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовый интерфейс объекта системы

#pragma once

#include "istatemachinecontext.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Базовый интерфейс объекта системы
      /// </summary>
      interface ISystemObject : public IStateMachineContext
      {
      public:
        /// Используется специализированными обертками для контроля имплементации интерфейса IObject
        typedef int IsSystemObject;
      };



      interface IPlatformInterceptor : public ISystemObject
      {
      public:
        virtual IExportable * GetApiEndpoint() = 0;
        virtual const char * GetApiId() = 0;
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller