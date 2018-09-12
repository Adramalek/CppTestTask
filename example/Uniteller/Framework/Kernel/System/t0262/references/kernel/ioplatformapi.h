#pragma once
#include <iostream>
#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Io
      {
        static const char * ApiId = "FileSystem";

        class IIoPlatformApi : public IExportable
        {
        public:
          virtual int fopen_s(_Outptr_result_maybenull_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode) = 0;
          virtual size_t fread(void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File) = 0;
          virtual int feof(_In_ FILE * _File) = 0;
          virtual int fclose(_Inout_ FILE * _File) = 0;
          virtual int fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin) = 0;
          virtual long ftell(_Inout_ FILE * _File) = 0;
          virtual void rewind(_Inout_ FILE * _File) = 0;
          virtual size_t fwrite(_In_reads_bytes_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File) = 0;
					virtual int fflush(FILE * stream) = 0;
          virtual FILE *_fsopen(const char *filename, const char *mode, int shflag) = 0;
          virtual void _chdir(const char * path) = 0;
        };

      } // пространство имен CommonApi
    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
