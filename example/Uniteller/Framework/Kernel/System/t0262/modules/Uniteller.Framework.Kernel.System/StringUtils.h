// Файл содержит утилитарные методы работы со строками

#pragma once

#include <string>
#include <list>
#include <algorithm> 
#include <cctype>
#include <regex>
#include "Uniteller.Framework.Kernel.System.h"

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

          void UnpackFirst(const std::string & source, const std::string & delim, std::string& resHead, std::string& resTail, bool MultiDelims);

          void UnpackLast(const std::string & source, const std::string & delim, std::string& resHead, std::string& resTail, bool MultiDelims);

          std::list<std::string> Split(const std::string &s, const std::string & delim, bool MultiDelims, bool AllowEmpty);

          std::list<std::string> MatchFormat(const char* & fmt, const char * & source, int & matched);

          int ValidateString (const char * & source, const char * & fmt, std::string & value);
        }
      } //namespace System
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller


