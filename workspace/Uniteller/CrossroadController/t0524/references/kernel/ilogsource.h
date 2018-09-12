// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс логгера

#pragma once

#include "iexportable.h" // IExportable
#include "logseverity.h" // Тревожность события

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс логгера
      /// </summary>
      interface ILogSource : public IExportable
      {
      public:
        /// <summary>
        /// Регистрирует событие в логе
        /// </summary>
        /// <param name="severity">Тревожность</param>
        /// <param name="message">Сообщение</param>
        /// <param name="">Параметры</param>
        virtual void RegisterEvent(LogSeverity severity, const char * message, ...) = 0;        
        /// <summary>
        /// Регистрирует событие в логе
        /// </summary>
        /// <param name="severity">Тревожность</param>
        /// <param name="message">Сообщение</param>
        /// <param name="">Параметры</param>
        virtual void RegisterEvent(LogSeverity severity, const char * message) = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller