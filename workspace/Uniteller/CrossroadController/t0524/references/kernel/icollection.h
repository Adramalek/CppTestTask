// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������-������������

#pragma once

#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ���������
      /// </summary>
      template <class T>
      interface ICollection : public IEnumeration<T>
      {
      public: // ������
        /// <summary>
        /// ��������� �������� ������������
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// ��������� �������� ������� � ������������ (� �����)
        /// </summary>
        /// <param name="value">��������, ����������� � ������������</param>
        virtual void Add(const T & value) = 0;
        /// <summary>
        /// ��������� ���������� ������ �������� � ���������, ���� ��� ��� �����������
        /// </summary>
        /// <param name="value">�������� ��� ������ � ������������</param>
        /// <param name="startIndex">�������� ����� � �������� � ��������</param>
        /// <returns>������ ���������� ��������� value ��� -1 � ������, ���� �������� ���</returns>
        virtual int IndexOf(const T & value, const int startIndex = 0) = 0;
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller