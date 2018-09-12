// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ���������� ���������� KeyNotFoundException (���� �� ������)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {       
      /// <summary>
      /// ��������� � ��������������������� ���������
      /// </summary>
      class KeyNotFoundException : public KernelException
      {
      public:
        /// <summary>
        /// �������������� ����� ��������� ���������� <see cref="KeyNotFoundException"/>.
        /// </summary>
        /// <param name="path">����, ������� �� ������.</param>
        explicit KeyNotFoundException(const char * path) : KernelException("���� %s �� ������", path)
        {
        }
      };
     

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller