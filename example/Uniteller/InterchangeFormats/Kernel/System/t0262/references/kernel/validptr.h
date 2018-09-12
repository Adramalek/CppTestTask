// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит функции проверки корректности

#pragma once

#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      // Verify that a pointer points to valid memory inline
      inline bool isValidAddress(const void* p, size_t nBytes,
        BOOL bReadWrite = TRUE) throw()
      {
        //bool bResult;
        //try
        //{
        return ((p != NULL) && !IsBadReadPtr(p, nBytes) &&
          (!bReadWrite || !IsBadWritePtr(const_cast<LPVOID>(p), nBytes)));
        //}
        //catch (...)
        //{
        //	bResult = false;
        //}
        //return bResult;
      }

      inline bool isValidComPointer(IMessage * p) throw()
      {	
        try
        {
          // Элементарнейшая проверка на NULL. Если бы все было так легко
          if (!p)
            return false;
          // проверяем адрес: 
          if ( !isValidAddress(p, sizeof( IMessage ), FALSE ) ) 
            return false;
          // Проверка на ужасный мусор в памяти - совсем левый указатель
          // * ( void** ) должен указывать на vtable. Указатель на vtable
          // должен быть корректен
          void ** p0 =  ( void** ) p;
          if (!p0)
            return false;
          if ( !isValidAddress( p0, sizeof( void** ), FALSE ) )
            return false;
          void * p1 =  * ( void** ) p;
          if (!p1)
            return false;
          if ( !isValidAddress( p1, sizeof( void* ), FALSE ) )
            return false;
          // удостовериваемся, что указатель на vtable корректен
          void** vfptr = ( void** ) * ( void** ) p;
          if ( !isValidAddress( vfptr, sizeof( void* ), FALSE ) )
            return false;

          // проверяем первую запись vtable
          void* pvtf0 = vfptr[ 0 ];
          // У IDispatch точно есть одна функция
          if ( IsBadCodePtr( ( FARPROC ) pvtf0 ) )
            return false;

          if ( !isValidAddress(p, sizeof( IExportable ), TRUE ) ) 
            return false;

          // Еще одна злая проверка

          //// По идее, код выше должен решить вопросы с inproc объектом
          //// Если мы имеем дело с outproc объектом, то попробуем с помощью QueryInterface
          //t * p3 = NULL;
          //HRESULT hr = p->QueryInterface(__uuidof(t), reinterpret_cast<void **>(&p3));
          //if (FAILED(hr))
          //  return false;
          //if (!p3)
          //  return false;
          //if ( !isValidAddress( p3, sizeof( void* ), FALSE ) )
          //  return false;
          //// Дополнительная проверка
          //if ( !isValidAddress(p, sizeof( t ), FALSE ) ) 
          //  return false;
          //p3->Release();
          return true;
        }
        catch (...)
        {    
        }
        return false;
      }


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller