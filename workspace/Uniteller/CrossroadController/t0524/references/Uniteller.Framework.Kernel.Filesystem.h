// Uniteller.Framework.Kernel.FileSystem

// ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
// �������� ����������. ��� ������������� ��������� ������� ��������� �������� � ������� UniText, 
// ������������� � ����� protocol.utx, � ����� ��������� ���� ��������� ������������� ����� �� �������������� ��������.

#pragma once
#include "kernel/protocolwrapper.h"

// ������������ ���������
#include "Uniteller.Framework.Kernel.FileSystem.Interceptor.h"
using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace FileSystem
      {
        namespace Protocol
        {
          // ���������� ������������ ������� ���� �� ������ ����������
          using Uniteller::Framework::Kernel::FileSystem::Interceptor::Protocol::G1::WinApiAttr;
          using Uniteller::Framework::Kernel::FileSystem::Interceptor::Protocol::G1::IsValidWinApiAttrValue;

          BEGIN_PROTOCOL(8, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// ����������� ������ ��� ������ � �������� ��������
            /// </summary>
            #pragma endregion
            
            #pragma region Flags
            
            /// <summary> 
            /// �������� ��������. �� ������ ��������� �� ��������� �����������
            /// </summary>
            /// <summary> 
            /// ����� �������� ��������� ��� ��������� �����
            /// </summary>
            #pragma endregion
            
            //���������
            #pragma region Messages and wrappers
            
            //���������
            
            BEGIN_WRAPPER()
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          

          BEGIN_PROTOCOL(8, 2)
            
            #pragma region Enumerations
            /// <summary> 
            /// ����������� ������ ��� ������ � �������� ��������
            /// </summary>
            enum class Errors
            {
              AccessDenied = 1, // ������� ��������� ������ � ���������� ����� ��� ���������� (��-�� ���� ������� ��� ��-�� ����, ��� �� ������������ ������ ���������)
              AlreadyExists = 2, // ���� ��� ����� ��� ����������
              FileSystemFailure = 3, // ����� �������� �������
              InvalidArgument = 4, // ������������ ��������
              NotExist = 5, // ���� ��� ����� �� ����������
              OutOfSpace = 6 // ������������ ��������� ������������ ��� ���������� ��������
            };
            
            /// <summary>
            /// ��������� ������������ �������� ��� ������������� ���� Errors
            /// </summary>
            inline bool IsValidErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 7));
            }
            
            /// <summary>
            /// ������� ������������ ��� �������������� �������� �������� � ������������� ���� Errors
            /// </summary>
            inline Errors ConvertToErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return Errors::AccessDenied;
                case 2:
                  return Errors::AlreadyExists;
                case 3:
                  return Errors::FileSystemFailure;
                case 4:
                  return Errors::InvalidArgument;
                case 5:
                  return Errors::NotExist;
                case 6:
                  return Errors::OutOfSpace;
                default: throw KernelException("���������� ������������� �������� �������� %d � ���� Errors", value);
                }
            }
            
            #pragma endregion
            
            #pragma region Flags
            
            /// <summary> 
            /// �������� ��������. �� ������ ��������� �� ��������� �����������
            /// </summary>
            enum class Attributes
            {
              Archive = 1, //Windows
              GroupExecute = 2, //UNIX
              GroupRead = 4, //UNIX
              GroupWrite = 8, //UNIX
              Hidden = 16, //Windows
              OthersExecute = 32, //UNIX
              OthersRead = 64, //UNIX
              OthersWrite = 128, //UNIX
              OwnerExecute = 256, //UNIX
              OwnerRead = 512, //UNIX
              OwnerWrite = 1024, //UNIX
              ReadOnly = 2048, //Windows
              System = 4096 //Windows
            };
            
            /// <summary>
            /// ��������, ����������� ����������� ����� ��� ������ Attributes
            /// </summary>
            inline Attributes operator|(Attributes a, Attributes b)
            {
              return static_cast<Attributes>(static_cast<int>(a), static_cast<int>(b));
            }
            
            /// <summary>
            /// ��������� ��������� ����������� �� ����� mask � Attributes
            /// </summary>
            /// <param name="variable">����������</param>
            /// <param name="mask">����� ��� ��������</param>
            inline bool IsFlagSet(Attributes variable, Attributes mask)
            {
              int m = static_cast<int>(mask);
              return (static_cast<int>(variable) & m)==m;
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ����� Attributes
            /// </summary>
            /// <param name="value">�������� ��� ��������</param>
            inline bool IsValidAttributesValue(const int value)
            {
              return value <= 8191;
            }
            /// <summary> 
            /// ����� �������� ��������� ��� ��������� �����
            /// </summary>
            enum class CompareTests
            {
              Content = 1, //�������� �� �����������
              Date = 2, //�������� �� ����
              Recursive = 4, //���������� ����������� ����������
              Size = 8 //�������� �� �������
            };
            
            /// <summary>
            /// ��������, ����������� ����������� ����� ��� ������ CompareTests
            /// </summary>
            inline CompareTests operator|(CompareTests a, CompareTests b)
            {
              return static_cast<CompareTests>(static_cast<int>(a), static_cast<int>(b));
            }
            
            /// <summary>
            /// ��������� ��������� ����������� �� ����� mask � CompareTests
            /// </summary>
            /// <param name="variable">����������</param>
            /// <param name="mask">����� ��� ��������</param>
            inline bool IsFlagSet(CompareTests variable, CompareTests mask)
            {
              int m = static_cast<int>(mask);
              return (static_cast<int>(variable) & m)==m;
            }
            
            /// <summary>
            /// ��������� ������������ �������� ��� ����� CompareTests
            /// </summary>
            /// <param name="value">�������� ��� ��������</param>
            inline bool IsValidCompareTestsValue(const int value)
            {
              return value <= 15;
            }
            #pragma endregion
            
            //���������
            #pragma region Messages and wrappers
            
            //���������
            // ������� ���� �� ���� ��������� ����� (InvalidArgument)
            BEGIN_MESSAGE(AppendPath,3,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ������������� ����
              ARGUMENT(0, string, PathEnd);
              // ���������� ��� ������������� ���� (������� � ����� ����������� �� ����� ��������)
              ARGUMENT(1, string, PathStart);
            END_MESSAGE(); // AppendPath

            // ����� �� AppendPath
            BEGIN_MESSAGE(AppendPathAnswer,4,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������� ���� � �������� ��������� �����������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // AppendPathAnswer

            // ������� ��� ����� � ���������� �� ��������� ���������� (InvalidArgument, AccessDenied, NotExist)
            BEGIN_MESSAGE(ClearFolder,11,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMask("*");
              }
              // ����� ��� ����� ����� ��� ����������. ���������� "*" ���������� ��������� ��������. ��������� ������ �� ���������� � ����� ������� ������������� �����.
              ARGUMENT(0, string, Mask);
              // ���� (���������� ��� �������������) � ���������� ��������� �����������
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // ClearFolder

            // ������������ � ������ �������� ������� �����
            BEGIN_MESSAGE(ClearFolderAnswer,42,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ClearFolderAnswer

            // ���������� ��� ����� (InvalidArgument,NotExist,AccessDenied)
            BEGIN_MESSAGE(CompareFiles,22,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� (���������� ��� �������������) � ������� ����� ��� ���������
              ARGUMENT(0, string, File1);
              // ���� (���������� ��� �������������) �� ������� ����� ��� ���������
              ARGUMENT(1, string, File2);
            END_MESSAGE(); // CompareFiles

            // ����� �� CompareFiles
            BEGIN_MESSAGE(CompareFilesAnswer,23,5)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� true ���� �������� ������ ��������� ����� false
              ARGUMENT(0, bool, EqAttributes);
              // ���������� true ���� ���������� ������ ��������� ����� false
              ARGUMENT(1, bool, EqContent);
              // ���������� true ���� ���� �������� ������ ��������� ����� false
              ARGUMENT(2, bool, EqDateCreation);
              // ���������� true ���� ���� ��������� ������ ��������� ����� false
              ARGUMENT(3, bool, EqDateMod);
              // ���������� true ���� ������� ������ ��������� ����� false
              ARGUMENT(4, bool, EqSize);
            END_MESSAGE(); // CompareFilesAnswer

            // ���������� ��� ����� � ������������ � ����������� (InvalidArgument,NotExist,AccessDenied). ��� ���������� ������ ������������ � �� ��������� � ��������.
            BEGIN_MESSAGE(CompareFolders,24,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� (���������� ��� �������������) � ������ �����
              ARGUMENT(0, string, File1);
              // ���� (���������� ��� �������������) �� ������ �����
              ARGUMENT(1, string, File2);
              // ����� �������� ���������. ���� �� ������� �� ���� ������������ ������ ����� ������
              FLAG(2, CompareTests, Test);
            END_MESSAGE(); // CompareFolders

            // CompareFolders
            BEGIN_MESSAGE(CompareFoldersAnswer,25,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� �������� ����� ��������� � ���������� ���������
              ARGUMENT(0, bool, EqDateCreation);
              // ���� ��������� ����� ��������� � ���������� ���������
              ARGUMENT(1, bool, EqDateMod);
              // true - � ������������ � ���������� �� ������� ���������� ���������� ����� ���������
              ARGUMENT(2, bool, Equal);
            END_MESSAGE(); // CompareFoldersAnswer

            // �������� ����. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(CopyFile,16,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� ���� ���� ���������� � ���������� ��������� �����������. ���� ���� ���������� �� �� ����� �����������.
              ARGUMENT(0, string, DestPath);
              // ���� � ����� (���������� ��� �������������) ������� ���� ���������� � ���������� ��������� �����������. ������������� "*" ���������.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFile

            // ������������ � ������, ���� ���� ��� ������� ����������
            BEGIN_MESSAGE(CopyFileAnswer,31,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFileAnswer

            // �������� ����. �������������� ������ * ��� ������ ����� �������� �����, ��� ��� ������������� �������������� ��� ��������������� ����� �����. ������������ ����� ����������������. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(CopyFileToFolder,32,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� (���������� ��� �������������) ���� ���� ���������� � ���������� ��������� �����������. ������������� "*" ���������. ���� ���� ���������� �� �� ����� �����������.
              ARGUMENT(0, string, DestPath);
              // ���� � ����� (���������� ��� �������������) ������� ���� ���������� � ���������� ��������� ����������� ����� ��������� "*"
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFileToFolder

            // ������������ � ������, ���� ���� ��� ������� ����������
            BEGIN_MESSAGE(CopyFileToFolderAnswer,33,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFileToFolderAnswer

            // �������� �����  (InvalidArgument, AccessDenied). �� ���������� ����� ����������, ������������ ����� ����������������.
            BEGIN_MESSAGE(CopyFolder,20,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� (���������� ��� �������������) � ������� ���� ���������� ��������� ����� � ���������� ��������� �����������
              ARGUMENT(0, string, DestPath);
              // ���� � ����� (���������� ��� �������������) ������� ���� ���������� � ���������� ��������� �����������
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFolder

            // ������������ � ������, ���� ������� ��� ������� ����������
            BEGIN_MESSAGE(CopyFolderAnswer,30,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFolderAnswer

            // ������� ����� �� ���������� ����. ���� ���� �� ����������, �� �� ���������. (InvalidArgument, AlreadyExists)
            BEGIN_MESSAGE(CreateFolder,9,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� ���� � ���������� ��������� ����������� (InvalidArgument AccessDenied)
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // CreateFolder

            // ������������ � ������ ��������� �������� �����
            BEGIN_MESSAGE(CreateFolderAnswer,40,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CreateFolderAnswer

            // �������� ����� �� �����
            BEGIN_MESSAGE(DeleteFile,44,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� ���������� �����
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // DeleteFile

            // ������������ � ������ ��������� ������� �����
            BEGIN_MESSAGE(DeleteFileAnswer,45,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� ��������
              ARGUMENT(0, bool, Result);
            END_MESSAGE(); // DeleteFileAnswer

            // ������� ����� �� �����
            BEGIN_MESSAGE(DeleteFiles,46,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� ���������� � ������� ����� ����� ����� ���������� ������.
              ARGUMENT(0, string, FolderName);
              // ����� ��� ���� ������
              ARGUMENT(1, string, Mask);
              // ������� �� ���������� ����� � ��������������
              ARGUMENT(2, bool, Recursively);
            END_MESSAGE(); // DeleteFiles

            // ������������ � ������ ��������� �������� ������.
            BEGIN_MESSAGE(DeleteFilesAnswer,47,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� ��������� ������
              ARGUMENT(0, int, FilesDeleted);
            END_MESSAGE(); // DeleteFilesAnswer

            // ������� ����� ������ �� ���� ����������. ���� ����� �� ����������, ������ �� ������������.
            BEGIN_MESSAGE(DeleteFolder,10,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� (���������� ��� �������������) � ���������� ��������� �����������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // DeleteFolder

            // ������������ � ������ ��������� �������� �����
            BEGIN_MESSAGE(DeleteFolderAnswer,41,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // DeleteFolderAnswer

            // ����� � ������ �����-���� ������������� ������
            BEGIN_MESSAGE(Error,28,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ����� ������ ������ ���������
              ENUM(0, Errors, ErrorValue);
            END_MESSAGE(); // Error

            // �� ���������� ���� ������������ �������� ����� (InvalidArgument). �������� ����� - ��� ��������� ���� ����� ���������� �����������.
            BEGIN_MESSAGE(ExtractFilename,12,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� (���������� ��� �������������) � ���������� ��������� �����������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractFilename

            // ����� �� ExtractFilename
            BEGIN_MESSAGE(ExtractFilenameAnswer,13,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� �����. ����� ���� ������ ���� � ������� ��� ������� ���� ��� �������� ����� ���������� �����������.
              ARGUMENT(0, string, Name);
            END_MESSAGE(); // ExtractFilenameAnswer

            // �� ���������� ���� ��������� �������� �����, ����� ���� �� ������������ (InvalidArgument)
            BEGIN_MESSAGE(ExtractPath,14,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� ���� (���������� ��� �������������)
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractPath

            // ����� �� ExtractPath
            BEGIN_MESSAGE(ExtractPathAnswer,15,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ���������� ��������� �����������. ����� ���� "\\" ���� � ������� �� ���� �������� ����� ������������ ������������.
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractPathAnswer

            // ����������, ���������� �� ��������� ����. ����� �� ���� �� �������. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(FileExists,7,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� (���������� ��� �������������) � ���������� ��������� �����������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // FileExists

            // ����� �� FileExists
            BEGIN_MESSAGE(FileExistsAnswer,8,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // true - ���������� false - �� ����������
              ARGUMENT(0, bool, Exists);
            END_MESSAGE(); // FileExistsAnswer

            // �������� ������
            BEGIN_MESSAGE(FindClose,38,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ��������� ������
              ARGUMENT(0, int, SearchIndex);
            END_MESSAGE(); // FindClose

            // ��������� �������� ������ ���������� � ���� ������
            BEGIN_MESSAGE(FindCloseAnswer,39,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������� �������� ������
              ARGUMENT(0, bool, Result);
            END_MESSAGE(); // FindCloseAnswer

            // ���� ���� ��� �����
            BEGIN_MESSAGE(FindFirst,34,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ����� ������
              ARGUMENT(0, string, Mask);
              // ���� �� �������� �������������� ����� (���������� ��� �������������) ����� ��������� "*"
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // FindFirst

            // ������������ ���� ���� (�����) ������� ������(�)
            BEGIN_MESSAGE(FindFirstAnswer,35,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� �����
              FLAG(0, WinApiAttr, Attributes);
              // ��� �����
              ARGUMENT(1, string, FileName);
              // ������ ��������� ������
              ARGUMENT(2, int, SearchIndex);
            END_MESSAGE(); // FindFirstAnswer

            // ���� ��������� ���� ��� �����
            BEGIN_MESSAGE(FindNext,36,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ��������� ������
              ARGUMENT(0, int, SearchIndex);
            END_MESSAGE(); // FindNext

            // ��������� ������ ���������� ����� ���������� � ���� ������
            BEGIN_MESSAGE(FindNextAnswer,37,3)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� �����
              FLAG(0, WinApiAttr, Attributes);
              // ��� �����
              ARGUMENT(1, string, FileName);
              // ��������� ������ ���������� �����
              ARGUMENT(2, bool, Result);
            END_MESSAGE(); // FindNextAnswer

            // ����������, ���������� �� ��������� ����� (InvalidArgument)
            BEGIN_MESSAGE(FolderExists,5,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� (���������� ��� �������������) � ��������� �������� �����������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // FolderExists

            // ����� �� FolderExists
            BEGIN_MESSAGE(FolderExistsAnswer,6,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // true - ���������� false - �� ����������
              ARGUMENT(0, bool, Exists);
            END_MESSAGE(); // FolderExistsAnswer

            // �������� ����� ������������� � ��������� ����������
            BEGIN_MESSAGE(GetDirectories,48,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� ��� ����� ������������� �����
              ARGUMENT(0, string, FolderName);
            END_MESSAGE(); // GetDirectories

            // ������� ������ ������������� ��� ��������� ����������
            BEGIN_MESSAGE(GetDirectoriesAnswer,49,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ������ ���� ������������� ����������� � ��������� ����������
              ARGUMENT(0, StringList, Names);
            END_MESSAGE(); // GetDirectoriesAnswer

            // �������� ���������� �� ����� �����
            BEGIN_MESSAGE(GetExtension,54,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ��� ������������� ���� � ����� � ���� ��� � �����������
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetExtension

            // ������� ���������� �� ����� �����
            BEGIN_MESSAGE(GetExtensionAnswer,55,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� �� ����� �����
              ARGUMENT(0, string, Extension);
            END_MESSAGE(); // GetExtensionAnswer

            // �������� ���������� �� ��������� ����� ��� ����� (InvalidArgument, NotExist)
            BEGIN_MESSAGE(GetFileInfo,26,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� ��� ����� (���������� ��� �������������) � ���������� �������������
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // GetFileInfo

            // ����� �� GetFileInfo
            BEGIN_MESSAGE(GetFileInfoAnswer,27,4)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��������
              FLAG(0, Attributes, Attr);
              // ���� �������� �����
              ARGUMENT(1, timestamp_t, DateCreation);
              // ���� ��������� �����
              ARGUMENT(2, timestamp_t, DateMod);
              // ������ ����� � ������
              ARGUMENT(3, int, Size);
            END_MESSAGE(); // GetFileInfoAnswer

            // �������� ��� ����� ��� ����������
            BEGIN_MESSAGE(GetFileNameWithoutExtension,52,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ��� ������������� ���� � ����� � ���� ��� � �����������
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetFileNameWithoutExtension

            // ������� ����������� ����� ����� ��� ����������
            BEGIN_MESSAGE(GetFileNameWithoutExtensionAnswer,53,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� ����� ��� ����������
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetFileNameWithoutExtensionAnswer

            // �������� ����� ������ � ��������� ����������
            BEGIN_MESSAGE(GetFiles,50,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMask("*");
              }
              // ���������� ��� ����� ������������� �����
              ARGUMENT(0, string, FolderName);
              // ����� ��� ���� ������.
              ARGUMENT(1, string, Mask);
            END_MESSAGE(); // GetFiles

            // ������� ������ ������ ��� ��������� ����������
            BEGIN_MESSAGE(GetFilesAnswer,51,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ������ ������ ���� ������ ����������� � ��������� ����������
              ARGUMENT(0, StringList, Names);
            END_MESSAGE(); // GetFilesAnswer

            // �������� ���������� ������, ��������������� �������� �����, � �������� �����
            BEGIN_MESSAGE(GetFilesCount,56,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // �����
              ARGUMENT(0, string, Mask);
              // ���������� ���� � �����
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetFilesCount

            // ������� ����������� ���������� ������
            BEGIN_MESSAGE(GetFilesCountAnswer,57,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���������� ������
              ARGUMENT(0, int, Count);
            END_MESSAGE(); // GetFilesCountAnswer

            // �������� ����� ����� ���� � �������� ����� � ������, ��������������� �������� �����
            BEGIN_MESSAGE(GetMostRecentFileName,60,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // �����
              ARGUMENT(0, string, Mask);
              // ���������� ���� � �����
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetMostRecentFileName

            // ������� ����� ������ ������ �����
            BEGIN_MESSAGE(GetMostRecentFileNameAnswer,61,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� �����
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetMostRecentFileNameAnswer

            // �������� ��������� ���� � �������� ����� � ������, ��������������� �������� �����
            BEGIN_MESSAGE(GetOldestFileName,58,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // �����
              ARGUMENT(0, string, Mask);
              // ���������� ���� � �����
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetOldestFileName

            // ������� ����� ���������� �����
            BEGIN_MESSAGE(GetOldestFileNameAnswer,59,1)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ��� �����
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetOldestFileNameAnswer

            // ���������� ���� ��������� ���� ��� �����  (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(MoveFile,17,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ������������ ����� (���������� ��� �������������) � ������� ���� ��������� �����������.
              ARGUMENT(0, string, DestPath);
              // ���� � ����� ��� ����� (���������� ��� �������������) ������� ���� ����������� � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // MoveFile

            // ��������� ����������� ����� ���������� � ���� ������
            BEGIN_MESSAGE(MoveFileAnswer,19,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // MoveFileAnswer

            // ���������� ��� ��������������� ���� ��������� ���� ��� ����� (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(RenameFile,18,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // ���� � ����� ��� ����� (���������� ��� �������������). �������� ���� ��� ����� ����� ������������� � ������������ � ���� �����.
              ARGUMENT(0, string, DestPath);
              // ���� � ����� ��� ����� (���������� ��� �������������) ������� ���� ����������� � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // RenameFile

            // ��������� ����������� ����� ���������� � ���� ������
            BEGIN_MESSAGE(RenameFileAnswer,29,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // true ���� �������� ���� ��� ������� ������ ����� false
              ARGUMENT(0, bool, DestCreated);
              // true ���� �������� ���� ��� ������� ������ ����� false
              ARGUMENT(1, bool, SrcRemoved);
            END_MESSAGE(); // RenameFileAnswer

            // ������������� �������� �����, ��������� ��������� ����������� �� ��� (AccessDenied)
            BEGIN_MESSAGE(SetFolderContentAttributes,21,2)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
              // �������� �����
              FLAG(0, WinApiAttr, Attr);
              // ���� � ���������� ��������� ����������� (���������� ��� �������������)
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // SetFolderContentAttributes

            // ������������ � ������ �������� ��������� ���������
            BEGIN_MESSAGE(SetFolderContentAttributesAnswer,43,0)
              /// <summary>
              /// ������������� ���������
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // SetFolderContentAttributesAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// ������� ���� �� ���� ��������� ����� (InvalidArgument)
              /// </summary>
              /// <param name="pathEnd">������ ������������� ����</param>
              /// <param name="pathStart">���������� ��� ������������� ���� (������� � ����� ����������� �� ����� ��������)</param>
              void AppendPath(const string & pathEnd, const string & pathStart) const
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ��� ����� � ���������� �� ��������� ���������� (InvalidArgument, AccessDenied, NotExist)
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              /// <param name="Mask">����� ��� ����� ����� ��� ����������. ���������� "*" ���������� ��������� ��������. ��������� ������ �� ���������� � �����, ������� ������������� �����.</param>
              void ClearFolder(const string & path, string mask = "*") const
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ��� ����� (InvalidArgument,NotExist,AccessDenied)
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������� ����� ��� ���������</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������� ����� ��� ���������</param>
              void CompareFiles(const string & file1, const string & file2) const
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ��� ����� � ������������ � ����������� (InvalidArgument,NotExist,AccessDenied). ��� ���������� ������ ������������ � �� ��������� � ��������.
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������ �����</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������ �����</param>
              /// <param name="test">����� �������� ���������. ���� �� ������� �� ����, ������������ ������ ����� ������</param>
              void CompareFolders(const string & file1, const string & file2, CompareTests test) const
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">���� � �����, ���� ���� ����������, � ���������� ��������� �����������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������.</param>
              void CopyFile(const string & destPath, const string & srcPath) const
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����. �������������� ������ * ��� ������ ����� �������� �����, ��� ��� ������������� �������������� ��� ��������������� ����� �����. ������������ ����� ����������������. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), ���� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������, ����� ��������� "*"</param>
              void CopyFileToFolder(const string & destPath, const string & srcPath) const
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� �����  (InvalidArgument, AccessDenied). �� ���������� ����� ����������, ������������ ����� ����������������.
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), � ������� ���� ���������� ��������� �����, � ���������� ��������� �����������</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������</param>
              void CopyFolder(const string & destPath, const string & srcPath) const
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ����� �� ���������� ����. ���� ���� �� ����������, �� �� ���������. (InvalidArgument, AlreadyExists)
              /// </summary>
              /// <param name="path">���������� ���� � ���������� ��������� ����������� (InvalidArgument, AccessDenied)</param>
              void CreateFolder(const string & path) const
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����� �� �����
              /// </summary>
              /// <param name="fileName">��� ���������� �����</param>
              void DeleteFile(const string & fileName) const
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ����� �� �����
              /// </summary>
              /// <param name="folderName">��� ����������, � ������� ����� ����� ����� ���������� ������.</param>
              /// <param name="mask">����� ��� ���� ������</param>
              /// <param name="recursively">������� �� ���������� ����� � ��������������</param>
              void DeleteFiles(const string & folderName, const string & mask, bool recursively) const
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������� ����� ������ �� ���� ����������. ���� ����� �� ����������, ������ �� ������������.
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void DeleteFolder(const string & path) const
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ����� � ������ �����-���� ������������� ������
              /// </summary>
              /// <param name="errorValue">����� ������ ������ ���������</param>
              void Error(Errors errorValue) const
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �� ���������� ���� ������������ �������� ����� (InvalidArgument). �������� ����� - ��� ��������� ���� ����� ���������� �����������.
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void ExtractFilename(const string & path) const
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �� ���������� ���� ��������� �������� �����, ����� ���� �� ������������ (InvalidArgument)
              /// </summary>
              /// <param name="path">�������� ���� (���������� ��� �������������)</param>
              void ExtractPath(const string & path) const
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ����������, ���������� �� ��������� ����. ����� �� ���� �� �������. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void FileExists(const string & path) const
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void FindClose(int searchIndex) const
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���� ���� ��� �����
              /// </summary>
              /// <param name="mask">����� ������</param>
              /// <param name="path">����, �� �������� �������������� ����� (���������� ��� �������������), ����� ��������� "*"</param>
              void FindFirst(const string & mask, const string & path) const
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���� ��������� ���� ��� �����
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void FindNext(int searchIndex) const
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ����������, ���������� �� ��������� ����� (InvalidArgument)
              /// </summary>
              /// <param name="path">���� � ����� (���������� ��� �������������) � ��������� �������� �����������</param>
              void FolderExists(const string & path) const
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����� ������������� � ��������� ����������
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              void GetDirectories(const string & folderName) const
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ���������� �� ����� �����
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void GetExtension(const string & fileName) const
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ���������� �� ��������� ����� ��� ����� (InvalidArgument, NotExist)
              /// </summary>
              /// <param name="path">���� � ����� ��� ����� (���������� ��� �������������) � ���������� �������������</param>
              void GetFileInfo(const string & path) const
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��� ����� ��� ����������
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void GetFileNameWithoutExtension(const string & fileName) const
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����� ������ � ��������� ����������
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              /// <param name="Mask">����� ��� ���� ������.</param>
              void GetFiles(const string & folderName, string mask = "*") const
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ���������� ������, ��������������� �������� �����, � �������� �����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="Mask">�����</param>
              void GetFilesCount(const string & path, string mask = "::") const
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ����� ����� ���� � �������� ����� � ������, ��������������� �������� �����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="Mask">�����</param>
              void GetMostRecentFileName(const string & path, string mask = "::") const
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ��������� ���� � �������� ����� � ������, ��������������� �������� �����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="Mask">�����</param>
              void GetOldestFileName(const string & path, string mask = "::") const
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ���� ��������� ���� ��� �����  (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">���� � ������������ ����� (���������� ��� �������������), � ������� ���� ��������� �����������.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void MoveFile(const string & destPath, const string & srcPath) const
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ���������� ��� ��������������� ���� ��������� ���� ��� ����� (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">���� � ����� ��� ����� (���������� ��� �������������). �������� ���� ��� ����� ����� ������������� � ������������ � ���� �����.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void RenameFile(const string & destPath, const string & srcPath) const
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// ������������� �������� �����, ��������� ��������� ����������� �� ��� (AccessDenied)
              /// </summary>
              /// <param name="attr">�������� �����</param>
              /// <param name="path">���� � ���������� ��������� ����������� (���������� ��� �������������)</param>
              void SetFolderContentAttributes(WinApiAttr attr, const string & path) const
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// �������� ������� AppendPath �� ������
              /// </summary>
              /// <param name="pathEnd">������ ������������� ����</param>
              /// <param name="pathStart">���������� ��� ������������� ���� (������� � ����� ����������� �� ����� ��������)</param>
              void SendAppendPath(address target, const string & pathEnd, const string & pathStart)
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� AppendPath ������ ����
              /// </summary>
              /// <param name="pathEnd">������ ������������� ����</param>
              /// <param name="pathStart">���������� ��� ������������� ���� (������� � ����� ����������� �� ����� ��������)</param>
              void RaiseAppendPath(const string & pathEnd, const string & pathStart)
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� AppendPathAnswer �� ������
              /// </summary>
              /// <param name="path">������� ���� � �������� ��������� �����������</param>
              void SendAppendPathAnswer(address target, const string & path)
              {
                G2::AppendPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� AppendPathAnswer ������ ����
              /// </summary>
              /// <param name="path">������� ���� � �������� ��������� �����������</param>
              void RaiseAppendPathAnswer(const string & path)
              {
                G2::AppendPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ClearFolder �� ������
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              /// <param name="mask">����� ��� ����� ����� ��� ����������. ���������� "*" ���������� ��������� ��������. ��������� ������ �� ���������� � �����, ������� ������������� �����.</param>
              void SendClearFolder(address target, const string & path, const string & mask = "*")
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ClearFolder ������ ����
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              /// <param name="mask">����� ��� ����� ����� ��� ����������. ���������� "*" ���������� ��������� ��������. ��������� ������ �� ���������� � �����, ������� ������������� �����.</param>
              void RaiseClearFolder(const string & path, const string & mask = "*")
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ClearFolderAnswer �� ������
              /// </summary>
              void SendClearFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::ClearFolderAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� ClearFolderAnswer ������ ����
              /// </summary>
              void RaiseClearFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ClearFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� CompareFiles �� ������
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������� ����� ��� ���������</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������� ����� ��� ���������</param>
              void SendCompareFiles(address target, const string & file1, const string & file2)
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CompareFiles ������ ����
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������� ����� ��� ���������</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������� ����� ��� ���������</param>
              void RaiseCompareFiles(const string & file1, const string & file2)
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CompareFilesAnswer �� ������
              /// </summary>
              /// <param name="eqAttributes">���������� true, ���� �������� ������ ���������, ����� false</param>
              /// <param name="eqContent">���������� true, ���� ���������� ������ ���������, ����� false</param>
              /// <param name="eqDateCreation">���������� true, ���� ���� �������� ������ ���������, ����� false</param>
              /// <param name="eqDateMod">���������� true, ���� ���� ��������� ������ ���������, ����� false</param>
              /// <param name="eqSize">���������� true, ���� ������� ������ ���������, ����� false</param>
              void SendCompareFilesAnswer(address target, bool eqAttributes, bool eqContent, bool eqDateCreation, bool eqDateMod, bool eqSize)
              {
                G2::CompareFilesAnswer cmd;
                cmd.SetEqAttributes(eqAttributes);
                cmd.SetEqContent(eqContent);
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqSize(eqSize);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CompareFilesAnswer ������ ����
              /// </summary>
              /// <param name="eqAttributes">���������� true, ���� �������� ������ ���������, ����� false</param>
              /// <param name="eqContent">���������� true, ���� ���������� ������ ���������, ����� false</param>
              /// <param name="eqDateCreation">���������� true, ���� ���� �������� ������ ���������, ����� false</param>
              /// <param name="eqDateMod">���������� true, ���� ���� ��������� ������ ���������, ����� false</param>
              /// <param name="eqSize">���������� true, ���� ������� ������ ���������, ����� false</param>
              void RaiseCompareFilesAnswer(bool eqAttributes, bool eqContent, bool eqDateCreation, bool eqDateMod, bool eqSize)
              {
                G2::CompareFilesAnswer cmd;
                cmd.SetEqAttributes(eqAttributes);
                cmd.SetEqContent(eqContent);
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqSize(eqSize);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CompareFolders �� ������
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������ �����</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������ �����</param>
              /// <param name="test">����� �������� ���������. ���� �� ������� �� ����, ������������ ������ ����� ������</param>
              void SendCompareFolders(address target, const string & file1, const string & file2, CompareTests test)
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CompareFolders ������ ����
              /// </summary>
              /// <param name="file1">���� (���������� ��� �������������) � ������ �����</param>
              /// <param name="file2">���� (���������� ��� �������������) �� ������ �����</param>
              /// <param name="test">����� �������� ���������. ���� �� ������� �� ����, ������������ ������ ����� ������</param>
              void RaiseCompareFolders(const string & file1, const string & file2, CompareTests test)
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CompareFoldersAnswer �� ������
              /// </summary>
              /// <param name="eqDateCreation">���� �������� �����, ��������� � ����������, ���������</param>
              /// <param name="eqDateMod">���� ��������� �����, ��������� � ����������, ���������</param>
              /// <param name="equal">true - � ������������ � ���������� �� ������� ���������� ���������� ����� ���������</param>
              void SendCompareFoldersAnswer(address target, bool eqDateCreation, bool eqDateMod, bool equal)
              {
                G2::CompareFoldersAnswer cmd;
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqual(equal);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CompareFoldersAnswer ������ ����
              /// </summary>
              /// <param name="eqDateCreation">���� �������� �����, ��������� � ����������, ���������</param>
              /// <param name="eqDateMod">���� ��������� �����, ��������� � ����������, ���������</param>
              /// <param name="equal">true - � ������������ � ���������� �� ������� ���������� ���������� ����� ���������</param>
              void RaiseCompareFoldersAnswer(bool eqDateCreation, bool eqDateMod, bool equal)
              {
                G2::CompareFoldersAnswer cmd;
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqual(equal);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CopyFile �� ������
              /// </summary>
              /// <param name="destPath">���� � �����, ���� ���� ����������, � ���������� ��������� �����������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������.</param>
              void SendCopyFile(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CopyFile ������ ����
              /// </summary>
              /// <param name="destPath">���� � �����, ���� ���� ����������, � ���������� ��������� �����������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������.</param>
              void RaiseCopyFile(const string & destPath, const string & srcPath)
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CopyFileAnswer �� ������
              /// </summary>
              void SendCopyFileAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFileAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� CopyFileAnswer ������ ����
              /// </summary>
              void RaiseCopyFileAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFileAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� CopyFileToFolder �� ������
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), ���� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������, ����� ��������� "*"</param>
              void SendCopyFileToFolder(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CopyFileToFolder ������ ����
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), ���� ���� ����������, � ���������� ��������� �����������. ������������� "*" ���������. ���� ���� ����������, �� �� ����� �����������.</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������, ����� ��������� "*"</param>
              void RaiseCopyFileToFolder(const string & destPath, const string & srcPath)
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CopyFileToFolderAnswer �� ������
              /// </summary>
              void SendCopyFileToFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFileToFolderAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� CopyFileToFolderAnswer ������ ����
              /// </summary>
              void RaiseCopyFileToFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFileToFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� CopyFolder �� ������
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), � ������� ���� ���������� ��������� �����, � ���������� ��������� �����������</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������</param>
              void SendCopyFolder(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CopyFolder ������ ����
              /// </summary>
              /// <param name="destPath">���� � ����� (���������� ��� �������������), � ������� ���� ���������� ��������� �����, � ���������� ��������� �����������</param>
              /// <param name="srcPath">���� � ����� (���������� ��� �������������), ������� ���� ����������, � ���������� ��������� �����������</param>
              void RaiseCopyFolder(const string & destPath, const string & srcPath)
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CopyFolderAnswer �� ������
              /// </summary>
              void SendCopyFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFolderAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� CopyFolderAnswer ������ ����
              /// </summary>
              void RaiseCopyFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� CreateFolder �� ������
              /// </summary>
              /// <param name="path">���������� ���� � ���������� ��������� ����������� (InvalidArgument, AccessDenied)</param>
              void SendCreateFolder(address target, const string & path)
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� CreateFolder ������ ����
              /// </summary>
              /// <param name="path">���������� ���� � ���������� ��������� ����������� (InvalidArgument, AccessDenied)</param>
              void RaiseCreateFolder(const string & path)
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� CreateFolderAnswer �� ������
              /// </summary>
              void SendCreateFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CreateFolderAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� CreateFolderAnswer ������ ����
              /// </summary>
              void RaiseCreateFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CreateFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� DeleteFile �� ������
              /// </summary>
              /// <param name="fileName">��� ���������� �����</param>
              void SendDeleteFile(address target, const string & fileName)
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� DeleteFile ������ ����
              /// </summary>
              /// <param name="fileName">��� ���������� �����</param>
              void RaiseDeleteFile(const string & fileName)
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� DeleteFileAnswer �� ������
              /// </summary>
              /// <param name="result">��������� ��������</param>
              void SendDeleteFileAnswer(address target, bool result)
              {
                G2::DeleteFileAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� DeleteFileAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� ��������</param>
              void RaiseDeleteFileAnswer(bool result)
              {
                G2::DeleteFileAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� DeleteFiles �� ������
              /// </summary>
              /// <param name="folderName">��� ����������, � ������� ����� ����� ����� ���������� ������.</param>
              /// <param name="mask">����� ��� ���� ������</param>
              /// <param name="recursively">������� �� ���������� ����� � ��������������</param>
              void SendDeleteFiles(address target, const string & folderName, const string & mask, bool recursively)
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� DeleteFiles ������ ����
              /// </summary>
              /// <param name="folderName">��� ����������, � ������� ����� ����� ����� ���������� ������.</param>
              /// <param name="mask">����� ��� ���� ������</param>
              /// <param name="recursively">������� �� ���������� ����� � ��������������</param>
              void RaiseDeleteFiles(const string & folderName, const string & mask, bool recursively)
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� DeleteFilesAnswer �� ������
              /// </summary>
              /// <param name="filesDeleted">���������� ��������� ������</param>
              void SendDeleteFilesAnswer(address target, int filesDeleted)
              {
                G2::DeleteFilesAnswer cmd;
                cmd.SetFilesDeleted(filesDeleted);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� DeleteFilesAnswer ������ ����
              /// </summary>
              /// <param name="filesDeleted">���������� ��������� ������</param>
              void RaiseDeleteFilesAnswer(int filesDeleted)
              {
                G2::DeleteFilesAnswer cmd;
                cmd.SetFilesDeleted(filesDeleted);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� DeleteFolder �� ������
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void SendDeleteFolder(address target, const string & path)
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� DeleteFolder ������ ����
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void RaiseDeleteFolder(const string & path)
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� DeleteFolderAnswer �� ������
              /// </summary>
              void SendDeleteFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::DeleteFolderAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� DeleteFolderAnswer ������ ����
              /// </summary>
              void RaiseDeleteFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::DeleteFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� Error �� ������
              /// </summary>
              /// <param name="errorValue">����� ������ ������ ���������</param>
              void SendError(address target, Errors errorValue)
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� Error ������ ����
              /// </summary>
              /// <param name="errorValue">����� ������ ������ ���������</param>
              void RaiseError(Errors errorValue)
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ExtractFilename �� ������
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void SendExtractFilename(address target, const string & path)
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ExtractFilename ������ ����
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void RaiseExtractFilename(const string & path)
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ExtractFilenameAnswer �� ������
              /// </summary>
              /// <param name="name">�������� �����. ����� ���� ������, ���� � ������� ��� ������� ���� ��� �������� ����� ���������� �����������.</param>
              void SendExtractFilenameAnswer(address target, const string & name)
              {
                G2::ExtractFilenameAnswer cmd;
                cmd.SetName(name);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ExtractFilenameAnswer ������ ����
              /// </summary>
              /// <param name="name">�������� �����. ����� ���� ������, ���� � ������� ��� ������� ���� ��� �������� ����� ���������� �����������.</param>
              void RaiseExtractFilenameAnswer(const string & name)
              {
                G2::ExtractFilenameAnswer cmd;
                cmd.SetName(name);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ExtractPath �� ������
              /// </summary>
              /// <param name="path">�������� ���� (���������� ��� �������������)</param>
              void SendExtractPath(address target, const string & path)
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ExtractPath ������ ����
              /// </summary>
              /// <param name="path">�������� ���� (���������� ��� �������������)</param>
              void RaiseExtractPath(const string & path)
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� ExtractPathAnswer �� ������
              /// </summary>
              /// <param name="path">���� � ���������� ��������� �����������. ����� ���� "\\", ���� � ������� �� ���� �������� ����� ������������ ������������.</param>
              void SendExtractPathAnswer(address target, const string & path)
              {
                G2::ExtractPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� ExtractPathAnswer ������ ����
              /// </summary>
              /// <param name="path">���� � ���������� ��������� �����������. ����� ���� "\\", ���� � ������� �� ���� �������� ����� ������������ ������������.</param>
              void RaiseExtractPathAnswer(const string & path)
              {
                G2::ExtractPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FileExists �� ������
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void SendFileExists(address target, const string & path)
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FileExists ������ ����
              /// </summary>
              /// <param name="path">���� (���������� ��� �������������) � ���������� ��������� �����������</param>
              void RaiseFileExists(const string & path)
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FileExistsAnswer �� ������
              /// </summary>
              /// <param name="exists">true - ����������, false - �� ����������</param>
              void SendFileExistsAnswer(address target, bool exists)
              {
                G2::FileExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FileExistsAnswer ������ ����
              /// </summary>
              /// <param name="exists">true - ����������, false - �� ����������</param>
              void RaiseFileExistsAnswer(bool exists)
              {
                G2::FileExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindClose �� ������
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void SendFindClose(address target, int searchIndex)
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindClose ������ ����
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void RaiseFindClose(int searchIndex)
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindCloseAnswer �� ������
              /// </summary>
              /// <param name="result">��������� �������� ������</param>
              void SendFindCloseAnswer(address target, bool result)
              {
                G2::FindCloseAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindCloseAnswer ������ ����
              /// </summary>
              /// <param name="result">��������� �������� ������</param>
              void RaiseFindCloseAnswer(bool result)
              {
                G2::FindCloseAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindFirst �� ������
              /// </summary>
              /// <param name="mask">����� ������</param>
              /// <param name="path">����, �� �������� �������������� ����� (���������� ��� �������������), ����� ��������� "*"</param>
              void SendFindFirst(address target, const string & mask, const string & path)
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindFirst ������ ����
              /// </summary>
              /// <param name="mask">����� ������</param>
              /// <param name="path">����, �� �������� �������������� ����� (���������� ��� �������������), ����� ��������� "*"</param>
              void RaiseFindFirst(const string & mask, const string & path)
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindFirstAnswer �� ������
              /// </summary>
              /// <param name="attributes">�������� �����</param>
              /// <param name="fileName">��� �����</param>
              /// <param name="searchIndex">������ ��������� ������</param>
              void SendFindFirstAnswer(address target, WinApiAttr attributes, const string & fileName, int searchIndex)
              {
                G2::FindFirstAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindFirstAnswer ������ ����
              /// </summary>
              /// <param name="attributes">�������� �����</param>
              /// <param name="fileName">��� �����</param>
              /// <param name="searchIndex">������ ��������� ������</param>
              void RaiseFindFirstAnswer(WinApiAttr attributes, const string & fileName, int searchIndex)
              {
                G2::FindFirstAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindNext �� ������
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void SendFindNext(address target, int searchIndex)
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindNext ������ ����
              /// </summary>
              /// <param name="searchIndex">������ ��������� ������</param>
              void RaiseFindNext(int searchIndex)
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FindNextAnswer �� ������
              /// </summary>
              /// <param name="attributes">�������� �����</param>
              /// <param name="fileName">��� �����</param>
              /// <param name="result">��������� ������ ���������� �����</param>
              void SendFindNextAnswer(address target, WinApiAttr attributes, const string & fileName, bool result)
              {
                G2::FindNextAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FindNextAnswer ������ ����
              /// </summary>
              /// <param name="attributes">�������� �����</param>
              /// <param name="fileName">��� �����</param>
              /// <param name="result">��������� ������ ���������� �����</param>
              void RaiseFindNextAnswer(WinApiAttr attributes, const string & fileName, bool result)
              {
                G2::FindNextAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FolderExists �� ������
              /// </summary>
              /// <param name="path">���� � ����� (���������� ��� �������������) � ��������� �������� �����������</param>
              void SendFolderExists(address target, const string & path)
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FolderExists ������ ����
              /// </summary>
              /// <param name="path">���� � ����� (���������� ��� �������������) � ��������� �������� �����������</param>
              void RaiseFolderExists(const string & path)
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� FolderExistsAnswer �� ������
              /// </summary>
              /// <param name="exists">true - ����������, false - �� ����������</param>
              void SendFolderExistsAnswer(address target, bool exists)
              {
                G2::FolderExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� FolderExistsAnswer ������ ����
              /// </summary>
              /// <param name="exists">true - ����������, false - �� ����������</param>
              void RaiseFolderExistsAnswer(bool exists)
              {
                G2::FolderExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetDirectories �� ������
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              void SendGetDirectories(address target, const string & folderName)
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetDirectories ������ ����
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              void RaiseGetDirectories(const string & folderName)
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetDirectoriesAnswer �� ������
              /// </summary>
              /// <param name="names">������ ������ ���� �������������, ����������� � ��������� ����������</param>
              void SendGetDirectoriesAnswer(address target, const StringList & names)
              {
                G2::GetDirectoriesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetDirectoriesAnswer ������ ����
              /// </summary>
              /// <param name="names">������ ������ ���� �������������, ����������� � ��������� ����������</param>
              void RaiseGetDirectoriesAnswer(const StringList & names)
              {
                G2::GetDirectoriesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetExtension �� ������
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void SendGetExtension(address target, const string & fileName)
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetExtension ������ ����
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void RaiseGetExtension(const string & fileName)
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetExtensionAnswer �� ������
              /// </summary>
              /// <param name="extension">���������� �� ����� �����</param>
              void SendGetExtensionAnswer(address target, const string & extension)
              {
                G2::GetExtensionAnswer cmd;
                cmd.SetExtension(extension);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetExtensionAnswer ������ ����
              /// </summary>
              /// <param name="extension">���������� �� ����� �����</param>
              void RaiseGetExtensionAnswer(const string & extension)
              {
                G2::GetExtensionAnswer cmd;
                cmd.SetExtension(extension);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFileInfo �� ������
              /// </summary>
              /// <param name="path">���� � ����� ��� ����� (���������� ��� �������������) � ���������� �������������</param>
              void SendGetFileInfo(address target, const string & path)
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFileInfo ������ ����
              /// </summary>
              /// <param name="path">���� � ����� ��� ����� (���������� ��� �������������) � ���������� �������������</param>
              void RaiseGetFileInfo(const string & path)
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFileInfoAnswer �� ������
              /// </summary>
              /// <param name="attr">��������</param>
              /// <param name="dateCreation">���� �������� �����</param>
              /// <param name="dateMod">���� ��������� �����</param>
              /// <param name="size">������ ����� � ������</param>
              void SendGetFileInfoAnswer(address target, Attributes attr, timestamp_t dateCreation, timestamp_t dateMod, int size)
              {
                G2::GetFileInfoAnswer cmd;
                cmd.SetAttr(attr);
                cmd.SetDateCreation(dateCreation);
                cmd.SetDateMod(dateMod);
                cmd.SetSize(size);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFileInfoAnswer ������ ����
              /// </summary>
              /// <param name="attr">��������</param>
              /// <param name="dateCreation">���� �������� �����</param>
              /// <param name="dateMod">���� ��������� �����</param>
              /// <param name="size">������ ����� � ������</param>
              void RaiseGetFileInfoAnswer(Attributes attr, timestamp_t dateCreation, timestamp_t dateMod, int size)
              {
                G2::GetFileInfoAnswer cmd;
                cmd.SetAttr(attr);
                cmd.SetDateCreation(dateCreation);
                cmd.SetDateMod(dateMod);
                cmd.SetSize(size);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFileNameWithoutExtension �� ������
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void SendGetFileNameWithoutExtension(address target, const string & fileName)
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFileNameWithoutExtension ������ ����
              /// </summary>
              /// <param name="fileName">������ ��� ������������� ���� � ����� � ���� ��� � �����������</param>
              void RaiseGetFileNameWithoutExtension(const string & fileName)
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFileNameWithoutExtensionAnswer �� ������
              /// </summary>
              /// <param name="fileName">��� ����� ��� ����������</param>
              void SendGetFileNameWithoutExtensionAnswer(address target, const string & fileName)
              {
                G2::GetFileNameWithoutExtensionAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFileNameWithoutExtensionAnswer ������ ����
              /// </summary>
              /// <param name="fileName">��� ����� ��� ����������</param>
              void RaiseGetFileNameWithoutExtensionAnswer(const string & fileName)
              {
                G2::GetFileNameWithoutExtensionAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFiles �� ������
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              /// <param name="mask">����� ��� ���� ������.</param>
              void SendGetFiles(address target, const string & folderName, const string & mask = "*")
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFiles ������ ����
              /// </summary>
              /// <param name="folderName">����������, ��� ����� ������������� �����</param>
              /// <param name="mask">����� ��� ���� ������.</param>
              void RaiseGetFiles(const string & folderName, const string & mask = "*")
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFilesAnswer �� ������
              /// </summary>
              /// <param name="names">������ ������ ���� ������, ����������� � ��������� ����������</param>
              void SendGetFilesAnswer(address target, const StringList & names)
              {
                G2::GetFilesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFilesAnswer ������ ����
              /// </summary>
              /// <param name="names">������ ������ ���� ������, ����������� � ��������� ����������</param>
              void RaiseGetFilesAnswer(const StringList & names)
              {
                G2::GetFilesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFilesCount �� ������
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void SendGetFilesCount(address target, const string & path, const string & mask = "::")
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFilesCount ������ ����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void RaiseGetFilesCount(const string & path, const string & mask = "::")
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetFilesCountAnswer �� ������
              /// </summary>
              /// <param name="count">���������� ������</param>
              void SendGetFilesCountAnswer(address target, int count)
              {
                G2::GetFilesCountAnswer cmd;
                cmd.SetCount(count);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetFilesCountAnswer ������ ����
              /// </summary>
              /// <param name="count">���������� ������</param>
              void RaiseGetFilesCountAnswer(int count)
              {
                G2::GetFilesCountAnswer cmd;
                cmd.SetCount(count);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetMostRecentFileName �� ������
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void SendGetMostRecentFileName(address target, const string & path, const string & mask = "::")
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetMostRecentFileName ������ ����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void RaiseGetMostRecentFileName(const string & path, const string & mask = "::")
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetMostRecentFileNameAnswer �� ������
              /// </summary>
              /// <param name="fileName">��� �����</param>
              void SendGetMostRecentFileNameAnswer(address target, const string & fileName)
              {
                G2::GetMostRecentFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetMostRecentFileNameAnswer ������ ����
              /// </summary>
              /// <param name="fileName">��� �����</param>
              void RaiseGetMostRecentFileNameAnswer(const string & fileName)
              {
                G2::GetMostRecentFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetOldestFileName �� ������
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void SendGetOldestFileName(address target, const string & path, const string & mask = "::")
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetOldestFileName ������ ����
              /// </summary>
              /// <param name="path">���������� ���� � �����</param>
              /// <param name="mask">�����</param>
              void RaiseGetOldestFileName(const string & path, const string & mask = "::")
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� GetOldestFileNameAnswer �� ������
              /// </summary>
              /// <param name="fileName">��� �����</param>
              void SendGetOldestFileNameAnswer(address target, const string & fileName)
              {
                G2::GetOldestFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� GetOldestFileNameAnswer ������ ����
              /// </summary>
              /// <param name="fileName">��� �����</param>
              void RaiseGetOldestFileNameAnswer(const string & fileName)
              {
                G2::GetOldestFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� MoveFile �� ������
              /// </summary>
              /// <param name="destPath">���� � ������������ ����� (���������� ��� �������������), � ������� ���� ��������� �����������.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void SendMoveFile(address target, const string & destPath, const string & srcPath)
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� MoveFile ������ ����
              /// </summary>
              /// <param name="destPath">���� � ������������ ����� (���������� ��� �������������), � ������� ���� ��������� �����������.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void RaiseMoveFile(const string & destPath, const string & srcPath)
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� MoveFileAnswer �� ������
              /// </summary>
              void SendMoveFileAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::MoveFileAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� MoveFileAnswer ������ ����
              /// </summary>
              void RaiseMoveFileAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::MoveFileAnswer, 2); 
              }
              
              /// <summary> 
              /// �������� ������� RenameFile �� ������
              /// </summary>
              /// <param name="destPath">���� � ����� ��� ����� (���������� ��� �������������). �������� ���� ��� ����� ����� ������������� � ������������ � ���� �����.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void SendRenameFile(address target, const string & destPath, const string & srcPath)
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� RenameFile ������ ����
              /// </summary>
              /// <param name="destPath">���� � ����� ��� ����� (���������� ��� �������������). �������� ���� ��� ����� ����� ������������� � ������������ � ���� �����.</param>
              /// <param name="srcPath">���� � ����� ��� ����� (���������� ��� �������������), ������� ���� �����������, � ���������� ��������� �����������. �� ��������� �������� ���� ���� ����� ������.</param>
              void RaiseRenameFile(const string & destPath, const string & srcPath)
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� RenameFileAnswer �� ������
              /// </summary>
              /// <param name="destCreated">true, ���� �������� ���� ��� ������� ������, ����� false</param>
              /// <param name="srcRemoved">true, ���� �������� ���� ��� ������� ������, ����� false</param>
              void SendRenameFileAnswer(address target, bool destCreated, bool srcRemoved)
              {
                G2::RenameFileAnswer cmd;
                cmd.SetDestCreated(destCreated);
                cmd.SetSrcRemoved(srcRemoved);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� RenameFileAnswer ������ ����
              /// </summary>
              /// <param name="destCreated">true, ���� �������� ���� ��� ������� ������, ����� false</param>
              /// <param name="srcRemoved">true, ���� �������� ���� ��� ������� ������, ����� false</param>
              void RaiseRenameFileAnswer(bool destCreated, bool srcRemoved)
              {
                G2::RenameFileAnswer cmd;
                cmd.SetDestCreated(destCreated);
                cmd.SetSrcRemoved(srcRemoved);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� SetFolderContentAttributes �� ������
              /// </summary>
              /// <param name="attr">�������� �����</param>
              /// <param name="path">���� � ���������� ��������� ����������� (���������� ��� �������������)</param>
              void SendSetFolderContentAttributes(address target, WinApiAttr attr, const string & path)
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// �������� ������� SetFolderContentAttributes ������ ����
              /// </summary>
              /// <param name="attr">�������� �����</param>
              /// <param name="path">���� � ���������� ��������� ����������� (���������� ��� �������������)</param>
              void RaiseSetFolderContentAttributes(WinApiAttr attr, const string & path)
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// �������� ������� SetFolderContentAttributesAnswer �� ������
              /// </summary>
              void SendSetFolderContentAttributesAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::SetFolderContentAttributesAnswer, 2); 
              }
              /// <summary> 
              /// �������� ������� SetFolderContentAttributesAnswer ������ ����
              /// </summary>
              void RaiseSetFolderContentAttributesAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::SetFolderContentAttributesAnswer, 2); 
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // ������������ ���� Protocol
        } // ������������ ���� FileSystem
      } // ������������ ���� Kernel
    } // ������������ ���� Framework
  } // ������������ ���� Uniteller
