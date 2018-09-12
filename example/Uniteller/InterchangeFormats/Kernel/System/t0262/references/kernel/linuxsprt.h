#pragma once

#include <stdexcept>
#include <stdlib.h>
#include <inttypes.h>
#include <cstring>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <sstream>
#include <stdint.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#ifdef __GNUG__
#include <errno.h>
#endif

#if __GNUC__ < 5
#include <string>
#include <bits/basic_string_hash.h>
#endif

#ifndef __x86_64__
typedef long long  int64_t;
typedef unsigned long long   uint64_t;
#endif

#define __int64 long long 
#define _strtoui64 strtoull

#ifndef ULONG_MAX
#define ULONG_MAX 0xffffffffUL
#endif

#ifndef LONG_MIN
#define LONG_MIN (-2147483647L - 1)
#endif

#ifndef LONG_MAX
#define LONG_MAX 2147483647L
#endif

#define _UI64_MAX (unsigned __int64)0xffffffffffffffffULL//ui64
#define __int16 int16_t
#define __int8 char
#define _TRUNCATE ((unsigned int)-1)

#define errno_t int

// Совместимость с атрибутами MSVC
#define _Outptr_result_maybenull_
#define _In_z_
#define _In_
#define _Inout_
#define _In_reads_bytes_(x)
#define _Inout_opt_
#define _In_opt_
#define _Field_z_
#define _Out_writes_bytes_opt_(x)

// Совместимость с типами Win32
typedef void * HANDLE;
typedef HANDLE * PHANDLE;
typedef const char * LPCTSTR;
typedef void * HMODULE;
typedef unsigned long * ULONG_PTR;
typedef long * LONG_PTR;

typedef unsigned char UCHAR;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL            *PBOOL;
typedef BOOL             *LPBOOL;
typedef BYTE            *PBYTE;
typedef BYTE             *LPBYTE;
typedef int             *PINT;
typedef int              *LPINT;
typedef WORD            *PWORD;
typedef WORD             *LPWORD;
typedef long             *LPLONG;
typedef DWORD           *PDWORD;
typedef DWORD            *LPDWORD;
typedef void             *LPVOID;
typedef const void       *LPCVOID;
typedef void * PVOID;
typedef char * LPSTR;
typedef void * HWND;
typedef char CHAR;
typedef short SHORT;
typedef const char * LPCSTR;
typedef const char * LPCTSTR;
typedef const char * LPTSTR;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef unsigned long long ULONGLONG;
typedef unsigned long ULONG;
typedef unsigned long		*PULONG;
typedef long LONG;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef INT32_MAX
#define INT32_MAX 0x7fffffff
#endif

#ifndef INT32_MIN
#define INT32_MIN (-INT32_MAX - 1) 
#endif


#define INFINITE            0xFFFFFFFF  // Infinite timeout

#define _SH_DENYRW      0x10    /* deny read/write mode */
#define _SH_DENYWR      0x20    /* deny write mode */
#define _SH_DENYRD      0x30    /* deny read mode */
#define _SH_DENYNO      0x40    /* deny none mode */
#define _SH_SECURE      0x80    /* secure mode */

#define STD_INPUT_HANDLE (DWORD)-10
#define STD_OUTPUT_HANDLE (DWORD)-11
#define STD_ERROR_HANDLE (DWORD)-12

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        } DUMMYSTRUCTNAME;
        PVOID Pointer;
    } DUMMYUNIONNAME;

    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

#define STATUS_WAIT_0                           ((DWORD   )0x00000000L) 
#define STATUS_ABANDONED_WAIT_0          ((DWORD   )0x00000080L)  

#define WAIT_FAILED ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )

typedef enum _FINDEX_INFO_LEVELS {
    FindExInfoStandard,
    FindExInfoBasic,
    FindExInfoMaxInfoLevel
} FINDEX_INFO_LEVELS;

#define FIND_FIRST_EX_CASE_SENSITIVE   0x00000001
#define FIND_FIRST_EX_LARGE_FETCH      0x00000002

typedef enum _FINDEX_SEARCH_OPS {
    FindExSearchNameMatch,
    FindExSearchLimitToDirectories,
    FindExSearchLimitToDevices,
    FindExSearchMaxSearchOp
} FINDEX_SEARCH_OPS;

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

#define MAX_PATH          1024

typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    _Field_z_ CHAR   cFileName[ MAX_PATH ];
    _Field_z_ CHAR   cAlternateFileName[ 14 ];
#ifdef _MAC
    DWORD dwFileType;
    DWORD dwCreatorType;
    WORD  wFinderFlags;
#endif
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
} SMALL_RECT, *PSMALL_RECT;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD dwSize;
    COORD dwCursorPosition;
    WORD  wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

#define KERNEL_EXPORT

#ifndef __INTRINSIC_DEFINED__InterlockedIncrement
inline long  _InterlockedIncrement(long volatile * m_nReferences)
{
  return __sync_fetch_and_add(m_nReferences, 1);
}
#endif

#ifndef __INTRINSIC_DEFINED__InterlockedDecrement
inline long  _InterlockedDecrement(long volatile * m_nReferences)
{
  __sync_fetch_and_sub(m_nReferences, 1);
  return *m_nReferences;
}
#endif

#ifndef _TIME_H__S
inline int localtime_s(struct tm * _tm, const time_t * time)
{
  if (time==NULL)
    return -1;
  *_tm = *localtime(time);
  return 0;
}
#endif

inline errno_t gmtime_s(struct tm * _tm, const time_t * time)
{
  if (!time)
    {

		_tm->tm_sec=-1;
		_tm->tm_min=-1;
		_tm->tm_hour=-1;
		_tm->tm_mday=-1;
		_tm->tm_mon=-1;
		_tm->tm_year=-1;
		_tm->tm_wday=-1;
		_tm->tm_yday=-1;
		return -1;
	}
  *_tm = *gmtime(time);
  return 0;
}

inline int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr)
{
    int written;
    va_list argcopy;
    __va_copy(argcopy, argptr); //копируем список аргументов, чтобы не портить стек
    if (count!=_TRUNCATE)
    {
        written=vsnprintf(buffer, sizeOfBuffer, format, argptr);
    }
    else
    {
        int factNum=0;
        factNum = vsnprintf(0, 0, format, argcopy);
        if ((factNum + strlen(buffer)+1) <= sizeOfBuffer)
        {
            written= vsnprintf(buffer, sizeOfBuffer, format, argptr);
        }
        else
        {
            int size=sizeOfBuffer-strlen(buffer);
            /*written=*/vsnprintf(buffer, size, format, argptr);
            written=-1; //нормальное поведение vsnprintf_s в данном случае
        }
    }
    va_end(argcopy);
    return written;
}

inline int fopen_s(FILE **f, const char *name, const char *mode)
{
   int ret = 0;
   *f = fopen(name, mode);
   /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
   if (!*f)
       ret = errno;
   return ret;
}

inline FILE * _fsopen(const char *filename, const char *mode, int shflag)
{
  return ::fopen(filename, mode);
}


inline void Sleep(int x)
{
  usleep(x * 1000);
}

inline int strcpy_s(char * _Dst, int _SizeInBytes, const char * _Src)
{
  strcpy(_Dst, _Src);
  return 0;
}

namespace std
{
  template <typename T>
  std::string to_string(T value)
  {
    //create an output string stream
    std::ostringstream os;

    //throw the value into the string stream
    os << value;

    //convert the string stream into a string and return
    return os.str();
  }
}

#define sprintf_s(buffer, buffer_size, stringbuffer, ...) (sprintf(buffer, stringbuffer, __VA_ARGS__))

// Глушим ASSERT-ы
#define _ASSERTE(x)

#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_DEVICE 0x40

#define ERROR_SUCCESS 0
#define ERROR_FILE_NOT_FOUND             2
#define ERROR_ACCESS_DENIED              5
#define ERROR_SHARING_VIOLATION          32
#define ERROR_CURRENT_DIRECTORY          16
#define ERROR_NETWORK_ACCESS_DENIED      65
#define ERROR_DISK_FULL                  112
#define ERROR_HANDLE_DISK_FULL           39
#define ERROR_ALREADY_EXISTS             183
#define ERROR_INVALID_DRIVE              15
#define ERROR_DEV_NOT_EXIST              55
#define ERROR_PATH_NOT_FOUND             3
#define ERROR_NO_MORE_FILES              18
#define ERROR_BUFFER_OVERFLOW			 111
#define ERROR_NO_DATA					 232
#define ERROR_NOT_SUPPORTED				 50
#define ERROR_INVALID_DATA				 13
#define ERROR_INVALID_PARAMETER          87			

#define GENERIC_READ                     0x80000000
#define OPEN_EXISTING       3
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

#ifndef TCP_NODELAY
#define TCP_NODELAY						 0x0001
#endif

typedef union _ULARGE_INTEGER 
{
  struct {
    DWORD LowPart;
    ULONG  HighPart;
  };
  struct {
    DWORD LowPart;
    ULONG  HighPart;
  } u;
  ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

typedef void * HKEY;
typedef HKEY * PHKEY;

typedef ULONG REGSAM; 

#define CONST const

typedef struct _STARTUPINFOA {
    DWORD   cb;
    LPSTR   lpReserved;
    LPSTR   lpDesktop;
    LPSTR   lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

#define MAX_ADAPTER_ADDRESS_LENGTH 8
#define MAX_ADAPTER_DESCRIPTION_LENGTH 128
#define MAX_ADAPTER_NAME_LENGTH 256

typedef struct {
	char String[4 * 4];
} IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;

typedef struct _IP_ADDR_STRING {
	struct _IP_ADDR_STRING  *Next;
	IP_ADDRESS_STRING      IpAddress;
	IP_MASK_STRING         IpMask;
	DWORD                  Context;
} IP_ADDR_STRING, *PIP_ADDR_STRING;

typedef struct _IP_ADAPTER_INFO {
	struct _IP_ADAPTER_INFO  *Next;
	DWORD                   ComboIndex;
	char                    AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
	char                    Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
	UINT                    AddressLength;
	BYTE                    Address[MAX_ADAPTER_ADDRESS_LENGTH];
	DWORD                   Index;
	UINT                    Type;
	UINT                    DhcpEnabled;
	PIP_ADDR_STRING         CurrentIpAddress;
	IP_ADDR_STRING          IpAddressList;
	IP_ADDR_STRING          GatewayList;
	IP_ADDR_STRING          DhcpServer;
	BOOL                    HaveWins;
	IP_ADDR_STRING          PrimaryWinsServer;
	IP_ADDR_STRING          SecondaryWinsServer;
	time_t                  LeaseObtained;
	time_t                  LeaseExpires;
} IP_ADAPTER_INFO, *PIP_ADAPTER_INFO;

typedef struct _IP_PER_ADAPTER_INFO {
	UINT            AutoconfigEnabled;
	UINT            AutoconfigActive;
	PIP_ADDR_STRING CurrentDnsServer;
	IP_ADDR_STRING  DnsServerList;
} IP_PER_ADAPTER_INFO, *PIP_PER_ADAPTER_INFO;

typedef void * HDESK;
typedef void * DEVMODE;
typedef DWORD ACCESS_MASK;

#define STARTF_USESHOWWINDOW 1
#define STARTF_USESTDHANDLES 2
#define SW_SHOWMAXIMIZED 0 
#define NORMAL_PRIORITY_CLASS 0
#define DESKTOP_CREATEWINDOW 1

#define REG_NONE                    ( 0 )   // No value type
#define REG_SZ                      ( 1 )   // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
                                            // (with environment variable references)
#define REG_BINARY                  ( 3 )   // Free form binary
#define REG_DWORD                   ( 4 )   // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
#define REG_LINK                    ( 6 )   // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware description
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10 )
#define REG_QWORD                   ( 11 )  // 64-bit number
#define REG_QWORD_LITTLE_ENDIAN     ( 11 )  // 64-bit number (same as REG_QWORD)

#define HKEY_CLASSES_ROOT                   (( HKEY ) (ULONG_PTR)((LONG)0x80000000) )
#define HKEY_CURRENT_USER                   (( HKEY ) (ULONG_PTR)((LONG)0x80000001) )
#define HKEY_LOCAL_MACHINE                  (( HKEY ) (ULONG_PTR)((LONG)0x80000002) )
#define HKEY_USERS                          (( HKEY ) (ULONG_PTR)((LONG)0x80000003) )
#define HKEY_PERFORMANCE_DATA               (( HKEY ) (ULONG_PTR)((LONG)0x80000004) )
#define HKEY_PERFORMANCE_TEXT               (( HKEY ) (ULONG_PTR)((LONG)0x80000050) )
#define HKEY_PERFORMANCE_NLSTEXT            (( HKEY ) (ULONG_PTR)((LONG)0x80000060) )


#define HKEY_CURRENT_CONFIG                 (( HKEY ) (ULONG_PTR)((LONG)0x80000005) )
#define HKEY_DYN_DATA                       (( HKEY ) (ULONG_PTR)((LONG)0x80000006) )
#define HKEY_CURRENT_USER_LOCAL_SETTINGS    (( HKEY ) (ULONG_PTR)((LONG)0x80000007) )


typedef struct _DCB {
  DWORD DCBlength;      /* sizeof(DCB)                     */
  DWORD BaudRate;       /* Baudrate at which running       */
  DWORD fBinary : 1;     /* Binary Mode (skip EOF check)    */
  DWORD fParity : 1;     /* Enable parity checking          */
  DWORD fOutxCtsFlow : 1; /* CTS handshaking on output       */
  DWORD fOutxDsrFlow : 1; /* DSR handshaking on output       */
  DWORD fDtrControl : 2;  /* DTR Flow control                */
  DWORD fDsrSensitivity : 1; /* DSR Sensitivity              */
  DWORD fTXContinueOnXoff : 1; /* Continue TX when Xoff sent */
  DWORD fOutX : 1;       /* Enable output X-ON/X-OFF        */
  DWORD fInX : 1;        /* Enable input X-ON/X-OFF         */
  DWORD fErrorChar : 1;  /* Enable Err Replacement          */
  DWORD fNull : 1;       /* Enable Null stripping           */
  DWORD fRtsControl : 2;  /* Rts Flow control                */
  DWORD fAbortOnError : 1; /* Abort all reads and writes on Error */
  DWORD fDummy2 : 17;     /* Reserved                        */
  WORD wReserved;       /* Not currently used              */
  WORD XonLim;          /* Transmit X-ON threshold         */
  WORD XoffLim;         /* Transmit X-OFF threshold        */
  BYTE ByteSize;        /* Number of bits/byte, 4-8        */
  BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
  BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
  char XonChar;         /* Tx and Rx X-ON character        */
  char XoffChar;        /* Tx and Rx X-OFF character       */
  char ErrorChar;       /* Error replacement char          */
  char EofChar;         /* End of Input character          */
  char EvtChar;         /* Received Event character        */
  WORD wReserved1;      /* Fill for now.                   */
} DCB, *LPDCB;

typedef struct _COMMTIMEOUTS {
  DWORD ReadIntervalTimeout;          /* Maximum time between read chars. */
  DWORD ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
  DWORD ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
  DWORD WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
  DWORD WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
} COMMTIMEOUTS, *LPCOMMTIMEOUTS;


typedef struct _COMSTAT {
  DWORD fCtsHold : 1;
  DWORD fDsrHold : 1;
  DWORD fRlsdHold : 1;
  DWORD fXoffHold : 1;
  DWORD fXoffSent : 1;
  DWORD fEof : 1;
  DWORD fTxim : 1;
  DWORD fReserved : 25;
  DWORD cbInQue;
  DWORD cbOutQue;
} COMSTAT, *LPCOMSTAT;

#define ERROR_NO_MORE_ITEMS              259L

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)

#define STANDARD_RIGHTS_ALL              (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)


#define KEY_QUERY_VALUE         (0x0001)
#define KEY_SET_VALUE           (0x0002)
#define KEY_CREATE_SUB_KEY      (0x0004)
#define KEY_ENUMERATE_SUB_KEYS  (0x0008)
#define KEY_NOTIFY              (0x0010)
#define KEY_CREATE_LINK         (0x0020)
#define KEY_WOW64_32KEY         (0x0200)
#define KEY_WOW64_64KEY         (0x0100)
#define KEY_WOW64_RES           (0x0300)

#define KEY_READ                ((STANDARD_RIGHTS_READ       |\
                                  KEY_QUERY_VALUE            |\
                                  KEY_ENUMERATE_SUB_KEYS     |\
                                  KEY_NOTIFY)                 \
                                  &                           \
                                 (~SYNCHRONIZE))


#define KEY_WRITE               ((STANDARD_RIGHTS_WRITE      |\
                                  KEY_SET_VALUE              |\
                                  KEY_CREATE_SUB_KEY)         \
                                  &                           \
                                 (~SYNCHRONIZE))

#define KEY_EXECUTE             ((KEY_READ)                   \
                                  &                           \
                                 (~SYNCHRONIZE))

#define KEY_ALL_ACCESS          ((STANDARD_RIGHTS_ALL        |\
                                  KEY_QUERY_VALUE            |\
                                  KEY_SET_VALUE              |\
                                  KEY_CREATE_SUB_KEY         |\
                                  KEY_ENUMERATE_SUB_KEYS     |\
                                  KEY_NOTIFY                 |\
                                  KEY_CREATE_LINK)            \
                                  &                           \
                                 (~SYNCHRONIZE))

#define GENERIC_WRITE                    (0x40000000L)


//
// Settable baud rates in the provider.
//

#define BAUD_075          ((DWORD)0x00000001)
#define BAUD_110          ((DWORD)0x00000002)
#define BAUD_134_5        ((DWORD)0x00000004)
#define BAUD_150          ((DWORD)0x00000008)
#define BAUD_300          ((DWORD)0x00000010)
#define BAUD_600          ((DWORD)0x00000020)
#define BAUD_1200         ((DWORD)0x00000040)
#define BAUD_1800         ((DWORD)0x00000080)
#define BAUD_2400         ((DWORD)0x00000100)
#define BAUD_4800         ((DWORD)0x00000200)
#define BAUD_7200         ((DWORD)0x00000400)
#define BAUD_9600         ((DWORD)0x00000800)
#define BAUD_14400        ((DWORD)0x00001000)
#define BAUD_19200        ((DWORD)0x00002000)
#define BAUD_38400        ((DWORD)0x00004000)
#define BAUD_56K          ((DWORD)0x00008000)
#define BAUD_128K         ((DWORD)0x00010000)
#define BAUD_115200       ((DWORD)0x00020000)
#define BAUD_57600        ((DWORD)0x00040000)
#define BAUD_USER         ((DWORD)0x10000000)

//
// Settable Data Bits
//

#define DATABITS_5        ((WORD)0x0001)
#define DATABITS_6        ((WORD)0x0002)
#define DATABITS_7        ((WORD)0x0004)
#define DATABITS_8        ((WORD)0x0008)
#define DATABITS_16       ((WORD)0x0010)
#define DATABITS_16X      ((WORD)0x0020)

//
// Settable Stop and Parity bits.
//

#define STOPBITS_10       ((WORD)0x0001)
#define STOPBITS_15       ((WORD)0x0002)
#define STOPBITS_20       ((WORD)0x0004)
#define PARITY_NONE       ((WORD)0x0100)
#define PARITY_ODD        ((WORD)0x0200)
#define PARITY_EVEN       ((WORD)0x0400)
#define PARITY_MARK       ((WORD)0x0800)
#define PARITY_SPACE      ((WORD)0x1000)

//
// Baud rates at which the communication device operates
//

#define CBR_110             110
#define CBR_300             300
#define CBR_600             600
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_19200           19200
#define CBR_38400           38400
#define CBR_56000           56000
#define CBR_57600           57600
#define CBR_115200          115200
#define CBR_128000          128000
#define CBR_256000          256000



#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

#define ONESTOPBIT          0
#define ONE5STOPBITS        1
#define TWOSTOPBITS         2

//
// DTR Control Flow Values.
//
#define DTR_CONTROL_DISABLE    0x00
#define DTR_CONTROL_ENABLE     0x01
#define DTR_CONTROL_HANDSHAKE  0x02

//
// RTS Control Flow Values
//
#define RTS_CONTROL_DISABLE    0x00
#define RTS_CONTROL_ENABLE     0x01
#define RTS_CONTROL_HANDSHAKE  0x02
#define RTS_CONTROL_TOGGLE     0x03


//
// Events
//

#define EV_RXCHAR           0x0001  // Any Character received
#define EV_RXFLAG           0x0002  // Received certain character
#define EV_TXEMPTY          0x0004  // Transmitt Queue Empty
#define EV_CTS              0x0008  // CTS changed state
#define EV_DSR              0x0010  // DSR changed state
#define EV_RLSD             0x0020  // RLSD changed state
#define EV_BREAK            0x0040  // BREAK received
#define EV_ERR              0x0080  // Line status error occurred
#define EV_RING             0x0100  // Ring signal detected
#define EV_PERR             0x0200  // Printer error occured
#define EV_RX80FULL         0x0400  // Receive buffer is 80 percent full
#define EV_EVENT1           0x0800  // Provider specific event 1
#define EV_EVENT2           0x1000  // Provider specific event 2

//
// Escape Functions
//

#define SETXOFF             1       // Simulate XOFF received
#define SETXON              2       // Simulate XON received
#define SETRTS              3       // Set RTS high
#define CLRRTS              4       // Set RTS low
#define SETDTR              5       // Set DTR high
#define CLRDTR              6       // Set DTR low
#define RESETDEV            7       // Reset device if possible
#define SETBREAK            8       // Set the device break line.
#define CLRBREAK            9       // Clear the device break line.

//
// PURGE function flags.
//
#define PURGE_TXABORT       0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT       0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR       0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR       0x0008  // Kill the typeahead buffer if there.

#define LPTx                0x80    // Set if ID is for LPT device

#define UCHAR unsigned char

#define _stricmp strcasecmp

#define WSAAPI
#define WINAPI
#define _Out_
#define FAR

typedef int                   SOCKET;
typedef unsigned long         u_long;
typedef unsigned short       u_short;
typedef const char * PCSTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

typedef struct addrinfo    ADDRINFOA;
typedef struct addrinfo * PADDRINFOA;
typedef hostent HOSTENT;

#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1

#define IPPROTO_IPV4 IPPROTO_TCP

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a & 0xff)) | ((WORD)((BYTE)(b & 0xff)) << 8)))

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128
typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char FAR *              lpVendorInfo;
} WSADATA, FAR * LPWSADATA;

#define SD_BOTH SHUT_RDWR

#define WSASYSNOTREADY                   10091L
#define WSAVERNOTSUPPORTED               10092L
#define WSANOTINITIALISED                10093L
#define WSAEINPROGRESS              EINPROGRESS
#define WSAEPROCLIM                      10067L
#define WSAEFAULT                        EFAULT
#define WSAENETDOWN                    ENETDOWN
#define WSAEACCES                        EACCES
#define WSAEADDRINUSE                EADDRINUSE
#define WSAEADDRNOTAVAIL          EADDRNOTAVAIL
#define WSAEINVAL                        EINVAL
#define WSAENOBUFS                      ENOBUFS
#define WSAENOTSOCK                    ENOTSOCK
#define WSAEISCONN                      EISCONN
#define WSAEMFILE                        EMFILE
#define WSAEOPNOTSUPP                EOPNOTSUPP
#define WSAEINTR                          EINTR
#define WSAECONNRESET                ECONNRESET
#define WSAEWOULDBLOCK              EWOULDBLOCK

#define ERROR_BUFFER_OVERFLOW 111

#ifdef __GNUG__
#if __GNUC__ < 5
namespace std
{
  inline int stoi(const std::string & s)
  {
    return atoi(s.c_str());
  }

  inline unsigned long long stoull( const std::string& str, size_t *pos = 0, int base = 10 )
  {
    return strtoull(str.c_str(), NULL, base);
  }

  inline unsigned long stoul( const std::string& str, size_t *pos = 0, int base = 10 )
  {
    return strtoul(str.c_str(), NULL, base);
  }
}
#endif
#endif
