// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ���������� ���������� NullReferenceException (��������� �� ��������� ���������)

#pragma once

#include "exception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      using std::exception;

      //#define ExceptionMessage(x, y) std::exception((std::string(x)+y).c_str())

      /// <summary>
      /// ��������� � ��������������������� ���������
      /// </summary>
      class NullReferenceException : public KernelException
      {
      public:
        /// <summary>
        /// �������������� ����� ��������� ���������� <see cref="NullReferenceException"/>.
        /// </summary>
        /// <param name="variable">��� ����������, ������� �� ����������������.</param>
        explicit NullReferenceException(const char * variable) : KernelException((std::string)"��������� �� ��������������������� ��������� " + variable)
        {
        }
      };
     

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller