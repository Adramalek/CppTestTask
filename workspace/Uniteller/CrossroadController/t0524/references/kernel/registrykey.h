// Uniteller.Framework.Kernel
// Version: 1.0.1
// Generation: 1
// Совместим с gcc

// Файл содержит реализацию ключа реестра

#pragma once

#include "utils.h"
#include "variant.h"
#include "iregistrykey.h"
#include "exportableenumeration.h"
#ifndef __GNUG__
#include "AvlTree.h"
#else
#include <set>
#endif

#include "keynotfoundexception.h"

// Переопределение std::less
namespace std
{
  template <>
  struct less<Uniteller::Framework::Kernel::IRegistryKey *> : public binary_function <Uniteller::Framework::Kernel::IRegistryKey *, Uniteller::Framework::Kernel::IRegistryKey *, bool>
  {
    bool operator()(
      const Uniteller::Framework::Kernel::IRegistryKey * _Left,
      const Uniteller::Framework::Kernel::IRegistryKey * _Right
      ) const
    {
      return strcmp(_Left->GetName(), _Right->GetName())<0;
    }
  };
}

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
		{
#ifndef __GNUG__
			class RegistrySet : public index_set < IRegistryKey * >
			{
			public:
				// Returns the position of the first item in the tree that matches 'data'
				// or NULL if no match is found.
				AVLNode<IRegistryKey *>* Select(const std::string & item) const
				{
					const char * s = item.c_str();
					AVLNode<IRegistryKey *> *at = _root;
					while (at)
					{
						const char * x = at->Data->GetName();
						if (strcmp(s, x)<0)
							at = at->Left;
						else
						{
							if (strcmp(x, s)>=0)		// match found
								return at;
							at = at->Right;
						}
					}
					return NULL;		// no match found
				}

				const_iterator select(const std::string & item) const
				{
					AVLNode<IRegistryKey *> *pos = Select(item);
					if (!pos)
						pos = _endnode;
					return AVLTree_Iterator(*this, pos);
				}
				// Returns the position of the first item in the tree that matches 'data'
				// or NULL if no match is found.
				AVLNode<IRegistryKey *>* Select(const char * s) const
				{
					AVLNode<IRegistryKey *> *at = _root;
					while (at)
					{
						const char * x = at->Data->GetName();
						if (strcmp(s, x)<0)
							at = at->Left;
						else
						{
							if (strcmp(x, s) >= 0)		// match found
								return at;
							at = at->Right;
						}
					}
					return NULL;		// no match found
				}

				const_iterator select(const char * item) const
				{
					AVLNode<IRegistryKey *> *pos = Select(item);
					if (!pos)
						pos = _endnode;
					return AVLTree_Iterator(*this, pos);
				}

			};
#else
  #define RegistrySet std::set<IRegistryKey *>
#endif

      class RegistryKeyIterator : public Exportable<IRegistryKeyIterator>
      {
      private:
				RegistrySet::iterator m_Pointer;
				RegistrySet::iterator m_End;
      public:
				RegistryKeyIterator(const RegistrySet::iterator & i, const RegistrySet::iterator & end) :
					m_Pointer(i),
				  m_End(end)
        {
        }
        bool IsEqualTo(IRegistryKeyIterator * iterator)
        {
          return m_Pointer == ((RegistryKeyIterator *)iterator)->m_Pointer;
        }
        IRegistryKeyIterator * MoveNext()
        {
          ++m_Pointer;
					// Секция ниже не требуется, т.к. !Documentation всегда в начале списка
          /*if (m_Pointer != m_End)
          {
            if (strcmp((*m_Pointer)->GetName(), "!Documentation")==0)
              ++m_Pointer;
          }*/
          return this;
        }
				IRegistryKeyIterator * Advance(int x)
				{
#ifndef __GNUG__
					m_Pointer += x;
#else
          while (x > 0)
          {
            ++m_Pointer;
            --x;
          }
#endif
					return this;
				}
        IRegistryKey * GetValue()
        {
          if (m_End == m_Pointer)
            return NULL;
          (*m_Pointer)->AddRef();
          return *m_Pointer;
        }
      };


      /// <summary>
      /// Ключ реестра метаданных
      /// </summary>
      class RegistryKey : public Exportable<IRegistryKey>
      {
      private:
        Variant m_Value;

        // Указатель на родительский ключ
				RegistrySet m_SubKeys;
				typedef RegistrySet::iterator iterator;
				typedef RegistrySet::const_iterator const_iterator;
      public:
        RegistryKey()
        {
        }
				explicit RegistryKey(const std::string & sName) : m_Name(sName)
				{
				}
        explicit RegistryKey(const char * szName) : m_Name(szName)
        {
        }
        RegistryKey(const char * szName, IVariant * value) : m_Name(szName)
        {
          if (value)
            m_Value = value;
        }
        RegistryKey(const char * szName, const char * value) : m_Value(value), m_Name(szName)
        {
        }
				//RegistryKey(const char * szName, const std::string & value) : m_Name(szName), m_Value(value)
        //{
				//}
				template <class T>
				RegistryKey(const char * szName, const T & value) : m_Value(value), m_Name(szName)
				{
				}
				template <class T>
				RegistryKey(const std::string & name, const T & value) : m_Value(value), m_Name(name)
				{
				}
        ~RegistryKey()
        {
          Clear();
        }
        // имя ключа
        PROPERTY_IMPLEMENTATION_STRING(Name);

        IVariant * GetValue()
        {
          return new Variant(m_Value);
        }

				IVariant * PeekValue() override
				{
					IVariant * v = &m_Value;
					v->AddRef();
					return v;
				}
        void SetValue(IVariant * value) override
        {
          m_Value = value;
        }

        #pragma region Subkeys management

        /// <summary>
        /// Позволяет добавить дочерний узел
        /// </summary>
        /// <param name="child">Дочерний узел.</param>
        void AddChild(IRegistryKey * child) override
        {
          if (child)
          {
            child->AddRef();
						iterator i = m_SubKeys.find(child);
						if (i == m_SubKeys.end())
            {
              m_SubKeys.insert(child);
            }
            else
            {
              if (*i) // Отпускаем ссылку
                (*i)->Release();
              m_SubKeys.erase(i);
              m_SubKeys.insert(child);
            }
          }
        }

        /// <summary>
        /// Позволяет проверить существует ли ключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Существует ли ключ (true - да, false - нет).</returns>
        bool IsSubKeyExists(const char * name) const override
        {
					if (m_SubKeys.size() == 0)
						return false;
#ifndef __GNUG__
					return m_SubKeys.Select(name) != NULL;
#else
          RegistryKey key(name);
          iterator i = m_SubKeys.find(&key);
          return (i != m_SubKeys.end());
#endif
        }

        /// <summary>
        /// Возвращает подключ по имени.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Указатель на подключ, если он существует, NULL - иначе.</returns>
        IRegistryKey * GetSubKey(const char * name) override
        {
					if (m_SubKeys.size() > 0)
					{
          #ifndef __GNUG__
						AVLNode<IRegistryKey *> * i = m_SubKeys.Select(name);
						if (i != NULL)
						{
							IRegistryKey * res = i->Data;
							res->AddRef(); // Увеличиваем счетчик ссылок, прежде чем вернуть ключ
							return res;
						}
          #else
            RegistryKey key(name);
            iterator i = m_SubKeys.find(&key); //keyToFind.p);
            if (i != m_SubKeys.end())
            {
              (*i)->AddRef(); // Увеличиваем счетчик ссылок, прежде чем вернуть ключ
              return (*i);
            }
          #endif
					}
          return NULL;
        }
        /// <summary>
        /// Создает новый подключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        void CreateSubKey(const char * name, IVariant * value) override
        {
          m_SubKeys.insert(new RegistryKey(name, value));
        }

				IRegistryKey * MakeSubKey(const char * name, IVariant * value)
				{
					IRegistryKey * result = new RegistryKey(name, value);
					m_SubKeys.insert(result);
					result->AddRef();
					return result;
				}

        /// <summary>
        /// Позволяет удалить подключ.
        /// </summary>
        /// <param name="name">Имя подключа для удаления.</param>
        void RemoveSubKey(const char * name) override
        {
#ifndef __GNUG__
          iterator i = m_SubKeys.select(name);
#else
          RegistryKey key(name);
          iterator i = m_SubKeys.find(&key);
#endif
          if (i != m_SubKeys.end())
          {
            if (*i) // Отпускаем ссылку
              (*i)->Release();
            m_SubKeys.erase(i);
          }
        }
        /// <summary>
        /// Возвращает значение под ключа
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Значение подключа (если он существует или NULL иначе).</returns>
        IVariant * GetSubKeyValue(const char * name)  const
        {
#ifndef __GNUG__
					AVLNode<IRegistryKey *> * i = m_SubKeys.Select(name);
					if (i != NULL)
						return i->Data->GetValue();
#else
          RegistryKey key(name);
          iterator i = m_SubKeys.find(&key);
          if (i != m_SubKeys.end())
            return (*i)->GetValue();
#endif
          return NULL;
        }

        /// <summary>
        /// Устанавливает значение подключа
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        /// <description>
        /// Используется для установки новых значений в подключи. Если передать имя не существующего подключа,
        /// то он будет создан и ему будет установлено значение <paramref name="value"/>.
        /// </description>
        void SetSubKeyValue(const char * name, IVariant * value)
        {
          RegistryKeyPtr key;
          key.Attach(GetSubKey(name));
          if (key.p)
          {
            key->SetValue(value);
          }
          else
          {
            CreateSubKey(name, value);
          }
        }


      #pragma endregion

      #pragma region Query functions
        /// <summary>
        /// Позволяет проверить существует ли ключ.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Существует ли ключ (true - да, false - нет).</returns>
        bool IsKeyExists(const char * path)
        {
					if (m_SubKeys.size() == 0)
						return false;
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (key.p)
              return key->IsKeyExists(relative.c_str());
            return false;
          }
          return IsSubKeyExists(root.c_str());
        }
        /// <summary>
        /// Возвращает ключ по пути.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Указатель на ключ, если он существует, NULL - иначе.</returns>
        IRegistryKey * GetKey(const char * path)
        {
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (key.p)
              return key->GetKey(relative.c_str());
            return NULL;
          }
          return GetSubKey(root.c_str());
        }

        /// <summary>
        /// Создает ключ
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа.</param>
        void CreateKey(const char * path, IVariant * value)
        {
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (!key.p)
            {
							key.Attach(MakeSubKey(root.c_str(), NULL));
            }
            key->CreateKey(relative.c_str(), value);
          }
          else
          {
            CreateSubKey(root.c_str(), value);
          }
        }
        /// <summary>
        /// Удаляет ключ.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        void RemoveKey(const char * path)
        {
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (key.p)
              key->RemoveKey(relative.c_str());
          }
          else
          {
            return RemoveSubKey(root.c_str());
          }
        }
        /// <summary>
        /// Возвращает значение ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Значение ключа (если он существует или NULL иначе).</returns>
        IVariant * GetKeyValue(const char * path)
        {
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (key.p)
              return key->GetKeyValue(relative.c_str());
            return NULL;
          }
          return GetSubKeyValue(root.c_str());
        }

        /// <summary>
        /// Устанавливает значение ключа
        /// </summary>
        /// <param name="name">Имя ключа.</param>
        /// <param name="value">Значение ключа</param>
        /// <description>
        /// Используется для установки новых значений в ключи. Если передать имя не существующего ключа,
        /// то он будет создан (если надо с родительскими ключами) и ему будет установлено значение <paramref name="value"/>.
        /// </description>
        void SetKeyValue(const char * name, IVariant * value)
        {
          RegistryKeyPtr key;
          key.Attach(GetKey(name));
          if (key.p)
          {
            key->SetValue(value);
          }
          else
          {
            CreateKey(name, value);
          }
        }
      #pragma endregion

        /// <summary>
        /// Очищает все подключи данного
        /// </summary>
        void Clear() override
        {
          const_iterator end = m_SubKeys.end();
          for (iterator i = m_SubKeys.begin(); i != end; ++i)
          {
            (*i)->Release();
          }
          m_SubKeys.clear();
        }

        /// <summary>
        /// Позволяет получить число подключей данного ключа
        /// </summary>
        /// <returns>Число подключей</returns>
        size_t GetSubKeysCount() const
        {
          size_t result = m_SubKeys.size();
          if (result >0)
          {
            const_iterator i = m_SubKeys.begin();
            if (strcmp((*i)->GetName(), "!Documentation") == 0)
              --result;
          }
          return result;
        }

        /// <summary>
        /// Позволяет получить подключи данного ключа
        /// </summary>
        /// <returns>Контейнер, содержащий все подключи данного ключа.</returns>
        IEnumeration<IRegistryKey *> * GetSubKeys()
        {
          SmartPointer<ExportableEnumeration<IRegistryKey>> result;
          result.Create();
					const_iterator begin = m_SubKeys.begin();
					if (begin != m_SubKeys.end())
					{
						if (strcmp((*begin)->GetName(), "!Documentation") == 0)
							++begin;
					}
					const_iterator end = m_SubKeys.end();
					for (const_iterator i = begin; i != end; ++i)
					{
  					result->Add(*i);
					}
          return result.Detach();
        }

        /// <summary>
        /// Позволяет получить число подключей данного ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Число подключей</returns>
        size_t GetSubKeysCount(const char * path)
        {
          RegistryKeyPtr key;
          key.Attach(GetKey(path));
          if (key.p)
            return key->GetSubKeysCount();
          return 0;
        }

        /// <summary>
        /// Позволяет получить подключи данного ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Контейнер, содержащий все подключи данного ключа.</returns>
        IEnumeration<IRegistryKey *> * GetSubKeys(const char * path)
        {
          RegistryKeyPtr key;
          key.Attach(GetKey(path));
          if (key.p)
            return key->GetSubKeys();
          return NULL;
        }

        /// <summary>
        /// Позволяет получить итератор, указывающий на первый подключ данного ключа
        /// </summary>
        /// <returns>Указатель на итератор, указывающий на первый подключ данного ключа</returns>
        IRegistryKeyIterator * Begin()
        {
          iterator i = m_SubKeys.begin();
					iterator end = m_SubKeys.end();
					if (i != end)
          {
            if (strcmp((*i)->GetName(), "!Documentation")==0)
              ++i;
          }
					return new RegistryKeyIterator(i, end);
        }
        /// <summary>
        /// Позволяет получить итератор, указывающий на конец подключей данного ключа
        /// </summary>
        /// <returns>Указатель на итератор, указывающий на конец подключей данного ключа</returns>
        IRegistryKeyIterator * End()
        {
					iterator end = m_SubKeys.end();
					return new RegistryKeyIterator(end, end);
        }

