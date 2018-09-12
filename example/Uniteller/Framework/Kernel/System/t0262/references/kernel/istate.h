// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������� ��������� ��������

#pragma once

#include "istartable.h"
#include "istatemachinecontext.h"
#include "imessagefilter.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
            
      /// <summary>
      /// ��������� ��������� ��������� ��������
      /// </summary>
      interface IState : public IStartable<IStateMachineContext>
      {
      public: // ��������
        // ��� ���������
        READONLY_PROPERTY_DECLARATION(char *, Name);
        // �������
        PROPERTY_DECLARATION(int, TimeOut);
        // ��������� �� ������ ���������
        PROPERTY_DECLARATION(bool, IsStartState);
        // �������� �� ������ ���������
        PROPERTY_DECLARATION(bool, IsStopState);
        // ���������� ��� ���������
        PROPERTY_DECLARATION(__int16, StateId);
        // ������������� �� ��������������� �������
        PROPERTY_DECLARATION(bool, IsPostponeFilter);
      public:
        /// <summary>
        /// ��������� �������
        /// </summary>
        /// <param name="evt">��� �������</param>
        /// <param name="next">��������� ���������</param>
        /// <param name="constraints">���������, ������� ����� �������������� �� ��������</param>
        virtual void AddTransition(event_t evt, IState * next, IMessageFilter * constraints) = 0;
        /// <summary>
        /// ��������� ���������� ������� � ������ ���������
        /// </summary>
        /// <param name="evt">��� �������</param>
        /// <returns>��������� ��������� ��� NULL, ���� ������� �� ��������������</returns>
        virtual IState * HandleEvent(event_t evt) = 0;     
        /// <summary>
        /// ��������� �������� ����������� �������
        /// </summary>
        /// <returns>������ ���������, ������� ����� ���� ���������� � ������ ���������</returns>
        virtual IMessageFilter * GetAllowedEvents() = 0;

        /// <summary>
        /// ��������� �������� ����������� ��������� ������� � ������ ��������, ��������������� �������� evt
        /// </summary>
        /// <returns>������ ���������, ������� ����� ���� ����������</returns>
        virtual IMessageFilter * GetAllowedEvents(event_t evt) = 0;

        /// <summary>
        /// ������� ������ ���������
        /// </summary>
        virtual void ClearTransitions() = 0;          
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller