// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс менеджера логов

#pragma once

#include "ilogsource.h" // ILogSource

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс менеджера логов
      /// </summary>
      interface ILogManager : public IExportable
      {
      public:
        /// <summary>
        /// Открывает источник событий в логах
        /// </summary>
        /// <param name="source">Имя источника событий.</param>
        /// <returns>Источник событий (логгер)</returns>
        virtual ILogSource * OpenSource(const char * source) = 0;
      };
      
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller