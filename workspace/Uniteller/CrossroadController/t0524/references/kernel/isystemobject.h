// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ��������� ������� �������

#pragma once

#include "istatemachinecontext.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ������� ��������� ������� �������
      /// </summary>
      interface ISystemObject : public IStateMachineContext
      {
      public:
        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IObject
        typedef int IsSystemObject;
      };



      interface IPlatformInterceptor : public ISystemObject
      {
      public:
        virtual IExportable * GetApiEndpoint() = 0;
        virtual const char * GetApiId() = 0;
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller