// Uniteller.Framework.Kernel.Tester

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
      namespace Tester
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(2, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// ������ ������������
            /// </summary>
            enum class InterceptorErrors
            {
              AlreadyConnected = 1, // - ��� ���������� � ������� ������
              CouldNotConnect = 2, // - �� ������� ������������ � ������
              CouldNotDisconnect = 3, // - �� ������� ����������� � ������
              TimeOut = 4, // - ������������� ������� ���� �������������� �� ��������
              UnexpectedAnswer = 5, // - ������ �������� �����
              UnexpectedEvent = 6 // - ������ ����������� �������
            };
            
            /// <summary> 
            /// ����� ��������� ������� platform-api
            /// </summary>
            enum class PlatformInterceptMode
            {
              Fail = 1, // - ������ ��� ������ ������ api-������� (����������� �������� ����������� ��������� ������ ����������� ����)
              Intercept = 2, // - ����������� � �������� �����������
              None = 3 // - �� ������������� ����� ������� � �������� ���������� ����� ���������
            };
            
            /// <summary> 
            /// ���� ������ �������� ������������
            /// </summary>
            enum class TesterErrors
            {
              AddressAlreadyExists = 40, // - �������� ����� ��� ��������� (��� ���������� �� ����)
              AddressToObserveNotFound = 28, // - ����� ��� ������������� �� ������ (� ������� observe, observeoutput)
              BadConstraints = 24, // - ���������� ������ � ������������ �� ������ � ����������� CheckTimer (����������� ���������� Fail/Pass)
              CommandFormatError = 12, // - ������ ������� �������
              CommandLineError = 16, // - ������ ������� ��������� ������
              CommandNotSupported = 10, // - ������� �� ��������������
              CouldNotConnectInterceptor = 46, // - �� ������� ���������� ����������� � ������
              CouldNotDisconnectInterceptor = 47, // - �� ������� ��������� ����������� �� ������
              DataFileFormatError = 54, // - � ����� ������ ������ ������� ����������� ������
              DataFileNotFound = 53, // - ����������� ���� ������
              DatasetFormatError = 56, // - �������� ������ ������ ������
              DatasetHasWrongLink = 52, // - � ����� ������ �� ������ ��������� ����
              DatasetNotFound = 55, // - ����� ������ �� ������ � �������
              EvalStackOverflow = 57, // - ����� ����������� �������, ����������� ��� ���������� ���������, ��������� ���������� ������
              EventNotFound = 4, // - ������� �� ������� � �����������,
              ExpectedEventNotOccured = 9, // - ��������� ������� �� ������. ����-���.
              ExtraParameterInCall = 42, // - ��� ������ ��������� �������� ������ ���������
              FatalError = 17, // - �������������� ������
              IncorrectArgumentsLength = 6, // - �� ������� ���������� ���������� (���� ������� Strict),
              IncorrectArrayIndex = 50, // - ������ ������� �������
              IncorrectEventInFilter = 34, // - �������� ������� � ������� (Intercept, Observe, EmulateMQ)
              IncorrectFormatInFilter = 36, // - �������� ������ ������� (Intercept, Observe, EmulateMQ)
              IncorrectMachineState = 14, // - �������� ��������� ������
              IncorrectModeInFilter = 35, // - �������� ����� ������� (Intercept, Observe, EmulateMQ)
              IncorrectVariableName = 27, // - ��������� �������� ����� ����������
              IndexOutOfRange = 49, // - ������ ������� ����� �� ���������� �������
              InputFileError = 2, // - ������ ������ � ������,
              InterceptorAlreadyConnected = 45, // - ��� ���������� � ������� ������
              InvalidArgumentType = 30, // - ������� �������� �������� ��� ���������
              InvalidConstraint = 22, // - �������� ��� ����������� � ����������� CheckTimer
              InvalidConstraintValue = 23, // - �������� �������� ����������� � ����������� CheckTimer
              InvalidDateTimeFormat = 51, // - �������� ������ ����/�������
              InvalidEmulateMqMode = 43, // - �������� ����� � ����������� Emulate
              InvalidEmulateMqOptions = 33, // - ��������� ��������� � ����������� EmulateMQ
              InvalidFlag = 25, // - ����������� ���� (� ������������ IsSet, IsNotSet)
              InvalidMask = 29, // - �������� ����� (����������� �������� �����)
              InvalidProcedure = 59, // - ������ � ���� ��������� (�������� �������� �� �������������)
              InvalidProcedureCall = 41, // - �������� ����� ��������� (�� ��� ��������� ��������)
              InvalidSource = 31, // - ��������� �������� ��������� (� ������� Receive)
              InvalidStringValue = 32, // - ��������� ������ ��������� ��������� ��� ��������� �� ������������� � ������ � ���������� Concat
              InvalidTimerDirective = 20, // - ��������� ��������� � ����������� CheckTimer (�� Fail, Pass � �� Kill).
              MessageToReceiveNeeded = 44, // - ��������� ��� ������� ���� ��������� ��� ������ � ReceiveAsync
              ModuleNotLoaded = 15, // - ����������� ������ ��������� �� �������
              NotInterceptor = 48, // - ������� ������������ � �������� ������������ �� �����������
              ProcedureCallConflict = 60, // - ��� ������ ��������� � ���� � ���� ���������� ���������� ����� ��� ���� out ��������
              ProtocolIncompatibility = 1, // - ��������������� ����������
              RegExpFormatError = 37, // - ������ ������� ����������� ���������
              Success = 0, // - �����
              TimerAlreadyDefined = 18, // - ������ � ����� ������ ��� ���������.
              UndefinedTimer = 19, // - ������ �� ���������
              UnexpectedEvent = 5, // - �� ������� ��� �������,
              UnexpectedEventSource = 11, // - �������� ��������� �� �� ���� ������, �� �������� �� ����� ���������
              UnexpectedModuleAddress = 13, // - �� ������� ���������� ����� ������
              UnexpectedTimerValue = 21, // - �������� ������� ����� �� ������������� �������. ���������� ��-�� ��������� ������� �������� ����������.
              UnexpectedValue = 7, // - �� ������� ���������� ����������,
              UnknownParamIndex = 8, // - �� ������ �������� � ���������
              UsingVariableNameAsTimer = 26, // - ������� ������������ ��� ���������� � �������� ����� �������
              VariableNeededForOutArgument = 58, // - ��� �������� �������� ��������� ��������� ��������� ��������� ��� ����������
              WrongParameterDefinition = 38, // - �������� ����������� ��������� ���������
              WrongProcedureDefinition = 39, // - ��������� ���������� ���������
              WrongUtxFormat = 3 // - ������ ������� UTX,
            };
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� InterceptorErrors
            /// </summary>
            inline bool IsValidInterceptorErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 7));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� InterceptorErrors
            /// </summary>
            inline InterceptorErrors ConvertToInterceptorErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return InterceptorErrors::AlreadyConnected;
                case 2:
                  return InterceptorErrors::CouldNotConnect;
                case 3:
                  return InterceptorErrors::CouldNotDisconnect;
                case 4:
                  return InterceptorErrors::TimeOut;
                case 5:
                  return InterceptorErrors::UnexpectedAnswer;
                case 6:
                  return InterceptorErrors::UnexpectedEvent;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� InterceptorErrors", value);
                }
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� PlatformInterceptMode
            /// </summary>
            inline bool IsValidPlatformInterceptModeValue(const int value)
            {
              return ((value >= 1)&&(value < 4));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� PlatformInterceptMode
            /// </summary>
            inline PlatformInterceptMode ConvertToPlatformInterceptMode(const int value)
            {
              switch (value)
              {
                case 1:
                  return PlatformInterceptMode::Fail;
                case 2:
                  return PlatformInterceptMode::Intercept;
                case 3:
                  return PlatformInterceptMode::None;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� PlatformInterceptMode", value);
                }
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� TesterErrors
            /// </summary>
            inline bool IsValidTesterErrorsValue(const int value)
            {
              return ((value >= 0)&&(value < 61));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� TesterErrors
            /// </summary>
            inline TesterErrors ConvertToTesterErrors(const int value)
            {
              switch (value)
              {
                case 40:
                  return TesterErrors::AddressAlreadyExists;
                case 28:
                  return TesterErrors::AddressToObserveNotFound;
                case 24:
                  return TesterErrors::BadConstraints;
                case 12:
                  return TesterErrors::CommandFormatError;
                case 16:
                  return TesterErrors::CommandLineError;
                case 10:
                  return TesterErrors::CommandNotSupported;
                case 46:
                  return TesterErrors::CouldNotConnectInterceptor;
                case 47:
                  return TesterErrors::CouldNotDisconnectInterceptor;
                case 54:
                  return TesterErrors::DataFileFormatError;
                case 53:
                  return TesterErrors::DataFileNotFound;
                case 56:
                  return TesterErrors::DatasetFormatError;
                case 52:
                  return TesterErrors::DatasetHasWrongLink;
                case 55:
                  return TesterErrors::DatasetNotFound;
                case 57:
                  return TesterErrors::EvalStackOverflow;
                case 4:
                  return TesterErrors::EventNotFound;
                case 9:
                  return TesterErrors::ExpectedEventNotOccured;
                case 42:
                  return TesterErrors::ExtraParameterInCall;
                case 17:
                  return TesterErrors::FatalError;
                case 6:
                  return TesterErrors::IncorrectArgumentsLength;
                case 50:
                  return TesterErrors::IncorrectArrayIndex;
                case 34:
                  return TesterErrors::IncorrectEventInFilter;
                case 36:
                  return TesterErrors::IncorrectFormatInFilter;
                case 14:
                  return TesterErrors::IncorrectMachineState;
                case 35:
                  return TesterErrors::IncorrectModeInFilter;
                case 27:
                  return TesterErrors::IncorrectVariableName;
                case 49:
                  return TesterErrors::IndexOutOfRange;
                case 2:
                  return TesterErrors::InputFileError;
                case 45:
                  return TesterErrors::InterceptorAlreadyConnected;
                case 30:
                  return TesterErrors::InvalidArgumentType;
                case 22:
                  return TesterErrors::InvalidConstraint;
                case 23:
                  return TesterErrors::InvalidConstraintValue;
                case 51:
                  return TesterErrors::InvalidDateTimeFormat;
                case 43:
                  return TesterErrors::InvalidEmulateMqMode;
                case 33:
                  return TesterErrors::InvalidEmulateMqOptions;
                case 25:
                  return TesterErrors::InvalidFlag;
                case 29:
                  return TesterErrors::InvalidMask;
                case 59:
                  return TesterErrors::InvalidProcedure;
                case 41:
                  return TesterErrors::InvalidProcedureCall;
                case 31:
                  return TesterErrors::InvalidSource;
                case 32:
                  return TesterErrors::InvalidStringValue;
                case 20:
                  return TesterErrors::InvalidTimerDirective;
                case 44:
                  return TesterErrors::MessageToReceiveNeeded;
                case 15:
                  return TesterErrors::ModuleNotLoaded;
                case 48:
                  return TesterErrors::NotInterceptor;
                case 60:
                  return TesterErrors::ProcedureCallConflict;
                case 1:
                  return TesterErrors::ProtocolIncompatibility;
                case 37:
                  return TesterErrors::RegExpFormatError;
                case 0:
                  return TesterErrors::Success;
                case 18:
                  return TesterErrors::TimerAlreadyDefined;
                case 19:
                  return TesterErrors::UndefinedTimer;
                case 5:
                  return TesterErrors::UnexpectedEvent;
                case 11:
                  return TesterErrors::UnexpectedEventSource;
                case 13:
                  return TesterErrors::UnexpectedModuleAddress;
                case 21:
                  return TesterErrors::UnexpectedTimerValue;
                case 7:
                  return TesterErrors::UnexpectedValue;
                case 8:
                  return TesterErrors::UnknownParamIndex;
                case 26:
                  return TesterErrors::UsingVariableNameAsTimer;
                case 58:
                  return TesterErrors::VariableNeededForOutArgument;
                case 38:
                  return TesterErrors::WrongParameterDefinition;
                case 39:
                  return TesterErrors::WrongProcedureDefinition;
                case 3:
                  return TesterErrors::WrongUtxFormat;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� TesterErrors", value);
                }
            }
            
            #pragma endregion
            
            //���������
            #pragma region Messages and wrappers
            
            //���������
            // �������� �������� �������
            BEGIN_MESSAGE(CheckTimer,11,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CheckTimer

            // ������� Compatible. ������������� ��������� ������������� �� � �������� ������������� ��������� �� � ���������, ����������� ��������� ������� � ������������ ������.
            BEGIN_MESSAGE(Compatible,1,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Compatible

            // ������� EndOfFile. �������� ����� ����� ��� ������� ��������� ����� ����.
            BEGIN_MESSAGE(EndOfFile,2,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // EndOfFile

            // ������ ������� ��������������� ������������. � ����������� ������� - ���� ������ ��������� ���������� � ��������� �������, ���� ������ �������.
            BEGIN_MESSAGE(Fail,5,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������� ������ -1 - ������ ������
              ENUM(0, TesterErrors, Result);
            END_MESSAGE(); // Fail

            // ������ ������� ������������ ������� ������� api ��������� ������������ � ������������� ������
            BEGIN_MESSAGE(InstallInterceptor,15,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ � ������� ����� ������������ �������� ������������� ������� ������� api ���������
              ARGUMENT(0, string, Module);
            END_MESSAGE(); // InstallInterceptor

            // ��������� ����������� ������������ � ������
            BEGIN_MESSAGE(InstallInterceptorAnswer,21,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // - ����������� �� �����������
              ARGUMENT(0, bool, Installed);
              // - ������
              ARGUMENT(1, string, Module);
            END_MESSAGE(); // InstallInterceptorAnswer

            // ������������ � ������ ��������� � ������� ������� ��������� �������� ��������� ��� ���������� ������ (Intercept)
            BEGIN_MESSAGE(Intercept,12,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Intercept

            // ��������� �������� ������ API
            BEGIN_MESSAGE(Intercepted,18,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� �������������� ������
              ARGUMENT(0, string, MethodName);
            END_MESSAGE(); // Intercepted

            // ������������ � ������ ������� ������-������������
            BEGIN_MESSAGE(InterceptorFailed,20,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMessage("");
              }
              // - �������� ������
              ARGUMENT(0, string, Message);
              // - ������� ������
              ENUM(1, InterceptorErrors, Reason);
            END_MESSAGE(); // InterceptorFailed

            // ����������� ���������
            BEGIN_MESSAGE(InterceptorInstalled,24,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // InterceptorInstalled

            // ����������� ��������
            BEGIN_MESSAGE(InterceptorUninstalled,23,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // InterceptorUninstalled

            // ������������ � ������ ��������� � ������� ������� ��������� �������� �������� ��������� ��� ���������� ������ (Observe)
            BEGIN_MESSAGE(Observe,13,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Observe

            // ������������ � ������ ��������� � ������� ������� ��������� ��������� ��������� ��� ���������� ������ (ObserveOutput)
            BEGIN_MESSAGE(ObserveOutput,14,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ObserveOutput

            // ������������ � ������ ��������� � ������� �������  Receive. �������� ����, ��������� ��������� ������� � ���������������� �����������.
            BEGIN_MESSAGE(Receive,4,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Receive

            // ������������ � ������ ��������� � ������� ������� ������������ ������ ���������� ���������
            BEGIN_MESSAGE(ReceiveAsync,19,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ReceiveAsync

            // ���������� �������� � ������ ������������ ���������
            BEGIN_MESSAGE(ScriptUpdated,9,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ScriptUpdated

            // ������������ � ������ ��������� � ������� ������� Send. �������� ����, ��������� �������� ������� � ���������������� �����������.
            BEGIN_MESSAGE(Send,3,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Send

            // ��������� ��������� ����� ��������� ��������� �������
            BEGIN_MESSAGE(SetFunctionInterceptMode,17,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� ������� PlatformApi ��� ������� ��������������� ����� ���������
              ARGUMENT(0, string, Function);
              // ����� ��������� �������
              ENUM(1, PlatformInterceptMode, Mode);
            END_MESSAGE(); // SetFunctionInterceptMode

            // ���������� ��������� ���������
            BEGIN_MESSAGE(Skip,8,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Skip

            // ��������� ���������
            BEGIN_MESSAGE(Skipped,7,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Skipped

            // ������ ������ �������
            BEGIN_MESSAGE(StartTimer,10,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // StartTimer

            // ������� Success. �������� ��������� ���������� � ��������� �������.
            BEGIN_MESSAGE(Success,6,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Success

            // ������ ������� ������������ ������� ������� api ��������� ����������� �� ������������� ������
            BEGIN_MESSAGE(UninstallInterceptor,16,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ � ������� ����� ��������� �������� ������������� ������� ������� api ���������
              ARGUMENT(0, string, Module);
            END_MESSAGE(); // UninstallInterceptor

            // ��������� ���������� ������������ �� ������
            BEGIN_MESSAGE(UninstallInterceptorAnswer,22,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // - ��������� ��� ���
              ARGUMENT(0, bool, Uninstalled);
            END_MESSAGE(); // UninstallInterceptorAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// �������� �������� �������
              /// </summary>
              void CheckTimer() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CheckTimer);
              }
              
              /// <summary> 
              /// ������� Compatible. ������������� ��������� ������������� �� � �������� ������������� ��������� �� � ���������, ����������� ��������� ������� � ������������ ������.
              /// </summary>
              void Compatible() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Compatible);
              }
              
              /// <summary> 
              /// ������� EndOfFile. �������� ����� ����� ��� ������� ��������� ����� ����.
              /// </summary>
              void EndOfFile() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::EndOfFile);
              }
              
              /// <summary> 
              /// ������ ������� ��������������� ������������. � ����������� ������� - ���� ������ ��������� ���������� � ��������� �������, ���� ������ �������.
              /// </summary>
              /// <param name="result">������� ������ -1 - ������ ������,</param>
              void Fail(TesterErrors result) const
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������ ������� ������������ ������� ������� api ��������� ������������ � ������������� ������
              /// </summary>
              /// <param name="module">������, � ������� ����� ������������ �������� ������������� ������� ������� api ���������</param>
              void InstallInterceptor(const string & module) const
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� ��������� �������� ��������� ��� ���������� ������ (Intercept)
              /// </summary>
              void Intercept() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Intercept);
              }
              
              /// <summary> 
              /// ��������� �������� ������ API
              /// </summary>
              /// <param name="methodName">��� �������������� ������</param>
              void Intercepted(const string & methodName) const
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������������ � ������ ������� ������-������������
              /// </summary>
              /// <param name="reason">- ������� ������</param>
              /// <param name="Message">- �������� ������</param>
              void InterceptorFailed(InterceptorErrors reason, string message = "") const
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ����������� ���������
              /// </summary>
              void InterceptorInstalled() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorInstalled);
              }
              
              /// <summary> 
              /// ����������� ��������
              /// </summary>
              void InterceptorUninstalled() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorUninstalled);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� ��������� �������� �������� ��������� ��� ���������� ������ (Observe)
              /// </summary>
              void Observe() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Observe);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� ��������� ��������� ��������� ��� ���������� ������ (ObserveOutput)
              /// </summary>
              void ObserveOutput() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ObserveOutput);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� �������  Receive. �������� ����, ��������� ��������� ������� � ���������������� �����������.
              /// </summary>
              void Receive() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Receive);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� ������������ ������ ���������� ���������
              /// </summary>
              void ReceiveAsync() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ReceiveAsync);
              }
              
              /// <summary> 
              /// ���������� �������� � ������ ������������ ���������
              /// </summary>
              void ScriptUpdated() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ScriptUpdated);
              }
              
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� Send. �������� ����, ��������� �������� ������� � ���������������� �����������.
              /// </summary>
              void Send() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Send);
              }
              
              /// <summary> 
              /// ��������� ��������� ����� ��������� ��������� �������
              /// </summary>
              /// <param name="function">��� ������� PlatformApi, ��� ������� ��������������� ����� ���������</param>
              /// <param name="mode">����� ��������� �������</param>
              void SetFunctionInterceptMode(const string & function, PlatformInterceptMode mode) const
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ��������� ���������
              /// </summary>
              void Skip() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skip);
              }
              
              /// <summary> 
              /// ��������� ���������
              /// </summary>
              void Skipped() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skipped);
              }
              
              /// <summary> 
              /// ������ ������ �������
              /// </summary>
              void StartTimer() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::StartTimer);
              }
              
              /// <summary> 
              /// ������� Success. �������� ��������� ���������� � ��������� �������.
              /// </summary>
              void Success() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
              }
              
              /// <summary> 
              /// ������ ������� ������������ ������� ������� api ��������� ����������� �� ������������� ������
              /// </summary>
              /// <param name="module">������, � ������� ����� ��������� �������� ������������� ������� ������� api ���������</param>
              void UninstallInterceptor(const string & module) const
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� CheckTimer �� ������
              /// </summary>
              void SendCheckTimer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::CheckTimer);
              }
              /// <summary> 
              /// �������� ������� CheckTimer ������ ����
              /// </summary>
              void RaiseCheckTimer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CheckTimer);
              }
              
              /// <summary> 
              /// �������� ������� Compatible �� ������
              /// </summary>
              void SendCompatible(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Compatible);
              }
              /// <summary> 
              /// �������� ������� Compatible ������ ����
              /// </summary>
              void RaiseCompatible()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Compatible);
              }
              
              /// <summary> 
              /// �������� ������� EndOfFile �� ������
              /// </summary>
              void SendEndOfFile(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::EndOfFile);
              }
              /// <summary> 
              /// �������� ������� EndOfFile ������ ����
              /// </summary>
              void RaiseEndOfFile()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::EndOfFile);
              }
              
              /// <summary> 
              /// �������� ������� Fail �� ������
              /// </summary>
              /// <param name="result">������� ������ -1 - ������ ������,</param>
              void SendFail(address target, TesterErrors result)
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Fail ������ ����
              /// </summary>
              /// <param name="result">������� ������ -1 - ������ ������,</param>
              void RaiseFail(TesterErrors result)
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� InstallInterceptor �� ������
              /// </summary>
              /// <param name="module">������, � ������� ����� ������������ �������� ������������� ������� ������� api ���������</param>
              void SendInstallInterceptor(address target, const string & module)
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� InstallInterceptor ������ ����
              /// </summary>
              /// <param name="module">������, � ������� ����� ������������ �������� ������������� ������� ������� api ���������</param>
              void RaiseInstallInterceptor(const string & module)
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� InstallInterceptorAnswer �� ������
              /// </summary>
              /// <param name="installed">- ����������� �� �����������</param>
              /// <param name="module">- ������</param>
              void SendInstallInterceptorAnswer(address target, bool installed, const string & module)
              {
                G1::InstallInterceptorAnswer cmd;
                cmd.SetInstalled(installed);
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� InstallInterceptorAnswer ������ ����
              /// </summary>
              /// <param name="installed">- ����������� �� �����������</param>
              /// <param name="module">- ������</param>
              void RaiseInstallInterceptorAnswer(bool installed, const string & module)
              {
                G1::InstallInterceptorAnswer cmd;
                cmd.SetInstalled(installed);
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Intercept �� ������
              /// </summary>
              void SendIntercept(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Intercept);
              }
              /// <summary> 
              /// �������� ������� Intercept ������ ����
              /// </summary>
              void RaiseIntercept()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Intercept);
              }
              
              /// <summary> 
              /// �������� ������� Intercepted �� ������
              /// </summary>
              /// <param name="methodName">��� �������������� ������</param>
              void SendIntercepted(address target, const string & methodName)
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Intercepted ������ ����
              /// </summary>
              /// <param name="methodName">��� �������������� ������</param>
              void RaiseIntercepted(const string & methodName)
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� InterceptorFailed �� ������
              /// </summary>
              /// <param name="reason">- ������� ������</param>
              /// <param name="message">- �������� ������</param>
              void SendInterceptorFailed(address target, InterceptorErrors reason, const string & message = "")
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� InterceptorFailed ������ ����
              /// </summary>
              /// <param name="reason">- ������� ������</param>
              /// <param name="message">- �������� ������</param>
              void RaiseInterceptorFailed(InterceptorErrors reason, const string & message = "")
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� InterceptorInstalled �� ������
              /// </summary>
              void SendInterceptorInstalled(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::InterceptorInstalled);
              }
              /// <summary> 
              /// �������� ������� InterceptorInstalled ������ ����
              /// </summary>
              void RaiseInterceptorInstalled()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorInstalled);
              }
              
              /// <summary> 
              /// �������� ������� InterceptorUninstalled �� ������
              /// </summary>
              void SendInterceptorUninstalled(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::InterceptorUninstalled);
              }
              /// <summary> 
              /// �������� ������� InterceptorUninstalled ������ ����
              /// </summary>
              void RaiseInterceptorUninstalled()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorUninstalled);
              }
              
              /// <summary> 
              /// �������� ������� Observe �� ������
              /// </summary>
              void SendObserve(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Observe);
              }
              /// <summary> 
              /// �������� ������� Observe ������ ����
              /// </summary>
              void RaiseObserve()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Observe);
              }
              
              /// <summary> 
              /// �������� ������� ObserveOutput �� ������
              /// </summary>
              void SendObserveOutput(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ObserveOutput);
              }
              /// <summary> 
              /// �������� ������� ObserveOutput ������ ����
              /// </summary>
              void RaiseObserveOutput()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ObserveOutput);
              }
              
              /// <summary> 
              /// �������� ������� Receive �� ������
              /// </summary>
              void SendReceive(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Receive);
              }
              /// <summary> 
              /// �������� ������� Receive ������ ����
              /// </summary>
              void RaiseReceive()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Receive);
              }
              
              /// <summary> 
              /// �������� ������� ReceiveAsync �� ������
              /// </summary>
              void SendReceiveAsync(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ReceiveAsync);
              }
              /// <summary> 
              /// �������� ������� ReceiveAsync ������ ����
              /// </summary>
              void RaiseReceiveAsync()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ReceiveAsync);
              }
              
              /// <summary> 
              /// �������� ������� ScriptUpdated �� ������
              /// </summary>
              void SendScriptUpdated(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ScriptUpdated);
              }
              /// <summary> 
              /// �������� ������� ScriptUpdated ������ ����
              /// </summary>
              void RaiseScriptUpdated()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ScriptUpdated);
              }
              
              /// <summary> 
              /// �������� ������� Send �� ������
              /// </summary>
              void SendSend(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Send);
              }
              /// <summary> 
              /// �������� ������� Send ������ ����
              /// </summary>
              void RaiseSend()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Send);
              }
              
              /// <summary> 
              /// �������� ������� SetFunctionInterceptMode �� ������
              /// </summary>
              /// <param name="function">��� ������� PlatformApi, ��� ������� ��������������� ����� ���������</param>
              /// <param name="mode">����� ��������� �������</param>
              void SendSetFunctionInterceptMode(address target, const string & function, PlatformInterceptMode mode)
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� SetFunctionInterceptMode ������ ����
              /// </summary>
              /// <param name="function">��� ������� PlatformApi, ��� ������� ��������������� ����� ���������</param>
              /// <param name="mode">����� ��������� �������</param>
              void RaiseSetFunctionInterceptMode(const string & function, PlatformInterceptMode mode)
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Skip �� ������
              /// </summary>
              void SendSkip(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Skip);
              }
              /// <summary> 
              /// �������� ������� Skip ������ ����
              /// </summary>
              void RaiseSkip()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skip);
              }
              
              /// <summary> 
              /// �������� ������� Skipped �� ������
              /// </summary>
              void SendSkipped(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Skipped);
              }
              /// <summary> 
              /// �������� ������� Skipped ������ ����
              /// </summary>
              void RaiseSkipped()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skipped);
              }
              
              /// <summary> 
              /// �������� ������� StartTimer �� ������
              /// </summary>
              void SendStartTimer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::StartTimer);
              }
              /// <summary> 
              /// �������� ������� StartTimer ������ ����
              /// </summary>
              void RaiseStartTimer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::StartTimer);
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
              /// �������� ������� UninstallInterceptor �� ������
              /// </summary>
              /// <param name="module">������, � ������� ����� ��������� �������� ������������� ������� ������� api ���������</param>
              void SendUninstallInterceptor(address target, const string & module)
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UninstallInterceptor ������ ����
              /// </summary>
              /// <param name="module">������, � ������� ����� ��������� �������� ������������� ������� ������� api ���������</param>
              void RaiseUninstallInterceptor(const string & module)
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� UninstallInterceptorAnswer �� ������
              /// </summary>
              /// <param name="uninstalled">- ��������� ��� ���</param>
              void SendUninstallInterceptorAnswer(address target, bool uninstalled)
              {
                G1::UninstallInterceptorAnswer cmd;
                cmd.SetUninstalled(uninstalled);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UninstallInterceptorAnswer ������ ����
              /// </summary>
              /// <param name="uninstalled">- ��������� ��� ���</param>
              void RaiseUninstallInterceptorAnswer(bool uninstalled)
              {
                G1::UninstallInterceptorAnswer cmd;
                cmd.SetUninstalled(uninstalled);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          

          BEGIN_PROTOCOL(2, 2)
            
            #pragma region Enumerations
            /// <summary> 
            /// ������ ������������
            /// </summary>
            /// <summary> 
            /// ����� ��������� ������� platform-api
            /// </summary>
            /// <summary> 
            /// ���� ������ �������� ������������
            /// </summary>
            #pragma endregion
            
            //���������
            #pragma region Messages and wrappers
            
            //���������
            // ������������ � ������ ��������� � ������� ������� ��������� ������� �������� ��������� �� ���������� ������ (SetFilter)
            BEGIN_MESSAGE(ChangeFilter,25,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ChangeFilter

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// ������������ � ������ ��������� � ������� ������� ��������� ������� �������� ��������� �� ���������� ������ (SetFilter)
              /// </summary>
              void ChangeFilter() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ChangeFilter, 2); 
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� ChangeFilter �� ������
              /// </summary>
              void SendChangeFilter(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::ChangeFilter, 2); 
              }
              /// <summary> 
              /// �������� ������� ChangeFilter ������ ����
              /// </summary>
              void RaiseChangeFilter()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ChangeFilter, 2); 
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // ������������ ���� Protocol
        } // ������������ ���� Tester
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
#pragma region Macro
#ifdef USE_KERNEL_TESTER_HELPERS
#define FAIL_IF(cond, code) if (cond) {\
                             m_Protocol.RaiseFail(Protocol::G1::TesterErrors::code);\
                             return;\
                           }
#endif
#pragma endregion
