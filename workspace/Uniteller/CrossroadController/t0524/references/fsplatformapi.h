#pragma once

#include "kernel/interceptor.h"
#include "kernel/ioplatformapi.h"

#ifndef __GNUG__
#include "stdafx.h"
#include "resource.h"
#endif

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace FileSystem
      {
        static const char * ApiId = "FileSystem";
        
        class IPlatformApi : public Io::IIoPlatformApi
        {
        public:
          virtual LPSTR PathCombineA(LPSTR pszDest, LPCSTR pszDir,  LPCSTR pszFile) = 0;
          virtual BOOL PathCanonicalizeA(LPSTR pszBuf, LPCSTR pszPath) = 0;
          virtual LPSTR PathFindFileNameA(LPCSTR pszPath) = 0;
          virtual BOOL PathRemoveFileSpecA(LPSTR pszPath) = 0;
          virtual HANDLE FindFirstFileExA(LPCSTR lpFileName,
            FINDEX_INFO_LEVELS fInfoLevelId,
            LPVOID lpFindFileData,
            FINDEX_SEARCH_OPS fSearchOp,
            LPVOID lpSearchFilter,
            DWORD dwAdditionalFlags) = 0;
          virtual HANDLE
            FindFirstFileA(
            LPCSTR lpFileName,
            LPWIN32_FIND_DATAA lpFindFileData
            ) = 0;
          virtual BOOL FindNextFileA(
            HANDLE hFindFile,
            LPWIN32_FIND_DATAA lpFindFileData) = 0;
          virtual BOOL SetFileAttributesA( _In_ LPCSTR lpFileName, _In_ DWORD dwFileAttributes )=0;
          virtual BOOL CreateDirectoryA( _In_ LPCSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes )=0;
          virtual BOOL CopyFileA( _In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName, _In_ BOOL bFailIfExists )=0;

          virtual BOOL DeleteFileA( _In_ LPCSTR lpFileName )=0;
          virtual BOOL RemoveDirectoryA( _In_ LPCSTR lpPathName )=0;
          virtual BOOL MoveFileA( _In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName )=0;

          virtual BOOL FindClose(HANDLE hFindFile)=0;
          virtual HANDLE CreateFileA( 
            _In_ LPCSTR lpFileName, 
            _In_ DWORD dwDesiredAccess, 
            _In_ DWORD dwShareMode, 
            _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
            _In_ DWORD dwCreationDisposition, 
            _In_ DWORD dwFlagsAndAttributes, 
            _In_opt_ HANDLE hTemplateFile )=0;
          virtual BOOL GetFileTime(HANDLE hFile,
            LPFILETIME lpCreationTime,
            LPFILETIME lpLastAccessTime,
            LPFILETIME lpLastWriteTime) = 0;          
          virtual DWORD GetFileSize(HANDLE hFile,
            LPDWORD lpFileSizeHigh) = 0;
          virtual DWORD GetFileAttributesA(LPCSTR lpFileName) = 0;
          
          virtual int SHCreateDirectoryExA(_In_opt_ HWND hwnd, _In_ LPCSTR pszPath, _In_opt_ const SECURITY_ATTRIBUTES *psa) =0;
          virtual DWORD GetCurrentDirectoryA(_In_ DWORD nBufferLength, _Out_ LPSTR lpBuffer) = 0;
          virtual BOOL SetCurrentDirectoryA(_In_ LPCSTR lpPathName) = 0;

        };

      } // пространство имен CommonApi
    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