#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
        void AttachValue(IVariant * value)
        {
          m_Value.SwapWith(value);
        }
#endif
				/// <summary>
				/// Возвращает значение ключа
				/// </summary>
				/// <param name="path">Путь к ключу.</param>
				/// <returns>Значение ключа (если он существует или NULL иначе).</returns>
				IVariant * PeekKeyValue(const char * path)
				{
#ifndef __GNUG__
					std::string root, relative;
					if (Utils::GetRootAndRelative(path, root, relative))
					{
						const_iterator i = m_SubKeys.select(root);
						if (i != m_SubKeys.end())
							return (*i)->PeekKeyValue(relative.c_str());
					}
					else
					{
						AVLNode<IRegistryKey *> * i = m_SubKeys.Select(path);
						if (i != NULL)
							return i->Data->PeekValue();
					}
					return NULL;
#else
          std::string root, relative;
          if (Utils::GetRootAndRelative(path, root, relative))
          {
            RegistryKeyPtr key;
            key.Attach(GetSubKey(root.c_str()));
            if (key.p)
              return key->PeekKeyValue(relative.c_str());
            return NULL;
          }
          return PeekSubKeyValue(path);

/*	                std::string relative = path;
					IRegistryKey * key = this;
					std::string root;
					while (Utils::GetRootAndRelative(relative, root, relative))
					{
						key = key->PeekSubKey(root.c_str());
						if (!key)
							return NULL;
					}
					return key->PeekSubKeyValue(relative.c_str());*/
#endif
				}
				/// <summary>
				/// Возвращает значение подключа
				/// </summary>
				/// <param name="name">Имя подключа.</param>
				/// <returns>Значение подключа (если он существует или NULL иначе).</returns>
				IVariant * PeekSubKeyValue(const char * name) const
				{
#ifndef __GNUG__
					AVLNode<IRegistryKey *> * i = m_SubKeys.Select(name);
					if (i != NULL)
						return i->Data->PeekValue();
#else
          RegistryKey key(name);
          iterator i = m_SubKeys.find(&key);
          if (i != m_SubKeys.end())
            return (*i)->PeekValue();
#endif
					return NULL;
				}

				/// <summary>
				/// Возвращает подключ по имени.
				/// </summary>
				/// <param name="name">Имя подключа.</param>
				/// <returns>Указатель на подключ, если он существует, NULL - иначе.</returns>
				IRegistryKey * PeekSubKey(const char * name) override
				{
					if (m_SubKeys.size() > 0)
					{
#ifndef __GNUG__
						AVLNode<IRegistryKey *> * i = m_SubKeys.Select(name);
						if (i != NULL)
							return i->Data;
#else
            RegistryKey key(name);
            iterator i = m_SubKeys.find(&key);
            if (i != m_SubKeys.end())
            {
              (*i)->AddRef(); // !!! Разобраться
              return (*i); // Отпускаем ссылку
            }
#endif
					}
					return NULL;
				}

        inline IRegistryKey * Scan(const char * xpath)
        {
          const_iterator end = m_SubKeys.end();
          for (iterator i = m_SubKeys.begin(); i != end; ++i)
          {
            IRegistryKey * result = (*i)->SelectFirst(xpath);
            if (result)
              return result;
          }
          return NULL;
        }

        /// <summary>
        /// Выполняет поиск первого совпавшего с маской xpath узла в реестре
        /// </summary>
        /// <param name="xpath">Маска пути узла для поиска, может содержать *, означающее произвольное имя узла</param>
        /// <returns>Указатель на первый найденный ключ или NULL.</returns>
        IRegistryKey * SelectFirst(const char * xpath) override
        {
          std::string root, relative;
          if (Utils::GetRootAndRelative(xpath, root, relative))
          {
            switch (root[0])
            {
            case '*':
              if (root.size() == 1)
                return Scan(relative.c_str());
              { // Формат с вариантами
                const std::vector<std::string> & variants = Utils::Split(root.substr(2, root.size() - 3), '|');
                std::vector<std::string>::const_iterator end = variants.end();
                for (std::vector<std::string>::const_iterator j = variants.begin(); j != end; ++j)
                {
#ifndef __GNUG__
                  AVLNode<IRegistryKey *> * i = m_SubKeys.Select(*j);
                  if ((i != NULL) && (i->Data != NULL))
                  {
                    IRegistryKey * result = i->Data->SelectFirst(relative.c_str());
                    if (result)
                      return result;
                  }
#else
                  RegistryKey key(*j);
                  iterator i = m_SubKeys.find(&key);
                  if (i != m_SubKeys.end())
                  {
                    //(*i)->AddRef();
                    IRegistryKey * result = (*i)->SelectFirst(relative.c_str());
                    if (result)
                      return result;
                  }
#endif
                }
              }
              break;
            case '>': // Направленный поиск
              {
#ifndef __GNUG__
              AVLNode<IRegistryKey *> * i = m_SubKeys.Select(root.substr(1));
              if ((i != NULL) && (i->Data != NULL))
              {
                return i->Data->SelectFirst(relative.c_str());
              }
#else
              RegistryKey key(root.substr(1));
              iterator i = m_SubKeys.find(&key);
              if (i != m_SubKeys.end())
              {
                //(*i)->AddRef();
                return (*i)->SelectFirst(relative.c_str());
              }
#endif
              }
              // Если направленный поиск не удался - brute force!
              return Scan(relative.c_str());
            default:
              {
#ifndef __GNUG__
                AVLNode<IRegistryKey *> * i = m_SubKeys.Select(root);
                if ((i != NULL) && (i->Data != NULL))
                  return i->Data->SelectFirst(relative.c_str());
#else
                RegistryKey key(root);
                iterator i = m_SubKeys.find(&key);
                if (i != m_SubKeys.end())
                {
                  //(*i)->AddRef();
                  return (*i)->SelectFirst(relative.c_str());
                }
#endif
                /*RegistryKeyPtr key;
                 key.Attach(GetSubKey(root.c_str()));
                 if (key.p)
                 return key->SelectFirst(relative.c_str());*/
                }
                break;
            }
            return NULL; // Ничего не нашли
          }
          return GetSubKey(root.c_str());
        }
      };


    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller

