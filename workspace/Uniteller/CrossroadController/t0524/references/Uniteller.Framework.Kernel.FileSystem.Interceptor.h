// Uniteller.Framework.Kernel.FileSystem.Interceptor

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
      namespace FileSystem
      {
        namespace Interceptor
        {
          namespace Protocol
          {

            BEGIN_PROTOCOL(11, 1)
              
              #pragma region Enumerations
              /// <summary> 
              /// ����������� ������ ��� ������ � �������� ��������
              /// </summary>
              enum class FileSystemApiErrors
              {
                ErrorAccessDenied = 5, // ���� ����������
                ErrorCurrentDirectory = 16, // ����� �� ����� ���� �������
                ErrorDevNotExist = 55, // ���������� ����������
                ErrorDiskFull = 112, // ������������ ���������� ����� �� �����
                ErrorFileNotFound = 2, // ���� �� ������
                ErrorHandleDiskFull = 39, // ���� ����������
                ErrorInvalidDrive = 15, // ���� �� ����������
                ErrorNetworkAccessDenied = 65, // ������� ���� ����������
                ErrorNoMoreFiles = 18, // ������ ��� ������, ��������������� �������� �������
                ErrorPathNotFound = 3 // ���� � ����� �� ������
              };
              
              /// <summary> 
              /// ����� ������
              /// </summary>
              /// <summary>
              /// ��������� ������������ �������� ��� ������������� ���� FileSystemApiErrors
              /// </summary>
              inline bool IsValidFileSystemApiErrorsValue(const int value)
              {
                return ((value >= 2)&&(value < 4)) || ((value >= 5)&&(value < 6)) || ((value >= 15)&&(value < 17)) || ((value >= 18)&&(value < 19)) || ((value >= 39)&&(value < 40)) || ((value >= 55)&&(value < 56)) || ((value >= 65)&&(value < 66)) || ((value >= 112)&&(value < 113));
              }
              
              /// <summary>
              /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� FileSystemApiErrors
              /// </summary>
              inline FileSystemApiErrors ConvertToFileSystemApiErrors(const int value)
              {
                switch (value)
                {
                  case 5:
                    return FileSystemApiErrors::ErrorAccessDenied;
                  case 16:
                    return FileSystemApiErrors::ErrorCurrentDirectory;
                  case 55:
                    return FileSystemApiErrors::ErrorDevNotExist;
                  case 112:
                    return FileSystemApiErrors::ErrorDiskFull;
                  case 2:
                    return FileSystemApiErrors::ErrorFileNotFound;
                  case 39:
                    return FileSystemApiErrors::ErrorHandleDiskFull;
                  case 15:
                    return FileSystemApiErrors::ErrorInvalidDrive;
                  case 65:
                    return FileSystemApiErrors::ErrorNetworkAccessDenied;
                  case 18:
                    return FileSystemApiErrors::ErrorNoMoreFiles;
                  case 3:
                    return FileSystemApiErrors::ErrorPathNotFound;
                  default: throw KernelException("���������� ������������� �������� �������� %d � ���� FileSystemApiErrors", value);
                  }
              }
              
              #pragma endregion
              
              #pragma region Flags
              
              /// <summary> 
              /// ��������� WinAPI ��� �������� ���������
              /// </summary>
              enum class WinApiAttr
              {
                Archive = 32, //��������
                Folder = 16, //�����
                Hidden = 2, //�������
                Normal = 128, //�� ����� ������ ���������
                ReadOnly = 1, //������ ������
                System = 4 //���������
              };
              
              /// <summary>
              /// ��������, ����������� ����������� ����� ��� ������ WinApiAttr
              /// </summary>
              inline WinApiAttr operator|(WinApiAttr a, WinApiAttr b)
              {
                return static_cast<WinApiAttr>(static_cast<int>(a), static_cast<int>(b));
              }
              
              /// <summary>
              /// ��������� ��������� ����������� �� ����� mask � WinApiAttr
              /// </summary>
              /// <param name="variable">����������</param>
              /// <param name="mask">����� ��� ��������</param>
              inline bool IsFlagSet(WinApiAttr variable, WinApiAttr mask)
              {
                int m = static_cast<int>(mask);
                return (static_cast<int>(variable) & m)==m;
              }
              
              /// <summary>
              /// ��������� ������������ �������� ��� ����� WinApiAttr
              /// </summary>
              /// <param name="value">�������� ��� ��������</param>
              inline bool IsValidWinApiAttrValue(const int value)
              {
                return value <= 183;
              }
              #pragma endregion
              
              //���������
              #pragma region Messages and wrappers
              
              //���������
              // ����������� ����� ��������� ������������ ������������ ������ � �������� �� ����������� �������
              BEGIN_MESSAGE(CompletedTest,1,6)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetAttributes((WinApiAttr)WinApiAttr::Normal);
                  SetParamInt(0);
                  SetParamStr("");
                  SetResult(false);
                  SetTimeCreated(std::chrono::system_clock::time_point(std::chrono::milliseconds(0)));
                  SetTimeModified(std::chrono::system_clock::time_point(std::chrono::milliseconds(0)));
                }
                // ������������ ��������
                FLAG(0, WinApiAttr, Attributes);
                // �������� ��������
                ARGUMENT(1, int, ParamInt);
                // ��������� ��������
                ARGUMENT(2, string, ParamStr);
                // ��������� ������ ������� �� �� ��������� �����
                ARGUMENT(3, bool, Result);
                // ���� ��������
                ARGUMENT(4, timestamp_t, TimeCreated);
                // ���� ���������
                ARGUMENT(5, timestamp_t, TimeModified);
              END_MESSAGE(); // CompletedTest

              // ��������� � ��������� ������ ������� WindowsApi CopyFileA
              BEGIN_MESSAGE(CopyFileAIntercepted,27,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �������� �����
                ARGUMENT(0, string, PathDst);
                // ���� � ����������� �����
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // CopyFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi CopyFileA
              BEGIN_MESSAGE(CopyFileA_Answer,28,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CopyFileA_Answer

              // ��������� � ��������� ������ ������� WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(CreateDirectoryAIntercepted,24,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // CreateDirectoryAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(CreateDirectoryA_Answer,25,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreateDirectoryA_Answer

              // ��������� � ��������� ������ ������� WindowsApi CreateFileA
              BEGIN_MESSAGE(CreateFileAIntercepted,30,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // CreateFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi CreateFileA
              BEGIN_MESSAGE(CreateFileA_Answer,31,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreateFileA_Answer

              // ��������� � ��������� ������ ������� WindowsApi DeleteFileA
              BEGIN_MESSAGE(DeleteFileAIntercepted,33,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // DeleteFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi DeleteFileA
              BEGIN_MESSAGE(DeleteFileA_Answer,34,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // DeleteFileA_Answer

              // ����� �� ��������� � ��������� ������ ������� fclose
              BEGIN_MESSAGE(FcloseAnswer,65,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // true - ���� ������� ������ false - ������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FcloseAnswer

              // ��������� � ��������� ������ ������� fclose
              BEGIN_MESSAGE(FcloseIntercepted,64,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FcloseIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi Feof
              BEGIN_MESSAGE(FeofAnswer,61,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // true - ����� ����� false - ��� ���
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FeofAnswer

              // ��������� � ��������� ������ ������� WindowsApi Feof
              BEGIN_MESSAGE(FeofIntercepted,60,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FeofIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi FindClose
              BEGIN_MESSAGE(FindCloseAnswer,74,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FindCloseAnswer

              // ��������� � ��������� ������ ������� WindowsApi FindClose
              BEGIN_MESSAGE(FindCloseIntercepted,73,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FindCloseIntercepted

              // ��������� � ��������� ������ ������� WindowsApi FindFirstFileA
              BEGIN_MESSAGE(FindFirstFileAIntercepted,18,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ������
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // FindFirstFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi FindFirstFileA
              BEGIN_MESSAGE(FindFirstFileA_Answer,19,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����� ��� � WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // �������� ���������� �����
                ARGUMENT(1, string, Filename);
                // false - ������� ������ INVALID_ARGUMENT true - �������� ����������� �������
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindFirstFileA_Answer

              // ��������� � ��������� ������ ������� WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(FindFirstFileExAIntercepted,15,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ������
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // FindFirstFileExAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(FindFirstFileExA_Answer,16,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����� ��� � WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // �������� ���������� �����
                ARGUMENT(1, string, Filename);
                // false - ������� ������ INVALID_ARGUMENT true - �������� ����������� �������
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindFirstFileExA_Answer

              // ��������� � ��������� ������ ������� WindowsApi FindNextFileA
              BEGIN_MESSAGE(FindNextFileAIntercepted,42,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FindNextFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi FindNextFileA
              BEGIN_MESSAGE(FindNextFileA_Answer,43,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����� ��� � WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // �������� ���������� �����
                ARGUMENT(1, string, Filename);
                // ��������� ������ �������
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindNextFileA_Answer

              // ����� �� ��������� � ��������� ������ ������� fopen_s
              BEGIN_MESSAGE(Fopen_sAnswer,55,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���������
                ARGUMENT(0, int, Errno);
              END_MESSAGE(); // Fopen_sAnswer

              // ��������� � ��������� ������ ������� fopen_s
              BEGIN_MESSAGE(Fopen_sIntercepted,54,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �����
                ARGUMENT(0, string, Mode);
                // ���� � �����
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // Fopen_sIntercepted

              // ����� �� ��������� � ��������� ������ ������� fread
              BEGIN_MESSAGE(FreadAnswer,58,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����������� �������
                ARGUMENT(0, string, Buffer);
              END_MESSAGE(); // FreadAnswer

              // ��������� � ��������� ������ ������� fread
              BEGIN_MESSAGE(FreadIntercepted,57,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���������� ���������
                ARGUMENT(0, int, Count);
                // �������� ������������
                ARGUMENT(1, int, Handle);
                // ������ ��������
                ARGUMENT(2, int, ItemSize);
              END_MESSAGE(); // FreadIntercepted

              // ��������� � ��������� ������ ������� WindowsApi GetFileAttributesA
              BEGIN_MESSAGE(GetFileAttributesAIntercepted,51,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // GetFileAttributesAIntercepted

              // ����� �� ��������� � ��������� ������ ������� GetFileAttributesA
              BEGIN_MESSAGE(GetFileAttributesA_Answer,52,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� �����
                FLAG(0, WinApiAttr, Attributes);
              END_MESSAGE(); // GetFileAttributesA_Answer

              // ����� �� ��������� � ��������� ������ ������� WindowsApi GetFileSize
              BEGIN_MESSAGE(GetFileSizeAnswer,49,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ������ �����
                ARGUMENT(0, int, Size);
              END_MESSAGE(); // GetFileSizeAnswer

              // ��������� � ��������� ������ ������� WindowsApi GetFileSize
              BEGIN_MESSAGE(GetFileSizeIntercepted,48,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // GetFileSizeIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi GetFileTime
              BEGIN_MESSAGE(GetFileTimeAnswer,46,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
                // ���� �������� �����
                ARGUMENT(1, timestamp_t, TimeCreate);
                // ���� ��������� �����
                ARGUMENT(2, timestamp_t, TimeModify);
              END_MESSAGE(); // GetFileTimeAnswer

              // ��������� � ��������� ������ ������� WindowsApi GetFileTime
              BEGIN_MESSAGE(GetFileTimeIntercepted,45,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // GetFileTimeIntercepted

              // ��������� � ��������� ������ ������� WindowsApi MoveFileA
              BEGIN_MESSAGE(MoveFileAIntercepted,39,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �������� �����
                ARGUMENT(0, string, PathDst);
                // ���� � ������������� �����
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // MoveFileAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi MoveFileA
              BEGIN_MESSAGE(MoveFileA_Answer,40,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // MoveFileA_Answer

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(PathCanonicalizeAIntercepted,6,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ������������� ����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathCanonicalizeAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(PathCanonicalizeA_Answer,7,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������������� ����
                ARGUMENT(0, string, Path);
                // true - ������� false - ���������
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // PathCanonicalizeA_Answer

              // ��������� � ��������� ������ ������� PathCombineA
              BEGIN_MESSAGE(PathCombineAIntercepted,3,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ������
                ARGUMENT(0, string, PathIn);
                // ���������� ������
                ARGUMENT(1, string, PathMore);
              END_MESSAGE(); // PathCombineAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathCombineA
              BEGIN_MESSAGE(PathCombineA_Answer,4,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathCombineA_Answer

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(PathFindFileNameAIntercepted,9,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathFindFileNameAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(PathFindFileNameA_Answer,10,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� �����
                ARGUMENT(0, string, Filename);
              END_MESSAGE(); // PathFindFileNameA_Answer

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(PathRemoveFileSpecAIntercepted,12,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ������ �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathRemoveFileSpecAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(PathRemoveFileSpecA_Answer,13,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� ��� ����� �����
                ARGUMENT(0, string, Path);
                // ��������� ������ �������
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // PathRemoveFileSpecA_Answer

              // ��������� � ��������� ������ ������� WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(RemoveDirectoryAIntercepted,36,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // RemoveDirectoryAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(RemoveDirectoryA_Answer,37,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // RemoveDirectoryA_Answer

              // ��������� � ��������� ������ ������� WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(SHCreateDirectoryExAIntercepted,67,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // SHCreateDirectoryExAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(SHCreateDirectoryExA_Answer,68,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� ������ (��� �� ��� � ��� GetLastError)
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // SHCreateDirectoryExA_Answer

              // ��������� � ��������� ������ ������� WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(SetFileAttributesAIntercepted,21,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� �����
                FLAG(0, WinApiAttr, Attributes);
                // ���� � �����
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // SetFileAttributesAIntercepted

              // ����� �� ��������� � ��������� ������ ������� WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(SetFileAttributesA_Answer,22,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��������� ������ �������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetFileAttributesA_Answer

              // ���������� �������� ����� ������� WindowsApi CopyFileA
              BEGIN_MESSAGE(TestCopyFileA,26,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ����� � ������� ��������
                ARGUMENT(0, string, PathDst);
                // ���� � ����������� �����
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // TestCopyFileA

              // ���������� �������� ����� ������� WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(TestCreateDirectoryA,23,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ����������� �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestCreateDirectoryA

              // ���������� �������� ����� ������� WindowsApi CreateFileA
              BEGIN_MESSAGE(TestCreateFileA,29,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ������������ �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestCreateFileA

              // ���������� �������� ����� ������� WindowsApi DeleteFileA
              BEGIN_MESSAGE(TestDeleteFileA,32,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ���������� �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestDeleteFileA

              // ���������� �������� ����� ������� fclose
              BEGIN_MESSAGE(TestFclose,63,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFclose

              // ���������� �������� ����� ������� feof
              BEGIN_MESSAGE(TestFeof,59,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFeof

              // ���������� �������� ����� ������� WindowsApi FindClose
              BEGIN_MESSAGE(TestFindClose,72,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFindClose

              // ���������� �������� ����� ������� WindowsApi FindFirstFileA
              BEGIN_MESSAGE(TestFindFirstFileA,17,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ������
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // TestFindFirstFileA

              // ���������� �������� ����� ������� WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(TestFindFirstFileExA,14,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ������
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // TestFindFirstFileExA

              // ���������� �������� ����� ������� WindowsApi FindNextFileA
              BEGIN_MESSAGE(TestFindNextFileA,41,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFindNextFileA

              // ���������� �������� ����� ������� fopen_s
              BEGIN_MESSAGE(TestFopen_s,53,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �����
                ARGUMENT(0, string, Mode);
                // ���� � �����
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // TestFopen_s

              // ���������� �������� ����� ������� fread
              BEGIN_MESSAGE(TestFread,56,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                  SetItemSize(1);
                }
                // ���������� ���������
                ARGUMENT(0, int, Count);
                // ������ ��������
                ARGUMENT(1, int, ItemSize);
              END_MESSAGE(); // TestFread

              // ���������� �������� ����� ������� WindowsApi GetFileAttributesA
              BEGIN_MESSAGE(TestGetFileAttributesA,50,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestGetFileAttributesA

              // ���������� �������� ����� ������� WindowsApi GetFileSize
              BEGIN_MESSAGE(TestGetFileSize,47,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetFileSize

              // ���������� �������� ����� ������� WindowsApi GetFileTime
              BEGIN_MESSAGE(TestGetFileTime,44,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetFileTime

              // ���������� �������� ����� ������� WindowsApi MoveFileA
              BEGIN_MESSAGE(TestMoveFileA,38,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ����� � ������� ����������
                ARGUMENT(0, string, PathDst);
                // ���� � ������������� �����
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // TestMoveFileA

              // ���������� �������� ����� ������� WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(TestPathCanonicalizeA,5,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ������������� ����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathCanonicalizeA

              // ���������� �������� ����� ������� WindowsApi PathCombineA
              BEGIN_MESSAGE(TestPathCombineA,2,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ������
                ARGUMENT(0, string, PathIn);
                // ���������� ������
                ARGUMENT(1, string, PathMore);
              END_MESSAGE(); // TestPathCombineA

              // ���������� �������� ����� ������� WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(TestPathFindFileNameA,8,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathFindFileNameA

              // ���������� �������� ����� ������� WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(TestPathRemoveFileSpecA,11,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ������ �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathRemoveFileSpecA

              // ���������� �������� ����� ������� WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(TestRemoveDirectoryA,35,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � ��������� �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestRemoveDirectoryA

              // ���������� �������� ����� ������� WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(TestSHCreateDirectoryExA,66,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���� � �����
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestSHCreateDirectoryExA

              // ���������� �������� ����� ������� WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(TestSetFileAttributesA,20,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����� ��� � WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // ���� � �����
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // TestSetFileAttributesA

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// ����������� ����� ��������� ������������ ������������ ������ � �������� �� ����������� �������
                /// </summary>
                /// <param name="Attributes">������������ ��������</param>
                /// <param name="ParamInt">�������� ��������</param>
                /// <param name="ParamStr">��������� ��������</param>
                /// <param name="Result">��������� ������ �������, �� �� ��������� �����</param>
                /// <param name="TimeCreated">���� ��������</param>
                /// <param name="TimeModified">���� ���������</param>
                void CompletedTest(WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, string paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0))) const
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi CopyFileA
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void CopyFileAIntercepted(const string & pathDst, const string & pathSrc) const
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi CreateDirectoryA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void CreateDirectoryAIntercepted(const string & path) const
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi CreateFileA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void CreateFileAIntercepted(const string & path) const
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi DeleteFileA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void DeleteFileAIntercepted(const string & path) const
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fclose
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void FcloseIntercepted(int handle) const
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi Feof
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void FeofIntercepted(int handle) const
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi FindClose
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void FindCloseIntercepted(int handle) const
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi FindFirstFileA
                /// </summary>
                /// <param name="mask">����� ������</param>
                void FindFirstFileAIntercepted(const string & mask) const
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi FindFirstFileExA
                /// </summary>
                /// <param name="mask">����� ������</param>
                void FindFirstFileExAIntercepted(const string & mask) const
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi FindNextFileA
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void FindNextFileAIntercepted(int handle) const
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fopen_s
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void Fopen_sIntercepted(const string & mode, const string & path) const
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fread
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="handle">�������� ������������</param>
                /// <param name="itemSize">������ ��������</param>
                void FreadIntercepted(int count, int handle, int itemSize) const
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi GetFileAttributesA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void GetFileAttributesAIntercepted(const string & path) const
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi GetFileSize
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void GetFileSizeIntercepted(int handle) const
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi GetFileTime
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void GetFileTimeIntercepted(int handle) const
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi MoveFileA
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void MoveFileAIntercepted(const string & pathDst, const string & pathSrc) const
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����� �� ��������� � ��������� ������ ������� WindowsApi PathCanonicalizeA
                /// </summary>
                /// <param name="path">������������� ����</param>
                void PathCanonicalizeAIntercepted(const string & path) const
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� PathCombineA
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void PathCombineAIntercepted(const string & pathIn, const string & pathMore) const
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����� �� ��������� � ��������� ������ ������� WindowsApi PathFindFileNameA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void PathFindFileNameAIntercepted(const string & path) const
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ����� �� ��������� � ��������� ������ ������� WindowsApi PathRemoveFileSpecA
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void PathRemoveFileSpecAIntercepted(const string & path) const
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi RemoveDirectoryA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RemoveDirectoryAIntercepted(const string & path) const
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi SHCreateDirectoryExA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SHCreateDirectoryExAIntercepted(const string & path) const
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� WindowsApi SetFileAttributesA
                /// </summary>
                /// <param name="attributes">�������� �����</param>
                /// <param name="path">���� � �����</param>
                void SetFileAttributesAIntercepted(WinApiAttr attributes, const string & path) const
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi CopyFileA
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ��������</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void TestCopyFileA(const string & pathDst, const string & pathSrc) const
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi CreateDirectoryA
                /// </summary>
                /// <param name="path">���� � ����������� �����</param>
                void TestCreateDirectoryA(const string & path) const
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi CreateFileA
                /// </summary>
                /// <param name="path">���� � ������������ �����</param>
                void TestCreateFileA(const string & path) const
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi DeleteFileA
                /// </summary>
                /// <param name="path">���� � ���������� �����</param>
                void TestDeleteFileA(const string & path) const
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� fclose
                /// </summary>
                void TestFclose() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFclose);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� feof
                /// </summary>
                void TestFeof() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFeof);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi FindClose
                /// </summary>
                void TestFindClose() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindClose);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi FindFirstFileA
                /// </summary>
                /// <param name="mask">����� ������</param>
                void TestFindFirstFileA(const string & mask) const
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi FindFirstFileExA
                /// </summary>
                /// <param name="mask">����� ������</param>
                void TestFindFirstFileExA(const string & mask) const
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi FindNextFileA
                /// </summary>
                void TestFindNextFileA() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindNextFileA);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� fopen_s
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void TestFopen_s(const string & mode, const string & path) const
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� fread
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="ItemSize">������ ��������</param>
                void TestFread(int count, int itemSize = 1) const
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi GetFileAttributesA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void TestGetFileAttributesA(const string & path) const
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi GetFileSize
                /// </summary>
                void TestGetFileSize() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileSize);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi GetFileTime
                /// </summary>
                void TestGetFileTime() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileTime);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi MoveFileA
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ����������</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void TestMoveFileA(const string & pathDst, const string & pathSrc) const
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi PathCanonicalizeA
                /// </summary>
                /// <param name="path">������������� ����</param>
                void TestPathCanonicalizeA(const string & path) const
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi PathCombineA
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void TestPathCombineA(const string & pathIn, const string & pathMore) const
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi PathFindFileNameA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void TestPathFindFileNameA(const string & path) const
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi PathRemoveFileSpecA
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void TestPathRemoveFileSpecA(const string & path) const
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi RemoveDirectoryA
                /// </summary>
                /// <param name="path">���� � ��������� �����</param>
                void TestRemoveDirectoryA(const string & path) const
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi SHCreateDirectoryExA
                /// </summary>
                /// <param name="path">���� � �����</param>
                void TestSHCreateDirectoryExA(const string & path) const
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� WindowsApi SetFileAttributesA
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="path">���� � �����</param>
                void TestSetFileAttributesA(WinApiAttr attributes, const string & path) const
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// �������� ������� CompletedTest �� ������
                /// </summary>
                /// <param name="attributes">������������ ��������</param>
                /// <param name="paramInt">�������� ��������</param>
                /// <param name="paramStr">��������� ��������</param>
                /// <param name="result">��������� ������ �������, �� �� ��������� �����</param>
                /// <param name="timeCreated">���� ��������</param>
                /// <param name="timeModified">���� ���������</param>
                void SendCompletedTest(address target, WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, const string & paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)))
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CompletedTest ������ ����
                /// </summary>
                /// <param name="attributes">������������ ��������</param>
                /// <param name="paramInt">�������� ��������</param>
                /// <param name="paramStr">��������� ��������</param>
                /// <param name="result">��������� ������ �������, �� �� ��������� �����</param>
                /// <param name="timeCreated">���� ��������</param>
                /// <param name="timeModified">���� ���������</param>
                void RaiseCompletedTest(WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, const string & paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)))
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CopyFileAIntercepted �� ������
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void SendCopyFileAIntercepted(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CopyFileAIntercepted ������ ����
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void RaiseCopyFileAIntercepted(const string & pathDst, const string & pathSrc)
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CopyFileA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendCopyFileA_Answer(address target, bool result)
                {
                  G1::CopyFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CopyFileA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseCopyFileA_Answer(bool result)
                {
                  G1::CopyFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateDirectoryAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendCreateDirectoryAIntercepted(address target, const string & path)
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateDirectoryAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseCreateDirectoryAIntercepted(const string & path)
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateDirectoryA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendCreateDirectoryA_Answer(address target, bool result)
                {
                  G1::CreateDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateDirectoryA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseCreateDirectoryA_Answer(bool result)
                {
                  G1::CreateDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateFileAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendCreateFileAIntercepted(address target, const string & path)
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateFileAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseCreateFileAIntercepted(const string & path)
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� CreateFileA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendCreateFileA_Answer(address target, bool result)
                {
                  G1::CreateFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� CreateFileA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseCreateFileA_Answer(bool result)
                {
                  G1::CreateFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� DeleteFileAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendDeleteFileAIntercepted(address target, const string & path)
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� DeleteFileAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseDeleteFileAIntercepted(const string & path)
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� DeleteFileA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendDeleteFileA_Answer(address target, bool result)
                {
                  G1::DeleteFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� DeleteFileA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseDeleteFileA_Answer(bool result)
                {
                  G1::DeleteFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FcloseAnswer �� ������
                /// </summary>
                /// <param name="result">true - ���� ������� ������, false - ������</param>
                void SendFcloseAnswer(address target, bool result)
                {
                  G1::FcloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FcloseAnswer ������ ����
                /// </summary>
                /// <param name="result">true - ���� ������� ������, false - ������</param>
                void RaiseFcloseAnswer(bool result)
                {
                  G1::FcloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FcloseIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendFcloseIntercepted(address target, int handle)
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FcloseIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseFcloseIntercepted(int handle)
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FeofAnswer �� ������
                /// </summary>
                /// <param name="result">true - ����� �����, false - ��� ���</param>
                void SendFeofAnswer(address target, bool result)
                {
                  G1::FeofAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FeofAnswer ������ ����
                /// </summary>
                /// <param name="result">true - ����� �����, false - ��� ���</param>
                void RaiseFeofAnswer(bool result)
                {
                  G1::FeofAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FeofIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendFeofIntercepted(address target, int handle)
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FeofIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseFeofIntercepted(int handle)
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindCloseAnswer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendFindCloseAnswer(address target, bool result)
                {
                  G1::FindCloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindCloseAnswer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseFindCloseAnswer(bool result)
                {
                  G1::FindCloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindCloseIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendFindCloseIntercepted(address target, int handle)
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindCloseIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseFindCloseIntercepted(int handle)
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindFirstFileAIntercepted �� ������
                /// </summary>
                /// <param name="mask">����� ������</param>
                void SendFindFirstFileAIntercepted(address target, const string & mask)
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindFirstFileAIntercepted ������ ����
                /// </summary>
                /// <param name="mask">����� ������</param>
                void RaiseFindFirstFileAIntercepted(const string & mask)
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindFirstFileA_Answer �� ������
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">false - ������� ������ INVALID_ARGUMENT, true - �������� ����������� �������</param>
                void SendFindFirstFileA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindFirstFileA_Answer ������ ����
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">false - ������� ������ INVALID_ARGUMENT, true - �������� ����������� �������</param>
                void RaiseFindFirstFileA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindFirstFileExAIntercepted �� ������
                /// </summary>
                /// <param name="mask">����� ������</param>
                void SendFindFirstFileExAIntercepted(address target, const string & mask)
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindFirstFileExAIntercepted ������ ����
                /// </summary>
                /// <param name="mask">����� ������</param>
                void RaiseFindFirstFileExAIntercepted(const string & mask)
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindFirstFileExA_Answer �� ������
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">false - ������� ������ INVALID_ARGUMENT, true - �������� ����������� �������</param>
                void SendFindFirstFileExA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileExA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindFirstFileExA_Answer ������ ����
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">false - ������� ������ INVALID_ARGUMENT, true - �������� ����������� �������</param>
                void RaiseFindFirstFileExA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileExA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindNextFileAIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendFindNextFileAIntercepted(address target, int handle)
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindNextFileAIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseFindNextFileAIntercepted(int handle)
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FindNextFileA_Answer �� ������
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">��������� ������ �������</param>
                void SendFindNextFileA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindNextFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FindNextFileA_Answer ������ ����
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="filename">�������� ���������� �����</param>
                /// <param name="result">��������� ������ �������</param>
                void RaiseFindNextFileA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindNextFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� Fopen_sAnswer �� ������
                /// </summary>
                /// <param name="errno">���������</param>
                void SendFopen_sAnswer(address target, int errno)
                {
                  G1::Fopen_sAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� Fopen_sAnswer ������ ����
                /// </summary>
                /// <param name="errno">���������</param>
                void RaiseFopen_sAnswer(int errno)
                {
                  G1::Fopen_sAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� Fopen_sIntercepted �� ������
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void SendFopen_sIntercepted(address target, const string & mode, const string & path)
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� Fopen_sIntercepted ������ ����
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void RaiseFopen_sIntercepted(const string & mode, const string & path)
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FreadAnswer �� ������
                /// </summary>
                /// <param name="buffer">����������� �������</param>
                void SendFreadAnswer(address target, const string & buffer)
                {
                  G1::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FreadAnswer ������ ����
                /// </summary>
                /// <param name="buffer">����������� �������</param>
                void RaiseFreadAnswer(const string & buffer)
                {
                  G1::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FreadIntercepted �� ������
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="handle">�������� ������������</param>
                /// <param name="itemSize">������ ��������</param>
                void SendFreadIntercepted(address target, int count, int handle, int itemSize)
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FreadIntercepted ������ ����
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="handle">�������� ������������</param>
                /// <param name="itemSize">������ ��������</param>
                void RaiseFreadIntercepted(int count, int handle, int itemSize)
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileAttributesAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendGetFileAttributesAIntercepted(address target, const string & path)
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileAttributesAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseGetFileAttributesAIntercepted(const string & path)
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileAttributesA_Answer �� ������
                /// </summary>
                /// <param name="attributes">�������� �����</param>
                void SendGetFileAttributesA_Answer(address target, WinApiAttr attributes)
                {
                  G1::GetFileAttributesA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileAttributesA_Answer ������ ����
                /// </summary>
                /// <param name="attributes">�������� �����</param>
                void RaiseGetFileAttributesA_Answer(WinApiAttr attributes)
                {
                  G1::GetFileAttributesA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileSizeAnswer �� ������
                /// </summary>
                /// <param name="size">������ �����</param>
                void SendGetFileSizeAnswer(address target, int size)
                {
                  G1::GetFileSizeAnswer cmd;
                  cmd.SetSize(size);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileSizeAnswer ������ ����
                /// </summary>
                /// <param name="size">������ �����</param>
                void RaiseGetFileSizeAnswer(int size)
                {
                  G1::GetFileSizeAnswer cmd;
                  cmd.SetSize(size);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileSizeIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendGetFileSizeIntercepted(address target, int handle)
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileSizeIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseGetFileSizeIntercepted(int handle)
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileTimeAnswer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                /// <param name="timeCreate">���� �������� �����</param>
                /// <param name="timeModify">���� ��������� �����</param>
                void SendGetFileTimeAnswer(address target, bool result, timestamp_t timeCreate, timestamp_t timeModify)
                {
                  G1::GetFileTimeAnswer cmd;
                  cmd.SetResult(result);
                  cmd.SetTimeCreate(timeCreate);
                  cmd.SetTimeModify(timeModify);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileTimeAnswer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                /// <param name="timeCreate">���� �������� �����</param>
                /// <param name="timeModify">���� ��������� �����</param>
                void RaiseGetFileTimeAnswer(bool result, timestamp_t timeCreate, timestamp_t timeModify)
                {
                  G1::GetFileTimeAnswer cmd;
                  cmd.SetResult(result);
                  cmd.SetTimeCreate(timeCreate);
                  cmd.SetTimeModify(timeModify);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetFileTimeIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendGetFileTimeIntercepted(address target, int handle)
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetFileTimeIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseGetFileTimeIntercepted(int handle)
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� MoveFileAIntercepted �� ������
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void SendMoveFileAIntercepted(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� MoveFileAIntercepted ������ ����
                /// </summary>
                /// <param name="pathDst">���� � �������� �����</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void RaiseMoveFileAIntercepted(const string & pathDst, const string & pathSrc)
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� MoveFileA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendMoveFileA_Answer(address target, bool result)
                {
                  G1::MoveFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� MoveFileA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseMoveFileA_Answer(bool result)
                {
                  G1::MoveFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathCanonicalizeAIntercepted �� ������
                /// </summary>
                /// <param name="path">������������� ����</param>
                void SendPathCanonicalizeAIntercepted(address target, const string & path)
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathCanonicalizeAIntercepted ������ ����
                /// </summary>
                /// <param name="path">������������� ����</param>
                void RaisePathCanonicalizeAIntercepted(const string & path)
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathCanonicalizeA_Answer �� ������
                /// </summary>
                /// <param name="path">�������������� ����</param>
                /// <param name="result">true - �������, false - ���������</param>
                void SendPathCanonicalizeA_Answer(address target, const string & path, bool result)
                {
                  G1::PathCanonicalizeA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathCanonicalizeA_Answer ������ ����
                /// </summary>
                /// <param name="path">�������������� ����</param>
                /// <param name="result">true - �������, false - ���������</param>
                void RaisePathCanonicalizeA_Answer(const string & path, bool result)
                {
                  G1::PathCanonicalizeA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathCombineAIntercepted �� ������
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void SendPathCombineAIntercepted(address target, const string & pathIn, const string & pathMore)
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathCombineAIntercepted ������ ����
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void RaisePathCombineAIntercepted(const string & pathIn, const string & pathMore)
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathCombineA_Answer �� ������
                /// </summary>
                /// <param name="path">�������� ����</param>
                void SendPathCombineA_Answer(address target, const string & path)
                {
                  G1::PathCombineA_Answer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathCombineA_Answer ������ ����
                /// </summary>
                /// <param name="path">�������� ����</param>
                void RaisePathCombineA_Answer(const string & path)
                {
                  G1::PathCombineA_Answer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathFindFileNameAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendPathFindFileNameAIntercepted(address target, const string & path)
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathFindFileNameAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaisePathFindFileNameAIntercepted(const string & path)
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathFindFileNameA_Answer �� ������
                /// </summary>
                /// <param name="filename">��� �����</param>
                void SendPathFindFileNameA_Answer(address target, const string & filename)
                {
                  G1::PathFindFileNameA_Answer cmd;
                  cmd.SetFilename(filename);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathFindFileNameA_Answer ������ ����
                /// </summary>
                /// <param name="filename">��� �����</param>
                void RaisePathFindFileNameA_Answer(const string & filename)
                {
                  G1::PathFindFileNameA_Answer cmd;
                  cmd.SetFilename(filename);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathRemoveFileSpecAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void SendPathRemoveFileSpecAIntercepted(address target, const string & path)
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathRemoveFileSpecAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void RaisePathRemoveFileSpecAIntercepted(const string & path)
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� PathRemoveFileSpecA_Answer �� ������
                /// </summary>
                /// <param name="path">���� ��� ����� �����</param>
                /// <param name="result">��������� ������ �������</param>
                void SendPathRemoveFileSpecA_Answer(address target, const string & path, bool result)
                {
                  G1::PathRemoveFileSpecA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� PathRemoveFileSpecA_Answer ������ ����
                /// </summary>
                /// <param name="path">���� ��� ����� �����</param>
                /// <param name="result">��������� ������ �������</param>
                void RaisePathRemoveFileSpecA_Answer(const string & path, bool result)
                {
                  G1::PathRemoveFileSpecA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� RemoveDirectoryAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendRemoveDirectoryAIntercepted(address target, const string & path)
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� RemoveDirectoryAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseRemoveDirectoryAIntercepted(const string & path)
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� RemoveDirectoryA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendRemoveDirectoryA_Answer(address target, bool result)
                {
                  G1::RemoveDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� RemoveDirectoryA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseRemoveDirectoryA_Answer(bool result)
                {
                  G1::RemoveDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SHCreateDirectoryExAIntercepted �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendSHCreateDirectoryExAIntercepted(address target, const string & path)
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SHCreateDirectoryExAIntercepted ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseSHCreateDirectoryExAIntercepted(const string & path)
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SHCreateDirectoryExA_Answer �� ������
                /// </summary>
                /// <param name="code">��� ������ (��� ��, ��� � ��� GetLastError)</param>
                void SendSHCreateDirectoryExA_Answer(address target, int code)
                {
                  G1::SHCreateDirectoryExA_Answer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SHCreateDirectoryExA_Answer ������ ����
                /// </summary>
                /// <param name="code">��� ������ (��� ��, ��� � ��� GetLastError)</param>
                void RaiseSHCreateDirectoryExA_Answer(int code)
                {
                  G1::SHCreateDirectoryExA_Answer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetFileAttributesAIntercepted �� ������
                /// </summary>
                /// <param name="attributes">�������� �����</param>
                /// <param name="path">���� � �����</param>
                void SendSetFileAttributesAIntercepted(address target, WinApiAttr attributes, const string & path)
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetFileAttributesAIntercepted ������ ����
                /// </summary>
                /// <param name="attributes">�������� �����</param>
                /// <param name="path">���� � �����</param>
                void RaiseSetFileAttributesAIntercepted(WinApiAttr attributes, const string & path)
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetFileAttributesA_Answer �� ������
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void SendSetFileAttributesA_Answer(address target, bool result)
                {
                  G1::SetFileAttributesA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetFileAttributesA_Answer ������ ����
                /// </summary>
                /// <param name="result">��������� ������ �������</param>
                void RaiseSetFileAttributesA_Answer(bool result)
                {
                  G1::SetFileAttributesA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestCopyFileA �� ������
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ��������</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void SendTestCopyFileA(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestCopyFileA ������ ����
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ��������</param>
                /// <param name="pathSrc">���� � ����������� �����</param>
                void RaiseTestCopyFileA(const string & pathDst, const string & pathSrc)
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestCreateDirectoryA �� ������
                /// </summary>
                /// <param name="path">���� � ����������� �����</param>
                void SendTestCreateDirectoryA(address target, const string & path)
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestCreateDirectoryA ������ ����
                /// </summary>
                /// <param name="path">���� � ����������� �����</param>
                void RaiseTestCreateDirectoryA(const string & path)
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestCreateFileA �� ������
                /// </summary>
                /// <param name="path">���� � ������������ �����</param>
                void SendTestCreateFileA(address target, const string & path)
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestCreateFileA ������ ����
                /// </summary>
                /// <param name="path">���� � ������������ �����</param>
                void RaiseTestCreateFileA(const string & path)
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestDeleteFileA �� ������
                /// </summary>
                /// <param name="path">���� � ���������� �����</param>
                void SendTestDeleteFileA(address target, const string & path)
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestDeleteFileA ������ ����
                /// </summary>
                /// <param name="path">���� � ���������� �����</param>
                void RaiseTestDeleteFileA(const string & path)
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFclose �� ������
                /// </summary>
                void SendTestFclose(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFclose);
                }
                /// <summary> 
                /// �������� ������� TestFclose ������ ����
                /// </summary>
                void RaiseTestFclose()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFclose);
                }
                
                /// <summary> 
                /// �������� ������� TestFeof �� ������
                /// </summary>
                void SendTestFeof(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFeof);
                }
                /// <summary> 
                /// �������� ������� TestFeof ������ ����
                /// </summary>
                void RaiseTestFeof()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFeof);
                }
                
                /// <summary> 
                /// �������� ������� TestFindClose �� ������
                /// </summary>
                void SendTestFindClose(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFindClose);
                }
                /// <summary> 
                /// �������� ������� TestFindClose ������ ����
                /// </summary>
                void RaiseTestFindClose()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindClose);
                }
                
                /// <summary> 
                /// �������� ������� TestFindFirstFileA �� ������
                /// </summary>
                /// <param name="mask">����� ������</param>
                void SendTestFindFirstFileA(address target, const string & mask)
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFindFirstFileA ������ ����
                /// </summary>
                /// <param name="mask">����� ������</param>
                void RaiseTestFindFirstFileA(const string & mask)
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFindFirstFileExA �� ������
                /// </summary>
                /// <param name="mask">����� ������</param>
                void SendTestFindFirstFileExA(address target, const string & mask)
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFindFirstFileExA ������ ����
                /// </summary>
                /// <param name="mask">����� ������</param>
                void RaiseTestFindFirstFileExA(const string & mask)
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFindNextFileA �� ������
                /// </summary>
                void SendTestFindNextFileA(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFindNextFileA);
                }
                /// <summary> 
                /// �������� ������� TestFindNextFileA ������ ����
                /// </summary>
                void RaiseTestFindNextFileA()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindNextFileA);
                }
                
                /// <summary> 
                /// �������� ������� TestFopen_s �� ������
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void SendTestFopen_s(address target, const string & mode, const string & path)
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFopen_s ������ ����
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="path">���� � �����</param>
                void RaiseTestFopen_s(const string & mode, const string & path)
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFread �� ������
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="itemSize">������ ��������</param>
                void SendTestFread(address target, int count, int itemSize = 1)
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFread ������ ����
                /// </summary>
                /// <param name="count">���������� ���������</param>
                /// <param name="itemSize">������ ��������</param>
                void RaiseTestFread(int count, int itemSize = 1)
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestGetFileAttributesA �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendTestGetFileAttributesA(address target, const string & path)
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestGetFileAttributesA ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseTestGetFileAttributesA(const string & path)
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestGetFileSize �� ������
                /// </summary>
                void SendTestGetFileSize(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestGetFileSize);
                }
                /// <summary> 
                /// �������� ������� TestGetFileSize ������ ����
                /// </summary>
                void RaiseTestGetFileSize()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileSize);
                }
                
                /// <summary> 
                /// �������� ������� TestGetFileTime �� ������
                /// </summary>
                void SendTestGetFileTime(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestGetFileTime);
                }
                /// <summary> 
                /// �������� ������� TestGetFileTime ������ ����
                /// </summary>
                void RaiseTestGetFileTime()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileTime);
                }
                
                /// <summary> 
                /// �������� ������� TestMoveFileA �� ������
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ����������</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void SendTestMoveFileA(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestMoveFileA ������ ����
                /// </summary>
                /// <param name="pathDst">���� � �����, � ������� ����������</param>
                /// <param name="pathSrc">���� � ������������� �����</param>
                void RaiseTestMoveFileA(const string & pathDst, const string & pathSrc)
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestPathCanonicalizeA �� ������
                /// </summary>
                /// <param name="path">������������� ����</param>
                void SendTestPathCanonicalizeA(address target, const string & path)
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestPathCanonicalizeA ������ ����
                /// </summary>
                /// <param name="path">������������� ����</param>
                void RaiseTestPathCanonicalizeA(const string & path)
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestPathCombineA �� ������
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void SendTestPathCombineA(address target, const string & pathIn, const string & pathMore)
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestPathCombineA ������ ����
                /// </summary>
                /// <param name="pathIn">�������� ������</param>
                /// <param name="pathMore">���������� ������</param>
                void RaiseTestPathCombineA(const string & pathIn, const string & pathMore)
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestPathFindFileNameA �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendTestPathFindFileNameA(address target, const string & path)
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestPathFindFileNameA ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseTestPathFindFileNameA(const string & path)
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestPathRemoveFileSpecA �� ������
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void SendTestPathRemoveFileSpecA(address target, const string & path)
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestPathRemoveFileSpecA ������ ����
                /// </summary>
                /// <param name="path">���� � ������ �����</param>
                void RaiseTestPathRemoveFileSpecA(const string & path)
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestRemoveDirectoryA �� ������
                /// </summary>
                /// <param name="path">���� � ��������� �����</param>
                void SendTestRemoveDirectoryA(address target, const string & path)
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestRemoveDirectoryA ������ ����
                /// </summary>
                /// <param name="path">���� � ��������� �����</param>
                void RaiseTestRemoveDirectoryA(const string & path)
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestSHCreateDirectoryExA �� ������
                /// </summary>
                /// <param name="path">���� � �����</param>
                void SendTestSHCreateDirectoryExA(address target, const string & path)
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestSHCreateDirectoryExA ������ ����
                /// </summary>
                /// <param name="path">���� � �����</param>
                void RaiseTestSHCreateDirectoryExA(const string & path)
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestSetFileAttributesA �� ������
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="path">���� � �����</param>
                void SendTestSetFileAttributesA(address target, WinApiAttr attributes, const string & path)
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestSetFileAttributesA ������ ����
                /// </summary>
                /// <param name="attributes">�������� ����� ��� � WinAPI</param>
                /// <param name="path">���� � �����</param>
                void RaiseTestSetFileAttributesA(WinApiAttr attributes, const string & path)
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            

            BEGIN_PROTOCOL(11, 2)
              
              #pragma region Enumerations
              /// <summary> 
              /// ����������� ������ ��� ������ � �������� ��������
              /// </summary>
              enum class FileSystemApiErrors
              {
                ErrorAccessDenied = 5, // ���� ����������
                ErrorCurrentDirectory = 16, // ����� �� ����� ���� �������
                ErrorDevNotExist = 55, // ���������� ����������
                ErrorDiskFull = 112, // ������������ ���������� ����� �� �����
                ErrorFileNotFound = 2, // ���� �� ������
                ErrorHandleDiskFull = 39, // ���� ����������
                ErrorInvalidDrive = 15, // ���� �� ����������
                ErrorNetworkAccessDenied = 65, // ������� ���� ����������
                ErrorNoMoreFiles = 18, // ������ ��� ������, ��������������� �������� �������
                ErrorPathNotFound = 3 // ���� � ����� �� ������
              };
              
              /// <summary> 
              /// ����� ������
              /// </summary>
              enum class ReadMode
              {
                ReadLine = 2, // - ������ ���������
                ReadWord = 1 // - ������ �����
              };
              
              /// <summary>
              /// ��������� ������������ �������� ��� ������������� ���� FileSystemApiErrors
              /// </summary>
              inline bool IsValidFileSystemApiErrorsValue(const int value)
              {
                return ((value >= 2)&&(value < 4)) || ((value >= 5)&&(value < 6)) || ((value >= 15)&&(value < 17)) || ((value >= 18)&&(value < 19)) || ((value >= 39)&&(value < 40)) || ((value >= 55)&&(value < 56)) || ((value >= 65)&&(value < 66)) || ((value >= 112)&&(value < 113));
              }
              
              /// <summary>
              /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� FileSystemApiErrors
              /// </summary>
              inline FileSystemApiErrors ConvertToFileSystemApiErrors(const int value)
              {
                switch (value)
                {
                  case 5:
                    return FileSystemApiErrors::ErrorAccessDenied;
                  case 16:
                    return FileSystemApiErrors::ErrorCurrentDirectory;
                  case 55:
                    return FileSystemApiErrors::ErrorDevNotExist;
                  case 112:
                    return FileSystemApiErrors::ErrorDiskFull;
                  case 2:
                    return FileSystemApiErrors::ErrorFileNotFound;
                  case 39:
                    return FileSystemApiErrors::ErrorHandleDiskFull;
                  case 15:
                    return FileSystemApiErrors::ErrorInvalidDrive;
                  case 65:
                    return FileSystemApiErrors::ErrorNetworkAccessDenied;
                  case 18:
                    return FileSystemApiErrors::ErrorNoMoreFiles;
                  case 3:
                    return FileSystemApiErrors::ErrorPathNotFound;
                  default: throw KernelException("���������� ������������� �������� �������� %d � ���� FileSystemApiErrors", value);
                  }
              }
              
              /// <summary>
              /// ��������� ������������ �������� ��� ������������� ���� ReadMode
              /// </summary>
              inline bool IsValidReadModeValue(const int value)
              {
                return ((value >= 1)&&(value < 3));
              }
              
              /// <summary>
              /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� ReadMode
              /// </summary>
              inline ReadMode ConvertToReadMode(const int value)
              {
                switch (value)
                {
                  case 2:
                    return ReadMode::ReadLine;
                  case 1:
                    return ReadMode::ReadWord;
                  default: throw KernelException("���������� ������������� �������� �������� %d � ���� ReadMode", value);
                  }
              }
              
              #pragma endregion
              
              #pragma region Flags
              
              /// <summary> 
              /// ��������� WinAPI ��� �������� ���������
              /// </summary>
              enum class WinApiAttr
              {
                Archive = 32, //��������
                Folder = 16, //�����
                Hidden = 2, //�������
                Normal = 128, //�� ����� ������ ���������
                ReadOnly = 1, //������ ������
                System = 4 //���������
              };
              
              /// <summary>
              /// ��������, ����������� ����������� ����� ��� ������ WinApiAttr
              /// </summary>
              inline WinApiAttr operator|(WinApiAttr a, WinApiAttr b)
              {
                return static_cast<WinApiAttr>(static_cast<int>(a), static_cast<int>(b));
              }
              
              /// <summary>
              /// ��������� ��������� ����������� �� ����� mask � WinApiAttr
              /// </summary>
              /// <param name="variable">����������</param>
              /// <param name="mask">����� ��� ��������</param>
              inline bool IsFlagSet(WinApiAttr variable, WinApiAttr mask)
              {
                int m = static_cast<int>(mask);
                return (static_cast<int>(variable) & m)==m;
              }
              
              /// <summary>
              /// ��������� ������������ �������� ��� ����� WinApiAttr
              /// </summary>
              /// <param name="value">�������� ��� ��������</param>
              inline bool IsValidWinApiAttrValue(const int value)
              {
                return value <= 183;
              }
              #pragma endregion
              
              //���������
              #pragma region Messages and wrappers
              
              //���������
              // ����� �� ��������� � ��������� ������ ������� fflush
              BEGIN_MESSAGE(FFlushAnswer,86,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� ������
                ARGUMENT(0, int, Error);
              END_MESSAGE(); // FFlushAnswer

              // ��������� � ��������� ������ ������� fflush
              BEGIN_MESSAGE(FFlushIntercepted,85,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FFlushIntercepted

              // ����� �� ��������� � ��������� ������ ������� fseek
              BEGIN_MESSAGE(FSeekAnswer,71,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���������
                ARGUMENT(0, int, Errno);
              END_MESSAGE(); // FSeekAnswer

              // ��������� � ��������� ������ ������� fseek
              BEGIN_MESSAGE(FSeekIntercepted,70,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, FileHandle);
                // ���������� ������ �� Origin
                ARGUMENT(1, int, Offset);
                // ��������� ������� ���������
                ARGUMENT(2, int, Origin);
              END_MESSAGE(); // FSeekIntercepted

              // ����� �� ��������� � ��������� ������ ������� ftell
              BEGIN_MESSAGE(FTellAnswer,77,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ������ �����
                ARGUMENT(0, int, FilePosition);
              END_MESSAGE(); // FTellAnswer

              // ��������� � ��������� ������ ������� ftell
              BEGIN_MESSAGE(FTellIntercepted,76,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, FileHandle);
              END_MESSAGE(); // FTellIntercepted

              // ����� �� ��������� � ��������� ������ ������� fwrite
              BEGIN_MESSAGE(FWriteAnswer,83,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ��������� ���������
                ARGUMENT(0, int, BytesWritten);
              END_MESSAGE(); // FWriteAnswer

              // ��������� � ��������� ������ ������� fwrite
              BEGIN_MESSAGE(FWriteIntercepted,82,4)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ���������
                ARGUMENT(0, int, Count);
                // ������ ��� ������
                ARGUMENT(1, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(1, data, len);
                }
                // �������� ����������
                ARGUMENT(2, int, Handle);
                // ������ ��������
                ARGUMENT(3, int, ItemSize);
              END_MESSAGE(); // FWriteIntercepted

              // ����� �� ��������� � ��������� ������ ������� fread
              BEGIN_MESSAGE(FreadAnswer,58,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����������� �������
                ARGUMENT(0, ByteVector, Buffer);
                void SetBuffer(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
              END_MESSAGE(); // FreadAnswer

              // ����� �� ������������� ����� ������� GetCurrentDirectory
              BEGIN_MESSAGE(GetCurrentDirectoryAnswer,95,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ���� � ������� ������� ����������
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // GetCurrentDirectoryAnswer

              // ���������� ����� ������� GetCurrentDirectory
              BEGIN_MESSAGE(GetCurrentDirectoryIntercepted,94,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // GetCurrentDirectoryIntercepted

              // ����� �� ��������� � ��������� ������ ������� geterrno
              BEGIN_MESSAGE(GetErrNoAnswer,90,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� ������
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // GetErrNoAnswer

              // ��������� � ��������� ������ ������� geterrno
              BEGIN_MESSAGE(GetErrNoIntercepted,89,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // GetErrNoIntercepted

              // ����� �� ��������� � ��������� ������ ������� read
              BEGIN_MESSAGE(ReadAnswer,92,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����������� �����
                ARGUMENT(0, string, Text);
              END_MESSAGE(); // ReadAnswer

              // ��������� � ��������� ������ ������� read
              BEGIN_MESSAGE(ReadIntercepted,91,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
                // ����� ������
                ENUM(1, ReadMode, Mode);
              END_MESSAGE(); // ReadIntercepted

              // ����� �� ��������� � ��������� ������ ������� rewind
              BEGIN_MESSAGE(RewindAnswer,80,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // RewindAnswer

              // ��������� � ��������� ������ ������� rewind
              BEGIN_MESSAGE(RewindIntercepted,79,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // RewindIntercepted

              // ������������
              BEGIN_MESSAGE(SetCurrentDirectoryAnswer,98,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� ����������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetCurrentDirectoryAnswer

              // ������������
              BEGIN_MESSAGE(SetCurrentDirectoryIntercepted,97,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ���� ��� ��������� ������� ������� ����������
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // SetCurrentDirectoryIntercepted

              // ���������� �������� ����� fflush
              BEGIN_MESSAGE(TestFFlush,84,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �������� ����������
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // TestFFlush

              // ���������� �������� ����� ������� fseek
              BEGIN_MESSAGE(TestFSeek,69,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ���������� ������ �� Origin
                ARGUMENT(0, int, Offset);
                // ��������� ������� ���������
                ARGUMENT(1, int, Origin);
              END_MESSAGE(); // TestFSeek

              // ���������� �������� ����� ������� ftell
              BEGIN_MESSAGE(TestFTell,75,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFTell

              // ���������� �������� ����� ������� fwrite
              BEGIN_MESSAGE(TestFWrite,81,3)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ����� ���������
                ARGUMENT(0, int, Count);
                // ������ ��� ������
                ARGUMENT(1, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(1, data, len);
                }
                // ������ ��������
                ARGUMENT(2, int, ItemSize);
              END_MESSAGE(); // TestFWrite

              // ������������ ������ ������� GetCurrentDirectory
              BEGIN_MESSAGE(TestGetCurrentDirectory,93,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetCurrentDirectory

              // ���������� �������� ����� ������� rewind
              BEGIN_MESSAGE(TestRewind,78,0)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestRewind

              // ������������
              BEGIN_MESSAGE(TestSetCurrentDirectory,96,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // - ���� ��� ��������� ������� ������� ����������
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestSetCurrentDirectory

              // ����� �� ��������� � ��������� ������ ������� fsopen
              BEGIN_MESSAGE(_fsopenAnswer,88,1)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // ��� ����������
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // _fsopenAnswer

              // ��������� � ��������� ������ ������� fsopen
              BEGIN_MESSAGE(_fsopenIntercepted,87,2)
                /// <summary>
                /// ������������� ���������
                /// </summary>
                void InitializeMessage()
                {
                }
                // �����
                ARGUMENT(0, string, Mode);
                // ��� ����������� �������������.
                ARGUMENT(1, int, ShFlag);
              END_MESSAGE(); // _fsopenIntercepted

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// ��������� � ��������� ������ ������� fflush
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void FFlushIntercepted(int handle) const
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fseek
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void FSeekIntercepted(int fileHandle, int offset, int origin) const
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� ftell
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                void FTellIntercepted(int fileHandle) const
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fwrite
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="handle">�������� ����������</param>
                /// <param name="itemSize">������ ��������</param>
                void FWriteIntercepted(int count, const ByteVector & data, int handle, int itemSize) const
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� ����� ������� GetCurrentDirectory
                /// </summary>
                void GetCurrentDirectoryIntercepted() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� geterrno
                /// </summary>
                void GetErrNoIntercepted() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetErrNoIntercepted, 2); 
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� read
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                /// <param name="mode">����� ������</param>
                void ReadIntercepted(int handle, ReadMode mode) const
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� rewind
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RewindIntercepted(int handle) const
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ������������
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void SetCurrentDirectoryIntercepted(const string & path) const
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� fflush
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void TestFFlush(int handle) const
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� fseek
                /// </summary>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void TestFSeek(int offset, int origin) const
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� ftell
                /// </summary>
                void TestFTell() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestFTell, 2); 
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� fwrite
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="itemSize">������ ��������</param>
                void TestFWrite(int count, const ByteVector & data, int itemSize) const
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ������������ ������ ������� GetCurrentDirectory
                /// </summary>
                void TestGetCurrentDirectory() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestGetCurrentDirectory, 2); 
                }
                
                /// <summary> 
                /// ���������� �������� ����� ������� rewind
                /// </summary>
                void TestRewind() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestRewind, 2); 
                }
                
                /// <summary> 
                /// ������������
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void TestSetCurrentDirectory(const string & path) const
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// ��������� � ��������� ������ ������� fsopen
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="shFlag">��� ����������� �������������.</param>
                void _fsopenIntercepted(const string & mode, int shFlag) const
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// �������� ������� FFlushAnswer �� ������
                /// </summary>
                /// <param name="error">��� ������</param>
                void SendFFlushAnswer(address target, int error)
                {
                  G2::FFlushAnswer cmd;
                  cmd.SetError(error);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FFlushAnswer ������ ����
                /// </summary>
                /// <param name="error">��� ������</param>
                void RaiseFFlushAnswer(int error)
                {
                  G2::FFlushAnswer cmd;
                  cmd.SetError(error);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FFlushIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendFFlushIntercepted(address target, int handle)
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FFlushIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseFFlushIntercepted(int handle)
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FSeekAnswer �� ������
                /// </summary>
                /// <param name="errno">���������</param>
                void SendFSeekAnswer(address target, int errno)
                {
                  G2::FSeekAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FSeekAnswer ������ ����
                /// </summary>
                /// <param name="errno">���������</param>
                void RaiseFSeekAnswer(int errno)
                {
                  G2::FSeekAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FSeekIntercepted �� ������
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void SendFSeekIntercepted(address target, int fileHandle, int offset, int origin)
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FSeekIntercepted ������ ����
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void RaiseFSeekIntercepted(int fileHandle, int offset, int origin)
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FTellAnswer �� ������
                /// </summary>
                /// <param name="filePosition">������ �����</param>
                void SendFTellAnswer(address target, int filePosition)
                {
                  G2::FTellAnswer cmd;
                  cmd.SetFilePosition(filePosition);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FTellAnswer ������ ����
                /// </summary>
                /// <param name="filePosition">������ �����</param>
                void RaiseFTellAnswer(int filePosition)
                {
                  G2::FTellAnswer cmd;
                  cmd.SetFilePosition(filePosition);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FTellIntercepted �� ������
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                void SendFTellIntercepted(address target, int fileHandle)
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FTellIntercepted ������ ����
                /// </summary>
                /// <param name="fileHandle">�������� ����������</param>
                void RaiseFTellIntercepted(int fileHandle)
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FWriteAnswer �� ������
                /// </summary>
                /// <param name="bytesWritten">����� ��������� ���������</param>
                void SendFWriteAnswer(address target, int bytesWritten)
                {
                  G2::FWriteAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FWriteAnswer ������ ����
                /// </summary>
                /// <param name="bytesWritten">����� ��������� ���������</param>
                void RaiseFWriteAnswer(int bytesWritten)
                {
                  G2::FWriteAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FWriteIntercepted �� ������
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="handle">�������� ����������</param>
                /// <param name="itemSize">������ ��������</param>
                void SendFWriteIntercepted(address target, int count, const ByteVector & data, int handle, int itemSize)
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FWriteIntercepted ������ ����
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="handle">�������� ����������</param>
                /// <param name="itemSize">������ ��������</param>
                void RaiseFWriteIntercepted(int count, const ByteVector & data, int handle, int itemSize)
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� FreadAnswer �� ������
                /// </summary>
                /// <param name="buffer">����������� �������</param>
                void SendFreadAnswer(address target, const ByteVector & buffer)
                {
                  G2::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� FreadAnswer ������ ����
                /// </summary>
                /// <param name="buffer">����������� �������</param>
                void RaiseFreadAnswer(const ByteVector & buffer)
                {
                  G2::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetCurrentDirectoryAnswer �� ������
                /// </summary>
                /// <param name="path">- ���� � ������� ������� ����������</param>
                void SendGetCurrentDirectoryAnswer(address target, const string & path)
                {
                  G2::GetCurrentDirectoryAnswer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetCurrentDirectoryAnswer ������ ����
                /// </summary>
                /// <param name="path">- ���� � ������� ������� ����������</param>
                void RaiseGetCurrentDirectoryAnswer(const string & path)
                {
                  G2::GetCurrentDirectoryAnswer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetCurrentDirectoryIntercepted �� ������
                /// </summary>
                void SendGetCurrentDirectoryIntercepted(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                /// <summary> 
                /// �������� ������� GetCurrentDirectoryIntercepted ������ ����
                /// </summary>
                void RaiseGetCurrentDirectoryIntercepted()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                
                /// <summary> 
                /// �������� ������� GetErrNoAnswer �� ������
                /// </summary>
                /// <param name="code">��� ������</param>
                void SendGetErrNoAnswer(address target, int code)
                {
                  G2::GetErrNoAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� GetErrNoAnswer ������ ����
                /// </summary>
                /// <param name="code">��� ������</param>
                void RaiseGetErrNoAnswer(int code)
                {
                  G2::GetErrNoAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� GetErrNoIntercepted �� ������
                /// </summary>
                void SendGetErrNoIntercepted(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::GetErrNoIntercepted, 2); 
                }
                /// <summary> 
                /// �������� ������� GetErrNoIntercepted ������ ����
                /// </summary>
                void RaiseGetErrNoIntercepted()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetErrNoIntercepted, 2); 
                }
                
                /// <summary> 
                /// �������� ������� ReadAnswer �� ������
                /// </summary>
                /// <param name="text">����������� �����</param>
                void SendReadAnswer(address target, const string & text)
                {
                  G2::ReadAnswer cmd;
                  cmd.SetText(text);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ReadAnswer ������ ����
                /// </summary>
                /// <param name="text">����������� �����</param>
                void RaiseReadAnswer(const string & text)
                {
                  G2::ReadAnswer cmd;
                  cmd.SetText(text);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� ReadIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                /// <param name="mode">����� ������</param>
                void SendReadIntercepted(address target, int handle, ReadMode mode)
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� ReadIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                /// <param name="mode">����� ������</param>
                void RaiseReadIntercepted(int handle, ReadMode mode)
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� RewindAnswer �� ������
                /// </summary>
                void SendRewindAnswer(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::RewindAnswer, 2); 
                }
                /// <summary> 
                /// �������� ������� RewindAnswer ������ ����
                /// </summary>
                void RaiseRewindAnswer()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::RewindAnswer, 2); 
                }
                
                /// <summary> 
                /// �������� ������� RewindIntercepted �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendRewindIntercepted(address target, int handle)
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� RewindIntercepted ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseRewindIntercepted(int handle)
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetCurrentDirectoryAnswer �� ������
                /// </summary>
                /// <param name="result">��� ����������</param>
                void SendSetCurrentDirectoryAnswer(address target, bool result)
                {
                  G2::SetCurrentDirectoryAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetCurrentDirectoryAnswer ������ ����
                /// </summary>
                /// <param name="result">��� ����������</param>
                void RaiseSetCurrentDirectoryAnswer(bool result)
                {
                  G2::SetCurrentDirectoryAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� SetCurrentDirectoryIntercepted �� ������
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void SendSetCurrentDirectoryIntercepted(address target, const string & path)
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� SetCurrentDirectoryIntercepted ������ ����
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void RaiseSetCurrentDirectoryIntercepted(const string & path)
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFFlush �� ������
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void SendTestFFlush(address target, int handle)
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFFlush ������ ����
                /// </summary>
                /// <param name="handle">�������� ����������</param>
                void RaiseTestFFlush(int handle)
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFSeek �� ������
                /// </summary>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void SendTestFSeek(address target, int offset, int origin)
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFSeek ������ ����
                /// </summary>
                /// <param name="offset">���������� ������ �� Origin</param>
                /// <param name="origin">��������� ������� ���������</param>
                void RaiseTestFSeek(int offset, int origin)
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestFTell �� ������
                /// </summary>
                void SendTestFTell(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestFTell, 2); 
                }
                /// <summary> 
                /// �������� ������� TestFTell ������ ����
                /// </summary>
                void RaiseTestFTell()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestFTell, 2); 
                }
                
                /// <summary> 
                /// �������� ������� TestFWrite �� ������
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="itemSize">������ ��������</param>
                void SendTestFWrite(address target, int count, const ByteVector & data, int itemSize)
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestFWrite ������ ����
                /// </summary>
                /// <param name="count">����� ���������</param>
                /// <param name="data">������ ��� ������</param>
                /// <param name="itemSize">������ ��������</param>
                void RaiseTestFWrite(int count, const ByteVector & data, int itemSize)
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� TestGetCurrentDirectory �� ������
                /// </summary>
                void SendTestGetCurrentDirectory(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestGetCurrentDirectory, 2); 
                }
                /// <summary> 
                /// �������� ������� TestGetCurrentDirectory ������ ����
                /// </summary>
                void RaiseTestGetCurrentDirectory()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestGetCurrentDirectory, 2); 
                }
                
                /// <summary> 
                /// �������� ������� TestRewind �� ������
                /// </summary>
                void SendTestRewind(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestRewind, 2); 
                }
                /// <summary> 
                /// �������� ������� TestRewind ������ ����
                /// </summary>
                void RaiseTestRewind()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestRewind, 2); 
                }
                
                /// <summary> 
                /// �������� ������� TestSetCurrentDirectory �� ������
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void SendTestSetCurrentDirectory(address target, const string & path)
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� TestSetCurrentDirectory ������ ����
                /// </summary>
                /// <param name="path">- ���� ��� ��������� ������� ������� ����������</param>
                void RaiseTestSetCurrentDirectory(const string & path)
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� _fsopenAnswer �� ������
                /// </summary>
                /// <param name="result">��� ����������</param>
                void Send_fsopenAnswer(address target, bool result)
                {
                  G2::_fsopenAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� _fsopenAnswer ������ ����
                /// </summary>
                /// <param name="result">��� ����������</param>
                void Raise_fsopenAnswer(bool result)
                {
                  G2::_fsopenAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// �������� ������� _fsopenIntercepted �� ������
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="shFlag">��� ����������� �������������.</param>
                void Send_fsopenIntercepted(address target, const string & mode, int shFlag)
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// �������� ������� _fsopenIntercepted ������ ����
                /// </summary>
                /// <param name="mode">�����</param>
                /// <param name="shFlag">��� ����������� �������������.</param>
                void Raise_fsopenIntercepted(const string & mode, int shFlag)
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            
            } // ������������ ���� Protocol
          } // ������������ ���� Interceptor
        } // ������������ ���� FileSystem
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
