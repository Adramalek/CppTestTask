// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include "ivariant.h"
#include <chrono> // std::system_clock

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      typedef const char * address;
      typedef unsigned int event_t;      
      typedef std::chrono::system_clock::time_point timestamp_t;
      
      /// <summary>
      /// ��������� ���������
      /// </summary>
      interface IMessage : public IExportable
      {
      public: // ��������
        
        // ���������
        READONLY_PROPERTY_DECLARATION(int, Generation);
        // ��� ���������
        READONLY_PROPERTY_DECLARATION(event_t, Kind);

        // ���������
        PROPERTY_DECLARATION(int, Priority);
        // ����� ���������� ���������
        PROPERTY_DECLARATION(size_t, ArgumentsCount);
        // ������������� ��������� ���������
        PROPERTY_DECLARATION_STRING(SourceId);
        // ������������� ��������� ���������
        PROPERTY_DECLARATION_STRING(TargetId);
        // ����� �������� ���������
        PROPERTY_DECLARATION(timestamp_t, SendTime);               
      public: // ������

        /// <summary>
        /// ��������� �������� ������ ���������� ���������
        /// </summary>
        virtual void Clear() = 0;

        /// <summary>
        /// ��������� �������� �������� ��������� �� �������
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <returns>�������� ���������</returns>
        virtual IVariant * GetArgument(size_t index) = 0;
        /// <summary>
        /// ��������� ���������� �������� ��������� �� �������
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <param name="value">�������� ���������</param>
        virtual void SetArgument(size_t index, IVariant * value) = 0;
        /// <summary>
        /// ��������� ���������� �������� ��������� �� ������� (����� �������������)
        /// </summary>
        /// <param name="index">������ ���������</param>
        /// <param name="value">�������� ���������</param>
        virtual void SetArgumentTo(size_t index, IVariant * value) = 0;
      };

      // ��������� �� ���������
      typedef SmartPointer<IMessage> MessagePtr;

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller