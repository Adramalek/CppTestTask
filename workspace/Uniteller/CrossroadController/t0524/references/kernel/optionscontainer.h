// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс контейнера свойств

#pragma once

#include "ioptionscontainer.h"
#include "variant.h"
#include "enumeration.h"
#include "linq"
#include <map>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// Базовая реализация контейнера свойств
      /// </summary>
      template <class T>
      class OptionsContainer : public Exportable<T>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsOptionsContainer OnlyOptionsContainer;

        template <class Q>
        friend class OptionsLoader;
        template <class Q>
        friend class OptionsSerializer;
      private:
        std::map<std::string, Variant *> m_Options;
        typedef std::map<std::string, Variant *>::iterator iterator;
        typedef std::map<std::string, Variant *>::const_iterator const_iterator;
      public: // Методы
        /// <summary>
        /// Конструктор
        /// <summary>
        OptionsContainer()
        {
        }
        ~OptionsContainer()
        {
          Clear();
        }

        /// <summary>
        /// Позволяет проверить установлена ли указанная в параметре name опция
        /// </summary>
        /// <param name="name">Имя опции.</param>
        /// <returns>true, если опция установлена (передана в командной строке), false - иначе</returns>
        bool IsSet(const char * name) const
        {
          const_iterator i = m_Options.find(name);
          return (i != m_Options.end());
        }
        /// <summary>
        /// Возвращает значение опции
        /// </summary>
        /// <param name="name">Имя опции для получения ее значения.</param>
        /// <returns>Значение настройки, соответствующей имени name</returns>
        IVariant * GetOption(const char * name) const
        {
          const_iterator i = m_Options.find(name);
          if (i != m_Options.end())
          {
            if (i->second)
            {
              i->second->AddRef();
              return i->second;
            }
          }
          return NULL;
        }
        /// <summary>
        /// Возвращает имена опций
        /// </summary>
        /// <returns>Перечисление имен опций</returns>
        IEnumeration<const char *> * GetOptionNames() const
        {
          SmartPointer<VectorEnumeration<const char *, std::string>> result;
          result.Create();
          foreach(const_iterator, i, m_Options)
          {
            result->AddItem(i->first.c_str());
          }
          return result.Detach();
        }

        void Clear()
        {
          Linq::CleanNullableCollection(m_Options);
        }
        void AddOption(const char * name)
        {
          iterator i = m_Options.find(name);
          if (i == m_Options.end())
            m_Options.insert(std::make_pair(name, new Variant()));
        }
        template <class Y>
        void AddOption(const char * name, const Y & value)
        {
          iterator i = m_Options.find(name);
          if (i == m_Options.end())
          {
            m_Options.insert(std::make_pair(name, new Variant(value)));
          }
          else
            *(i->second) = value;
        }
        void AddOption(const char * name, IVariant * value)
        {
          iterator i = m_Options.find(name);
          if (i == m_Options.end())
          {
            VariantPtr result;
            result.Create();
            *result = value;

            m_Options.insert(std::make_pair(name, result.Detach()));
          }
          else
            *(i->second) = value;
        }
      };



    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
