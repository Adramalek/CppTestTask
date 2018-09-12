// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию исключения KeyAlreadyExistsException (ключ не найден)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {       
      /// <summary>
      /// Обращение к существующему указателю с целью переименования
      /// </summary>
      class KeyAlreadyExistsException : public KernelException
      {
      public:
        /// <summary>
        /// Инициализирует новый экземпляр исключения <see cref="KeyAlreadyExistsException"/>.
        /// </summary>
        /// <param name="path">Ключ, который уже существует.</param>
        explicit KeyAlreadyExistsException(const char * path) : KernelException("Ключ %s уже существует", path)
        {
        }
      };
     

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller