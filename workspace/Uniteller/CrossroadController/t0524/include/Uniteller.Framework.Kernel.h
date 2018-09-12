// Uniteller.Framework.Kernel

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText, 
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Protocol
      {

        BEGIN_PROTOCOL(0, 1)
          
          #pragma region Enumerations
          /// <summary> 
          /// Собирает наиболее общие ошибки, отправляемые модулями во время выполнения каких-либо действий
          /// </summary>
          enum class CommonErrors
          {
            IOError = 4, // Ошибка ввода-вывода неизвестной природы. Например, ошибки при чтении файлов, связанные с аппаратными сбоями или отказом файловой системы.
            InvalidArgument = 1, // Метод посчитал, что один из переданных аргументов - некорректный. Относится как к пустым или нулевым, так и к аргументам неправильного формата.
            NotExist = 5, // Указанный файл, дескриптор или порт не существует
            OutOfMemory = 3, // Метод попытался выделить память и получил отказ операционной системы
            TimeOut = 2 // Время ожидания какой-либо операции, выполняемой методом, истекло. Например, от порта ввода-вывода не пришел ответ. Не путать с тайм-аутом нахождения автомата модуля в определенном состоянии.
          };
          
          /// <summary> 
          /// Типы ошибок, возникающих в работе декларативным образом описанных хендлеров
          /// </summary>
          enum class HandlerErrors
          {
            ArrayViolation = 7, // - Попытка использовать модификатор доступа к элементу массива к аргументу сообщения, не являющемуся массивом
            EventNotFound = 1, // - событие не найдено в репозитории
            IncorrectArrayIndex = 6, // - Индекс массива неверен
            IncorrectVariableName = 8, // - Ошибочное значение имени переменной
            IndexOutOfRange = 5, // - Индекс массива вышел за допустимые границы
            InvalidArgumentType = 14, // - Попытка передать неверный тип аргумента
            InvalidDescriptor = 11, // - Ошибочный дескриптор декларативным образом заданного обработчика в конечном автомате
            InvalidFlag = 12, // - Неизвестный флаг (в конструкциях IsSet, IsNotSet)
            InvalidGeneration = 2, // - Указано неверное значение поколения сообщения
            InvalidPause = 17, // - Неверное значение паузы в команде Send
            InvalidSectionFormat = 16, // - Ошибка формата секции в декларативном обработчике
            IsNotSetFormatError = 10, // - Ошибка формата инструкции IsNotSet
            IsSetFormatError = 9, // - Ошибка формата инструкции IsSet
            MalformedMessage = 4, // - Плохо сформированное сообщение (null в качестве аргумента, который должен быть заполнен)
            RegExpFormatError = 13, // - Ошибка формата регулярного выражения
            UnexpectedModuleAddress = 15, // - Не удалось распознать адрес модуля
            UnknownParamIndex = 3 // - Не найден параметр в сообщении
          };
          
          /// <summary> 
          /// Идентифицирует платформу
          /// </summary>
          enum class Platforms
          {
            MacOs = 3, // MacOS любых версий
            Other = 4, // Если платформу не удалось классифицировать (что странно)
            Unix = 2, // (Все, что построено на базе Unix или Linux, кроме MacOS)
            Windows = 1 // Windows (NT, XP, Vista, 7, 8)
          };
          
          /// <summary>
          /// Валидатор корректности значения для перечислимого типа CommonErrors
          /// </summary>
          inline bool IsValidCommonErrorsValue(const int value)
          {
            return ((value >= 1)&&(value < 6));
          }
          
          /// <summary>
          /// Следует использовать для преобразования числовых значений к перечислимому типу CommonErrors
          /// </summary>
          inline CommonErrors ConvertToCommonErrors(const int value)
          {
            switch (value)
            {
              case 4:
                return CommonErrors::IOError;
              case 1:
                return CommonErrors::InvalidArgument;
              case 5:
                return CommonErrors::NotExist;
              case 3:
                return CommonErrors::OutOfMemory;
              case 2:
                return CommonErrors::TimeOut;
              default: throw KernelException("Невозможно преобразовать числовое значение %d к типу CommonErrors", value);
              }
          }
          
          /// <summary>
          /// Валидатор корректности значения для перечислимого типа HandlerErrors
          /// </summary>
          inline bool IsValidHandlerErrorsValue(const int value)
          {
            return ((value >= 1)&&(value < 18));
          }
          
          /// <summary>
          /// Следует использовать для преобразования числовых значений к перечислимому типу HandlerErrors
          /// </summary>
          inline HandlerErrors ConvertToHandlerErrors(const int value)
          {
            switch (value)
            {
              case 7:
                return HandlerErrors::ArrayViolation;
              case 1:
                return HandlerErrors::EventNotFound;
              case 6:
                return HandlerErrors::IncorrectArrayIndex;
              case 8:
                return HandlerErrors::IncorrectVariableName;
              case 5:
                return HandlerErrors::IndexOutOfRange;
              case 14:
                return HandlerErrors::InvalidArgumentType;
              case 11:
                return HandlerErrors::InvalidDescriptor;
              case 12:
                return HandlerErrors::InvalidFlag;
              case 2:
                return HandlerErrors::InvalidGeneration;
              case 17:
                return HandlerErrors::InvalidPause;
              case 16:
                return HandlerErrors::InvalidSectionFormat;
              case 10:
                return HandlerErrors::IsNotSetFormatError;
              case 9:
                return HandlerErrors::IsSetFormatError;
              case 4:
                return HandlerErrors::MalformedMessage;
              case 13:
                return HandlerErrors::RegExpFormatError;
              case 15:
                return HandlerErrors::UnexpectedModuleAddress;
              case 3:
                return HandlerErrors::UnknownParamIndex;
              default: throw KernelException("Невозможно преобразовать числовое значение %d к типу HandlerErrors", value);
              }
          }
          
          /// <summary>
          /// Валидатор корректности значения для перечислимого типа Platforms
          /// </summary>
          inline bool IsValidPlatformsValue(const int value)
          {
            return ((value >= 1)&&(value < 5));
          }
          
          /// <summary>
          /// Следует использовать для преобразования числовых значений к перечислимому типу Platforms
          /// </summary>
          inline Platforms ConvertToPlatforms(const int value)
          {
            switch (value)
            {
              case 3:
                return Platforms::MacOs;
              case 4:
                return Platforms::Other;
              case 2:
                return Platforms::Unix;
              case 1:
                return Platforms::Windows;
              default: throw KernelException("Невозможно преобразовать числовое значение %d к типу Platforms", value);
              }
          }
          
          #pragma endregion
          
          //Структуры
          #pragma region Messages and wrappers
          
          //Сообщения
          // Активационное сообщение ядра
          BEGIN_MESSAGE(Activate,21,1)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Свойства объекта
            ARGUMENT(0, VariantVector, Properties);
          END_MESSAGE(); // Activate

          // Ответ модуля на активационное сообщение ядра
          BEGIN_MESSAGE(ActivateAnswer,22,2)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
              SetMessage("");
              SetResult(true);
            }
            // - Детальное описание в случае неудачи
            ARGUMENT(0, string, Message);
            // - Результат (удалось ли активироваться)
            ARGUMENT(1, bool, Result);
          END_MESSAGE(); // ActivateAnswer

          // При выполнении сообщения модуль столкнулся с проблемой общего характера
          BEGIN_MESSAGE(CommonError,10,1)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Объект идентифицирующий проблему
            ENUM(0, CommonErrors, Error);
          END_MESSAGE(); // CommonError

          // Перехвачено событие CreateInstance, создание экземпляра было разрешено
          BEGIN_MESSAGE(CreateInstanceAllowed,15,3)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Требуемое поколение модуля (0 - любое)
            ARGUMENT(0, int, ModuleGeneration);
            // - Назначенный уникальный идентификатор модуля
            ARGUMENT(1, string, ModuleId);
            // - Тип модуля для создания
            ARGUMENT(2, string, ModuleType);
          END_MESSAGE(); // CreateInstanceAllowed

          // Перехвачено событие CreateInstance, создание экземпляра подавлено и настроен перехват
          BEGIN_MESSAGE(CreateInstanceIntercepted,14,4)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Перехватчик
            ARGUMENT(0, string, Interceptor);
            // - Требуемое поколение модуля (0 - любое)
            ARGUMENT(1, int, ModuleGeneration);
            // - Назначенный уникальный идентификатор модуля
            ARGUMENT(2, string, ModuleId);
            // - Тип модуля для создания
            ARGUMENT(3, string, ModuleType);
          END_MESSAGE(); // CreateInstanceIntercepted

          // Обращение с сообщением данного поколения не поддерживается
          BEGIN_MESSAGE(GenerationNotSupported,16,2)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Тип события при реакции на которое произошла ошибка
            ARGUMENT(0, int, EventKind);
            // - Поколение которое не поддерживается
            ARGUMENT(1, int, MessageGeneration);
          END_MESSAGE(); // GenerationNotSupported

          // Сообщение позволяет узнать платформу, на которой запущен вызываемый модуль
          BEGIN_MESSAGE(GetModulePlatform,12,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // GetModulePlatform

          // Сообщение, содержащее информацию о платформе, на которой исполняется модуль
          BEGIN_MESSAGE(GetModulePlatformAnswer,13,1)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Платформа на которой запущен модуль отправляющий ответ
            ENUM(0, Platforms, Platform);
          END_MESSAGE(); // GetModulePlatformAnswer

          // Сообщение, отправляемое в случае если есть ошибка в декларативно описанном обработчике
          BEGIN_MESSAGE(HandlerError,18,2)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Тип ошибки
            ENUM(0, HandlerErrors, Kind);
            // - Детальное описание ошибки
            ARGUMENT(1, string, Message);
          END_MESSAGE(); // HandlerError

          // Перехваченное сообщение
          BEGIN_MESSAGE(InterceptedMessage,8,1)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Перехваченное сообщение (вложенный контейнер)
            ARGUMENT(0, message, Message);
          END_MESSAGE(); // InterceptedMessage

          // Сообщение-триггер, использующееся в технологии декларативно-описанных перехватчиков
          BEGIN_MESSAGE(MatchError,17,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // MatchError

          // Модуль не смог обработать сообщение
          BEGIN_MESSAGE(ModuleFailedOnEvent,2,3)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Тип события при реакции на которое произошла ошибка
            ARGUMENT(0, int, EventKind);
            // - Тип ошибки (исключения)
            ARGUMENT(1, string, ExceptionKind);
            // - Сообщение об ошибки
            ARGUMENT(2, string, ExceptionMessage);
          END_MESSAGE(); // ModuleFailedOnEvent

          // Сообщение, полученное по подписке
          BEGIN_MESSAGE(OverHearedMessage,9,1)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Перехваченное сообщение (вложенный контейнер)
            ARGUMENT(0, message, Message);
          END_MESSAGE(); // OverHearedMessage

          // - Возобновляет ожидание на секции Receive
          BEGIN_MESSAGE(ResetWait,20,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
              SetPriority(2147483640);
            }
          END_MESSAGE(); // ResetWait

          // Служебное сообщение ядра, используемое для автоматически срабатывающих (по инициативе ядра) переходов в автоматах
          BEGIN_MESSAGE(Shift,19,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
              SetPriority(2147483640);
            }
          END_MESSAGE(); // Shift

          // Команда инициализации
          BEGIN_MESSAGE(Start,3,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Start

          // Сообщение, присылаемое в момент изменения состояния атрибута состояния конечного автомата
          BEGIN_MESSAGE(StateAttributeChanged,6,4)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Имя изменившегося атрибута (Как минимум TimeOut)
            ARGUMENT(0, string, AttributeName);
            // - Новое значение атрибута
            ARGUMENT(1, variant, AttributeNewValue);
            template <class Y>
            Y CastAttributeNewValue() const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeNewValue();
              if (!val.p)
                throw BadCastException();
              return Variant::ConvertTo<Y>(val.p);
            }
            template <class Y>
            Y GetAttributeNewValue(const Y & defval) const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeNewValue();
              if (!val.p)
                return defval;
              return Variant::ConvertTo<Y>(val.p);
            }
            // - Старое значение атрибута
            ARGUMENT(2, variant, AttributeOldValue);
            template <class Y>
            Y CastAttributeOldValue() const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeOldValue();
              if (!val.p)
                throw BadCastException();
              return Variant::ConvertTo<Y>(val.p);
            }
            template <class Y>
            Y GetAttributeOldValue(const Y & defval) const
            {
              SmartPointer<IVariant> val;
              val <<= GetAttributeOldValue();
              if (!val.p)
                return defval;
              return Variant::ConvertTo<Y>(val.p);
            }
            // - Идентификатор модуля в машине которого изменился атрибут состояния
            ARGUMENT(3, string, ModuleId);
          END_MESSAGE(); // StateAttributeChanged

          // Событие, присылаемое в момент изменения состояния конечного автомата
          BEGIN_MESSAGE(StateChanged,5,4)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Событие активировавшее переход
            ARGUMENT(0, int, Event);
            // - Имя конечного автомата перешедшего в новое состояние
            ARGUMENT(1, string, MachineName);
            // - Новое состояние машины
            ARGUMENT(2, string, NewState);
            // - Старое состояние машины
            ARGUMENT(3, string, OldState);
          END_MESSAGE(); // StateChanged

          // Команда остановки
          BEGIN_MESSAGE(Stop,4,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Stop

          // - Ответ, посылаемый модулем на любое успешно выполненное сообщение, не имеющее собственного ответа
          BEGIN_MESSAGE(Success,11,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // Success

          // Сообщение TimeOut. Рассылается машинами состояний в случае превышения допустимого интервала нахождения в определенном состоянии.
          BEGIN_MESSAGE(TimeOut,1,0)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
          END_MESSAGE(); // TimeOut

          // Неожиданное поведение функции-обработчика
          BEGIN_MESSAGE(UnexpectedBehaviour,7,5)
            /// <summary>
            /// Инициализация сообщений
            /// </summary>
            void InitializeMessage()
            {
            }
            // - Событие активировавшее переход
            ARGUMENT(0, int, Event);
            // - Имя конечного автомата в котором случилась ошибка
            ARGUMENT(1, string, MachineName);
            // - Отправляемое сообщение (вложенный контейнер)
            ARGUMENT(2, message, Message);
            // - Новое состояние машины
            ARGUMENT(3, string, NewState);
            // - Старое состояние машины
            ARGUMENT(4, string, OldState);
          END_MESSAGE(); // UnexpectedBehaviour

          
          BEGIN_WRAPPER()
            /// <summary> 
            /// Активационное сообщение ядра
            /// </summary>
            /// <param name="properties">- Свойства объекта</param>
            void Activate(const VariantVector & properties) const
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// При выполнении сообщения модуль столкнулся с проблемой общего характера
            /// </summary>
            /// <param name="error">- Объект, идентифицирующий проблему</param>
            void CommonError(CommonErrors error) const
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Перехвачено событие CreateInstance, создание экземпляра было разрешено
            /// </summary>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void CreateInstanceAllowed(int moduleGeneration, const string & moduleId, const string & moduleType) const
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Перехвачено событие CreateInstance, создание экземпляра подавлено и настроен перехват
            /// </summary>
            /// <param name="interceptor">- Перехватчик</param>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void CreateInstanceIntercepted(const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType) const
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Обращение с сообщением данного поколения не поддерживается
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="messageGeneration">- Поколение, которое не поддерживается</param>
            void GenerationNotSupported(int eventKind, int messageGeneration) const
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Сообщение позволяет узнать платформу, на которой запущен вызываемый модуль
            /// </summary>
            void GetModulePlatform() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::GetModulePlatform);
            }
            
            /// <summary> 
            /// Сообщение, отправляемое в случае если есть ошибка в декларативно описанном обработчике
            /// </summary>
            /// <param name="kind">- Тип ошибки</param>
            /// <param name="message">- Детальное описание ошибки</param>
            void HandlerError(HandlerErrors kind, const string & message) const
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Перехваченное сообщение
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void InterceptedMessage(message message) const
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Сообщение-триггер, использующееся в технологии декларативно-описанных перехватчиков
            /// </summary>
            void MatchError() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::MatchError);
            }
            
            /// <summary> 
            /// Модуль не смог обработать сообщение
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="exceptionKind">- Тип ошибки (исключения)</param>
            /// <param name="exceptionMessage">- Сообщение об ошибки</param>
            void ModuleFailedOnEvent(int eventKind, const string & exceptionKind, const string & exceptionMessage) const
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Сообщение, полученное по подписке
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void OverHearedMessage(message message) const
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// - Возобновляет ожидание на секции Receive
            /// </summary>
            void ResetWait() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ResetWait);
            }
            
            /// <summary> 
            /// Служебное сообщение ядра, используемое для автоматически срабатывающих (по инициативе ядра) переходов в автоматах
            /// </summary>
            void Shift() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shift);
            }
            
            /// <summary> 
            /// Команда инициализации
            /// </summary>
            void Start() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
            }
            
            /// <summary> 
            /// Сообщение, присылаемое в момент изменения состояния атрибута состояния конечного автомата
            /// </summary>
            /// <param name="attributeName">- Имя изменившегося атрибута (Как минимум TimeOut)</param>
            /// <param name="attributeNewValue">- Новое значение атрибута</param>
            /// <param name="attributeOldValue">- Старое значение атрибута</param>
            /// <param name="moduleId">- Идентификатор модуля в машине которого изменился атрибут состояния</param>
            void StateAttributeChanged(const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId) const
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Событие, присылаемое в момент изменения состояния конечного автомата
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата перешедшего в новое состояние</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void StateChanged(int event, const string & machineName, const string & newState, const string & oldState) const
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Команда остановки
            /// </summary>
            void Stop() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Stop);
            }
            
            /// <summary> 
            /// - Ответ, посылаемый модулем на любое успешно выполненное сообщение, не имеющее собственного ответа
            /// </summary>
            void Success() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
            }
            
            /// <summary> 
            /// Сообщение TimeOut. Рассылается машинами состояний в случае превышения допустимого интервала нахождения в определенном состоянии.
            /// </summary>
            void TimeOut() const
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TimeOut);
            }
            
            /// <summary> 
            /// Неожиданное поведение функции-обработчика
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата в котором случилась ошибка</param>
            /// <param name="message">- Отправляемое сообщение (вложенный контейнер)</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void UnexpectedBehaviour(int event, const string & machineName, message message, const string & newState, const string & oldState) const
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
          END_WRAPPER();
          
          BEGIN_IMPLEMENTATION()
            /// <summary> 
            /// Отправка события Activate по адресу
            /// </summary>
            /// <param name="properties">- Свойства объекта</param>
            void SendActivate(address target, const VariantVector & properties)
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события Activate самому себе
            /// </summary>
            /// <param name="properties">- Свойства объекта</param>
            void RaiseActivate(const VariantVector & properties)
            {
              G1::Activate cmd;
              cmd.SetProperties(properties);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события ActivateAnswer по адресу
            /// </summary>
            /// <param name="message">- Детальное описание в случае неудачи</param>
            /// <param name="result">- Результат (удалось ли активироваться)</param>
            void SendActivateAnswer(address target, const string & message = "", bool result = true)
            {
              G1::ActivateAnswer cmd;
              cmd.SetMessage(message);
              cmd.SetResult(result);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события ActivateAnswer самому себе
            /// </summary>
            /// <param name="message">- Детальное описание в случае неудачи</param>
            /// <param name="result">- Результат (удалось ли активироваться)</param>
            void RaiseActivateAnswer(const string & message = "", bool result = true)
            {
              G1::ActivateAnswer cmd;
              cmd.SetMessage(message);
              cmd.SetResult(result);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события CommonError по адресу
            /// </summary>
            /// <param name="error">- Объект, идентифицирующий проблему</param>
            void SendCommonError(address target, CommonErrors error)
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события CommonError самому себе
            /// </summary>
            /// <param name="error">- Объект, идентифицирующий проблему</param>
            void RaiseCommonError(CommonErrors error)
            {
              G1::CommonError cmd;
              cmd.SetError(error);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события CreateInstanceAllowed по адресу
            /// </summary>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void SendCreateInstanceAllowed(address target, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события CreateInstanceAllowed самому себе
            /// </summary>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void RaiseCreateInstanceAllowed(int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceAllowed cmd;
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события CreateInstanceIntercepted по адресу
            /// </summary>
            /// <param name="interceptor">- Перехватчик</param>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void SendCreateInstanceIntercepted(address target, const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события CreateInstanceIntercepted самому себе
            /// </summary>
            /// <param name="interceptor">- Перехватчик</param>
            /// <param name="moduleGeneration">- Требуемое поколение модуля (0 - любое)</param>
            /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
            /// <param name="moduleType">- Тип модуля для создания</param>
            void RaiseCreateInstanceIntercepted(const string & interceptor, int moduleGeneration, const string & moduleId, const string & moduleType)
            {
              G1::CreateInstanceIntercepted cmd;
              cmd.SetInterceptor(interceptor);
              cmd.SetModuleGeneration(moduleGeneration);
              cmd.SetModuleId(moduleId);
              cmd.SetModuleType(moduleType);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события GenerationNotSupported по адресу
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="messageGeneration">- Поколение, которое не поддерживается</param>
            void SendGenerationNotSupported(address target, int eventKind, int messageGeneration)
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события GenerationNotSupported самому себе
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="messageGeneration">- Поколение, которое не поддерживается</param>
            void RaiseGenerationNotSupported(int eventKind, int messageGeneration)
            {
              G1::GenerationNotSupported cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetMessageGeneration(messageGeneration);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события GetModulePlatform по адресу
            /// </summary>
            void SendGetModulePlatform(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::GetModulePlatform);
            }
            /// <summary> 
            /// Отправка события GetModulePlatform самому себе
            /// </summary>
            void RaiseGetModulePlatform()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::GetModulePlatform);
            }
            
            /// <summary> 
            /// Отправка события GetModulePlatformAnswer по адресу
            /// </summary>
            /// <param name="platform">- Платформа, на которой запущен модуль, отправляющий ответ</param>
            void SendGetModulePlatformAnswer(address target, Platforms platform)
            {
              G1::GetModulePlatformAnswer cmd;
              cmd.SetPlatform(platform);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события GetModulePlatformAnswer самому себе
            /// </summary>
            /// <param name="platform">- Платформа, на которой запущен модуль, отправляющий ответ</param>
            void RaiseGetModulePlatformAnswer(Platforms platform)
            {
              G1::GetModulePlatformAnswer cmd;
              cmd.SetPlatform(platform);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события HandlerError по адресу
            /// </summary>
            /// <param name="kind">- Тип ошибки</param>
            /// <param name="message">- Детальное описание ошибки</param>
            void SendHandlerError(address target, HandlerErrors kind, const string & message)
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события HandlerError самому себе
            /// </summary>
            /// <param name="kind">- Тип ошибки</param>
            /// <param name="message">- Детальное описание ошибки</param>
            void RaiseHandlerError(HandlerErrors kind, const string & message)
            {
              G1::HandlerError cmd;
              cmd.SetKind(kind);
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события InterceptedMessage по адресу
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void SendInterceptedMessage(address target, message message)
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события InterceptedMessage самому себе
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void RaiseInterceptedMessage(message message)
            {
              G1::InterceptedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события MatchError по адресу
            /// </summary>
            void SendMatchError(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::MatchError);
            }
            /// <summary> 
            /// Отправка события MatchError самому себе
            /// </summary>
            void RaiseMatchError()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::MatchError);
            }
            
            /// <summary> 
            /// Отправка события ModuleFailedOnEvent по адресу
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="exceptionKind">- Тип ошибки (исключения)</param>
            /// <param name="exceptionMessage">- Сообщение об ошибки</param>
            void SendModuleFailedOnEvent(address target, int eventKind, const string & exceptionKind, const string & exceptionMessage)
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события ModuleFailedOnEvent самому себе
            /// </summary>
            /// <param name="eventKind">- Тип, события, при реакции на которое произошла ошибка</param>
            /// <param name="exceptionKind">- Тип ошибки (исключения)</param>
            /// <param name="exceptionMessage">- Сообщение об ошибки</param>
            void RaiseModuleFailedOnEvent(int eventKind, const string & exceptionKind, const string & exceptionMessage)
            {
              G1::ModuleFailedOnEvent cmd;
              cmd.SetEventKind(eventKind);
              cmd.SetExceptionKind(exceptionKind);
              cmd.SetExceptionMessage(exceptionMessage);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события OverHearedMessage по адресу
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void SendOverHearedMessage(address target, message message)
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события OverHearedMessage самому себе
            /// </summary>
            /// <param name="message">- Перехваченное сообщение (вложенный контейнер)</param>
            void RaiseOverHearedMessage(message message)
            {
              G1::OverHearedMessage cmd;
              cmd.SetMessage(message);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события ResetWait по адресу
            /// </summary>
            void SendResetWait(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::ResetWait, 1, 2147483640); 
            }
            /// <summary> 
            /// Отправка события ResetWait самому себе
            /// </summary>
            void RaiseResetWait()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ResetWait, 1, 2147483640); 
            }
            
            /// <summary> 
            /// Отправка события Shift по адресу
            /// </summary>
            void SendShift(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Shift, 1, 2147483640); 
            }
            /// <summary> 
            /// Отправка события Shift самому себе
            /// </summary>
            void RaiseShift()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shift, 1, 2147483640); 
            }
            
            /// <summary> 
            /// Отправка события Start по адресу
            /// </summary>
            void SendStart(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Start);
            }
            /// <summary> 
            /// Отправка события Start самому себе
            /// </summary>
            void RaiseStart()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
            }
            
            /// <summary> 
            /// Отправка события StateAttributeChanged по адресу
            /// </summary>
            /// <param name="attributeName">- Имя изменившегося атрибута (Как минимум TimeOut)</param>
            /// <param name="attributeNewValue">- Новое значение атрибута</param>
            /// <param name="attributeOldValue">- Старое значение атрибута</param>
            /// <param name="moduleId">- Идентификатор модуля в машине которого изменился атрибут состояния</param>
            void SendStateAttributeChanged(address target, const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId)
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события StateAttributeChanged самому себе
            /// </summary>
            /// <param name="attributeName">- Имя изменившегося атрибута (Как минимум TimeOut)</param>
            /// <param name="attributeNewValue">- Новое значение атрибута</param>
            /// <param name="attributeOldValue">- Старое значение атрибута</param>
            /// <param name="moduleId">- Идентификатор модуля в машине которого изменился атрибут состояния</param>
            void RaiseStateAttributeChanged(const string & attributeName, variant attributeNewValue, variant attributeOldValue, const string & moduleId)
            {
              G1::StateAttributeChanged cmd;
              cmd.SetAttributeName(attributeName);
              cmd.SetAttributeNewValue(attributeNewValue);
              cmd.SetAttributeOldValue(attributeOldValue);
              cmd.SetModuleId(moduleId);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события StateChanged по адресу
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата перешедшего в новое состояние</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void SendStateChanged(address target, int event, const string & machineName, const string & newState, const string & oldState)
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события StateChanged самому себе
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата перешедшего в новое состояние</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void RaiseStateChanged(int event, const string & machineName, const string & newState, const string & oldState)
            {
              G1::StateChanged cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
            /// <summary> 
            /// Отправка события Stop по адресу
            /// </summary>
            void SendStop(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Stop);
            }
            /// <summary> 
            /// Отправка события Stop самому себе
            /// </summary>
            void RaiseStop()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Stop);
            }
            
            /// <summary> 
            /// Отправка события Success по адресу
            /// </summary>
            void SendSuccess(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::Success);
            }
            /// <summary> 
            /// Отправка события Success самому себе
            /// </summary>
            void RaiseSuccess()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
            }
            
            /// <summary> 
            /// Отправка события TimeOut по адресу
            /// </summary>
            void SendTimeOut(address target)
            {
              m_RequestDispatcher->SendEvent(target, G1::Codes::TimeOut);
            }
            /// <summary> 
            /// Отправка события TimeOut самому себе
            /// </summary>
            void RaiseTimeOut()
            {
              m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TimeOut);
            }
            
            /// <summary> 
            /// Отправка события UnexpectedBehaviour по адресу
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата в котором случилась ошибка</param>
            /// <param name="message">- Отправляемое сообщение (вложенный контейнер)</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void SendUnexpectedBehaviour(address target, int event, const string & machineName, message message, const string & newState, const string & oldState)
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(target, cmd);
            }
            /// <summary> 
            /// Отправка события UnexpectedBehaviour самому себе
            /// </summary>
            /// <param name="event">- Событие, активировавшее переход</param>
            /// <param name="machineName">- Имя конечного автомата в котором случилась ошибка</param>
            /// <param name="message">- Отправляемое сообщение (вложенный контейнер)</param>
            /// <param name="newState">- Новое состояние машины</param>
            /// <param name="oldState">- Старое состояние машины</param>
            void RaiseUnexpectedBehaviour(int event, const string & machineName, message message, const string & newState, const string & oldState)
            {
              G1::UnexpectedBehaviour cmd;
              cmd.SetEvent(event);
              cmd.SetMachineName(machineName);
              cmd.SetMessage(message);
              cmd.SetNewState(newState);
              cmd.SetOldState(oldState);
              m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
            }
            
          END_IMPLEMENTATION();
          
          #pragma endregion
        END_PROTOCOL()
        
        } // пространство имен Protocol
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
