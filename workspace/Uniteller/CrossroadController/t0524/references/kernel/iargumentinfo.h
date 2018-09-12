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

                          // тип
			  PROPERTY_DECLARATION(VariantType, Type);
				
			  virtual IVariant * GetDefaultValue() = 0;
			  virtual void SetDefaultValue(IVariant * value) = 0;
			};
						
		}
	}
}

