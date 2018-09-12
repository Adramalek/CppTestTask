// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс сообщения, передаваемого по шине передачи сообщений

#pragma once

#include "iset.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс фильтра сообщений
      /// </summary>
      interface IMessageFilter : public ISet<int>
      {
      public: // Свойства
        // является ли фильтр эксклюзивным
        PROPERTY_DECLARATION(bool, IsExclusive);
        /// <summary>
        /// Позволяет проверить код сообщения, на пропуск в фильтром
        /// </summary>
        /// <param name="message">Сообщение для проверки на пропуск фильтром</param>
        /// <returns>true - если сообщение пропущено фильтром, false - иначе </returns>
        virtual bool Check(int message) = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller