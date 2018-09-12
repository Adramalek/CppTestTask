// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� �������� ������������

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
          // ��������������� �������� �� NULL. ���� �� ��� ���� ��� �����
          if (!p)
            return false;
          // ��������� �����: 
          if ( !isValidAddress(p, sizeof( IMessage ), FALSE ) ) 
            return false;
          // �������� �� ������� ����� � ������ - ������ ����� ���������
          // * ( void** ) ������ ��������� �� vtable. ��������� �� vtable
          // ������ ���� ���������
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
          // ����������������, ��� ��������� �� vtable ���������
          void** vfptr = ( void** ) * ( void** ) p;
          if ( !isValidAddress( vfptr, sizeof( void* ), FALSE ) )
            return false;

          // ��������� ������ ������ vtable
          void* pvtf0 = vfptr[ 0 ];
          // � IDispatch ����� ���� ���� �������
          if ( IsBadCodePtr( ( FARPROC ) pvtf0 ) )
            return false;

          if ( !isValidAddress(p, sizeof( IExportable ), TRUE ) ) 
            return false;

          // ��� ���� ���� ��������

          //// �� ����, ��� ���� ������ ������ ������� � inproc ��������
          //// ���� �� ����� ���� � outproc ��������, �� ��������� � ������� QueryInterface
          //t * p3 = NULL;
          //HRESULT hr = p->QueryInterface(__uuidof(t), reinterpret_cast<void **>(&p3));
          //if (FAILED(hr))
          //  return false;
          //if (!p3)
          //  return false;
          //if ( !isValidAddress( p3, sizeof( void* ), FALSE ) )
          //  return false;
          //// �������������� ��������
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


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller