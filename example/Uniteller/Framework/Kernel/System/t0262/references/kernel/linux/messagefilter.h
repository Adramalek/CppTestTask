// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include <set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

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
        std::map<int, size_t> m_Index;
        std::vector<int> m_Filter;
        typedef std::map<int, size_t>::iterator index_iterator;
        typedef std::map<int, size_t>::const_iterator const_index_iterator;
        std::mutex mx;
      public:
        /// <summary>
        /// �����������. ��-��������� ������������� ��� ���������� � �����������
        /// <summary>
        MessageFilter()
        {
          m_IsExclusive = false;
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
          m_Index.clear();
        }
        /// <summary>
        /// ��������� �������� ������� � ������������ (� �����)
        /// </summary>
        /// <param name="value">��������, ����������� � ������������</param>
        void Add(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
          const_index_iterator i = m_Index.find(value);
          if (i == m_Index.end())
          {
            size_t index = m_Filter.size();
            m_Filter.push_back(value);
            m_Index.insert(std::make_pair(value,index));
          }
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
          const_index_iterator i = m_Index.find(value);
          if (i != m_Index.end())
            return (int)i->second;
          return -1;
        }
        /// <summary>
        /// ��������� ������ ����������� �� ��������� �������� ���������
        /// </summary>
        bool Contains(const int & value)
        {
          std::unique_lock<std::mutex> lk(mx);
          const_index_iterator i = m_Index.find(value);
          bool result = (i != m_Index.end());
          if (!result)
          {
            int code = value & 0xFFFF0000;
            i = m_Index.find(code);
            return (i != m_Index.end());
          }
          return result;
        }
        const size_t GetCount() const
        {
          return m_Index.size();
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
