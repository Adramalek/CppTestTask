// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс менеджера логов

#pragma once

#include "ilogmanager.h" // ILogSource
#include <string>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      /// <summary>
      /// Позволяет получить менеджер логов
      /// </summary>
      ILogManager * QueryLogManager();
      
      //template <class T>
      //class Loggerable
      //{
      //protected:
      //  SmartPointer<ILogSource> m_Logger;
      //public:
      //};

      class Enter2Log
      {
      private:
        std::string m_FuncName;
      public:
        Enter2Log(const char *func, const char * args, ...)
        {
          m_FuncName = func;
          m_Args = args;
        }
        std::string m_Args;
      };


      #define DECLARE_LOG_SOURCE(name) \
        protected: \
          SmartPointer<ILogSource> m_Logger; \
        public: \
          void InitLoggingSource() \
          { \
            SmartPointer<ILogManager> manager; \
            manager.Attach(QueryLogManager()); \
            m_Logger.Attach(manager->OpenSource(#name)); \
          }


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller