// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ����� �������

#pragma once

#include "iregistrydatasource.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ��������� ������ ������������� ������
      /// </summary>
      interface IVendorDataSource : public IRegistryDataSource
      {
      public:       
        /// <summary>
        /// ���������� �������� � ���������� ������� � ������� UNITEXT � ��������� ������
        /// </summary>
        /// <param name="module">������ �� �������� ����� �������� ������ � ������� UNITEXT.</param>
        /// <param name="resid">������������� ������� ��� ��������.</param>
        virtual void Connect(void * module, int resid) = 0;        
        /// <summary>
        /// ���������� �������� � ���������� �������� ������ � ������� UTC
        /// </summary>
        /// <param name="data">������ ���������.</param>
        /// <param name="len">����� ������.</param>
        virtual void ConnectData(unsigned char data[], int len) = 0;
        /// <summary>
        /// ���������� �������� � ���������� ��������� ������� (���������� ���������� ��� �����) � ������� UTC
        /// </summary>
        /// <param name="data">������ ���������.</param>
        /// <param name="len">����� ������.</param>
        virtual void ConnectUtc(void * module, int resid) = 0;
      };

      typedef SmartPointer<IVendorDataSource> VendorDataSourcePtr;


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller

