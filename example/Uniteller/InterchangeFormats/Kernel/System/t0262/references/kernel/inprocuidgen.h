// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ��������� ���������� ���������� ���������������

#pragma once

#include "iuidgen.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ������� ��������� ���������� ���������� ���������������
      /// </summary>
      class InprocUnicalIdGenerator : public Exportable<IUnicalIdGenerator>
      {
      private:
				// ��������� ��������������� �������
        int m_nLastGeneratedValue;
        std::string m_Value;
      public:
        InprocUnicalIdGenerator() : m_nLastGeneratedValue(0)
        {
        }
        /// <summary>
        /// ���������� ���������� �������������
        /// </summary>
        /// <returns> ���������� ������������� </returns>
        address GetUnicalId() 
        {
          ++m_nLastGeneratedValue;
          m_Value = std::to_string(m_nLastGeneratedValue);
          return m_Value.c_str();
        }
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller