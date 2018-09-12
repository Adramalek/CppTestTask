// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию коллекции-перечисления

#pragma once

#include "exportable.h"
#include "ienumeration.h"
#include <vector>
#include <list>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      template <class X, class Y>
      inline  X ConvertType(Y & value)
      {
        return (X)value;
      }

      /// <summary>
      /// Интерфейс перечисления
      /// </summary>
      template <class T, class Y>
      class VectorEnumeration : public Exportable<IEnumeration<T>>
      {
      private:
        std::vector<Y> m_Items;
      public: // Методы
				/// <summary>
				/// Возвращает число элементов в перечислении
				/// </summary>
        const size_t GetCount() const
        {
          return m_Items.size();
        }
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        T GetItem(int index)
        {
          return ConvertType<T, Y>(m_Items[index]);
        }
				/// <summary>
				/// Добавляет элемент в перечисление
				/// </summary>
        void AddItem(T item)
        {
          m_Items.push_back(item);
        }        
				/// <summary>
				/// Добавляет несколько элементов в перечисление
				/// </summary>
        void AddRange(const std::list<Y> & range)
        {
          m_Items.insert(m_Items.end(), range.begin(), range.end());
        }
      };

      template <>
      inline const char * ConvertType(std::string & value)
      {
        return value.c_str();
      }


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
