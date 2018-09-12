// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include "imessagebus.h"
#include "irequestdispatcher.h"
#include "apiendpointerror.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 


      /// <summary>
      /// ��������� ����������� ���������� ����. ��������� ������� ��������� (�������) ����
      /// ������������� �������� ������� ���������� ���������� �����: ��������� ���������� �������� ������� 
      /// � ���������� �� � ����, ��������� ���������� �������
      /// </summary>
      interface IMqController : public IMessageBus
      {        
      public:
        /// <summary>
        /// ������� � ���������� � ������� ���� ��������� ������� ������� ���� kind
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="generation">��������� ���������</param>
        /// <param name="id">���� �������� �����-�� ��������, ��
        /// ����� ����������� ������� ���������� ��� ������ ���������� ������ � �������� ������. ���� ��������� ��������
        /// ��� �������� �������, �� � �������� � ����������� ���������� ������� ����� �������� � ����� �������������         
        /// ����������. ���� ������ �� ��������, �� ���� ������������� ����������� ����� ������ � ��������� ��� � �������� ���������� </param>
        /// <returns>����� ������������� ������</returns>
        virtual address CreateInstance(const char * kind, int generation, address id) = 0;
        /// <summary>
        /// ������� ����� ���� � �������� ����� �� ��� ������-������, ��������� ���������� master
        /// </summary>
        /// <param name="master">����� ������, ������� ����� �������� ������-������� ����������� ����</param>
        /// <returns>���������� ����� ��������� ����</returns>
        virtual address CreateMq(address master) = 0;
        /// <summary>
        /// ��������� ������ ���� �� �� ������ ���� ������������ ������ � ������� id
        /// </summary>
        /// <param name="id">����� ������, ������� ����� ����� ����� ������������ � ���� �������</param>
        /// <returns>���������� true ���� ������ � ����� ��������� ���������, ����� ���������� false.</returns>
        virtual bool HasAddress(address id) const = 0;

        /// <summary>
        /// ��������� ���������������� ��������� ������-������ � �������� ������-������������ ���������, ������������
        /// �� ����� id. ���� � �������� id �������� ������ ������, �� ����� ������ ����� ����� �� ���� � ����� ����������
        /// �������� ��������� � ����� ������. ���� ����� id ��� ��������� � ����, �� ����� ������������� ������.
        /// </summary>
        /// <param name="interceptor">����� ������, ������� ����� ���������� � �������� ������������</param>
        /// <param name="id">����� ������,  ��������� �������� ����� ���������������</param>
        /// <returns>����� �� �������� �������������� �������� ���������</returns>
        virtual address RegisterAsInterceptor(address interceptor, address id) =0;

        /// <summary>
        /// ��������� ���������������� ��������� ������-������ � �������� ������-������������ ���������, ������������
        /// �� ����� id. ���� � �������� id �������� ������ ������, �� ����� ������ ����� ����� �� ���� � ����� ����������
        /// �������� ��������� � ����� ������. ���� ����� id ��� ��������� � ����, �� ����� ������������� ������.
        /// </summary>
        /// <param name="interceptor">����� ������, ������� ����� ���������� � �������� ������������</param>
        /// <param name="id">����� ������,  ��������� �������� ����� ���������������</param>
        /// <param name="filter">������ ���������</param>
        /// <returns>����� �� �������� �������������� �������� ���������</returns>
        virtual address RegisterAsInterceptor(address interceptor, address id, IMessageFilter * filter) =0;

        /// <summary>
        /// ��������� ������ ���������� �� ������� ������ � ������� id (��������� �������� ���������)
        /// </summary>
        /// <param name="observer">����� ������, ������� ����� ���������� � �������� ���������� ������� ������� ������</param>
        /// <param name="id">����� ������,  ��������� �������� ����� ������������� �� ������-����������� observer</param>
        virtual bool RegisterObserver(address observer, address id) = 0;

        /// <summary>
        /// ��������� ������ ���������� �� ������� ������ � ������� id (��������� �������� ���������)
        /// </summary>
        /// <param name="observer">����� ������, ������� ����� ���������� � �������� ���������� ������� ������� ������</param>
        /// <param name="id">����� ������,  ��������� �������� ����� ������������� �� ������-����������� observer</param>
        /// <param name="filter">������ ���������</param>
        virtual bool RegisterObserver(address observer, address id, IMessageFilter * filter) = 0;

        /// <summary>
        /// ��������� ������ ���������� �� ������� ������ � ������� id (��������� ��������� ���������)
        /// </summary>
        /// <param name="observer">����� ������, ������� ����� ���������� � �������� ���������� ������� ������� ������</param>
        /// <param name="observable">����� ������, ��������� ��������� �������� ����� ������������� �� ������-����������� observer</param>
        virtual void RegisterSendTrafficObserver(address observer, address observable) = 0;

        /// <summary>
        /// ��������� ������ ���������� �� ������� ������ � ������� id (��������� ��������� ���������)
        /// </summary>
        /// <param name="observer">����� ������, ������� ����� ���������� � �������� ���������� ������� ������� ������</param>
        /// <param name="observable">����� ������, ��������� ��������� �������� ����� ������������� �� ������-����������� observer</param>
        /// <param name="filter">������ ���������</param>
        virtual void RegisterSendTrafficObserver(address observer, address observable, IMessageFilter * filter) = 0;

        virtual void MqEmulation(address master,  address bus, IMqController * emulator) = 0;

        /// <summary>
        /// ��������� ��������� ������������ �� ������ ������������ ��������� 
        /// </summary>
        virtual bool IsUnitSupportsGeneration(address unit, int generation) = 0;
        /// <summary>
        /// ��������� ��������� ������������ �� ������ ������������ ��������
        /// </summary>
        virtual bool IsUnitSupportsProtocol(address unit, const char * szProtocol, int generation) = 0;
        /// <summary>
        /// ���������� ������������ ���������� �� �� ������� ������
        /// </summary>
        /// <param name="kind">��� ������� ��� �������� � ����������� � ����</param>
        /// <param name="generation">��������� ���������</param>
        virtual bool ColdLoad(const char * kind, int generation) = 0;

        virtual void Stop() = 0;

        virtual ApiEndpointError ConnectToApiEndpoint(address unit, address module) = 0;
        virtual ApiEndpointError DisconnectFromApiEndpoint(address unit, address module) = 0;
      };



    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller