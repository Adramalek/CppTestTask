// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���������� ��������������� �� dll �������
#pragma once

#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
#ifdef __GNUG__
#if __GNUC__ < 5 
      long _InterlockedIncrement(long * x);
      long _InterlockedDecrement(long * x);
#endif
#endif

      /// <summary>
      /// ������� ���������� ��������������� �������
      /// <summary>
      template <class T>
      class Exportable : public T
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsExportable OnlyExportable;
        // ����� ������
        long m_nReferences;
      public:
        /// <summary>
        /// �����������, ������������� ������� ������ � �������
        /// </summary>
        Exportable() : m_nReferences(1)
        {
        }

        /// <summary>
        /// ����������� ������� ������ �� ���������������� ������ �� �������
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
        long AddRef() override
        { 
#ifndef __GNUG__
          return _InterlockedIncrement(&m_nReferences); // ++m_nReferences;
#else
#if __GNUC__ < 5 
          return _InterlockedIncrement(&m_nReferences); 
#else
          __sync_fetch_and_add(&m_nReferences, 1);
          return m_nReferences;
#endif
#endif
        }
        /// <summary>
        /// ��������� ������� ������ �� ���������������� ������ �� ������� 
        /// </summary>
        /// <returns>���������� ������� �������� �������� ������.</returns>
        long Release() override
        {			
#ifndef __GNUG__		
          if (_InterlockedDecrement(&m_nReferences) == 0)
#else
#if __GNUC__ < 5 
          if (_InterlockedDecrement(&m_nReferences) == 0)
#else
          if (__sync_fetch_and_sub(&m_nReferences, 1) == 1)
#endif
#endif
          {
            delete this;
            return 0;
          }
          return m_nReferences;
        }
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller
