// Uniteller.Framework.Kernel.CommonApi.Interceptor

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
      namespace CommonApi
      {
        namespace Interceptor
        {
          namespace Protocol
          {

            BEGIN_PROTOCOL(23, 1)
              
              #pragma region Enumerations
              /// <summary> 
              /// �������, ������� ����� ����������� �����������
              /// </summary>
              enum class InterceptedFunctions
              {
                CloseHandle = 1, // ������� WinApi CloseHandle
                CreateEvent = 7, // ������� WinApi CreateEvent
                CreatePipe = 4, // ������� WinApi CreatePipe
                GetLastError = 2, // ������� WinApi GetLastError
                InvalidHandleTest = 12, // ���� ��������� ��������� � Handle
                LeakTest = 11, // ���� ������
                PeekNamedPipe = 5, // ������� WinApi PeekNamedPipe
                ReadFile = 6, // ������� WinApi ReadFile
                ResetEvent = 9, // ������� WinApi ResetEvent
                SetEvent = 8, // ������� WinApi SetEvent
                WaitForMultipleObjects = 3, // ������� WinApi WaitForMultipleObjects
                WaitForSingleObject = 10, // ������� WinApi WaitForSingleObject
                WriteFile = 13 // ������� WinApi WriteFile
              };
              
              /// <summary>
              /// ��������� ������������ �������� ��� ������������� ���� InterceptedFunctions
              /// </summary>
              inline bool IsValidInterceptedFunctionsValue(const int value)
              {
                return ((value >= 1)&&(value < 14));
              }
              
              /// <summary>
              /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� InterceptedFunctions
              /// </summary>
              inline InterceptedFunctions ConvertToInterceptedFunctions(const int value)
              {
                switch (value)
                {
                  case 1:
                    return InterceptedFunctions::CloseHandle;
                  case 7:
                    return InterceptedFunctions::CreateEvent;
                  case 4:
                    return InterceptedFunctions::CreatePipe;
                  case 2:
                    return InterceptedFunctions::GetLastError;
                  case 12:
                    return InterceptedFunctions::InvalidHandleTest;
                  case 11:
                    return InterceptedFunctions::LeakTest;
                  case 5:
                    return InterceptedFunctions::PeekNamedPipe;
                  case 6:
                    return InterceptedFunctions::ReadFile;
                  case 9:
                    return InterceptedFunctions::ResetEvent;
                  case 8:
                    return InterceptedFunctions::SetEvent;
                  case 3:
                    return InterceptedFunctions::WaitForMultipleObjects;
                  case 10:
                    return InterceptedFunctions::WaitForSingleObject;
                  case 13:
                    return InterceptedFunctions::WriteFile;
                  default: throw KernelException("���������� ������������� �������� �������� %d � ���� InterceptedFunctions", value);
                  }
              }
              
              #pragma endregion
              
              //���������
              #pragma region Messages and wrappers
              
              //���������
              // �������� � ������ ����������� ������ ������ � handle (������� ������������ ��� �������������� �������)
              BEGIN_MESSAGE(AlreadyReleasedHandle,26,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // AlreadyReleasedHandle

              // ����������� � ������ ��������� ������� ������� CloseHandle
              BEGIN_MESSAGE(CloseHandleIntercepted,3,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����������� Handle
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // CloseHandleIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� CloseHandle
              BEGIN_MESSAGE(CloseHandleInterceptedAnswer,4,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������� �� ������� ������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CloseHandleInterceptedAnswer

              // ����������� ����� ��������� ������������ ������������ ������ � �������� �� ����������� �������
              BEGIN_MESSAGE(CompletedTest,2,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������������ ���������
                ARGUMENT(0, StringList, Parameters);
                // - ��������� �����
                ARGUMENT(1, int, Result);
              END_MESSAGE(); // CompletedTest

              // ����������� � ������ ��������� ������� ������� CreateEvent
              BEGIN_MESSAGE(CreateEventIntercepted,13,4)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������ �� ����� Event �� �����
                ARGUMENT(0, bool, AlreadyExist);
                // - ��������� ���������
                ARGUMENT(1, bool, InitialState);
                // - ������ �������������
                ARGUMENT(2, bool, ManualReset);
                // - ���
                ARGUMENT(3, string, Name);
              END_MESSAGE(); // CreateEventIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� CreateEvent
              BEGIN_MESSAGE(CreateEventInterceptedAnswer,14,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetAllocHandle(true);
                }
                // - ��������� �� ������������� Handle �������
                ARGUMENT(0, bool, AllocHandle);
              END_MESSAGE(); // CreateEventInterceptedAnswer

              // ������� �� ������������� handle
              BEGIN_MESSAGE(CreateHandle,21,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ���������� ���������� (������������ ��� ����������� ������� ������ ������)
                ARGUMENT(0, string, DebugInfo);
              END_MESSAGE(); // CreateHandle

              // ����� �� ������� �� ������������� handle
              BEGIN_MESSAGE(CreateHandleAnswer,22,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - �������������� handle
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // CreateHandleAnswer

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� CreatePipe
              BEGIN_MESSAGE(CreatePipeInterceptedAnswer,8,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������� �� �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreatePipeInterceptedAnswer

              // ��������� ���������� ����� �������� ������ ������
              BEGIN_MESSAGE(EnableLeaksControl,24,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������ (������ ������-�����������) �������������� �������
                ARGUMENT(0, string, Module);
              END_MESSAGE(); // EnableLeaksControl

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� GetLastError
              BEGIN_MESSAGE(GetLastErrorInterceptedAnswer,5,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ��� ������
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // GetLastErrorInterceptedAnswer

              // �������� � ������ ����������� ������ ������ � handle (�������������)
              BEGIN_MESSAGE(InvalidHandle,25,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // InvalidHandle

              // ���������� �� ������� ������
              BEGIN_MESSAGE(LeaksInformation,23,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����� ����������� ������ (������ handle)
                ARGUMENT(0, int, HandleLeaksCount);
                // - ���������� �� ������� ������
                ARGUMENT(1, StringList, LeaksData);
                // - ���������� �� ������
                ARGUMENT(2, bool, LeaksDetected);
              END_MESSAGE(); // LeaksInformation

              // ����������� � ������ ��������� ������� ������� PeekNamedPipe
              BEGIN_MESSAGE(PeekNamedPipeIntercepted,9,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������ ������
                ARGUMENT(0, int, BufferSize);
                // - Handle �����
                ARGUMENT(1, int, PipeHandle);
              END_MESSAGE(); // PeekNamedPipeIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� PeekNamedPipe
              BEGIN_MESSAGE(PeekNamedPipeInterceptedAnswer,10,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - �������� ���� ��� ������ (�����)
                ARGUMENT(0, int, BytesAvail);
                // - ��������� ������ (���������)
                ARGUMENT(1, string, Data);
                // - ������ �� �����
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // PeekNamedPipeInterceptedAnswer

              // ����������� � ������ ��������� ������� ������� ReadFile
              BEGIN_MESSAGE(ReadFileIntercepted,11,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle ��� ������
                ARGUMENT(0, int, Handle);
                // - ��������� �� ��������� Overlapped
                ARGUMENT(1, int, Overlapped);
                // - ����� ���� ��� ������
                ARGUMENT(2, int, ToRead);
              END_MESSAGE(); // ReadFileIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� ReadFile
              BEGIN_MESSAGE(ReadFileInterceptedAnswer,12,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ��������� ������
                ARGUMENT(0, string, Data);
                // - ������ �� �����
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // ReadFileInterceptedAnswer

              // ����������� � ������ ��������� ������� ������� ResetEvent
              BEGIN_MESSAGE(ResetEventIntercepted,17,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle �������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // ResetEventIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� ResetEvent
              BEGIN_MESSAGE(ResetEventInterceptedAnswer,18,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - ������ �� �����
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // ResetEventInterceptedAnswer

              // ����������� � ������ ��������� ������� ������� SetEvent
              BEGIN_MESSAGE(SetEventIntercepted,15,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle �������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // SetEventIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� SetEvent
              BEGIN_MESSAGE(SetEventInterceptedAnswer,16,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - ������ �� �����
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetEventInterceptedAnswer

              // ���������� ������������ ������������� �������
              BEGIN_MESSAGE(TestInterceptedFunc,1,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ������� ��� ������������ ������������
                ENUM(0, InterceptedFunctions, Func);
              END_MESSAGE(); // TestInterceptedFunc

              // ����������� � ������ ��������� ������� ������� WaitForMultipleObjects
              BEGIN_MESSAGE(WaitForMultipleObjectsIntercepted,6,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����� �������� ��� ��������
                ARGUMENT(0, int, Count);
                // - ����-��� ��� ��������
                ARGUMENT(1, int, Milliseconds);
                // - ����� �� ����
                ARGUMENT(2, bool, WaitAll);
              END_MESSAGE(); // WaitForMultipleObjectsIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� WaitForMultipleObjects
              BEGIN_MESSAGE(WaitForMultipleObjectsInterceptedAnswer,7,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����� ��� WaitForMultipleObjects (������� ��������)
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // WaitForMultipleObjectsInterceptedAnswer

              // ����������� � ������ ��������� ������� ������� WaitForSingleObject
              BEGIN_MESSAGE(WaitForSingleObjectIntercepted,19,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����-��� ��� ��������
                ARGUMENT(0, int, Milliseconds);
                // - ������ ��� ��������
                ARGUMENT(1, int, Object);
              END_MESSAGE(); // WaitForSingleObjectIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� WaitForSingleObject
              BEGIN_MESSAGE(WaitForSingleObjectInterceptedAnswer,20,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ����� ��� WaitForSingleObject (������� ��������)
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // WaitForSingleObjectInterceptedAnswer

              // �������� � ������ ��������� ������� WriteFile
              BEGIN_MESSAGE(WriteFileIntercepted,27,4)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - �����
                ARGUMENT(0, ByteVector, Buffer);
                void SetBuffer(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
                // - ����� ���� ��� ������
                ARGUMENT(1, int, BytesToWrite);
                // - Handle �����
                ARGUMENT(2, int, FileHandle);
                // - ����� � HEX
                ARGUMENT(3, string, HexBuffer);
              END_MESSAGE(); // WriteFileIntercepted

              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� WriteFileIntercepted
              BEGIN_MESSAGE(WriteFileInterceptedAnswer,28,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - ����� ���������� ������
                ARGUMENT(0, int, BytesWritten);
                // - ������ �� �����
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // WriteFileInterceptedAnswer

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// �������� � ������ ����������� ������ ������ � handle (������� ������������ ��� �������������� �������)
                /// </summary>
                void AlreadyReleasedHandle() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::AlreadyReleasedHandle);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� CloseHandle
                /// </summary>
                /// <param name="handle">- ����������� Handle</param>
                void CloseHandleIntercepted(int handle) const
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� ����� ��������� ������������ ������������ ������ � �������� �� ����������� �������
                /// </summary>
                /// <param name="parameters">- ������������ ���������</param>
                /// <param name="result">- ��������� �����</param>
                void CompletedTest(const StringList & parameters, int result) const
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� CreateEvent
                /// </summary>
                /// <param name="alreadyExist">- ������ �� ����� Event �� �����</param>
                /// <param name="initialState">- ��������� ���������</param>
                /// <param name="manualReset">- ������ �������������</param>
                /// <param name="name">- ���</param>
                void CreateEventIntercepted(bool alreadyExist, bool initialState, bool manualReset, const string & name) const
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ������� �� ������������� handle
                /// </summary>
                /// <param name="debugInfo">- ���������� ���������� (������������ ��� ����������� ������� ������ ������)</param>
                void CreateHandle(const string & debugInfo) const
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� ���������� ����� �������� ������ ������
                /// </summary>
                /// <param name="module">- ������ (������ ������-�����������), �������������� �������</param>
                void EnableLeaksControl(const string & module) const
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� � ������ ����������� ������ ������ � handle (�������������)
                /// </summary>
                void InvalidHandle() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InvalidHandle);
                }
                
                /// <summary> 
                /// ���������� �� ������� ������
                /// </summary>
                /// <param name="handleLeaksCount">- ����� ����������� ������ (������ handle)</param>
                /// <param name="leaksData">- ���������� �� ������� ������</param>
                /// <param name="leaksDetected">- ���������� �� ������</param>
                void LeaksInformation(int handleLeaksCount, const StringList & leaksData, bool leaksDetected) const
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� PeekNamedPipe
                /// </summary>
                /// <param name="bufferSize">- ������ ������</param>
                /// <param name="pipeHandle">- Handle �����</param>
                void PeekNamedPipeIntercepted(int bufferSize, int pipeHandle) const
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� ReadFile
                /// </summary>
                /// <param name="handle">- Handle ��� ������</param>
                /// <param name="overlapped">- ��������� �� ��������� Overlapped</param>
                /// <param name="toRead">- ����� ���� ��� ������</param>
                void ReadFileIntercepted(int handle, int overlapped, int toRead) const
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� ResetEvent
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void ResetEventIntercepted(int handle) const
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� SetEvent
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void SetEventIntercepted(int handle) const
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� ������������ ������������� �������
                /// </summary>
                /// <param name="func">- ������� ��� ������������ ������������</param>
                void TestInterceptedFunc(InterceptedFunctions func) const
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� WaitForMultipleObjects
                /// </summary>
                /// <param name="count">- ����� �������� ��� ��������</param>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="waitAll">- ����� �� ����</param>
                void WaitForMultipleObjectsIntercepted(int count, int milliseconds, bool waitAll) const
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����������� � ������ ��������� ������� ������� WaitForSingleObject
                /// </summary>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="object">- ������ ��� ��������</param>
                void WaitForSingleObjectIntercepted(int milliseconds, int object) const
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� � ������ ��������� ������� WriteFile
                /// </summary>
                /// <param name="buffer">- �����</param>
                /// <param name="bytesToWrite">- ����� ���� ��� ������</param>
                /// <param name="fileHandle">- Handle �����</param>
                /// <param name="hexBuffer">- ����� � HEX</param>
                void WriteFileIntercepted(const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer) const
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// �������� ������� AlreadyReleasedHandle �� ������
                /// </summary>
                void SendAlreadyReleasedHandle(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::AlreadyReleasedHandle);
                }
                /// <summary> 
                /// �������� ������� AlreadyReleasedHandle ������ ����
                /// </summary>
                void RaiseAlreadyReleasedHandle()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::AlreadyReleasedHandle);
                }
                
                /// <summary> 
                /// �������� ������� CloseHandleIntercepted �� ������
                /// </summary>
                /// <param name="handle">- ����������� Handle</param>
                void SendCloseHandleIntercepted(address target, int handle)
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CloseHandleIntercepted ������ ����
                /// </summary>
                /// <param name="handle">- ����������� Handle</param>
                void RaiseCloseHandleIntercepted(int handle)
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CloseHandleInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ������� �� ������� ������</param>
                void SendCloseHandleInterceptedAnswer(address target, bool result)
                {
                  G1::CloseHandleInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CloseHandleInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ������� �� ������� ������</param>
                void RaiseCloseHandleInterceptedAnswer(bool result)
                {
                  G1::CloseHandleInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CompletedTest �� ������
                /// </summary>
                /// <param name="parameters">- ������������ ���������</param>
                /// <param name="result">- ��������� �����</param>
                void SendCompletedTest(address target, const StringList & parameters, int result)
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CompletedTest ������ ����
                /// </summary>
                /// <param name="parameters">- ������������ ���������</param>
                /// <param name="result">- ��������� �����</param>
                void RaiseCompletedTest(const StringList & parameters, int result)
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateEventIntercepted �� ������
                /// </summary>
                /// <param name="alreadyExist">- ������ �� ����� Event �� �����</param>
                /// <param name="initialState">- ��������� ���������</param>
                /// <param name="manualReset">- ������ �������������</param>
                /// <param name="name">- ���</param>
                void SendCreateEventIntercepted(address target, bool alreadyExist, bool initialState, bool manualReset, const string & name)
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateEventIntercepted ������ ����
                /// </summary>
                /// <param name="alreadyExist">- ������ �� ����� Event �� �����</param>
                /// <param name="initialState">- ��������� ���������</param>
                /// <param name="manualReset">- ������ �������������</param>
                /// <param name="name">- ���</param>
                void RaiseCreateEventIntercepted(bool alreadyExist, bool initialState, bool manualReset, const string & name)
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateEventInterceptedAnswer �� ������
                /// </summary>
                /// <param name="allocHandle">- ��������� �� ������������� Handle �������</param>
                void SendCreateEventInterceptedAnswer(address target, bool allocHandle = true)
                {
                  G1::CreateEventInterceptedAnswer cmd;
                  cmd.SetAllocHandle(allocHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateEventInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="allocHandle">- ��������� �� ������������� Handle �������</param>
                void RaiseCreateEventInterceptedAnswer(bool allocHandle = true)
                {
                  G1::CreateEventInterceptedAnswer cmd;
                  cmd.SetAllocHandle(allocHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateHandle �� ������
                /// </summary>
                /// <param name="debugInfo">- ���������� ���������� (������������ ��� ����������� ������� ������ ������)</param>
                void SendCreateHandle(address target, const string & debugInfo)
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateHandle ������ ����
                /// </summary>
                /// <param name="debugInfo">- ���������� ���������� (������������ ��� ����������� ������� ������ ������)</param>
                void RaiseCreateHandle(const string & debugInfo)
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateHandleAnswer �� ������
                /// </summary>
                /// <param name="result">- �������������� handle</param>
                void SendCreateHandleAnswer(address target, int result)
                {
                  G1::CreateHandleAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateHandleAnswer ������ ����
                /// </summary>
                /// <param name="result">- �������������� handle</param>
                void RaiseCreateHandleAnswer(int result)
                {
                  G1::CreateHandleAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreatePipeInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ������� �� �������</param>
                void SendCreatePipeInterceptedAnswer(address target, bool result)
                {
                  G1::CreatePipeInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreatePipeInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ������� �� �������</param>
                void RaiseCreatePipeInterceptedAnswer(bool result)
                {
                  G1::CreatePipeInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� EnableLeaksControl �� ������
                /// </summary>
                /// <param name="module">- ������ (������ ������-�����������), �������������� �������</param>
                void SendEnableLeaksControl(address target, const string & module)
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� EnableLeaksControl ������ ����
                /// </summary>
                /// <param name="module">- ������ (������ ������-�����������), �������������� �������</param>
                void RaiseEnableLeaksControl(const string & module)
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetLastErrorInterceptedAnswer �� ������
                /// </summary>
                /// <param name="code">- ��� ������</param>
                void SendGetLastErrorInterceptedAnswer(address target, int code)
                {
                  G1::GetLastErrorInterceptedAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetLastErrorInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="code">- ��� ������</param>
                void RaiseGetLastErrorInterceptedAnswer(int code)
                {
                  G1::GetLastErrorInterceptedAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� InvalidHandle �� ������
                /// </summary>
                void SendInvalidHandle(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::InvalidHandle);
                }
                /// <summary> 
                /// �������� ������� InvalidHandle ������ ����
                /// </summary>
                void RaiseInvalidHandle()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InvalidHandle);
                }
                
                /// <summary> 
                /// �������� ������� LeaksInformation �� ������
                /// </summary>
                /// <param name="handleLeaksCount">- ����� ����������� ������ (������ handle)</param>
                /// <param name="leaksData">- ���������� �� ������� ������</param>
                /// <param name="leaksDetected">- ���������� �� ������</param>
                void SendLeaksInformation(address target, int handleLeaksCount, const StringList & leaksData, bool leaksDetected)
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� LeaksInformation ������ ����
                /// </summary>
                /// <param name="handleLeaksCount">- ����� ����������� ������ (������ handle)</param>
                /// <param name="leaksData">- ���������� �� ������� ������</param>
                /// <param name="leaksDetected">- ���������� �� ������</param>
                void RaiseLeaksInformation(int handleLeaksCount, const StringList & leaksData, bool leaksDetected)
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PeekNamedPipeIntercepted �� ������
                /// </summary>
                /// <param name="bufferSize">- ������ ������</param>
                /// <param name="pipeHandle">- Handle �����</param>
                void SendPeekNamedPipeIntercepted(address target, int bufferSize, int pipeHandle)
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PeekNamedPipeIntercepted ������ ����
                /// </summary>
                /// <param name="bufferSize">- ������ ������</param>
                /// <param name="pipeHandle">- Handle �����</param>
                void RaisePeekNamedPipeIntercepted(int bufferSize, int pipeHandle)
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PeekNamedPipeInterceptedAnswer �� ������
                /// </summary>
                /// <param name="bytesAvail">- �������� ���� ��� ������ (�����)</param>
                /// <param name="data">- ��������� ������ (���������)</param>
                /// <param name="result">- ������ �� �����</param>
                void SendPeekNamedPipeInterceptedAnswer(address target, int bytesAvail, const string & data, bool result)
                {
                  G1::PeekNamedPipeInterceptedAnswer cmd;
                  cmd.SetBytesAvail(bytesAvail);
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PeekNamedPipeInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="bytesAvail">- �������� ���� ��� ������ (�����)</param>
                /// <param name="data">- ��������� ������ (���������)</param>
                /// <param name="result">- ������ �� �����</param>
                void RaisePeekNamedPipeInterceptedAnswer(int bytesAvail, const string & data, bool result)
                {
                  G1::PeekNamedPipeInterceptedAnswer cmd;
                  cmd.SetBytesAvail(bytesAvail);
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� ReadFileIntercepted �� ������
                /// </summary>
                /// <param name="handle">- Handle ��� ������</param>
                /// <param name="overlapped">- ��������� �� ��������� Overlapped</param>
                /// <param name="toRead">- ����� ���� ��� ������</param>
                void SendReadFileIntercepted(address target, int handle, int overlapped, int toRead)
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ReadFileIntercepted ������ ����
                /// </summary>
                /// <param name="handle">- Handle ��� ������</param>
                /// <param name="overlapped">- ��������� �� ��������� Overlapped</param>
                /// <param name="toRead">- ����� ���� ��� ������</param>
                void RaiseReadFileIntercepted(int handle, int overlapped, int toRead)
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� ReadFileInterceptedAnswer �� ������
                /// </summary>
                /// <param name="data">- ��������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void SendReadFileInterceptedAnswer(address target, const string & data, bool result)
                {
                  G1::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ReadFileInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="data">- ��������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void RaiseReadFileInterceptedAnswer(const string & data, bool result)
                {
                  G1::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� ResetEventIntercepted �� ������
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void SendResetEventIntercepted(address target, int handle)
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ResetEventIntercepted ������ ����
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void RaiseResetEventIntercepted(int handle)
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� ResetEventInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ������ �� �����</param>
                void SendResetEventInterceptedAnswer(address target, bool result = true)
                {
                  G1::ResetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ResetEventInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ������ �� �����</param>
                void RaiseResetEventInterceptedAnswer(bool result = true)
                {
                  G1::ResetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetEventIntercepted �� ������
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void SendSetEventIntercepted(address target, int handle)
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetEventIntercepted ������ ����
                /// </summary>
                /// <param name="handle">- Handle �������</param>
                void RaiseSetEventIntercepted(int handle)
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetEventInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ������ �� �����</param>
                void SendSetEventInterceptedAnswer(address target, bool result = true)
                {
                  G1::SetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetEventInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ������ �� �����</param>
                void RaiseSetEventInterceptedAnswer(bool result = true)
                {
                  G1::SetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestInterceptedFunc �� ������
                /// </summary>
                /// <param name="func">- ������� ��� ������������ ������������</param>
                void SendTestInterceptedFunc(address target, InterceptedFunctions func)
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestInterceptedFunc ������ ����
                /// </summary>
                /// <param name="func">- ������� ��� ������������ ������������</param>
                void RaiseTestInterceptedFunc(InterceptedFunctions func)
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WaitForMultipleObjectsIntercepted �� ������
                /// </summary>
                /// <param name="count">- ����� �������� ��� ��������</param>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="waitAll">- ����� �� ����</param>
                void SendWaitForMultipleObjectsIntercepted(address target, int count, int milliseconds, bool waitAll)
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WaitForMultipleObjectsIntercepted ������ ����
                /// </summary>
                /// <param name="count">- ����� �������� ��� ��������</param>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="waitAll">- ����� �� ����</param>
                void RaiseWaitForMultipleObjectsIntercepted(int count, int milliseconds, bool waitAll)
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WaitForMultipleObjectsInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ����� ��� WaitForMultipleObjects (������� ��������)</param>
                void SendWaitForMultipleObjectsInterceptedAnswer(address target, int result)
                {
                  G1::WaitForMultipleObjectsInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WaitForMultipleObjectsInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ����� ��� WaitForMultipleObjects (������� ��������)</param>
                void RaiseWaitForMultipleObjectsInterceptedAnswer(int result)
                {
                  G1::WaitForMultipleObjectsInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WaitForSingleObjectIntercepted �� ������
                /// </summary>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="object">- ������ ��� ��������</param>
                void SendWaitForSingleObjectIntercepted(address target, int milliseconds, int object)
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WaitForSingleObjectIntercepted ������ ����
                /// </summary>
                /// <param name="milliseconds">- ����-��� ��� ��������</param>
                /// <param name="object">- ������ ��� ��������</param>
                void RaiseWaitForSingleObjectIntercepted(int milliseconds, int object)
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WaitForSingleObjectInterceptedAnswer �� ������
                /// </summary>
                /// <param name="result">- ����� ��� WaitForSingleObject (������� ��������)</param>
                void SendWaitForSingleObjectInterceptedAnswer(address target, int result)
                {
                  G1::WaitForSingleObjectInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WaitForSingleObjectInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="result">- ����� ��� WaitForSingleObject (������� ��������)</param>
                void RaiseWaitForSingleObjectInterceptedAnswer(int result)
                {
                  G1::WaitForSingleObjectInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WriteFileIntercepted �� ������
                /// </summary>
                /// <param name="buffer">- �����</param>
                /// <param name="bytesToWrite">- ����� ���� ��� ������</param>
                /// <param name="fileHandle">- Handle �����</param>
                /// <param name="hexBuffer">- ����� � HEX</param>
                void SendWriteFileIntercepted(address target, const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer)
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WriteFileIntercepted ������ ����
                /// </summary>
                /// <param name="buffer">- �����</param>
                /// <param name="bytesToWrite">- ����� ���� ��� ������</param>
                /// <param name="fileHandle">- Handle �����</param>
                /// <param name="hexBuffer">- ����� � HEX</param>
                void RaiseWriteFileIntercepted(const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer)
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� WriteFileInterceptedAnswer �� ������
                /// </summary>
                /// <param name="bytesWritten">- ����� ���������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void SendWriteFileInterceptedAnswer(address target, int bytesWritten, bool result = true)
                {
                  G1::WriteFileInterceptedAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� WriteFileInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="bytesWritten">- ����� ���������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void RaiseWriteFileInterceptedAnswer(int bytesWritten, bool result = true)
                {
                  G1::WriteFileInterceptedAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            

            BEGIN_PROTOCOL(23, 2)
              
              #pragma region Enumerations
              /// <summary> 
              /// �������, ������� ����� ����������� �����������
              /// </summary>
              #pragma endregion
              
              //���������
              #pragma region Messages and wrappers
              
              //���������
              // ����������� �� ������� ������������ � ����� �� ��������� � ������ ������������� ������� ReadFile
              BEGIN_MESSAGE(ReadFileInterceptedAnswer,12,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ��������� ������
                ARGUMENT(0, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
                // - ������ �� �����
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // ReadFileInterceptedAnswer

              
              BEGIN_WRAPPER()
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// �������� ������� ReadFileInterceptedAnswer �� ������
                /// </summary>
                /// <param name="data">- ��������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void SendReadFileInterceptedAnswer(address target, const ByteVector & data, bool result)
                {
                  G2::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ReadFileInterceptedAnswer ������ ����
                /// </summary>
                /// <param name="data">- ��������� ������</param>
                /// <param name="result">- ������ �� �����</param>
                void RaiseReadFileInterceptedAnswer(const ByteVector & data, bool result)
                {
                  G2::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            
            } // ������������ ���� Protocol
          } // ������������ ���� Interceptor
        } // ������������ ���� CommonApi
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
