// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���� �������� ���������

#pragma once

#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ���� �������� ���������
      /// </summary>
      interface IMessageBus : public IExportable
      {
      public:
        /// <summary>
        /// ��������� ��������� ��������� message ��������� target
        /// </summary>        
        /// <param name="target">����� ��������� ���������.</param>
        /// <param name="message">��������� ��� ��������.</param>
        /// <returns>������� �� ��������� ���������</retuns>
        virtual bool SendMessage(address target, IMessage * message) = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller