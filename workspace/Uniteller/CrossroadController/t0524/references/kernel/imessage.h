// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс сообщения, передаваемого по шине передачи сообщений

#pragma once

#include "ivariant.h"
#include <chrono> // std::system_clock

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      typedef const char * address;
      typedef unsigned int event_t;      
      typedef std::chrono::system_clock::time_point timestamp_t;
      
      /// <summary>
      /// Интерфейс сообщения
      /// </summary>
      interface IMessage : public IExportable
      {
      public: // Свойства
        
        // поколение
        READONLY_PROPERTY_DECLARATION(int, Generation);
        // тип сообщения
        READONLY_PROPERTY_DECLARATION(event_t, Kind);

        // приоритет
        PROPERTY_DECLARATION(int, Priority);
        // число аргументов сообщения
        PROPERTY_DECLARATION(size_t, ArgumentsCount);
        // идентификатор источника сообщения
        PROPERTY_DECLARATION_STRING(SourceId);
        // идентификатор приемника сообщения
        PROPERTY_DECLARATION_STRING(TargetId);
        // Время отправки сообщения
        PROPERTY_DECLARATION(timestamp_t, SendTime);               
      public: // Методы

        /// <summary>
        /// Позволяет очистить массив аргументов сообщения
        /// </summary>
        virtual void Clear() = 0;

        /// <summary>
        /// Позволяет получить аргумент сообщения по индексу
        /// </summary>
        /// <param name="index">Индекс аргумента</param>
        /// <returns>Аргумент сообщения</returns>
        virtual IVariant * GetArgument(size_t index) = 0;
        /// <summary>
        /// Позволяет установить аргумент сообщения по индексу
        /// </summary>
        /// <param name="index">Индекс аргумента</param>
        /// <param name="value">Аргумент сообщения</param>
        virtual void SetArgument(size_t index, IVariant * value) = 0;
        /// <summary>
        /// Позволяет установить аргумент сообщения по индексу (путем присоединения)
        /// </summary>
        /// <param name="index">Индекс аргумента</param>
        /// <param name="value">Аргумент сообщения</param>
        virtual void SetArgumentTo(size_t index, IVariant * value) = 0;
      };

      // Указатель на сообщение
      typedef SmartPointer<IMessage> MessagePtr;

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller