// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс состояния конечного автомата

#pragma once

#include "istartable.h"
#include "istatemachinecontext.h"
#include "imessagefilter.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
            
      /// <summary>
      /// Интерфейс состояния конечного автомата
      /// </summary>
      interface IState : public IStartable<IStateMachineContext>
      {
      public: // Свойства
        // имя состояния
        READONLY_PROPERTY_DECLARATION(char *, Name);
        // таймаут
        PROPERTY_DECLARATION(int, TimeOut);
        // начальное ли данное состояние
        PROPERTY_DECLARATION(bool, IsStartState);
        // конечное ли данное состояние
        PROPERTY_DECLARATION(bool, IsStopState);
        // уникальный код состояния
        PROPERTY_DECLARATION(__int16, StateId);
        // отбрасываются ли отфильтрованные события
        PROPERTY_DECLARATION(bool, IsPostponeFilter);
      public:
        /// <summary>
        /// Добавляет переход
        /// </summary>
        /// <param name="evt">Тип события</param>
        /// <param name="next">Следующее состояние</param>
        /// <param name="constraints">Сообщения, которые могут генерироваться на переходе</param>
        virtual void AddTransition(event_t evt, IState * next, IMessageFilter * constraints) = 0;
        /// <summary>
        /// Позволяет обработать событие в данном состоянии
        /// </summary>
        /// <param name="evt">Тип события</param>
        /// <returns>Следующее состояние или NULL, если переход не осуществляется</returns>
        virtual IState * HandleEvent(event_t evt) = 0;     
        /// <summary>
        /// Позволяет получить разрешенные события
        /// </summary>
        /// <returns>Фильтр сообщений, которые могут быть обработаны в данном состоянии</returns>
        virtual IMessageFilter * GetAllowedEvents() = 0;

        /// <summary>
        /// Позволяет получить разрешенные исходящие события в момент перехода, активированного событием evt
        /// </summary>
        /// <returns>Фильтр сообщений, которые могут быть отправлены</returns>
        virtual IMessageFilter * GetAllowedEvents(event_t evt) = 0;

        /// <summary>
        /// Очищает список переходов
        /// </summary>
        virtual void ClearTransitions() = 0;          
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller