#pragma once

#include "kernel/systemobject.h"
#include "Uniteller.Framework.Kernel.System.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      namespace System
      {

        class Machine : public LibraryImpl
        {
        public:
          BEGIN_HANDLERS_MAP()
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::ReplaceAll,  &Machine::ReplaceAllHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::Split, &Machine::SplitHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::TrimLeft, &Machine::TrimLeftHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::TrimRight, &Machine::TrimRightHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::Trim, &Machine::TrimHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::UnpackFirst, &Machine::UnpackFirstHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::UnpackLast, &Machine::UnpackLastHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::MatchFormat, &Machine::MatchFormatHandler);
            REGISTER_HANDLER("Idle", "Idle", Protocol::G1::Codes::GetLength, &Machine::GetLengthHandler);
          END_HANDLERS_MAP()
        public:
          explicit Machine(IKernelApi * api) : LibraryImpl("Uniteller.Framework.Kernel.System", api)
          {
          }
        protected:
          DECLARE_CHAIN_HANDLER(ReplaceAllHandler, Protocol::G1::ReplaceAll);
          DECLARE_CHAIN_HANDLER(SplitHandler, Protocol::G1::Split);
          DECLARE_CHAIN_HANDLER(TrimLeftHandler, Protocol::G1::TrimLeft);
          DECLARE_CHAIN_HANDLER(TrimRightHandler, Protocol::G1::TrimRight);
          DECLARE_CHAIN_HANDLER(TrimHandler, Protocol::G1::Trim);
          DECLARE_CHAIN_HANDLER(UnpackFirstHandler, Protocol::G1::UnpackFirst);
          DECLARE_CHAIN_HANDLER(UnpackLastHandler, Protocol::G1::UnpackLast);
          DECLARE_CHAIN_HANDLER(MatchFormatHandler, Protocol::G1::MatchFormat);
          DECLARE_CHAIN_HANDLER(GetLengthHandler, Protocol::G1::GetLength);
        };

      }
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller