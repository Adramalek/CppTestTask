// Uniteller.Framework
// Version: 1.0.0
// Generation: 1

// ���� �������� ������ ������� �������������� �������� "enum"-����� � �������������� �� ���������.

#pragma once

#include <string>

#define LITERAL_IN_QUOTES(lit) #lit

namespace Uniteller
{
  namespace Framework
  { 

        /// <summary>
        /// ����������� ��� ��������������� � ������������� �����, �� �������� � ���� ������ �������������� �������� � ������� �����������.
        /// </summary>
        /// <param name="typeTo">��� ������������ ���������</param>
        /// <param name="typeFrom"> ������������� ��� </param>
        /// <param name="min">Enum ��������� ������������ ����������� ��������</param>
        /// <param name="max">Enum ��������� ������������ ������������ ��������</param>
        /// <returns>
        /// ����� ������ ����� ��� � ������� ����������� ThisType::From().
        /// ��� ������ � ��� ���������� ���������� ������ �������� ThisType::Constants[].
        /// </returns>
        template <typename typeTo, typename typeFrom, typeFrom min, typeFrom max>
        struct Converter{
            static const typeTo Constants[1+(int)max-(int)min];
            
            static typeTo From (typeFrom value)
            {
                if ((value < min) || (value > max))
                    throw std::exception("Overflow value " LITERAL_IN_QUOTES(typeFrom) "!" ); // Kernel::CommonErrors::InvalidArgument;

                return Constants[(int)value-(int)min];
            }
        };

  } // ������������ ���� Framework 
} // ������������ ���� Uniteller