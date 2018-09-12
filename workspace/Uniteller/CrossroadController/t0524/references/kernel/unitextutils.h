#pragma once

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      namespace UnitextUtils
      {
        inline void SkipSpaces(const char * & source)
        {
          while ((*source != '\n') && (*source != '\0') && (*source<=32)&& (*source>0))
            ++source;
        }

      }

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller