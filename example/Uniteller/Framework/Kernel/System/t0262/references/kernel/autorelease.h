// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию умного указателя (SmartPointer)

#pragma once

#include "smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// Умный указатель для автоматического освобождения указателя. Следует использовать тогда,
      /// когда указатель на экспортируемый объект возвращаемый одной функцией передается в другую функцию
      /// </summary>
      template <class T>
      class AutoRelease
      {
      private:
        T * p;
      public:
        AutoRelease()
        {
        }
        /// <summary>
        /// Initializes a new instance of the <see cref="AutoRelease{T}"/> class.
        /// </summary>
        /// <param name="pointer">The pointer.</param>
        AutoRelease(T * pointer) : p(pointer)
        {
        }
        /// <summary>
        /// Деструктор
        /// </summary>
        ~AutoRelease()
        {
          if (p)
            p->Release();
        }
        /// <summary>
        /// Оператор T*.
        /// </summary>
        /// <returns>
        /// Возвращает указатель 
        /// </returns>
        operator T*() const throw()
        {
          return p;
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller