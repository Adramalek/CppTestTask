// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс запускаемого объекта

#pragma once

#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

#pragma region IStartable

      /// <summary>
      /// Интерфейс запускаемого объекта
      /// </summary>
      template <class T>
      interface IStartable : public IExportable
      {
      public: // Свойства
        // запущен ли
        READONLY_PROPERTY_DECLARATION(bool, IsStarted);
      public: // Методы
        /// <summary>
        /// Запускает запускаемый объект
        /// </summary>
        /// <param name="context"> Контекст </param>
        virtual void Start(T * context) = 0;
        /// <summary>
        /// Останавливает запускаемый объект
        /// </summary>
        virtual void Stop() = 0;


        /// Используется специализированными обертками для контроля имплементации интерфейса IExportable
        typedef int IsStartable;
      };

      /// <summary>
      /// Интерфейс запускаемого объекта
      /// </summary>
      template <>
      interface IStartable<void> : public IExportable
      {
      public: // Свойства
        // запущен ли
        READONLY_PROPERTY_DECLARATION(bool, IsStarted);
      public: // Методы
        /// <summary>
        /// Запускает запускаемый объект
        /// </summary>
        virtual void Start() = 0;
        /// <summary>
        /// Останавливает запускаемый объект
        /// </summary>
        virtual void Stop() = 0;


        /// Используется специализированными обертками для контроля имплементации интерфейса IExportable
        typedef int IsStartable;
      };

#pragma endregion


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller