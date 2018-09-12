// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию интерфейса экспортируемого из dll объекта
#pragma once

#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// Базовая реализация неразрушимого (перманентного) объекта
      /// <summary>
      template <class T>
      class Indestructible : public T
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;
      public:
        /// <summary>
        /// Конструктор, устанавливает счетчик ссылок в единицу
        /// </summary>
				Indestructible()
        {
        }

        /// <summary>
        /// Увеличивает счетчик ссылок на экспортированный объект на единицу
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
				long AddRef()
        {
					return 1;
        }
        /// <summary>
        /// Уменьшает счетчик ссылок на экспортированный объект на единицу 
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
				long Release()
        {					   
          return 1;
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller