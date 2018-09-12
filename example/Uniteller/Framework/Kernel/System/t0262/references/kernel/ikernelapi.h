// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���� Variant

#pragma once

#include "ivendordatasource.h"
#include "istatemachine.h"
#include "iregistry.h"
#include "ifactory.h"
#include "iapplicationhost.h"
#include "iuidgen.h"
#include "iprotocolreflection.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// �������������� ��������� ���������� �����-���� Uniteller.Framework.Kernel
      /// </summary>
      interface IKernelApi : public IExportable
      {
      public:
        /// <summary>
        /// ��������� �������� ��������� ����-������ ������������� ������
        /// </summary>
        /// <returns>��������� �� ����� ��������� ���������� ����-������ ������������� ������</returns>
        virtual IVendorDataSource * CreateVendorDataSource() = 0;
        /// <summary>
        /// ��������� ��������� �������� ������� �� ����-��������
        /// </summary>
        /// <param name="name">��� ��������� �������� ��� ��������.</param>
        /// <returns>��������� �� �������� �������</returns>
        virtual IStateMachine * LoadStateMachine(const char * name) = 0;
        /// <summary>
        /// ��������� �������� ������ ����-������
        /// </summary>
        /// <returns>��������� �� ������ ����-������</returns>
        virtual IRegistry * GetRegistry() = 0;   
        /// <summary>
        /// ���������� ����������� ��� �����-���� ���������� ������� �������
        /// </summary>
        /// <returns>��������� �� ������� �������</returns>
        virtual IFactory * GetStandardFactory() = 0;
        /// <summary>
        /// ������� ����������� ���� ����������
        /// </summary>
        /// <param name="argc">����� ���������� ��������� ������.</param>
        /// <param name="argv">��������� ��������� ������.</param>
        /// <returns></returns>
        virtual IApplicationHost * StartApplication(IFactory * factory, IUnicalIdGenerator * generator, int argc, char *argv[]) = 0;

        /// <summary>
        /// ��������� ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szText">����� ��� �������</param>
        /// <returns>������ �������</returns>
        virtual IEnumeration<IRegistryHive *> * ParseUniText(const char * szText) = 0;

        /// <summary>
        /// ������������� ����
        /// </summary>
        virtual void Stop() = 0;

        /// <summary>
        /// ���������� ��������� �� ��������� �����-����
        /// </summary>
        virtual IProtocolReflection * GetReflector() = 0;

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ���������� � ������ �����-���� �������� ����-������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        virtual void LoadUniTextDataSource(const char * szFilePath) = 0;

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ��������� ������ ������ � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        /// <returns>������ �������</returns>
        virtual IEnumeration<IRegistryHive *> * LoadUniTextFile(const char * szFile) = 0;

        /// <summary>
        /// ��������� ��������� �� �������� ����� (����������������� utc) � ��������� � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        /// <returns>������ �������</returns>
        virtual IEnumeration<IRegistryHive *> * LoadUtcFile(const char * szFile) = 0;

        /// <summary>
        /// ��������� �������� �� ������� ���� (����������������� utc) � ��������� � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        virtual void WriteUtcFile(const char * szFile, IEnumeration<IRegistryHive *> * hives) = 0;

        /// <summary>
        /// ��������� ��������� �� �������� ����� � ���������� � ������ �����-���� �������� ����-������ � ������� compressed UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        virtual void LoadUtcDataSource(const char * szFilePath) = 0;

        /// <summary>
        /// ��������� ��������� �� ������� ���� (����������������� utc) � ��������� � ������� UniText
        /// </summary>
        /// <param name="szFile">���� ��� �������� � �������</param>
        virtual void WriteUniTextFile(const char * szFile, IEnumeration<IRegistryHive *> * hives) = 0;

        /// <summary>
        /// ��������� ��������� ����� UTC
        /// </summary>   
        virtual void LoadPackage(const char * szPackName) = 0;

      };
    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller