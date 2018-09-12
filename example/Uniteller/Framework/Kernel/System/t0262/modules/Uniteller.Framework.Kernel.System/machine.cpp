#include "machine.h"
#include "kernel/utils.h"
#include "kernel/xregistrykey.h"
#include "StringUtils.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      namespace System
      {

        bool Machine::ReplaceAllHandler(const Protocol::G1::ReplaceAll & message, Protocol::G1::ReplaceAllAnswer & answer)
        {
          answer.SetResult(Utils::ReplaceAll(message.GetSource(), message.GetPattern(), message.GetValue()));
          return true;
        }

        bool Machine::SplitHandler(const Protocol::G1::Split & message, Protocol::G1::SplitAnswer & answer)
        {
          bool mode = !!(int)message.GetMode();
          answer.SetResult(StringUtils::Split(message.GetSource(), message.GetDelim(), mode, message.GetAllowEmpty()));
          return true;
        }
        
        bool Machine::TrimLeftHandler(const Protocol::G1::TrimLeft & message, Protocol::G1::TrimLeftAnswer & answer)
        {
          std::string source = message.GetSource();
          answer.SetResult(Utils::TrimLeft(source));
          return true;
        }

        bool Machine::TrimRightHandler(const Protocol::G1::TrimRight & message, Protocol::G1::TrimRightAnswer & answer)
        {
          string source = message.GetSource();
          answer.SetResult(Utils::TrimRight(source));
          return true;
        }

        bool Machine::TrimHandler(const Protocol::G1::Trim & message, Protocol::G1::TrimAnswer & answer)
        {
          answer.SetResult(Utils::Trim(message.GetSource()));
          return true;
        }

        bool Machine::UnpackFirstHandler(const Protocol::G1::UnpackFirst & message, Protocol::G1::UnpackFirstAnswer & answer)
        {
          string source = message.GetSource();
          string delim = message.GetDelim();
          if (source.empty() || delim.empty())
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::Error);
            answer.SetHead("");
            answer.SetTail("");
            return true;
          }
          std::string resHead, resTail;
          //строка совпала с разделителем, отправляем сообщение о неудаче
          if (strcmp(source.c_str(), delim.c_str()) == 0)
            {
              answer.SetStatus(Protocol::G1::UnpackAnswerStatus::IsDivider);
              answer.SetHead("");
              answer.SetTail("");
              return true;
            }
          bool mode = !!(int)message.GetMode();
          StringUtils::UnpackFirst(source, delim, resHead, resTail, mode);
          if (resHead=="")
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::NoHead);
            answer.SetHead("");
            answer.SetTail(resTail);
            return true;
          }
          else if (resTail=="")
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::NoTail);
            answer.SetTail("");
            answer.SetHead(resHead);
            return true;
          }
          else
          {
            // обычное успешное завершение
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::Success);
            answer.SetTail(resTail);
            answer.SetHead(resHead);
            return true;
          }
        }

        bool Machine::UnpackLastHandler(const Protocol::G1::UnpackLast & message, Protocol::G1::UnpackLastAnswer & answer)
        {
          string delim = message.GetDelim();
          string source = message.GetSource();
          if (source.empty() || delim.empty())
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::Error);
            answer.SetHead("");
            answer.SetTail("");
            return true;
          }
          std::string resHead, resTail;
          //строка совпала с разделителем, отправляем сообщение о неудаче
          if (strcmp(source.c_str(), delim.c_str()) == 0)
            {
              answer.SetStatus(Protocol::G1::UnpackAnswerStatus::IsDivider);
              answer.SetHead("");
              answer.SetTail("");
              return true;
            }
          bool mode = !!(int)message.GetMode();
          StringUtils::UnpackLast(source, delim, resHead, resTail, mode);
          if (resHead=="")
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::NoHead);
            answer.SetHead("");
            answer.SetTail(resTail);
            return true;
          }
          else if (resTail=="")
          {
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::NoTail);
            answer.SetTail("");
            answer.SetHead(resHead);
            return true;
          }
          else
          {
            // обычное успешное завершение
            answer.SetStatus(Protocol::G1::UnpackAnswerStatus::Success);
            answer.SetTail(resTail);
            answer.SetHead(resHead);
            return true;
          }
        }

         bool Machine::MatchFormatHandler(const Protocol::G1::MatchFormat & message, Protocol::G1::MatchFormatAnswer & answer)
         {
           int m;
           std::list<std::string> result;
           std::string fm=message.GetFormat();
           std::string sr=message.GetSource();
           const char *fmt= fm.c_str();
           const char *src=sr.c_str();
           result=StringUtils::MatchFormat(fmt, src , m);
           answer.SetResult(result);
           answer.SetMatchResult((Protocol::G1::Matching)m);
           return true;
         }

         bool Machine::GetLengthHandler(const Protocol::G1::GetLength & message, Protocol::G1::GetLengthAnswer & answer)
         {
           answer.SetResult(message.GetSource().length());
           return true;
         }
      }
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller