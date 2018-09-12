// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ������ ��������� (SmartPointer)

#pragma once

#include "smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// ����� ��������� ��� ��������������� ������������ ���������. ������� ������������ �����,
      /// ����� ��������� �� �������������� ������ ������������ ����� �������� ���������� � ������ �������
      /// </summary>
      template <class T>
      class AutoRelease
      {
      private:
        T * p;
      public:
        AutoRelease()
        {
        }
        /// <summary>
        /// Initializes a new instance of the <see cref="AutoRelease{T}"/> class.
        /// </summary>
        /// <param name="pointer">The pointer.</param>
        AutoRelease(T * pointer) : p(pointer)
        {
        }
        /// <summary>
        /// ����������
        /// </summary>
        ~AutoRelease()
        {
          if (p)
            p->Release();
        }
        /// <summary>
        /// �������� T*.
        /// </summary>
        /// <returns>
        /// ���������� ��������� 
        /// </returns>
        operator T*() const throw()
        {
          return p;
        }
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller