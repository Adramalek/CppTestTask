// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс контейнера свойств

#pragma once

#include "exportable.h"
#include "ivariant.h"
#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс контейнера свойств
      /// </summary>
      interface IOptionsContainer : public IExportable
      {
      public: // Методы

        /// <summary>
        /// Позволяет проверить установлена ли указанная в параметре name опция
        /// </summary>
        /// <param name="name">Имя опции.</param>
        /// <returns>true, если опция установлена (передана в командной строке), false - иначе</returns>
        virtual bool IsSet(const char * name) const = 0;

        /// <summary>
        /// Возвращает значение опции
        /// </summary>
        /// <param name="name">Имя опции для получения ее значения.</param>
        /// <returns>Значение настройки, соответствующей имени name. Если настройка не указана или не найдена будет возращен NULL.</returns>
        virtual IVariant * GetOption(const char * name) const = 0;
        
        /// <summary>
        /// Возвращает имена опций
        /// </summary>
        /// <returns>Перечисление имен опций</returns>
        virtual IEnumeration<const char *> * GetOptionNames() const = 0;

        /// Используется специализированными обертками для контроля имплементации интерфейса IOptionsContainer
        typedef int IsOptionsContainer;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller