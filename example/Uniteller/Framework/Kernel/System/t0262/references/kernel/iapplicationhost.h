// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ����� ���������� �����-����

#pragma once

#include "iapplicationstartupinfo.h"
#include "istartable.h"
#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ����� ����������
      /// </summary>      
      interface IApplicationHost : public IStartable<IApplicationStartupInfo>
      {
      public: // ������        
        /// <summary>
        /// ���������� ���� �������� ������ ��������� ����������, ������������ � �����
        /// <summary>
        virtual void WaitForExist() = 0;
        /// <summary>
        /// ��������� ��������� �� �������� ���� (����-��������) ��������� �������� ������-������ �����
        /// <summary>
        virtual bool TransmitMessage(IMessage * message) = 0;

        /// <summary>
        /// ���������� ������������ ���������� �� �� ������� ������
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="generation">��������� ���������</param>
        /// <returns>��������� ��������</returns>
        virtual bool ColdLoad(const char * kind, int generation) = 0;

        /// <summary>
        /// ������������� ����������
        /// </summary>
        virtual void Terminate() = 0;
        /// <summary>
        /// ���������� ���� �������� ������ ��������� ����������, ������������ � �����
        /// <summary>
        /// <param name="timeout">����-��� � �������������</param>
        /// <returns>������� �� ����</returns>
        virtual bool WaitForExist(size_t timeout) = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller