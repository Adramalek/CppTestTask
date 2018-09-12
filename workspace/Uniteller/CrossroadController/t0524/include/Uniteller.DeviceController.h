// Uniteller.DeviceController

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace DeviceController
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(110, 1)
        
        #pragma region Enumerations
        /// <summary> 
        /// ���� ���������
        /// </summary>
        enum class ColorType
        {
          Green = 3, // - ������� ����
          Red = 1, // - ������� ����
          Yellow = 2 // - ������ ����
        };
        
        /// <summary>
        /// ��������� ������������ �������� ��� ������������� ���� ColorType
        /// </summary>
        inline bool IsValidColorTypeValue(const int value)
        {
          return ((value >= 1)&&(value < 4));
        }
        
        /// <summary>
        /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� ColorType
        /// </summary>
        inline ColorType ConvertToColorType(const int value)
        {
          switch (value)
          {
            case 3:
              return ColorType::Green;
            case 1:
              return ColorType::Red;
            case 2:
              return ColorType::Yellow;
            default: throw KernelException("���������� ������������� �������� �������� %d � ���� ColorType", value);
            }
        }
        
        #pragma endregion
        
        //���������
        #pragma region Messages and wrappers
        
        //���������
        // ������ � ������ ����������� (������)
        BEGIN_MESSAGE(Fail,3,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Fail

        // ���������� ����� ������
        BEGIN_MESSAGE(SetLight,1,1)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
          // - ��������� ���� �������
          ENUM(0, ColorType, Color);
        END_MESSAGE(); // SetLight

        // ������� ����������� ����������
        BEGIN_MESSAGE(Success,2,0)
          /// <summary>
          /// ������������� ���������
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Success

        
        BEGIN_WRAPPER()
          /// <summary> 
          /// ������ � ������ ����������� (������)
          /// </summary>
          void Fail() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Fail);
          }
          
          /// <summary> 
          /// ���������� ����� ������
          /// </summary>
          /// <param name="color">- ��������� ���� �������</param>
          void SetLight(ColorType color) const
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
          }
          
          /// <summary> 
          /// ������� ����������� ����������
          /// </summary>
          void Success() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
          }
          
        END_WRAPPER();
        
        BEGIN_IMPLEMENTATION()
          /// <summary> 
          /// �������� ������� Fail �� ������
          /// </summary>
          void SendFail(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Fail);
          }
          /// <summary> 
          /// �������� ������� Fail ������ ����
          /// </summary>
          void RaiseFail()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Fail);
          }
          
          /// <summary> 
          /// �������� ������� SetLight �� ������
          /// </summary>
          /// <param name="color">- ��������� ���� �������</param>
          void SendSetLight(address target, ColorType color)
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(target, cmd);
          }
          /// <summary> 
          /// �������� ������� SetLight ������ ����
          /// </summary>
          /// <param name="color">- ��������� ���� �������</param>
          void RaiseSetLight(ColorType color)
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
          }
          
          /// <summary> 
          /// �������� ������� Success �� ������
          /// </summary>
          void SendSuccess(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Success);
          }
          /// <summary> 
          /// �������� ������� Success ������ ����
          /// </summary>
          void RaiseSuccess()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
          }
          
        END_IMPLEMENTATION();
        
        #pragma endregion
      END_PROTOCOL()
      
      } // ������������ ���� Protocol
    } // ������������ ���� DeviceController
  } // ������������ ���� Uniteller
#pragma region Macro
#ifdef USE_DEVICECONTROLLER_HELPERS
#define FAIL_IF(cond, code) if (cond) {\
                             m_Protocol.RaiseFail(Protocol::G1::DeviceControllerErrors::code);\
                             return;\
                           }
#endif
#pragma endregion
