// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию умного указателя (SmartPointer)

#pragma once

#include "smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// Умный указатель
      /// </summary>
      template <class T, class Impl>
      class GlobalPointer
      {
      protected:
        void Swap(GlobalPointer& other)
        {
          T* pTemp = p;
          p = other.p;
          other.p = pTemp;
        }
      public:
        /// <summary>
        /// Конструктор
        /// </summary>
        GlobalPointer() : p(new Impl())
        {          
        }
        /// <summary>
        /// Создает умный указатель, инициализирует его интерфейсом и автоматически увеличивает счетчик ссылок.
        /// </summary>
        /// <param name="lp">The lp.</param>
        GlobalPointer(_Inout_opt_ T* lp) throw()
        {
          p = lp;
          if (p != NULL)
            p->AddRef();
        }
        /// <summary>
        /// Деструктор.
        /// </summary>
        ~GlobalPointer()
        {
          if (p)
            p->Release();
        }
        operator T*() const throw()
        {
          return p;
        }
        T& operator*() const
        {
          if (!p)
            throw NullReferenceException("p");
          return *p;
        }
        NoAddRefReleaseOnIExportable<T>* operator->() const
        {          
          if (!p)
            throw NullReferenceException("p");          
          return (NoAddRefReleaseOnIExportable<T>*)p;
        }
        bool operator!() const throw()
        {	
          return (p == NULL);
        }

        bool operator!=(_In_opt_ T* pT) const
        {
          return !operator==(pT);
        }
        bool operator==(_In_opt_ T* pT) const throw()
        {
          return p == pT;
        }
                
        /// <summary>
        /// Освобождает ссылку на интерфейс и устанавливает ее значение в NULL
        /// </summary>
        /// <returns></returns>
        void Release() throw()
        {
          T* pTemp = p;
          if (pTemp)
          {
            p = NULL;
            pTemp->Release();
          }
        }

        // Attach to an existing interface (does not AddRef)
        void Attach(_In_opt_ T* p2) throw()
        {
          if (p)
          {
            int ref = p->Release();
            (ref);
            // Attaching to the same object only works if duplicate references are being coalesced.  Otherwise
            // re-attaching will cause the pointer to be released and may cause a crash on a subsequent dereference.
            //ATLASSERT(ref != 0 || p2 != p);
          }
          p = p2;
        }
        // Detach the interface (does not Release)
        T* Detach() throw()
        {
          T* pt = p;
          p = NULL;
          return pt;
        }

        void CopyTo(T** ppT) throw()
        {
          ATLASSERT(ppT != NULL);
          if (ppT == NULL)
            return; // E_POINTER
          *ppT = p;
          if (p)
            p->AddRef();
        }

        T* Copy() const
        {
          if (p)
          {
            p->AddRef();
          }
          return p;
        }

        T* operator=(_Inout_opt_ T* lp) throw()
        {
          if(*this!=lp)
          {
            GlobalPointer(lp).Swap(*this);
          }
          return *this;
        }

        T* operator <<=(_Inout_opt_ T* lp) throw()
        {
          if(*this!=lp)
          {
            Attach(lp);
          }
          return *this;
        }

        T* operator=(_Inout_ const SmartPointer<T>& lp) throw()
        {
          if(*this!=lp)
          {
            GlobalPointer(lp.p).Swap(*this);
          }
          return *this;
        }	        

        #ifndef __GNUG__
        T* operator=(_Inout_ SmartPointer<T>&& lp) throw()
        {			
          if (*this != lp)
          {
            GlobalPointer(static_cast<SmartPointer&&>(lp)).Swap(*this);
          }
          return *this;		
        }
        #endif

        /// <summary>
        /// Инициализация указателя новым экземпляром объекта типа T
        /// </summary>
        void Create()
        {
          Attach(new Impl());
        }

        /// <summary>
        /// Инициализация указателя новым экземпляром объекта типа Q
        /// </summary>
        template <class Q>
        void Create()
        {
          Attach(new Q());
        }


        // Attach to an existing interface (does not AddRef)
        template <class Q>
        void Attach(_In_opt_ Q* p2) throw()
        {
          if (p)
          {
            //int ref = 
            p->Release();
            //(ref);
            // Attaching to the same object only works if duplicate references are being coalesced.  Otherwise
            // re-attaching will cause the pointer to be released and may cause a crash on a subsequent dereference.
            //ATLASSERT(ref != 0 || p2 != p);
          }
          p = dynamic_cast<T *>(p2);
        }
        
        template <class Q>
        T* operator=(_Inout_opt_ Q* lp) throw()
        {
          if(*this!=lp)
          {
            if (p)
            {
              //int ref = 
              p->Release();
              //(ref);
            }
            p = dynamic_cast<T *>(lp);
            if (p)
              p->AddRef();
          }
          return *this;
        }


        T * p;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller