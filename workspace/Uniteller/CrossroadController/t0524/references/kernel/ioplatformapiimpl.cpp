#include "ioplatformapiimpl.h"
#ifdef __GNUG__
#include <unistd.h>
#else
#include <direct.h>
#endif

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Io
      {
        GlobalPointer<IIoPlatformApi, PlatformApi> Platform;

        PlatformApi::PlatformApi(void)
        {
        }

        PlatformApi::~PlatformApi(void)
        {
        }

        int PlatformApi::fopen_s( _Outptr_result_maybenull_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode )
        {
          return ::fopen_s(_File,_Filename,_Mode);
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

        FILE * PlatformApi::_fsopen(const char *filename, const char *mode, int shflag)
        {
          return ::_fsopen(filename, mode, shflag);
        }

        void PlatformApi::_chdir(const char * path)
        {
#ifndef __GNUG__
          ::_chdir(path);
#else
          chdir(path);
#endif
        }
      }
    }
  }
}
