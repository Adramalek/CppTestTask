// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������� �������� � ���� �������� ���������

#pragma once

#include "imessagebus.h"
#include "imessagefilter.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ���������� �������� � ����
      /// </summary>
      interface IRequestDispatcher : public IMessageBus
      {      
      public:
        // ������������� ������
        PROPERTY_DECLARATION(bool, IsPostponeFilter);
        /// <summary>
        /// ��������� ���������� ������ ����������� ���������
        /// ���� ������� NULL, �� ������� ��������� �� ����������
        /// </summary>
        virtual void SetFilter(IMessageFilter * filter) = 0;
        /// <summary>
        /// ���������� ���������� ������� ������ �� ����
        /// </summary>
        virtual void Disconnect() = 0;        

        virtual const char * GetAddress() const = 0;

				/// <summary>
				/// ��������� ��������������� � ��������� ��������� message ��������� target
				/// </summary>        
				/// <param name="target">����� ��������� ���������.</param>
				/// <param name="message">��������� ��� ��������.</param>
				/// <returns>������� �� ��������� ���������</retuns>
				virtual bool SendEvent(address target, event_t message, int generation = 1, int priority = 0) = 0;
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller