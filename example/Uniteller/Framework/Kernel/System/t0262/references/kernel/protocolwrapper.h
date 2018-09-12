// Uniteller.Framework.Kernel.Host

// ƒанный файл был сгенерирован автоматически! ≈го ручное изменение запрещено правилами
// процесса разработки. ѕри необходимости изменени€ следует исправить протокол в формате UniText, 
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/xmessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      interface IProtocolEndPoint
      {
      public:
        virtual bool SendMessage(address reciver, IMessage * message) = 0;
        virtual bool SendEvent(address reciver, event_t message, int generation = 1, int priority = 0) = 0;
      };

      class ProtocolWrapper
      {
      protected:
        std::string m_sModuleId;              
        IProtocolEndPoint * m_RequestDispatcher;
      public:
        void SetModuleId(address addr, IProtocolEndPoint * rd)
        {
          m_sModuleId = addr;
          m_RequestDispatcher = rd;
        }
        std::string GetModuleId() const
        {
          return m_sModuleId;
        }
      };                     

      #define USE_PROTOCOL(x, generation, name) x::Protocol::G##generation::Wrapper m_##name;        
      #define BEGIN_WRAPPER() class Wrapper : public ProtocolWrapper { public:
      #define END_WRAPPER() }

      #define IMPLEMENT_PROTOCOL(x, generation, name) x::Protocol::G##generation::Implementation m_##name;  

      #define BEGIN_ENDPOINTS() void OnConnected() { MachineImpl::OnConnected();
      #define END_ENDPOINTS() }

      #define PROTOCOL_ENDPOINT(name, id) m_##name.SetModuleId(id, this);                
      

      #define BEGIN_IMPLEMENTATION() class Implementation : public ProtocolWrapper { public:
      #define END_IMPLEMENTATION() }




#define S(x) ((std::stringstream)(std::stringstream("")<<x)).str()

    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
