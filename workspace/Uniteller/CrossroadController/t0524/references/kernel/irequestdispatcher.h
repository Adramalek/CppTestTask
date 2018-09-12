// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс диспетчера запросов к шине передачи сообщений

#pragma once

#include "imessagebus.h"
#include "imessagefilter.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс диспетчера запросов к шине
      /// </summary>
      interface IRequestDispatcher : public IMessageBus
      {      
      public:
        // откладывающий фильтр
        PROPERTY_DECLARATION(bool, IsPostponeFilter);
        /// <summary>
        /// Позволяет установить фильтр принимаемых сообщений
        /// Если передан NULL, то никакие сообщения не передаются
        /// </summary>
        virtual void SetFilter(IMessageFilter * filter) = 0;
        /// <summary>
        /// Инициирует отключение данного модуля от шины
        /// </summary>
        virtual void Disconnect() = 0;        

        virtual const char * GetAddress() const = 0;

				/// <summary>
				/// Позволяет сконструировать и отправить сообщение message приемнику target
				/// </summary>        
				/// <param name="target">Адрес приемника сообщения.</param>
				/// <param name="message">Сообщение для отправки.</param>
				/// <returns>Удалось ли отправить сообщение</retuns>
				virtual bool SendEvent(address target, event_t message, int generation = 1, int priority = 0) = 0;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller