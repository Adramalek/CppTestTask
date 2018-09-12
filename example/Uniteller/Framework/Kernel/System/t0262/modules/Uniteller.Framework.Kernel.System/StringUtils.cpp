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
          /// ��������� ������� �� ����������� � ���������� ������ �����
          /// </summary>
          /// <param name="s">�������� ������</param>
          /// <param name="delim">�����������</param>
          /// <param name="MultiDelims">�����. False - ��������� �� ������ �� ������������, True - �� ������ ������������������</param>
          /// <param name="AllowEmpty">��������� �� ������ ������ � ����������</param>
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
            //������� �� ������������ �� ������
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
          /// ��������� �����-����������� ��� ���� Unpack
          /// </summary>
          /// <param name="pos">��������� ������� ��� ������</param>
          /// <param name="len">����� ������������������ ������� ��� ������</param>
          /// <param name="source">�������� ������</param>
          /// <param name="resHead">�������� �����</param>
          /// <param name="resTail">��������� �����</param>
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
          /// ��������� ������� ������ source �� ������� ��������� ������� delim �� ������ � �����
          /// </summary>
          /// <param name="source">�������� ������</param>
          /// <param name="delim">������-�����������</param>
          /// <param name="resHead">"������"</param>
          /// <param name="resTail">"�����"</param>
          /// <param name="MultiDelims">����� ������ �������. 0 - ����� ����������� �� ���������, 1 - ������ ������������������</param>
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
              if (pos==std::string::npos || pos>=source.length()) //��� First ���������� �������� �����
              {
                resHead=source;
                resTail="";
                return;
              }
              //������ ������ ������
              Unpacker(pos, 1, source, resHead, resTail);              
            }
            else
            {
              std::string::size_type dlen=delim.length();
              //���� ������ ������ ��������� ��������� delim 
              std::string::size_type pos=source.find(delim);
              if (pos==std::string::npos || pos>=source.length()) //��� First ���������� �������� �����
              {
                resHead=source;
                resTail="";
                return;
              }
              Unpacker(pos, dlen, source, resHead, resTail);             
            }
          }

          /// <summary>
          /// ��������� ������� ������ source �� ���������� ��������� ������� delim �� ������ � �����
          /// </summary>
          /// <param name="source">�������� ������</param>
          /// <param name="delim">������-�����������</param>
          /// <param name="resHead">"������"</param>
          /// <param name="resTail">"�����"</param>
          /// <param name="MultiDelims">����� ������ �������. 1 - ����� ����������� �� ���������, 0 - ������ ������������������</param>
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
              if (pos==std::string::npos || pos>=source.length()) //��� Last ���������� ��������� �����
              {
                resHead="";
                resTail=source;
                return;
              }
              //������ � ��������
              Unpacker(pos, 1, source, resHead, resTail);             
            }
            else
            {
              std::string::size_type dlen=delim.length();
              //���� ������ ������ ��������� ��������� delim 
              std::string::size_type spos=source.find(delim),pos=std::string::npos;
              while (spos!=std::string::npos)
              {
                //���������� ���������� ��������
                pos=spos;
                spos=source.find(delim,pos+dlen);
              }
              if (pos==std::string::npos || pos>=source.length()) //��� Last ���������� ��������� �����
              {
                resHead="";
                resTail=source;
                return;
              }
              Unpacker(pos, dlen, source, resHead, resTail);             
            }
          }

          /// <summary>
          /// ���������, ������������� �� ������ �������, � ���������� �� ����������� ���������
          /// </summary>
          /// <param name="fmt">������</param>
          /// <param name="source">������</param>
          /// <param name="matched">���������: 0 - �����, 1 - �������, 2 - ��� ������ �������</param>
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
              else if (*fmt!='\\') //�� �������������� �� ������� ������
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
            if(*source!='\0') //������ ������, � ������� �� �����������
            {
              matched=(int)Protocol::G1::Matching::Fail;
              return lst;
            }
            matched=(int)Protocol::G1::Matching::Success;
            return lst;
          }

#pragma region Internal functions ��� �������


          int ValidateString (const char * & source, const char * & fmt,  std::string & value)
          {
            std::string repeats, res;
            //�������� �������� ��� '\'
            ++ fmt;
            if (*fmt<='0' || *fmt>'9')
              return (int)Protocol::G1::Matching::WrongFormat;
            while (*fmt>='0' && *fmt <='9')
            {
              repeats+=*fmt;
              ++fmt;
            }
            int num=atoi(repeats.c_str());
            if (*fmt!='w' && *fmt!='d') //���� ������ �� ��������� �� ����� ��� �����
              return (int)Protocol::G1::Matching::WrongFormat;
            if (*fmt=='w') //�����
            {
              ++fmt;
              for (int i=0; i<num; i++)
              {
                if ((*source>='a' && *source<='z') || (*source >='A' && *source <='Z') || (*source>='�' && *source<='�') || (*source >='�' && *source <='�'))
                {
                  res+=*source;
                  ++source;
                }
                else return (int)Protocol::G1::Matching::Fail;
              }
              value = res;
              return (int)Protocol::G1::Matching::Success;
            }
            if (*fmt=='d') //�����
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
      } //������������ ���� System
    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller

