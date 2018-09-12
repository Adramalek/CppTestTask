// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс шины передачи сообщений

#pragma once

#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс шины передачи сообщений
      /// </summary>
      interface IMessageBus : public IExportable
      {
      public:
        /// <summary>
        /// Позволяет отправить сообщение message приемнику target
        /// </summary>        
        /// <param name="target">Адрес приемника сообщения.</param>
        /// <param name="message">Сообщение для отправки.</param>
        /// <returns>Удалось ли отправить сообщение</retuns>
        virtual bool SendMessage(address target, IMessage * message) = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller