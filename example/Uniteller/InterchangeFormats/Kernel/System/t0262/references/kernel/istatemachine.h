// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ‘айл содержит интерфейс конечного автомата

#pragma once

#include "istate.h"
#include "istatemachinecontext.h"
#include "iregistrykey.h"
#include "irequestdispatcher.h"
#include "istatemachinehandler.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// »нтерфейс конечного автомата
      /// </summary>
      interface IStateMachine : public IStartable<IStateMachineContext>
      {
      public:
        /// <summary>
        /// ƒобавл€ет состо€ние
        /// </summary>
        /// <param name="state">—осто€ние</param>
        virtual void AddState(IState * state) = 0;
        /// <summary>
        /// ƒобавл€ет переход
        /// </summary>
        /// <param name="sFrom">—осто€ние из которого осуществл€етс€ переход</param>
        /// <param name="sTo">—осто€ние в которое осуществл€етс€ переход</param>
        /// <param name="evt">—обытие, по которому осуществл€етс€ переход</param>        
        /// <param name="constraints">—ообщени€, которые могут генерироватьс€ на переходе</param>
        /// <param name="handler">ƒекларативным образом заданный обработчик перехода (если нету, то null)</param>
        /// <param name="handlerLevel">”ровень декларативного обработчика</param>
        virtual void AddTransition(IState * sFrom, IState * sTo, event_t evt, IMessageFilter * constraints, IStateMachineHandler * handler,
          unsigned __int8 handlerLevel) = 0;              
        /// <summary>
        /// ѕозвол€ет передавать конечному автомату событи€ из шины передачи событий (сообщений)
        /// </summary>
        /// <param name="message">—ообщение, пришедшее из шины передачи сообщений.</param>
        virtual void HandleEvent(IMessage * message, IRequestDispatcher * dispatcher) = 0;
        /// <summary>
        /// ѕозвол€ет получить состо€ние конечного автомата по имени
        /// </summary>
        /// <param name="name">»м€ состо€ни€.</param>
        /// <returns>—осто€ние машины (если оно найдено) или NULL если состо€ние с таким именем не определено</returns>
        virtual IState * GetState(const char * name) = 0;       

        /// <summary>
        /// ѕозвол€ет установить значение переменной контекста
        /// </summary>
        virtual void SetContextVariable(const char * name, IVariant * value) = 0;
        /// <summary>
        /// ѕозвол€ет получить значение переменной контекста
        /// </summary>
        virtual IVariant * GetContextVariable(const char * name) = 0;
      };           

      // »спользуетс€ дл€ создани€ кодов событий
      #define MAKE_EVENT_CODE(x,y,z) ((unsigned __int64)x<<48) | ((unsigned __int64)y<<32) | ((unsigned __int64)z)

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller