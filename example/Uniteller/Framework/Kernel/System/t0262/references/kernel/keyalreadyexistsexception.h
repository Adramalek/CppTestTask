// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ���������� ���������� KeyAlreadyExistsException (���� �� ������)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {       
      /// <summary>
      /// ��������� � ������������� ��������� � ����� ��������������
      /// </summary>
      class KeyAlreadyExistsException : public KernelException
      {
      public:
        /// <summary>
        /// �������������� ����� ��������� ���������� <see cref="KeyAlreadyExistsException"/>.
        /// </summary>
        /// <param name="path">����, ������� ��� ����������.</param>
        explicit KeyAlreadyExistsException(const char * path) : KernelException("���� %s ��� ����������", path)
        {
        }
      };
     

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller