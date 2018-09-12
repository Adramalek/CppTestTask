#pragma once

#include "kernel/iregistryhive.h"

namespace Uniteller 
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// ��������� ����� �������
      /// </summary>
      class RegistryHive : public Exportable<IRegistryHive>
      {
      public: // ��������
        // �������� ����
        SMART_POINTER_PROPERTY(IRegistryKey, Data);
        // ���� � ������������ ������
        PROPERTY_IMPLEMENTATION_STRING(Root);
        // ��������� ������� ����� �������
        PROPERTY_IMPLEMENTATION(UniTextParserErrors, ParseResult);
        // ��������� ������� UniText
        PROPERTY_IMPLEMENTATION_STRING(ParserMessage);
      };      

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller