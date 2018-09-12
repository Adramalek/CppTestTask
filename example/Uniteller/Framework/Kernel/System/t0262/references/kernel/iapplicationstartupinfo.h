// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс коллекции-перечисления

#pragma once

#include "ienumeration.h"
#include "ioptionscontainer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс объекта, инкапсулирующего параметры для запуска приложения
      /// </summary>
      interface IApplicationStartupInfo : public IOptionsContainer
      {
      public: // Методы
        // Главный модуль приложения
        PROPERTY_DECLARATION_STRING(Main);
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller