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
#ifdef __GNUG__
#if __GNUC__ < 5 
      long _InterlockedIncrement(long * x);
      long _InterlockedDecrement(long * x);
#endif
#endif

      /// <summary>
      /// Базовая реализация экспортируемого объекта
      /// <summary>
      template <class T>
      class Exportable : public T
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;
        // Число ссылок
        long m_nReferences;
      public:
        /// <summary>
        /// Конструктор, устанавливает счетчик ссылок в единицу
        /// </summary>
        Exportable() : m_nReferences(1)
        {
        }

        /// <summary>
        /// Увеличивает счетчик ссылок на экспортированный объект на единицу
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
        long AddRef() override
        { 
#ifndef __GNUG__
          return _InterlockedIncrement(&m_nReferences); // ++m_nReferences;
#else
#if __GNUC__ < 5 
          return _InterlockedIncrement(&m_nReferences); 
#else
          __sync_fetch_and_add(&m_nReferences, 1);
          return m_nReferences;
#endif
#endif
        }
        /// <summary>
        /// Уменьшает счетчик ссылок на экспортированный объект на единицу 
        /// </summary>
        /// <returns>Возвращает текущее значение счетчика ссылок.</returns>
        long Release() override
        {			
#ifndef __GNUG__		
          if (_InterlockedDecrement(&m_nReferences) == 0)
#else
#if __GNUC__ < 5 
          if (_InterlockedDecrement(&m_nReferences) == 0)
#else
          if (__sync_fetch_and_sub(&m_nReferences, 1) == 1)
#endif
#endif
          {
            delete this;
            return 0;
          }
          return m_nReferences;
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
