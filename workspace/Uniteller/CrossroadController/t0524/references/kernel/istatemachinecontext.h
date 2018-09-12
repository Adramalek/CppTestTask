// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������� ��������� ��������

#pragma once

#include "imessage.h"
#include "imessagefilter.h"
#include "iobject.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ��������� ��������� ��������
      /// </summary>
      interface IStateMachineContext : public ICoreObject
      {
      public:
        /// <summary>
        /// ���������� ����-���
        /// </summary>
        virtual void RaiseTimeOut() = 0;

        /// <summary>
        /// ��������� �������� ������ ����������� �������
        /// </summary>
        /// <param name="filter"> ������ ������� </param>
        virtual void SetFilter(bool isPostpone, IMessageFilter * filter) = 0;

        /// <summary>
        /// ��������� �������� ������ ������������ �������
        /// </summary>
        /// <param name="filter"> ������ ������� </param>
        virtual void SetOutboxFilter(IMessageFilter * filter, const char * szOldStateName, const char * szNewStateName) = 0;
        
        /// <summary>
        /// ��������� ������������� ������� ��������� ��������� ������
        /// </summary>
        /// <param name="nFrom"> ���������-�������� </param>
        /// <param name="nTo"> ���������-�������� </param>
        /// <param name="evt"> �������, �������������� ������� </param>
        virtual void OnTransition(const __int16 nFrom, const __int16 nTo, IMessage * evt) = 0;

        /// <summary>
        /// ��������� ����������� ������ ������� ������
        /// </summary>
        virtual void OnMachineStarted() = 0;
        /// <summary>
        /// ��������� ����������� ������ ��������� ������
        /// </summary>
        virtual void OnMachineStopped() = 0;
        /// <summary>
        /// ��������� �������� � ���������� � ��������� ������� � ��������
        /// </summary>
        virtual void RegisterTransition(const char * szFrom, const char * szTo, event_t evt) = 0;
        /// <summary>
        /// ��������� �������� �� ��������� ���������� ����-����
        /// </summary>
        virtual int GetTimeOutOvveride() = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller