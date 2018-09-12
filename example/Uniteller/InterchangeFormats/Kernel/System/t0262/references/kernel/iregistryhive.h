// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ����� �������

#pragma once

#include "iregistrykey.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ���� ������ ������� UniText-�
      /// <summary>
      enum class UniTextParserErrors
      {
        Success = 0, // ��� ������
        DuplicateKey = 1, // ������������ �����
        HierarchyError = 2, // ������ ��������
        ValueError = 3 // �� ������� ��������� �������� �����. ������ �������.
      };

      /// <summary>
      /// ��������� ����� �������
      /// </summary>
      interface IRegistryHive : public IExportable
      {
      public: 
        POINTER_PROPERTY_DECLARATION(IRegistryKey, Data); // �������� ����
        PROPERTY_DECLARATION_STRING(Root); // ���� � ������������ ������
        PROPERTY_DECLARATION(UniTextParserErrors, ParseResult ); // ��������� ������� ����� �������
        PROPERTY_DECLARATION_STRING(ParserMessage); // ��������� ������� UniText
      };

      typedef SmartPointer<IRegistryHive> RegistryHivePtr;


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller