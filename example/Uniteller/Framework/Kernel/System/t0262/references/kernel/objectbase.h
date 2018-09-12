// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ��������� ������� �������

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
        // � �������� ��������� ������� ���������� ���������, ����������� IObject
        typedef typename T::IsObject OnlyObject;
      protected:
        // ��������� �������� � ������
        SmartPointer<IRequestDispatcher> m_RequestDispatcher;
        // ���������� ����������-����
        SmartPointer<IMqController> m_MqController;

        // ���������� �������� ��������������� �������
        std::map<std::string, IRequestDispatcher *> m_Intercepted;
        // ������ ������������ ���������� ���
        std::map<std::string, IMqController *> m_MqControllers;
      protected:
        std::string m_sType;
      public:
        const char * GetType() const
        {
          return m_sType.c_str();
        }
        // ���������� ������������� �������
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
        /// ��������� ���������� � ������� ������� ��������� ��������, ����������� ������������ 
        /// ��������� �������� ���� �������� ���������
        /// </summary>
        /// <param name="moduleId"> ������������� ������, ��������� �������� �������� ���������� </param>
        /// <param name="dispatcher"> ��������� �������� </param>
        void SetRequestDispatcher(address moduleId, IRequestDispatcher * dispatcher)
        {
					if (strcmp(m_UnicalId.c_str(), moduleId) ==0)
          { // ������� �����������
            m_RequestDispatcher = dispatcher;
            OnConnected();
          }
          else
          { // ������������ ��� �����������
            if (dispatcher)
            {
              dispatcher->AddRef();
              m_Intercepted.insert(std::make_pair(moduleId, dispatcher));
            }
          }
        }

        /// <summary>
        /// ��������� �������� ��������� ��������
        /// <summary>
        IRequestDispatcher * GetRequestDispatcher() 
        {
          return m_RequestDispatcher.Copy();
        }

        /// <summary>
        /// ��������� �������� ��������� �������� �� ���������������� ������
        /// <summary>
        /// <param name="id">����� ���������������� ������</param>
        /// <returns>��������� �� ��������� �������� �� ���������������� ������</returns>
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
        /// ��������� ��������� ��������������� �� ������ ����������� ������� �������� � ��������� ������ ��� ������ id
        /// </summary>
        /// <param name="id">����� ���������������� ������</param>
        /// <returns>��������� �� ��������� �������� �� ���������������� ������</returns>
        bool IsIntercepted(address id) const
        {
          std::map<std::string, IRequestDispatcher *>::const_iterator i = m_Intercepted.find(id);
					return  (i != m_Intercepted.end());
        }

        /// <summary>
        /// ��������� ���������� � ������ ���������� ���������� ����. ��� ��������� ��� ����� ������ �������
        /// ���� ����, ��������� � ���������� � ���� ���� ������ ������, � ����� ��������� �������.
        /// </summary>
        /// <param name="busId">������������� ����, ���������� ������� ���������� ������</param>
        /// <param name="controller">���������� ��� ���������� �����</param>
        void SetMqController(address /*busId*/, IMqController * controller)
        {
          m_MqController = controller;
        }

        /// <summary>
        /// ��������� ����������� ������ ����������� � ���� �������� ��������� � ��������� �����-�� �������� ��������
        /// </summary>
        virtual void OnConnected()
        {
        }

				/// <summary>
				/// ���������� ����� �������� API ���������
				/// </summary>
        virtual IExportable * SetPlatformApiEndpoint(const char * /*szHive*/, IExportable * /*api*/)
        {
          return NULL;
        }

        /// <summary>
        /// ��������� �������� ������ ����������� �������
        /// </summary>
        /// <param name="filter"> ������ ������� </param>
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


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller
