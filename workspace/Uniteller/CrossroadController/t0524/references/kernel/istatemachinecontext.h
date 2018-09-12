// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс контекста конечного автомата

#pragma once

#include "imessage.h"
#include "imessagefilter.h"
#include "iobject.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс контекста конечного автомата
      /// </summary>
      interface IStateMachineContext : public ICoreObject
      {
      public:
        /// <summary>
        /// Генерирует тайм-аут
        /// </summary>
        virtual void RaiseTimeOut() = 0;

        /// <summary>
        /// Позволяет изменить фильтр принимаемых событий
        /// </summary>
        /// <param name="filter"> Фильтр событий </param>
        virtual void SetFilter(bool isPostpone, IMessageFilter * filter) = 0;

        /// <summary>
        /// Позволяет изменить фильтр отправляемых событий
        /// </summary>
        /// <param name="filter"> Фильтр событий </param>
        virtual void SetOutboxFilter(IMessageFilter * filter, const char * szOldStateName, const char * szNewStateName) = 0;
        
        /// <summary>
        /// Позволяет перехватывать моменты изменения состояний машины
        /// </summary>
        /// <param name="nFrom"> Состояние-источник </param>
        /// <param name="nTo"> Состояние-приемник </param>
        /// <param name="evt"> Событие, активировавшее переход </param>
        virtual void OnTransition(const __int16 nFrom, const __int16 nTo, IMessage * evt) = 0;

        /// <summary>
        /// Позволяет перехватить момент запуска машины
        /// </summary>
        virtual void OnMachineStarted() = 0;
        /// <summary>
        /// Позволяет перехватить момент остановки машины
        /// </summary>
        virtual void OnMachineStopped() = 0;
        /// <summary>
        /// Позволяет получить и обработать в контексте событие о переходе
        /// </summary>
        virtual void RegisterTransition(const char * szFrom, const char * szTo, event_t evt) = 0;
        /// <summary>
        /// Позволяет получить от контекста перекрытие тайм-аута
        /// </summary>
        virtual int GetTimeOutOvveride() = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller