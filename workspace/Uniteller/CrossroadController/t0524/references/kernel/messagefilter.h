// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include "imessagefilter.h"
#include <set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#ifndef __GNUG__
#include "avltree.h"
#else
  #include "linux/messagefilter.h"
  #define index_set std::set
#endif // __GNUG__

#ifndef __GNUG__
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      /// <summary>
      /// ���������� ������� ���������
      /// </summary>
      class MessageFilter : public Exportable<IMessageFilter>
      {
      private:
				index_set<int> m_Filter;
				typedef index_set<int>::const_iterator iterator;
        std::mutex mx;
      public:
        /// <summary>
        /// �����������. ��-��������� ������������� ��� ���������� � �����������
        /// <summary>
				MessageFilter() : m_IsExclusive(false)
        {
        }
        // �������� �� ������ ������������
        PROPERTY_IMPLEMENTATION(bool, IsExclusive);
        /// <summary>
        /// ��������� �������� ������������
        /// </summary>
        void Clear()
        {
          std::unique_lock<std::mutex> lk(mx);
          m_Filter.clear();
        }
        /// <summary>
        /// ��������� �������� ������� � ������������ (� �����)
        /// </summary>
        /// <param name="value">��������, ����������� � ������������</param>
        void Add(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
					m_Filter.insert(value);
        }
        /// <summary>
        /// ��������� �������� ������� �� ������������ �� �������
        /// </summary>
        /// <param name="index">������ �������� ������������</param>
        /// <returns>������� ������������ � �������� index</returns>
        int GetItem(int index)
        {
          std::unique_lock<std::mutex> lk(mx);
          return m_Filter[index];
        }
        /// <summary>
        /// ��������� ���������� ������ �������� � ���������, ���� ��� ��� �����������
        /// </summary>
        /// <param name="value">�������� ��� ������ � ������������</param>
        /// <param name="startIndex">�������� ����� � �������� � ��������</param>
        /// <returns>������ ���������� ��������� value ��� -1 � ������, ���� �������� ���</returns>
        int IndexOf(const int & value, const int /*startIndex*/ = 0)
        {
          std::unique_lock<std::mutex> lk(mx);
					iterator i = m_Filter.find(value);
					if (i != m_Filter.end())
					{
						size_t pos = i - m_Filter.begin();
						return pos;
					}
          return -1;
        }
        /// <summary>
        /// ��������� ������ ����������� �� ��������� �������� ���������
        /// </summary>
        bool Contains(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
					iterator i = m_Filter.find(value);
					const iterator e = m_Filter.end();
					if (i != e)
						return true;

				  int code = value & 0xFFFF0000;
					i = m_Filter.find(code);
					return (i != e);
        }
        const size_t GetCount() const
        {
					return m_Filter.size();
        }
        /// <summary>
        /// ��������� ��������� ��� ���������, �� ������� � ��������
        /// </summary>
        /// <param name="message">��������� ��� �������� �� ������� ��������</param>
        /// <returns>true - ���� ��������� ��������� ��������, false - ����� </returns>
        bool Check(int message)
        {
          return m_IsExclusive ? !Contains(message) : Contains(message) || Contains(0);
        }
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework
} // ������������ ���� Uniteller
#endif
