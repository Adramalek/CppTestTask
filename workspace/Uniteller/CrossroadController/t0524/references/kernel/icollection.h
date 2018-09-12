// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс коллекции-перечисления

#pragma once

#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс коллекции
      /// </summary>
      template <class T>
      interface ICollection : public IEnumeration<T>
      {
      public: // Методы
        /// <summary>
        /// Позволяет очистить перечисление
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// Позволяет добавить элемент в перечисление (в конец)
        /// </summary>
        /// <param name="value">Значение, добавляемое в перечисление</param>
        virtual void Add(const T & value) = 0;
        /// <summary>
        /// Позволяет определить индекс значения в множестве, если оно ему принадлежит
        /// </summary>
        /// <param name="value">Значение для поиска в перечислении</param>
        /// <param name="startIndex">Начинать поиск с элемента с индексом</param>
        /// <returns>Индекс найденного вхождения value или -1 в случае, если такового нет</returns>
        virtual int IndexOf(const T & value, const int startIndex = 0) = 0;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller