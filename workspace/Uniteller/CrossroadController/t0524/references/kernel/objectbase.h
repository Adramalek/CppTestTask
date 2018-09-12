// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовый интерфейс объекта системы

#pragma once

#include "iobject.h"
#include <map>
#include "kernel/linq"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      template <class T>
      class ObjectBase : public Exportable<T>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IObject
        typedef typename T::IsObject OnlyObject;
      protected:
        // Диспетчер запросов к модулю
        SmartPointer<IRequestDispatcher> m_RequestDispatcher;
        // Контроллер логической-шины
        SmartPointer<IMqController> m_MqController;

        // Диспетчеры запросов перехватываемых модулей
        std::map<std::string, IRequestDispatcher *> m_Intercepted;
        // Индекс контроллеров логических шин
        std::map<std::string, IMqController *> m_MqControllers;
      protected:
        std::string m_sType;
      public:
        const char * GetType() const
        {
          return m_sType.c_str();
        }
        // уникальный идентификатор объекта
        PROPERTY_IMPLEMENTATION_STRING(UnicalId);
      public:
#ifdef __GNUG__
        ObjectBase(const char * szType) : m_sType(szType)
        {
        }
#endif

        virtual ~ObjectBase()
        {
          CleanUpIntercepted();
          CleanUpMqControllers();    
        }
      protected:
        void CleanUpIntercepted()
        {
          Linq::CleanExportableMap(m_Intercepted);
        }
        void CleanUpMqControllers()
        {          
          m_MqController.Release();
          Linq::CleanExportableMap(m_MqControllers);
        }
      public:
        /// <summary>
        /// Позволяет подключить к объекту системы диспетчер запросов, позволяющий пользоваться 
        /// функциями отправки шины передачи сообщений
        /// </summary>
        /// <param name="moduleId"> Идентификатор модуля, диспетчер запросов которого передается </param>
        /// <param name="dispatcher"> Диспетчер запросов </param>
        void SetRequestDispatcher(address moduleId, IRequestDispatcher * dispatcher)
        {
					if (strcmp(m_UnicalId.c_str(), moduleId) ==0)
          { // Обычное подключение
            m_RequestDispatcher = dispatcher;
            OnConnected();
          }
          else
          { // Подключаемся как перехватчик
            if (dispatcher)
            {
              dispatcher->AddRef();
              m_Intercepted.insert(std::make_pair(moduleId, dispatcher));
            }
          }
        }

        /// <summary>
        /// Позволяет получить диспетчер запросов
        /// <summary>
        IRequestDispatcher * GetRequestDispatcher() 
        {
          return m_RequestDispatcher.Copy();
        }

        /// <summary>
        /// Позволяет получить диспетчер запросов от перехватываемого модуля
        /// <summary>
        /// <param name="id">Адрес перехватываемого модуля</param>
        /// <returns>Указатель на диспетчер запросов от перехватываемого модуля</returns>
        IRequestDispatcher * GetRequestDispatcher(address intercepted) 
        {
          std::map<std::string, IRequestDispatcher *>::iterator i = m_Intercepted.find(intercepted);
          if (i != m_Intercepted.end())
          {
            if (i->second)
              i->second->AddRef();
            return i->second;
          }
          return NULL;
        }

        /// <summary>
        /// Позволяет проверить перехватывается ли данным экземпляром объекта входящий и исходящий трафик для адреса id
        /// </summary>
        /// <param name="id">Адрес перехватываемого модуля</param>
        /// <returns>Указатель на диспетчер запросов от перехватываемого модуля</returns>
        bool IsIntercepted(address id) const
        {
          std::map<std::string, IRequestDispatcher *>::const_iterator i = m_Intercepted.find(id);
					return  (i != m_Intercepted.end());
        }

        /// <summary>
        /// Позволяет подключить к модулю контроллер логической шины. Это позволяет ему стать мастер модулем
        /// этой шины, создавать и подключать к этой шине другие модули, а также создавать подшины.
        /// </summary>
        /// <param name="busId">Идентификатор шины, контроллер который передается модулю</param>
        /// <param name="controller">Контроллер для управления шиной</param>
        void SetMqController(address /*busId*/, IMqController * controller)
        {
          m_MqController = controller;
        }

        /// <summary>
        /// Позволяет перехватить момент подключения к шине передачи сообщений и выполнить какие-то полезные действия
        /// </summary>
        virtual void OnConnected()
        {
        }

				/// <summary>
				/// Подключает точку изоляции API платформы
				/// </summary>
        virtual IExportable * SetPlatformApiEndpoint(const char * /*szHive*/, IExportable * /*api*/)
        {
          return NULL;
        }

        /// <summary>
        /// Позволяет изменить фильтр принимаемых событий
        /// </summary>
        /// <param name="filter"> Фильтр событий </param>
        void SetFilter(bool isPostpone, IMessageFilter * filter)
        {
          m_RequestDispatcher->SetIsPostponeFilter(isPostpone);
          m_RequestDispatcher->SetFilter(filter);
        }
#ifdef __GNUG__
        bool SendMessageRd(const char * address, IMessage * msg)
        {
          return m_RequestDispatcher->SendMessage(address, msg);
        }

        bool SendMessageMq(const char * address, IMessage * msg)
        {
          return m_MqController->SendMessage(address, msg);
        }

        void Disconnect()
        {
          m_RequestDispatcher->Disconnect();
        }

        IRequestDispatcher * GetRD()
        {
          return m_RequestDispatcher.p;
        }

        void ReleaseRD()
        {
          m_RequestDispatcher.Release();
        }

        bool SendEventRd(address reciver, event_t message, int generation = 1, int priority = 0)
        {
          return m_RequestDispatcher->SendEvent(reciver, message, generation, priority);
        }
#endif
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
