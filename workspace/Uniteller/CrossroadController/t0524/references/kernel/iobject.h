// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовый интерфейс объекта системы

#pragma once

#include "irequestdispatcher.h"
#include "imqcontroller.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
#ifdef __GNUG__
#if __GNUC__ < 5
#define NO_CASTS
#endif
#endif

      /// <summary>
      /// Базовый интерфейс объекта системы
      /// </summary>
      interface IObject : public IExportable
      {
      public:
        // имя типа объекта
        READONLY_PROPERTY_DECLARATION(char *, Type);
        // уникальный идентификатор объекта
        READONLY_PROPERTY_DECLARATION(char *, UnicalId);
        /// <summary>
        /// Позволяет объекту системы получать сообщения из шины передачи сообщений
        /// </summary>
        /// <param name="message"> Сообщение </param>
        virtual bool ProcessMessage(IMessage * message) = 0;

        /// Используется специализированными обертками для контроля имплементации интерфейса IObject
        typedef int IsObject;
#ifndef NO_CASTS
      };

      /// <summary>
      /// Интерфейс объекта системы, используемый ядром
      /// </summary>
      interface ICoreObject : public IObject
      {
      public:
#endif
        /// <summary>
        /// Позволяет подключить к объекту системы диспетчер запросов, позволяющий пользоваться 
        /// функциями отправки шины передачи сообщений
        /// </summary>
        /// <param name="moduleId"> Идентификатор модуля, диспетчер запросов которого передается </param>
        /// <param name="dispatcher"> Диспетчер запросов </param>
        virtual void SetRequestDispatcher(address moduleId, IRequestDispatcher * dispatcher) = 0;
        /// <summary>
        /// Позволяет подключить к модулю контроллер логической шины. Это позволяет ему стать мастер модулем
        /// этой шины, создавать и подключать к этой шине другие модули, а также создавать подшины.
        /// </summary>
        /// <param name="busId">Идентификатор шины, контроллер который передается модулю</param>
        /// <param name="controller">Контроллер для управления шиной</param>
        virtual void SetMqController(address busId, IMqController * controller) = 0;
        /// <summary>
        /// Позволяет установить уникальный идентификатор объекта
        /// </summary>
        /// <param name="szUnicalId">Уникальный идентификатор объекта.</param>
        virtual void SetUnicalId(const char * szUnicalId) = 0;
        /// <summary>
        /// Позволяет получить диспетчер запросов модуля
        /// </summary>
        virtual IRequestDispatcher * GetRequestDispatcher() = 0;
        /// <summary>
        /// Позволяет получить информацию о том поддерживается ли данное поколение
        /// </summary>
        /// <param name="generation">Поколение.</param>
        virtual bool IsGenerationSupported(int generation) = 0;
        /// <summary>
        /// Позволяет получить информацию о том поддерживается ли данный протокол
        /// </summary>
        /// <param name="szProtocol">Протокол.</param>
        /// <param name="generation">Поколение протокола.</param>
        virtual bool IsProtocolSupported(const char * szProtocol, int generation) = 0;

        virtual IExportable * SetPlatformApiEndpoint(const char * szHive, IExportable * api) = 0;
      };

#ifdef __GNUG__
#if __GNUC__ < 5
  typedef IObject ICoreObject;
#endif
#endif


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
