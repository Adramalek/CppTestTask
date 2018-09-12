// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ������ ��������� (SmartPointer)

#pragma once

#include "exportable.h"
#include "nullreferenceexception.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 
      /// <summary>
      /// ��������� ������� ����������� ������ ���������� ��������� ������
      /// ����� ��������� ��������� ����� �����-�������
      /// </summary>
      template <class T>
      class NoAddRefReleaseOnIExportable : 
        public T
      {
      private:                  
        /// <summary>
        /// ����������� ������� ������ �� ���������������� ������ �� �������
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				virtual long AddRef() = 0;
        /// <summary>
        /// ��������� ������� ������ �� ���������������� ������ �� ������� 
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
				virtual long Release() = 0;
        NoAddRefReleaseOnIExportable()
        {
        }
      };

      /// <summary>
      /// ����� ���������
      /// </summary>
      template <class T>
      class SmartPointer
      {
      protected:
        void Swap(SmartPointer& other)
        {
          T* pTemp = p;
          p = other.p;
          other.p = pTemp;
        }
      public:
        /// <summary>
        /// �����������
        /// </summary>
        SmartPointer() : p(NULL)
        {          
        }
        /// <summary>
        /// ������� ����� ���������, �������������� ��� ����������� � ������������� ����������� ������� ������.
        /// </summary>
        /// <param name="lp">The lp.</param>
	SmartPointer(_Inout_opt_ T* lp) throw() : p(lp)
        {
					if (p != NULL)
						p->AddRef();
				}

				SmartPointer(const SmartPointer<T> & other) : p(other.p)
				{
					if (p != NULL)
						p->AddRef();
				}

        /// <summary>
        /// ����������.
        /// </summary>
        ~SmartPointer()
        {
					T* pTemp = p;
					if (pTemp)
					{
						p = NULL;
						pTemp->Release();
					}
        }
				//The assert on operator& usually indicates a bug.  If this is really
				//what is needed, however, take the address of the p member explicitly.
				T** operator&() // throw()
				{
#if _ITERATOR_DEBUG_LEVEL == 2
					if (p!=NULL)
						throw KernelException("p != NULL");
#endif
					return &p;
				}
        operator T*() const throw()
        {
          return p;
        }
        T& operator*() const
        {
#if _ITERATOR_DEBUG_LEVEL == 2
          if (!p)
            throw NullReferenceException("p");
#endif
          return *p;
        }
        NoAddRefReleaseOnIExportable<T>* operator->() const
        {          
#if _ITERATOR_DEBUG_LEVEL == 2
          if (!p)
            throw NullReferenceException("p");          
#endif
          return (NoAddRefReleaseOnIExportable<T>*)p;
        }
        bool operator!() const throw()
        {	
          return (p == NULL);
        }

				bool operator!=(_In_opt_ T* pT) const throw()
        {
					return p != pT;//!operator==(pT);
        }
        bool operator==(_In_opt_ T* pT) const throw()
        {
          return p == pT;
        }
                
        /// <summary>
        /// ����������� ������ �� ��������� � ������������� �� �������� � NULL
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
            /*int ref = */
            p->Release();
            /*(ref);*/
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
					if (ppT == NULL)
						return;
          *ppT = p;
          if (p)
            p->AddRef();
        }

        T* Copy() const
        {
          if (p)
            p->AddRef();
          return p;
        }

        T* operator=(_Inout_opt_ T* lp) throw()
        {
					if (p != lp)
					{			
						SmartPointer(lp).Swap(*this);
					}
          return *this;
        }

        T* operator <<=(_Inout_opt_ T* lp) throw()
        {
					if (p != lp)
            Attach(lp);
          return *this;
        }

        T* operator=(_Inout_ const SmartPointer<T>& lp) throw()
        {
					if (p != lp)
            SmartPointer(lp.p).Swap(*this);
          return *this;
        }	        

     #ifndef __GNUG__
        T* operator=(_Inout_ SmartPointer<T>&& lp) throw()
        {			
					if (p != lp)
            SmartPointer(static_cast<SmartPointer<T>&&>(lp)).Swap(*this);
          return *this;		
        }
     #endif

        /// <summary>
        /// ������������� ��������� ����� ����������� ������� ���� T
        /// </summary>
        void Create()
        {
          Attach(new T());
        }

        /// <summary>
        /// ������������� ��������� ����� ����������� ������� ���� Q
        /// </summary>
        template <class Q>
        void Create()
        {
          Attach(new Q());
        }

        T * p;
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller