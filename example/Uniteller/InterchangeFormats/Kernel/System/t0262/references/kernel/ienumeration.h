// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������-������������

#pragma once

#include "exportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ������������
      /// </summary>
      template <class T>
      interface IEnumeration : public IExportable
      {
      public: // ��������
        // ����� ��������� � ������������
        READONLY_PROPERTY_DECLARATION(size_t, Count);
      public: // ������
        /// <summary>
        /// ��������� �������� ������� �� ������������ �� �������
        /// </summary>
        /// <param name="index">������ �������� ������������</param>
        /// <returns>������� ������������ � �������� index</returns>
        virtual T GetItem(int index) = 0;				
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller