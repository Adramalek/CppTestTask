// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ��������� ��������

#pragma once

#include "istate.h"
#include "istatemachinecontext.h"
#include "iregistrykey.h"
#include "irequestdispatcher.h"
#include "istatemachinehandler.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ��������� ��������
      /// </summary>
      interface IStateMachine : public IStartable<IStateMachineContext>
      {
      public:
        /// <summary>
        /// ��������� ���������
        /// </summary>
        /// <param name="state">���������</param>
        virtual void AddState(IState * state) = 0;
        /// <summary>
        /// ��������� �������
        /// </summary>
        /// <param name="sFrom">��������� �� �������� �������������� �������</param>
        /// <param name="sTo">��������� � ������� �������������� �������</param>
        /// <param name="evt">�������, �� �������� �������������� �������</param>        
        /// <param name="constraints">���������, ������� ����� �������������� �� ��������</param>
        /// <param name="handler">������������� ������� �������� ���������� �������� (���� ����, �� null)</param>
        /// <param name="handlerLevel">������� �������������� �����������</param>
        virtual void AddTransition(IState * sFrom, IState * sTo, event_t evt, IMessageFilter * constraints, IStateMachineHandler * handler,
          unsigned __int8 handlerLevel) = 0;              
        /// <summary>
        /// ��������� ���������� ��������� �������� ������� �� ���� �������� ������� (���������)
        /// </summary>
        /// <param name="message">���������, ��������� �� ���� �������� ���������.</param>
        virtual void HandleEvent(IMessage * message, IRequestDispatcher * dispatcher) = 0;
        /// <summary>
        /// ��������� �������� ��������� ��������� �������� �� �����
        /// </summary>
        /// <param name="name">��� ���������.</param>
        /// <returns>��������� ������ (���� ��� �������) ��� NULL ���� ��������� � ����� ������ �� ����������</returns>
        virtual IState * GetState(const char * name) = 0;       

        /// <summary>
        /// ��������� ���������� �������� ���������� ���������
        /// </summary>
        virtual void SetContextVariable(const char * name, IVariant * value) = 0;
        /// <summary>
        /// ��������� �������� �������� ���������� ���������
        /// </summary>
        virtual IVariant * GetContextVariable(const char * name) = 0;
      };           

      // ������������ ��� �������� ����� �������
      #define MAKE_EVENT_CODE(x,y,z) ((unsigned __int64)x<<48) | ((unsigned __int64)y<<32) | ((unsigned __int64)z)

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller