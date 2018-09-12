#pragma once

#include "kernel/igenerationinfo.h"

namespace Uniteller
{
	namespace Framework
	{
		namespace Kernel
		{

			interface IMessageInfo : public IExportable
			{
			public:
                          // ��� ���������
				READONLY_PROPERTY_DECLARATION(event_t, Kind);
                          // ���������
				PROPERTY_DECLARATION(int, Priority);
                          // ������������ ��������
				PROPERTY_DECLARATION_STRING(Protocol);
                          // ��� ���������
				PROPERTY_DECLARATION_STRING(Name);
								
				virtual void AddGeneration(size_t gen, IGenerationInfo * info) = 0;
				virtual IGenerationInfo * QueryGeneration(size_t gen) = 0;
				virtual bool HasGeneration(size_t gen) = 0;
				virtual int QueryArgumentIndex(size_t gen, const char * arg) = 0;
        virtual VariantType QueryArgumentType(size_t gen, const char * arg) = 0;
				virtual IMessage * CreateMessage(size_t generation, int argc) = 0;
				virtual IArgumentInfo * QueryArgument(size_t gen, const char * szName) = 0;
				virtual IArgumentInfo * PeekArgument(size_t gen, const char * szName) = 0;
			};
		}
	}
}

