// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� �������

#pragma once

#include "iexportable.h" // IExportable
#include "logseverity.h" // ����������� �������

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� �������
      /// </summary>
      interface ILogSource : public IExportable
      {
      public:
        /// <summary>
        /// ������������ ������� � ����
        /// </summary>
        /// <param name="severity">�����������</param>
        /// <param name="message">���������</param>
        /// <param name="">���������</param>
        virtual void RegisterEvent(LogSeverity severity, const char * message, ...) = 0;        
        /// <summary>
        /// ������������ ������� � ����
        /// </summary>
        /// <param name="severity">�����������</param>
        /// <param name="message">���������</param>
        /// <param name="">���������</param>
        virtual void RegisterEvent(LogSeverity severity, const char * message) = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller