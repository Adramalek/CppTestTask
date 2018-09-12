// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������� �������

#pragma once

#include "exportable.h"
#include "ivariant.h"
#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ���������� �������
      /// </summary>
      interface IOptionsContainer : public IExportable
      {
      public: // ������

        /// <summary>
        /// ��������� ��������� ����������� �� ��������� � ��������� name �����
        /// </summary>
        /// <param name="name">��� �����.</param>
        /// <returns>true, ���� ����� ����������� (�������� � ��������� ������), false - �����</returns>
        virtual bool IsSet(const char * name) const = 0;

        /// <summary>
        /// ���������� �������� �����
        /// </summary>
        /// <param name="name">��� ����� ��� ��������� �� ��������.</param>
        /// <returns>�������� ���������, ��������������� ����� name. ���� ��������� �� ������� ��� �� ������� ����� �������� NULL.</returns>
        virtual IVariant * GetOption(const char * name) const = 0;
        
        /// <summary>
        /// ���������� ����� �����
        /// </summary>
        /// <returns>������������ ���� �����</returns>
        virtual IEnumeration<const char *> * GetOptionNames() const = 0;

        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IOptionsContainer
        typedef int IsOptionsContainer;
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller