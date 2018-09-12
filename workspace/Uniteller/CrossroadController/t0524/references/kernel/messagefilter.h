// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс сообщения, передаваемого по шине передачи сообщений

#pragma once

#include "imessagefilter.h"
#include <set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#ifndef __GNUG__
#include "avltree.h"
#else
  #include "linux/messagefilter.h"
  #define index_set std::set
#endif // __GNUG__

#ifndef __GNUG__
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      /// <summary>
      /// Реализация фильтра сообщений
      /// </summary>
      class MessageFilter : public Exportable<IMessageFilter>
      {
      private:
				index_set<int> m_Filter;
				typedef index_set<int>::const_iterator iterator;
        std::mutex mx;
      public:
        /// <summary>
        /// Конструктор. По-умолчанию устанавливает тип фильтрации в инклюзивный
        /// <summary>
				MessageFilter() : m_IsExclusive(false)
        {
        }
        // является ли фильтр эксклюзивным
        PROPERTY_IMPLEMENTATION(bool, IsExclusive);
        /// <summary>
        /// Позволяет очистить перечисление
        /// </summary>
        void Clear()
        {
          std::unique_lock<std::mutex> lk(mx);
          m_Filter.clear();
        }
        /// <summary>
        /// Позволяет добавить элемент в перечисление (в конец)
        /// </summary>
        /// <param name="value">Значение, добавляемое в перечисление</param>
        void Add(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
					m_Filter.insert(value);
        }
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        int GetItem(int index)
        {
          std::unique_lock<std::mutex> lk(mx);
          return m_Filter[index];
        }
        /// <summary>
        /// Позволяет определить индекс значения в множестве, если оно ему принадлежит
        /// </summary>
        /// <param name="value">Значение для поиска в перечислении</param>
        /// <param name="startIndex">Начинать поиск с элемента с индексом</param>
        /// <returns>Индекс найденного вхождения value или -1 в случае, если такового нет</returns>
        int IndexOf(const int & value, const int /*startIndex*/ = 0)
        {
          std::unique_lock<std::mutex> lk(mx);
					iterator i = m_Filter.find(value);
					if (i != m_Filter.end())
					{
						size_t pos = i - m_Filter.begin();
						return pos;
					}
          return -1;
        }
        /// <summary>
        /// Позволяет понять принадлежит ли указанное значение множеству
        /// </summary>
        bool Contains(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
					iterator i = m_Filter.find(value);
					const iterator e = m_Filter.end();
					if (i != e)
						return true;

				  int code = value & 0xFFFF0000;
					i = m_Filter.find(code);
					return (i != e);
        }
        const size_t GetCount() const
        {
					return m_Filter.size();
        }
        /// <summary>
        /// Позволяет проверить код сообщения, на пропуск в фильтром
        /// </summary>
        /// <param name="message">Сообщение для проверки на пропуск фильтром</param>
        /// <returns>true - если сообщение пропущено фильтром, false - иначе </returns>
        bool Check(int message)
        {
          return m_IsExclusive ? !Contains(message) : Contains(message) || Contains(0);
        }
      };


    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
#endif
