// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������� �����

#pragma once

#include "ilogsource.h" // ILogSource

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ��������� �����
      /// </summary>
      interface ILogManager : public IExportable
      {
      public:
        /// <summary>
        /// ��������� �������� ������� � �����
        /// </summary>
        /// <param name="source">��� ��������� �������.</param>
        /// <returns>�������� ������� (������)</returns>
        virtual ILogSource * OpenSource(const char * source) = 0;
      };
      
    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller