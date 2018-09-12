// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������-������������

#pragma once

#include "icollection.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// ��������� ���������
      /// </summary>
      template <class T>
      interface ISet : public ICollection<T>
      {
      public:
        /// <summary>
        /// ��������� ������ ����������� �� ��������� �������� ���������
        /// </summary>
        virtual bool Contains(const T & value) = 0;
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller