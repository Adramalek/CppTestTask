// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс коллекции-перечисления

#pragma once

#include "exportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс перечисления
      /// </summary>
      template <class T>
      interface IEnumeration : public IExportable
      {
      public: // Свойства
        // число элементов в перечислении
        READONLY_PROPERTY_DECLARATION(size_t, Count);
      public: // Методы
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        virtual T GetItem(int index) = 0;				
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller