#pragma once

#include "kernel/iargumentinfo.h"

namespace Uniteller
{
	namespace Framework
	{
		namespace Kernel
		{

			interface IGenerationInfo : public IExportable
			{
			public:
				virtual IArgumentInfo * QueryArgument(const char * szName) = 0;
				virtual IArgumentInfo * PeekArgument(const char * szName) = 0;
				virtual int QueryArgumentIndex(const char * szName) = 0;
				virtual void AddArgument(IArgumentInfo * arg) = 0;
				virtual VariantType QueryArgumentType(const char * szName) = 0;
				virtual IMessage * MakeMessage(event_t kind, int generation) = 0;
			};

		}
	}
}

