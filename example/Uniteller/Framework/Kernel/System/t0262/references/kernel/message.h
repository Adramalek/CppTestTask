// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ���������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include "imessage.h" // IMessage
#include "variant.h" // Variant
#include "smartpointer.h" // SmartPointer<T>
#include <vector> // std::vector

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      using std::vector;

      typedef SmartPointer<Variant> VariantPtr;

      /// <summary>
      /// ������� ����� ��� ���� ���������, ������������ �� ���� �������� ���������
      /// </summary>
      class Message : public Exportable<IMessage>
      {
      private:
        vector<IVariant *> m_Arguments;
      public: // ��������
        // ���������
        PROPERTY_IMPLEMENTATION(int, Priority);
        // ������������� ��������� ���������
        PROPERTY_IMPLEMENTATION_STRING(SourceId);
        // ������������� ��������� ���������
        PROPERTY_IMPLEMENTATION_STRING(TargetId);
				
        // ���������
        READONLY_PROPERTY_IMPLEMENTATION(int, Generation);
        // ��� ���������
        READONLY_PROPERTY_IMPLEMENTATION(event_t, Kind);
        // ����� �������� ���������
        PROPERTY_IMPLEMENTATION(timestamp_t, SendTime);

      public: // ������
        
        /// <summary>
        /// �������������� ����� ��������� ��������� <see cref="Message"/>.
        /// </summary>
        /// <param name="kind">��� ���������.</param>
        /// <param name="generation">���������.</param>
        Message(int kind, int generation) : m_Priority(0), m_Generation(generation), m_Kind(kind),					
          m_SendTime(std::chrono::system_clock::now())
        {          
        }
        /// <summary>
        /// �������������� ����� ��������� ��������� <see cref="Message"/>.
        /// </summary>
        /// <param name="kind">��� ���������.</param>
        /// <param name="generation">���������.</param>
        /// <param name="priority">���������.</param>
        Message(int kind, int generation, int priority, const char * szSource, const char * szTarget) : m_Priority(priority), 
          m_SourceId(szSource), m_TargetId(szTarget), m_Generation(generation), m_Kind(kind),           
					m_SendTime(std::chrono::system_clock::now())
        {
        }
        /// <summary>
        /// �������������� ����� ��������� ��������� <see cref="Message"/> class.
        /// </summary>
        /// <param name="kind">��� ���������.</param>
        /// <param name="generation">���������.</param>
        /// <param name="argc">����� ����������.</param>
        Message(int kind, int generation, int argc) : m_Arguments(argc), m_Priority(0), m_Generation(generation),  m_Kind(kind),
					m_SendTime(std::chrono::system_clock::now())
        {          
          SetArgumentsCount(argc);          
        }

        ~Message()
        {
          Clear();
        }

        /// <summary>
        /// ��������� �������� ������ ���������� ���������
        /// </summary>
        void Clear()
        {
					SetArgumentsCount(0);
        }

        /// <summary>
        /// ��������� �������� �������� ��������� �� �������
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <returns>�������� ���������</returns>
        IVariant * GetArgument(size_t index) override
        {
          if (index<m_Arguments.size())
          {
            IVariant * result = m_Arguments[index];
            if (result)
            {
              result->AddRef();
              return result;
            }
            return new Variant(); // Empty!
          }
          switch (index)
          {
          case (size_t)-2:
            return new Variant(m_SourceId);
          case (size_t)-3:
            return new Variant(m_TargetId);
          case (size_t)-4:
            return new Variant(m_Generation);
          case (size_t)-5:
            return new Variant(m_Kind);
          case (size_t)-6:
            return new Variant((int)m_Arguments.size());
          case (size_t)-7:
            return new Variant(m_Priority);
          case (size_t)-8:
            return new Variant(m_SendTime);
          }
          return NULL;
        }
        
        /// <summary>
        /// ��������� ���������� �������� ��������� �� �������
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <returns>�������� ���������</returns>
        void SetArgument(size_t index, IVariant * value)
        {
          if (index < m_Arguments.size())
          {
            IVariant * v = m_Arguments[index];
            m_Arguments[index] = new Variant(value);
            if (v)
            {
              v->Release();
              v = NULL;
            }
          }
          else
            throw OutOfRangeException("������ ������� �� ������� �������");
        }

        PROPERTY(size_t, ArgumentsCount);
        void SetArgumentsCount(const size_t & value)
        {
          size_t current = m_Arguments.size();
          if (current > value)
            Reduce(value, current);
          else
            if (current < value)
							m_Arguments.resize(value, NULL);
              //Expand(value, current);          
        }
        /// <summary>
        /// ���������� ����� ���������� � ���������
        /// </summary>
        const size_t GetArgumentsCount() const
        {
          return m_Arguments.size();
        }
      private:
        
        /// <summary>
        /// ��������� ������ ����� ���������� �� ��������, ����������� � ��������� size.
        /// </summary>
        /// <param name="size">�������� ������ ����� ����������</param>
        /// <param name="current">������� ������ ����� ����������</param>
        void Reduce(const size_t size, const size_t current)
        {
          for (size_t i = size; i<current; ++i)
          {
            IVariant * arg = m_Arguments[i];
            if (arg)
						{
							m_Arguments[i] = NULL;
              arg->Release();
              arg = NULL;
            }
          }
          m_Arguments.resize(size);
        }

        /// <summary>
        /// ��������� ���������� �������� ��������� �� �������
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <returns>�������� ���������</returns>
        void SetArgumentTo(size_t index, IVariant * value)
        {
          if (index < m_Arguments.size())
          {
            IVariant * v = m_Arguments[index];
            if (v)
            {
              v->Release();
              v = NULL;
            }
            if (value)
            {
              m_Arguments[index] = value;
              value->AddRef();
            }
            else
              m_Arguments[index] = new Variant();
          }
          else
						throw OutOfRangeException("������ ������� �� ������� �������");
        }
      };


    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller