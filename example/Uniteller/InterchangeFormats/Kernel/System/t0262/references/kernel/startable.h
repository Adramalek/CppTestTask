// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���������� ��������������� �� dll �������
#pragma once

#include <list>
#include "istartable.h"
#include "exportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// ������� ���������� ������������ �������
      /// <summary>
      template <class T, class C>
      class Startable : public Exportable<T>
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsStartable OnlyExportable;

      public: // ��������
        // ������� ��
        READONLY_PROPERTY_IMPLEMENTATION(bool, IsStarted);
      public:
        /// <summary>
        /// �����������, ������������� ������� ������ � �������
        /// </summary>
        Startable() : m_IsStarted(false)
        {
        }
        /// <summary>
        /// ��������� ����������� ������
        /// </summary>
        void Start(C * context)
        {
          if (!m_IsStarted)
            m_IsStarted = OnStart(context);
        }
        /// <summary>
        /// ������������� ����������� ������
        /// </summary>
        void Stop()
        {
          if (m_IsStarted)
            m_IsStarted = !OnStop();
        }

        /// <summary>
        /// ��������� ��������� ��������� � ������ �������
        /// </summary>
        /// <returns>���������� ���� - ������ �� ��� ������ (true - ��������� �������, false - ��������� �� �������).</returns>
        virtual bool OnStart(C * /*context*/)
        {
          return true;
        }
        /// <summary>
        /// ��������� ��������� ��������� � ������ ���������
        /// </summary>
        /// <returns>���������� ���� - ������ �� ������ ��������� (true - ���������� �������, false - ���������� �� �������).</returns>
        virtual bool OnStop()
        {
          return false;
        }       
      };


      /// <summary>
      /// ������� ���������� ������������ �������
      /// <summary>
      template <class T>
      class Startable<T, void> : public Exportable<T>
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsStartable OnlyExportable;

      public: // ��������
        // ������� ��
        READONLY_PROPERTY_IMPLEMENTATION(bool, IsStarted);
      public:
        /// <summary>
        /// �����������, ������������� ������� ������ � �������
        /// </summary>
        Startable() : m_IsStarted(false)
        {
        }
        /// <summary>
        /// ��������� ����������� ������
        /// </summary>
        void Start()
        {
          if (!m_IsStarted)
            m_IsStarted = OnStart();
        }
        /// <summary>
        /// ������������� ����������� ������
        /// </summary>
        void Stop()
        {
          if (m_IsStarted)
            m_IsStarted = !OnStop();
        }

        /// <summary>
        /// ��������� ��������� ��������� � ������ �������
        /// </summary>
        /// <returns>���������� ���� - ������ �� ��� ������ (true - ��������� �������, false - ��������� �� �������).</returns>
        virtual bool OnStart()
        {
          return true;
        }
        /// <summary>
        /// ��������� ��������� ��������� � ������ ���������
        /// </summary>
        /// <returns>���������� ���� - ������ �� ������ ��������� (true - ���������� �������, false - ���������� �� �������).</returns>
        virtual bool OnStop()
        {
          return true;
        }       
      };

      template <class T>
      class startable_list : public std::list<T>
      {
      public:
        void clear()
        {
          typename std::list<T>::const_iterator e = std::list<T>::end();
          typename std::list<T>::const_iterator i = std::list<T>::begin();
          while (i!=e)
          {
            T startable = *i;
            startable->Stop();
            startable->Release();
            ++i;
          }
          std::list<T>::clear();
        }
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller