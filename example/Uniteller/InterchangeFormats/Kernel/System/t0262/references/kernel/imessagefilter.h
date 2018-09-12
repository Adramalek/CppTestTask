// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include "iset.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ������� ���������
      /// </summary>
      interface IMessageFilter : public ISet<int>
      {
      public: // ��������
        // �������� �� ������ ������������
        PROPERTY_DECLARATION(bool, IsExclusive);
        /// <summary>
        /// ��������� ��������� ��� ���������, �� ������� � ��������
        /// </summary>
        /// <param name="message">��������� ��� �������� �� ������� ��������</param>
        /// <returns>true - ���� ��������� ��������� ��������, false - ����� </returns>
        virtual bool Check(int message) = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller