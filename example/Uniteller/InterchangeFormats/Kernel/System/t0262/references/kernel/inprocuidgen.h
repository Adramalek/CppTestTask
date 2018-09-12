// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовый интерфейс генератора уникальных идентификаторов

#pragma once

#include "iuidgen.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Базовый интерфейс генератора уникальных идентификаторов
      /// </summary>
      class InprocUnicalIdGenerator : public Exportable<IUnicalIdGenerator>
      {
      private:
				// Последний сгенерированный элемент
        int m_nLastGeneratedValue;
        std::string m_Value;
      public:
        InprocUnicalIdGenerator() : m_nLastGeneratedValue(0)
        {
        }
        /// <summary>
        /// Возвращает уникальный идентификатор
        /// </summary>
        /// <returns> Уникальный идентификатор </returns>
        address GetUnicalId() 
        {
          ++m_nLastGeneratedValue;
          m_Value = std::to_string(m_nLastGeneratedValue);
          return m_Value.c_str();
        }
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller