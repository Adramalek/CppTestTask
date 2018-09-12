// Uniteller.MainLogic

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace MainLogic
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(101, 1)
        
        //���������
        #pragma region Messages and wrappers
        
        //���������
        // �������� � ������ ���������
        BEGIN_MESSAGE(ProblemDetected,3,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // ProblemDetected

        // ��������� ����������� ������
        BEGIN_MESSAGE(Shutdown,2,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Shutdown

        // �������� ���� ������ ���������
        BEGIN_MESSAGE(Start,1,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Start

        
        BEGIN_WRAPPER()
          /// <summary> 
          /// �������� � ������ ���������
          /// </summary>
          void ProblemDetected() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ProblemDetected);
          }
          
          /// <summary> 
          /// ��������� ����������� ������
          /// </summary>
          void Shutdown() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shutdown);
          }
          
          /// <summary> 
          /// �������� ���� ������ ���������
          /// </summary>
          void Start() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
          }
          
        END_WRAPPER();
        
        BEGIN_IMPLEMENTATION()
          /// <summary> 
          /// �������� ������� ProblemDetected �� ������
          /// </summary>
          void SendProblemDetected(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::ProblemDetected);
          }
          /// <summary> 
          /// �������� ������� ProblemDetected ������ ����
          /// </summary>
          void RaiseProblemDetected()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ProblemDetected);
          }
          
          /// <summary> 
          /// �������� ������� Shutdown �� ������
          /// </summary>
          void SendShutdown(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Shutdown);
          }
          /// <summary> 
          /// �������� ������� Shutdown ������ ����
          /// </summary>
          void RaiseShutdown()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shutdown);
          }
          
          /// <summary> 
          /// �������� ������� Start �� ������
          /// </summary>
          void SendStart(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Start);
          }
          /// <summary> 
          /// �������� ������� Start ������ ����
          /// </summary>
          void RaiseStart()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
          }
          
        END_IMPLEMENTATION();
        
        #pragma endregion
      END_PROTOCOL()
      
      } // ������������ ���� Protocol
    } // ������������ ���� MainLogic
  } // ������������ ���� Uniteller
