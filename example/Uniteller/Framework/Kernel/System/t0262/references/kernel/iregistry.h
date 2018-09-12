// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ������� ����-������

#pragma once

#include "iregistrydatasource.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ������� ����-������
      /// </summary>
      interface IRegistry : public IExportable
      {
      public: // ������
        /// <summary>
        /// ��������� �������� ���� ������� ����-������ �� �����
        /// </summary>
        virtual IRegistryKey * Open(const char * path, bool create = true) = 0;
        /// <summary>
        /// ��������� ���������� � ������� �������� ������
        /// </summary>
        /// <param name="source">The source.</param>
        virtual void AddSource(IRegistryDataSource * source) = 0;
        /// <summary>
        /// ��������� ���������� � ������� �������� ������ (����� ������ �������� IRegistryHive)
        /// </summary>
        /// <param name="source">The source.</param>
        virtual void AddHives(IEnumeration<IRegistryHive *> * sources) = 0;
				/// <summary>
				/// ��������� �������� ������
				/// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// ��������� ��������� xpath-������ �� �������
        /// </summary>
        /// <param name="xpath">������</param>
        virtual IRegistryKey * SelectFirst(const char * xpath) = 0;
        /// <summary>
        /// ��������� ��������� xpath-������ �� ������� � ��������� ���������� ������� �� �� �������
        /// </summary>
        /// <param name="xpath">������</param>
        virtual bool NotEmpty(const char * xpath) = 0;
      };
 
      #define MAKE_PATH(root, relative) (std::string(root)+"/"+relative).c_str()

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller