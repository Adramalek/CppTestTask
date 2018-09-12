#pragma once

#include <map>
#include <string>
#include "smartpointer.h"
#include "iexportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      /// <summary>
      /// ��������� ���������� ������ ��������� �������
      /// </summary>
      template <class T>
      class ExportableDictionary
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsExportable OnlyExportable;
      private:
        std::map<std::string, T> m_Variables;
        typedef typename std::map<std::string, T>::iterator iterator;
      public: 
        /// <summary>
        /// ������������ ����� �� ���������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <returns></returns>
        T GetItem(const std::string & s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
            return it->second;
          }
          return NULL;
        }

        /// <summary>
        /// ������������ ����� �� ���������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <returns></returns>
        T GetItem(const char * s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
            return it->second;
          }
          return NULL;
        }  

        /// <summary>
        /// ��������� � ��������� �������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <param name="value">��������</param>
        void Add(const std::string& s, T value)
        {
          iterator it = m_Variables.find(s);
          if (it != m_Variables.end())
          {           
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));

        }

        /// <summary>
        /// ��������� � ��������� �������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <param name="value">��������</param>
        void Add(const char* s, T value)
        {
          iterator it = m_Variables.find(s);
          if (it != m_Variables.end())
          {            
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// ��������� �������� ��������� �������
        /// </summary>
        void Clear()
        {
          m_Variables.clear();
        }

        ~ExportableDictionary()
        {
          Clear();
        }
      };

      /// <summary>
      /// ��������� ���������� ������ ��������� ������� ��� ����������
      /// </summary>
      template <class T>
      class ExportableDictionary<T *>
      {
        // � �������� ��������� ������� ���������� ���������, ����������� IExportable
        typedef typename T::IsExportable OnlyExportable;
      private:
        std::map<std::string, T *> m_Variables;
        typedef typename std::map<std::string, T *>::iterator iterator;
      public:

        /// <summary>
        /// ������������ ����� �� ���������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <returns></returns>
        T * GetItem(const std::string & s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
          {
              T * p=it->second;
              if (p)
                p->AddRef(); // ����������� ������� ������, ������ ��� ������� ��������
              return p;
          }
          return NULL;
        }

        /// <summary>
        /// ������������ ����� �� ���������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <returns></returns>
        T * GetItem(const char * s)
        {
          iterator it=m_Variables.find(s);
          if (it!=m_Variables.end())
            {
              T * p=it->second;
              if (p)
                p->AddRef(); // ����������� ������� ������, ������ ��� ������� ��������
              return p;
            }
          return NULL;
        }  

        /// <summary>
        /// ��������� � ��������� �������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <param name="value">��������</param>
        void Add(const std::string& s, T * value)
        {
          iterator it = m_Variables.find(s);
          value->AddRef();
          if (it != m_Variables.end())
          {            
            it->second->Release();
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
          
        }

        /// <summary>
        /// ��������� � ��������� �������
        /// </summary>
        /// <param name="s">��� �����</param>
        /// <param name="value">��������</param>
        void Add(const char* s, T * value)
        {
          iterator it = m_Variables.find(s);
          value->AddRef();
          if (it != m_Variables.end())
          {            
            it->second->Release();
            it->second = value;
          }
          else
            m_Variables.insert(std::make_pair(s, value));
        }

        /// <summary>
        /// ��������� �������� ��������� �������
        /// </summary>
        void Clear()
        {
          for (iterator it=m_Variables.begin(); it!=m_Variables.end();++it)
          {
            T * p=it->second;
            if (p)
              p->Release();
          }
          m_Variables.clear();
        }

        ~ExportableDictionary<T *>()
        {
          Clear();
        }
      };
   
    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller