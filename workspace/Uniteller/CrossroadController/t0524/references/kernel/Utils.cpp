// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию утилитарных функций
#include "utils.h"
#include <stdarg.h>
//#include <sstream>

#ifdef __GNUG__
#include "linuxsprt.h"
#endif

std::string m_buffer = "";

namespace Uniteller
{
	namespace Framework
	{
		namespace Kernel
		{

			char g_converter[260] = {
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1,
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				-1, -1, -1, -1, -1, -1, -1,
				10, 11, 12, 13, 14, 15,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1,
				10, 11, 12, 13, 14, 15,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			};

			namespace Utils
			{
				using std::string;

				/// <summary>
				/// Заменяет все вхождения строки pattern в строку source строкой value
				/// </summary>
				/// <param name="source">Исходная строка</param>
				/// <param name="pattern">Заменяемая подстрока</param>
				/// <param name="value">Строка замены</param>
				/// <returns></returns>
				string ReplaceAll(const std::string& source, const std::string& pattern, const std::string& value)
				{
					if (pattern.empty())
						return source;
					string str = source;
					size_t start_pos = 0;
					size_t pattern_length = pattern.length();
					size_t value_length = value.length();
					while ((start_pos = str.find(pattern, start_pos)) != std::string::npos)
					{
						str.replace(start_pos, pattern_length, value);
						start_pos += value_length; // In case 'to' contains 'from', like replacing 'x' with 'yx'
					}
					return str;
				}

				/// <summary>
				/// Заменяет все вхождения строки pattern в строку source строкой value
				/// </summary>
				/// <param name="source">Исходная строка</param>
				/// <param name="pattern">Заменяемая подстрока</param>
				/// <param name="value">Строка замены</param>
				/// <returns></returns>
				string ReplaceAll(const char * source, const char * pattern, const char * value)
				{
					string sPattern = pattern;
					if (sPattern.empty())
						return source;
					string str = source;
					size_t start_pos = 0;
					size_t pattern_length = sPattern.length();
					size_t value_length = strlen(value);
					while ((start_pos = str.find(pattern, start_pos)) != std::string::npos)
					{
						str.replace(start_pos, pattern_length, value);
						start_pos += value_length; // In case 'to' contains 'from', like replacing 'x' with 'yx'
					}
					return str;
				}

				/// <summary>
				/// Форматирует строку
				/// </summary>
				/// <param name="fmt">Исходная строка</param>
				/// <param name=""></param>
				/// <returns></returns>
				string FormatString(const char * fmt, ...)
				{
					int size = 100;
					string str;
					va_list ap;
					while (1)
					{
						str.resize(size);
						va_start(ap, fmt);
						int n = vsnprintf_s((char *)str.c_str(), size, _TRUNCATE, fmt, ap);
						va_end(ap);
						if ((n > -1) && (n < size))
						{
							str.resize(n);
							return str;
						}
						if (n > -1)
							size = n + 1;
						else
							size *= 2;
					}
					//return str;
				}

				/// <summary>
				/// Форматирует строку
				/// </summary>
				/// <param name="fmt">Исходная строка</param>
				/// <param name=""></param>
				/// <returns></returns>
				string FormatString(const char * fmt, va_list arg)
				{
					int size = 100;
					string str;
					while (1)
					{
						str.resize(size);
						int n = vsnprintf_s((char *)str.c_str(), size, _TRUNCATE, fmt, arg);
						if ((n > -1) && (n < size))
						{
							str.resize(n);
							return str;
						}
						if (n > -1)
							size = n + 1;
						else
							size *= 2;
					}
					//return str;
				}

				/// <summary>
				///  Проверяет, есть ли в ключе Key1\Key2 подключи Key1 и Key2
				/// </summary>
				/// <param name="sKey">Исходная строка Key1\Key2</param>
				/// <param name="sRoot">Строка key1</param>
				/// <param name="sRelative">строка key2</param>
				/// <returns></returns>
				bool GetRootAndRelative(const std::string & sKey, std::string & sRoot,
					std::string & sRelative)
				{
					const char * j = sKey.c_str();
					const size_t l = sKey.size();
					size_t nDelimeter;
					for (nDelimeter = 0; (nDelimeter < l) && (*j != '\\') && (*j != '/'); ++nDelimeter, ++j);

					if (nDelimeter != l)
					{
						if (nDelimeter == 0)
							return GetRootAndRelative(sKey.substr(1), sRoot, sRelative);
						//sRoot.assign(sKey, 0, nDelimeter);
						sRoot.assign(sKey, 0, nDelimeter);
						sRelative.assign(j + 1, l - nDelimeter - 1); // sKey.substr(nDelimeter + 1);
						return true;
					}
					sRoot.assign(sKey);
					sRelative.assign("",(size_t)0);
					return false;
				}

				//std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems)
				//{
				//	std::stringstream ss(s);
				//	std::string item;
				//	while (std::getline(ss, item, delim))
				//	{
				//		elems.push_back(item);
				//	}
				//	return elems;
				//}

				/// <summary>
				/// Возвращает строковый массив, содержащий подстроки данной строки, разделенные элементом delim
				/// </summary>
				/// <param name="s">Исходная строка</param>
				/// <param name="delim">Разделитель</param>
				/// <returns></returns>
				std::vector<std::string> Split(const std::string &s, char delim)
				{
					std::vector<std::string> elems;
					const char * str = s.c_str();
					const char * start = str;
					while (*str!=0)
					{
						if (*str == delim)
						{
							if (start < str)
								elems.push_back(string(start, str));
							start = str+1;
						}
						++str;
					}
					if (start < str)
						elems.push_back(start);

					//size_t l = s.size();
					//size_t begin = 0;
					//bool in_token = false;
					//for (size_t it = 0; it < l; ++it)
					//{
					//	if (s[it] == delim)
					//	{
					//		if (in_token)
					//		{
					//			elems.push_back(s.substr(begin, it-begin));
					//			in_token = false;
					//		}
					//	}
					//	else if (!in_token)
					//	{
					//		begin = it;
					//		in_token = true;
					//	}
					//}
					//if (in_token)
					//	elems.push_back(s.substr(begin));
					return elems;
				}

				const char * ExportLocal(const  std::string & s)
				{
					m_buffer = s;
					return m_buffer.c_str();
				}

				/// <summary>
				/// Разбивает путь на имя файла и путь к нему
				/// </summary>
				/// <param name="path">Полный путь</param>
				/// <param name="resPath">Путь</param>
				/// <param name="resName">Файл</param>
				void ExtractPath(const std::string & path, std::string& resPath, std::string& resName)
				{
#ifndef __GNUG__
					size_t pos = path.find_last_of('\\');
#else
					size_t pos = path.find_last_of('/');
#endif
					resPath = path.substr(0, pos);
          if (pos + 1 < path.length())
            resName = path.substr(pos + 1, path.length() - pos - 1);
          else
            resName.clear(); // = "";
				}

				bool IsNumber(const std::string& s)
				{
					std::string::const_iterator it = s.begin();
					while (it != s.end() && std::isdigit(*it)) ++it;
					return !s.empty() && it == s.end();
				}

				/* C Version */
				std::vector<std::string> ParseInstructions(const std::string & val)
				{
					std::vector<std::string> result;
					register const char * s = val.c_str();
					while (*s == ' ')
						++s;
					register const char * j = s;
					while (*s != '\0')
					{
						switch (*s)
						{
							case '"':
							{
								++s;
								register int k = 1;
								while ((*s != '\0') && (k > 0))
								{
									if (*s == '"')
										--k;
									++s;
								}
								break;
							}
							case ',':
							{
								register const char * z = s;
                while (((z - 1) > j) && ((*(z - 1) == ' ') || (*(z - 1) == '\t') || (*(z - 1) == '\r') || (*(z - 1) == '\n')))
									--z;
								result.push_back(std::string(j, z));
								++s;
								while (*s == ' ')
									++s;
								j = s;
								break;
							}
							case '<':
							{
								++s;
								register int k = 1;
								while ((*s != '\0') && (k > 0))
								{
									switch (*s)
									{
										case '<': ++k; break;
										case '>': --k; break;
									}
									++s;
								}
								break;
							}
							case '{':
							{
								++s;
								register int k = 1;
								while ((*s != '\0') && (k > 0))
								{
									switch (*s)
									{
										case '{': ++k; break;
										case '}': --k; break;
									}
									++s;
								}
								break;
							}
							default:
								++s;
								break;
						}
					}

					if (j < s)
					{
						const char * z = s;
            while (((z - 1) > j) && ((*(z - 1) == ' ') || (*(z - 1) == '\t') || (*(z - 1) == '\r') || (*(z - 1) == '\n')))
							--z;
						result.push_back(std::string(j, z));
					}
					return result;
				}

				/* C++ Version
				std::vector<std::string> ParseInstructions(const std::string & val)
				{
					std::vector<std::string> result;
					size_t max = val.size();
					size_t i = 0;
					size_t j = 0;
					while ((i < max) && (val[i] == ' '))
						++i;
					while (i < max)
					{
						switch (val[i])
						{
							case '"':
							{
								++i;
								int k = 1;
								while ((i < max) && (k>0))
								{
									if (val[i] == '"')
										--k;
									++i;
								}
								break;
							}
							case ',':
								result.push_back(Utils::TrimEnd(val.substr(j, i - j)));
								++i;
								while ((i < max) && (val[i] == ' '))
									++i;
								j = i;
								break;
							case '<':
							{
								++i;
								int k = 1;
								while ((i < max) && (k>0))
								{
									switch (val[i])
									{
										case '<': ++k; break;
										case '>': --k; break;
									}
									++i;
								}
								break;
							}
							default:
								++i;
								break;
						}
					}
					if (j < i)
					{
						result.push_back(Utils::TrimEnd(val.substr(j, i - j)));
					}
					return result;
				}*/

        unsigned char hex2nibble(char c)
        {
          char x = g_converter[(unsigned int)c];
          if (x<0)
            throw std::bad_cast();
          return x;
          //static char hex[] = "0123456789ABCDEF0123456789abcdef";
          //          
          //const char *pc = strchr(hex, c);
          //if (pc == NULL)
          //  throw std::bad_cast();
          ////ufw::error::enforce(0 != pc, "Invalid hex char: " + charToStr(c));
          //
          //return (pc - hex) & 0xf;
        }

        bool FromHex(const std::string &s, std::vector<unsigned char> &v) // appends data into the vector!!!
        {
          size_t max = s.size();
          if (max % 2)
            return false;
          for (unsigned i = 0; i < max;)
          {
            char hi = g_converter[(unsigned int)s[i++]];
            char lo = g_converter[(unsigned int)s[i++]];
            if ((hi < 0) || (lo < 0))
            {
              v.clear();
              return false;
            }
            v.push_back((hi << 4) | lo);
          }
          return true;
        }

        std::string& byteToHexAppend(const unsigned char b, std::string &res)
        {
          static const unsigned char hexSymb[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

          res += hexSymb[(b >> 4) & 0x0F];
          res += hexSymb[b & 0x0F];          

          return  res;
        }

        std::string ToHex(const std::vector<unsigned char> & data)
        {
          std::string res = "";
          size_t max = data.size();
          for (size_t i = 0; i<max; ++i)
          {
            byteToHexAppend(data[i], res);
          }
          return res;
        }

        std::string ToHex(const unsigned short data)
        {
          std::string res = "";
          byteToHexAppend(*((unsigned char*)(&data)), res);
          byteToHexAppend(*((unsigned char*)(&data) + 1), res);
          return res;
        }

        /// <summary>
        /// Конвертирует 8-разрядное число в hex-строку
        /// </summary>
        std::string ToHex(const unsigned char data)
        {
          std::string res = "";
          byteToHexAppend(data, res);
          return res;
        }


      void EncodeLength(std::vector<unsigned char> & vector, size_t size)
      {
        if (size<=127)
          vector.push_back(size);
        else
        {
          if (size<=0xFF)
          {
            vector.push_back(129);   // 1000 0001
            vector.push_back((unsigned __int8)size);
          }
          else
            if (size<=0xFFFF)
            {
              vector.push_back(130);   // 1000 0002
              vector.push_back((unsigned __int8)((size>>8)&0xFF));
              vector.push_back((unsigned __int8)(size&0xFF));
            }
            else
              if (size<=0xFFFFFF)
              {
                vector.push_back(131);   // 1000 0003
                vector.push_back((unsigned __int8)((size>>16)&0xFF));
                vector.push_back((unsigned __int8)((size>>8)&0xFF));
                vector.push_back((unsigned __int8)(size&0xFF));
              }
              else
                if (size<=0xFFFFFFFF)
                {
                  vector.push_back(132);   // 1000 0003
                  vector.push_back((unsigned __int8)((size>>24)&0xFF));
                  vector.push_back((unsigned __int8)((size>>16)&0xFF));
                  vector.push_back((unsigned __int8)((size>>8)&0xFF));
                  vector.push_back((unsigned __int8)(size&0xFF));
                }
        }
      }

        unsigned int BcdToInt(const std::vector<unsigned char> & bcd)
        {
          unsigned int result(0);
          size_t length = bcd.size();
          unsigned char * nybbles = (unsigned char *)bcd.data();
          while (length--) 
          {
            result = result * 100 + (*nybbles >> 4) * 10 + (*nybbles & 15);
            ++nybbles;
          }      
          return result;
        }

			} // пространство имен Utils
		} // пространство имен Kernel
	} // пространство имен Framework
} // пространство имен Uniteller
