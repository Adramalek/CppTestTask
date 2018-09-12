// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию типа Variant

#pragma once

#include "ivariant.h"
#include "autorelease.h"
//#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
//#include "indestructible.h"
//#endif
#include "exportableenumeration.h"
#include <string>
#include <set>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include "linq"

typedef unsigned int uint;

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      extern char g_converter[260];

      typedef ExportableEnumeration<IVariant> VariantVector;
      typedef IEnumeration<IVariant*> * VariantEnumerationPtr;
      typedef IExportable * ExportablePtr;

#ifndef small // так мы проверяем, что был включен RPCNDR.H
      typedef unsigned char byte;
#endif
      typedef std::vector<unsigned char> ByteVector;

//#pragma region Конверсия простых типов
      template <class X, class Y>
      inline X CastTo(const Y & value)
      {
        return (X)value;
      }

      template <class T>
      inline T CastTo(const T & value)
      {
        return value;
      }

      template <>
      inline int CastTo(const ByteVector & value);
      template <>
      inline std::vector<unsigned char> CastTo(const VariantEnumerationPtr & value);
      template <>
      inline std::string CastTo(const std::chrono::system_clock::time_point & value);
      template <>
      inline std::chrono::system_clock::time_point CastTo(const ByteVector & value);
      template <>
      inline std::vector<unsigned char> CastTo(const long long & value);
      template <>
      inline VariantVector CastTo(const std::string & value);
      template <>
      inline VariantVector CastTo(const std::chrono::system_clock::time_point & value);
      template <>
      inline long long CastTo(const std::chrono::system_clock::time_point & value);
      template <>
      inline bool CastTo(const ByteVector & value);

			template <>
			inline VariantEnumerationPtr CastTo<VariantEnumerationPtr, VariantEnumerationPtr>(const VariantEnumerationPtr & value)
			{
				if (value)
					value->AddRef();
				return value;
			}

			template <>
			inline ExportablePtr CastTo<ExportablePtr, ExportablePtr>(const ExportablePtr & value)
			{
				if (value)
					value->AddRef();
				return value;
			}

      template <>
      inline std::string CastTo(const uint & value)
      {
        return std::to_string(value);
      }

      template <>
      inline byte CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0: return 0;
        case 1: return value[0];
        default:
          throw BadCastException("Конверсия не определена");
        }                
      }

      template <>
      inline byte CastTo(const std::chrono::system_clock::time_point & value)
      {
        return CastTo<byte>(CastTo<long long>(value));
      }

      template <>
      inline bool CastTo(const std::chrono::system_clock::time_point & value)
      {
        return value.time_since_epoch().count() != 0;
      }

      template <>
      inline unsigned int CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch());
        long long res = ms.count();        
        if ((res >= 0) && (res <= 4294967295LL)) // (long long)
          return static_cast<uint>(res);
        throw BadCastException("Конверсия не определена: value out of unsigned int range");
      }

      template <>
      inline int CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch());
        long long res = ms.count();
        if ((res >= 0) && (res <= 4294967295LL)) // (long long)
          return static_cast<int>(res);
        throw BadCastException("Конверсия не определена: value out of int range");
      }

      template <>
      inline long unsigned int CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch());
        long long res = ms.count();
        if ((res >= 0) && (res <= 4294967295LL)) // (long long)
          return static_cast<long unsigned int>(res);
        throw BadCastException("Конверсия не определена: value out of long unsigned int range");
      }

      template <>
      inline unsigned int CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0:
          return 0;
        case 1:
          return value[0];
        case 2:
          return (value[0] << 8) | value[1];
        case 3:
          return (value[0] << 16) | (value[1] << 8) | value[2];
        case 4:
          return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | value[3];
        default:
          throw BadCastException("Конверсия не определена: более 4х байт в массиве");
        }
      }

      template <>
      inline unsigned int CastTo(const VariantEnumerationPtr & value)
      {
        return CastTo<unsigned int>(CastTo<std::vector<unsigned char>>(value));
      }

      template <>
      inline byte CastTo(const VariantEnumerationPtr & value)
      {
        return CastTo<byte>(CastTo<std::vector<unsigned char>>(value));
      }

      template <>
      inline bool CastTo(const VariantEnumerationPtr & value)
      {
        if (value == NULL)
          return false;
        return CastTo<bool>(CastTo<std::vector<unsigned char>>(value));
      }


      template <>
      inline bool CastTo(const ExportablePtr & value)
      {
        return value != NULL;
      }

      template <>
      inline byte CastTo(const ExportablePtr & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline int CastTo(const VariantEnumerationPtr & value)
      {
        return CastTo<int>(CastTo<std::vector<unsigned char>>(value));
      }

      template <>
      inline unsigned int CastTo(const ExportablePtr & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline VariantEnumerationPtr CastTo(const ByteVector & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }
      
      template <>
      inline bool CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0: return false;
        case 1: return value[0] != 0;
        default: 
          throw BadCastException("Конверсия не определена");
        }        
      }

      template <>
      inline VariantEnumerationPtr CastTo(const std::string & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline VariantEnumerationPtr CastTo(const std::chrono::system_clock::time_point & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline long long CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::milliseconds result = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch());
        return result.count();
      }

      template <>
      inline long long CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0:
          return 0;
        case 1:
          return value[0];
        case 2:
          return (value[0] << 8) | value[1];
        case 3:
          return (value[0] << 16) | (value[1] << 8) | value[2];
        case 4:
          return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | value[3];
        case 5:
          return (static_cast<long long>(value[0]) << 32) | (value[1] << 24) | (value[2] << 16) | (value[3] << 8) | value[4];
        case 6:
          return (static_cast<long long>(value[0]) << 40) | (static_cast<long long>(value[1]) << 32) | (value[2] << 24) | (value[3] << 16) | (value[4] << 8) | value[5];
        case 7:
          return (static_cast<long long>(value[0]) << 48) | (static_cast<long long>(value[1]) << 40) | (static_cast<long long>(value[2]) << 32) | (value[3] << 24) | (value[4] << 16) | (value[5] << 8) | value[6];
        case 8:
          return (static_cast<long long>(value[0]) << 56) | (static_cast<long long>(value[1]) << 48) | (static_cast<long long>(value[2]) << 40) | (static_cast<long long>(value[3]) << 32) | (value[4] << 24) | (value[5] << 16) | (value[6] << 8) | value[7];
        default:
          throw BadCastException("Конверсия не определена: более 8 байт на число");
        }
      }

      template <>
      inline int CastTo(const ExportablePtr & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }


      template <>
      inline long unsigned int CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0:
          return 0;
        case 1:
          return value[0];
        case 2:
          return (value[0] << 8) | value[1];
        case 3:
          return (value[0] << 16) | (value[1] << 8) | value[2];
        case 4:
          return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | value[3];
/*        case 5:
          return (static_cast<long unsigned int>(value[0]) << 32) | (value[1] << 24) | (value[2] << 16) | (value[3] << 8) | value[4];
        case 6:
          return (static_cast<long unsigned int>(value[0]) << 40) | (static_cast<long unsigned int>(value[1]) << 32) | (value[2] << 24) | (value[3] << 16) | (value[4] << 8) | value[5];
        case 7:
          return (static_cast<long unsigned int>(value[0]) << 48) | (static_cast<long unsigned int>(value[1]) << 40) | (static_cast<long unsigned int>(value[2]) << 32) | (value[3] << 24) | (value[4] << 16) | (value[5] << 8) | value[6];
        case 8:
          return (static_cast<long unsigned int>(value[0]) << 56) | (static_cast<long unsigned int>(value[1]) << 48) | (static_cast<long unsigned int>(value[2]) << 40) | (static_cast<long unsigned int>(value[3]) << 32) | (value[4] << 24) | (value[5] << 16) | (value[6] << 8) | value[7];*/
        default:
          throw BadCastException("Конверсия не определена: более 4х байт на число");
        }
      }

      template <>
      inline long unsigned int CastTo(const ExportablePtr & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const std::string & value)
      {
        // YYYY,
        // YYYYMM,
        // YYYYMMDD,
        // YYYYMMDDhhmmss
        // YYYYMMDDhhmmssfff
        switch (value.size())
        {
        case 4: // YYYY                    
          break;
        case 6: // YYYYMM
          break;
        case 8: // YYYYMMDD
          break;
        case 14: // YYYYMMDDhhmmss
          break;
        case 17: // YYYYMMDDhhmmssfff
          break; 
        }
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const bool & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const int & value)
      {
        return std::chrono::system_clock::time_point(std::chrono::milliseconds(value));
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const uint & value)
      {
        return std::chrono::system_clock::time_point(std::chrono::milliseconds(value));
      }


      template <>
      inline std::chrono::system_clock::time_point CastTo(const long long & value)
      {
        return std::chrono::system_clock::time_point(std::chrono::milliseconds(value));
      }


      template <>
      inline std::chrono::system_clock::time_point CastTo(const ExportablePtr & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const VariantEnumerationPtr & value)
      {
        return CastTo<std::chrono::system_clock::time_point>(CastTo<ByteVector>(value));
      }

      template <>
      inline std::chrono::system_clock::time_point CastTo(const ByteVector & value)
      {
        return std::chrono::system_clock::time_point(std::chrono::milliseconds(CastTo<long long>(value)));
      }

      template <>
      inline int CastTo(const ByteVector & value)
      {
        switch (value.size())
        {
        case 0:
          return 0;
        case 1:
          return value[0];
        case 2:
          return (value[0] << 8) | value[1];
        case 3:
          return (value[0] << 16) | (value[1] << 8) | value[2];
        case 4:
          return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | value[3];
        default:
          throw BadCastException("Конверсия не определена");
        }
      }

      template <>
      inline ExportablePtr CastTo(const std::chrono::system_clock::time_point & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::set<int> CastTo(const ByteVector & value)
      {
				return std::set<int>(value.begin(), value.end());
      }

      template <>
      inline std::set<int> CastTo(const std::chrono::system_clock::time_point & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::set<std::string> CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::set<std::string> result;
        result.insert(CastTo<std::string>(value));
        return result;
      }

      template <>
      inline std::set<std::string> CastTo(const ByteVector & value)
      {
        std::set<std::string> result;
        size_t max = value.size();
        for (size_t i = 0; i<max; ++i)
        {
          result.insert(std::to_string(static_cast<int>(value[i])));
        }
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::system_clock::duration tp = value.time_since_epoch();
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
        std::chrono::system_clock::time_point fraction = value - seconds;
        std::chrono::system_clock::time_point j = value - fraction.time_since_epoch();

        time_t time = std::chrono::system_clock::to_time_t(j);
        tm t;
        localtime_s(&t, &time);

        std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

        std::list<std::string> result;
        result.push_back(std::to_string(t.tm_year + 1900)); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx

        std::stringstream x;
        x << std::setfill('0') << std::setw(2) << (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        result.push_back(x.str());
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_mday;
        result.push_back(x.str());
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_hour;
        result.push_back(x.str());
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_min;
        result.push_back(x.str());
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_sec;
        result.push_back(x.str());
        x.clear();
        x << std::setfill('0') << std::setw(3) << millis.count();
        result.push_back(x.str());
        x.clear();
        return result;
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::system_clock::duration tp = value.time_since_epoch();
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
        std::chrono::system_clock::time_point fraction = value - seconds;
        std::chrono::system_clock::time_point j = value - fraction.time_since_epoch();

        time_t time = std::chrono::system_clock::to_time_t(j);
        tm t;
        localtime_s(&t, &time);

        std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

        std::map<std::string, std::string> result;
        result.insert(std::make_pair("Year", std::to_string(t.tm_year + 1900))); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx

        std::stringstream x;
        x << std::setfill('0') << std::setw(2) << (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        result.insert(std::make_pair("Month", x.str()));
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_mday;
        result.insert(std::make_pair("Day", x.str()));
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_hour;
        result.insert(std::make_pair("Hour", x.str()));
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_min;
        result.insert(std::make_pair("Min", x.str()));
        x.clear();
        x << std::setfill('0') << std::setw(2) << t.tm_sec;
        result.insert(std::make_pair("Sec", x.str()));
        x.clear();
        x << std::setfill('0') << std::setw(3) << millis.count();
        result.insert(std::make_pair("Milis", x.str()));
        x.clear();
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const std::chrono::system_clock::time_point & value)
      {
        return CastTo<std::vector<unsigned char>>(CastTo<long long>(value));
      }

      template <>
      inline std::string CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::system_clock::duration tp = value.time_since_epoch();
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
        std::chrono::system_clock::time_point fraction = value - seconds;
        std::chrono::system_clock::time_point j = value - fraction.time_since_epoch();

        time_t time = std::chrono::system_clock::to_time_t(j);
        tm t;
        localtime_s(&t, &time);

        std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

        std::stringstream x;
        x << '[';
        x << (t.tm_year + 1900); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        x << '.';
        x << std::setfill('0') << std::setw(2) << (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        x << '.';
        x << std::setfill('0') << std::setw(2) << t.tm_mday;
        x << ' ';
        x << std::setfill('0') << std::setw(2) << t.tm_hour;
        x << ':';
        x << std::setfill('0') << std::setw(2) << t.tm_min;
        x << ':';
        x << std::setfill('0') << std::setw(2) << t.tm_sec;
        x << '.';
        x << std::setfill('0') << std::setw(3) << millis.count();
        x << ']';
        return x.str();
      }

      template <>
      inline const char * CastTo(const std::string & value)
      {
        return value.c_str();
      }


      template <>
      inline const char * CastTo(const std::chrono::system_clock::time_point & value)
      {
        std::chrono::system_clock::duration tp = value.time_since_epoch();
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
        std::chrono::system_clock::time_point fraction = value - seconds;
        std::chrono::system_clock::time_point j = value - fraction.time_since_epoch();

        time_t time = std::chrono::system_clock::to_time_t(j);
        tm t;
        localtime_s(&t, &time);

        std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

        std::stringstream x;
        x << '[';
        x << (t.tm_year + 1900); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        x << '.';
        x << std::setfill('0') << std::setw(2) << (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
        x << '.';
        x << std::setfill('0') << std::setw(2) << t.tm_mday;
        x << ' ';
        x << std::setfill('0') << std::setw(2) << t.tm_hour;
        x << ':';
        x << std::setfill('0') << std::setw(2) << t.tm_min;
        x << ':';
        x << std::setfill('0') << std::setw(2) << t.tm_sec;
        x << '.';
        x << std::setfill('0') << std::setw(3) << millis.count();
        x << ']';
        return export_local(x.str());
      }


      template <>
      inline long long CastTo(const std::string & value)
      {
        return atoi(value.c_str());
      }

      template <>
      inline long unsigned int CastTo(const std::string & value)
      {
        return atoi(value.c_str());
      }


      template <>
      inline int CastTo(const std::string & value)
      {
        return atoi(value.c_str());
      }

      template <>
      inline uint CastTo(const std::string & value)
      {
        return (uint)atoi(value.c_str());
      }

      template <>
      inline byte CastTo(const std::string & value)
      {
        return (byte)atoi(value.c_str());
      }

      template <>
      inline int CastTo(const bool & value)
      {
        return value ? 1 : 0;
      }

      template <>
      inline long long CastTo(const bool & value)
      {
        return value ? 1 : 0;
      }

      template <>
      inline long unsigned int CastTo(const bool & value)
      {
        return value ? 1 : 0;
      }

      template <>
      inline std::string CastTo(const int & value)
      {
        return std::to_string(value);
      }


      template <>
      inline std::string CastTo(const long long & value)
      {
        return std::to_string(value);
      }

      template <>
      inline std::string CastTo(const bool & value)
      {
        return value ? "True" : "False";
      }

      template <>
      inline bool CastTo(const uint & value)
      {
        return value > 0;
      }

      template <>
      inline bool CastTo(const int & value)
      {
        return value > 0;
      }

      template <>
      inline bool CastTo(const long long & value)
      {
        return value > 0;
      }

      template <>
      inline uint CastTo(const long long & value)
      {
        if ((value >=0) && (value <= 4294967295LL)) // (long long)
          return (uint)value;
        throw BadCastException("value out of unsigned int range");
      }


      template <>
      inline bool CastTo(const std::string & value)
      {
        return strcmp(value.c_str(), "True")==0;
      }

      template <>
      inline std::string CastTo(const ByteVector & value)
      {
        std::string result = "{";

        size_t max = value.size();
        for (size_t i=0;i<max;++i)
        {
          if (i>0)
            result += ", ";
          result += std::to_string((int)value[i]);
        }
        result += "}";
        return result;
      }

      template <>
      inline const char* CastTo(const ByteVector & value)
      {
        std::string result = "{";

        size_t max = value.size();
        for (size_t i=0;i<max;++i)
        {
          if (i>0)
            result += ", ";
          result += std::to_string((int)value[i]);
        }
        result += "}";
        return export_local(result);
      }


			template <>
			inline std::string CastTo(const VariantEnumerationPtr & value);

//#pragma endregion 

      /// <summary>
      /// Контейнер позволяющий хранить строки, числа или логические значения
      /// <summary>
      class Variant : public Exportable<IVariant>
      {
      private:

//#pragma region Holders

        class IValueHolder : public IExportable
        {
        public:
          virtual VariantType GetType() const = 0;
          virtual IValueHolder * Clone() = 0;
        };


//#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
//				class EmptyHolder : public Indestructible<IValueHolder>
//#else
				class EmptyHolder : public Exportable<IValueHolder>
//#endif
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          EmptyHolder()
          {
          }
          VariantType GetType() const override
          {
            return VariantType::EmptyValue;
          }
          IValueHolder * Clone() override
          {
            AddRef();
            return this;
          }
        };

        class StringHolder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          StringHolder()
          {
          }
					explicit StringHolder(const char * value) : m_Value(value)
          {
          }
					explicit StringHolder(const std::string & value) : m_Value(value)
          {
          }
		  VariantType GetType() const override
          {
            return VariantType::StringValue;
          }
          IValueHolder * Clone() override
          {
            			AddRef();
						return this;
          }
          //AUTO_PROPERTY(std::string, Value);
					std::string m_Value;
        };

        class TimePointHolder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
					TimePointHolder() : m_Value(std::chrono::system_clock::now())
          {
          }
					explicit TimePointHolder(const std::chrono::system_clock::time_point & value) : m_Value(value)
          {
          }
		      VariantType GetType() const override
          {
            return VariantType::TimePoint;
          }
          IValueHolder * Clone() override
          {
            return new TimePointHolder(m_Value);
          }
          AUTO_PROPERTY(std::chrono::system_clock::time_point, Value);
        };

        class IntegerHolder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          IntegerHolder() : m_Value(0)
          {
          }
					explicit IntegerHolder(const int & value) : m_Value(value)
          {
          }
					VariantType GetType() const override
          {
            return VariantType::IntegerValue;
          }
          IValueHolder * Clone() override
          {
						AddRef();
						return this;
          }
          AUTO_PROPERTY(int, Value);
        };

        class UintHolder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          UintHolder() : m_Value(0)
          {
          }
					explicit UintHolder(const uint & value) : m_Value(value)
          {
          }
					VariantType GetType() const override
          {
            return VariantType::UnsignedIntegerValue;
          }
          IValueHolder * Clone() override
          {
						AddRef();
						return this;
          }
          AUTO_PROPERTY(uint, Value);
        };

        class Int64Holder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          Int64Holder() : m_Value(0)
          {
          }
				  explicit Int64Holder(const long long & value) : m_Value(value)
          {
          }
					VariantType GetType() const override
          {
            return VariantType::Int64Value;
          }
          IValueHolder * Clone() override
          {
						AddRef();
						return this;
          }
          AUTO_PROPERTY(long long, Value);
        };

        class BooleanHolder : public Exportable<IValueHolder>
        {
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          BooleanHolder() : m_Value(false)
          {
          }
					explicit BooleanHolder(const bool value) : m_Value(value)
          {
          }
					VariantType GetType() const override
          {
            return VariantType::BooleanValue;
          } 
          IValueHolder * Clone() override
          {
            AddRef();
            return this;
          }
					bool m_Value;
        };

        class ArrayHolder : public Exportable<IValueHolder>
        {
        private:
          SmartPointer<IEnumeration<IVariant *> > m_Value;
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          ArrayHolder()
          {
          }

          explicit ArrayHolder(const std::string & value)
          {
            m_Value <<= ParseArray(value);
          }
          explicit ArrayHolder(IEnumeration<IVariant *> * value)
          {
            m_Value <<= CopyVariantEnumeration(value);
          }
          VariantType GetType() const override
          {
            return VariantType::ArrayValue;
          }
          IValueHolder * Clone() override
          {
            AddRef();
            return this;
          }
          IEnumeration<IVariant *> * GetValue() const
          {
            return m_Value.Copy();
          }
          void SetValue(IEnumeration<IVariant *> * value)
          {
            m_Value <<= CopyVariantEnumeration(value);
          }
          void Attach(IEnumeration<IVariant *> * value)
          {
            m_Value <<= value;
          }
        private:
          static IEnumeration<IVariant *> * CopyVariantEnumeration(IEnumeration<IVariant *> * p)
          {
            SmartPointer<ExportableEnumeration<IVariant>> result;
            result.Create();

            size_t max = p->GetCount();
            size_t i;
            for (i = 0; i<max; ++i)
            {
              SmartPointer<IVariant> value;
              value <<= p->GetItem(i);
              SmartPointer<IVariant> tmp;
							tmp <<= new Variant(value.p);
              result->Add(tmp.p);
            }
            return result.Detach();
          }
        };

        class ByteArrayHolder : public Exportable<IValueHolder>
        {
				public:
          ByteVector m_Value;
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          ByteArrayHolder()
          {
          }
          ByteArrayHolder(const unsigned char * data, const size_t len)
          {
            m_Value.insert(m_Value.end(), data, data+len);
          }
					explicit ByteArrayHolder(const ByteVector & value) : m_Value(value)
          {
          }
					VariantType GetType() const override
          {
            return VariantType::ByteArrayValue;
          }
          IValueHolder * Clone() override
          {
						AddRef();
						return this;
          }
        };

        class ExportableHolder : public Exportable<IValueHolder>
        {
        private:
          SmartPointer<IExportable> m_Value;
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
          ExportableHolder()
          {
          }
          explicit ExportableHolder(IExportable * value) : m_Value(value)
          {
          }
  	  VariantType GetType() const override
          {
            return VariantType::ExportableValue;
          }
          IValueHolder * Clone() override
          {
						AddRef();
						return this;
          }
          IExportable * GetValue() const
          {
            return m_Value.Copy();
          }
          void SetValue(IExportable * value)
          {
            m_Value = value;
          }
        };

				class LambdaExpression : public Exportable < IValueHolder >
				{
				private:
					// Аргументы выражения
					std::vector<IVariant *> m_Arguments;
				public:
					/// <summary>
					/// Конструктор
					/// </summary>
					LambdaExpression()
					{
					}
					~LambdaExpression()
					{
						Clear();
					}
					VariantType GetType() const override
					{
						return VariantType::LambdaExpression;
					}
					IValueHolder * Clone() override
					{
						AddRef();
						return this;
					}
					AUTO_PROPERTY(ExpressionType, Kind);
					size_t GetArguemtsCount() const
					{
						return m_Arguments.size();
					}
					READONLY_PROPERTY(size_t, ArgumentsCount);
					IVariant * PeekArgument(size_t index)
					{
						return m_Arguments[index];
					}
					void AddArgument(IVariant * val)
					{
						val->AddRef();
						m_Arguments.push_back(val);
					}
					void Clear()
					{
						/*for (IVariant * arg : m_Arguments)
							arg->Release();
						m_Arguments.clear();*/
                      Linq::CleanExportableCollection(m_Arguments);
					}
				};

        class HolderFactory
        {
        private:
          Variant::EmptyHolder * m_Empty;
          Variant::BooleanHolder * m_True;
          Variant::BooleanHolder * m_False;
          Variant::StringHolder * m_EmptyString;
        public:
          HolderFactory() : 
            m_Empty(new EmptyHolder()),
            m_True(new BooleanHolder(true)),
            m_False(new BooleanHolder(false)),
            m_EmptyString(new StringHolder(""))
          {
          }
          IValueHolder * Empty()
          {
            if (!m_Empty)
            {
              m_Empty = new EmptyHolder();
            }
            m_Empty->AddRef();
            return m_Empty;
          }
          IValueHolder * True()
          {
            if (!m_True)
            {
              m_True = new BooleanHolder(true);
            }
            m_True->AddRef();
            return m_True;
          }
          IValueHolder * False()
          {
            if (!m_False)
            {
              m_False = new BooleanHolder(false);
            }
            m_False->AddRef();
            return m_False;
          }
          IValueHolder * Create(bool v)
          {
            return v ? True() : False();
          }
          IValueHolder * Create(const std::string & s)
          {
            if (s.size() == 0)
            {
              if (!m_EmptyString)
                m_EmptyString = new StringHolder("");
              m_EmptyString->AddRef();
              return m_EmptyString;
            }
            return new StringHolder(s);
          }
        private:
#if __GNUC__ < 5 
          HolderFactory(const HolderFactory & ) {}
#else
          HolderFactory(const HolderFactory & ) = delete;
#endif
        };



#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS 				
        static Variant::HolderFactory g_Factory;
        //static IValueHolder * QueryEmptyHolder();
#define QueryEmptyHolder g_Factory.Empty()
#define QueryFalseHolder g_Factory.False()
#define QueryTrueHolder g_Factory.True()
#define QueryBooleanHolder g_Factory.Create
#define QueryStringHolder g_Factory.Create

//#define QueryEmptyHolder new EmptyHolder()
//#define QueryFalseHolder new BooleanHolder(false)
//#define QueryTrueHolder new BooleanHolder(true)
//#define QueryBooleanHolder new BooleanHolder 
//#define QueryStringHolder new StringHolder 

#else

#define QueryEmptyHolder new EmptyHolder()
#define QueryFalseHolder new BooleanHolder(false)
#define QueryTrueHolder new BooleanHolder(true)
#define QueryBooleanHolder new BooleanHolder 
#define QueryStringHolder new StringHolder 

#endif

      private:
        IValueHolder * m_Holder;
      public:
        /// <summary>
        /// Конструирует пустой Variant
        /// </summary>
				Variant() : m_Holder(QueryEmptyHolder)
        {
        }
        /// <summary>
        /// Конструирует Variant и помещает в него строковое значение value
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="const char*"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const char * value) : m_Holder(new StringHolder(value))
        {
        }
        /// <summary>
        /// Конструирует Variant и помещает в него строковое значение value
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="std::string"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const std::string & value) : m_Holder(new StringHolder(value))
        {
        }
        /// <summary>
        /// Конструирует Variant и помещает в него числовое значение value
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="int"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const int value) : m_Holder(new IntegerHolder(value))
        {
        }
        Variant(const long value) : m_Holder(new IntegerHolder(value))
        {
        }
        /// <summary>
        /// Конструирует Variant и помещает в него числовое значение value (__int64)
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="__int64"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const long long value) : m_Holder(new Int64Holder(value))
        {
        }

        /// <summary>
        /// Конструирует Variant и помещает в него числовое значение value (__int64)
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="__int64"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const long unsigned int value) : m_Holder(new Int64Holder(value))
        {
        }

        /// <summary>
        /// Конструирует Variant и помещает в него числовое значение value
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="int"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const uint value) : m_Holder(new UintHolder(value))
        {
        }
        /// <summary>
        /// Конструирует Variant и помещает в него логическое значение value
        /// </summary>
        /// <param name = "value">
        ///  Значение типа <see cref="bool"/>, устанавливаемое в конструируемый Variant
        /// </param>
        Variant(const bool value) : m_Holder(QueryBooleanHolder(value))
        {
        }
        Variant(IEnumeration<IVariant *> * value) : m_Holder(new ArrayHolder(value))
        {
        }
        Variant(const std::chrono::system_clock::time_point & value) :
					m_Holder(new TimePointHolder(value))
        {
        }
        template <class Q>
				Variant(const std::list<Q> & value)
        {
          SmartPointer<ExportableEnumeration<IVariant>> result;
          result.Create();

          typename std::list<Q>::const_iterator i = value.begin();
          typename std::list<Q>::const_iterator e = value.end();
          for (; i!=e; ++i)
          {
            SmartPointer<Variant> v;
            v <<= new Variant(*i);
            result->Add(v.p);
          }
          ArrayHolder * h = new ArrayHolder();
          h->Attach(result.Detach());
          m_Holder = h;
        }

        template <class Q>
        Variant(const std::vector<Q> & value)
        {
          SmartPointer<ExportableEnumeration<IVariant>> result;
          result.Create();

          typename std::vector<Q>::const_iterator i = value.begin();
          typename std::vector<Q>::const_iterator e = value.end();
          for (; i!=e; ++i)
          {
            SmartPointer<Variant> v;
						v <<= new Variant(*i);
            result->Add(v.p);
          }
          ArrayHolder * h = new ArrayHolder();
          h->Attach(result.Detach());
          m_Holder = h;
        }
        
        // Байт-вектор
        Variant(const ByteVector & value) : m_Holder(new ByteArrayHolder(value))
        {
        }

        // Контейнер свойств
      	/*Variant(const std::map<std::string, IVariant *> & value) : m_Holder(new PropertyMapHolder(value))
        {
        }*/

				Variant(const unsigned char * data, const size_t len) : m_Holder(new ByteArrayHolder(data, len))
        {
        }

        template <class Q>
        Variant(const std::set<Q> & value)
        {
          SmartPointer<ExportableEnumeration<IVariant>> result;
          result.Create();

          typename std::set<Q>::const_iterator i = value.begin();
          typename std::set<Q>::const_iterator e = value.end();
          for (; i!=e; ++i)
          {
            SmartPointer<IVariant> v;
						v <<= new Variant(*i);
            result->Add(v.p);
          }
          ArrayHolder * h = new ArrayHolder();
          h->Attach(result.Detach());
          m_Holder = h;
        }

        Variant(const std::map<std::string, std::string> & value)
        {
          SmartPointer<ExportableEnumeration<IVariant>> result;
          result.Create();

          std::map<std::string, std::string>::const_iterator i = value.begin();
          std::map<std::string, std::string>::const_iterator e = value.end();
          for (; i!=e; ++i)
          {
            SmartPointer<Variant> v;
						v <<= new Variant(i->first);
            result->Add(v.p);
						v <<= new Variant(i->second);
            result->Add(v.p);
          }
          ArrayHolder * h = new ArrayHolder();
          h->Attach(result.Detach());
          m_Holder = h;
        }

				Variant(VariantVector & other) : m_Holder(new ArrayHolder(&other))
        {
        }

				Variant(IExportable * other) : m_Holder(new ExportableHolder(other))
				{
				}

        /// <summary>
        /// Конструктор копирования.
        /// </summary>
        /// <param name="other">Значение для копирования.</param>
				Variant(const Variant & other)
        {
          m_Holder = other.m_Holder->Clone();
        }

        Variant(IVariant * other)
        {
          Variant * v = dynamic_cast<Variant *>(other);
          if (v)
          {
            m_Holder = v->m_Holder->Clone();
          }
          else
            m_Holder = QueryEmptyHolder;
        }

        /// <summary>
        /// Деструктор
        /// </summary>
        ~Variant()
        {
          IValueHolder * h = m_Holder;
          m_Holder = NULL;
          h->Release();
        }

        Variant & operator=(const Variant& rhs)
        {
          IValueHolder * h = m_Holder;
          m_Holder =  rhs.m_Holder->Clone();
          h->Release();
          return *this;
        }

        Variant & operator=(const ByteVector & value)
        {
           IValueHolder * h = m_Holder;
           m_Holder =  new ByteArrayHolder(value);
           h->Release();
           return *this;
        }
        Variant & operator=(const IVariant * rhs)
        {
          IValueHolder * h = m_Holder;
          //m_Holder = NULL;
          if (rhs)
            m_Holder = ((Variant *)rhs)->m_Holder->Clone();
          else
            m_Holder = QueryEmptyHolder;
          h->Release();
          return *this;
        }

        Variant & operator=(const int rhs)
        {
          m_Holder->Release();
          m_Holder = NULL;
          m_Holder = new IntegerHolder(rhs);
          return *this;
        }

        Variant & operator=(const long rhs)
        {
          m_Holder->Release();
          m_Holder = NULL;
          m_Holder = new IntegerHolder(rhs);
          return *this;
        }
        Variant & operator=(const long long rhs)
        {
          m_Holder->Release();
          m_Holder = new Int64Holder(rhs);
          return *this;
        }
        Variant & operator=(const long unsigned int rhs)
        {
          m_Holder->Release();
          //m_Holder = NULL;
          m_Holder = new Int64Holder(rhs);
          return *this;
        }

        Variant & operator=(const uint rhs)
        {
					IValueHolder * h = m_Holder;
          m_Holder = new UintHolder(rhs);
					h->Release();
          return *this;
        }

        Variant & operator=(const std::chrono::system_clock::time_point & rhs)
				{
					IValueHolder * h = m_Holder;
					m_Holder = new TimePointHolder(rhs);
					h->Release();
          return *this;
        }

        Variant & operator=(const bool rhs)
				{
					IValueHolder * h = m_Holder;
					m_Holder = QueryBooleanHolder(rhs);
					h->Release();
          return *this;
        }

        Variant & operator=(const std::string & rhs)
				{
					IValueHolder * h = m_Holder;
          m_Holder = new StringHolder(rhs);
					h->Release();
          return *this;
        }

        Variant & operator=(const char * rhs)
				{
					IValueHolder * h = m_Holder;
					m_Holder = new StringHolder(rhs);
					h->Release();
          return *this;
        }

        Variant & operator=(IEnumeration<IVariant *> * rhs)
        {
          IValueHolder * h = m_Holder;
          m_Holder = new ArrayHolder(rhs);
          h->Release();
          return *this;
        }

        Variant & operator=(ExportableEnumeration<IVariant> & rhs)
        {
          IValueHolder * h = m_Holder;
          m_Holder = new ArrayHolder(&rhs);
          h->Release();
          return *this;
        }

        /// <summary>
        /// Возвращает тип хранимого значения
        /// </summary>
        /// <returns> Тип хранимого значения </returns>
        VariantType GetType() const override
        {
          return m_Holder->GetType();
        }

        void Clear()
        {
          if (m_Holder->GetType() != VariantType::EmptyValue)
          {
            IValueHolder * h = m_Holder;
            //m_Holder = NULL;
						m_Holder = QueryEmptyHolder;
            h->Release();
          }
        }

        void SetExportableValue(IExportable * rhs)
        {
					IValueHolder * h = m_Holder;
					m_Holder = new ExportableHolder(rhs);
					h->Release();
        }

        void SetArrayValue(IEnumeration<IVariant *> * rhs)
				{
          IValueHolder * h = m_Holder;
          ArrayHolder * r = new ArrayHolder();
          r->Attach(rhs);
          m_Holder = r;
          h->Release();
				}

				/// <summary>
				/// Разбирает Variant
				/// </summary>
				/// <returns>Признак является ли выделенное выражение константой</returns>
				bool Parse(const std::string & str)
				{
					const char * s = str.c_str();
					while (*s == ' ') // Пропускаем пробелы
						++s;
					switch (*s)
					{
						case 'T':
							++s;
							m_Holder->Release();
							if (strcmp(s, "rue") == 0)
								m_Holder = QueryTrueHolder;//new BooleanHolder(true);
							else
								m_Holder = new StringHolder(str);
							return true;
						case 'F':
							++s;
							m_Holder->Release();
							if (strcmp(s, "alse") == 0)
								m_Holder = QueryFalseHolder; //new BooleanHolder(false);
							else
								m_Holder = new StringHolder(str);
							return true;
						case '{':
						  {
							  m_Holder->Release();
							  int max = str.size();
								if ((max >= 2) && s[max - 1] == '}')
								{
									const std::string & st = str.substr(1, max - 2);
									// Режем s по символу ','
									//SmartPointer<IEnumeration<IVariant *>> result;
									//result <<= ParseArray(st);
                  m_Holder = new ArrayHolder(st);
								}
                else
                  m_Holder = new StringHolder(str);
						  }
							return true;
						case '"':
						  {
							  ++s;
								std::string value;
							  while ((*s == '"') && (*(s + 1) == '"'))
							  {
							  	value += *s;
							  	s += 2;
							  }
							  while ((*s != '"') && (*s != '\0'))
							  {
							  	if (*s == '\\')
							  	{
							  		switch (*(s + 1))
							  		{
							  		case 'x':
							  		  {
							  				s += 2;  // Пропуск слеша
							  				int lhs = g_converter[(unsigned char)*s];
												int rhs = g_converter[(unsigned char)*(s + 1)];
							  				if ((lhs >= 0) && (rhs >= 0))
							  				{
							  					value += (char)((lhs <<4) | rhs);       // (char)(lhs<<4 + rhs); //
							  					s += 2;
							  				}
							  				else
							  					value += "\\x";
							  			}
							  			break;
							  		case '\\':
							  			s += 2; // Пропуск слеша
							  			value += "\\";
							  			break;
							  		default:
							  			value += *s;
							  			++s;
							  			break;
							  		}
							  	}
							  	else
							  	{
							  		value += *s;
							  		++s;
							  	}
							  	while ((*s == '"') && (*(s + 1) == '"'))
							  	{
							  		value += *s;
							  		s += 2;
							  	}
							  }
							  /*if (*s == '"')
							  	++s;*/
                m_Holder->Release();
                m_Holder = new StringHolder(value);
						  }
							return true;
						case '0':
							if (*(s + 1) == 'x')
							{
								// HexToString
								std::stringstream ss;
								ss << std::hex << s;
								unsigned long long x = 0;
								ss >> x;
								if (x > (unsigned long long)ULONG_MAX)
								{
									operator= ((long long)x);
									return true;
								}
								operator= ((long)x);
								return true;
							}            
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
            case '-':
	  					{
								const char * n = s;
                char *p = 0;
                errno = 0;
                long val = strtol(n, &p, 10);
								if ((p == n) || (((val == LONG_MIN) || (val == LONG_MAX)) && (errno == ERANGE)) || (*p != '\0'))
								{
									//n = s;
									p = 0;
									unsigned long long y = _strtoui64(n, &p, 10);
                  if ((p == n) || ((y == _UI64_MAX) && ((errno == ERANGE) || (errno == EINVAL)))) // Out of range
									{
										operator=(s);
										return true;
									}
									if (*p <= 32)
										operator=((long long)y);
									else
										operator=(s);
									//return true;
								}
								else
									operator=(val);
								return true;
  						}
						case '\0':
							Clear();
							return true;
						case '?': // Локальная переменная?
						case '$': // Регистр?
						case '<':
              m_Holder->Release();
              m_Holder = new StringHolder(s);
							return false; // Подозрение на лямбда-выражение
						default: // Некая константа              
              m_Holder->Release();
              m_Holder = new StringHolder(s);
							return true;
					}
				}

        static IEnumeration<IVariant *> * ParseArray(const std::string & s)
        {
          // Режем s по символу ','
          std::list<ExportableEnumeration<IVariant>*> data;
          data.push_back(new ExportableEnumeration<IVariant>());

          size_t i = 0;
          size_t k = 0;
          size_t max = s.size();
          while (i<max)
          {
            switch (s[i])
            {
            case ',':
              if (i>k)
              {
                const std::string & x = Utils::Trim(s.substr(k, i - k));
                SmartPointer<Variant> v;
                v <<= new Variant();
                v->Parse(x);
                (*data.rbegin())->Add(v);                
              }
              ++i;
              k = i;
              break;
            case '{':
              {
                ++i;
                data.push_back(new ExportableEnumeration<IVariant>());
                k = i;
              }
              break;
            case '}':
              {
                ++i;
                if (data.size() > 1)
                {
                  IEnumeration<IVariant *> * last = *data.rbegin();
                  data.pop_back();
                  SmartPointer<IVariant> v;
                  v <<= new Variant(last);
                  last->Release();
                  (*data.rbegin())->Add(v.p);
                  k = i;
                }
              }
              break;
            default:
              ++i;
            }
          }
          if (i>k)
          {
            const std::string & tmp = Utils::Trim(s.substr(k));
            SmartPointer<Variant> v;
            v <<= new Variant();
            v->Parse(tmp);
            (*data.rbegin())->Add(v);
          }

          return *data.rbegin(); // result.Detach();
        }

#pragma region Type convertion

        template <class T>
        T ConvertTo()
        {
          switch (m_Holder->GetType())
          {
          case VariantType::EmptyValue:
            return T();
          case VariantType::UnsignedIntegerValue:
            return CastTo<T, uint>(((IntegerHolder *)m_Holder)->GetValue());
          case VariantType::IntegerValue:
            return CastTo<T, int>(((IntegerHolder *)m_Holder)->GetValue());
          case VariantType::Int64Value:
            return CastTo<T, long long>(((Int64Holder *)m_Holder)->GetValue());
          case VariantType::BooleanValue:
            return CastTo<T, bool>(((BooleanHolder *)m_Holder)->m_Value);
          case VariantType::StringValue:
						return CastTo<T, std::string>(((StringHolder *)m_Holder)->m_Value);
          case VariantType::ByteArrayValue:
						return CastTo<T, ByteVector>(((ByteArrayHolder *)m_Holder)->m_Value);
          case VariantType::ArrayValue:
            {
              SmartPointer<IEnumeration<IVariant*>> value;
              value <<= ((ArrayHolder *)m_Holder)->GetValue();
							return CastTo<T, IEnumeration<IVariant*> *>(value.p);
            }
          case VariantType::ExportableValue:
            {
              SmartPointer<IExportable> value;
              value <<= ((ExportableHolder *)m_Holder)->GetValue();
              return CastTo<T, ExportablePtr>(value.p);
            }
          case VariantType::TimePoint:
            return CastTo<T, std::chrono::system_clock::time_point>(((TimePointHolder *)m_Holder)->GetValue());
          default:
            throw BadCastException("Конверсия не определена");
          }
        }

#ifndef __GNUG__
        //template <>
        //int ConvertTo<int>();

      //  template <>
      //  uint ConvertTo<uint>()
      //  {
      //    switch (m_Holder->GetType())
      //    {
      //    case VariantType::EmptyValue:
      //      return 0;
      //    case VariantType::UnsignedIntegerValue:
      //      return ((UintHolder *)m_Holder)->GetValue();
      //    case VariantType::IntegerValue:
      //      return (uint)((IntegerHolder *)m_Holder)->GetValue();
      //    case VariantType::Int64Value:
      //      return (uint)((Int64Holder *)m_Holder)->GetValue();
      //    case VariantType::BooleanValue:
      //      return CastTo<uint, bool>(((BooleanHolder *)m_Holder)->m_Value);
      //    case VariantType::StringValue:
						//return CastTo<uint, std::string>(((StringHolder *)m_Holder)->m_Value);
      //    case VariantType::TimePoint:
      //      return 0;
      //    default:
      //      throw BadCastException("Конверсия не определена");
      //    }
      //  }

     //   template <>
     //   std::string ConvertTo<std::string>()
     //   {
     //     switch (m_Holder->GetType())
     //     {
     //     case VariantType::EmptyValue:
     //       return "";
     //     case VariantType::IntegerValue:
     //       return CastTo<std::string, int>(((IntegerHolder *)m_Holder)->GetValue());
     //     case VariantType::UnsignedIntegerValue:
     //       return CastTo<std::string, uint>(((UintHolder *)m_Holder)->GetValue());
     //     case VariantType::Int64Value:
     //       return CastTo<std::string, long long>(((Int64Holder *)m_Holder)->GetValue());
     //     case VariantType::BooleanValue:
     //       return CastTo<std::string, bool>(((BooleanHolder *)m_Holder)->m_Value);
     //     case VariantType::StringValue:
					//	return ((StringHolder *)m_Holder)->m_Value;
     //     case VariantType::ByteArrayValue:
     //     	return CastTo<std::string>(((ByteArrayHolder *)m_Holder)->m_Value);
     //     case VariantType::ArrayValue:
     //       {
     //         SmartPointer<IEnumeration<IVariant*>> value;
     //         value <<= ((ArrayHolder *)m_Holder)->GetValue();
					//		return CastTo<std::string>(value.p);
     //       }
     //     case VariantType::TimePoint:
     //       {
     //         std::chrono::system_clock::time_point val = ((TimePointHolder *)m_Holder)->GetValue();

     //         std::chrono::system_clock::duration tp = val.time_since_epoch();
     //         auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
     //         auto fraction = val - seconds;
     //         std::chrono::system_clock::time_point j = val-fraction.time_since_epoch();

     //         time_t time = std::chrono::system_clock::to_time_t(j);
     //         tm t;
     //         localtime_s(&t, &time);

     //         std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

     //         std::stringstream x;
     //         x<<'[';
     //         x<< (t.tm_year+1900); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
     //         x<< '.';
     //         x<<std::setfill('0')<<std::setw(2)<< (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
     //         x<< '.';
     //         x<<std::setfill('0')<<std::setw(2)<< t.tm_mday;
     //         x<< ' ';
     //         x<<std::setfill('0')<<std::setw(2)<<t.tm_hour;
     //         x<< ':';
     //         x<<std::setfill('0')<<std::setw(2)<<t.tm_min;
     //         x<< ':';
     //         x<<std::setfill('0')<<std::setw(2)<<t.tm_sec;
     //         x<< '.';
     //         x<<std::setfill('0')<<std::setw(3)<<millis.count();
     //         x<<']';
     //         return x.str();
     //       }
					//case VariantType::ExportableValue:
     //                                     return "exportable";
     //     default:
     //       throw BadCastException("Конверсия не определена");
     //     }
     //   }

				template <>
				const char * ConvertTo<const char *>()
				{
					switch (m_Holder->GetType())
					{
					case VariantType::EmptyValue:
						return "";
					case VariantType::IntegerValue:
						return export_local((CastTo<std::string, int>(((IntegerHolder *)m_Holder)->GetValue())));
					case VariantType::UnsignedIntegerValue:
						return export_local((CastTo<std::string, uint>(((UintHolder *)m_Holder)->GetValue())));
					case VariantType::Int64Value:
						return export_local((CastTo<std::string, long long>(((Int64Holder *)m_Holder)->GetValue())));
					case VariantType::BooleanValue:
						return export_local((CastTo<std::string, bool>(((BooleanHolder *)m_Holder)->m_Value)));
					case VariantType::StringValue:
						return ((StringHolder *)m_Holder)->m_Value.c_str();
					case VariantType::ByteArrayValue:
						return export_local(CastTo<std::string>(((ByteArrayHolder *)m_Holder)->m_Value));
					case VariantType::ArrayValue:
					{
						SmartPointer<IEnumeration<IVariant*>> value;
						value <<= ((ArrayHolder *)m_Holder)->GetValue();
						//return ConvertVariantArrayToString(value.p);
						return export_local(CastTo<std::string>(value.p));
					}
					case VariantType::TimePoint:
					{
						std::chrono::system_clock::time_point val = ((TimePointHolder *)m_Holder)->GetValue();

						std::chrono::system_clock::duration tp = val.time_since_epoch();
						auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
						auto fraction = val - seconds;
						std::chrono::system_clock::time_point j = val - fraction.time_since_epoch();

						time_t time = std::chrono::system_clock::to_time_t(j);
						tm t;
						localtime_s(&t, &time);

						std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(fraction.time_since_epoch());

						std::stringstream x;
						x << '[';
						x << (t.tm_year + 1900); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
						x << '.';
						x << std::setfill('0') << std::setw(2) << (t.tm_mon + 1); // Подробности http://msdn.microsoft.com/ru-ru/library/a442x3ye.aspx
						x << '.';
						x << std::setfill('0') << std::setw(2) << t.tm_mday;
						x << ' ';
						x << std::setfill('0') << std::setw(2) << t.tm_hour;
						x << ':';
						x << std::setfill('0') << std::setw(2) << t.tm_min;
						x << ':';
						x << std::setfill('0') << std::setw(2) << t.tm_sec;
						x << '.';
						x << std::setfill('0') << std::setw(3) << millis.count();
						x << ']';
						return export_local(x.str());
					}
					case VariantType::ExportableValue:
             return "exportable";
					default:
						throw BadCastException("Конверсия не определена");
					}
				}

      //  template <>
      //  bool ConvertTo<bool>()
      //  {
      //    switch (m_Holder->GetType())
      //    {
      //    case VariantType::EmptyValue:
      //      return false;
      //    case VariantType::UnsignedIntegerValue:
      //      return CastTo<bool, uint>(((IntegerHolder *)m_Holder)->GetValue());
      //    case VariantType::IntegerValue:
      //      return CastTo<bool, int>(((IntegerHolder *)m_Holder)->GetValue());
      //    case VariantType::Int64Value:
      //      return CastTo<bool, long long>(((Int64Holder *)m_Holder)->GetValue());
      //    case VariantType::BooleanValue:
      //      return ((BooleanHolder *)m_Holder)->m_Value;
      //    case VariantType::StringValue:
						//return CastTo<bool, std::string>(((StringHolder *)m_Holder)->m_Value);
      //    case VariantType::TimePoint:
      //      return true;
      //    default:
      //      throw BadCastException("Конверсия не определена");
      //    }
      //  }
#endif
#pragma endregion


        template <class T>
        static inline T ConvertTo(IVariant * variant)
        {
          return ((Variant *)variant)->ConvertTo<T>();
        }

				template <class T>
				static inline T Access(IVariant * variant)
				{
					return ((Variant *)variant)->ConvertTo<T>();
				}

#ifndef __GNUG__
				template <>
				static ByteVector Access(IVariant * variant)
				{
					return ((ByteArrayHolder *)(((Variant *)variant)->m_Holder))->m_Value;
				}

				template <>
				static std::string Access(IVariant * variant)
				{
					return ((StringHolder *)(((Variant *)variant)->m_Holder))->m_Value;
				}

				template <>
				static int Access(IVariant * variant)
				{
					return ((IntegerHolder *)(((Variant *)variant)->m_Holder))->GetValue();
				}
#endif

        static bool IsEqual(IVariant * v1, IVariant * v2)
        {
          //if (v1 == v2)
          //  return true;
          if (!v1)
            return !v2;
          if (!v2)
            return false;
          if ((v1 == v2) || (((Variant *)v1)->m_Holder == ((Variant *)v2)->m_Holder))
            return true;

          const VariantType t1 = v1->GetType();
          const VariantType t2 = v2->GetType();
          switch (t1)
          {
          case VariantType::EmptyValue:
            return t2 == VariantType::EmptyValue;
          case VariantType::IntegerValue:
            switch (t2)
            {
            case VariantType::IntegerValue:
              return ((IntegerHolder *)((Variant *)v1)->m_Holder)->GetValue() == ((IntegerHolder *)((Variant *)v2)->m_Holder)->GetValue();
            case VariantType::UnsignedIntegerValue:
              return ConvertTo<unsigned int>(v1) == ((UintHolder *)((Variant *)v2)->m_Holder)->GetValue();
            case VariantType::Int64Value:
              if (ConvertTo<long long>(v2)>LONG_MAX)
                return ConvertTo<long long>(v1) == Access<long long>(v2);
              else
                return ConvertTo<unsigned int>(v1) == ConvertTo<unsigned int>(v2);
            case VariantType::TimePoint:
              return ConvertTo<std::chrono::system_clock::time_point>(v1) == Access<std::chrono::system_clock::time_point>(v2);
            default:
              return false;
            }
          case VariantType::Int64Value:
            switch (t2)
            {
            case VariantType::Int64Value:
              return ((Int64Holder *)((Variant *)v1)->m_Holder)->GetValue() == ((Int64Holder *)((Variant *)v2)->m_Holder)->GetValue();
            case VariantType::TimePoint:
              return ConvertTo<std::chrono::system_clock::time_point>(v1) == ConvertTo<std::chrono::system_clock::time_point>(v2);
            case VariantType::IntegerValue:
              return ConvertTo<long long>(v1) == ConvertTo<long long>(v2);
            case VariantType::UnsignedIntegerValue:
              if (ConvertTo<long long>(v1)>LONG_MAX)
                return ConvertTo<long long>(v1) == ConvertTo<long long>(v2);
              else
                return ConvertTo<unsigned int>(v1) == ConvertTo<unsigned int>(v2);
            default:
              return false;
            }
          case VariantType::BooleanValue:
            return (t2 == t1) && (((BooleanHolder *)((Variant *)v1)->m_Holder)->m_Value == ((BooleanHolder *)((Variant *)v2)->m_Holder)->m_Value);
          case VariantType::StringValue:            
            return (t2 == t1) && (strcmp(((StringHolder *)((Variant *)v1)->m_Holder)->m_Value.c_str(),
              ((StringHolder *)((Variant *)v2)->m_Holder)->m_Value.c_str()) == 0);            
          case VariantType::ByteArrayValue:
          {
            switch (t2)
            {
            case VariantType::ByteArrayValue:
            {
              const ByteVector & value1 = ((ByteArrayHolder *)(((Variant *)v1)->m_Holder))->m_Value;
              const ByteVector & value2 = ((ByteArrayHolder *)(((Variant *)v2)->m_Holder))->m_Value;
              size_t max = value2.size();
              if (value1.size() != max)
                return false;
              for (size_t i = 0; i<max; ++i)
              {
                if (value1[i] != value2[i])
                  return false;
              }
              return true;
            }
            case VariantType::ArrayValue:
            {
              const ByteVector & data1 = ((ByteArrayHolder *)(((Variant *)v1)->m_Holder))->m_Value;
              const ByteVector & data2 = ConvertTo<ByteVector>(v2);
              size_t max = data1.size();
              if (max != data2.size())
                return false;
              for (size_t i = 0; i < max; ++i)
                if (data1[i] != data2[i])
                  return false;
              return true;
            }
            case VariantType::LambdaExpression:
            default:
              return false;
            }
          }
          case VariantType::ArrayValue:
          {
            switch (t2)
            {
            case VariantType::ArrayValue:
            {
              SmartPointer<IEnumeration<IVariant*>> value1;
              SmartPointer<IEnumeration<IVariant*>> value2;
              value1 <<= ((ArrayHolder *)(((Variant *)v1)->m_Holder))->GetValue();
              value2 <<= ((ArrayHolder *)(((Variant *)v2)->m_Holder))->GetValue();
              size_t max = value2->GetCount();
              if (value1->GetCount() != max)
                return false;
              for (size_t i = 0; i<max; ++i)
              {
                SmartPointer<IVariant> tmp1;
                tmp1 <<= value1->GetItem(i);
                SmartPointer<IVariant> tmp2;
                tmp2 <<= value2->GetItem(i);
                if (!IsEqual(tmp1, tmp2))
                  return false;
              }
              return true;
            }
            case VariantType::ByteArrayValue:
            {
              const ByteVector & data1 = ConvertTo<ByteVector>(v1);
              const ByteVector & data2 = ((ByteArrayHolder *)(((Variant *)v2)->m_Holder))->m_Value;//ConvertTo<ByteVector>(v2);
              size_t max = data1.size();
              if (max != data2.size())
                return false;
              for (size_t i = 0; i<max; ++i)
                if (data1[i] != data2[i])
                  return false;
              return true;
            }
            default:
              return false;
            }
          }
          case VariantType::UnsignedIntegerValue:
            switch (t2)
            {
            case VariantType::UnsignedIntegerValue:
              return ((UintHolder *)((Variant *)v1)->m_Holder)->GetValue() == ((UintHolder *)((Variant *)v2)->m_Holder)->GetValue();
            case VariantType::Int64Value:
              if (ConvertTo<long long>(v2)>LONG_MAX)
                return ConvertTo<long long>(v1) == ConvertTo<long long>(v2);
              else
                return ConvertTo<unsigned int>(v1) == ConvertTo<unsigned int>(v2);
            case VariantType::IntegerValue:
              return ConvertTo<unsigned int>(v1) == ConvertTo<unsigned int>(v2);
            default:
              return false;
            }
          case VariantType::TimePoint:
            switch (t2)
            {
            case VariantType::TimePoint:
              return ConvertTo<std::chrono::system_clock::time_point>(v1) == ConvertTo<std::chrono::system_clock::time_point>(v2);
            case VariantType::IntegerValue:
            case VariantType::Int64Value:
              return ConvertTo<std::chrono::system_clock::time_point>(v1) == ConvertTo<std::chrono::system_clock::time_point>(v2);
            default:
              return false;
            }
          case VariantType::ExportableValue:
            if (t2 == VariantType::ExportableValue)
            {
              SmartPointer<IExportable> value1;
              SmartPointer<IExportable> value2;
              value1 <<= ((ExportableHolder *)(((Variant *)v1)->m_Holder))->GetValue();
              value2 <<= ((ExportableHolder *)(((Variant *)v2)->m_Holder))->GetValue();
              return value1.p == value2.p;
            }
#ifdef __GNUG__
          case VariantType::LambdaExpression:
            return false;
#endif
          }
          return false;
        }

#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
        void SwapWith(IVariant * other)
        {
          Variant * v = dynamic_cast<Variant *>(other);
          IValueHolder * h = m_Holder;
          m_Holder = v->m_Holder;
          m_Holder->AddRef();
          h->Release();
        }
#endif
      };

      // Указатель на Variant
      typedef SmartPointer<Variant> VariantPtr;

      template <>
      inline VariantVector CastTo(const std::string & value)
      {
        VariantVector result;
        VariantPtr val;
        val.Attach(new Variant(value));
        result.Add(val.p);
        return result;
      }

      template <>
      inline VariantVector CastTo(const std::chrono::system_clock::time_point & value)
      {
        VariantVector result;
        VariantPtr val;
        val.Attach(new Variant(value));
        result.Add(val.p);
        return result;
      }

      template <>
      inline std::set<int> CastTo(const VariantEnumerationPtr & value)
      {
        std::set<int> result;
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)value->GetItem(i));
            result.insert(res->ConvertTo<int>());
          }
        }
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const VariantEnumerationPtr & value)
      {
        std::list<std::string> result;
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)value->GetItem(i));
            result.push_back(res->ConvertTo<std::string>());
          }
        }
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const VariantEnumerationPtr & value)
      {
        std::vector<unsigned char> result;
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)value->GetItem(i));
            VariantType vt = res->GetType();
            if ((vt != VariantType::IntegerValue) &&
                (vt != VariantType::UnsignedIntegerValue) &&
                (vt != VariantType::Int64Value))
              throw BadCastException();
            //if (res->GetType() != VariantType::IntegerValue)
            //  throw BadCastException();
            int k = res->ConvertTo<int>();
            if (k>255)
              throw BadCastException();
            result.push_back((unsigned char)k);
          }
        }
        return result;
      }

      template <>
      inline VariantVector CastTo(const VariantEnumerationPtr & value)
      {
        VariantVector result;
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)value->GetItem(i));
            result.Add(res);
          }
        }
        return result;
      }

      template <>
      inline VariantVector CastTo(const ByteVector & value)
      {
        VariantVector result;
        size_t max = value.size();
        for (size_t i=0;i<max;++i)
        {
          VariantPtr res;
          res.Attach(new Variant(value[i]));
          result.Add(res);
        }
        return result;
      }

      template <>
      inline std::set<std::string> CastTo(const VariantEnumerationPtr & value)
      {
        std::set<std::string> result;
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)value->GetItem(i));
            result.insert(res->ConvertTo<std::string>());
          }
        }
        return result;
      }

      template <>
      inline std::set<int> CastTo(const int & value)
      {
        std::set<int> result;
        result.insert(value);
        return result;
      }

      template <>
      inline std::set<int> CastTo(const uint & value)
      {
        std::set<int> result;
        result.insert(value);
        return result;
      }

      template <>
      inline std::set<int> CastTo(const long long & value)
      {
        std::set<int> result;
        result.insert((int)value);
        return result;
      }


      template <>
      inline std::set<int> CastTo(const bool & value)
      {
        std::set<int> result;
        result.insert(value ? 1 : 0);
        return result;
      }

      template <>
      inline std::set<int> CastTo(const std::string & value)
      {
        std::set<int> result;
        result.insert(atoi(value.c_str()));
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const unsigned int & value)
      {
        std::vector<unsigned char> result;
        if (value<=255)
          result.push_back((unsigned char)value);
        else
        {
          result.push_back(value >> 24);
          result.push_back((value >> 16) & 0xFF);
          result.push_back((value >> 8) & 0xFF);
          result.push_back((value)& 0xFF);
        }
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const int & value)
      {
        std::vector<unsigned char> result;
        if (value<=255)
          result.push_back((unsigned char)value);
        else
        {
          result.push_back(value >> 24);
          result.push_back((value >> 16) & 0xFF);
          result.push_back((value >> 8) & 0xFF);
          result.push_back((value)& 0xFF);
        }
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const long long & value)
      {
        std::vector<unsigned char> result;
        if (value<=255)
          result.push_back((unsigned char)value);
        else
        {
          result.push_back((value >> 56) & 0xFF);
          result.push_back((value >> 48) & 0xFF);
          result.push_back((value >> 40) & 0xFF);
          result.push_back((value >> 32) & 0xFF);
          result.push_back((value >> 24) & 0xFF);
          result.push_back((value >> 16) & 0xFF);
          result.push_back((value >> 8) & 0xFF);
          result.push_back((value)& 0xFF);
        }
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const bool & value)
      {
        std::vector<unsigned char> result;
        result.push_back(value ? 1 : 0);
        return result;
      }



      template <>
      inline std::vector<unsigned char> CastTo(const std::string & value)
      {
        std::vector<unsigned char> result;
        size_t max = value.size();
        if (!Utils::IsNumber(value)) //(max > 3) && 
        {
          result.resize(max);
          for (size_t i = 0; i<max; ++i)
            result[i] = value[i];
        }
        else
        {
          int val = atoi(value.c_str());
          if (val > 255)
          {
            result.resize(max);
            for (size_t i = 0; i<max; ++i)
              result[i] = value[i];
          }
          else //throw BadCastException();
            result.push_back((unsigned char)val);
        }
        return result;
      }
/*
      template <>
      inline std::vector<unsigned char> CastTo(const std::string & value)
      {
        std::vector<unsigned char> result;
        int val = atoi(value.c_str());
        if (val > 255)
          throw BadCastException();
        result.push_back((unsigned char)val);
        return result;
      } */


      template <>
      inline std::set<int> CastTo(const ExportablePtr & value)
      {
        std::set<int> result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)v->GetItem(i));
            result.insert(res->ConvertTo<int>());
          }
        }
        return result;
      }

      template <>
      inline std::vector<unsigned char> CastTo(const ExportablePtr & value)
      {
        std::vector<unsigned char> result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)v->GetItem(i));
            VariantType vt = res->GetType();
            if ((vt != VariantType::IntegerValue) &&
                (vt != VariantType::UnsignedIntegerValue) &&
                (vt != VariantType::Int64Value))
              throw BadCastException();
            //if (res->GetType() != VariantType::IntegerValue)
            //  throw BadCastException();
            int k = res->ConvertTo<int>();
            if (k>255)
              throw BadCastException();
            result.push_back((unsigned char)k);
          }
        }
        return result;
      }

      template <>
      inline VariantVector CastTo(const ExportablePtr & value)
      {
        VariantVector result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)v->GetItem(i));
            result.Add(res);
          }
        }
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const int & value)
      {
        std::list<std::string> result;
        result.push_back(std::to_string(value));
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const long long & value)
      {
        std::list<std::string> result;
        result.push_back(std::to_string(value));
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const bool & value)
      {
        std::list<std::string> result;
        result.push_back(value ? "True" : "False");
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const std::string & value)
      {
        std::list<std::string> result;
        result.push_back(value);
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const ExportablePtr & value)
      {
        std::list<std::string> result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)v->GetItem(i));
            result.push_back(res->ConvertTo<std::string>());
          }
        }
        return result;
      }

      template <>
      inline std::list<std::string> CastTo(const ByteVector & /*value*/)
      {
        throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::set<std::string> CastTo(const int & value)
      {
        std::set<std::string> result;
        result.insert(std::to_string(value));
        return result;
      }

      template <>
      inline std::set<std::string> CastTo(const uint & value)
      {
        std::set<std::string> result;
        result.insert(std::to_string(value));
        return result;
      }


      template <>
      inline std::set<std::string> CastTo(const long long & value)
      {
        std::set<std::string> result;
        result.insert(std::to_string(value));
        return result;
      }


      template <>
      inline std::set<std::string> CastTo(const bool & value)
      {
        std::set<std::string> result;
        result.insert(value ? "True" : "False");
        return result;
      }

      template <>
      inline std::set<std::string> CastTo(const std::string & value)
      {
        std::set<std::string> result;
        result.insert(value);
        return result;
      }

      template <>
      inline std::set<std::string> CastTo(const ExportablePtr & value)
      {
        std::set<std::string> result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          for (size_t i=0;i<max;++i)
          {
            VariantPtr res;
            res.Attach((Variant *)v->GetItem(i));
            result.insert(res->ConvertTo<std::string>());
          }
        }
        return result;
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const int & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const long long & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const bool & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const std::string & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const unsigned int & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const ByteVector & /*value*/)
      {
        throw BadCastException();
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const ExportablePtr & value)
      {
        std::map<std::string, std::string> result;
        if (value)
        {
          VariantEnumerationPtr v = (VariantEnumerationPtr)value;
          size_t max = v->GetCount();
          if (max % 2 != 0)
          {
            size_t i=0;
            while (i<max)
            {
              VariantPtr key;
              key.Attach((Variant *)v->GetItem(i));
              ++i;
              VariantPtr val;
              val.Attach((Variant *)v->GetItem(i));
              ++i;
              result.insert(std::make_pair(key->ConvertTo<std::string>(), val->ConvertTo<std::string>()));
            }
          }
        }
        return result;
      }

      template <>
      inline std::string CastTo(const ExportablePtr & value)
      {
        if (!value)
          return "null";
        return "<object>";
        //  throw BadCastException("Конверсия не определена");
      }

      template <>
      inline std::map<std::string, std::string> CastTo(const VariantEnumerationPtr & value)
      {
        std::map<std::string, std::string> result;
        if (value)
        {
          size_t max = value->GetCount();
          if (max % 2 == 0)
          {
            size_t i=0;
            while (i<max)
            {
              VariantPtr key;
              key.Attach((Variant *)value->GetItem(i));
              ++i;
              VariantPtr val;
              val.Attach((Variant *)value->GetItem(i));
              ++i;
              result.insert(std::make_pair(key->ConvertTo<std::string>(), val->ConvertTo<std::string>()));
            }
          }
        }
        return result;
      }

      template <>
      inline std::string CastTo(const VariantEnumerationPtr & value)
      {
        std::string result = "{";
        if (value)
        {
          size_t max = value->GetCount();
          for (size_t i=0;i<max;++i)
          {
            if (i>0)
              result += ", ";
            SmartPointer<IVariant> res;
            res.Attach(value->GetItem(i));
						result += Variant::ConvertTo<std::string>(res);
          }
        }
        result += "}";
        return result;
      }

//#ifndef __GNUG__
//      template <>
//      int Variant::ConvertTo<int>()
//      {
//        switch (m_Holder->GetType())
//        {
//        case VariantType::EmptyValue:
//          return 0;
//        case VariantType::UnsignedIntegerValue:
//          return ((UintHolder *)m_Holder)->GetValue();
//        case VariantType::IntegerValue:
//          return ((IntegerHolder *)m_Holder)->GetValue();
//        case VariantType::Int64Value:
//          return (int)((Int64Holder *)m_Holder)->GetValue();
//        case VariantType::BooleanValue:
//          return CastTo<int, bool>(((BooleanHolder *)m_Holder)->m_Value);
//        case VariantType::StringValue:
//          return CastTo<int, std::string>(((StringHolder *)m_Holder)->m_Value);
//        case VariantType::TimePoint:
//          return 0;
//        default:
//          throw BadCastException("Конверсия не определена");
//        }
//      }
//#endif

      template <>
      inline ExportablePtr CastTo(const std::string & /*value*/)
      {
        return NULL;
      }

      template <>
      inline ExportablePtr CastTo(const ByteVector & /*value*/)
      {
        return NULL;
      }

      template <>
      inline VariantVector CastTo(const int & value)
      {
        VariantVector result;
        VariantPtr val;
        val <<= new Variant(value);
        result.Add(val.p);
        return result;
      }

      template <>
      inline VariantVector CastTo(const uint & value)
      {
        VariantVector result;
        VariantPtr val;
        val <<= new Variant(value);
        result.Add(val.p);
        return result;
      }

      template <>
      inline VariantVector CastTo(const long long & value)
      {
        VariantVector result;
        VariantPtr val;
        val <<= new Variant(value);
        result.Add(val.p);
        return result;
      }

      template <>
      inline VariantVector CastTo(const bool & value)
      {
        VariantVector result;
        VariantPtr val;
        val <<= new Variant(value);
        result.Add(val.p);
        return result;
      }

      typedef IVariant* variant;

      typedef std::list<std::string> StringList;
      typedef std::set<std::string> StringSet;
      typedef std::list<int> IntList;
      typedef std::set<int> IntSet;
      typedef std::map<std::string, std::string> StringMap;
#ifdef __GNUG__
      typedef std::string StringListItem;
      typedef std::string StringVectorItem;
#endif

      /// <summary>
      /// Конструирует объект ByteVector по массиву
      /// </summary>
      #define MakeByteVector(count, data) ByteVector(data, data+count)

      template <class T>
      inline T VariantPtrTo(IVariant * value)
      {
        return Variant::ConvertTo<T>(value);
      }

    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller

