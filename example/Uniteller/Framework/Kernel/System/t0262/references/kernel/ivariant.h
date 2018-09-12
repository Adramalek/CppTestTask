// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию типа Variant

#pragma once

#include "smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Типы представляемых значений
      /// </summary>
      enum class VariantType : unsigned __int8
      {
        // Значения нет
        EmptyValue   = 0,
        // Целое число (__int32)
        IntegerValue = 1,
        // Логическое значение
        BooleanValue = 2,
        // Строка
        StringValue  = 3,
        // Массив
        ArrayValue = 4,
        // IExportable
        ExportableValue = 5,
        // Время
        TimePoint = 6,
        // Целое число (__int64)
        Int64Value = 7,
        // Беззнаковое целое число (__int32)
        UnsignedIntegerValue = 8,
        // Массив байт
        ByteArrayValue = 9,
        // Лямбда-выражение
        LambdaExpression = 10,
        // Контейнер свойств
        //PropertyMapValue = 11
      };

			/// <summary>
			/// Тип лямбда-выражения
			/// </summary>
			enum class ExpressionType
			{
				Variable, // Переменная (глобальная)
				LocalVariable, // Локальная переменная
				Enumeration, // Значение перечислимого типа
				//Constant, // Константа
				Concat, // Вызов concat:
				Append, // Вызов append:
				Str,    // Вызов str:
				MakeDate, // Вызов MakeDate:
				MakeTime,
				MakeDateTime,
				DayOf,
				MonthOf,
				YearOf,
				Inc,
				Dec,
				//HourOf,
				//SecondOf,
				//MinuteOf,
				Get,
				SizeOf,
				Copy,
				Substr,
				MakeByteVector,
				GetBytes,
				OneOf,
				Range,
				Regexp,
				ToString,
				CheckBit,
				StartsWith,
				Mod,
				ToHex				
			};


      /// <summary>
      /// Интерфейс контейнера, позволяющего хранить строки, числа или логические значения
      /// </summary>
      interface IVariant : public IExportable
      {
      public:
        /// <summary>
        /// Возвращает тип хранимого значения
        /// </summary>
        /// <returns> Тип хранимого значения </returns>
        virtual VariantType GetType() const = 0;
      };
      

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller

namespace std
{

  inline std::string to_string(Uniteller::Framework::Kernel::VariantType vt)
  {
    switch (vt)
    {    
      case Uniteller::Framework::Kernel::VariantType::EmptyValue: 
        return "Empty (0)";
      // Целое число (__int32)
      case Uniteller::Framework::Kernel::VariantType::IntegerValue:
        return "Int32 (1)";
        // Логическое значение
      case Uniteller::Framework::Kernel::VariantType::BooleanValue:
        return "Boolean (2)";
        // Строка
      case Uniteller::Framework::Kernel::VariantType::StringValue:
        return "String (3)";
        // Массив
      case Uniteller::Framework::Kernel::VariantType::ArrayValue:
        return "Array (4)";
        // IExportable
      case Uniteller::Framework::Kernel::VariantType::ExportableValue:
        return "Exportable (5)";
        // Время
      case Uniteller::Framework::Kernel::VariantType::TimePoint:
        return "TimePoint (6)";
        // Целое число (__int64)
      case Uniteller::Framework::Kernel::VariantType::Int64Value:
        return "Int64 (7)";
        // Беззнаковое целое число (__int32)
      case Uniteller::Framework::Kernel::VariantType::UnsignedIntegerValue:
        return "UInt32 (8)";
        // Массив байт
      case Uniteller::Framework::Kernel::VariantType::ByteArrayValue:
        return "ByteVector (9)";
        // Лямбда-выражение
      case Uniteller::Framework::Kernel::VariantType::LambdaExpression:
        return "Lambda (10)";
      default:
        return "Unknown Type (incompatible kernel?)";
    }
  }

} // std
