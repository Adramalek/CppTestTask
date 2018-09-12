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
        
        #pragma region Enumerations
        /// <summary> 
        /// ���� ������� ���������. ������������ ������� ������������ ������.
        /// </summary>
        enum class ColorType
        {
          Green = 40, // - ������ ����, 40 ������.
          Red = 30, // - ������� ����, 30 ������.
          Yellow = 5 // - Ƹ���� ����, 5 ������.
        };
        
        /// <summary>
        /// ��������� ������������ �������� ��� ������������� ���� ColorType
        /// </summary>
        inline bool IsValidColorTypeValue(const int value)
        {
          return ((value >= 5)&&(value < 6)) || ((value >= 30)&&(value < 31)) || ((value >= 40)&&(value < 41));
        }
        
        /// <summary>
        /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� ColorType
        /// </summary>
        inline ColorType ConvertToColorType(const int value)
        {
          switch (value)
          {
            case 40:
              return ColorType::Green;
            case 30:
              return ColorType::Red;
            case 5:
              return ColorType::Yellow;
            default: throw KernelException("���������� ������������� �������� �������� %d � ���� ColorType", value);
            }
        }
        
        #pragma endregion
        
        //���������
        #pragma region Messages and wrappers
        
        //���������
        // ��������� ������ �� �����.
        BEGIN_MESSAGE(Pause,2,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Pause

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
          /// ��������� ������ �� �����.
          /// </summary>
          void Pause() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Pause);
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
          /// �������� ������� Pause �� ������
          /// </summary>
          void SendPause(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Pause);
          }
          /// <summary> 
          /// �������� ������� Pause ������ ����
          /// </summary>
          void RaisePause()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Pause);
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
