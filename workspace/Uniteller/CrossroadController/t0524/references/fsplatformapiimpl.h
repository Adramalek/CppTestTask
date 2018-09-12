#pragma once

#include "fsplatformapi.h"
#include "commonplatformapiimpl.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace FileSystem
      {

        class PlatformApi : public Exportable<IPlatformApi>
        {
        public:
          PlatformApi(void);
          ~PlatformApi(void);

          LPSTR PathCombineA(LPSTR pszDest, LPCSTR pszDir,  LPCSTR pszFile);
          BOOL PathCanonicalizeA(LPSTR pszBuf, LPCSTR pszPath);
          LPSTR PathFindFileNameA(LPCSTR pszPath);
          BOOL PathRemoveFileSpecA(LPSTR pszPath);
          HANDLE FindFirstFileExA(LPCSTR lpFileName,
            FINDEX_INFO_LEVELS fInfoLevelId,
            LPVOID lpFindFileData,
            FINDEX_SEARCH_OPS fSearchOp,
            LPVOID lpSearchFilter,
            DWORD dwAdditionalFlags);
          HANDLE
            FindFirstFileA(
            LPCSTR lpFileName,
            LPWIN32_FIND_DATAA lpFindFileData
            );
          BOOL SetFileAttributesA( _In_ LPCSTR lpFileName, _In_ DWORD dwFileAttributes );
          BOOL CreateDirectoryA( _In_ LPCSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes );
          BOOL CopyFileA( _In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName, _In_ BOOL bFailIfExists );
          HANDLE CreateFileA( 
            _In_ LPCSTR lpFileName, 
            _In_ DWORD dwDesiredAccess, 
            _In_ DWORD dwShareMode, 
            _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
            _In_ DWORD dwCreationDisposition, 
            _In_ DWORD dwFlagsAndAttributes, 
            _In_opt_ HANDLE hTemplateFile );

          BOOL FindClose(HANDLE hFindFile);

          BOOL DeleteFileA( _In_ LPCSTR lpFileName );
          BOOL RemoveDirectoryA( _In_ LPCSTR lpPathName );
          BOOL MoveFileA( _In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName );

          BOOL FindNextFileA(
            HANDLE hFindFile,
            LPWIN32_FIND_DATAA lpFindFileData);
          BOOL GetFileTime(HANDLE hFile,
            LPFILETIME lpCreationTime,
            LPFILETIME lpLastAccessTime,
            LPFILETIME lpLastWriteTime);
          DWORD GetFileSize(HANDLE hFile,
            LPDWORD lpFileSizeHigh);
          DWORD GetFileAttributesA(LPCSTR lpFileName);

          DWORD GetCurrentDirectoryA(_In_ DWORD nBufferLength, _Out_ LPSTR lpBuffer);
          BOOL SetCurrentDirectoryA(_In_ LPCSTR lpPathName);

          int fopen_s(_Outptr_result_maybenull_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode);
          size_t fread(void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
          int feof(_In_ FILE * _File);
          int fclose(_Inout_ FILE * _File);
          int fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
          long ftell(_Inout_ FILE * _File);
          void rewind(_Inout_ FILE * _File);
          int fflush(_Inout_ FILE * stream);
     
          int SHCreateDirectoryExA(_In_opt_ HWND hwnd, _In_ LPCSTR pszPath, _In_opt_ const SECURITY_ATTRIBUTES *psa);

          size_t fwrite(_In_reads_bytes_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
          FILE *_fsopen(const char *filename,		const char *mode,	int shflag);
          void _chdir(const char * path);
		  
          int rename(const char * oldPath, const char * newPath);
        };

        extern GlobalPointer<IPlatformApi, PlatformApi> Platform;

      }
    }
  }
}