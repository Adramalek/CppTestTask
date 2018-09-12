#pragma once

#include "kernel/iregistryhive.h"

namespace Uniteller 
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// Интерфейс ключа реестра
      /// </summary>
      class RegistryHive : public Exportable<IRegistryHive>
      {
      public: // Свойства
        // корневой ключ
        SMART_POINTER_PROPERTY(IRegistryKey, Data);
        // путь в родительском дереве
        PROPERTY_IMPLEMENTATION_STRING(Root);
        // результат разбора куста реестра
        PROPERTY_IMPLEMENTATION(UniTextParserErrors, ParseResult);
        // сообщения парсера UniText
        PROPERTY_IMPLEMENTATION_STRING(ParserMessage);
      };      

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller