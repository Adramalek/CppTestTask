// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ����� �������

#pragma once

#include "iregistryhive.h"
#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ��������� ������ ������� ����-������
      /// </summary>
      interface IRegistryDataSource : public IExportable
      {
      public: 
      //  PROPERTY_DECLARATION_STRING(ConnectionString, ������ �����������);
        /// <summary>
        /// ��������� ����� ����� ������� ����-������ �� ��������� ������
        /// </summary>
        /// <returns>��������� ����������� ����� �������</returns>
        virtual IEnumeration<IRegistryHive *> * Load() = 0;
        /// <summary>
        /// ����������� ����� ����� ������� ����-������
        /// </summary>
        /// <param name="roots">��������� ����� �������.</param>
        virtual void Save(IEnumeration<IRegistryHive *> * roots) = 0;
      };

      typedef SmartPointer<IRegistryDataSource> RegistryDataSourcePtr;


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller