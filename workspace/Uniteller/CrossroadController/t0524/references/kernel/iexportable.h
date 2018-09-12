// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс экспортируемого из dll объекта

#pragma once

#include "autoproperty.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

#pragma region IExportable

      /// <summary>
      /// Интерфейс экспортируемого объекта
      /// </summary>
      interface IExportable
      {
      public:        
        /// <summary>
        /// Виртуальный конструктор (для обеспечения корректного освобождения памяти)
        /// </summary>
        virtual ~IExportable() 
        {
        }
        /// <summary>
        /// Увеличивает счетчик ссылок на экспортированный объект на единицу
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
				virtual long AddRef() = 0;
        /// <summary>
        /// Уменьшает счетчик ссылок на экспортированный объект на единицу 
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
				virtual long Release() = 0;

        /// Используется специализированными обертками для контроля имплементации интерфейса IExportable
        typedef int IsExportable;
      };

#pragma endregion


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller