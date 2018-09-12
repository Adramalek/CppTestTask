// Uniteller.Framework.Kernel.Host

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Host
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(5, 1)
            
            #pragma region ������������
            /// <summary> 
            /// ���� ������ ����-������ �����-����
            /// </summary>
            enum class HostErrors
            {
              FailedToCreateModule = 1, // - �� ������� ������� � ���������� � ���� ����������� ������
              MasterModuleDoesNotSet = 2 // - �� ������� ���������� ����� ������-������ ��������� ���������.
            };
            
            /// <summary> 
            /// ��� �����������
            /// </summary>
            enum class ObserverKind
            {
              Both = 2, // - ���������� �� ��������� � �������� ��������
              Inbox = 1, // - ���������� �� �������� ��������
              Outbox = 0 // - ���������� �� ��������� ��������
            };
            
            // ����������
            inline bool IsValidHostErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 3));
            }
            
            inline HostErrors ConvertToHostErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return HostErrors::FailedToCreateModule;
                case 2:
                  return HostErrors::MasterModuleDoesNotSet;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� HostErrors", value);
                }
            }
            
            inline bool IsValidObserverKindValue(const int value)
            {
              return ((value >= 0)&&(value < 3));
            }
            
            inline ObserverKind ConvertToObserverKind(const int value)
            {
              switch (value)
              {
                case 2:
                  return ObserverKind::Both;
                case 1:
                  return ObserverKind::Inbox;
                case 0:
                  return ObserverKind::Outbox;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� ObserverKind", value);
                }
            }
            
            #pragma endregion
            
            #pragma region ��������� � �������
            
            //���������
            // ������� ��� ��������� ����-������ ���� (� ��� ��������� ������ � ����-��������)
            BEGIN_MESSAGE(CloseHost,13,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CloseHost

            // ������� CreateInstance ��������� ������������ �������� � ����������� � ���� �������� ��������� ����������� ����� ��������
            BEGIN_MESSAGE(CreateInstance,12,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, Generation, - ��������� ��������� ������ (0 - �����));
              ARGUMENT(1, string, ModuleId, - �������� ���������� ������������� ������);
              ARGUMENT(2, string, ModuleType, - ��� ������ ��� ��������);
            END_MESSAGE(); // CreateInstance

            // ����� �� ������� CreateInstance
            BEGIN_MESSAGE(CreateInstanceAnswer,19,4)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, Generation, - ��������� ��������� ������ (0 - �����));
              ARGUMENT(1, bool, IsCreated, - ������ �� ������);
              ARGUMENT(2, string, ModuleId, - ����������� ���������� ������������� ������);
              ARGUMENT(3, string, ModuleType, - ��� ������ ��� ��������);
            END_MESSAGE(); // CreateInstanceAnswer

            // ������� ����� ��������� ������� ������������ ���������
            BEGIN_MESSAGE(CreateInterceptor,17,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Intercepted, - ������ ��������� �������� ����� ���������������);
              ARGUMENT(1, string, Interceptor, - ������ ������� ������� ������� ������������ ���������);
            END_MESSAGE(); // CreateInterceptor

            // ���������� �������� �������
            BEGIN_MESSAGE(CreateLogicBus,15,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Master, - ������������� ������-������);
            END_MESSAGE(); // CreateLogicBus

            // �������� ���������, ���������� � ������ ��������� �������� ���������� ����
            BEGIN_MESSAGE(CreateLogicBusAnswer,16,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, LogicBusId, - ������������� ��������� ���������� ����);
            END_MESSAGE(); // CreateLogicBusAnswer

            // ������ ������� ����� ��������� ������� ���������� ��������� (������-observer, ���������� ����� ��������� ������� ������)
            BEGIN_MESSAGE(CreateObserver,18,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, ObserverKind, Mode, - ����� ����������);
              ARGUMENT(1, string, Observed, - ������ ��������� �������� ����� ������������ ����� � �����������);
              ARGUMENT(2, string, Observer, - ������ ������� ������� ������� ���������� ���������);
            END_MESSAGE(); // CreateObserver

            // ������ ����-������ ����
            BEGIN_MESSAGE(Fail,14,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, HostErrors, ErrorCode, - ��� ������);
            END_MESSAGE(); // Fail

            // �������� �������� ����� ��������� ������
            BEGIN_MESSAGE(GetCommandLineOption,10,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Option, - ��� ����� ��� ���������);
            END_MESSAGE(); // GetCommandLineOption

            // �������� �������� ����� ��������� ������
            BEGIN_MESSAGE(GetCommandLineOptionAnswer,11,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, IsOptionSet, - ����������� �� �����);
              ARGUMENT(1, string, Option, - ��� �����);
              ARGUMENT(2, string, OptionValue, - �������� �����);
            END_MESSAGE(); // GetCommandLineOptionAnswer

            // ������� QueryKey. ��������� ��������� �������� ����� ������� ����-������.
            BEGIN_MESSAGE(QueryRegistryKey,3,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Path, - ���� � ������� ����-������ ��� ������);
            END_MESSAGE(); // QueryRegistryKey

            // ��������� QueryRegistryKeyAnswer (����� �� ������� QueryRegistryKey).
            BEGIN_MESSAGE(QueryRegistryKeyAnswer,4,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, KeyExists, - ��������� ���������� �� ����);
              ARGUMENT(1, variant, Value, - ��������� �������� �����);
            END_MESSAGE(); // QueryRegistryKeyAnswer

            // ������� QuerySubKeysCount. ��������� �������� ����� ��������� ���������� � ��������� Path ����� ������� ����-������.
            BEGIN_MESSAGE(QuerySubKeysCount,7,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Path, - ���� � ������� ����-������ ��� ������ ���������);
            END_MESSAGE(); // QuerySubKeysCount

            // ��������� QuerySubKeysCountAnswer (����� �� ������� QuerySubKeysCount).
            BEGIN_MESSAGE(QuerySubKeysCountAnswer,8,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, KeyExists, - ��������� ���������� �� ����);
              ARGUMENT(1, int, Value, - ��������� ���� ���������);
            END_MESSAGE(); // QuerySubKeysCountAnswer

            // ������� ReplaceAll. ��������� ������ �������, �������������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source.
            BEGIN_MESSAGE(ReplaceAll,1,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Pattern, - ������ ��� ������);
              ARGUMENT(1, string, Source, - ������ � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value);
              ARGUMENT(2, string, Value, - ������ ��� �������);
            END_MESSAGE(); // ReplaceAll

            // ��������� ReplaceAllAnswer (����� �� ������� ReplaceAll). �������� ��������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source, ���������� � ������� ReplaceAll.
            BEGIN_MESSAGE(ReplaceAllAnswer,2,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Result, - ��������� ���������� ������� ReplaceAll);
            END_MESSAGE(); // ReplaceAllAnswer

            // ������������� ��� �������� �� ����-��������
            BEGIN_MESSAGE(SetHostProcessExitCode,9,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, - ��� ��������);
            END_MESSAGE(); // SetHostProcessExitCode

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// ������� ��� ��������� ����-������ ���� (� ��� ��������� ������ � ����-��������)
              /// </summary>
              void CloseHost()
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� CreateInstance ��������� ������������ �������� � ����������� � ���� �������� ��������� ����������� ����� ��������
              /// </summary>
              /// <param name="generation">- ��������� ��������� ������ (0 - �����)</param>
              /// <param name="moduleId">- �������� ���������� ������������� ������</param>
              /// <param name="moduleType">- ��� ������ ��� ��������</param>
              void CreateInstance(int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ����� ��������� ������� ������������ ���������
              /// </summary>
              /// <param name="intercepted">- ������, ��������� �������� ����� ���������������</param>
              /// <param name="interceptor">- ������, ������� ������� ������� ������������ ���������</param>
              void CreateInterceptor(const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� �������� �������
              /// </summary>
              /// <param name="master">- ������������� ������-������</param>
              void CreateLogicBus(const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������ ������� ����� ��������� ������� ���������� ��������� (������-observer, ���������� ����� ��������� ������� ������)
              /// </summary>
              /// <param name="mode">- ����� ����������</param>
              /// <param name="observed">- ������, ��������� �������� ����� ������������ ����� � �����������</param>
              /// <param name="observer">- ������, ������� ������� ������� ���������� ���������</param>
              void CreateObserver(ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������ ����-������ ����
              /// </summary>
              /// <param name="errorCode">- ��� ������</param>
              void Fail(HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� �������� ����� ��������� ������
              /// </summary>
              /// <param name="option">- ��� ����� ��� ���������</param>
              void GetCommandLineOption(const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� QueryKey. ��������� ��������� �������� ����� ������� ����-������.
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������</param>
              void QueryRegistryKey(const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� QuerySubKeysCount. ��������� �������� ����� ��������� ���������� � ��������� Path ����� ������� ����-������.
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������ ���������</param>
              void QuerySubKeysCount(const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ReplaceAll. ��������� ������ �������, �������������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source.
              /// </summary>
              /// <param name="pattern">- ������ ��� ������</param>
              /// <param name="source">- ������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">- ������ ��� �������</param>
              void ReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������������� ��� �������� �� ����-��������
              /// </summary>
              /// <param name="exitCode">- ��� ��������</param>
              void SetHostProcessExitCode(int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� CloseHost�� ������
              /// </summary>
              void SendCloseHost(address target)
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CloseHost ������ ����
              /// </summary>
              void RaiseCloseHost()
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateInstance�� ������
              /// </summary>
              /// <param name="generation">- ��������� ��������� ������ (0 - �����)</param>
              /// <param name="moduleId">- �������� ���������� ������������� ������</param>
              /// <param name="moduleType">- ��� ������ ��� ��������</param>
              void SendCreateInstance(address target, int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateInstance ������ ����
              /// </summary>
              /// <param name="generation">- ��������� ��������� ������ (0 - �����)</param>
              /// <param name="moduleId">- �������� ���������� ������������� ������</param>
              /// <param name="moduleType">- ��� ������ ��� ��������</param>
              void RaiseCreateInstance(int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateInstanceAnswer�� ������
              /// </summary>
              /// <param name="generation">- ��������� ��������� ������ (0 - �����)</param>
              /// <param name="isCreated">- ������ �� ������</param>
              /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
              /// <param name="moduleType">- ��� ������ ��� ��������</param>
              void SendCreateInstanceAnswer(address target, int generation, bool isCreated, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstanceAnswer cmd;
                cmd.Generation = generation;
                cmd.IsCreated = isCreated;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateInstanceAnswer ������ ����
              /// </summary>
              /// <param name="generation">- ��������� ��������� ������ (0 - �����)</param>
              /// <param name="isCreated">- ������ �� ������</param>
              /// <param name="moduleId">- ����������� ���������� ������������� ������</param>
              /// <param name="moduleType">- ��� ������ ��� ��������</param>
              void RaiseCreateInstanceAnswer(int generation, bool isCreated, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstanceAnswer cmd;
                cmd.Generation = generation;
                cmd.IsCreated = isCreated;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateInterceptor�� ������
              /// </summary>
              /// <param name="intercepted">- ������, ��������� �������� ����� ���������������</param>
              /// <param name="interceptor">- ������, ������� ������� ������� ������������ ���������</param>
              void SendCreateInterceptor(address target, const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateInterceptor ������ ����
              /// </summary>
              /// <param name="intercepted">- ������, ��������� �������� ����� ���������������</param>
              /// <param name="interceptor">- ������, ������� ������� ������� ������������ ���������</param>
              void RaiseCreateInterceptor(const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateLogicBus�� ������
              /// </summary>
              /// <param name="master">- ������������� ������-������</param>
              void SendCreateLogicBus(address target, const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateLogicBus ������ ����
              /// </summary>
              /// <param name="master">- ������������� ������-������</param>
              void RaiseCreateLogicBus(const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateLogicBusAnswer�� ������
              /// </summary>
              /// <param name="logicBusId">- ������������� ��������� ���������� ����</param>
              void SendCreateLogicBusAnswer(address target, const string & logicBusId)
              {
                G1::CreateLogicBusAnswer cmd;
                cmd.LogicBusId = logicBusId;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateLogicBusAnswer ������ ����
              /// </summary>
              /// <param name="logicBusId">- ������������� ��������� ���������� ����</param>
              void RaiseCreateLogicBusAnswer(const string & logicBusId)
              {
                G1::CreateLogicBusAnswer cmd;
                cmd.LogicBusId = logicBusId;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateObserver�� ������
              /// </summary>
              /// <param name="mode">- ����� ����������</param>
              /// <param name="observed">- ������, ��������� �������� ����� ������������ ����� � �����������</param>
              /// <param name="observer">- ������, ������� ������� ������� ���������� ���������</param>
              void SendCreateObserver(address target, ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateObserver ������ ����
              /// </summary>
              /// <param name="mode">- ����� ����������</param>
              /// <param name="observed">- ������, ��������� �������� ����� ������������ ����� � �����������</param>
              /// <param name="observer">- ������, ������� ������� ������� ���������� ���������</param>
              void RaiseCreateObserver(ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Fail�� ������
              /// </summary>
              /// <param name="errorCode">- ��� ������</param>
              void SendFail(address target, HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Fail ������ ����
              /// </summary>
              /// <param name="errorCode">- ��� ������</param>
              void RaiseFail(HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetCommandLineOption�� ������
              /// </summary>
              /// <param name="option">- ��� ����� ��� ���������</param>
              void SendGetCommandLineOption(address target, const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetCommandLineOption ������ ����
              /// </summary>
              /// <param name="option">- ��� ����� ��� ���������</param>
              void RaiseGetCommandLineOption(const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetCommandLineOptionAnswer�� ������
              /// </summary>
              /// <param name="isOptionSet">- ����������� �� �����</param>
              /// <param name="option">- ��� �����</param>
              /// <param name="optionValue">- �������� �����</param>
              void SendGetCommandLineOptionAnswer(address target, bool isOptionSet, const string & option, const string & optionValue)
              {
                G1::GetCommandLineOptionAnswer cmd;
                cmd.IsOptionSet = isOptionSet;
                cmd.Option = option;
                cmd.OptionValue = optionValue;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetCommandLineOptionAnswer ������ ����
              /// </summary>
              /// <param name="isOptionSet">- ����������� �� �����</param>
              /// <param name="option">- ��� �����</param>
              /// <param name="optionValue">- �������� �����</param>
              void RaiseGetCommandLineOptionAnswer(bool isOptionSet, const string & option, const string & optionValue)
              {
                G1::GetCommandLineOptionAnswer cmd;
                cmd.IsOptionSet = isOptionSet;
                cmd.Option = option;
                cmd.OptionValue = optionValue;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� QueryRegistryKey�� ������
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������</param>
              void SendQueryRegistryKey(address target, const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� QueryRegistryKey ������ ����
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������</param>
              void RaiseQueryRegistryKey(const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� QueryRegistryKeyAnswer�� ������
              /// </summary>
              /// <param name="keyExists">- ��������� ���������� �� ����</param>
              /// <param name="value">- ��������� �������� �����</param>
              void SendQueryRegistryKeyAnswer(address target, bool keyExists, variant value)
              {
                G1::QueryRegistryKeyAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� QueryRegistryKeyAnswer ������ ����
              /// </summary>
              /// <param name="keyExists">- ��������� ���������� �� ����</param>
              /// <param name="value">- ��������� �������� �����</param>
              void RaiseQueryRegistryKeyAnswer(bool keyExists, variant value)
              {
                G1::QueryRegistryKeyAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� QuerySubKeysCount�� ������
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������ ���������</param>
              void SendQuerySubKeysCount(address target, const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� QuerySubKeysCount ������ ����
              /// </summary>
              /// <param name="path">- ���� � ������� ����-������ ��� ������ ���������</param>
              void RaiseQuerySubKeysCount(const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� QuerySubKeysCountAnswer�� ������
              /// </summary>
              /// <param name="keyExists">- ��������� ���������� �� ����</param>
              /// <param name="value">- ��������� ���� ���������</param>
              void SendQuerySubKeysCountAnswer(address target, bool keyExists, int value)
              {
                G1::QuerySubKeysCountAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� QuerySubKeysCountAnswer ������ ����
              /// </summary>
              /// <param name="keyExists">- ��������� ���������� �� ����</param>
              /// <param name="value">- ��������� ���� ���������</param>
              void RaiseQuerySubKeysCountAnswer(bool keyExists, int value)
              {
                G1::QuerySubKeysCountAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ReplaceAll�� ������
              /// </summary>
              /// <param name="pattern">- ������ ��� ������</param>
              /// <param name="source">- ������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">- ������ ��� �������</param>
              void SendReplaceAll(address target, const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ReplaceAll ������ ����
              /// </summary>
              /// <param name="pattern">- ������ ��� ������</param>
              /// <param name="source">- ������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">- ������ ��� �������</param>
              void RaiseReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ReplaceAllAnswer�� ������
              /// </summary>
              /// <param name="result">- ��������� ���������� ������� ReplaceAll</param>
              void SendReplaceAllAnswer(address target, const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.Result = result;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ReplaceAllAnswer ������ ����
              /// </summary>
              /// <param name="result">- ��������� ���������� ������� ReplaceAll</param>
              void RaiseReplaceAllAnswer(const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.Result = result;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� SetHostProcessExitCode�� ������
              /// </summary>
              /// <param name="exitCode">- ��� ��������</param>
              void SendSetHostProcessExitCode(address target, int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� SetHostProcessExitCode ������ ����
              /// </summary>
              /// <param name="exitCode">- ��� ��������</param>
              void RaiseSetHostProcessExitCode(int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // ������������ ���� Protocol
        } // ������������ ���� Host
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
