// Uniteller.CrossroadController

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace CrossroadController
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(101, 1)
        
        //���������
        #pragma region Messages and wrappers
        
        //���������
        // ������ �������� ������ ��� ������� �������
        BEGIN_MESSAGE(CountDownGreen,4,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownGreen

        // ������ �������� ������ ��� �������� �������
        BEGIN_MESSAGE(CountDownRed,2,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownRed

        // ������ �������� ������ ��� ������ �������
        BEGIN_MESSAGE(CountDownYellow,3,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownYellow

        // ��������� �������� ����� ������������ ������� ���������.
        BEGIN_MESSAGE(SetNextLight,1,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // SetNextLight

        
        BEGIN_WRAPPER()
          /// <summary> 
          /// ������ �������� ������ ��� ������� �������
          /// </summary>
          void CountDownGreen() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownGreen);
          }
          
          /// <summary> 
          /// ������ �������� ������ ��� �������� �������
          /// </summary>
          void CountDownRed() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownRed);
          }
          
          /// <summary> 
          /// ������ �������� ������ ��� ������ �������
          /// </summary>
          void CountDownYellow() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownYellow);
          }
          
          /// <summary> 
          /// ��������� �������� ����� ������������ ������� ���������.
          /// </summary>
          void SetNextLight() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::SetNextLight);
          }
          
        END_WRAPPER();
        
        BEGIN_IMPLEMENTATION()
          /// <summary> 
          /// �������� ������� CountDownGreen �� ������
          /// </summary>
          void SendCountDownGreen(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownGreen);
          }
          /// <summary> 
          /// �������� ������� CountDownGreen ������ ����
          /// </summary>
          void RaiseCountDownGreen()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownGreen);
          }
          
          /// <summary> 
          /// �������� ������� CountDownRed �� ������
          /// </summary>
          void SendCountDownRed(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownRed);
          }
          /// <summary> 
          /// �������� ������� CountDownRed ������ ����
          /// </summary>
          void RaiseCountDownRed()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownRed);
          }
          
          /// <summary> 
          /// �������� ������� CountDownYellow �� ������
          /// </summary>
          void SendCountDownYellow(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownYellow);
          }
          /// <summary> 
          /// �������� ������� CountDownYellow ������ ����
          /// </summary>
          void RaiseCountDownYellow()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownYellow);
          }
          
          /// <summary> 
          /// �������� ������� SetNextLight �� ������
          /// </summary>
          void SendSetNextLight(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::SetNextLight);
          }
          /// <summary> 
          /// �������� ������� SetNextLight ������ ����
          /// </summary>
          void RaiseSetNextLight()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::SetNextLight);
          }
          
        END_IMPLEMENTATION();
        
        #pragma endregion
      END_PROTOCOL()
      
      } // ������������ ���� Protocol
    } // ������������ ���� CrossroadController
  } // ������������ ���� Uniteller
