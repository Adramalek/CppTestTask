#pragma once

#include <map>
#include <string>
#include "smartpointer.h"
#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      /// <summary>
      /// Шаблонная реализация класса контейнер свойств
      /// </summary>
      template <class T>
      class ExportableDictionary
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;
      private:
        std::map<std::string, T> m_Variables;
        typedef typename std::map<std::string, T>::iterator iterator;
      public: 
        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T GetItem(const std::string & s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
            return it->second;
          }
          return NULL;
        }

        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T GetItem(const char * s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
            return it->second;
          }
          return NULL;
        }  

        /// <summary>
        /// Добавляет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const std::string& s, T value)
        {
          iterator it = m_Variables.find(s);
          if (it != m_Variables.end())
          {           
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));

        }

        /// <summary>
        /// Позволяет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const char* s, T value)
        {
          iterator it = m_Variables.find(s);
          if (it != m_Variables.end())
          {            
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// Позволяет очистить контейнер свойств
        /// </summary>
        void Clear()
        {
          m_Variables.clear();
        }

        ~ExportableDictionary()
        {
          Clear();
        }
      };

      /// <summary>
      /// Шаблонная реализация класса контейнер свойств для указателей
      /// </summary>
      template <class T>
      class ExportableDictionary<T *>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;
      private:
        std::map<std::string, T *> m_Variables;
        typedef typename std::map<std::string, T *>::iterator iterator;
      public:

        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T * GetItem(const std::string & s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
              T * p=it->second;
              if (p)
                p->AddRef(); // Увеличиваем счетчик ссылок, прежде чем вернуть значение
              return p;
          }
          return NULL;
        }

        /// <summary>
        /// Осуществляет поиск по коллекции
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <returns></returns>
        T * GetItem(const char * s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
            {
              T * p=it->second;
              if (p)
                p->AddRef(); // Увеличиваем счетчик ссылок, прежде чем вернуть значение
              return p;
            }
          return NULL;
        }  

        /// <summary>
        /// Добавляет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const std::string& s, T * value)
        {
          iterator it = m_Variables.find(s);
          value->AddRef();
          if (it != m_Variables.end())
          {            
            it->second->Release();
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
          
        }

        /// <summary>
        /// Позволяет в коллекцию элемент
        /// </summary>
        /// <param name="s">Имя ключа</param>
        /// <param name="value">Значение</param>
        void Add(const char* s, T * value)
        {
          iterator it = m_Variables.find(s);
          value->AddRef();
          if (it != m_Variables.end())
          {            
            it->second->Release();
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// Позволяет очистить контейнер свойств
        /// </summary>
        void Clear()
        {
          for (iterator it=m_Variables.begin(); it!=m_Variables.end();++it)
          {
            T * p=it->second;
            if (p)
              p->Release();
          }
          m_Variables.clear();
        }

        ~ExportableDictionary<T *>()
        {
          Clear();
        }
      };
   
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller