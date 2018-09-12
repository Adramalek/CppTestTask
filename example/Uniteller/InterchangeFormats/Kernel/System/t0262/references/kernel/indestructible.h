// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���������� ��������������� �� dll �������
#pragma once

#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// ������� ���������� ������������� (�������������) �������
      /// <summary>
      template <class T>
      class Indestructible : public T
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsExportable OnlyExportable;
      public:
        /// <summary>
        /// �����������, ������������� ������� ������ � �������
        /// </summary>
				Indestructible()
        {
        }

        /// <summary>
        /// ����������� ������� ������ �� ���������������� ������ �� �������
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				long AddRef()
        {
					return 1;
        }
        /// <summary>
        /// ��������� ������� ������ �� ���������������� ������ �� ������� 
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				long Release()
        {					   
          return 1;
        }
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller