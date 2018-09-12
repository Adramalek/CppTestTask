// Uniteller.Framework.Kernel.System

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
      namespace System
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(1, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// ���� ��� ������������� ����������� Delim � ���������� Split,Unpack
            /// </summary>
            enum class DelimMode
            {
              AnyOf = 0, // - ������������ ����� �� ��������, ��������� � Delim
              Sequence = 1 // - ������������ ��������� � Delim ���������
            };
            
            /// <summary> 
            /// ���� ������� ������ �� ��������� MatchFormat
            /// </summary>
            enum class Matching
            {
              Fail = 1, // - ��������� ���������
              Success = 0, // - ��������� �������
              WrongFormat = 2 // - ����������� ����� ������
            };
            
            /// <summary> 
            /// ���� ������� ������ �� ��������� Unpack
            /// </summary>
            enum class UnpackAnswerStatus
            {
              Error = 4, // - ������ (�������� ��������� ���������, ������ �����������, ������ ������ source � ��)
              IsDivider = 3, // - ������ ������� � ������������, ������������ ��������� �����
              NoHead = 2, // - �� ���������� �������� ����� ������ ��� UnpackLast
              NoTail = 1, // - �� ���������� ��������� ����� ������ ��� UnpackFirst
              Success = 0 // - �������� ����������
            };
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� DelimMode
            /// </summary>
            inline bool IsValidDelimModeValue(const int value)
            {
              return ((value >= 0)&&(value < 2));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� DelimMode
            /// </summary>
            inline DelimMode ConvertToDelimMode(const int value)
            {
              switch (value)
              {
                case 0:
                  return DelimMode::AnyOf;
                case 1:
                  return DelimMode::Sequence;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� DelimMode", value);
                }
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� Matching
            /// </summary>
            inline bool IsValidMatchingValue(const int value)
            {
              return ((value >= 0)&&(value < 3));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� Matching
            /// </summary>
            inline Matching ConvertToMatching(const int value)
            {
              switch (value)
              {
                case 1:
                  return Matching::Fail;
                case 0:
                  return Matching::Success;
                case 2:
                  return Matching::WrongFormat;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� Matching", value);
                }
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� UnpackAnswerStatus
            /// </summary>
            inline bool IsValidUnpackAnswerStatusValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� UnpackAnswerStatus
            /// </summary>
            inline UnpackAnswerStatus ConvertToUnpackAnswerStatus(const int value)
            {
              switch (value)
              {
                case 4:
                  return UnpackAnswerStatus::Error;
                case 3:
                  return UnpackAnswerStatus::IsDivider;
                case 2:
                  return UnpackAnswerStatus::NoHead;
                case 1:
                  return UnpackAnswerStatus::NoTail;
                case 0:
                  return UnpackAnswerStatus::Success;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� UnpackAnswerStatus", value);
                }
            }
            
            #pragma endregion
            
            //���������
            #pragma region Messages and wrappers
            
            //���������
            // ������� GetLength. ��������� ������ ������� �� ��������� ����� ������
            BEGIN_MESSAGE(GetLength,17,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ������
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // GetLength

            // ��������� ���������� GetLength
            BEGIN_MESSAGE(GetLengthAnswer,18,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ����� ������
              ARGUMENT(0, int, Result);
            END_MESSAGE(); // GetLengthAnswer

            // ������� MatchFormat. ��������� ������ �������, ����������� ������������ ������ Source ������� Format � ������������ ���������, ��������������� �������
            BEGIN_MESSAGE(MatchFormat,15,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ �������������
              ARGUMENT(0, string, Format);
              // �������� ������
              ARGUMENT(1, string, Source);
            END_MESSAGE(); // MatchFormat

            // ��������� ���������� ������� MatchFormat
            BEGIN_MESSAGE(MatchFormatAnswer,16,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������� �� ���������
              ENUM(0, Matching, MatchResult);
              // ������ ����� ������� ������� ������ ������������� � ��������
              ARGUMENT(1, StringList, Result);
            END_MESSAGE(); // MatchFormatAnswer

            // ������� ReplaceAll. ��������� ������ �������, �������������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source.
            BEGIN_MESSAGE(ReplaceAll,1,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ��� ������
              ARGUMENT(0, string, Pattern);
              // ������ � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value
              ARGUMENT(1, string, Source);
              // ������ ��� �������
              ARGUMENT(2, string, Value);
            END_MESSAGE(); // ReplaceAll

            // ��������� ReplaceAllAnswer (����� �� ������� ReplaceAll). �������� ��������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source, ���������� � ������� ReplaceAll.
            BEGIN_MESSAGE(ReplaceAllAnswer,2,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ���������� ������� ReplaceAll
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // ReplaceAllAnswer

            // ������� Split. ��������� ������ �������, �������������� ��������� ��������� ������ Source �� ����������� Delim
            BEGIN_MESSAGE(Split,3,4)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetAllowEmpty(false);
                SetMode((DelimMode)DelimMode::AnyOf);
              }
              // ����������� �� ������ ������ � ������
              ARGUMENT(0, bool, AllowEmpty);
              // ������ ��� ������������������ �������� ������� ������ ������������
              ARGUMENT(1, string, Delim);
              // ����� ������ �������
              ENUM(2, DelimMode, Mode);
              // ������ ������� ����� �����������
              ARGUMENT(3, string, Source);
            END_MESSAGE(); // Split

            // ��������� SplitAnswer (����� �� ������� Split)
            BEGIN_MESSAGE(SplitAnswer,4,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ���������� ������� Split
              ARGUMENT(0, StringList, Result);
            END_MESSAGE(); // SplitAnswer

            // ������� Trim. ��������� ������ �������, ��������� ���������� ������� � ������ � � ����� ������ Source
            BEGIN_MESSAGE(Trim,13,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ������
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // Trim

            // ������� TrimAnswer
            BEGIN_MESSAGE(TrimAnswer,14,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ���������� ������� Trim
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimAnswer

            // ������� TrimLeft. ��������� ������ �������, ��������� ���������� ������� � ������ ������ Source
            BEGIN_MESSAGE(TrimLeft,9,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ������
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // TrimLeft

            // ������� TrimLeftAnswer
            BEGIN_MESSAGE(TrimLeftAnswer,10,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ���������� ������� TrimLeft
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimLeftAnswer

            // ������� TrimRight. ��������� ������ �������, ��������� ���������� ������� � ����� ������ Source
            BEGIN_MESSAGE(TrimRight,11,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ������
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // TrimRight

            // ������� TrimRightAnswer
            BEGIN_MESSAGE(TrimRightAnswer,12,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ���������� ������� TrimRight
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimRightAnswer

            // ������� UnpackFirst. ��������� ������ �������, �������������� ��������� ������ Source �� "������" � "�����" �� ������� ��������� ����������� Delim
            BEGIN_MESSAGE(UnpackFirst,5,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMode((DelimMode)DelimMode::Sequence);
              }
              // ������-�����������
              ARGUMENT(0, string, Delim);
              // ����� ������ �������
              ENUM(1, DelimMode, Mode);
              // ������ ��� ���������
              ARGUMENT(2, string, Source);
            END_MESSAGE(); // UnpackFirst

            // ��������� ���������� ������� UnpackFirst
            BEGIN_MESSAGE(UnpackFirstAnswer,6,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ����� ������
              ARGUMENT(0, string, Head);
              // ���� ���������� ������� UnpackFirst
              ENUM(1, UnpackAnswerStatus, Status);
              // ��������� ����� ������
              ARGUMENT(2, string, Tail);
            END_MESSAGE(); // UnpackFirstAnswer

            // ������� UnpackEntry. ��������� ������ �������, �������������� ��������� ������ Source �� "������" � "�����" �� ���������� ��������� ����������� Delim
            BEGIN_MESSAGE(UnpackLast,7,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMode((DelimMode)DelimMode::Sequence);
              }
              // ������-�����������
              ARGUMENT(0, string, Delim);
              // ����� ������ �������
              ENUM(1, DelimMode, Mode);
              // ������ ��� ���������
              ARGUMENT(2, string, Source);
            END_MESSAGE(); // UnpackLast

            // ��������� ���������� ������� UnpackLast
            BEGIN_MESSAGE(UnpackLastAnswer,8,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ����� ������
              ARGUMENT(0, string, Head);
              // | ���� ���������� ������� UnpackLast
              ENUM(1, UnpackAnswerStatus, Status);
              // ��������� ����� ������
              ARGUMENT(2, string, Tail);
            END_MESSAGE(); // UnpackLastAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// ������� GetLength. ��������� ������ ������� �� ��������� ����� ������
              /// </summary>
              /// <param name="source">�������� ������</param>
              void GetLength(const string & source) const
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� MatchFormat. ��������� ������ �������, ����������� ������������ ������ Source ������� Format � ������������ ���������, ��������������� �������
              /// </summary>
              /// <param name="format">������ �������������</param>
              /// <param name="source">�������� ������</param>
              void MatchFormat(const string & format, const string & source) const
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ReplaceAll. ��������� ������ �������, �������������� ������ ���� ��������� ��������� Pattern �� �������� ������ Value � ������ Source.
              /// </summary>
              /// <param name="pattern">������ ��� ������</param>
              /// <param name="source">������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">������ ��� �������</param>
              void ReplaceAll(const string & pattern, const string & source, const string & value) const
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� Split. ��������� ������ �������, �������������� ��������� ��������� ������ Source �� ����������� Delim
              /// </summary>
              /// <param name="delim">������ ��� ������������������ ��������, ������� ������ ������������</param>
              /// <param name="source">������, ������� ����� �����������</param>
              /// <param name="AllowEmpty">����������� �� ������ ������ � ������</param>
              /// <param name="Mode">����� ������ �������</param>
              void Split(const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf) const
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� Trim. ��������� ������ �������, ��������� ���������� ������� � ������ � � ����� ������ Source
              /// </summary>
              /// <param name="source">�������� ������</param>
              void Trim(const string & source) const
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� TrimLeft. ��������� ������ �������, ��������� ���������� ������� � ������ ������ Source
              /// </summary>
              /// <param name="source">�������� ������</param>
              void TrimLeft(const string & source) const
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� TrimRight. ��������� ������ �������, ��������� ���������� ������� � ����� ������ Source
              /// </summary>
              /// <param name="source">�������� ������</param>
              void TrimRight(const string & source) const
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� UnpackFirst. ��������� ������ �������, �������������� ��������� ������ Source �� "������" � "�����" �� ������� ��������� ����������� Delim
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="Mode">����� ������ �������</param>
              void UnpackFirst(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence) const
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� UnpackEntry. ��������� ������ �������, �������������� ��������� ������ Source �� "������" � "�����" �� ���������� ��������� ����������� Delim
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="Mode">����� ������ �������</param>
              void UnpackLast(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence) const
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� GetLength �� ������
              /// </summary>
              /// <param name="source">�������� ������</param>
              void SendGetLength(address target, const string & source)
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetLength ������ ����
              /// </summary>
              /// <param name="source">�������� ������</param>
              void RaiseGetLength(const string & source)
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetLengthAnswer �� ������
              /// </summary>
              /// <param name="result">����� ������</param>
              void SendGetLengthAnswer(address target, int result)
              {
                G1::GetLengthAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetLengthAnswer ������ ����
              /// </summary>
              /// <param name="result">����� ������</param>
              void RaiseGetLengthAnswer(int result)
              {
                G1::GetLengthAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� MatchFormat �� ������
              /// </summary>
              /// <param name="format">������ �������������</param>
              /// <param name="source">�������� ������</param>
              void SendMatchFormat(address target, const string & format, const string & source)
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� MatchFormat ������ ����
              /// </summary>
              /// <param name="format">������ �������������</param>
              /// <param name="source">�������� ������</param>
              void RaiseMatchFormat(const string & format, const string & source)
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� MatchFormatAnswer �� ������
              /// </summary>
              /// <param name="matchResult">������� �� ���������</param>
              /// <param name="result">������ �����, ������� ������� ������ ������������� � ��������</param>
              void SendMatchFormatAnswer(address target, Matching matchResult, const StringList & result)
              {
                G1::MatchFormatAnswer cmd;
                cmd.SetMatchResult(matchResult);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� MatchFormatAnswer ������ ����
              /// </summary>
              /// <param name="matchResult">������� �� ���������</param>
              /// <param name="result">������ �����, ������� ������� ������ ������������� � ��������</param>
              void RaiseMatchFormatAnswer(Matching matchResult, const StringList & result)
              {
                G1::MatchFormatAnswer cmd;
                cmd.SetMatchResult(matchResult);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ReplaceAll �� ������
              /// </summary>
              /// <param name="pattern">������ ��� ������</param>
              /// <param name="source">������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">������ ��� �������</param>
              void SendReplaceAll(address target, const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ReplaceAll ������ ����
              /// </summary>
              /// <param name="pattern">������ ��� ������</param>
              /// <param name="source">������, � ������� ����� �������������� ������ ��������� ��������� Pattern ���������� Value</param>
              /// <param name="value">������ ��� �������</param>
              void RaiseReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ReplaceAllAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ���������� ������� ReplaceAll</param>
              void SendReplaceAllAnswer(address target, const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ReplaceAllAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ���������� ������� ReplaceAll</param>
              void RaiseReplaceAllAnswer(const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Split �� ������
              /// </summary>
              /// <param name="delim">������ ��� ������������������ ��������, ������� ������ ������������</param>
              /// <param name="source">������, ������� ����� �����������</param>
              /// <param name="allowEmpty">����������� �� ������ ������ � ������</param>
              /// <param name="mode">����� ������ �������</param>
              void SendSplit(address target, const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf)
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Split ������ ����
              /// </summary>
              /// <param name="delim">������ ��� ������������������ ��������, ������� ������ ������������</param>
              /// <param name="source">������, ������� ����� �����������</param>
              /// <param name="allowEmpty">����������� �� ������ ������ � ������</param>
              /// <param name="mode">����� ������ �������</param>
              void RaiseSplit(const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf)
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� SplitAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ���������� ������� Split</param>
              void SendSplitAnswer(address target, const StringList & result)
              {
                G1::SplitAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� SplitAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ���������� ������� Split</param>
              void RaiseSplitAnswer(const StringList & result)
              {
                G1::SplitAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� Trim �� ������
              /// </summary>
              /// <param name="source">�������� ������</param>
              void SendTrim(address target, const string & source)
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Trim ������ ����
              /// </summary>
              /// <param name="source">�������� ������</param>
              void RaiseTrim(const string & source)
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� TrimAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ���������� ������� Trim</param>
              void SendTrimAnswer(address target, const string & result)
              {
                G1::TrimAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� TrimAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ���������� ������� Trim</param>
              void RaiseTrimAnswer(const string & result)
              {
                G1::TrimAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� TrimLeft �� ������
              /// </summary>
              /// <param name="source">�������� ������</param>
              void SendTrimLeft(address target, const string & source)
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� TrimLeft ������ ����
              /// </summary>
              /// <param name="source">�������� ������</param>
              void RaiseTrimLeft(const string & source)
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� TrimLeftAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ���������� ������� TrimLeft</param>
              void SendTrimLeftAnswer(address target, const string & result)
              {
                G1::TrimLeftAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� TrimLeftAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ���������� ������� TrimLeft</param>
              void RaiseTrimLeftAnswer(const string & result)
              {
                G1::TrimLeftAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� TrimRight �� ������
              /// </summary>
              /// <param name="source">�������� ������</param>
              void SendTrimRight(address target, const string & source)
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� TrimRight ������ ����
              /// </summary>
              /// <param name="source">�������� ������</param>
              void RaiseTrimRight(const string & source)
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� TrimRightAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ���������� ������� TrimRight</param>
              void SendTrimRightAnswer(address target, const string & result)
              {
                G1::TrimRightAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� TrimRightAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ���������� ������� TrimRight</param>
              void RaiseTrimRightAnswer(const string & result)
              {
                G1::TrimRightAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� UnpackFirst �� ������
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="mode">����� ������ �������</param>
              void SendUnpackFirst(address target, const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UnpackFirst ������ ����
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="mode">����� ������ �������</param>
              void RaiseUnpackFirst(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� UnpackFirstAnswer �� ������
              /// </summary>
              /// <param name="head">�������� ����� ������</param>
              /// <param name="status">���� ���������� ������� UnpackFirst</param>
              /// <param name="tail">��������� ����� ������</param>
              void SendUnpackFirstAnswer(address target, const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackFirstAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UnpackFirstAnswer ������ ����
              /// </summary>
              /// <param name="head">�������� ����� ������</param>
              /// <param name="status">���� ���������� ������� UnpackFirst</param>
              /// <param name="tail">��������� ����� ������</param>
              void RaiseUnpackFirstAnswer(const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackFirstAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� UnpackLast �� ������
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="mode">����� ������ �������</param>
              void SendUnpackLast(address target, const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UnpackLast ������ ����
              /// </summary>
              /// <param name="delim">������-�����������</param>
              /// <param name="source">������ ��� ���������</param>
              /// <param name="mode">����� ������ �������</param>
              void RaiseUnpackLast(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� UnpackLastAnswer �� ������
              /// </summary>
              /// <param name="head">�������� ����� ������</param>
              /// <param name="status">| ���� ���������� ������� UnpackLast</param>
              /// <param name="tail">��������� ����� ������</param>
              void SendUnpackLastAnswer(address target, const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackLastAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� UnpackLastAnswer ������ ����
              /// </summary>
              /// <param name="head">�������� ����� ������</param>
              /// <param name="status">| ���� ���������� ������� UnpackLast</param>
              /// <param name="tail">��������� ����� ������</param>
              void RaiseUnpackLastAnswer(const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackLastAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // ������������ ���� Protocol
        } // ������������ ���� System
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
