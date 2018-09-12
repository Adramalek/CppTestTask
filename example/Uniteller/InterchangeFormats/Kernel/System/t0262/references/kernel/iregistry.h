// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс реестра мета-данных

#pragma once

#include "iregistrydatasource.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс реестра мета-данных
      /// </summary>
      interface IRegistry : public IExportable
      {
      public: // Методы
        /// <summary>
        /// Позволяет получить ключ реестра мета-данных по имени
        /// </summary>
        virtual IRegistryKey * Open(const char * path, bool create = true) = 0;
        /// <summary>
        /// Позволяет подключить к реестру источник данных
        /// </summary>
        /// <param name="source">The source.</param>
        virtual void AddSource(IRegistryDataSource * source) = 0;
        /// <summary>
        /// Позволяет подключить к реестру источник данных (через массив объектов IRegistryHive)
        /// </summary>
        /// <param name="source">The source.</param>
        virtual void AddHives(IEnumeration<IRegistryHive *> * sources) = 0;
				/// <summary>
				/// Позволяет очистить реестр
				/// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// Позволяет выполнить xpath-запрос на реестре
        /// </summary>
        /// <param name="xpath">Запрос</param>
        virtual IRegistryKey * SelectFirst(const char * xpath) = 0;
        /// <summary>
        /// Позволяет выполнить xpath-запрос на реестре и проверить полученную выборку на не пустоту
        /// </summary>
        /// <param name="xpath">Запрос</param>
        virtual bool NotEmpty(const char * xpath) = 0;
      };
 
      #define MAKE_PATH(root, relative) (std::string(root)+"/"+relative).c_str()

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller