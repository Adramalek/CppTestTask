#pragma once

#include "iregistrykey.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      interface IStateMachineHandler : public IExportable
      {
      public:
        // ����� �����������
        PROPERTY_DECLARATION(unsigned __int8, HandlerClass);
        /// <summary>
        /// ��������� ������� ����������� ������ Receive
        /// </summary>
        virtual unsigned __int8 CountReceiveStages() const = 0;
        /// <summary>
        /// ���������� ���������� �����������
        /// </summary>
				virtual IRegistryKey * GetDescriptor() = 0;

				/// <summary>
				/// ��������� �� ��������� ���������
				/// </summary>
				//virtual bool IsActivator() const = 0;

        /// <summary>
        /// ������������ ��������� � ������ �����������
        /// </summary>
        virtual IRegistryKey * GetSubKey(const char * key) = 0;

      };

    }
  }
}