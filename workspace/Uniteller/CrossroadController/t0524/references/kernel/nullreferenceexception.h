// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию исключения NullReferenceException (обращение по неверному указателю)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      using std::exception;

      //#define ExceptionMessage(x, y) std::exception((std::string(x)+y).c_str())

      /// <summary>
      /// Обращение к неинициализированному указателю
      /// </summary>
      class NullReferenceException : public KernelException
      {
      public:
        /// <summary>
        /// Инициализирует новый экземпляр исключения <see cref="NullReferenceException"/>.
        /// </summary>
        /// <param name="variable">Имя переменной, которая не инициализирована.</param>
        explicit NullReferenceException(const char * variable) : KernelException((std::string)"Обращение по неинициализированному указателю " + variable)
        {
        }
      };
     

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller