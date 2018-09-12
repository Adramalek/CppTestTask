// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию обертки вокруг указателя на перечисление

#pragma once

#include "smartpointer.h"
#include "ienumeration.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      
      template<class T, class Tag = void>
      class EnumerationIterator : public std::iterator<std::forward_iterator_tag, T>
      {
      private:
        size_t m_nPosition;
        SmartPointer<IEnumeration<T>> m_Enumeration;
      public:
				EnumerationIterator(const EnumerationIterator & src) : m_nPosition(src.m_nPosition)
        {          
          m_Enumeration = src.m_Enumeration;
        }
				EnumerationIterator(IEnumeration<T> * e, size_t x) : m_nPosition(x)
        {
          m_Enumeration = e;
        }

        T operator*() const
        {
          return m_Enumeration->GetItem(m_nPosition);
        }
        T* operator->() const
        {
          return &m_Enumeration->GetItem(m_nPosition);
        }

        EnumerationIterator& operator++()
        {
          ++m_nPosition;
          return *this;
        }
        EnumerationIterator operator++(int x)
        {
					return EnumerationIterator(m_Enumeration, m_nPosition + x);
        }

        bool operator==(const EnumerationIterator & b) const
        {
          return m_nPosition == b.m_nPosition;
        }

        bool operator!=(const EnumerationIterator & b) const
        {
          return m_nPosition != b.m_nPosition;
        }
      };
      
      template <class T>
			class EnumerationWrapper : public SmartPointer<IEnumeration<T>>
      {
      public:
        EnumerationWrapper()
        {
        }
				EnumerationWrapper(IEnumeration<T> * p) : SmartPointer<IEnumeration<T>>(p)
        {
        }

        size_t GetSize()
        {
          return p->GetCount();
        }

        //operator IEnumeration<T> *() 
        //{
        //  return m_Enumeration.p;
        //}

      };

      template <class T>
      class EnumerationWrapper<SmartPointer<T>>
      {
      private:
        SmartPointer<IEnumeration<T *>> m_Enumeration;
      public:

        EnumerationWrapper()
        {
        }
        EnumerationWrapper(IEnumeration<T *> * p)
        {
          m_Enumeration = p;
        }

        void Attach(IEnumeration<T *> * p)
        {
          m_Enumeration.Attach(p);
        }

        size_t GetSize()
        {
          return m_Enumeration->GetCount();
        }

        operator IEnumeration<T *> *() 
        {
          return m_Enumeration.p;
        }
      };

      template<class T>
      class EnumerationIterator<SmartPointer<T>> : public std::iterator<std::forward_iterator_tag, SmartPointer<T>>
      {
      private:
        size_t m_nPosition;
        SmartPointer<IEnumeration<T *>> m_Enumeration;        
      public:
        EnumerationIterator(const EnumerationIterator & src)
        {
          m_nPosition = src.m_nPosition;
          m_Enumeration = src.m_Enumeration;
        }
        EnumerationIterator(IEnumeration<T *> * e, size_t x)
        {
          m_Enumeration = e;
          m_nPosition = x;
        }

        T* operator*() const
        {
          SmartPointer<T> result;
          result <<=m_Enumeration->GetItem(m_nPosition);
          return result.p;
        }
        T* operator->() const
        {
          SmartPointer<T> result;
          result <<=m_Enumeration->GetItem(m_nPosition);
          return result;
          //return &m_Enumeration->GetItem(m_nPosition);
        }

        EnumerationIterator& operator++()
        {
          ++m_nPosition;
          return *this;
        }
        EnumerationIterator operator++(int x)
        {
          EnumerationIterator result;
          result.m_Enumeration = m_Enumeration;
          result.m_nPosition = m_nPosition + x;
          return result;
        }

        bool operator==(const EnumerationIterator & b) const
        {
          return m_nPosition == b.m_nPosition;
        }
        bool operator!=(const EnumerationIterator & b) const
        {
          return m_nPosition != b.m_nPosition;
        }

        //// one way conversion: iterator -> const_iterator
        //operator EnumerationIterator<T const, Tag>() const
        //{

        //}
      };

      template <class T>
      EnumerationIterator<T> begin(EnumerationWrapper<T> & container)
      {
        EnumerationIterator<T> result(container, 0);        
        return result;
      }

      template <class T>
      EnumerationIterator<T> end(EnumerationWrapper<T> & container)
      {
        EnumerationIterator<T> result(container, container.GetSize());        
        return result;
      }


      template <class T>
      EnumerationIterator<SmartPointer<T>> begin(EnumerationWrapper<SmartPointer<T>> & container)
      {
        EnumerationIterator<SmartPointer<T>> result(container, 0);        
        return result;
      }

      template <class T>
      EnumerationIterator<SmartPointer<T>> end(EnumerationWrapper<SmartPointer<T>> & container)
      {
        EnumerationIterator<SmartPointer<T>> result(container, container.GetSize());        
        return result;
      }


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller

