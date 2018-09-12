// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс ключа реестра

#pragma once

#include "iregistryhive.h"
#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс источника данных реестра мета-данных
      /// </summary>
      interface IRegistryDataSource : public IExportable
      {
      public: 
      //  PROPERTY_DECLARATION_STRING(ConnectionString, строка подключения);
        /// <summary>
        /// Загружает набор узлов реестра мета-данных из источника данных
        /// </summary>
        /// <returns>Коллекция загруженных узлов реестра</returns>
        virtual IEnumeration<IRegistryHive *> * Load() = 0;
        /// <summary>
        /// Сериализует набор узлов реестра мета-данных
        /// </summary>
        /// <param name="roots">Коллекция узлов реестра.</param>
        virtual void Save(IEnumeration<IRegistryHive *> * roots) = 0;
      };

      typedef SmartPointer<IRegistryDataSource> RegistryDataSourcePtr;


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller