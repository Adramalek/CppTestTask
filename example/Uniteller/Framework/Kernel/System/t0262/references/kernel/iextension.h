#pragma once

#include "kernel/exportable.h"
#include "kernel/ikernelapi.h"
#include "kernel/iobject.h"
#include "ExtensionLoadResult.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// ��������� ���������� �������-���������� �����-����
      /// </summary>
      interface IExtension : public IExportable
      {
      public:

        /// <summary>
        /// ��������� ������
        /// </summary>
        virtual ExtensionLoadResult Load(const std::string & root, IKernelApi * api) = 0;

        /// <summary>
        /// ������� ��������� ������� �������
        /// </summary>
        virtual IObject * CreateInstance(IKernelApi * api) = 0;
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller