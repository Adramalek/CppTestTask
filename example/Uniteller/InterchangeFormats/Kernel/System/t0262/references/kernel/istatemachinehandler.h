#pragma once

#include "iregistrykey.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      interface IStateMachineHandler : public IExportable
      {
      public:
        // Класс обработчика
        PROPERTY_DECLARATION(unsigned __int8, HandlerClass);
        /// <summary>
        /// Вычисляет глубину вложенности секций Receive
        /// </summary>
        virtual unsigned __int8 CountReceiveStages() const = 0;
        /// <summary>
        /// Возвращает дескриптор обработчика
        /// </summary>
				virtual IRegistryKey * GetDescriptor() = 0;

				/// <summary>
				/// Требуется ли сохранять активатор
				/// </summary>
				//virtual bool IsActivator() const = 0;

        /// <summary>
        /// Обеспечивает обращение к секции дескриптора
        /// </summary>
        virtual IRegistryKey * GetSubKey(const char * key) = 0;

      };

    }
  }
}