// Uniteller.Framework.Kernel

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Protocol
      {

        BEGIN_PROTOCOL(0, 1)
          
          #pragma region Enumerations
          /// <summary> 
          /// �������� �������� ����� ������, ������������ �������� �� ����� ���������� �����-���� ��������
          /// </summary>
          enum class CommonErrors
          {
            IOError = 4, // ������ �����-������ ����������� �������. ��������, ������ ��� ������ ������, ��������� � ����������� ������ ��� ������� �������� �������.
            InvalidArgument = 1, // ����� ��������, ��� ���� �� ���������� ���������� - ������������. ��������� ��� � ������ ��� �������, ��� � � ���������� ������������� �������.
            NotExist = 5, // ��������� ����, ���������� ��� ���� �� ����������
            OutOfMemory = 3, // ����� ��������� �������� ������ � ������� ����� ������������ �������
            TimeOut = 2 // ����� �������� �����-���� ��������, ����������� �������, �������. ��������, �� ����� �����-������ �� ������ �����. �� ������ � ����-����� ���������� �������� ������ � ������������ ���������.
          };
          
          /// <summary> 
          /// ���� ������, ����������� � ������ ������������� ������� ��������� ���������
          /// </summary>
          enum class HandlerErrors
          {
            ArrayViolation = 7, // - ������� ������������ ����������� ������� � �������� ������� � ��������� ���������, �� ����������� ��������
            EventNotFound = 1, // - ������� �� ������� � �����������
            IncorrectArrayIndex = 6, // - ������ ������� �������
            IncorrectVariableName = 8, // - ��������� �������� ����� ����������
            IndexOutOfRange = 5, // - ������ ������� ����� �� ���������� �������
            InvalidArgumentType = 14, // - ������� �������� �������� ��� ���������
            InvalidDescriptor = 11, // - ��������� ���������� ������������� ������� ��������� ����������� � �������� ��������
            InvalidFlag = 12, // - ����������� ���� (� ������������ IsSet, IsNotSet)
            InvalidGeneration = 2, // - ������� �������� �������� ��������� ���������
            InvalidPause = 17, // - �������� �������� ����� � ������� Send
            InvalidSectionFormat = 16, // - ������ ������� ������ � ������������� �����������
            IsNotSetFormatError = 10, // - ������ ������� ���������� IsNotSet
            IsSetFormatError = 9, // - ������ ������� ���������� IsSet
            MalformedMessage = 4, // - ����� �������������� ��������� (null � �������� ���������, ������� ������ ���� ��������)
            RegExpFormatError = 13, // - ������ ������� ����������� ���������
            UnexpectedModuleAddress = 15, // - �� ������� ���������� ����� ������
            UnknownParamIndex = 3 // - �� ������ �������� � ���������
          };
          
          /// <summary> 
          /// �������������� ���������
          /// </summary>
          enum class Platforms
          {
            MacOs = 3, // MacOS ����� ������
            Other = 4, // ���� ��������� �� ������� ���������������� (��� �������)
            Unix = 2, // (���, ��� ��������� �� ���� Unix ��� Linux, ����� MacOS)
            Windows = 1 // Windows (NT, XP, Vista, 7, 8)
          };
          
          /// <summary>
          /// ��������� ������������ �������� ��� ������������� ���� CommonErrors
          /// </summary>
          inline bool IsValidCommonErrorsValue(const int value)
          {
            return ((value >= 1)&&(value < 6));
          }
          
          /// <summary>
          /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� CommonErrors
          /// </summary>
          inline CommonErrors ConvertToCommonErrors(const int value)
          {
            switch (value)
            {
              case 4:
                return CommonErrors::IOError;
              case 1:
                return CommonErrors::InvalidArgument;
              case 5:
                return CommonErrors::NotExist;
              case 3:
                return CommonErrors::OutOfMemory;
              case 2:
                return CommonErrors::TimeOut;
              default: throw KernelException("���������� ������������� �������� �������� %d � ���� CommonErrors", value);
              }
          }
          
          /// <summary>
          /// ��������� ������������ �������� ��� ������������� ���� HandlerErrors
          /// </summary>
          inline bool IsValidHandlerErrorsValue(const int value)
          {
            return ((value >= 1)&&(value < 18));
          }
          
          /// <summary>
          /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� HandlerErrors
          /// </summary>
          inline HandlerErrors ConvertToHandlerErrors(const int value)
          {
            switch (value)
            {
              case 7:
                return HandlerErrors::ArrayViolation;
              case 1:
                return HandlerErrors::EventNotFound;
              case 6:
                return HandlerErrors::IncorrectArrayIndex;
              case 8:
                return HandlerErrors::IncorrectVariableName;
              case 5:
                return HandlerErrors::IndexOutOfRange;
              case 14:
                return HandlerErrors::InvalidArgumentType;
              case 11:
                return HandlerErrors::InvalidDescriptor;
              case 12:
                return HandlerErrors::InvalidFlag;
              case 2:
                return HandlerErrors::InvalidGeneration;
              case 17:
                return HandlerErrors::InvalidPause;
              case 16:
                return HandlerErrors::InvalidSectionFormat;
              case 10:
                return HandlerErrors::IsNotSetFormatError;
              case 9:
                return HandlerErrors::IsSetFormatError;
              case 4:
                return HandlerErrors::MalformedMessage;
              case 13:
                return HandlerErrors::RegExpFormatError;
              case 15:
                return HandlerErrors::UnexpectedModuleAddress;
              case 3:
                return HandlerErrors::UnknownParamIndex;
              default: throw KernelException("���������� ������������� �������� �������� %d � ���� HandlerErrors", value);
              }
          }
          
          /// <summary>
          /// ��������� ������������ �������� ��� ������������� ���� Platforms
          /// </summary>
          inline bool IsValidPlatformsValue(const int value)
          {
            return ((value >= 1)&&(value < 5));
          }
          
          /// <summary>
          /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� Platforms
          /// </summary>
          inline Platforms ConvertToPlatforms(const int value)
          {
            switch (value)
            {
              case 3:
                return Platforms::MacOs;
              case 4:
                return Platforms::Other;
              case 2:
                return Platforms::Unix;
              case 1:
                return Platforms::Windows;
              default: throw KernelException("���������� ������������� �������� �������� %d � ���� Platforms", value);
              }
          }
          
          #pragma endregion
          
          //���������
          #pragma region Messages and wrappers
          
          //���������
          // ������������� ��������� ����
          BEGIN_MESSAGE(Activate,21,1)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - �������� �������
            ARGUMENT(0, VariantVector, Properties);
          END_MESSAGE(); // Activate

          // ����� ������ �� ������������� ��������� ����
          BEGIN_MESSAGE(ActivateAnswer,22,2)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
              SetMessage("");
              SetResult(true);
            }
            // - ��������� �������� � ������ �������
            ARGUMENT(0, string, Message);
            // - ��������� (������� �� ��������������)
            ARGUMENT(1, bool, Result);
          END_MESSAGE(); // ActivateAnswer

          // ��� ���������� ��������� ������ ���������� � ��������� ������ ���������
          BEGIN_MESSAGE(CommonError,10,1)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ������ ���������������� ��������
            ENUM(0, CommonErrors, Error);
          END_MESSAGE(); // CommonError

          // ����������� ������� CreateInstance, �������� ���������� ���� ���������
          BEGIN_MESSAGE(CreateInstanceAllowed,15,3)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��������� ��������� ������ (0 - �����)
            ARGUMENT(0, int, ModuleGeneration);
            // - ����������� ���������� ������������� ������
            ARGUMENT(1, string, ModuleId);
            // - ��� ������ ��� ��������
            ARGUMENT(2, string, ModuleType);
          END_MESSAGE(); // CreateInstanceAllowed

          // ����������� ������� CreateInstance, �������� ���������� ��������� � �������� ��������
          BEGIN_MESSAGE(CreateInstanceIntercepted,14,4)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - �����������
            ARGUMENT(0, string, Interceptor);
            // - ��������� ��������� ������ (0 - �����)
            ARGUMENT(1, int, ModuleGeneration);
            // - ����������� ���������� ������������� ������
            ARGUMENT(2, string, ModuleId);
            // - ��� ������ ��� ��������
            ARGUMENT(3, string, ModuleType);
          END_MESSAGE(); // CreateInstanceIntercepted

          // ��������� � ���������� ������� ��������� �� ��������������
          BEGIN_MESSAGE(GenerationNotSupported,16,2)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��� ������� ��� ������� �� ������� ��������� ������
            ARGUMENT(0, int, EventKind);
            // - ��������� ������� �� ��������������
            ARGUMENT(1, int, MessageGeneration);
          END_MESSAGE(); // GenerationNotSupported

          // ��������� ��������� ������ ���������, �� ������� ������� ���������� ������
          BEGIN_MESSAGE(GetModulePlatform,12,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // GetModulePlatform

          // ���������, ���������� ���������� � ���������, �� ������� ����������� ������
          BEGIN_MESSAGE(GetModulePlatformAnswer,13,1)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��������� �� ������� ������� ������ ������������ �����
            ENUM(0, Platforms, Platform);
          END_MESSAGE(); // GetModulePlatformAnswer

          // ���������, ������������ � ������ ���� ���� ������ � ������������ ��������� �����������
          BEGIN_MESSAGE(HandlerError,18,2)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��� ������
            ENUM(0, HandlerErrors, Kind);
            // - ��������� �������� ������
            ARGUMENT(1, string, Message);
          END_MESSAGE(); // HandlerError

          // ������������� ���������
          BEGIN_MESSAGE(InterceptedMessage,8,1)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ������������� ��������� (��������� ���������)
            ARGUMENT(0, message, Message);
          END_MESSAGE(); // InterceptedMessage

          // ���������-�������, �������������� � ���������� ������������-��������� �������������
          BEGIN_MESSAGE(MatchError,17,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // MatchError

          // ������ �� ���� ���������� ���������
          BEGIN_MESSAGE(ModuleFailedOnEvent,2,3)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��� ������� ��� ������� �� ������� ��������� ������
            ARGUMENT(0, int, EventKind);
            // - ��� ������ (����������)
            ARGUMENT(1, string, ExceptionKind);
            // - ��������� �� ������
            ARGUMENT(2, string, ExceptionMessage);
          END_MESSAGE(); // ModuleFailedOnEvent

          // ���������, ���������� �� ��������
          BEGIN_MESSAGE(OverHearedMessage,9,1)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ������������� ��������� (��������� ���������)
            ARGUMENT(0, message, Message);
          END_MESSAGE(); // OverHearedMessage

          // - ������������ �������� �� ������ Receive
          BEGIN_MESSAGE(ResetWait,20,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
              SetPriority(2147483640);
            }
          END_MESSAGE(); // ResetWait

          // ��������� ��������� ����, ������������ ��� ������������� ������������� (�� ���������� ����) ��������� � ���������
          BEGIN_MESSAGE(Shift,19,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
              SetPriority(2147483640);
            }
          END_MESSAGE(); // Shift

          // ������� �������������
          BEGIN_MESSAGE(Start,3,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Start

          // ���������, ����������� � ������ ��������� ��������� �������� ��������� ��������� ��������
          BEGIN_MESSAGE(StateAttributeChanged,6,4)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ��� ������������� �������� (��� ������� TimeOut)
            ARGUMENT(0, string, AttributeName);
            // - ����� �������� ��������
            ARGUMENT(1, variant, AttributeNewValue);
            template <class Y>
            Y CastAttributeNewValue() const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeNewValue();
              if (!val.p)
                throw BadCastException();
              return Variant::ConvertTo<Y>(val.p);
            }
            template <class Y>
            Y GetAttributeNewValue(const Y & defval) const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeNewValue();
              if (!val.p)
                return defval;
              return Variant::ConvertTo<Y>(val.p);
            }
            // - ������ �������� ��������
            ARGUMENT(2, variant, AttributeOldValue);
            template <class Y>
            Y CastAttributeOldValue() const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeOldValue();
              if (!val.p)
                throw BadCastException();
              return Variant::ConvertTo<Y>(val.p);
            }
            template <class Y>
            Y GetAttributeOldValue(const Y & defval) const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeOldValue();
              if (!val.p)
                return defval;
              return Variant::ConvertTo<Y>(val.p);
            }
            // - ������������� ������ � ������ �������� ��������� ������� ���������
            ARGUMENT(3, string, ModuleId);
          END_MESSAGE(); // StateAttributeChanged

          // �������, ����������� � ������ ��������� ��������� ��������� ��������
          BEGIN_MESSAGE(StateChanged,5,4)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ������� �������������� �������
            ARGUMENT(0, int, Event);
            // - ��� ��������� �������� ����������� � ����� ���������
            ARGUMENT(1, string, MachineName);
            // - ����� ��������� ������
            ARGUMENT(2, string, NewState);
            // - ������ ��������� ������
            ARGUMENT(3, string, OldState);
          END_MESSAGE(); // StateChanged

          // ������� ���������
          BEGIN_MESSAGE(Stop,4,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Stop

          // - �����, ���������� ������� �� ����� ������� ����������� ���������, �� ������� ������������ ������
          BEGIN_MESSAGE(Success,11,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Success

          // ��������� TimeOut. ����������� �������� ��������� � ������ ���������� ����������� ��������� ���������� � ������������ ���������.
          BEGIN_MESSAGE(TimeOut,1,0)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // TimeOut

          // ����������� ��������� �������-�����������
          BEGIN_MESSAGE(UnexpectedBehaviour,7,5)
            /// <summary>
            /// ������������� ���������
            /// </summary>
            void InitializeMessage()
            {
            }
            // - ������� �������������� �������
            ARGUMENT(0, int, Event);
            // - ��� ��������� �������� � ������� ��������� ������
            ARGUMENT(1, string, MachineName);
            // - ������������ ��������� (��������� ���������)
            ARGUMENT(2, message, Message);
            // - ����� ��������� ������
            ARGUMENT(3, string, NewState);
            // - ������ ��������� ������
            ARGUMENT(4, string, OldState);
          END_MESSAGE(); // UnexpectedBehaviour

          
          BEGIN_WRAPPER()
            /// <summary> 
            /// ������������� ��������� ����
            /// </summary>
            /// <param name="properties">- �������� �������</param>
            void Activate(const VariantVector & properties) const
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ��� ���������� ��������� ������ ���������� � ��������� ������ ���������
            /// </summary>
            /// <param name="error">- ������, ���������������� ��������</param>
            void CommonError(CommonErrors error) const
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ����������� ������� CreateInstance, �������� ���������� ���� ���������
            /// </summary>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void CreateInstanceAllowed(int moduleGeneration, const string & moduleId, const string & moduleType) const
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ����������� ������� CreateInstance, �������� ���������� ��������� � �������� ��������
            /// </summary>
            /// <param name="interceptor">- �����������</param>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void CreateInstanceIntercepted(const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType) const
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ��������� � ���������� ������� ��������� �� ��������������
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="messageGeneration">- ���������, ������� �� ��������������</param>
            void GenerationNotSupported(int eventKind, int messageGeneration) const
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ��������� ��������� ������ ���������, �� ������� ������� ���������� ������
            /// </summary>
            void GetModulePlatform() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::GetModulePlatform);
            }
            
            /// <summary> 
            /// ���������, ������������ � ������ ���� ���� ������ � ������������ ��������� �����������
            /// </summary>
            /// <param name="kind">- ��� ������</param>
            /// <param name="message">- ��������� �������� ������</param>
            void HandlerError(HandlerErrors kind, const string & message) const
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ������������� ���������
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void InterceptedMessage(message message) const
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ���������-�������, �������������� � ���������� ������������-��������� �������������
            /// </summary>
            void MatchError() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::MatchError);
            }
            
            /// <summary> 
            /// ������ �� ���� ���������� ���������
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="exceptionKind">- ��� ������ (����������)</param>
            /// <param name="exceptionMessage">- ��������� �� ������</param>
            void ModuleFailedOnEvent(int eventKind, const string & exceptionKind, const string & exceptionMessage) const
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ���������, ���������� �� ��������
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void OverHearedMessage(message message) const
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// - ������������ �������� �� ������ Receive
            /// </summary>
            void ResetWait() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ResetWait);
            }
            
            /// <summary> 
            /// ��������� ��������� ����, ������������ ��� ������������� ������������� (�� ���������� ����) ��������� � ���������
            /// </summary>
            void Shift() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shift);
            }
            
            /// <summary> 
            /// ������� �������������
            /// </summary>
            void Start() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
            }
            
            /// <summary> 
            /// ���������, ����������� � ������ ��������� ��������� �������� ��������� ��������� ��������
            /// </summary>
            /// <param name="attributeName">- ��� ������������� �������� (��� ������� TimeOut)</param>
            /// <param name="attributeNewValue">- ����� �������� ��������</param>
            /// <param name="attributeOldValue">- ������ �������� ��������</param>
            /// <param name="moduleId">- ������������� ������ � ������ �������� ��������� ������� ���������</param>
            void StateAttributeChanged(const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId) const
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������, ����������� � ������ ��������� ��������� ��������� ��������
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� ����������� � ����� ���������</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void StateChanged(int event, const string & machineName, const string & newState, const string & oldState) const
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// ������� ���������
            /// </summary>
            void Stop() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Stop);
            }
            
            /// <summary> 
            /// - �����, ���������� ������� �� ����� ������� ����������� ���������, �� ������� ������������ ������
            /// </summary>
            void Success() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
            }
            
            /// <summary> 
            /// ��������� TimeOut. ����������� �������� ��������� � ������ ���������� ����������� ��������� ���������� � ������������ ���������.
            /// </summary>
            void TimeOut() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TimeOut);
            }
            
            /// <summary> 
            /// ����������� ��������� �������-�����������
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� � ������� ��������� ������</param>
            /// <param name="message">- ������������ ��������� (��������� ���������)</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void UnexpectedBehaviour(int event, const string & machineName, message message, const string & newState, const string & oldState) const
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
          END_WRAPPER();
          
          BEGIN_IMPLEMENTATION()
            /// <summary> 
            /// �������� ������� Activate �� ������
            /// </summary>
            /// <param name="properties">- �������� �������</param>
            void SendActivate(address target, const VariantVector & properties)
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� Activate ������ ����
            /// </summary>
            /// <param name="properties">- �������� �������</param>
            void RaiseActivate(const VariantVector & properties)
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� ActivateAnswer �� ������
            /// </summary>
            /// <param name="message">- ��������� �������� � ������ �������</param>
            /// <param name="result">- ��������� (������� �� ��������������)</param>
            void SendActivateAnswer(address target, const string & message = "", bool result = true)
            {
              G1::ActivateAnswer cmd;
              cmd.SetMessage(message);
              cmd.SetResult(result);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� ActivateAnswer ������ ����
            /// </summary>
            /// <param name="message">- ��������� �������� � ������ �������</param>
            /// <param name="result">- ��������� (������� �� ��������������)</param>
            void RaiseActivateAnswer(const string & message = "", bool result = true)
            {
              G1::ActivateAnswer cmd;
              cmd.SetMessage(message);
              cmd.SetResult(result);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� CommonError �� ������
            /// </summary>
            /// <param name="error">- ������, ���������������� ��������</param>
            void SendCommonError(address target, CommonErrors error)
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� CommonError ������ ����
            /// </summary>
            /// <param name="error">- ������, ���������������� ��������</param>
            void RaiseCommonError(CommonErrors error)
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� CreateInstanceAllowed �� ������
            /// </summary>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void SendCreateInstanceAllowed(address target, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� CreateInstanceAllowed ������ ����
            /// </summary>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void RaiseCreateInstanceAllowed(int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� CreateInstanceIntercepted �� ������
            /// </summary>
            /// <param name="interceptor">- �����������</param>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void SendCreateInstanceIntercepted(address target, const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� CreateInstanceIntercepted ������ ����
            /// </summary>
            /// <param name="interceptor">- �����������</param>
            /// <param name="moduleGeneration">- ��������� ��������� ������ (0 - �����)</param>
            /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
            /// <param name="moduleType">- ��� ������ ��� ��������</param>
            void RaiseCreateInstanceIntercepted(const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� GenerationNotSupported �� ������
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="messageGeneration">- ���������, ������� �� ��������������</param>
            void SendGenerationNotSupported(address target, int eventKind, int messageGeneration)
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� GenerationNotSupported ������ ����
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="messageGeneration">- ���������, ������� �� ��������������</param>
            void RaiseGenerationNotSupported(int eventKind, int messageGeneration)
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� GetModulePlatform �� ������
            /// </summary>
            void SendGetModulePlatform(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::GetModulePlatform);
            }
            /// <summary> 
            /// �������� ������� GetModulePlatform ������ ����
            /// </summary>
            void RaiseGetModulePlatform()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::GetModulePlatform);
            }
            
            /// <summary> 
            /// �������� ������� GetModulePlatformAnswer �� ������
            /// </summary>
            /// <param name="platform">- ���������, �� ������� ������� ������, ������������ �����</param>
            void SendGetModulePlatformAnswer(address target, Platforms platform)
            {
              G1::GetModulePlatformAnswer cmd;
              cmd.SetPlatform(platform);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� GetModulePlatformAnswer ������ ����
            /// </summary>
            /// <param name="platform">- ���������, �� ������� ������� ������, ������������ �����</param>
            void RaiseGetModulePlatformAnswer(Platforms platform)
            {
              G1::GetModulePlatformAnswer cmd;
              cmd.SetPlatform(platform);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� HandlerError �� ������
            /// </summary>
            /// <param name="kind">- ��� ������</param>
            /// <param name="message">- ��������� �������� ������</param>
            void SendHandlerError(address target, HandlerErrors kind, const string & message)
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� HandlerError ������ ����
            /// </summary>
            /// <param name="kind">- ��� ������</param>
            /// <param name="message">- ��������� �������� ������</param>
            void RaiseHandlerError(HandlerErrors kind, const string & message)
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� InterceptedMessage �� ������
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void SendInterceptedMessage(address target, message message)
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� InterceptedMessage ������ ����
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void RaiseInterceptedMessage(message message)
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� MatchError �� ������
            /// </summary>
            void SendMatchError(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::MatchError);
            }
            /// <summary> 
            /// �������� ������� MatchError ������ ����
            /// </summary>
            void RaiseMatchError()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::MatchError);
            }
            
            /// <summary> 
            /// �������� ������� ModuleFailedOnEvent �� ������
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="exceptionKind">- ��� ������ (����������)</param>
            /// <param name="exceptionMessage">- ��������� �� ������</param>
            void SendModuleFailedOnEvent(address target, int eventKind, const string & exceptionKind, const string & exceptionMessage)
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� ModuleFailedOnEvent ������ ����
            /// </summary>
            /// <param name="eventKind">- ���, �������, ��� ������� �� ������� ��������� ������</param>
            /// <param name="exceptionKind">- ��� ������ (����������)</param>
            /// <param name="exceptionMessage">- ��������� �� ������</param>
            void RaiseModuleFailedOnEvent(int eventKind, const string & exceptionKind, const string & exceptionMessage)
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� OverHearedMessage �� ������
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void SendOverHearedMessage(address target, message message)
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� OverHearedMessage ������ ����
            /// </summary>
            /// <param name="message">- ������������� ��������� (��������� ���������)</param>
            void RaiseOverHearedMessage(message message)
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� ResetWait �� ������
            /// </summary>
            void SendResetWait(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::ResetWait, 1, 2147483640); 
            }
            /// <summary> 
            /// �������� ������� ResetWait ������ ����
            /// </summary>
            void RaiseResetWait()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ResetWait, 1, 2147483640); 
            }
            
            /// <summary> 
            /// �������� ������� Shift �� ������
            /// </summary>
            void SendShift(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Shift, 1, 2147483640); 
            }
            /// <summary> 
            /// �������� ������� Shift ������ ����
            /// </summary>
            void RaiseShift()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shift, 1, 2147483640); 
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
            
            /// <summary> 
            /// �������� ������� StateAttributeChanged �� ������
            /// </summary>
            /// <param name="attributeName">- ��� ������������� �������� (��� ������� TimeOut)</param>
            /// <param name="attributeNewValue">- ����� �������� ��������</param>
            /// <param name="attributeOldValue">- ������ �������� ��������</param>
            /// <param name="moduleId">- ������������� ������ � ������ �������� ��������� ������� ���������</param>
            void SendStateAttributeChanged(address target, const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId)
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� StateAttributeChanged ������ ����
            /// </summary>
            /// <param name="attributeName">- ��� ������������� �������� (��� ������� TimeOut)</param>
            /// <param name="attributeNewValue">- ����� �������� ��������</param>
            /// <param name="attributeOldValue">- ������ �������� ��������</param>
            /// <param name="moduleId">- ������������� ������ � ������ �������� ��������� ������� ���������</param>
            void RaiseStateAttributeChanged(const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId)
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� StateChanged �� ������
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� ����������� � ����� ���������</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void SendStateChanged(address target, int event, const string & machineName, const string & newState, const string & oldState)
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� StateChanged ������ ����
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� ����������� � ����� ���������</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void RaiseStateChanged(int event, const string & machineName, const string & newState, const string & oldState)
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// �������� ������� Stop �� ������
            /// </summary>
            void SendStop(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Stop);
            }
            /// <summary> 
            /// �������� ������� Stop ������ ����
            /// </summary>
            void RaiseStop()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Stop);
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
            
            /// <summary> 
            /// �������� ������� TimeOut �� ������
            /// </summary>
            void SendTimeOut(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::TimeOut);
            }
            /// <summary> 
            /// �������� ������� TimeOut ������ ����
            /// </summary>
            void RaiseTimeOut()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TimeOut);
            }
            
            /// <summary> 
            /// �������� ������� UnexpectedBehaviour �� ������
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� � ������� ��������� ������</param>
            /// <param name="message">- ������������ ��������� (��������� ���������)</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void SendUnexpectedBehaviour(address target, int event, const string & machineName, message message, const string & newState, const string & oldState)
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// �������� ������� UnexpectedBehaviour ������ ����
            /// </summary>
            /// <param name="event">- �������, �������������� �������</param>
            /// <param name="machineName">- ��� ��������� �������� � ������� ��������� ������</param>
            /// <param name="message">- ������������ ��������� (��������� ���������)</param>
            /// <param name="newState">- ����� ��������� ������</param>
            /// <param name="oldState">- ������ ��������� ������</param>
            void RaiseUnexpectedBehaviour(int event, const string & machineName, message message, const string & newState, const string & oldState)
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
          END_IMPLEMENTATION();
          
          #pragma endregion
        END_PROTOCOL()
        
        } // ������������ ���� Protocol
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
