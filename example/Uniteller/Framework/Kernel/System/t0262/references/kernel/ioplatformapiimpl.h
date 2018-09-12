#pragma once

#include "ioplatformapi.h"
#include "globalpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Io
      {

        class PlatformApi : public Exportable<IIoPlatformApi>
        {
        public:
          PlatformApi(void);
          ~PlatformApi(void);

          int fopen_s(_Outptr_result_maybenull_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode);
          size_t fread(void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
          int feof(_In_ FILE * _File);
          int fclose(_Inout_ FILE * _File);
          int fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
          long ftell(_Inout_ FILE * _File);
          void rewind(_Inout_ FILE * _File);
          size_t fwrite(_In_reads_bytes_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
					int fflush(FILE * stream);
          FILE *_fsopen(const char *filename, const char *mode, int shflag);
          void _chdir(const char * path);
        };

        extern GlobalPointer<IIoPlatformApi, PlatformApi> Platform;

      }
    }
  }
}
