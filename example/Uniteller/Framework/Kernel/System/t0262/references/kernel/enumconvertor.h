// Uniteller.Framework
// Version: 1.0.0
// Generation: 1

// Файд содержит шаблон функции конвертирующей значения "enum"-типов в сопоставляемые им константы.

#pragma once

#include <string>

#define LITERAL_IN_QUOTES(lit) #lit

namespace Uniteller
{
  namespace Framework
  { 

        /// <summary>
        /// Статический тип отождествляемый с перечисляемым типом, он содержит в себе массив сопоставляемых констант и функцию конвертации.
        /// </summary>
        /// <param name="typeTo">Тип возвращаемой константы</param>
        /// <param name="typeFrom"> Перечисляемый тип </param>
        /// <param name="min">Enum константа определяющая минимальное значение</param>
        /// <param name="max">Enum константа определяющая максимальное значение</param>
        /// <returns>
        /// Будет создан новый тип и функция конвертации ThisType::From().
        /// Для работы с ней необходимо определить массив констант ThisType::Constants[].
        /// </returns>
        template <typename typeTo, typename typeFrom, typeFrom min, typeFrom max>
        struct Converter{
            static const typeTo Constants[1+(int)max-(int)min];
            
            static typeTo From (typeFrom value)
            {
                if ((value < min) || (value > max))
                    throw std::exception("Overflow value " LITERAL_IN_QUOTES(typeFrom) "!" ); // Kernel::CommonErrors::InvalidArgument;

                return Constants[(int)value-(int)min];
            }
        };

  } // пространство имен Framework 
} // пространство имен Uniteller