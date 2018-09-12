// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит перечислимый тип - тревожность

#pragma once

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      enum LogSeverity
      {
        LS_ERROR, // Ошибки
        LS_WARNING, // Предупреждения
        LS_DEBUG, // Отладка (тип информации о стеке вызовов)
        LS_INFO // Информация
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller