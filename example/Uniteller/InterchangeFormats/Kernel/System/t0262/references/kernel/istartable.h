// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ������������ �������

#pragma once

#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

#pragma region IStartable

      /// <summary>
      /// ��������� ������������ �������
      /// </summary>
      template <class T>
      interface IStartable : public IExportable
      {
      public: // ��������
        // ������� ��
        READONLY_PROPERTY_DECLARATION(bool, IsStarted);
      public: // ������
        /// <summary>
        /// ��������� ����������� ������
        /// </summary>
        /// <param name="context"> �������� </param>
        virtual void Start(T * context) = 0;
        /// <summary>
        /// ������������� ����������� ������
        /// </summary>
        virtual void Stop() = 0;


        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IExportable
        typedef int IsStartable;
      };

      /// <summary>
      /// ��������� ������������ �������
      /// </summary>
      template <>
      interface IStartable<void> : public IExportable
      {
      public: // ��������
        // ������� ��
        READONLY_PROPERTY_DECLARATION(bool, IsStarted);
      public: // ������
        /// <summary>
        /// ��������� ����������� ������
        /// </summary>
        virtual void Start() = 0;
        /// <summary>
        /// ������������� ����������� ������
        /// </summary>
        virtual void Stop() = 0;


        /// ������������ ������������������� ��������� ��� �������� ������������� ���������� IExportable
        typedef int IsStartable;
      };

#pragma endregion


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller