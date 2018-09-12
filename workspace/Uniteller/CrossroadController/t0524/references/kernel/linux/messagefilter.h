// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс сообщения, передаваемого по шине передачи сообщений

#pragma once

#include <set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

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
        std::map<int, size_t> m_Index;
        std::vector<int> m_Filter;
        typedef std::map<int, size_t>::iterator index_iterator;
        typedef std::map<int, size_t>::const_iterator const_index_iterator;
        std::mutex mx;
      public:
        /// <summary>
        /// Конструктор. По-умолчанию устанавливает тип фильтрации в инклюзивный
        /// <summary>
        MessageFilter()
        {
          m_IsExclusive = false;
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
          m_Index.clear();
        }
        /// <summary>
        /// Позволяет добавить элемент в перечисление (в конец)
        /// </summary>
        /// <param name="value">Значение, добавляемое в перечисление</param>
        void Add(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
          const_index_iterator i = m_Index.find(value);
          if (i == m_Index.end())
          {
            size_t index = m_Filter.size();
            m_Filter.push_back(value);
            m_Index.insert(std::make_pair(value,index));
          }
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
          const_index_iterator i = m_Index.find(value);
          if (i != m_Index.end())
            return (int)i->second;
          return -1;
        }
        /// <summary>
        /// Позволяет понять принадлежит ли указанное значение множеству
        /// </summary>
        bool Contains(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
          const_index_iterator i = m_Index.find(value);
          bool result = (i != m_Index.end());
          if (!result)
          {
            int code = value & 0xFFFF0000;
            i = m_Index.find(code);
            return (i != m_Index.end());
          }
          return result;
        }
        const size_t GetCount() const
        {
          return m_Index.size();
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
