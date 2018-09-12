#pragma once

#include <vector>
#include "ienumeration.h"
#include "ivariant.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      template <class X>
      inline X VariantPtrTo(IVariant * value);

      /// <summary>
      /// ���������� ��������������� ������������
      /// </summary>
      template <class T>
      class ExportableEnumeration : public Exportable<IEnumeration<T *>>
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsExportable OnlyExportable;

        // ������������ ��� �������� ������
        std::vector<T *> m_Data;
      public: // ��������
        /// <summary>
        /// ���������� ����� ��������� � ������������
        /// </summary>
        /// <returns></returns>
        const size_t GetCount() const
        {
          return m_Data.size();
        }
      public:
        /// <summary>
        /// �����������
        /// </summary>
        ExportableEnumeration()
        {
        }
				ExportableEnumeration(const ExportableEnumeration & src)
				{
					size_t max = src.m_Data.size();
					m_Data.resize(max);
					for (size_t i = 0; i < max; ++i)
					{
						m_Data[i] = src.m_Data[i];
						m_Data[i]->AddRef();
					}
				}
        ~ExportableEnumeration()
        {
          Clear();
        }
      public: // ������
        /// <summary>
        /// ��������� �������� ������� �� ������������ �� �������
        /// </summary>
        /// <param name="index">������ �������� ������������</param>
        /// <returns>������� ������������ � �������� index</returns>
        T * GetItem(int index) 
        {
          T * p = m_Data[index];
          if (p)
            p->AddRef();
          return p;
        }          
        /// <summary>
        /// ��������� �������� ������� �� ������������ �� ������� � ��������������� � ���������� ����
        /// </summary>
        /// <param name="index">������ �������� ������������</param>
        /// <returns>������� ������������ � �������� index</returns>
        template <class Y>
        const Y GetItem(int index)
        {
          T * p = m_Data[index];
          if (p)
            return VariantPtrTo<Y>(p);
          return Y();
        }
        /// <summary>
        /// ��������� �������� ������� �� ������������ �� ������� � ��������������� � ���������� ����
        /// </summary>
        /// <param name="index">������ �������� ������������</param>
        /// <param name="defvl">�������� ��-���������</param>
        /// <returns>������� ������������ � �������� index</returns>
        template <class Y>
        const Y GetItem(int index, const Y & defvl)
        {
          T * p = m_Data[index];
          if (p)
            return VariantPtrTo<Y>(p);
          return defvl;
        } 
        /// <summary>
        /// ��������� �������� ������������
        /// </summary>
        void Clear()
        {
          size_t max = m_Data.size();
          for (size_t i = 0; i<max; ++i)
          {
            T * p = m_Data[i];
            //if (p) - ������ ���� �� �����
              p->Release();
          }
          m_Data.resize(0);
        }
        /// <summary>
        /// ��������� �������� ������� � ������������ (� �����)
        /// </summary>
        /// <param name="value">��������, ����������� � ������������</param>
        void Add(T * value)
        {
          if (value)
          {
            value->AddRef();
            m_Data.push_back(value);
          }
        }  
        /// <summary>
        /// ��������� ���������� ��� ������������ � ����
        /// </summary>
        /// <param name="other">������������ ��� ����������� � ������.</param>
        void MergeWith(IEnumeration<T *> * other)
        {
          size_t max = other->GetCount();
          for (size_t i = 0; i<max; ++i)
            m_Data.push_back(other->GetItem(i));
        }

        ExportableEnumeration<T> & operator=(const ExportableEnumeration<T>& src)
        {
          size_t max = src.m_Data.size();
          m_Data.resize(max);
          for (size_t i = 0; i < max; ++i)
          {
            m_Data[i] = src.m_Data[i];
            m_Data[i]->AddRef();
          }
          return *this;
        }

      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller