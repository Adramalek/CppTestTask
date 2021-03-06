// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������������� �� dll �������

#pragma once
#include <map>
#include "objectbase.h"
#include "istatemachine.h"
#include "iregistrykey.h"
#include "ikernelapi.h"
#include "isystemobject.h"
#include "Uniteller.Framework.Kernel.h"
#include "xregistrykey.h"
#include "kernel/messagefilter.h"
#ifdef __GNUG__
  #include "kernel/linuxsprt.h"
#endif

#if defined(__GNUG__) && (__GNUC__ <5)
#define LIGHTWEIGHT_SYSTEMOBJECT
#endif

#ifdef PORTABLE_COMPILE
#define LIGHTWEIGHT_SYSTEMOBJECT
#endif

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {     

#ifndef __GNUG__
      template <class Implementation, class T, class EndPoint = IProtocolEndPoint>
#else
      template <class Implementation, class T, typename EventHandler, class EndPoint = IProtocolEndPoint>
#endif
      class SystemObject : public ObjectBase<T>, public EndPoint
      {
        // � �������� ��������� ������� ���������� ���������, ����������� ISystemObject
        typedef typename T::IsSystemObject OnlySystemObject;
      private:
        // �������� �������
        SmartPointer<IStateMachine> m_StateMachine;
        // ��� ��������� ��������
        std::string m_sStateMachineName;

        bool m_IsConnected;
        bool m_IsStopped;

#ifndef __GNUG__
        // �������������� ��� ����������� �������
        typedef typename void (Implementation::* EventHandler)(IMessage * message); 
#endif

        // ��� ����� ������������ �������
        typedef typename std::map<unsigned __int64, EventHandler> EventHandlersMap;

        EventHandlersMap m_Handlers;      
       
        std::mutex m_Lock;

        long m_TimeOutOvveride;

#ifndef LIGHTWEIGHT_SYSTEMOBJECT
        SmartPointer<IMessageFilter> m_OutboxMessageFilter;
#endif

        event_t m_Kind;
        std::string m_sOldState;
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
        std::string m_sNewState;
#endif
      protected:
        SmartPointer<IKernelApi> m_Api;
      public:
        /// <summary>
        /// ����������� ������� �������
        /// </summary>
        /// <param name="szName">��� ��������� �������� ��� ��������.</param>
        SystemObject(const char * szName, IKernelApi * api) : 
#ifdef __GNUG__
          ObjectBase<T>(szName),
#endif
          m_sStateMachineName(szName), m_IsConnected(false), m_IsStopped(false), m_TimeOutOvveride(-1), 
          m_Api(api)
        {
#ifndef __GNUG__
          m_sType = szName;
#endif
        }

        /// <summary>
        /// ��������� ����������� ������ ����������� � ���� �������� ��������� � ��������� �����-�� �������� ��������
        /// </summary>
        void OnConnected() override
        {
          if (!m_IsConnected)
          {
            // ��������� �������� �������
            m_StateMachine.Attach(m_Api->LoadStateMachine(m_sStateMachineName.c_str()));
            LoadHandlers();
            // ��������� �������� �������
            m_StateMachine->Start(this);
            m_IsConnected = true;
          }
        }

        /// <summary>
        /// ���������� ����-���
        /// </summary>
        void RaiseTimeOut()
        {
   	  std::unique_lock<std::mutex> lk(m_Lock);
          SendEvent(this->GetUnicalId(), Kernel::Protocol::G1::Codes::TimeOut);
        }

        const char * GetMachineName() const
        {
          return m_sStateMachineName.c_str();
        }

        const char * GetOldState() const
        {
          return m_sOldState.c_str();
        }


        /// <summary>
        /// ��������� �������� ������ ������������ �������
        /// </summary>
        /// <param name="filter"> ������ ������� </param>
        void SetOutboxFilter(IMessageFilter * filter, const char * szOldStateName, const char * szNewStateName)
        {
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          m_OutboxMessageFilter = filter;
          m_sNewState = szNewStateName;
#endif
          m_sOldState = szOldStateName;
        }

        /// <summary>
        /// ��������� ������������� ������� ��������� ��������� ������
        /// </summary>
        /// <param name="nFrom"> ���������-�������� </param>
        /// <param name="nTo"> ���������-�������� </param>
        /// <param name="evt"> �������, �������������� ������� </param>
        void OnTransition(const __int16 nFrom, const __int16 nTo, IMessage * evt)
        {
          m_Kind = evt->GetKind();
          unsigned long long eventCode = MAKE_EVENT_CODE(nFrom, nTo, m_Kind);
          try
          {
            if (!FindAndCallHandler(eventCode, evt))
            {
              eventCode = MAKE_EVENT_CODE(nFrom, nTo, (m_Kind & 0xFFFF0000)); // ���������� ����� ������� � ������ ���������
							//eventCode &= 0xFFFFFFFFFFFF0000;
              if (!FindAndCallHandler(eventCode, evt))
              {
                eventCode = MAKE_EVENT_CODE(nFrom, nTo, 0); // ���������� ����� �������
								//eventCode &= 0xFFFFFFFFFFFF0000;
                FindAndCallHandler(eventCode, evt);
              }
            }
          }
          catch (KernelException & ex)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("KernelException");
            answer.SetExceptionMessage(ex.what());
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
          catch (std::exception & stdex)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("std::exception");
            answer.SetExceptionMessage(stdex.what());
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
          catch (...)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("Unknown");
            answer.SetExceptionMessage("Unhandled C++ exception on handle transition");
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
        }

        /// <summary>
        /// ������������ ��� ������ � ������ �����������.
        /// </summary>
        /// <param name="handler"> ��� ����������� </param>
        /// <param name="evt"> ���������-��������� </param>
        bool FindAndCallHandler(unsigned long long handler, IMessage * evt)
        {
          typename EventHandlersMap::iterator i  = m_Handlers.find(handler);
          if (i != m_Handlers.end())
          {
            // �������� ����������! todo- ������ �� �����
            EventHandler p = i->second;   
            Implementation * pImplementation = (Implementation *)(this);      
            if (pImplementation)
              (pImplementation->*p)(evt); // ����� �����������
            return true;
          }
          return false;
        }


        /// <summary>
        /// ��������� ����������� ������ ������� ������
        /// </summary>
        virtual void OnMachineStarted()
        {
        }
        /// <summary>
        /// ��������� ����������� ������ ��������� ������
        /// </summary>
        virtual void OnMachineStopped()
        {
          m_IsStopped = true;

          // ����������� �� ���� � ��������� ������
#ifndef __GNUG__
          m_RequestDispatcher->Disconnect();
#else
          this->Disconnect();
#endif
        }

        /// <summary>
        /// ��������� ������� ������� �������� ��������� �� ���� �������� ���������
        /// </summary>
        /// <param name="message"> ��������� </param>
        bool ProcessMessage(IMessage * message)
        {
          std::unique_lock<std::mutex> lk(m_Lock);              
          if (!m_IsStopped) // ���� ���� ������ ����������� - ������ �� ������
          {
#ifndef __GNUG__
            m_StateMachine->HandleEvent(message, m_RequestDispatcher.p);            
#else
            m_StateMachine->HandleEvent(message, this->GetRD());
#endif
          }
          
          if (m_IsStopped)
          {
#ifndef __GNUG__
            m_RequestDispatcher.Release();
#else
            this->ReleaseRD();
#endif
            m_Api.Release();
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
            m_OutboxMessageFilter.Release();          
#endif
            this->CleanUpIntercepted();
            this->CleanUpMqControllers();
            m_StateMachine.Release();
            return true;
          }
          return false;
        }

        void RegisterTransition(const char * szFrom, const char * szTo, event_t evt)
        {
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          std::this_thread::yield();
          Protocol::G1::StateChanged message;
          message.SetEvent(evt);
          message.SetOldState(szFrom);
          message.SetNewState(szTo);
          message.SetMachineName(m_sStateMachineName.c_str());
#ifndef __GNUG__
          m_RequestDispatcher->SendMessage("master", message.p); // ����� ������ ������ ���� �� �����
#else
          this->SendMessageRd("master", message.p); // ����� ������ ������ ���� �� �����
#endif
#endif
        }

      protected: 

        /// <summary>
        /// ����������� ������������ ��������� � ��������
        /// </summary>
        /// <param name="szFrom">���������, ������� �������� �������.</param>
        /// <param name="szTo">���������, � ������� �������� �������.</param>
        /// <param name="kind">��� �������.</param>
        /// <param name="handler">������� ����������.</param>
        void AddEventHandler(const char * szFrom, const char * szTo, event_t kind, EventHandler handler) 
        {
          SmartPointer<IState> stateFrom, stateTo;
          stateFrom.Attach(m_StateMachine->GetState(szFrom));
          stateTo.Attach(m_StateMachine->GetState(szTo));
          unsigned long long eventCode = MAKE_EVENT_CODE(stateFrom->GetStateId(), stateTo->GetStateId(), kind);
          m_Handlers.insert(std::make_pair(eventCode, handler));
        }

        // ��������� ���  ����������� ����� ������������ �������
        virtual void LoadHandlers()
        {
        }
      protected: // �������� ���������

        bool CheckOutgoingMessage(IMessage * message)
        {
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          if (m_OutboxMessageFilter.p && message)
          {
            event_t kind = message->GetKind();            
            if (!m_OutboxMessageFilter->Check(0) && !m_OutboxMessageFilter->Check(kind))
            {
              Kernel::Protocol::G1::UnexpectedBehaviour command;
              command.SetMachineName(m_sStateMachineName.c_str());
              command.SetMessage(message);
              command.SetEvent(m_Kind);
              command.SetOldState(m_sOldState.c_str());
              command.SetNewState(m_sNewState.c_str());
#ifndef __GNUG__
              m_RequestDispatcher->SendMessage("master", command);
#else
              this->SendMessageRd("master", command);
#endif
              return false;
            }
          }
#endif
          return true;
        }


        bool CheckOutgoingMessage(event_t kind, int generation)
        {
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          if (m_OutboxMessageFilter.p)
          {
            if (!m_OutboxMessageFilter->Check(0) && !m_OutboxMessageFilter->Check(kind))
            {
              Kernel::Protocol::G1::UnexpectedBehaviour command;
              command.SetMachineName(m_sStateMachineName.c_str());
              SmartPointer<Message> message;
              message <<= new Message(kind, generation);
              command.SetMessage(message);
              command.SetEvent(m_Kind);
              command.SetOldState(m_sOldState.c_str());
              command.SetNewState(m_sNewState.c_str());
#ifndef __GNUG__
              m_RequestDispatcher->SendMessage("master", command);
#else
              this->SendMessageRd("master", command);
#endif
              return false;
            }
          }
#endif
          return true;
        }

        bool SendMessage(address reciver, IMessage * message)
        {
#ifndef __GNUG__
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          if (CheckOutgoingMessage(message) && m_RequestDispatcher.p)
#else
          if (m_RequestDispatcher.p)
#endif
          {
              if (message)
                message->SetSourceId(GetUnicalId());
              return m_RequestDispatcher->SendMessage(reciver, message);
          }
#else
          if (CheckOutgoingMessage(message))
          {
              if (message)
                message->SetSourceId(this->GetUnicalId());
              return this->SendMessageRd(reciver, message);
          }
#endif
          return false;
        }
        
        bool SendEvent(address reciver, event_t message, int generation = 1, int priority = 0)
        {
#ifndef __GNUG__
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
          if (CheckOutgoingMessage(message, generation) && m_RequestDispatcher.p)
#else
          if (m_RequestDispatcher.p)
#endif
              return m_RequestDispatcher->SendEvent(reciver, message, generation, priority);
#else
          if (CheckOutgoingMessage(message, generation))
              return this->SendEventRd(reciver, message, generation, priority);
#endif
          return false;
        }

        bool SendMessageToControlledBus(address reciver, IMessage * message)
        {          
          if (CheckOutgoingMessage(message))
          {
  
#ifndef __GNUG__
						switch (*reciver)
						{
							case 'm':
								if (strcmp(reciver+1, "aster") == 0)
									return m_RequestDispatcher->SendMessage(reciver, message);
								break;
							case ':':
								++reciver;
								return m_RequestDispatcher->SendMessage(reciver, message);
							case 's':
								if (strcmp(reciver+1, "elf") == 0)
									return m_RequestDispatcher->SendMessage(GetUnicalId(), message);
								break;
            }
            message->SetSourceId("master");

            return m_MqController->SendMessage(reciver, message);
#else

						switch (*reciver)
						{
							case 'm':
								if (strcmp(reciver+1, "aster") == 0)
									return this->SendMessageRd(reciver, message);
								break;
							case ':':
								++reciver;
								return this->SendMessageRd(reciver, message);
							case 's':
								if (strcmp(reciver+1, "elf") == 0)
									return this->SendMessageRd(this->GetUnicalId(), message);
								break;
						}

            message->SetSourceId("master");
            return this->SendMessageMq(reciver, message);
#endif
          }
          return true;
        }

        bool SendMessageToControlledBus(address reciver, address alias, IMessage * message)
        {
          if (strcmp(alias, "self") == 0)
            alias = this->GetUnicalId();
          else
          if (!this->IsIntercepted(alias))
            return false;     
          if (CheckOutgoingMessage(message))
          {
            message->SetSourceId(alias);   
#ifndef __GNUG__
						switch (*reciver)
						{
							case ':':
								++reciver;
								return m_RequestDispatcher->SendMessage(reciver, message);
							case 'm':
								if (strcmp(reciver+1, "aster")==0)
								  return m_RequestDispatcher->SendMessage(reciver, message);     
								break;
							case 's':
								if (strcmp(reciver+1, "elf")==0)
								  return m_RequestDispatcher->SendMessage(GetUnicalId(), message);      
								break;
						}
            return m_MqController->SendMessage(reciver, message);
#else
						switch (*reciver)
						{
							case ':':
								++reciver;
								return this->SendMessageRd(reciver, message);
							case 'm':
								if (strcmp(reciver+1, "aster")==0)
								  return this->SendMessageRd(reciver, message);
								break;
							case 's':
								if (strcmp(reciver+1, "elf")==0)
								  return this->SendMessageRd(this->GetUnicalId(), message);
								break;
						}
            return this->SendMessageMq(reciver, message);
#endif
          }
          return true;
        }

        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ���������
        /// </summary>
        /// <param name="generation">���������.</param>
        bool IsGenerationSupported(int generation)
        {
          RegistryKeyWrapper moduleInfo;
          moduleInfo <<= OpenKey(MAKE_PATH("Uniteller\\Images", m_sStateMachineName));
          SmartPointer<IVariant> generations;
          generations <<= moduleInfo->GetSubKeyValue("Generations");
          return CheckGeneration(generation, generations);
        }

        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ��������
        /// </summary>
        /// <param name="szProtocol">��������.</param>
        /// <param name="generation">��������� ���������.</param>
        bool IsProtocolSupported(const char * szProtocol, int generation)
        {
          RegistryKeyWrapper moduleInfo;
          moduleInfo <<= OpenKey(MAKE_PATH("Uniteller\\Images", m_sStateMachineName));
          SmartPointer<IVariant> generations;
          generations <<= moduleInfo.GetKeyValue(((string)"Protocols\\" + szProtocol).c_str());
          if (generations.p)
            return CheckGeneration(generation, generations);
          return false;
        }

        /// <summary>
        /// ��������� ���������� �������� ���������� ���������
        /// </summary>
        void SetContextVariable(const char * name, IVariant * value)
        {
          m_StateMachine->SetContextVariable(name, value);
        }

        /// <summary>
        /// ��������� ���������� �������� ���������� ���������
        /// </summary>
        template <class Z>
        void SetContextVariable(const char * name, const Z & value)
        {
          SmartPointer<IVariant> data;
          data <<= new Variant(value);
          m_StateMachine->SetContextVariable(name, data);
        }

        /// <summary>
        /// ��������� ���������� ��������� ������� � ����������� ���������� ���������, ����������� SchemeLoader-�� ������� ���������
        /// </summary>
        void SetProperties(IEnumeration<IVariant *> * properties)
        {
          int max = properties->GetCount();
          int i = 0;
          while (i<max)
          {
            SmartPointer<IVariant> vName, vValue;
            vName <<= properties->GetItem(i);
            ++i;
            vValue <<= properties->GetItem(i);
            ++i;
    
            const std::string name = Variant::ConvertTo<string>(vName.p);
    
            m_StateMachine->SetContextVariable(name.c_str(), vValue.p);
          }
        }


        /// <summary>
        /// ��������� �������� �������� ���������� ���������
        /// </summary>
        IVariant * GetContextVariable(const char * name)
        {
          return m_StateMachine->GetContextVariable(name);
        }

        template <class Y>
        Y GetContextVariable(const char * name)
        {
          SmartPointer<IVariant> value;
          value <<= m_StateMachine->GetContextVariable(name);
          if (value.p)
            return Variant::ConvertTo<Y>(value.p);
          else
          {
            printf("[FATAL] Variable %s was not found\n", name);
            throw KernelException("Variable %s was not found", name);
          }
        }

        template <class Y>
        bool TryGetContextVariable(const char * name, Y & result)
        {
          SmartPointer<IVariant> value;
          value <<= m_StateMachine->GetContextVariable(name);
          if (value.p)
          { 
            result = Variant::ConvertTo<Y>(value.p);
            return true;
          }
          return false;
        }

      protected:
        IRegistryKey * OpenKey(const char * szKeyName)
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          return registry->Open(szKeyName, true);
        }
        /// <summary>
        /// ��������� ��������� xpath-������ �� �������
        /// </summary>
        /// <param name="xpath">������</param>
        IRegistryKey * SelectFirst(const char * xpath)
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          return registry->SelectFirst(xpath);
        }
        /// <summary>
        /// ��������� ��������� xpath-������ �� ������� � ��������� ���������� ������� �� �� �������
        /// </summary>
        /// <param name="xpath">������</param>
        bool NotEmpty(const char * xpath)
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          return registry->NotEmpty(xpath);
        }

        IRegistry * GetRegistry()
        {
          return m_Api->GetRegistry();
        }
        IProtocolReflection * GetReflector()
        {
          return m_Api->GetReflector();
        }

        // ������ � UniText

        /// <summary>
        /// ��������� ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szText">����� ��� �������</param>
        /// <returns>������ �������</returns>
        IEnumeration<IRegistryHive *> * ParseUniText(const char * szText)
        {
          return m_Api->ParseUniText(szText);
        }

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ���������� � ������ �����-���� �������� ����-������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        void LoadUniTextDataSource(const char * szPath)
        {
          m_Api->LoadUniTextDataSource(szPath);
        }

        void LoadUtcDataSource(const char * szPath)
        {
          m_Api->LoadUtcDataSource(szPath);
        }

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        /// <returns>������ �������</returns>
        IEnumeration<IRegistryHive *> * LoadUniTextFile(const char * szPath)
        {
          return m_Api->LoadUniTextFile(szPath);
        }

        IEnumeration<IRegistryHive *> * LoadUtcFile(const char * szText)
        {
          return m_Api->LoadUtcFile(szText);
        }

        void WriteUtcFile(const char * szFileName, IEnumeration<IRegistryHive *> * hives)
        {
          m_Api->WriteUtcFile(szFileName, hives);
        }

        void WriteUniTextFile(const char * szFileName, IEnumeration<IRegistryHive *> * hives)
        {
          m_Api->WriteUniTextFile(szFileName, hives);
        }

        void OverrideTimeOut(int newTimeOut)
        {
#ifndef __GNUG__
          _InterlockedExchange(&m_TimeOutOvveride, newTimeOut);
#else
          m_TimeOutOvveride = newTimeOut;
#endif
        }

        int GetTimeOutOvveride()
        {
#ifndef __GNUG__
          return _InterlockedExchange(&m_TimeOutOvveride, -1);
#else
          int result = m_TimeOutOvveride;
          m_TimeOutOvveride = -1;
          return result;
#endif
        }

        bool CheckGeneration(int generation, IVariant * generations)
        {
          switch (generations->GetType())
          {
          case VariantType::IntegerValue:
            return ((Variant *)generations)->ConvertTo<int>() == generation;
          case VariantType::ArrayValue:
            {
              std::set<int> value = ((Variant *)generations)->ConvertTo<std::set<int>>();
              return value.find(generation) != value.end();
            }
          default:
            return false;
          }
        }

        /// <summary>
        /// ���������� root-���� ��������� �����-����
        /// </summary>
        std::string GetSystemRoot()
        {
          SmartPointer<IFactory> factory;
          factory <<= m_Api->GetStandardFactory();
          return factory->GetSystemRoot();
        }
      };
      
      #define BEGIN_HANDLERS_MAP() \
        void LoadHandlers() {

      #define REGISTER_HANDLER(From, To, Event, Handler) AddEventHandler(From, To, Event, Handler##System);
      #define REGISTER_STD_HANDLER(From, To, Event, Generation) AddEventHandler(From, To, Protocol::G##Generation::Codes::Event, &Machine::Event##Handler##Generation##System);

      #define END_HANDLERS_MAP() }

      #define DECLARE_HANDLER(Handler, Message) \
      void Handler##System(IMessage * message) \
      { \
        const Message msg(message); \
        Handler(msg); \
      } \
      void Handler(const Message & message)

      #define DECLARE_ASYNC_HANDLER(Handler, Message) \
      void Handler##System(IMessage * message) \
      { \
        message->AddRef(); \
        std::thread(&Machine::Handler##SystemAsync, this, message).detach();\
      } \
      void Handler##SystemAsync(IMessage * message) \
      { \
        const Message msg(message); \
        Handler(msg); \
        message->Release(); \
      } \
      void Handler(const Message & message)

      // ��������� ������ �������� ��� ��������� ��� ����������
      #define DECLARE_EVENT_HANDLER(Handler) \
      void Handler##System(IMessage * ) \
      { \
        Handler(); \
      } \
      void Handler()

      // ����������� ���������� (� ����� ������)
      #define DECLARE_ASYNC_EVENT_HANDLER(Handler) \
      void Handler##System(IMessage * ) \
      { \
        std::thread(&Machine::Handler, this).detach();\
      } \
      void Handler()

      #define DECLARE_STD_HANDLER(Message, Generation) \
      void Message##Handler##Generation##System(IMessage * message) \
      { \
        const Protocol::G##Generation::Message msg(message); \
        Message##Handler(msg); \
      } \
      void Message##Handler(const Protocol::G##Generation::Message & message)

      #define DECLARE_ASYNC_STD_HANDLER(Message, Generation) \
      void Message##Handler##Generation##System(IMessage * message) \
      { \
        message->AddRef(); \
        std::thread(&Machine::Message##Handler##Generation##SystemAsync, this, message).detach();\
      } \
      void Message##Handler##Generation##SystemAsync(IMessage * message) \
      { \
        const Protocol::G##Generation::Message msg(message); \
        Message##Handler(msg); \
        message->Release(); \
      } \
      void Message##Handler(const Protocol::G##Generation::Message & message)

      #define DECLARE_2G_HANDLER(Handler, Message, Generation1, Generation2) \
      void Handler##System(IMessage * message) \
      { \
        switch (message->GetGeneration()) \
        { \
        case Generation1: \
          { \
            const Protocol::G##Generation1::Message msg(message); \
            Handler(msg); \
          } \
          break; \
        case Generation2: \
          { \
            const Protocol::G##Generation2::Message msg(message); \
            Handler(msg); \
          } \
          break; \
        default: \
          { \
            Framework::Kernel::Protocol::G1::GenerationNotSupported answer; \
            answer.SetEventKind(message->GetKind()); \
            answer.SetMessageGeneration(message->GetGeneration()); \
            if (strcmp(message->GetTargetId(), "master")==0) \
            { \
              answer->SetSourceId(GetUnicalId()); \
              m_MqController->SendMessage(message->GetSourceId(), answer); \
            } \
            else\
              m_RequestDispatcher->SendMessage(message->GetSourceId(), answer); \
          } \
        }\
      } \
      void Handler(const Protocol::G##Generation1::Message & message); \
      void Handler(const Protocol::G##Generation2::Message & message);

      
      #define IMPLEMENT_STD_HANDLER(Message, Generation) void Machine::Message##Handler(const Protocol::G##Generation::Message & message)

      #define STD_HANDLER(Message, Generation) void Machine::Message##Handler##Generation(Protocol::G##Generation::Message & message)

      #define DECLARE_CHAIN_HANDLER(Handler, Message) \
      void Handler##System(IMessage * message) \
      {\
        const Message msg(message); \
        const string & src = msg.GetSourceId(); \
        Message##Answer answer; \
        if (Handler(msg, answer)) \
        {\
          if (strcmp(message->GetTargetId(), "master")==0) \
          { \
            answer->SetSourceId(GetUnicalId()); \
            m_MqController->SendMessage(src.c_str(), answer); \
          } \
          else\
            m_RequestDispatcher->SendMessage(src.c_str(), answer); \
        } \
      } \
      bool Handler(const Message & message, Message##Answer & answer)

      #define DECLARE_ASYNC_CHAIN_HANDLER(Message, Generation) \
      void Message##Handler##Generation##System(IMessage * message) \
      {\
        message->AddRef(); \
        std::thread(&Machine::Message##Handler##Generation##SystemAsync, this, message).detach();\
      }\
      void Message##Handler##Generation##SystemAsync(IMessage * message) \
      { \
        const Protocol::G##Generation::Message msg(message); \
        const string & src = msg.GetSourceId(); \
        Protocol::G##Generation::Message##Answer answer; \
        if (Message##Handler(msg, answer)) \
        {\
          if (strcmp(msg->GetTargetId(), "master")==0) \
          { \
            answer->SetSourceId(GetUnicalId()); \
            m_MqController->SendMessage(src.c_str(), answer); \
          }\
          else \
            m_RequestDispatcher->SendMessage(src.c_str(), answer); \
        }\
        message->Release(); \
      } \
      bool Message##Handler(const Protocol::G##Generation::Message & message, Protocol::G##Generation::Message##Answer & answer)

      #define AUTOANSWER_HANDLER(Handler, Message, Command) \
      void Handler##System(IMessage * message) \
      {\
        const Message msg(message); \
        const string & src = msg.GetSourceId(); \
        Message##Answer answer; \
        Command; \
        if (strcmp(message->GetTargetId(), "master")==0) \
        { \
          answer->SetSourceId(GetUnicalId()); \
          m_MqController->SendMessage(src.c_str(), answer); \
        } \
        else\
          m_RequestDispatcher->SendMessage(src.c_str(), answer); \
      }

      #define DECLARE_STD_CHAIN_HANDLER(Message, Generation) \
      void Message##Handler##Generation##System(IMessage * message) \
      { \
        const Protocol::G##Generation::Message msg(message); \
        const string & src = msg.GetSourceId(); \
        Protocol::G##Generation::Message##Answer answer; \
        if (Message##Handler(msg, answer)) \
        {\
          if (strcmp(msg->GetTargetId(), "master")==0) \
          { \
            answer->SetSourceId(GetUnicalId()); \
            m_MqController->SendMessage(src.c_str(), answer); \
          }\
          else \
            m_RequestDispatcher->SendMessage(src.c_str(), answer); \
        }\
      } \
      bool Message##Handler(const Protocol::G##Generation::Message & message, Protocol::G##Generation::Message##Answer & answer)


      #define DECLARE_SAFE_CHAIN_HANDLER(Handler, Message, Validator) \
      void Handler##System(IMessage * message) \
      {\
        const Message msg(message); \
        const string & src = msg.GetSourceId(); \
        Message##Answer answer; \
        try \
        { \
        if (Handler(msg, answer)) \
        {\
          if (strcmp(message->GetTargetId(), "master")==0) \
          { \
            answer->SetSourceId(GetUnicalId()); \
            m_MqController->SendMessage(src.c_str(), answer); \
          } \
          else\
            m_RequestDispatcher->SendMessage(src.c_str(), answer); \
        } \
        } \
        catch (Validator::Exception & e) \
        { \
          Validator::ErrorMessage notification; \
          if (!Validator::InitializeNotification(e, notification)) \
            throw; \
          m_RequestDispatcher->SendMessage(src.c_str(), notification); \
        } \
      } \
      bool Handler(const Message & message, Message##Answer & answer)


      #define DECLARE_SAFE_HANDLER(Handler, Message, Validator) \
      void Handler##System(IMessage * message) \
      { \
        const Message msg(message); \
        try \
        { \
          Handler(msg); \
        } \
        catch (Validator::Exception & e) \
        { \
          Validator::ErrorMessage notification; \
          if (!Validator::InitializeNotification(e, notification)) \
            throw; \
          m_RequestDispatcher->SendMessage(msg.GetSourceId(), notification); \
        } \
      } \
      void Handler(const Message & message)

      // ��������� ������ �������� ��� ��������� ��� ����������
      #define DECLARE_SAFE_EVENT_HANDLER(Handler, Validator) \
      void Handler##System(IMessage * message) \
      { \
        try \
        { \
          Handler(); \
        } \
        catch (Validator::Exception & e) \
        { \
          Validator::ErrorMessage notification; \
          if (!Validator::InitializeNotification(e, notification)) \
            throw; \
          m_RequestDispatcher->SendMessage(message->GetSourceId(), notification); \
        } \
      } \
      void Handler()

      #define DECLARE_SAFE_STD_HANDLER(Message, Generation, Validator) \
      void Message##Handler##Generation##System(IMessage * message) \
      { \
        const Protocol::G##Generation::Message msg(message); \
        try \
        { \
          Message##Handler(msg); \
        } \
        catch (Validator::Exception & e) \
        { \
          Validator::ErrorMessage notification; \
          if (!Validator::InitializeNotification(e, notification)) \
            throw; \
          m_RequestDispatcher->SendMessage(msg.GetSourceId(), notification); \
        } \
      } \
      void Message##Handler(const Protocol::G##Generation::Message & message)


#ifndef __GNUG__
      template <class Implementation, class T, class H, class EndPoint = IProtocolEndPoint>
      class Interceptor : public SystemObject<Implementation, T, EndPoint>
#else
      template <class Implementation, class T, class H, class EventHandler, class EndPoint = IProtocolEndPoint>
      class Interceptor : public SystemObject<Implementation, T, EventHandler, EndPoint>
#endif
      {
      protected:
        SmartPointer<H> m_apiHandler;
        std::string m_sApiId;
      public:
        IExportable * GetApiEndpoint()
        {
          return m_apiHandler.Copy();
        }
        const char * GetApiId()
        {
          return m_sApiId.c_str();
        }
        /// <summary>
        /// ����������� ������� �������
        /// </summary>
        /// <param name="szName">��� ��������� �������� ��� ��������.</param>
        Interceptor(const char * szName, IKernelApi * api, const char * apiId) :
#ifndef __GNUG__
          SystemObject(szName, api), 
#else
          SystemObject<Implementation, T, EventHandler, EndPoint>(szName, api), 
#endif
          m_sApiId(apiId)
        {
        }
      };

// ������ �������� ���������� ��� �������� ������ ������������� � GCC
#ifndef __GNUG__          
#define SystemObjectImpl(x,y) SystemObject<x, y>          
#define MachineImpl SystemObject<Machine, ISystemObject>  
#define InterceptorImpl Kernel::Interceptor<Machine, IPlatformInterceptor, CApiHandler>        
#else
#define SystemObjectImpl(x,y) SystemObject<x, y, void (x::*)(IMessage * message)>
#define MachineImpl SystemObject<Machine, ISystemObject, void (Machine::*)(IMessage * message)>
#define InterceptorImpl Kernel::Interceptor<Machine, IPlatformInterceptor, CApiHandler, void (Machine::*)(IMessage * message)>  
#endif


#ifndef __GNUG__
      template <class Implementation, class T, class EndPoint = IProtocolEndPoint>
#else
      template <class Implementation, class T, typename EventHandler, class EndPoint = IProtocolEndPoint>
#endif
      class NativeLibrary : public ObjectBase<T>, public EndPoint
      {
        // � �������� ��������� ������� ���������� ���������, ����������� ISystemObject
        typedef typename T::IsSystemObject OnlySystemObject;
      private:
        // ��� ��������� ��������
        std::string m_sStateMachineName;

        bool m_IsConnected;
        bool m_IsStopped;

#ifndef __GNUG__
        // �������������� ��� ����������� �������
        typedef typename void (Implementation::* EventHandler)(IMessage * message);
#endif

        // ��� ����� ������������ �������
        typedef typename std::map<unsigned __int64, EventHandler> EventHandlersMap;

        EventHandlersMap m_Handlers;

        SmartPointer<IKernelApi> m_Api;

        std::mutex m_Lock;

        long m_TimeOutOvveride;

        event_t m_Kind;

        SmartPointer<IMessageFilter> m_Filter;
      public:
        /// <summary>
        /// ����������� ������� �������
        /// </summary>
        /// <param name="szName">��� ��������� �������� ��� ��������.</param>
        NativeLibrary(const char * szName, IKernelApi * api) :
#ifdef __GNUG__
          ObjectBase<T>(szName),
#endif
          m_sStateMachineName(szName), m_IsConnected(false), m_TimeOutOvveride(-1), m_IsStopped(false),
          m_Api(api)
        {
#ifndef __GNUG__
          m_sType = szName;
#endif
          m_Filter<<=new MessageFilter();
          m_Filter->Add(Protocol::G1::Codes::Stop);
        }

        /// <summary>
        /// ��������� ����������� ������ ����������� � ���� �������� ��������� � ��������� �����-�� �������� ��������
        /// </summary>
        void OnConnected() override
        {
          if (!m_IsConnected)
          {
            // ��������� �����������
            LoadHandlers();
            m_IsConnected = true;
            OnMachineStarted();
            ObjectBase<T>::SetFilter(false, m_Filter.p);
          }
        }

        /// <summary>
        /// ���������� ����-���
        /// </summary>
        void RaiseTimeOut()
        {
          std::unique_lock<std::mutex> lk(m_Lock);
          SendEvent(this->GetUnicalId(), Kernel::Protocol::G1::Codes::TimeOut);
        }

        const char * GetMachineName() const
        {
          return m_sStateMachineName.c_str();
        }

        const char * GetOldState() const
        {
          return "Idle";
        }


        /// <summary>
        /// ��������� �������� ������ ������������ �������
        /// </summary>
        /// <param name="filter"> ������ ������� </param>
        void SetOutboxFilter(IMessageFilter * , const char * , const char * )
        {
        }

        /// <summary>
        /// ��������� ������������� ������� ��������� ��������� ������
        /// </summary>
        /// <param name="nFrom"> ���������-�������� </param>
        /// <param name="nTo"> ���������-�������� </param>
        /// <param name="evt"> �������, �������������� ������� </param>
        void OnTransition(const __int16 nFrom, const __int16 nTo, IMessage * evt)
        {
          m_Kind = evt->GetKind();
          unsigned long long eventCode = MAKE_EVENT_CODE(nFrom, nTo, m_Kind);
          try
          {
            if (!FindAndCallHandler(eventCode, evt))
            {
              eventCode = MAKE_EVENT_CODE(nFrom, nTo, (m_Kind & 0xFFFF0000)); // ���������� ����� ������� � ������ ���������
                                                                              //eventCode &= 0xFFFFFFFFFFFF0000;
              if (!FindAndCallHandler(eventCode, evt))
              {
                eventCode = MAKE_EVENT_CODE(nFrom, nTo, 0); // ���������� ����� �������
                                                            //eventCode &= 0xFFFFFFFFFFFF0000;
                FindAndCallHandler(eventCode, evt);
              }
            }
          }
          catch (KernelException & ex)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("KernelException");
            answer.SetExceptionMessage(ex.what());
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
          catch (std::exception & stdex)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("std::exception");
            answer.SetExceptionMessage(stdex.what());
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
          catch (...)
          {
            Protocol::G1::ModuleFailedOnEvent answer;
            answer.SetEventKind(m_Kind);
            answer.SetExceptionKind("Unknown");
            answer.SetExceptionMessage("Unhandled C++ exception on handle transition");
#ifndef __GNUG__
            m_RequestDispatcher->SendMessage(evt->GetSourceId(), answer);
#else
            this->SendMessageRd(evt->GetSourceId(), answer);
#endif
          }
        }

        /// <summary>
        /// ������������ ��� ������ � ������ �����������.
        /// </summary>
        /// <param name="handler"> ��� ����������� </param>
        /// <param name="evt"> ���������-��������� </param>
        bool FindAndCallHandler(unsigned long long handler, IMessage * evt)
        {
          typename EventHandlersMap::iterator i = m_Handlers.find(handler);
          if (i != m_Handlers.end())
          {
            // �������� ����������! todo- ������ �� �����
            EventHandler p = i->second;
            Implementation * pImplementation = (Implementation *)(this);
            if (pImplementation)
              (pImplementation->*p)(evt); // ����� �����������
            return true;
          }
          return false;
        }


        /// <summary>
        /// ��������� ����������� ������ ������� ������
        /// </summary>
        virtual void OnMachineStarted()
        {
        }
        /// <summary>
        /// ��������� ����������� ������ ��������� ������
        /// </summary>
        virtual void OnMachineStopped()
        {
          m_IsStopped = true;

          // ����������� �� ���� � ��������� ������
#ifndef __GNUG__
          m_RequestDispatcher->Disconnect();
#else
          this->Disconnect();
#endif
        }

        /// <summary>
        /// ��������� ������� ������� �������� ��������� �� ���� �������� ���������
        /// </summary>
        /// <param name="message"> ��������� </param>
        bool ProcessMessage(IMessage * message)
        {
          std::unique_lock<std::mutex> lk(m_Lock);
          if (!m_IsStopped) // ���� ���� ������ ����������� - ������ �� ������
          {
            event_t kind = message->GetKind();
            if (kind == Kernel::Protocol::G1::Codes::Stop)
            {
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
              RegisterTransition("Idle", "Stop", kind);
#endif
              OnMachineStopped();
            }
            else
            {
              FindAndCallHandler(kind, message);
#ifndef LIGHTWEIGHT_SYSTEMOBJECT
              RegisterTransition("Idle", "Idle", kind);
#endif
            }
          }

          if (m_IsStopped)
          {
#ifndef __GNUG__
            m_RequestDispatcher.Release();
#else
            this->ReleaseRD();
#endif
            m_Api.Release();
            this->CleanUpIntercepted();
            this->CleanUpMqControllers();
            return true;
          }
          return false;
        }

        void RegisterTransition(const char * szFrom, const char * szTo, event_t evt)
        {
          std::this_thread::yield();
          Protocol::G1::StateChanged message;
          message.SetEvent(evt);
          message.SetOldState(szFrom);
          message.SetNewState(szTo);
          message.SetMachineName(m_sStateMachineName.c_str());
#ifndef __GNUG__
          m_RequestDispatcher->SendMessage("master", message.p); // ����� ������ ������ ���� �� �����
#else
          this->SendMessageRd("master", message.p); // ����� ������ ������ ���� �� �����
#endif
        }

      protected:

        /// <summary>
        /// ����������� ������������ ��������� � ��������
        /// </summary>
        /// <param name="szFrom">���������, ������� �������� �������.</param>
        /// <param name="szTo">���������, � ������� �������� �������.</param>
        /// <param name="kind">��� �������.</param>
        /// <param name="handler">������� ����������.</param>
        void AddEventHandler(const char * , const char * , event_t kind, EventHandler handler)
        {
          unsigned long long eventCode = MAKE_EVENT_CODE(0, 0, kind);
          m_Handlers.insert(std::make_pair(eventCode, handler));
          
          m_Filter->Add(kind);
        }

        // ��������� ���  ����������� ����� ������������ �������
        virtual void LoadHandlers()
        {
        }
      protected: // �������� ���������

        bool SendMessage(address reciver, IMessage * message)
        {
#ifndef __GNUG__
          if (m_RequestDispatcher.p)
          {
            if (message)
              message->SetSourceId(GetUnicalId());
            return m_RequestDispatcher->SendMessage(reciver, message);
          }
          return false;
#else
          if (message)
            message->SetSourceId(this->GetUnicalId());
          return this->SendMessageRd(reciver, message);
#endif
        }

        bool SendEvent(address reciver, event_t message, int generation = 1, int priority = 0)
        {
#ifndef __GNUG__
          if (m_RequestDispatcher.p)
            return m_RequestDispatcher->SendEvent(reciver, message, generation, priority);
#else
          return this->SendEventRd(reciver, message, generation, priority);
#endif
          return false;
        }

        bool SendMessageToControlledBus(address reciver, IMessage * message)
        {
#ifndef __GNUG__
            switch (*reciver)
            {
            case 'm':
              if (strcmp(reciver + 1, "aster") == 0)
                return m_RequestDispatcher->SendMessage(reciver, message);
              break;
            case ':':
              ++reciver;
              return m_RequestDispatcher->SendMessage(reciver, message);
            case 's':
              if (strcmp(reciver + 1, "elf") == 0)
                return m_RequestDispatcher->SendMessage(GetUnicalId(), message);
              break;
            }
            message->SetSourceId("master");

            return m_MqController->SendMessage(reciver, message);
#else

            switch (*reciver)
            {
            case 'm':
              if (strcmp(reciver + 1, "aster") == 0)
                return this->SendMessageRd(reciver, message);
              break;
            case ':':
              ++reciver;
              return this->SendMessageRd(reciver, message);
            case 's':
              if (strcmp(reciver + 1, "elf") == 0)
                return this->SendMessageRd(this->GetUnicalId(), message);
              break;
            }

            message->SetSourceId("master");
            return this->SendMessageMq(reciver, message);
#endif
        }

        bool SendMessageToControlledBus(address reciver, address alias, IMessage * message)
        {
          if (strcmp(alias, "self") == 0)
            alias = this->GetUnicalId();
          else
            if (!this->IsIntercepted(alias))
              return false;
            message->SetSourceId(alias);
#ifndef __GNUG__
            switch (*reciver)
            {
            case ':':
              ++reciver;
              return m_RequestDispatcher->SendMessage(reciver, message);
            case 'm':
              if (strcmp(reciver + 1, "aster") == 0)
                return m_RequestDispatcher->SendMessage(reciver, message);
              break;
            case 's':
              if (strcmp(reciver + 1, "elf") == 0)
                return m_RequestDispatcher->SendMessage(GetUnicalId(), message);
              break;
            }
            return m_MqController->SendMessage(reciver, message);
#else
            switch (*reciver)
            {
            case ':':
              ++reciver;
              return this->SendMessageRd(reciver, message);
            case 'm':
              if (strcmp(reciver + 1, "aster") == 0)
                return this->SendMessageRd(reciver, message);
              break;
            case 's':
              if (strcmp(reciver + 1, "elf") == 0)
                return this->SendMessageRd(this->GetUnicalId(), message);
              break;
            }
            return this->SendMessageMq(reciver, message);
#endif
        }

        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ���������
        /// </summary>
        /// <param name="generation">���������.</param>
        bool IsGenerationSupported(int generation)
        {
          RegistryKeyWrapper moduleInfo;
          moduleInfo <<= OpenKey(MAKE_PATH("Uniteller\\Images", m_sStateMachineName));
          SmartPointer<IVariant> generations;
          generations <<= moduleInfo->GetSubKeyValue("Generations");
          return CheckGeneration(generation, generations);
        }

        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ��������
        /// </summary>
        /// <param name="szProtocol">��������.</param>
        /// <param name="generation">��������� ���������.</param>
        bool IsProtocolSupported(const char * szProtocol, int generation)
        {
          RegistryKeyWrapper moduleInfo;
          moduleInfo <<= OpenKey(MAKE_PATH("Uniteller\\Images", m_sStateMachineName));
          SmartPointer<IVariant> generations;
          generations <<= moduleInfo.GetKeyValue(((string)"Protocols\\" + szProtocol).c_str());
          if (generations.p)
            return CheckGeneration(generation, generations);
          return false;
        }

        ///// <summary>
        ///// ��������� ���������� �������� ���������� ���������
        ///// </summary>
        //void SetContextVariable(const char * name, IVariant * value)
        //{
        //  throw new KernelException("Library ");
        //}

        ///// <summary>
        ///// ��������� ���������� �������� ���������� ���������
        ///// </summary>
        //template <class Z>
        //void SetContextVariable(const char * name, const Z & value)
        //{
        //  SmartPointer<IVariant> data;
        //  data <<= new Variant(value);
        //  m_StateMachine->SetContextVariable(name, data);
        //}

        ///// <summary>
        ///// ��������� ���������� ��������� ������� � ����������� ���������� ���������, ����������� SchemeLoader-�� ������� ���������
        ///// </summary>
        //void SetProperties(IEnumeration<IVariant *> * properties)
        //{
        //  int max = properties->GetCount();
        //  int i = 0;
        //  while (i<max)
        //  {
        //    SmartPointer<IVariant> vName, vValue;
        //    vName <<= properties->GetItem(i);
        //    ++i;
        //    vValue <<= properties->GetItem(i);
        //    ++i;

        //    const std::string name = Variant::ConvertTo<string>(vName.p);

        //    m_StateMachine->SetContextVariable(name.c_str(), vValue.p);
        //  }
        //}


        ///// <summary>
        ///// ��������� �������� �������� ���������� ���������
        ///// </summary>
        //IVariant * GetContextVariable(const char * name)
        //{
        //  return m_StateMachine->GetContextVariable(name);
        //}

        //template <class Y>
        //Y GetContextVariable(const char * name)
        //{
        //  SmartPointer<IVariant> value;
        //  value <<= m_StateMachine->GetContextVariable(name);
        //  if (value.p)
        //    return Variant::ConvertTo<Y>(value.p);
        //  else
        //  {
        //    printf("[FATAL] Variable %s was not found\n", name);
        //    throw KernelException("Variable %s was not found", name);
        //  }
        //}

        //template <class Y>
        //bool TryGetContextVariable(const char * name, Y & result)
        //{
        //  SmartPointer<IVariant> value;
        //  value <<= m_StateMachine->GetContextVariable(name);
        //  if (value.p)
        //  {
        //    result = Variant::ConvertTo<Y>(value.p);
        //    return true;
        //  }
        //  return false;
        //}

      protected:
        IRegistryKey * OpenKey(const char * szKeyName)
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          return registry->Open(szKeyName, true);
        }
        IRegistry * GetRegistry()
        {
          return m_Api->GetRegistry();
        }
        IProtocolReflection * GetReflector()
        {
          return m_Api->GetReflector();
        }

        // ������ � UniText

        /// <summary>
        /// ��������� ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szText">����� ��� �������</param>
        /// <returns>������ �������</returns>
        IEnumeration<IRegistryHive *> * ParseUniText(const char * szText)
        {
          return m_Api->ParseUniText(szText);
        }

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ���������� � ������ �����-���� �������� ����-������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        void LoadUniTextDataSource(const char * szPath)
        {
          m_Api->LoadUniTextDataSource(szPath);
        }

        void LoadUtcDataSource(const char * szPath)
        {
          m_Api->LoadUtcDataSource(szPath);
        }

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        /// <returns>������ �������</returns>
        IEnumeration<IRegistryHive *> * LoadUniTextFile(const char * szPath)
        {
          return m_Api->LoadUniTextFile(szPath);
        }

        IEnumeration<IRegistryHive *> * LoadUtcFile(const char * szText)
        {
          return m_Api->LoadUtcFile(szText);
        }

        void WriteUtcFile(const char * szFileName, IEnumeration<IRegistryHive *> * hives)
        {
          m_Api->WriteUtcFile(szFileName, hives);
        }

        void WriteUniTextFile(const char * szFileName, IEnumeration<IRegistryHive *> * hives)
        {
          m_Api->WriteUniTextFile(szFileName, hives);
        }

        void OverrideTimeOut(int newTimeOut)
        {
#ifndef __GNUG__
          _InterlockedExchange(&m_TimeOutOvveride, newTimeOut);
#else
          m_TimeOutOvveride = newTimeOut;
#endif
        }

        int GetTimeOutOvveride()
        {
#ifndef __GNUG__
          return _InterlockedExchange(&m_TimeOutOvveride, -1);
#else
          int result = m_TimeOutOvveride;
          m_TimeOutOvveride = -1;
          return result;
#endif
        }

        bool CheckGeneration(int generation, IVariant * generations)
        {
          switch (generations->GetType())
          {
          case VariantType::IntegerValue:
            return ((Variant *)generations)->ConvertTo<int>() == generation;
          case VariantType::ArrayValue:
          {
            std::set<int> value = ((Variant *)generations)->ConvertTo<std::set<int>>();
            return value.find(generation) != value.end();
          }
          }
          return false;
        }

        /// <summary>
        /// ���������� root-���� ��������� �����-����
        /// </summary>
        std::string GetSystemRoot()
        {
          SmartPointer<IFactory> factory;
          factory <<= m_Api->GetStandardFactory();
          return factory->GetSystemRoot();
        }
      };

#ifndef __GNUG__          
#define LibraryImpl NativeLibrary<Machine, ISystemObject>          
#else
#define LibraryImpl NativeLibrary<Machine, ISystemObject, void (Machine::*)(IMessage * message)>
#endif

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller