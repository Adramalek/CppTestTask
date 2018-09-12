// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс коллекции-перечисления

#pragma once

#include "icollection.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс множества
      /// </summary>
      template <class T>
      interface ISet : public ICollection<T>
      {
      public:
        /// <summary>
        /// Позволяет понять принадлежит ли указанное значение множеству
        /// </summary>
        virtual bool Contains(const T & value) = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller