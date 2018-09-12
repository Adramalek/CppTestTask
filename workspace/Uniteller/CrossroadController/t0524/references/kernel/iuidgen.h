// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовый интерфейс генератора уникальных идентификаторов

#pragma once

#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Базовый интерфейс генератора уникальных идентификаторов
      /// </summary>
      interface IUnicalIdGenerator : public IExportable
      {
      public:
        /// <summary>
        /// Возвращает уникальный идентификатор
        /// </summary>
        /// <returns> Уникальный идентификатор </returns>
        virtual address GetUnicalId() = 0;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller