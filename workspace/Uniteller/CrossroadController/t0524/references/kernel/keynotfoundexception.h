// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию исключения KeyNotFoundException (ключ не найден)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {       
      /// <summary>
      /// Обращение к неинициализированному указателю
      /// </summary>
      class KeyNotFoundException : public KernelException
      {
      public:
        /// <summary>
        /// Инициализирует новый экземпляр исключения <see cref="KeyNotFoundException"/>.
        /// </summary>
        /// <param name="path">Ключ, который не найден.</param>
        explicit KeyNotFoundException(const char * path) : KernelException("Ключ %s не найден", path)
        {
        }
      };
     

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller