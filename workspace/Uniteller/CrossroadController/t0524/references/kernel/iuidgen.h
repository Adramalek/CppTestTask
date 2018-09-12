// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ��������� ���������� ���������� ���������������

#pragma once

#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ������� ��������� ���������� ���������� ���������������
      /// </summary>
      interface IUnicalIdGenerator : public IExportable
      {
      public:
        /// <summary>
        /// ���������� ���������� �������������
        /// </summary>
        /// <returns> ���������� ������������� </returns>
        virtual address GetUnicalId() = 0;
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller