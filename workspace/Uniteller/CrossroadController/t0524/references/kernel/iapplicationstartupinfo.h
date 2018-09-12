// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������-������������

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
      /// ��������� �������, ���������������� ��������� ��� ������� ����������
      /// </summary>
      interface IApplicationStartupInfo : public IOptionsContainer
      {
      public: // ������
        // ������� ������ ����������
        PROPERTY_DECLARATION_STRING(Main);
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller