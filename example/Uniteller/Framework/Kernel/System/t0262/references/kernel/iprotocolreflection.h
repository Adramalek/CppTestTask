// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ‘айл содержит базовую реализацию типа Variant

#pragma once

#include "ivendordatasource.h"
//#include "istatemachine.h"
#include "iregistry.h"
#include "ifactory.h"
#include "iapplicationhost.h"
#include "iuidgen.h"
#include "imessageinfo.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Ёкспортируемый интерфейс библиотеки микро-€дра Uniteller.Framework.Kernel
      /// </summary>
      interface IProtocolReflection : public IExportable
      {
      public:
          virtual void Load(IRegistry * registry) = 0;
          // ѕозвол€ет получить код сообщени€ по имени
          virtual event_t QueryMessageCode(const char * szMessage) = 0;
          virtual event_t QueryProtocolCode(const char * szProtocol) = 0;
          // ѕозвол€ет получить индекс аргумента сообщени€ по имени
          ////virtual int QueryMessageArgumentIndex(const char * szMessage, int generation, const char * szArgumentName) = 0;
          ////virtual int QueryMessageArgumentIndex(event_t evt, int generation, const char * szArgumentName) = 0;
          ////virtual VariantType QueryMessageArgumentType(const char * szMessage, int generation, const char * szArgumentName) = 0;
          /// <summary>
          /// ѕозвол€ет получить им€ сообщени€ по коду
          /// </summary>
          virtual std::string QueryMessageName(event_t code) = 0; 
          /// <summary>
          /// ѕозвол€ет получить им€ аргумента сообщени€ по индексу
          /// </summary>
					virtual std::string QueryMessageArgumentName(const char * szMessage, int generation, int index) = 0;

          virtual bool QueryEnumValueCode(const char * protocol, const char * szEnum, int generation, int & result) = 0;
          virtual bool QueryEnumValueCode(const char * szEnum, int generation, int & result) = 0;

          //virtual bool IsFlagMask(const char * szMask) = 0;

          ////virtual bool IsMessageGenerationExists(const char * szMessage, int generation) = 0;
          virtual bool IsEnumExists(const char * szEnum) = 0;
          virtual bool IsFlagExists(const char * szEnum) = 0;

					////virtual IMessage * QueryMessage(const char * protocol, const char * message, event_t code, int generation, int argc) = 0;

          virtual void Clear() = 0;

          virtual bool IsConnected() const = 0;
	
  	      virtual IMessageInfo * QueryMessageDescriptor(const char * szMessage) = 0;
      	  virtual IMessageInfo * QueryMessageDescriptor(const event_t code) = 0;
          virtual IVariant * QueryKey(const char * szKey) = 0;

          virtual bool EvalFlagMask(const char * mask, size_t border, int generation, int & result) = 0;
          //virtual bool EvalFlagMask(IForm * form, int generation, int & result) = 0;
          virtual IRegistryKey * OpenKey(const char * szKey) = 0;
      };

			bool UnpackItem(const std::string & value, std::string & module, std::string & item);

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller