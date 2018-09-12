#pragma once

#include <string>
#include <unordered_map>
#include <array>

#include "autoproperty.h" // Для совместимости со старыми версиями GCC

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Шаблонная реализация класса для парсинга команд в скрипте тестирования
      /// </summary>
#if (defined (__GNUG__) && (__GNUC__ < 5))
    template <class T, int Y>
#else
    template <class T, T Y>
#endif
      class IdentifierParser
      {
      private:
        std::unordered_map<std::string, T> m_Index; // Индекс
        typedef typename std::unordered_map<std::string, T>::iterator iterator;
        typedef typename std::unordered_map<std::string, T>::const_iterator const_iterator;
      public:

        /// <summary>
        /// Добавляет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const std::string& s, T value)
        {
          m_Index.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// Добавляет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const char* s, T value)
        {
          m_Index.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// Добавляет в коллекцию элемент
        /// </summary>
        /// <param name="value">Имя и значение</param>
        void Add(const std::pair<std::string, T> & value)
        {
          m_Index.insert(value);
        }

        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T Recognize(const std::string & s, const T dflt = Y) const
        {
          const_iterator it = m_Index.find(s);
          if (it!=m_Index.end())
            return it->second;
          return dflt;
        }

        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T Recognize(const char * s, const T dflt = Y) const
        {
          const_iterator it = m_Index.find(s);
          if (it!=m_Index.end())
            return it->second;
          return dflt;
        }  

        T operator[](const char * s) const
        {
          return Recognize(s);
        }

        T operator[](const std::string & s) const
        {
          return Recognize(s);
        }

        /// <summary>
        /// Конструктор
        /// </summary>
        IdentifierParser()
        {
        }

        /// <summary>
        /// Конструктор (для поддержки статической инициализации)
        /// </summary>
        template <size_t X>
        explicit IdentifierParser(const std::array<std::pair<std::string, T>, X> & args)
        {
          Add(args);
        }

        /// <summary>
        /// Добавляет в коллекцию переданные в args элементы
        /// </summary>
        /// <param name="args">Список элементов в форме пар для внесения в коллекцию</param>
				template <size_t X>
				void Add(const std::array<std::pair<std::string, T>, X> & args)
        {
          typename std::array<std::pair<std::string, T>, X>::const_iterator i = args.begin();
          typename std::array<std::pair<std::string, T>, X>::const_iterator e = args.end();
          for (; i!=e; ++i)
          {
            m_Index.insert(*i);
          }
        }

      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
