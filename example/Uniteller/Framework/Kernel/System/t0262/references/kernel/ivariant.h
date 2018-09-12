// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���� Variant

#pragma once

#include "smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ���� �������������� ��������
      /// </summary>
      enum class VariantType : unsigned __int8
      {
        // �������� ���
        EmptyValue   = 0,
        // ����� ����� (__int32)
        IntegerValue = 1,
        // ���������� ��������
        BooleanValue = 2,
        // ������
        StringValue  = 3,
        // ������
        ArrayValue = 4,
        // IExportable
        ExportableValue = 5,
        // �����
        TimePoint = 6,
        // ����� ����� (__int64)
        Int64Value = 7,
        // ����������� ����� ����� (__int32)
        UnsignedIntegerValue = 8,
        // ������ ����
        ByteArrayValue = 9,
        // ������-���������
        LambdaExpression = 10,
        // ��������� �������
        //PropertyMapValue = 11
      };

			/// <summary>
			/// ��� ������-���������
			/// </summary>
			enum class ExpressionType
			{
				Variable, // ���������� (����������)
				LocalVariable, // ��������� ����������
				Enumeration, // �������� ������������� ����
				//Constant, // ���������
				Concat, // ����� concat:
				Append, // ����� append:
				Str,    // ����� str:
				MakeDate, // ����� MakeDate:
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
      /// ��������� ����������, ������������ ������� ������, ����� ��� ���������� ��������
      /// </summary>
      interface IVariant : public IExportable
      {
      public:
        /// <summary>
        /// ���������� ��� ��������� ��������
        /// </summary>
        /// <returns> ��� ��������� �������� </returns>
        virtual VariantType GetType() const = 0;
      };
      

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller

namespace std
{

  inline std::string to_string(Uniteller::Framework::Kernel::VariantType vt)
  {
    switch (vt)
    {    
      case Uniteller::Framework::Kernel::VariantType::EmptyValue: 
        return "Empty (0)";
      // ����� ����� (__int32)
      case Uniteller::Framework::Kernel::VariantType::IntegerValue:
        return "Int32 (1)";
        // ���������� ��������
      case Uniteller::Framework::Kernel::VariantType::BooleanValue:
        return "Boolean (2)";
        // ������
      case Uniteller::Framework::Kernel::VariantType::StringValue:
        return "String (3)";
        // ������
      case Uniteller::Framework::Kernel::VariantType::ArrayValue:
        return "Array (4)";
        // IExportable
      case Uniteller::Framework::Kernel::VariantType::ExportableValue:
        return "Exportable (5)";
        // �����
      case Uniteller::Framework::Kernel::VariantType::TimePoint:
        return "TimePoint (6)";
        // ����� ����� (__int64)
      case Uniteller::Framework::Kernel::VariantType::Int64Value:
        return "Int64 (7)";
        // ����������� ����� ����� (__int32)
      case Uniteller::Framework::Kernel::VariantType::UnsignedIntegerValue:
        return "UInt32 (8)";
        // ������ ����
      case Uniteller::Framework::Kernel::VariantType::ByteArrayValue:
        return "ByteVector (9)";
        // ������-���������
      case Uniteller::Framework::Kernel::VariantType::LambdaExpression:
        return "Lambda (10)";
      default:
        return "Unknown Type (incompatible kernel?)";
    }
  }

} // std
