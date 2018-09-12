#pragma once
#ifndef __GNUG__
#include "stdafx.h"
#else
#include "kernel/linux/commonplatformapi.h"
#endif
#include "commonplatformapi.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace CommonApi
      {
        /// <summary>
        ///  ласс точки изол€ции Api платформы
        /// </summary>
        class PlatformApi : public Exportable<IPlatformApi>
        {
        public:
          PlatformApi(void) : m_nHandleCounter(0)
          {
          }
      
          /// <summary>
          /// 
          /// </summary>
          /// <returns></returns>
          DWORD GetLastError()
          {
            return ::GetLastError();
          }

          BOOL CloseFile(HANDLE hObject)  
          {
#ifndef __GNUG__
            return ::CloseHandle(hObject);
#else
            return ::CloseFile(hObject);
#endif
          }

          BOOL ReleaseEvent(HANDLE hObject) 
          {
#ifndef __GNUG__
            return ::CloseHandle(hObject);
#else
            return ::ReleaseEvent(hObject);
#endif
          }

          BOOL CloseHandle( HANDLE hObject )
          {
            return ::CloseHandle(hObject);
          }

          /// <summary>
          /// 
          /// </summary>
          /// <param name="nCount"></param>
          /// <param name="lpHandles"></param>
          /// <param name="bWaitAll"></param>
          /// <param name="dwMilliseconds"></param>
          /// <returns></returns>
          DWORD WaitForMultipleObjects( DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds )
          {
            return ::WaitForMultipleObjects(nCount, lpHandles, bWaitAll, dwMilliseconds);
          }

          BOOL CreatePipe( PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize )
          {
            return ::CreatePipe(hReadPipe, hWritePipe, lpPipeAttributes, nSize);
          }

          BOOL PeekNamedPipe( HANDLE hNamedPipe, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage )
          {
            return ::PeekNamedPipe( hNamedPipe, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage );
          }

          BOOL ReadFile( HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped )
          {
            return ::ReadFile( hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped );
          }

          HANDLE CreateEvent( LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCTSTR lpName )
          {
            return ::CreateEvent( lpEventAttributes, bManualReset, bInitialState, lpName );
          }

          BOOL SetEvent( HANDLE hEvent )
          {
            return ::SetEvent( hEvent );
          }

          BOOL ResetEvent( HANDLE hEvent )
          {
            return ::ResetEvent( hEvent );
          }

          DWORD WaitForSingleObject( HANDLE hHandle, DWORD dwMilliseconds )
          {
            return ::WaitForSingleObject( hHandle, dwMilliseconds );
          }

          HANDLE CreateHandle(const char *, const char *)
          {
            ++m_nHandleCounter; 
            return (HANDLE)m_nHandleCounter;
          }

          void ValidateHandle(HANDLE /*h*/)
          {
          }
          void ReleaseHandle(HANDLE /*h*/)
          {            
          }

          BOOL WriteFile(HANDLE hFile,
            LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
          {
            return ::WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
          }

        private:
          int m_nHandleCounter;
        };

        extern GlobalPointer<IPlatformApi, PlatformApi> Platform;

      }
    }
  }
}