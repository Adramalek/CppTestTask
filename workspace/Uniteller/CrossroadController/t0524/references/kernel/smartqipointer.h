// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию умного указателя (SmartPointer)

#pragma once

#include "kernel/smartpointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      /// <summary>
      /// Шаблон умного указателя, осуществляющего приведение интерфейсов
      /// </summary>
      template <class T>
      class SmartQiPointer : public SmartPointer<T>
      {
      public:
        /// <summary>
        /// Конструктор
        /// </summary>
        SmartQiPointer()
        {
        }
        /// <summary>
        /// Создает умный указатель, инициализирует его интерфейсом и автоматически увеличивает счетчик ссылок.
        /// </summary>
        /// <param name="lp">The lp.</param>
        SmartQiPointer(_Inout_opt_ T* lp) : SmartPointer<T>(lp)
        {
        }

        template <class Q>
        SmartQiPointer(_Inout_opt_ Q* lp) : SmartPointer<T>(dynamic_cast<T *>(lp))
        {
        }

        // Attach to an existing interface (does not AddRef)
        template <class Q>
        void Attach(_In_opt_ Q* p2) throw()
        {
          if (SmartPointer<T>::p)
          {
            /*int ref = */
            (SmartPointer<T>::p)->Release();
            /*(ref);*/
            // Attaching to the same object only works if duplicate references are being coalesced.  Otherwise
            // re-attaching will cause the pointer to be released and may cause a crash on a subsequent dereference.
            //ATLASSERT(ref != 0 || p2 != p);
          }
          (SmartPointer<T>::p) = dynamic_cast<T *>(p2);
        }

        template<class Q>
        T* operator <<=(_Inout_opt_ Q* lp) throw()
        {
          if((SmartPointer<T>::p)!=lp)
            Attach(lp);
          return *this;
        }

        template <class Q>
        T* operator=(_Inout_opt_ Q* lp) throw()
        {
          if((SmartPointer<T>::p)!=lp)
          {
            SmartPointer<T>(dynamic_cast<T *>(lp)).Swap(*this);
          }
          return *this;
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
