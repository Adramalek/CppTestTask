// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ��������� ������� �������

#pragma once

#include "irequestdispatcher.h"
#include "imqcontroller.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
#ifdef __GNUG__
#if __GNUC__ < 5
#define NO_CASTS
#endif
#endif

      /// <summary>
      /// ������� ��������� ������� �������
      /// </summary>
      interface IObject : public IExportable
      {
      public:
        // ��� ���� �������
        READONLY_PROPERTY_DECLARATION(char *, Type);
        // ���������� ������������� �������
        READONLY_PROPERTY_DECLARATION(char *, UnicalId);
        /// <summary>
        /// ��������� ������� ������� �������� ��������� �� ���� �������� ���������
        /// </summary>
        /// <param name="message"> ��������� </param>
        virtual bool ProcessMessage(IMessage * message) = 0;

        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IObject
        typedef int IsObject;
#ifndef NO_CASTS
      };

      /// <summary>
      /// ��������� ������� �������, ������������ �����
      /// </summary>
      interface ICoreObject : public IObject
      {
      public:
#endif
        /// <summary>
        /// ��������� ���������� � ������� ������� ��������� ��������, ����������� ������������ 
        /// ��������� �������� ���� �������� ���������
        /// </summary>
        /// <param name="moduleId"> ������������� ������, ��������� �������� �������� ���������� </param>
        /// <param name="dispatcher"> ��������� �������� </param>
        virtual void SetRequestDispatcher(address moduleId, IRequestDispatcher * dispatcher) = 0;
        /// <summary>
        /// ��������� ���������� � ������ ���������� ���������� ����. ��� ��������� ��� ����� ������ �������
        /// ���� ����, ��������� � ���������� � ���� ���� ������ ������, � ����� ��������� �������.
        /// </summary>
        /// <param name="busId">������������� ����, ���������� ������� ���������� ������</param>
        /// <param name="controller">���������� ��� ���������� �����</param>
        virtual void SetMqController(address busId, IMqController * controller) = 0;
        /// <summary>
        /// ��������� ���������� ���������� ������������� �������
        /// </summary>
        /// <param name="szUnicalId">���������� ������������� �������.</param>
        virtual void SetUnicalId(const char * szUnicalId) = 0;
        /// <summary>
        /// ��������� �������� ��������� �������� ������
        /// </summary>
        virtual IRequestDispatcher * GetRequestDispatcher() = 0;
        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ���������
        /// </summary>
        /// <param name="generation">���������.</param>
        virtual bool IsGenerationSupported(int generation) = 0;
        /// <summary>
        /// ��������� �������� ���������� � ��� �������������� �� ������ ��������
        /// </summary>
        /// <param name="szProtocol">��������.</param>
        /// <param name="generation">��������� ���������.</param>
        virtual bool IsProtocolSupported(const char * szProtocol, int generation) = 0;

        virtual IExportable * SetPlatformApiEndpoint(const char * szHive, IExportable * api) = 0;
      };

#ifdef __GNUG__
#if __GNUC__ < 5
  typedef IObject ICoreObject;
#endif
#endif


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller
