// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс ключа реестра

#pragma once

#include "iregistrykey.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Коды ошибок парсера UniText-а
      /// <summary>
      enum class UniTextParserErrors
      {
        Success = 0, // Нет ошибок
        DuplicateKey = 1, // Дублирование ключа
        HierarchyError = 2, // Ошибка иерархии
        ValueError = 3 // Не удалось загрузить значение ключа. Ошибка формата.
      };

      /// <summary>
      /// Интерфейс ключа реестра
      /// </summary>
      interface IRegistryHive : public IExportable
      {
      public: 
        POINTER_PROPERTY_DECLARATION(IRegistryKey, Data); // корневой ключ
        PROPERTY_DECLARATION_STRING(Root); // путь в родительском дереве
        PROPERTY_DECLARATION(UniTextParserErrors, ParseResult ); // результат разбора куста реестра
        PROPERTY_DECLARATION_STRING(ParserMessage); // сообщения парсера UniText
      };

      typedef SmartPointer<IRegistryHive> RegistryHivePtr;


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller