#include "StringUtils.h"
#include <regex>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      namespace System
      {
        namespace StringUtils 
        {
          /// <summary>
          /// Разбивает строчку по разделителю и возвращает список строк
          /// </summary>
          /// <param name="s">Исходная строка</param>
          /// <param name="delim">разделители</param>
          /// <param name="MultiDelims">Режим. False - разбивать по любому из разделителей, True - по точной последовательности</param>
          /// <param name="AllowEmpty">Допустимы ли пустые строки в результате</param>
          /// <returns></returns>
          std::list<std::string> Split(const std::string &s, const std::string & delim, bool MultiDelims, bool AllowEmpty)
          {
            std::list<std::string> result;
            if (delim.empty()) 
            {
              if (AllowEmpty || !s.empty()) 
                result.push_back(s);
              return result;
            }
            if (MultiDelims)
            {
              std::string::size_type cur_pos= s.find(delim), spos=0;
              if (cur_pos==std::string::npos)
              {
                if (AllowEmpty || !s.empty()) 
                  result.push_back(s);
                return result;
              }
              std::string temp, buffer = s;
              while (cur_pos!=std::string::npos)
              {
                temp=buffer.substr(spos, cur_pos-spos);
                if (AllowEmpty || !temp.empty()) 
                  result.push_back(temp);
                spos=cur_pos+delim.length();
                cur_pos=buffer.find(delim, spos);               
              }
              if (spos<=s.length())
              {
                temp=s.substr(spos, s.length()-spos);
                if (AllowEmpty || !temp.empty()) 
                  result.push_back(temp);
              }
             return result;
            }
            std::string::size_type cur_pos= s.find_first_of(delim), spos=0;
            //никакой из разделителей не найден
            if (cur_pos==std::string::npos)
            {
              if (AllowEmpty || !s.empty()) 
                result.push_back(s);
              return result;
            }
            std::string temp, buffer = s;
            while (cur_pos!=std::string::npos)
            {
              temp=buffer.substr(spos, cur_pos-spos);
              if (AllowEmpty || !temp.empty()) 
                result.push_back(temp);

              spos=cur_pos+1;
              cur_pos=buffer.find_first_of(delim, spos);                          
            }
            if (spos<=s.length())
            {
              temp=s.substr(spos, s.length()-spos);
              if (AllowEmpty || !temp.empty()) 
                result.push_back(temp);
            }
            return result;
          }

          /// <summary>
          /// Служебный метод-распаковщик для нужд Unpack
          /// </summary>
          /// <param name="pos">Стартовая позиция для поиска</param>
          /// <param name="len">Длина последовательности символа для поиска</param>
          /// <param name="source">Исходная строка</param>
          /// <param name="resHead">Головная часть</param>
          /// <param name="resTail">Хвостовая часть</param>
          void Unpacker( std::string::size_type pos, std::string::size_type len, const std::string &source, std::string &resHead, std::string &resTail )
          {
            if (pos>0 && pos<source.length()-len)
            {
              resHead=source.substr(0,pos);
              resTail=source.substr(pos+len,source.length()-pos-len);
            }
            else if (pos==0)
            {
              resHead="";
              resTail=source.substr(len,source.length()-len);
            }
            else if (pos==source.length()-len)
            {
              resHead=source.substr(0,source.length()-len);
              resTail="";
            }
          }

          /// <summary>
          /// Позволяет разбить строку source по первому вхождению символа delim на голову и хвост
          /// </summary>
          /// <param name="source">исходная строка</param>
          /// <param name="delim">Символ-разделитель</param>
          /// <param name="resHead">"Голова"</param>
          /// <param name="resTail">"Хвост"</param>
          /// <param name="MultiDelims">Режим работы функции. 0 - любой разделитель из указанных, 1 - точная последовательность</param>
          /// <returns></returns>
          void UnpackFirst(const std::string & source, const std::string & delim, std::string& resHead, std::string& resTail, bool MultiDelims)
          {
            if (source.empty()||delim.empty())
            {
              resHead="";
              resTail="";
              return;
            }
            if (!MultiDelims)
            {
              std::string::size_type pos = source.find_first_of(delim);
              if (pos==std::string::npos || pos>=source.length()) //для First возвращаем головную часть
              {
                resHead=source;
                resTail="";
                return;
              }
              //символ внутри строки
              Unpacker(pos, 1, source, resHead, resTail);              
            }
            else
            {
              std::string::size_type dlen=delim.length();
              //ищем первое точное вхождение подстроки delim 
              std::string::size_type pos=source.find(delim);
              if (pos==std::string::npos || pos>=source.length()) //для First возвращаем головную часть
              {
                resHead=source;
                resTail="";
                return;
              }
              Unpacker(pos, dlen, source, resHead, resTail);             
            }
          }

          /// <summary>
          /// Позволяет разбить строку source по последнему вхождению символа delim на голову и хвост
          /// </summary>
          /// <param name="source">исходная строка</param>
          /// <param name="delim">Символ-разделитель</param>
          /// <param name="resHead">"Голова"</param>
          /// <param name="resTail">"Хвост"</param>
          /// <param name="MultiDelims">Режим работы функции. 1 - любой разделитель из указанных, 0 - точная последовательность</param>
          /// <returns></returns>
          void UnpackLast(const std::string & source, const std::string & delim, std::string& resHead, std::string& resTail, bool MultiDelims)
          {
            if (source.empty()||delim.empty())
            {
              resHead="";
              resTail="";
              return;
            }
            if (!MultiDelims)
            {
              std::string::size_type pos = source.find_last_of(delim);
              if (pos==std::string::npos || pos>=source.length()) //для Last возвращаем хвостовую часть
              {
                resHead="";
                resTail=source;
                return;
              }
              //символ в середине
              Unpacker(pos, 1, source, resHead, resTail);             
            }
            else
            {
              std::string::size_type dlen=delim.length();
              //ищем первое точное вхождение подстроки delim 
              std::string::size_type spos=source.find(delim),pos=std::string::npos;
              while (spos!=std::string::npos)
              {
                //запоминаем предыдущее значение
                pos=spos;
                spos=source.find(delim,pos+dlen);
              }
              if (pos==std::string::npos || pos>=source.length()) //для Last возвращаем хвостовую часть
              {
                resHead="";
                resTail=source;
                return;
              }
              Unpacker(pos, dlen, source, resHead, resTail);             
            }
          }

          /// <summary>
          /// Проверяет, соответствует ли строка формату, и возвращает ее вариативные фрагменты
          /// </summary>
          /// <param name="fmt">Формат</param>
          /// <param name="source">Строка</param>
          /// <param name="matched">Результат: 0 - Успех, 1 - Неуспех, 2 - сам формат неверен</param>
          /// <returns></returns>
          std::list<std::string> MatchFormat(const char* & fmt, const char * & source, int & matched)
          {
            std::list<std::string> lst;
            std::string value="";
            while (*fmt !='\0')
            {
              if ((*fmt=='\\') && (*(fmt+1)=='\\'))
              {
                if (*source!='\\')
                {
                  matched=(int)Protocol::G1::Matching::Fail;
                  return lst;
                }
                ++fmt;
                ++fmt;
                ++source;
              }
              else if (*fmt!='\\') //не сопоставляемый по формату символ
                if (*source!=*fmt)
                {
                  matched=(int)Protocol::G1::Matching::Fail;
                  return lst;
                }
                else
                {
                  ++fmt;
                  ++source;
                }
              else
              {
                int result=ValidateString(source,fmt,value);
                if (result!=(int)Protocol::G1::Matching::Success)
                {
                  matched=result;
                  return lst;
                }
                lst.push_back(value);
              }
            }
            if(*source!='\0') //формат считан, а строчка не закончилась
            {
              matched=(int)Protocol::G1::Matching::Fail;
              return lst;
            }
            matched=(int)Protocol::G1::Matching::Success;
            return lst;
          }

#pragma region Internal functions для парсера


          int ValidateString (const char * & source, const char * & fmt,  std::string & value)
          {
            std::string repeats, res;
            //начинаем проверку без '\'
            ++ fmt;
            if (*fmt<='0' || *fmt>'9')
              return (int)Protocol::G1::Matching::WrongFormat;
            while (*fmt>='0' && *fmt <='9')
            {
              repeats+=*fmt;
              ++fmt;
            }
            int num=atoi(repeats.c_str());
            if (*fmt!='w' && *fmt!='d') //если формат не указывает на цифру или букву
              return (int)Protocol::G1::Matching::WrongFormat;
            if (*fmt=='w') //буквы
            {
              ++fmt;
              for (int i=0; i<num; i++)
              {
                if ((*source>='a' && *source<='z') || (*source >='A' && *source <='Z') || (*source>='а' && *source<='я') || (*source >='А' && *source <='Я'))
                {
                  res+=*source;
                  ++source;
                }
                else return (int)Protocol::G1::Matching::Fail;
              }
              value = res;
              return (int)Protocol::G1::Matching::Success;
            }
            if (*fmt=='d') //цифры
            {
              ++fmt;
              for (int i=0; i<num; i++)
              {
                if (*source>='0' && *source<='9')
                {
                  res+=*source;
                  ++source;
                }
                else return (int)Protocol::G1::Matching::Fail;
              }
              value= res;
              return (int)Protocol::G1::Matching::Success;
            }

            return (int)Protocol::G1::Matching::Success;
          }


#pragma endregion

        }
      } //пространство имен System
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller

