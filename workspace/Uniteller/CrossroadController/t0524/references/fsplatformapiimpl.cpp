#ifndef __GNUG__
#include <Shlwapi.h>
#include <ShlObj.h> 
#include <direct.h>
#else
#include "kernel/linux/filesystem.h"
#endif

#include "fsplatformapiimpl.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace FileSystem
      {
        GlobalPointer<IPlatformApi, PlatformApi> Platform;

        PlatformApi::PlatformApi(void)
        {
        }

        PlatformApi::~PlatformApi(void)
        {
        }

        LPSTR PlatformApi::PathCombineA( LPSTR pszDest, LPCSTR pszDir, LPCSTR pszFile )
        {         
          return ::PathCombineA(pszDest,pszDir,pszFile);
        }
        
        BOOL PlatformApi::PathCanonicalizeA( LPSTR pszBuf, LPCSTR pszPath )
        { 
          return ::PathCanonicalizeA(pszBuf,pszPath);
        }
        
        LPSTR PlatformApi::PathFindFileNameA( LPCSTR pszPath )
        { 
          return ::PathFindFileNameA(pszPath);
        }
        
        BOOL PlatformApi::PathRemoveFileSpecA( LPSTR pszPath )
        { 
          return ::PathRemoveFileSpecA(pszPath);
        }


        DWORD PlatformApi::GetCurrentDirectoryA(_In_ DWORD nBufferLength, _Out_ LPSTR lpBuffer)
        {
          return ::GetCurrentDirectoryA(nBufferLength, lpBuffer);
        }

        BOOL  PlatformApi::SetCurrentDirectoryA(_In_ LPCSTR lpPathName)
        {          
          return ::SetCurrentDirectoryA(lpPathName);
        }

        HANDLE PlatformApi::FindFirstFileExA( LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags )
        { 
          return ::FindFirstFileExA(lpFileName,fInfoLevelId,lpFindFileData,fSearchOp,lpSearchFilter,dwAdditionalFlags  );
        }

        BOOL PlatformApi::FindNextFileA( HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData )
        { 
          return ::FindNextFileA(hFindFile, lpFindFileData);
        }

        //HANDLE PlatformApi::CreateFileA( LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile )
        //{ 
        //  return ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
        //}

        BOOL PlatformApi::GetFileTime( HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime )
        { 
          return ::GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
        }

        DWORD PlatformApi::GetFileSize( HANDLE hFile, LPDWORD lpFileSizeHigh )
        { 
          return ::GetFileSize(hFile, lpFileSizeHigh);
        }

        DWORD PlatformApi::GetFileAttributesA( LPCSTR lpFileName )
        { 
          return ::GetFileAttributesA(lpFileName);
        }

        HANDLE PlatformApi::FindFirstFileA( LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData )
        {
          return ::FindFirstFileA(lpFileName,lpFindFileData);
        }

        BOOL PlatformApi::SetFileAttributesA( _In_ LPCSTR lpFileName, _In_ DWORD dwFileAttributes )
        {
          return ::SetFileAttributesA(lpFileName,dwFileAttributes);
        }

        BOOL PlatformApi::CreateDirectoryA( _In_ LPCSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes )
        {
          return ::CreateDirectoryA(lpPathName,lpSecurityAttributes);
        }

        BOOL PlatformApi::CopyFileA( _In_ LPCSTR lpExistingFileName,
          _In_ LPCSTR lpNewFileName, _In_ BOOL bFailIfExists )
        {
          return ::CopyFileA(lpExistingFileName,lpNewFileName,bFailIfExists);
        }

        BOOL PlatformApi::FindClose(HANDLE hFindFile)
        {
          return ::FindClose(hFindFile);
        }

        BOOL PlatformApi::DeleteFileA( _In_ LPCSTR lpFileName )
        {
          return ::DeleteFileA(lpFileName);
        }

        BOOL PlatformApi::RemoveDirectoryA( _In_ LPCSTR lpPathName )
        {
#ifndef __GNUG__
          return rmdir(lpPathName) == 0 ? TRUE : FALSE;
#else
          return ::RemoveDirectoryA(lpPathName); // - Глючит под Windows XP
#endif
        }

        BOOL PlatformApi::MoveFileA( _In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName )
        {
          return ::MoveFileA(lpExistingFileName,lpNewFileName);
        }

        HANDLE PlatformApi::CreateFileA( _In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile )
        {
          return ::CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
        }

        int PlatformApi::fopen_s( _Outptr_result_maybenull_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode )
        {
          return ::fopen_s(_File,_Filename,_Mode);
        }

	FILE * PlatformApi::_fsopen(const char *filename, const char *mode, int shflag)
	{
          return ::_fsopen(filename, mode, shflag);
	}

        size_t PlatformApi::fread( void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File )
        {
          return ::fread(_DstBuf,_ElementSize,_Count,_File);
        }

        int PlatformApi::feof( _In_ FILE * _File )
        {
          return ::feof(_File);
        }

        int PlatformApi::fclose( _Inout_ FILE * _File )
        {
          return ::fclose(_File);
        }

        int PlatformApi::SHCreateDirectoryExA( _In_opt_ HWND hwnd, _In_ LPCSTR pszPath, _In_opt_ const SECURITY_ATTRIBUTES *psa )
        {
          return ::SHCreateDirectoryExA(hwnd,pszPath, psa);
        }
        
        int PlatformApi::fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin)
        {
          return ::fseek(_File, _Offset, _Origin);
        }

        long PlatformApi::ftell(_Inout_ FILE * _File)
        {
          return ::ftell(_File);
        }

        void PlatformApi::rewind(_Inout_ FILE * _File)
        {
          return ::rewind(_File);
        }

        size_t PlatformApi::fwrite(_In_reads_bytes_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File)
        {
          return ::fwrite(_Str, _Size, _Count, _File);
        }

		int PlatformApi::fflush(FILE * stream)
		{
		  return ::fflush(stream);
		}

        void PlatformApi::_chdir(const char * path)
        {
          ::SetCurrentDirectoryA(path);
        }

        int PlatformApi::rename(const char * oldPath, const char * newPath)
        {
          return ::rename(oldPath, newPath);
        }
      }
    }
  }
}