#pragma once

#include "kernel/exportable.h"
#include "kernel/imessage.h"

namespace Uniteller
{
	namespace Framework
	{
		namespace Kernel
		{
			interface IArgumentInfo : public IExportable
			{
			public:
        // индекс аргумента
  			READONLY_PROPERTY_DECLARATION(int, Index);
        // имя
			  PROPERTY_DECLARATION_STRING(Name);				
				//PROPERTY_DECLARATION_STRING(TypeId, имя типа);
        // тип для контроля
        PROPERTY_DECLARATION(VariantType, Type);
        // реальный тип
        PROPERTY_DECLARATION(VariantType, RealType);
				
			  virtual IVariant * GetDefaultValue() = 0;
			  virtual void SetDefaultValue(IVariant * value) = 0;
			};
						
		}
	}
}

