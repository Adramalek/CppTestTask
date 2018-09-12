// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� �����������  ������� �������

#pragma once

#include "iobject.h" // IObject
#include "apiendpointerror.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      class IExtension;

      /// <summary>
      /// ��������� �����������  ������� �������
      /// </summary>
      interface IFactory : public IExportable
      {
      public:
        /// <summary>
        /// ���� � ����� ��������� �������
        /// </summary>
        PROPERTY_DECLARATION_STRING(SystemRoot);
        /// <summary>
        /// ������� � ���������� ��������� ������� ������� ���� kind
        /// </summary>
        /// <param name="kind">��� ������� ��� ��������</param>
        /// <param name="generation">��������� ���������</param>
        /// <returns>��������� �� ������ (���� �� ������� ������) ��� NULL </returns>
        virtual IObject * CreateInstance(const char * kind, int generation)=0;

        /// <summary>
        /// ���������� ������������ ���������� �� �� ������� ������
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="generation">��������� ���������</param>
        virtual bool ColdLoad(const char * kind, int generation)=0;        

        virtual ApiEndpointError ConnectToApiEndpoint(const char * EndPoint, IExportable * interceptor, const char * unit) = 0;
        virtual ApiEndpointError ConnectToApiEndpoint(const char * EndPoint, IExportable * interceptor, IExportable * unit) = 0;

        /// <summary>
        /// ��������� ��������� ����� ���������� UTC
        /// </summary>
        virtual void LoadApplicationPackage(const char * szName) = 0;

        /// <summary>
        /// ��������� ���������������� ���������� �������, ����������� ��������� �������� ���� kind
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="extension">����������-������������� ������� ���� kind</param>
        virtual void AddExtension(const char * kind, IExtension * extension) = 0;
        /// <summary>
        /// ������� �������� �������
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// ���������� ����������� � ������� ��� ������ ��� ����������� ��� ��������
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="generation">��������� ���������</param>
        virtual bool ActivateLoadedUnit(const char * kind, int generation)=0;        
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller