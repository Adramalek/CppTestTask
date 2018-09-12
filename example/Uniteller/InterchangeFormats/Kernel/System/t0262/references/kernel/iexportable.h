// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������������� �� dll �������

#pragma once

#include "autoproperty.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

#pragma region IExportable

      /// <summary>
      /// ��������� ��������������� �������
      /// </summary>
      interface IExportable
      {
      public:        
        /// <summary>
        /// ����������� ����������� (��� ����������� ����������� ������������ ������)
        /// </summary>
        virtual ~IExportable() 
        {
        }
        /// <summary>
        /// ����������� ������� ������ �� ���������������� ������ �� �������
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				virtual long AddRef() = 0;
        /// <summary>
        /// ��������� ������� ������ �� ���������������� ������ �� ������� 
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				virtual long Release() = 0;

        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IExportable
        typedef int IsExportable;
      };

#pragma endregion


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller