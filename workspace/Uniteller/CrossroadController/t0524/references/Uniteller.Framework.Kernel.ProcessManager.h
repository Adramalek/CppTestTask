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
      namespace ProcessManager
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(10, 1)
            
            #pragma region ������������
            /// <summary> 
            /// ��������� ��������� ������������ ��������
            /// </summary>
            enum class ProcessPriority
            {
              AboveNorm = 3, // ��������� AboveNormal
              BelowNorm = 1, // ��������� BelowNormal
              High = 4, // ��������� High
              Idle = 0, // ��������� Idle
              Normal = 2, // ��������� Normal
              RealTime = 5 // ��������� Realtime
            };
            
            /// <summary> 
            /// ��� ������ ������ �������
            /// </summary>
            enum class ProcessStartFailedCode
            {
              AccessDenied = 3, // �� ������� ���� ������� ��� ������� ������
              FileCannotBeExecuted = 4, // ��������� ���� �� �������� ����������� �������
              FileNotFound = 2, // ������ �������� ���� � ������ ���� �������� ��� ������
              NotEnoughResourses = 0, // ������������ �������� ��� ������� ��������
              RequiredParameterMissing = 1 // ������� ������������ ��� ������
            };
            
            /// <summary> 
            /// ��� ��������� ������ � ���������
            /// </summary>
            enum class ProcessStatusCode
            {
              Finished = 0, // ������� ���������, ��������� � ����������
              InternalException = 3, // ���������� ������ �������� �� ��������� � ���������� ������� ������� ��� "������"
              NotStarted = 4, // ������� �� ���������
              Released = 2, // ������� ��� "������" �� ��������� Release ���� � �������� ���������
              Terminated = 1 // ������� ��� ������� �� ��������� Terminate ���� �� ��������
            };
            
            /// <summary> 
            /// ��������� ��������� ���� ������������ ����������
            /// </summary>
            enum class WindowState
            {
              Default = 1, // ���� �� ���������, ������ � ��������� ���� ������������ ����� �����������
              Hidden = 3, // ���� �� ������������
              Maximized = 0, // ���� ����������� �� ������ �����
              Minimized = 2 // ��������� ����
            };
            
            // ����������
            inline bool IsValidProcessPriorityValue(const int value)
            {
              return ((value >= 0)&&(value < 6));
            }
            
            inline ProcessPriority ConvertToProcessPriority(const int value)
            {
              switch (value)
              {
                case 3:
                  return ProcessPriority::AboveNorm;
                case 1:
                  return ProcessPriority::BelowNorm;
                case 4:
                  return ProcessPriority::High;
                case 0:
                  return ProcessPriority::Idle;
                case 2:
                  return ProcessPriority::Normal;
                case 5:
                  return ProcessPriority::RealTime;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� ProcessPriority", value);
                }
            }
            
            inline bool IsValidProcessStartFailedCodeValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            inline ProcessStartFailedCode ConvertToProcessStartFailedCode(const int value)
            {
              switch (value)
              {
                case 3:
                  return ProcessStartFailedCode::AccessDenied;
                case 4:
                  return ProcessStartFailedCode::FileCannotBeExecuted;
                case 2:
                  return ProcessStartFailedCode::FileNotFound;
                case 0:
                  return ProcessStartFailedCode::NotEnoughResourses;
                case 1:
                  return ProcessStartFailedCode::RequiredParameterMissing;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� ProcessStartFailedCode", value);
                }
            }
            
            inline bool IsValidProcessStatusCodeValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            inline ProcessStatusCode ConvertToProcessStatusCode(const int value)
            {
              switch (value)
              {
                case 0:
                  return ProcessStatusCode::Finished;
                case 3:
                  return ProcessStatusCode::InternalException;
                case 4:
                  return ProcessStatusCode::NotStarted;
                case 2:
                  return ProcessStatusCode::Released;
                case 1:
                  return ProcessStatusCode::Terminated;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� ProcessStatusCode", value);
                }
            }
            
            inline bool IsValidWindowStateValue(const int value)
            {
              return ((value >= 0)&&(value < 4));
            }
            
            inline WindowState ConvertToWindowState(const int value)
            {
              switch (value)
              {
                case 1:
                  return WindowState::Default;
                case 3:
                  return WindowState::Hidden;
                case 0:
                  return WindowState::Maximized;
                case 2:
                  return WindowState::Minimized;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� WindowState", value);
                }
            }
            
            #pragma endregion
            
            #pragma region ��������� � �������
            
            //���������
            // ������ ���������� ���������� �������� ��������
            BEGIN_MESSAGE(GetResult,9,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // GetResult

            // �������� ��������� � ������������ ���������� �������� ��������
            BEGIN_MESSAGE(GetResultAnswer,10,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, ��� ������������ ������� ��������� �� ��� ���������� � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0);
              ENUM(1, ProcessStatusCode, StatusCode, ��� ��� ����������);
            END_MESSAGE(); // GetResultAnswer

            // �������� ��������� � ������ ��������� ����� ������ ���������� ������� ��������� � stdout
            BEGIN_MESSAGE(ProcessConsoleRedirect,8,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Line, ������ ���������� ������� ��������� � stdout);
            END_MESSAGE(); // ProcessConsoleRedirect

            // ��������� ������������ � ������ ���������� ��������
            BEGIN_MESSAGE(ProcessFinished,4,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, ��� ������������ ������� ��������� �� ��� ���������� � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0);
              ENUM(1, ProcessStatusCode, StatusCode, ��� ��� ����������);
            END_MESSAGE(); // ProcessFinished

            // "��������" �������� � ������ ���������� ������������� ������� � ��������� ������� ���������� ���������
            BEGIN_MESSAGE(ProcessRelease,7,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessRelease

            // ������ �������� �������� � ���������� �����������
            BEGIN_MESSAGE(ProcessStart,1,8)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                CommandLine = "";
                ConsoleRedirect = false;
                CurrentDirectory = "";
                Environment = StringMap();
                Priority = ProcessPriority::Normal;
                TimeOut = 0;
                WindowInitialState = WindowState::Default;
              }
              ARGUMENT(0, string, ApplicationName, ���� � ��� ������������ ������);
              ARGUMENT(1, string, CommandLine, ��������� ������������ ������ ����������� ���������);
              ARGUMENT(2, bool, ConsoleRedirect, �������� ��������� ��� ����� �������������� �������� ������ ���������� � ������� � ���������� ������� ������ � ��������� ConsoleRedirect
�������� ������������ ��� �������� ����������);
              ARGUMENT(3, string, CurrentDirectory, �������� ����������� ������� ���������� ������������ ����������);
              ARGUMENT(4, StringMap, Environment, ���� �� ������� �� ���� ���������� ��������� �� ������������ ������� ��������� ���������� ���������
���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ���� ���������� PATH �� ������������ ��������� ���������� ���������
���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ��� ���������� PATH �� ������������ ��������� ���������� ��������� ���� ���������� PATH �� ������� ���������);
              ENUM(5, ProcessPriority, Priority, ��������� ��������� ��������);
              ARGUMENT(6, int, TimeOut, ������� � ������������� �� ��������� �������� ������� ����������� �������������.);
              ENUM(7, WindowState, WindowInitialState, ��������� ��������� � ��������� ����);
            END_MESSAGE(); // ProcessStart

            // �������� ��������� ������������ � ������ ����������� ������� ��������
            BEGIN_MESSAGE(ProcessStartFailed,3,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, ProcessStartFailedCode, Reason, ������� �� ������� ������ �������� ��� ���������);
            END_MESSAGE(); // ProcessStartFailed

            // �������� ��������� ������������ � ������ ��������� ������� ��������
            BEGIN_MESSAGE(ProcessStartSuccessful,2,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessStartSuccessful

            // ���������� ��������
            BEGIN_MESSAGE(ProcessTerminate,5,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessTerminate

            // ��������� ����������� ���������� �������� �������� �� ��������
            BEGIN_MESSAGE(ProcessTerminateDueToTimeOut,6,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessTerminateDueToTimeOut

            // �������� ��������� � ������ ��������� ����������� ������ ��� ������ ������� �������� ��������
            BEGIN_MESSAGE(Ready,12,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Ready

            // ��������� �������������� ������ ������ ��� ���������� ����� ������ (��������)
            BEGIN_MESSAGE(Redo,13,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Redo

            // ���������� ������ ��� ������ ������� �������� ��������
            BEGIN_MESSAGE(Reset,11,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Reset

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// ������ ���������� ���������� �������� ��������
              /// </summary>
              void GetResult()
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��������� � ������ ��������� ����� ������ ���������� ������� ��������� � stdout
              /// </summary>
              /// <param name="line">������ ���������� ������� ��������� � stdout</param>
              void ProcessConsoleRedirect(const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ��������� ������������ � ������ ���������� ��������
              /// </summary>
              /// <param name="exitCode">��� ������������ ������� ��������� �� ��� ����������, � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0</param>
              /// <param name="statusCode">��� ��� ����������</param>
              void ProcessFinished(int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// "��������" �������� � ������ ���������� ������������� ������� � ��������� ������� ���������� ���������
              /// </summary>
              void ProcessRelease()
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������ �������� �������� � ���������� �����������
              /// </summary>
              /// <param name="applicationName">���� � ��� ������������ ������</param>
              /// <param name="CommandLine">��������� ������������ ������ ����������� ���������</param>
              /// <param name="ConsoleRedirect">�������� ��������� ��� ����� �������������� �������� ������ ���������� � ������� � ���������� ������� ������ � ��������� ConsoleRedirect
              /// �������� ������������ ��� �������� ����������</param>
              /// <param name="CurrentDirectory">�������� ����������� ������� ���������� ������������ ����������</param>
              /// <param name="Environment">���� �� ������� �� ���� ���������� ���������, �� ������������ ������� ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ���� ���������� PATH, �� ������������ ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ��� ���������� PATH, �� ������������ ��������� ���������� ��������� ���� ���������� PATH �� ������� ���������</param>
              /// <param name="Priority">��������� ��������� ��������</param>
              /// <param name="TimeOut">������� � ������������� �� ��������� �������� ������� ����������� �������������.</param>
              /// <param name="WindowInitialState">��������� ��������� � ��������� ����</param>
              void ProcessStart(const string & applicationName, string commandLine = "", bool consoleRedirect = false, string currentDirectory = "", StringMap environment = StringMap(), ProcessPriority priority = ProcessPriority::Normal, int timeOut = 0, WindowState windowInitialState = WindowState::Default)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��������� ������������ � ������ ����������� ������� ��������
              /// </summary>
              /// <param name="reason">������� �� ������� ������ �������� ��� ���������</param>
              void ProcessStartFailed(ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��������� ������������ � ������ ��������� ������� ��������
              /// </summary>
              void ProcessStartSuccessful()
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ��������
              /// </summary>
              void ProcessTerminate()
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ��������� ����������� ���������� �������� �������� �� ��������
              /// </summary>
              void ProcessTerminateDueToTimeOut()
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��������� � ������ ��������� ����������� ������ ��� ������ ������� �������� ��������
              /// </summary>
              void Ready()
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ��������� �������������� ������ ������ ��� ���������� ����� ������ (��������)
              /// </summary>
              void Redo()
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ������ ��� ������ ������� �������� ��������
              /// </summary>
              void Reset()
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� GetResult�� ������
              /// </summary>
              void SendGetResult(address target)
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetResult ������ ����
              /// </summary>
              void RaiseGetResult()
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetResultAnswer�� ������
              /// </summary>
              /// <param name="exitCode">��� ������������ ������� ��������� �� ��� ����������, � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0</param>
              /// <param name="statusCode">��� ��� ����������</param>
              void SendGetResultAnswer(address target, int exitCode, ProcessStatusCode statusCode)
              {
                G1::GetResultAnswer cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetResultAnswer ������ ����
              /// </summary>
              /// <param name="exitCode">��� ������������ ������� ��������� �� ��� ����������, � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0</param>
              /// <param name="statusCode">��� ��� ����������</param>
              void RaiseGetResultAnswer(int exitCode, ProcessStatusCode statusCode)
              {
                G1::GetResultAnswer cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessConsoleRedirect�� ������
              /// </summary>
              /// <param name="line">������ ���������� ������� ��������� � stdout</param>
              void SendProcessConsoleRedirect(address target, const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessConsoleRedirect ������ ����
              /// </summary>
              /// <param name="line">������ ���������� ������� ��������� � stdout</param>
              void RaiseProcessConsoleRedirect(const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessFinished�� ������
              /// </summary>
              /// <param name="exitCode">��� ������������ ������� ��������� �� ��� ����������, � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0</param>
              /// <param name="statusCode">��� ��� ����������</param>
              void SendProcessFinished(address target, int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessFinished ������ ����
              /// </summary>
              /// <param name="exitCode">��� ������������ ������� ��������� �� ��� ����������, � ������ ���� ������� �� ��� ������� ���� �� ��� ��������� �������� ������������ 0</param>
              /// <param name="statusCode">��� ��� ����������</param>
              void RaiseProcessFinished(int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessRelease�� ������
              /// </summary>
              void SendProcessRelease(address target)
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessRelease ������ ����
              /// </summary>
              void RaiseProcessRelease()
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessStart�� ������
              /// </summary>
              /// <param name="applicationName">���� � ��� ������������ ������</param>
              /// <param name="commandLine">��������� ������������ ������ ����������� ���������</param>
              /// <param name="consoleRedirect">�������� ��������� ��� ����� �������������� �������� ������ ���������� � ������� � ���������� ������� ������ � ��������� ConsoleRedirect
              /// �������� ������������ ��� �������� ����������</param>
              /// <param name="currentDirectory">�������� ����������� ������� ���������� ������������ ����������</param>
              /// <param name="environment">���� �� ������� �� ���� ���������� ���������, �� ������������ ������� ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ���� ���������� PATH, �� ������������ ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ��� ���������� PATH, �� ������������ ��������� ���������� ��������� ���� ���������� PATH �� ������� ���������</param>
              /// <param name="priority">��������� ��������� ��������</param>
              /// <param name="timeOut">������� � ������������� �� ��������� �������� ������� ����������� �������������.</param>
              /// <param name="windowInitialState">��������� ��������� � ��������� ����</param>
              void SendProcessStart(address target, const string & applicationName, const string & commandLine, bool consoleRedirect, const string & currentDirectory, StringMap environment, ProcessPriority priority, int timeOut, WindowState windowInitialState)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessStart ������ ����
              /// </summary>
              /// <param name="applicationName">���� � ��� ������������ ������</param>
              /// <param name="commandLine">��������� ������������ ������ ����������� ���������</param>
              /// <param name="consoleRedirect">�������� ��������� ��� ����� �������������� �������� ������ ���������� � ������� � ���������� ������� ������ � ��������� ConsoleRedirect
              /// �������� ������������ ��� �������� ����������</param>
              /// <param name="currentDirectory">�������� ����������� ������� ���������� ������������ ����������</param>
              /// <param name="environment">���� �� ������� �� ���� ���������� ���������, �� ������������ ������� ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ���� ���������� PATH, �� ������������ ��������� ���������� ���������
              /// ���� ������� ���� ���� ��������� ���������� ��������� � ����� ��� ��� ���������� PATH, �� ������������ ��������� ���������� ��������� ���� ���������� PATH �� ������� ���������</param>
              /// <param name="priority">��������� ��������� ��������</param>
              /// <param name="timeOut">������� � ������������� �� ��������� �������� ������� ����������� �������������.</param>
              /// <param name="windowInitialState">��������� ��������� � ��������� ����</param>
              void RaiseProcessStart(const string & applicationName, const string & commandLine, bool consoleRedirect, const string & currentDirectory, StringMap environment, ProcessPriority priority, int timeOut, WindowState windowInitialState)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessStartFailed�� ������
              /// </summary>
              /// <param name="reason">������� �� ������� ������ �������� ��� ���������</param>
              void SendProcessStartFailed(address target, ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessStartFailed ������ ����
              /// </summary>
              /// <param name="reason">������� �� ������� ������ �������� ��� ���������</param>
              void RaiseProcessStartFailed(ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessStartSuccessful�� ������
              /// </summary>
              void SendProcessStartSuccessful(address target)
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessStartSuccessful ������ ����
              /// </summary>
              void RaiseProcessStartSuccessful()
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessTerminate�� ������
              /// </summary>
              void SendProcessTerminate(address target)
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessTerminate ������ ����
              /// </summary>
              void RaiseProcessTerminate()
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ProcessTerminateDueToTimeOut�� ������
              /// </summary>
              void SendProcessTerminateDueToTimeOut(address target)
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ProcessTerminateDueToTimeOut ������ ����
              /// </summary>
              void RaiseProcessTerminateDueToTimeOut()
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Ready�� ������
              /// </summary>
              void SendReady(address target)
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Ready ������ ����
              /// </summary>
              void RaiseReady()
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Redo�� ������
              /// </summary>
              void SendRedo(address target)
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Redo ������ ����
              /// </summary>
              void RaiseRedo()
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Reset�� ������
              /// </summary>
              void SendReset(address target)
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Reset ������ ����
              /// </summary>
              void RaiseReset()
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // ������������ ���� Protocol
        } // ������������ ���� ProcessManager
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
