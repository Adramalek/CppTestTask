#pragma once

#ifndef __GNUG__
#include "stdafx.h"
#endif

#include "kernel/interceptor.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace CommonApi
      {
        static const char * ApiId = "CommonApi";

        /// <summary>
        /// Интерфейс блока перехватываемых функций API общего назначения
        /// </summary>
        class IPlatformApi : public IExportable
        {
        public:

          virtual DWORD GetLastError() = 0;
          
          virtual BOOL CloseHandle(HANDLE hObject) = 0;   
          virtual BOOL CloseFile(HANDLE hObject) = 0;   
          virtual BOOL ReleaseEvent(HANDLE hObject) = 0;   

          virtual DWORD WaitForMultipleObjects(DWORD nCount,
            const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds) = 0;

          virtual BOOL CreatePipe(
            PHANDLE hReadPipe,
            PHANDLE hWritePipe,
            LPSECURITY_ATTRIBUTES lpPipeAttributes,
            DWORD nSize
            ) = 0;

          virtual BOOL PeekNamedPipe(
            HANDLE hNamedPipe,
            LPVOID lpBuffer,
            DWORD nBufferSize,
            LPDWORD lpBytesRead,
            LPDWORD lpTotalBytesAvail,
            LPDWORD lpBytesLeftThisMessage
            ) = 0;

          virtual BOOL ReadFile(
            HANDLE hFile,
            LPVOID lpBuffer,
            DWORD nNumberOfBytesToRead,
            LPDWORD lpNumberOfBytesRead,
            LPOVERLAPPED lpOverlapped
            ) = 0;
          
          virtual HANDLE CreateEvent(
            LPSECURITY_ATTRIBUTES lpEventAttributes,
            BOOL bManualReset,
            BOOL bInitialState,
            LPCTSTR lpName
            ) = 0;

          virtual BOOL SetEvent(HANDLE hEvent) = 0;

          virtual BOOL ResetEvent(HANDLE hEvent) = 0;

          virtual DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) = 0;

          /// <summary>
          /// 
          /// </summary>
          virtual HANDLE CreateHandle(const char * szAllocator, const char * szDebugInfo) = 0;
          /// <summary>
          /// 
          /// </summary>
          virtual void ValidateHandle(HANDLE h) = 0;

          /// <summary>
          /// Использовать для освобождения хендлов, распределенных 
          /// </summary>
          virtual void ReleaseHandle(HANDLE h) = 0;

          virtual BOOL WriteFile(HANDLE hFile,
            LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) =  0;

        };

      } // пространство имен CommonApi
    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
