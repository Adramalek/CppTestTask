// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ���������, ������������� �� ���� �������� ���������

#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdarg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      namespace Utils
      {

        /// <summary>
        /// �������� ��� ��������� ������ pattern � ������ source ������� value
        /// </summary>
        /// <param name="source">�������� ������</param>
        /// <param name="pattern">���������� ���������</param>
        /// <param name="value">������ ������</param>
        /// <returns></returns>
        std::string ReplaceAll(const char * source, const char * pattern, const char * value);

        /// <summary>
        /// �������� ��� ��������� ������ pattern � ������ source ������� value
        /// </summary>
        /// <param name="source">�������� ������</param>
        /// <param name="pattern">���������� ���������</param>
        /// <param name="value">������ ������</param>
        /// <returns></returns>
        std::string ReplaceAll(const std::string& source, const std::string& pattern, const std::string& value);

        /// <summary>
        /// ����������� ������
        /// </summary>
        /// <param name="fmt">�������� ������</param>
        /// <param name=""></param>
        /// <returns></returns>
        std::string FormatString(const char * fmt, ...);

        /// <summary>
        /// ����������� ������
        /// </summary>
        /// <param name="fmt">�������� ������</param>
        /// <param name=""></param>
        /// <returns></returns>
        std::string FormatString(const char * fmt, va_list args);

        /// <summary>
        ///  �������� �� ������ ���� Key1\Key2 Key1 � Key2
        /// </summary>
        /// <param name="sKey">�������� ������ Key1\Key2</param>
        /// <param name="sRoot">������ key1</param>
        /// <param name="sRelative">������ key2</param>
        /// <returns></returns>
        bool GetRootAndRelative(const std::string & sKey, std::string & sRoot,
          std::string & sRelative);

        std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems);
        std::vector<std::string> Split(const std::string &s, char delim);
				
        /// <summary>
        /// ������� ���������� ������� � ������ �������� ������
        /// </summary>
        /// <param name="s">�������� ������</param>
        /// <returns></returns>
        static inline std::string &TrimLeft(std::string &s) 
        {
          s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
          return s;
        }
				
        /// <summary>
        /// ������� ������� � ������ ������
        /// </summary>
        /// <param name="s">�������� ������</param>
        /// <returns></returns>
        static inline std::string &TrimRight(std::string &s) 
        {
          s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
          return s;
        }

        /// <summary>
        /// ������� ���������� ������� ��� �������� ������
        /// </summary>
        /// <param name="s">�������� ������</param>
        /// <returns></returns>
        static inline std::string Trim(const std::string & s) 
        {
          std::string::size_type pos = s.find_first_not_of(" \n\r\t");
          if (pos == std::string::npos)
            return "";

          std::string::size_type n = s.find_last_not_of(" \n\r\t") - pos + 1;
          return s.substr(pos, n);
        }

				static inline std::string TrimEnd(const std::string & s)
				{
					std::string::size_type n = s.find_last_not_of(" \n\r\t") + 1;
					return s.substr(0, n);
				}

        inline bool EndsWith(const std::string& a, const std::string& b) 
        {
          if (b.size() > a.size()) 
            return false;
          return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
        }

      inline bool StartsWith(const std::string& a, const std::string& b)
      {
        if (b.size() > a.size())
          return false;
        return std::equal(a.begin(), a.begin() + b.size(), b.begin());
      } 

        /// <summary>
        /// ��������� ��������� �������� �� ������ ������
        /// </summary>
        inline bool IsStringEmpty(const std::string & s)
        {
					return s.size() == 0;
          //return strcmp(s.c_str(), "")==0;
        }

        /// <summary>
        /// ��������� ��������� �������� �� ������ ��������
        /// </summary>
        inline bool IsStringNotEmpty(const std::string & s)
        {
					return s.size() != 0;
          //return strcmp(s.c_str(), "")!=0;
        }

        static inline void ParseArgument(const std::string & arg, std::string & argument, std::string & subargument)
        {
          size_t i = arg.find_first_of('.');
          if (i != std::string::npos)
          {
            argument = arg.substr(0,i);
            subargument = arg.substr(i+1);
          }
          else
          {
            argument = arg;
            subargument.clear(); // = "";
          }
        }

        const char * ExportLocal(const  std::string & s);

        /// <summary>
        /// ��������� ���� �� ��� ����� � ���� � ����
        /// </summary>
        /// <param name="path">������ ����</param>
        /// <param name="resPath">����</param>
        /// <param name="resName">����</param>
        void ExtractPath(const std::string & path, std::string& resPath, std::string& resName);

        /// <summary>
        /// ��������� ��������� �������� �� ������ s - ������
        /// </summary>
        /// <param name="s">������</param>
        /// <returns>True - ���� ������, ���������� ��� �������� s �������� ������</returns>
        bool IsNumber(const std::string& s);

        /// <summary>
        /// ��������� ���������� � ������� ����� ������������� ������ �� ����������
        /// </summary>
        /// <param name="val">������ ��� �������</param>
        /// <returns>���������� ���������� � ������� ����� ������������� ������</returns>
        std::vector<std::string> ParseInstructions(const std::string & val);

        /// <summary>
        /// ��������� ������� ������ � ������� �������
        /// </summary>
  	    inline std::string ToUpper(const std::string & text)
	      {
          std::string temp = text;
	        std::transform( temp.begin(), temp.end(), temp.begin(), ::toupper);
	        return temp;
  	    }
	      
        /// <summary>
        /// ��������� ������� ������ � ������ �������
        /// </summary>
        inline std::string ToLower(const std::string & text)
        {
          std::string temp = text;
          std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
          return temp;
        }

        /// <summary>
        /// ������������ ����-������ � hex-������
        /// </summary>
        std::string ToHex(const std::vector<unsigned char> & data);
        /// <summary>
        /// ������������ 16-��������� ����� � hex-������
        /// </summary>
        std::string ToHex(const unsigned short data);
        /// <summary>
        /// ������������ 8-��������� ����� � hex-������
        /// </summary>
        std::string ToHex(const unsigned char data);
        /// <summary>
        /// ������������ BCD-����� � int
        /// </summary>
        unsigned int BcdToInt(const std::vector<unsigned char> & bcd);

        bool FromHex(const std::string &s, std::vector<unsigned char> &v);
        unsigned char hex2nibble(char c);
        std::string& byteToHexAppend(const unsigned char b, std::string &res);
     
        inline bool CheckBounds(const std::string & arg, const char left, const char right)
        {
#ifndef __GNUG__
          return (arg.front()==left) && (arg.back()==right);
#else
#if __GNUC__ < 5
          return (arg[0]==left) && (arg[arg.size()-1]==right);
#else
          return (arg.front()==left) && (arg.back()==right);
#endif
#endif
        }

        inline std::string RemoveBounds(const std::string & arg)
        {
          return arg.substr(1, arg.size()-2);
        }


        inline bool IsExpression(const std::string & arg)
        {
          return CheckBounds(arg, '<', '>');
        }

        inline bool IsLink(const std::string & arg)
        {
          return CheckBounds(arg, '[', ']');
        }

        void EncodeLength(std::vector<unsigned char> & vector, size_t size); 
      }

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller

#define export_local(x) Uniteller::Framework::Kernel::Utils::ExportLocal(x)