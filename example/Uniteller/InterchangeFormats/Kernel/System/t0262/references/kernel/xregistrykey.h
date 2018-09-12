// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию обертки вокруг указателя на ключ реестра

#pragma once

#include "utils.h"
#include "variant.h"
#include "iregistrykey.h"
#include "iregistry.h"
#include "registrykey.h"
#include "keyalreadyexistsexception.h"
#include "keynotfoundexception.h"
#include "kernel/linq"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      class RegistryKeyWrapperIterator;

      /// <summary>
      /// Обертка вокруг указателя на ключ реестра
      /// </summary>
      class RegistryKeyWrapper : public SmartPointer < IRegistryKey >
      {
      public:
        explicit RegistryKeyWrapper(const RegistryKeyWrapper & src) : SmartPointer<IRegistryKey>(src.p)
        {
        }
        RegistryKeyWrapper()
        {
        }
        RegistryKeyWrapper(IRegistryKey * key) : SmartPointer<IRegistryKey>(key)
        {
        }
        /// <summary>
        /// Создает обертку, открывает (или создает) ключ реестра и привязывает обертку к ключу
        /// </summary>
        RegistryKeyWrapper(IRegistry * registry, const char * path)
        {
          Attach(registry->Open(path));
        }

        inline RegistryKeyWrapper operator[](const std::string & path)
        {
          return QueryKey(path.c_str());
        }

        inline RegistryKeyWrapper operator[](const std::string & path) const
        {
          return QueryKey(path.c_str());
        }

        inline RegistryKeyWrapper operator[](const char * path)
        {
          return QueryKey(path);
        }

        inline RegistryKeyWrapper operator[](const char * path) const
        {
          return QueryKey(path);
        }


        RegistryKeyWrapper operator[](int index) const
        {
          RegistryKeyWrapper result;
          SmartPointer<IRegistryKeyIterator> begin, end;
          begin <<= Begin();
          end <<= End();
          begin <<= begin->Advance(index);
          if (!begin->IsEqualTo(end))
          {
            result <<= begin->GetValue();
          }
          return result;
        }

        RegistryKeyWrapper operator[](int index)
        {
          RegistryKeyWrapper result;
          SmartPointer<IRegistryKeyIterator> begin, end;
          begin <<= Begin();
          end <<= End();
          begin <<= begin->Advance(index);
          if (!begin->IsEqualTo(end))
          {
            result <<= begin->GetValue();
          }
          return result;
        }

        template <class T>
        T GetValue() const
        {
          SmartPointer<IVariant> value;
          value.Attach(p->PeekValue());
          if (value.p)
            return ((Variant *)value.p)->ConvertTo<T>();
          return T();
        }

        template <class Q>
        void SetValue(const Q value)
        {
          Variant v(value);
          p->SetValue(&v);
        }
#ifndef __GNUG__
        template <>
        void SetValue(const std::string& value)
        {
          Variant v(value);
          p->SetValue(&v);
        }
#endif

#pragma region Subkeys functions

        /// <summary>
        /// Возвращает подключ по имени.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Обертка вокруг указателя на подключ, если он существует, NULL - иначе.</returns>
        RegistryKeyWrapper QuerySubKey(const char * name) const
        {
          RegistryKeyWrapper wrapper;
          wrapper <<= p->GetSubKey(name);
          return wrapper;
        }

        /// <summary>
        /// Создает новый подключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        template <class Q>
        void CreateSubKey(const char * name, const Q value)
        {
          Variant v(value);
          p->CreateSubKey(name, &v);
        }

        /// <summary>
        /// Создает новый подключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        void CreateSubKey(const char * name, const std::string & value) const
        {
          Variant v(value);
          p->CreateSubKey(name, &v);
        }

        template <class Q>
        Q GetSubKeyValue(const char * name) const
        {
          SmartPointer<IVariant> value;
          value.Attach(p->PeekSubKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          throw KeyNotFoundException(name);
        }

        template <class Q>
        Q GetSubKeyValue(const char * name, const Q dflt) const
        {
          SmartPointer<IVariant> value;
          value.Attach(p->PeekSubKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          return dflt;
        }

        VariantType GetSubKeyValueType(const char * name) const
        {
          SmartPointer<IVariant> value;
          value <<= p->PeekSubKeyValue(name);
          if (!value.p)
            return VariantType::EmptyValue;
          return value->GetType();
        }

        template <class Q>
        void SetSubKeyValue(const char *name, Q value)
        {
          SmartPointer<IRegistryKey> child;
          child <<= p->GetSubKey(name);
          if (child.p)
          {
            Variant v(value);
            child->SetValue(&v);
          }
          else
            CreateSubKey(name, value);
        }

#pragma endregion

#pragma region Query functions
        /// <summary>
        /// Позволяет проверить существует ли ключ.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Существует ли ключ (true - да, false - нет).</returns>
        bool IsKeyExists(const std::string & path) const
        {
          return p->IsKeyExists(path.c_str());
        }

        /// <summary>
        /// Возвращает ключ по пути.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Указатель на ключ, если он существует, NULL - иначе.</returns>
        RegistryKeyWrapper QueryKey(const char * path) const
        {
          RegistryKeyWrapper result;
          result <<= p->GetKey(path);
          return result;
        }

        /// <summary>
        /// Создает ключ
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа.</param>
        template <class Q>
        void CreateKey(const char * path, const Q value)
        {
          Variant v(value);
          p->CreateKey(path, &v);
        }

        /// <summary>
        /// Создает ключ
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа.</param>
        void CreateKey(const char * path, const std::string & value)
        {
          Variant v(value);
          p->CreateKey(path, &v);
        }

        /// <summary>
        /// Создает ключ
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа.</param>
        void CreateKey(const char * path, const char * value)
        {
          Variant v(value);
          p->CreateKey(path, &v);
        }


        /// <summary>
        /// Переименовывает подключ
        /// </summary>
        /// <param name="oldname">Старое имя подключа</param>
        /// <param name="newname">Новое имя подключа</param>
        void RenameSubKey(const char * oldname, const char * newname)
        {
          if (p->IsSubKeyExists(newname))
            throw KeyAlreadyExistsException(newname);
          SmartPointer<IRegistryKey> subkey;
          subkey <<= p->GetSubKey(oldname);
          if (subkey != NULL)
          {
            p->RemoveSubKey(oldname);
            subkey->SetName(newname);
            p->AddChild(subkey);
          }
          else
            throw KeyNotFoundException(oldname);
        }

        IVariant * GetKeyValue(const std::string & name)
        {
          return p->GetKeyValue(name.c_str());
        }

        template <class Q>
        Q GetKeyValue(const char * name) const
        {
          SmartPointer<IVariant> value;
          value.Attach(p->PeekKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          throw KeyNotFoundException(name);
        }

        template <class Q>
        Q GetKeyValue(const std::string & path) const
        {
          const char * name = path.c_str();
          SmartPointer<IVariant> value;
          value.Attach(p->PeekKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          throw KeyNotFoundException(name);
        }

        template <class Q>
        Q GetKeyValue(const char * name, const Q dflt) const
        {
          SmartPointer<IVariant> value;
          value.Attach(p->PeekKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          return dflt;
        }

        template <class Q>
        Q GetKeyValue(const std::string & path, const Q dflt) const
        {
          const char * name = path.c_str();
          SmartPointer<IVariant> value;
          value.Attach(p->PeekKeyValue(name));
          if (value.p)
          {
            return ((Variant *)value.p)->ConvertTo<Q>();
          }
          return dflt;
        }
#pragma endregion

        /// <summary>
        /// Очищает все подключи данного
        /// </summary>
        void Clear()
        {
          if (p)
            p->Clear();
        }

        IRegistryKeyIterator * Begin() const
        {
          return p ? p->Begin() : NULL;
        }

        IRegistryKeyIterator * End() const
        {
          return p ? p->End() : NULL;
        }

        /// <summary>
        /// Прозволяет получить имя подключа по индексу
        /// </summary>
        std::string GetChildName(const size_t index) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          end <<= End();
          size_t j = 0;
          while (!i->IsEqualTo(end.p))
          {
            if (j == index)
            {
              SmartPointer<IRegistryKey> key;
              key <<= i->GetValue();
              return key->GetName();
            }
            ++j;
            i <<= i->MoveNext();
          }
          return "";
        }


        std::vector<const char *> GetSubkeyNames() const
        {
          std::vector<const char *> result;
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              IRegistryKey * key = i->GetValue();
              result.push_back(key->GetName());        
              key->Release();
              i <<= i->MoveNext();
            }
          }
          return result;
        }

        /// <summary>
        /// Выполняет поиск среди подключей данного ключа такой, который содержит поддерево, заданное path.
        /// </summary>
        IRegistryKey * FindSubkeyWith(const std::string & path, IRegistryKey ** selected) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (!i.p)
            return NULL;
          end <<= End();
          while (!i->IsEqualTo(end.p))
          {
            IRegistryKey * key = i->GetValue();
            *selected = key->GetKey(path.c_str());
            if (*selected)
              return key;
            key->Release();
            i <<= i->MoveNext();
          }
          return NULL;
        }

        RegistryKeyWrapperIterator begin() const;
        RegistryKeyWrapperIterator end() const;     

        typedef void(*Action)(const RegistryKeyWrapper & item);
        typedef void(*Action1)(RegistryKeyWrapper & item, int & value);

        template <Action action>
        inline void ForEach() const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              action(key);
              i <<= i->MoveNext();
            }
          }          
        }

        template <Action1 action>
        inline void ForEach(int value) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              action(key, value);
              i <<= i->MoveNext();
            }
          }
        }

        template <class T>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T), T & arg) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg);
              i <<= i->MoveNext();
            }
          } 
        }

        template <class T>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T &), T & arg) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg);
              i <<= i->MoveNext();
            }
          } 
        }

        template <class T1, class T2>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T1, T2), T1 arg1, T2 arg2) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg1, arg2);
              i <<= i->MoveNext();
            }
          }
        }

        template <class T1, class T2>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T1 &, T2), T1 & arg1, T2 arg2) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg1, arg2);
              i <<= i->MoveNext();
            }
          }
        }

        template <class T1, class T2>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T1 &, const T2 &), T1 & arg1, const T2 & arg2) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg1, arg2);
              i <<= i->MoveNext();
            }
          }
        }

        //template <class T1, class T2, class T3, void(*ParametrizedAction)(const RegistryKeyWrapper & item, T1, T2, T3)>
        template <class T1, class T2, class T3>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T1, T2, T3), T1 arg1, T2 arg2, T3 arg3) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg1, arg2, arg3);
              i <<= i->MoveNext();
            }
          }
        }

        template <typename T, typename ...Args>
        void ForEach(T * obj, void (T::*mf)(const RegistryKeyWrapper &, Args...), Args &&... args)
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              (obj->*mf)(key, std::forward<Args>(args)...);
              i <<= i->MoveNext();
            }
          }          
        }
                
        template <typename T>
        void ForEach(T * obj, void (T::*mf)(const RegistryKeyWrapper &)) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              (obj->*mf)(key);
              i <<= i->MoveNext();
            }
          }          
        }

        template <typename T, typename Y>
        void ForEach(T * obj, void (T::*mf)(const RegistryKeyWrapper &, Y), Y y) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              (obj->*mf)(key, y);
              i <<= i->MoveNext();
            }
          }
        }
        
        template <class T, typename Y, typename Z>
        void ForEach(T * obj, void (T::*mf)(const RegistryKeyWrapper &, const Y &, Z), const Y & y, Z z) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              (obj->*mf)(key, y, z);
              i <<= i->MoveNext();
            }
           }
         }

        template <typename T>
        bool Any(T * obj, bool (T::*mf)(const RegistryKeyWrapper &)) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              if ((obj->*mf)(key))
                return true;
              i <<= i->MoveNext();
            }
          }          
          return false;
        }

        template <typename T>
        inline void ForEachForEach(T * obj, void (T::*mf)(const RegistryKeyWrapper &)) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              key.ForEach(obj, mf);
              i <<= i->MoveNext();
            }
          }
        }
        

        template <class T1, class T2, class T3>
        inline bool Any(bool(*Action)(const RegistryKeyWrapper &, T1, T2, T3), T1 arg1, T2 arg2, T3 arg3) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              if (Action(key, arg1, arg2, arg3))
                return true;
              i <<= i->MoveNext();
            }
          }
          return false;
        }

        template <class T1, class T2, class T3, class T4>
        inline bool Any(bool(*Action)(const RegistryKeyWrapper &, T1, T2, T3, T4), T1 arg1, T2 arg2, T3 arg3, T4 arg4) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              if (Action(key, arg1, arg2, arg3, arg4))
                return true;
              i <<= i->MoveNext();
            }
          }
          return false;
        }
        //template <typename T1, typename T2, typename T3>
        //inline void ForEach3(void(*Action)(const RegistryKeyWrapper &, T1, T2, T3),T1 arg1, T2 arg2, T3 arg3) const
        //{
        //  SmartPointer<IRegistryKeyIterator> i, end;
        //  i <<= Begin();
        //  if (i.p)
        //  {
        //    end <<= End();
        //    while (!i->IsEqualTo(end.p))
        //    {
        //      RegistryKeyWrapper key;
        //      key <<= i->GetValue();
        //      Action(key, arg1, arg2, arg3);
        //      i <<= i->MoveNext();
        //    }
        //  }
        //}

        template <Action action>
        inline void ForEachForEach() const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              key.ForEach<action>();
              i <<= i->MoveNext();
            }
          }
        }

        template <class T1, class T2, class T3>
        inline void ForEach(void(*Action)(const RegistryKeyWrapper &, T1 &, const T2 &, const T3 & ), T1 & arg1, const T2 & arg2, const T3 & arg3) const
        {
          SmartPointer<IRegistryKeyIterator> i, end;
          i <<= Begin();
          if (i.p)
          {
            end <<= End();
            while (!i->IsEqualTo(end.p))
            {
              RegistryKeyWrapper key;
              key <<= i->GetValue();
              Action(key, arg1, arg2, arg3);
              i <<= i->MoveNext();
            }
          }
        }

      };

      /// <summary>
      /// Реализация итератора обертки ключа реестра для того, чтобы можно было использовать циклы for
      /// </summary>
      class RegistryKeyWrapperIterator : public std::iterator<std::forward_iterator_tag, RegistryKeyWrapper>
      {
      private:
        SmartPointer<IRegistryKeyIterator> m_Iterator;
        RegistryKeyWrapper wrapper;
      public:
        RegistryKeyWrapperIterator()
        {
        }
				RegistryKeyWrapperIterator(IRegistryKeyIterator * iterator) :
					m_Iterator(iterator)
        {
        }
				RegistryKeyWrapperIterator(const RegistryKeyWrapperIterator & src) :
					m_Iterator(src.m_Iterator.p)
        {
        }
        void Attach(IRegistryKeyIterator * iterator)
        {
          m_Iterator.Attach(iterator);
        }
        RegistryKeyWrapper & operator*()
        {
          wrapper.Attach(m_Iterator->GetValue());
          return wrapper;
        }

        RegistryKeyWrapperIterator& operator++()
        {
          m_Iterator->MoveNext();
          return *this;
        }

        bool operator==(const RegistryKeyWrapperIterator & b) const
        {
          if (!m_Iterator.p)
            return b.m_Iterator==NULL;
          return m_Iterator->IsEqualTo(b.m_Iterator.p);
        }
        bool operator!=(const RegistryKeyWrapperIterator & b) const
        {
          if (!m_Iterator.p)
            return b.m_Iterator.p!=NULL;
          return !m_Iterator->IsEqualTo(b.m_Iterator.p);
        }
      };


      RegistryKeyWrapperIterator begin(RegistryKeyWrapper & container);
      RegistryKeyWrapperIterator end(RegistryKeyWrapper & container);

      RegistryKeyWrapperIterator begin(const RegistryKeyWrapper & container);
      RegistryKeyWrapperIterator end(const RegistryKeyWrapper & container);

    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
