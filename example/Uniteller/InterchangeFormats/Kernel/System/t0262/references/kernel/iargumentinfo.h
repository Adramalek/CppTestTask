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
        // ������ ���������
  			READONLY_PROPERTY_DECLARATION(int, Index);
        // ���
			  PROPERTY_DECLARATION_STRING(Name);				
				//PROPERTY_DECLARATION_STRING(TypeId, ��� ����);
        // ��� ��� ��������
        PROPERTY_DECLARATION(VariantType, Type);
        // �������� ���
        PROPERTY_DECLARATION(VariantType, RealType);
				
			  virtual IVariant * GetDefaultValue() = 0;
			  virtual void SetDefaultValue(IVariant * value) = 0;
			};
						
		}
	}
}

