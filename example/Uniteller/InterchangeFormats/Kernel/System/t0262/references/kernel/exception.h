// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ���������� �������� ������ ���������� ���� 

#pragma once

#include <exception> // std::exception
#include "utils.h" // FormatString

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
    
      /// <summary>
      /// ������� ���������� ���������� ������ ����
      /// </summary>
      class KernelException : public std::runtime_error
      {
      public:
        explicit KernelException(const std::string & message) : std::runtime_error(message.c_str())
        {
        }
        KernelException(const char * fmt, ...) :
          std::runtime_error(Utils::FormatString(fmt, (va_start(m_args, fmt), m_args)).c_str())
        {
          va_end(m_args);          
        }      

      private:
        va_list m_args;

        // ����� �������� ������� ��� ���������� ���������� ���� � C++11
        //template <typename... Ts>
        //KernelException(const char *fmt, Ts ... ts) : std::exception(Utils::FormatString(fmt, ts...).c_str())
        //{
        //}      
        
      };

			class BadCastException : public KernelException
			{
			public:
				explicit BadCastException(const std::string & message) : KernelException(message)
				{
				}
				BadCastException() : KernelException("��������� �� ����������")
				{
				}
			};

			class OutOfRangeException : public KernelException
			{
			public:
				explicit OutOfRangeException(const std::string & message) : KernelException(message)
				{
				}
			};


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller