// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию класса обертки сообщения, передаваемого по шине передачи сообщений

#pragma once

#include "message.h" // IMessage
#include "kernel/smartqipointer.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      using std::string;

#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
			IMessage * CloneMessage(IMessage * src);
#endif
      
      /// <summary>
      /// Обертка вокруг указателя на сообщение
      /// </summary>
			class MessageWrapper : public MessagePtr
      {
      public:
        /// <summary>
        /// Инициализирует новый экземпляр обертки над сообщением <see cref="MessageWrapper"/>
        /// </summary>
        /// <param name="message">Сообщение</param>
				MessageWrapper(IMessage * message) : MessagePtr(message)
        {
        }
        /// <summary>
        /// Инициализирует новый экземпляр обертки над сообщением <see cref="MessageWrapper"/>
        /// </summary>
        /// <param name="kind">Тип сообщения</param>
        /// <param name="generation">Поколение</param>
        /// <param name="argc">Число аргументов</param>
        MessageWrapper(event_t kind, int generation, int argc)
        {
          Attach(new Message(kind, generation, argc));
        }
        // число аргументов
        PROPERTY_DELEGATION(size_t, ArgumentsCount, p);
        // поколение
        READONLY_PROPERTY_DELEGATION(int, Generation, p);
        // тип сообщения
        READONLY_PROPERTY_DELEGATION(event_t, Kind, p);
        // приоритет сообщения
        PROPERTY_DELEGATION(int, Priority, p);
        // источник сообщения
        READONLY_PROPERTY_DELEGATION(address, SourceId, p);
        // приемник сообщения
        READONLY_PROPERTY_DELEGATION(address, TargetId, p);
        
        /// <summary>
        /// Позволяет очистить сообщение
        /// </summary>
        void Clear()
        {
          p->Clear();
        }

        IMessage * Clone()
        {
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
					return CloneMessage(p);
#else
					if (!p)
						throw NullReferenceException("p");   
          SmartPointer<Message> msg;
          size_t max = p->GetArgumentsCount();
          msg <<= new Message(p->GetKind(), p->GetGeneration(), max);
          msg->SetTargetId(p->GetTargetId());
          msg->SetSourceId(p->GetSourceId());
          msg->SetPriority(p->GetPriority());
          msg->SetSendTime(p->GetSendTime());
          for (size_t i=0;i<max;++i)
          {
            SmartPointer<IVariant> arg;
            arg <<= p->GetArgument(i);
            msg->SetArgument(i, arg);
          }
          return msg.Detach();
#endif
        }

        //NoAddRefReleaseOnIExportable<IMessage>* operator->() const
        //{          
        //  if (!m_pMessage.p)
        //    throw NullReferenceException("m_pMessage");          
        //  return (NoAddRefReleaseOnIExportable<IMessage>*)m_pMessage.p;
        //}

        #define SET_ARGUMENT_IMPL(type) \
        void SetArgument_##type(size_t index, const type value)\
        {\
          if (!p) \
						throw NullReferenceException("p"); \
          SmartPointer<Variant> v;\
          v <<= new Variant(value);\
          p->SetArgumentTo(index, v);\
        }
        #define GET_ARGUMENT_IMPL(type)\
        type GetArgument_##type(size_t index) const \
        {\
          if (!p) \
						throw NullReferenceException("p"); \
          SmartPointer<IVariant> value;\
          value.Attach(p->GetArgument(index));\
          if (value.p)\
          {\
            return ((Variant *)value.p)->ConvertTo<type>();\
          }\
          throw std::out_of_range("index");\
        }
        
        SET_ARGUMENT_IMPL(uint)
        SET_ARGUMENT_IMPL(int)
        SET_ARGUMENT_IMPL(__int64)
        SET_ARGUMENT_IMPL(bool)
        SET_ARGUMENT_IMPL(timestamp_t)

        /// <summary>
        /// Позволяет установить аргумент строкового типа
        /// </summary>
        /// <param name="index">Индекс аргумента</param>
        /// <param name="value">Значение</param>
        void SetArgument_string(size_t index, const char * value)
        {
					if (!p) 
						throw NullReferenceException("p"); 
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v);
        }

        void SetArgument_variant(size_t index, IVariant * value)
        {
					if (!p)
						throw NullReferenceException("p");
					p->SetArgument(index, value);
        }

        void SetArgument_byte(size_t index, const byte value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant((int)value);
          p->SetArgument(index, v);
        }

        IVariant * GetArgument_variant(size_t index) const
				{
					if (!p)
						throw NullReferenceException("p");
          return p->GetArgument(index);
        }
 
        VariantType GetArgumentType(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> data;
          data <<= p->GetArgument(index);
          return data->GetType();
        }

        void SetArgument_message(size_t index, IMessage * value)
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<Variant> v;
          v.Create();
          v->SetExportableValue(value);
          p->SetArgumentTo(index, v);
        }

        IMessage * GetArgument_message(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          return (IMessage *)((Variant *)value.p)->ConvertTo<ExportablePtr>();
        }

        void SetArgument_StringList(size_t index, const std::list<std::string> & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v);
        }

        void SetArgument_StringSet(size_t index, const std::set<std::string> & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index,v);
        }

	      void SetArgument_StringMap(size_t index, const std::map<std::string, std::string> & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v);
        }

        void SetArgument_IntList(size_t index, const std::list<int> & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v);
        }

        void SetArgument_IntSet(size_t index, const std::set<int> & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v);
        }

        template <class MsgType>
        void SetArgument_MessagesVector(size_t index, const vector<MsgType> & value)
        {
					if (!p)
						throw NullReferenceException("p");
          Variant v;
          SmartPointer<ExportableEnumeration<IMessage>> data;
          data <<= new ExportableEnumeration<IMessage>();
          //for (auto i : value)
          typename vector<MsgType>::iterator i = value.begin();
          typename vector<MsgType>::iterator e = value.end();
          while (i!=e)
          {
            data->Add(*i);
            ++i;
          }
          v = data;
          p->SetArgument(index, &v);
        }

        template <class MsgType>
        vector<MsgType> GetArgument_MessagesVector(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          vector<MsgType> result;
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          SmartQiPointer<IEnumeration<IMessage *>> data;
          data <<= ((Variant *)value.p)->ConvertTo<ExportablePtr>();
          size_t max = data->GetCount();
          for (size_t i =0; i<max;++i)
          {
            SmartPointer<IMessage> message;
            message <<= data->GetItem(i);
            MsgType msg(message);
            result.push_back(msg);
          }
          return result;
        }

        void SetArgument_VariantVector(size_t index, const VariantVector & value)
        {
					if (!p)
						throw NullReferenceException("p");
          VariantVector * v1 = const_cast<VariantVector *>(&value);
					SmartPointer<Variant> v;
					v <<= new Variant(v1);
          p->SetArgumentTo(index, v.p);
        }

        std::list<std::string> GetArgument_StringList(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          return ((Variant *)value.p)->ConvertTo<std::list<std::string>>();
        }

        VariantVector GetArgument_VariantVector(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          return ((Variant *)value.p)->ConvertTo<VariantVector>();
        }

        std::set<std::string> GetArgument_StringSet(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          return ((Variant *)value.p)->ConvertTo<std::set<std::string>>();
        }

	      std::map<std::string, std::string> GetArgument_StringMap(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
		      return ((Variant *)value.p)->ConvertTo<std::map<std::string, std::string>>();
        }

        void SetArgument_ByteVector(size_t index, const std::vector<unsigned char> & value)
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<Variant> v;
          v<<= new Variant(value);
          p->SetArgumentTo(index, v); // Срезаем одно копирование массива
        }

        void SetArgument_ByteVector(size_t index, const unsigned char * data, const size_t len)
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<Variant> v;
          v <<= new Variant(data, len);
          p->SetArgumentTo(index, v); // Срезаем одно копирование массива
        }

        /// <summary>
        /// Позволяет установить аргумент строкового типа
        /// </summary>
        /// <param name="index">Индекс аргумента</param>
        /// <param name="value">Значение</param>
        void SetArgument_string(size_t index, const std::string & value)
        {
					if (!p)
						throw NullReferenceException("p");
					SmartPointer<Variant> v;
					v <<= new Variant(value);
          p->SetArgumentTo(index, v.p);
        }        

        GET_ARGUMENT_IMPL(uint)
        GET_ARGUMENT_IMPL(int)
        GET_ARGUMENT_IMPL(__int64)
        GET_ARGUMENT_IMPL(bool)
        GET_ARGUMENT_IMPL(byte)
        GET_ARGUMENT_IMPL(string)
        GET_ARGUMENT_IMPL(timestamp_t)

        std::vector<unsigned char> GetArgument_ByteVector(size_t index) const
        {
					if (!p)
						throw NullReferenceException("p");
          SmartPointer<IVariant> value;
          value <<= p->GetArgument(index);
          return ((Variant *)value.p)->ConvertTo<std::vector<unsigned char>>();
        }

      private:
        friend class InterceptorThread;
        friend class ObserverThread;
        friend class Dispatcher;
      };

#ifndef __GNUG__
      #define BEGIN_MESSAGE(Name, Kind, Argc) \
        namespace Codes { \
        const Uniteller::Framework::Kernel::event_t Name = MAKE_MESSAGE_CODE(Kind); \
        } \
        class Name : public MessageWrapper \
        { \
        public: \
          Name() : MessageWrapper(Codes::Name, ProtocolGeneration, Argc) \
          { \
            __if_exists(Name::InitializeMessage) { InitializeMessage(); } \
          } \
          explicit Name(IMessage * message) : MessageWrapper(message) \
          { \
          }
#else
      #define BEGIN_MESSAGE(Name, Kind, Argc) \
        namespace Codes { \
        const Uniteller::Framework::Kernel::event_t Name = MAKE_MESSAGE_CODE(Kind); \
        } \
        class Name : public MessageWrapper \
        { \
        public: \
          Name() : MessageWrapper(Codes::Name, ProtocolGeneration, Argc) \
          { \
            InitializeMessage(); \
          } \
          explicit Name(IMessage * message) : MessageWrapper(message) \
          { \
          }
#endif        
    #define END_MESSAGE() }; 
        
#ifndef __GNUG__
      #define ARGUMENT(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_##type(index, value); \
        } \
        type Get##name() const \
        { \
          return GetArgument_##type(index); \
        } \
        bool Is##name##NotEmpty() const \
        { \
          return GetArgumentType(index) != VariantType::EmptyValue; \
        } \
        __declspec(property(get=Get##name, put=Set##name)) type name             

      #define ENUM(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_int(index, (int)value); \
        } \
        type Get##name() const \
        { \
          return ConvertTo##type(GetArgument_int(index)); \
        } \
        bool Is##name##Valid() const \
        { \
          return IsValid##type##Value(GetArgument_int(index)); \
        } \
        __declspec(property(get=Get##name, put=Set##name)) type name       
 
      #define FLAG(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_int(index, (int)value); \
        } \
        type Get##name() const \
        { \
          return (##type)(GetArgument_int(index)); \
        } \
        bool Is##name##Valid() const \
        { \
          return IsValid##type##Value(GetArgument_int(index)); \
        } \
        __declspec(property(get=Get##name, put=Set##name)) type name   

      #define ALIAS(type, name1, name2) \
        inline void Set##name1(const type & value) \
        { \
          Set##name2(value); \
        } \
        inline type Get##name1() const \
        { \
          return Get##name2(); \
        } \
        bool Is##name1##NotEmpty() const \
        { \
          return Is##name2##NotEmpty(); \
        } \
        __declspec(property(get=Get##name2, put=Set##name2)) type name1            

#else

      #define ARGUMENT(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_##type(index, value); \
        } \
        type Get##name() const \
        { \
          return GetArgument_##type(index); \
        } \
        bool Is##name##NotEmpty() const \
        { \
          return GetArgumentType(index) != VariantType::EmptyValue; \
        } 

      #define ENUM(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_int(index, (int)value); \
        } \
        type Get##name() const \
        { \
          return ConvertTo##type(GetArgument_int(index)); \
        } \
        bool Is##name##Valid() const \
        { \
          return IsValid##type##Value(GetArgument_int(index)); \
        } 
 
      #define FLAG(index, type, name) \
        void Set##name(const type & value) \
        { \
          SetArgument_int(index, (int)value); \
        } \
        type Get##name() const \
        { \
          return (type)(GetArgument_int(index)); \
        } \
        bool Is##name##Valid() const \
        { \
          return IsValid##type##Value(GetArgument_int(index)); \
        }  


      #define ALIAS(type, name1, name2) \
        inline void Set##name1(const type & value) \
        { \
          Set##name2(value); \
        } \
        inline type Get##name1() const \
        { \
          return Get##name2(); \
        } \
        bool Is##name1##NotEmpty() const \
        { \
          return Is##name2##NotEmpty(); \
        }

#endif
        
    #define BEGIN_PROTOCOL(id, g) \
      namespace G##g { \
        const int ModuleId = id; \
        const int DefaultId = id<<16; \
        const int ProtocolGeneration = g; 

    #define END_PROTOCOL() }

    #define MAKE_MESSAGE_CODE(x) (ModuleId << 16 | x)

      typedef IMessage* message;

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
