// Uniteller.Framework.Kernel.Tester

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
      namespace Tester
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(2, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// Ошибки перехватчика
            /// </summary>
            enum class InterceptorErrors
            {
              AlreadyConnected = 1, // - Уже подключены к данному модулю
              CouldNotConnect = 2, // - Не удалось подключиться к модулю
              CouldNotDisconnect = 3, // - Не удалось отключиться к модулю
              TimeOut = 4, // - Перехваченная функция была разблокирована по таймауту
              UnexpectedAnswer = 5, // - Пришел неверный ответ
              UnexpectedEvent = 6 // - Пришло неожиданное событие
            };
            
            /// <summary> 
            /// Режим перехвата функции platform-api
            /// </summary>
            enum class PlatformInterceptMode
            {
              Fail = 1, // - Падать при вызове данной api-функции (возвращение заведомо оговоренной фатальной ошибки вызывающему коду)
              Intercept = 2, // - Перехватить и обернуть сообщениями
              None = 3 // - Не перехватывать вызов функции и бесшовно передавать вызов платформе
            };
            
            /// <summary> 
            /// Коды ошибок средства тестирования
            /// </summary>
            enum class TesterErrors
            {
              AddressAlreadyExists = 40, // - Неверный адрес для перехвата (уже существует на шине)
              AddressToObserveNotFound = 28, // - Адрес для прослушивания не найден (в режимах observe, observeoutput)
              BadConstraints = 24, // - Логическая ошибка в ограничениях на таймер в конструкции CheckTimer (пересечение интервалов Fail/Pass)
              CommandFormatError = 12, // - Ошибка формата команды
              CommandLineError = 16, // - Ошибка формата командной строки
              CommandNotSupported = 10, // - Команда не поддерживается
              CouldNotConnectInterceptor = 46, // - Не удалось подключить интерцептор к модулю
              CouldNotDisconnectInterceptor = 47, // - Не удалось отключить интерцептор от модуля
              DataFileFormatError = 54, // - В файле данных ошибка формата определения данных
              DataFileNotFound = 53, // - Отсутствует файл данных
              DatasetFormatError = 56, // - Неверный формат набора данных
              DatasetHasWrongLink = 52, // - В файле данных не найден указанный ключ
              DatasetNotFound = 55, // - Набор данных не найден в скрипте
              EvalStackOverflow = 57, // - Число рекурсивных вызовов, выполненных для вычисления выражения, превысило допустимые лимиты
              EventNotFound = 4, // - событие не найдено в репозитории,
              ExpectedEventNotOccured = 9, // - Ожидаемое событие не пришло. Тайм-аут.
              ExtraParameterInCall = 42, // - При вызове процедуры переданы лишние параметры
              FatalError = 17, // - Разрушительная ошибка
              IncorrectArgumentsLength = 6, // - не совпало количество параметров (если включен Strict),
              IncorrectArrayIndex = 50, // - Индекс массива неверен
              IncorrectEventInFilter = 34, // - Неверное событие в фильтре (Intercept, Observe, EmulateMQ)
              IncorrectFormatInFilter = 36, // - Неверный формат фильтра (Intercept, Observe, EmulateMQ)
              IncorrectMachineState = 14, // - Неверное состояние машины
              IncorrectModeInFilter = 35, // - Неверный режим фильтра (Intercept, Observe, EmulateMQ)
              IncorrectVariableName = 27, // - Ошибочное значение имени переменной
              IndexOutOfRange = 49, // - Индекс массива вышел за допустимые границы
              InputFileError = 2, // - ошибка работы с файлом,
              InterceptorAlreadyConnected = 45, // - Уже подключены к данному модулю
              InvalidArgumentType = 30, // - Попытка передать неверный тип аргумента
              InvalidConstraint = 22, // - Неверный тип ограничения в конструкции CheckTimer
              InvalidConstraintValue = 23, // - Неверное значение ограничения в конструкции CheckTimer
              InvalidDateTimeFormat = 51, // - Неверный формат даты/времени
              InvalidEmulateMqMode = 43, // - Неверный режим в конструкции Emulate
              InvalidEmulateMqOptions = 33, // - Ошибочные параметры в конструкции EmulateMQ
              InvalidFlag = 25, // - Неизвестный флаг (в конструкциях IsSet, IsNotSet)
              InvalidMask = 29, // - Неверная маска (неизвестное значение флага)
              InvalidProcedure = 59, // - Ошибка в теле процедуры (выходной параметр не присваивается)
              InvalidProcedureCall = 41, // - Неверный вызов процедуры (не все параметры переданы)
              InvalidSource = 31, // - Ошибочный источник сообщения (в команде Receive)
              InvalidStringValue = 32, // - Ошибочный формат строковой контсанты или выражение не преобразуемое к строке в инструкции Concat
              InvalidTimerDirective = 20, // - Ошибочная директива в конструкции CheckTimer (не Fail, Pass и не Kill).
              MessageToReceiveNeeded = 44, // - Требуется как минимум одно сообщение для приема в ReceiveAsync
              ModuleNotLoaded = 15, // - Необходимый модуль загрузить не удалось
              NotInterceptor = 48, // - Попытка использовать в качестве интерцептора не интерцептор
              ProcedureCallConflict = 60, // - При вызове процедуры в одну и туже переменную помещается более чем один out параметр
              ProtocolIncompatibility = 1, // - Несовместимость протоколов
              RegExpFormatError = 37, // - Ошибка формата регулярного выражения
              Success = 0, // - Успех
              TimerAlreadyDefined = 18, // - Таймер с таким именем уже определен.
              UndefinedTimer = 19, // - Таймер не определен
              UnexpectedEvent = 5, // - не совпало имя события,
              UnexpectedEventSource = 11, // - Получено сообщение не от того модуля, от которого мы ждали сообщение
              UnexpectedModuleAddress = 13, // - Не удалось распознать адрес модуля
              UnexpectedTimerValue = 21, // - Значение таймера вышло за установленные границы. Прерывание из-за нарушения условия скорости выполнения.
              UnexpectedValue = 7, // - не совпало содержимое параметров,
              UnknownParamIndex = 8, // - Не найден параметр в сообщении
              UsingVariableNameAsTimer = 26, // - Попытка использовать имя переменной в качестве имени таймера
              VariableNeededForOutArgument = 58, // - Для хранения значения выходного параметра процедуры требуется имя переменной
              WrongParameterDefinition = 38, // - Неверное определение параметра процедуры
              WrongProcedureDefinition = 39, // - Ошибочное объявление процедуры
              WrongUtxFormat = 3 // - ошибка формата UTX,
            };
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа InterceptorErrors
            /// </summary>
            inline bool IsValidInterceptorErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 7));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу InterceptorErrors
            /// </summary>
            inline InterceptorErrors ConvertToInterceptorErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return InterceptorErrors::AlreadyConnected;
                case 2:
                  return InterceptorErrors::CouldNotConnect;
                case 3:
                  return InterceptorErrors::CouldNotDisconnect;
                case 4:
                  return InterceptorErrors::TimeOut;
                case 5:
                  return InterceptorErrors::UnexpectedAnswer;
                case 6:
                  return InterceptorErrors::UnexpectedEvent;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу InterceptorErrors", value);
                }
            }
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа PlatformInterceptMode
            /// </summary>
            inline bool IsValidPlatformInterceptModeValue(const int value)
            {
              return ((value >= 1)&&(value < 4));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу PlatformInterceptMode
            /// </summary>
            inline PlatformInterceptMode ConvertToPlatformInterceptMode(const int value)
            {
              switch (value)
              {
                case 1:
                  return PlatformInterceptMode::Fail;
                case 2:
                  return PlatformInterceptMode::Intercept;
                case 3:
                  return PlatformInterceptMode::None;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу PlatformInterceptMode", value);
                }
            }
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа TesterErrors
            /// </summary>
            inline bool IsValidTesterErrorsValue(const int value)
            {
              return ((value >= 0)&&(value < 61));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу TesterErrors
            /// </summary>
            inline TesterErrors ConvertToTesterErrors(const int value)
            {
              switch (value)
              {
                case 40:
                  return TesterErrors::AddressAlreadyExists;
                case 28:
                  return TesterErrors::AddressToObserveNotFound;
                case 24:
                  return TesterErrors::BadConstraints;
                case 12:
                  return TesterErrors::CommandFormatError;
                case 16:
                  return TesterErrors::CommandLineError;
                case 10:
                  return TesterErrors::CommandNotSupported;
                case 46:
                  return TesterErrors::CouldNotConnectInterceptor;
                case 47:
                  return TesterErrors::CouldNotDisconnectInterceptor;
                case 54:
                  return TesterErrors::DataFileFormatError;
                case 53:
                  return TesterErrors::DataFileNotFound;
                case 56:
                  return TesterErrors::DatasetFormatError;
                case 52:
                  return TesterErrors::DatasetHasWrongLink;
                case 55:
                  return TesterErrors::DatasetNotFound;
                case 57:
                  return TesterErrors::EvalStackOverflow;
                case 4:
                  return TesterErrors::EventNotFound;
                case 9:
                  return TesterErrors::ExpectedEventNotOccured;
                case 42:
                  return TesterErrors::ExtraParameterInCall;
                case 17:
                  return TesterErrors::FatalError;
                case 6:
                  return TesterErrors::IncorrectArgumentsLength;
                case 50:
                  return TesterErrors::IncorrectArrayIndex;
                case 34:
                  return TesterErrors::IncorrectEventInFilter;
                case 36:
                  return TesterErrors::IncorrectFormatInFilter;
                case 14:
                  return TesterErrors::IncorrectMachineState;
                case 35:
                  return TesterErrors::IncorrectModeInFilter;
                case 27:
                  return TesterErrors::IncorrectVariableName;
                case 49:
                  return TesterErrors::IndexOutOfRange;
                case 2:
                  return TesterErrors::InputFileError;
                case 45:
                  return TesterErrors::InterceptorAlreadyConnected;
                case 30:
                  return TesterErrors::InvalidArgumentType;
                case 22:
                  return TesterErrors::InvalidConstraint;
                case 23:
                  return TesterErrors::InvalidConstraintValue;
                case 51:
                  return TesterErrors::InvalidDateTimeFormat;
                case 43:
                  return TesterErrors::InvalidEmulateMqMode;
                case 33:
                  return TesterErrors::InvalidEmulateMqOptions;
                case 25:
                  return TesterErrors::InvalidFlag;
                case 29:
                  return TesterErrors::InvalidMask;
                case 59:
                  return TesterErrors::InvalidProcedure;
                case 41:
                  return TesterErrors::InvalidProcedureCall;
                case 31:
                  return TesterErrors::InvalidSource;
                case 32:
                  return TesterErrors::InvalidStringValue;
                case 20:
                  return TesterErrors::InvalidTimerDirective;
                case 44:
                  return TesterErrors::MessageToReceiveNeeded;
                case 15:
                  return TesterErrors::ModuleNotLoaded;
                case 48:
                  return TesterErrors::NotInterceptor;
                case 60:
                  return TesterErrors::ProcedureCallConflict;
                case 1:
                  return TesterErrors::ProtocolIncompatibility;
                case 37:
                  return TesterErrors::RegExpFormatError;
                case 0:
                  return TesterErrors::Success;
                case 18:
                  return TesterErrors::TimerAlreadyDefined;
                case 19:
                  return TesterErrors::UndefinedTimer;
                case 5:
                  return TesterErrors::UnexpectedEvent;
                case 11:
                  return TesterErrors::UnexpectedEventSource;
                case 13:
                  return TesterErrors::UnexpectedModuleAddress;
                case 21:
                  return TesterErrors::UnexpectedTimerValue;
                case 7:
                  return TesterErrors::UnexpectedValue;
                case 8:
                  return TesterErrors::UnknownParamIndex;
                case 26:
                  return TesterErrors::UsingVariableNameAsTimer;
                case 58:
                  return TesterErrors::VariableNeededForOutArgument;
                case 38:
                  return TesterErrors::WrongParameterDefinition;
                case 39:
                  return TesterErrors::WrongProcedureDefinition;
                case 3:
                  return TesterErrors::WrongUtxFormat;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу TesterErrors", value);
                }
            }
            
            #pragma endregion
            
            //Структуры
            #pragma region Messages and wrappers
            
            //Сообщения
            // Проверка значения таймера
            BEGIN_MESSAGE(CheckTimer,11,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CheckTimer

            // Событие Compatible. Положительный результат инициализации КА и проверки совместимости протокола КА и микроядра, заявленного протокола скрипта и тестируемого модуля.
            BEGIN_MESSAGE(Compatible,1,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Compatible

            // Событие EndOfFile. Означает конец файла при попытке прочитать новый ключ.
            BEGIN_MESSAGE(EndOfFile,2,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // EndOfFile

            // Ошибка системы автоматического тестирования. В большинстве случаев - либо ошибка сравнения ожидаемого и заданного события, либо ошибка скрипта.
            BEGIN_MESSAGE(Fail,5,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Причина ошибки -1 - ошибка машины
              ENUM(0, TesterErrors, Result);
            END_MESSAGE(); // Fail

            // Подает команду перехватчику вызовов функций api платформы подключиться к определенному модулю
            BEGIN_MESSAGE(InstallInterceptor,15,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Модуль в который будет осуществлена инъекция перехватчиков вызовов функций api платформы
              ARGUMENT(0, string, Module);
            END_MESSAGE(); // InstallInterceptor

            // Результат подключения интерцептора к модулю
            BEGIN_MESSAGE(InstallInterceptorAnswer,21,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // - Подключился ли интерцептор
              ARGUMENT(0, bool, Installed);
              // - Модуль
              ARGUMENT(1, string, Module);
            END_MESSAGE(); // InstallInterceptorAnswer

            // Отправляется в момент получения в скрипте команды перехвата входящих сообщений для некоторого модуля (Intercept)
            BEGIN_MESSAGE(Intercept,12,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Intercept

            // Произошел перехват вызова API
            BEGIN_MESSAGE(Intercepted,18,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Имя перехваченного метода
              ARGUMENT(0, string, MethodName);
            END_MESSAGE(); // Intercepted

            // Отправляется в момент падения модуля-интерцептора
            BEGIN_MESSAGE(InterceptorFailed,20,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMessage("");
              }
              // - Описание ошибки
              ARGUMENT(0, string, Message);
              // - Причина ошибки
              ENUM(1, InterceptorErrors, Reason);
            END_MESSAGE(); // InterceptorFailed

            // Интерцептор подключен
            BEGIN_MESSAGE(InterceptorInstalled,24,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // InterceptorInstalled

            // Интерцептор отключен
            BEGIN_MESSAGE(InterceptorUninstalled,23,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // InterceptorUninstalled

            // Отправляется в момент получения в скрипте команды включения подписки входящих сообщений для некоторого модуля (Observe)
            BEGIN_MESSAGE(Observe,13,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Observe

            // Отправляется в момент получения в скрипте команды перехвата исходящих сообщений для некоторого модуля (ObserveOutput)
            BEGIN_MESSAGE(ObserveOutput,14,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ObserveOutput

            // Отправляется в момент получения в скрипте команды  Receive. Прочитан ключ, требующий получения события с соответствующими параметрами.
            BEGIN_MESSAGE(Receive,4,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Receive

            // Отправляется в момент получения в скрипте команды асинхронного приема нескольких сообщений
            BEGIN_MESSAGE(ReceiveAsync,19,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ReceiveAsync

            // Интеграция процедур в скрипт тестирования выполнена
            BEGIN_MESSAGE(ScriptUpdated,9,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ScriptUpdated

            // Отправляется в момент получения в скрипте команды Send. Прочитан ключ, требующий отправки события с соответствующими параметрами.
            BEGIN_MESSAGE(Send,3,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Send

            // Позволяет устновить режим перехвата отдельной функции
            BEGIN_MESSAGE(SetFunctionInterceptMode,17,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Имя функции PlatformApi для которой устанавливается режим перехвата
              ARGUMENT(0, string, Function);
              // Режим перехвата функции
              ENUM(1, PlatformInterceptMode, Mode);
            END_MESSAGE(); // SetFunctionInterceptMode

            // Пропустить несколько сообщений
            BEGIN_MESSAGE(Skip,8,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Skip

            // Сообщение пропущено
            BEGIN_MESSAGE(Skipped,7,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Skipped

            // Начать отсчет таймера
            BEGIN_MESSAGE(StartTimer,10,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // StartTimer

            // Событие Success. Успешное сравнение ожидаемого и заданного события.
            BEGIN_MESSAGE(Success,6,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Success

            // Подает команду перехватчику вызовов функций api платформы отключиться от определенного модуля
            BEGIN_MESSAGE(UninstallInterceptor,16,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Модуль в который будет отключена инъекция перехватчиков вызовов функций api платформы
              ARGUMENT(0, string, Module);
            END_MESSAGE(); // UninstallInterceptor

            // Результат отключения интерцептора от модуля
            BEGIN_MESSAGE(UninstallInterceptorAnswer,22,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // - Отключено или нет
              ARGUMENT(0, bool, Uninstalled);
            END_MESSAGE(); // UninstallInterceptorAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Проверка значения таймера
              /// </summary>
              void CheckTimer() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CheckTimer);
              }
              
              /// <summary> 
              /// Событие Compatible. Положительный результат инициализации КА и проверки совместимости протокола КА и микроядра, заявленного протокола скрипта и тестируемого модуля.
              /// </summary>
              void Compatible() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Compatible);
              }
              
              /// <summary> 
              /// Событие EndOfFile. Означает конец файла при попытке прочитать новый ключ.
              /// </summary>
              void EndOfFile() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::EndOfFile);
              }
              
              /// <summary> 
              /// Ошибка системы автоматического тестирования. В большинстве случаев - либо ошибка сравнения ожидаемого и заданного события, либо ошибка скрипта.
              /// </summary>
              /// <param name="result">Причина ошибки -1 - ошибка машины,</param>
              void Fail(TesterErrors result) const
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Подает команду перехватчику вызовов функций api платформы подключиться к определенному модулю
              /// </summary>
              /// <param name="module">Модуль, в который будет осуществлена инъекция перехватчиков вызовов функций api платформы</param>
              void InstallInterceptor(const string & module) const
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды перехвата входящих сообщений для некоторого модуля (Intercept)
              /// </summary>
              void Intercept() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Intercept);
              }
              
              /// <summary> 
              /// Произошел перехват вызова API
              /// </summary>
              /// <param name="methodName">Имя перехваченного метода</param>
              void Intercepted(const string & methodName) const
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправляется в момент падения модуля-интерцептора
              /// </summary>
              /// <param name="reason">- Причина ошибки</param>
              /// <param name="Message">- Описание ошибки</param>
              void InterceptorFailed(InterceptorErrors reason, string message = "") const
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Интерцептор подключен
              /// </summary>
              void InterceptorInstalled() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorInstalled);
              }
              
              /// <summary> 
              /// Интерцептор отключен
              /// </summary>
              void InterceptorUninstalled() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorUninstalled);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды включения подписки входящих сообщений для некоторого модуля (Observe)
              /// </summary>
              void Observe() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Observe);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды перехвата исходящих сообщений для некоторого модуля (ObserveOutput)
              /// </summary>
              void ObserveOutput() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ObserveOutput);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды  Receive. Прочитан ключ, требующий получения события с соответствующими параметрами.
              /// </summary>
              void Receive() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Receive);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды асинхронного приема нескольких сообщений
              /// </summary>
              void ReceiveAsync() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ReceiveAsync);
              }
              
              /// <summary> 
              /// Интеграция процедур в скрипт тестирования выполнена
              /// </summary>
              void ScriptUpdated() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ScriptUpdated);
              }
              
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды Send. Прочитан ключ, требующий отправки события с соответствующими параметрами.
              /// </summary>
              void Send() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Send);
              }
              
              /// <summary> 
              /// Позволяет устновить режим перехвата отдельной функции
              /// </summary>
              /// <param name="function">Имя функции PlatformApi, для которой устанавливается режим перехвата</param>
              /// <param name="mode">Режим перехвата функции</param>
              void SetFunctionInterceptMode(const string & function, PlatformInterceptMode mode) const
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Пропустить несколько сообщений
              /// </summary>
              void Skip() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skip);
              }
              
              /// <summary> 
              /// Сообщение пропущено
              /// </summary>
              void Skipped() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skipped);
              }
              
              /// <summary> 
              /// Начать отсчет таймера
              /// </summary>
              void StartTimer() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::StartTimer);
              }
              
              /// <summary> 
              /// Событие Success. Успешное сравнение ожидаемого и заданного события.
              /// </summary>
              void Success() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
              }
              
              /// <summary> 
              /// Подает команду перехватчику вызовов функций api платформы отключиться от определенного модуля
              /// </summary>
              /// <param name="module">Модуль, в который будет отключена инъекция перехватчиков вызовов функций api платформы</param>
              void UninstallInterceptor(const string & module) const
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события CheckTimer по адресу
              /// </summary>
              void SendCheckTimer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::CheckTimer);
              }
              /// <summary> 
              /// Отправка события CheckTimer самому себе
              /// </summary>
              void RaiseCheckTimer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CheckTimer);
              }
              
              /// <summary> 
              /// Отправка события Compatible по адресу
              /// </summary>
              void SendCompatible(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Compatible);
              }
              /// <summary> 
              /// Отправка события Compatible самому себе
              /// </summary>
              void RaiseCompatible()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Compatible);
              }
              
              /// <summary> 
              /// Отправка события EndOfFile по адресу
              /// </summary>
              void SendEndOfFile(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::EndOfFile);
              }
              /// <summary> 
              /// Отправка события EndOfFile самому себе
              /// </summary>
              void RaiseEndOfFile()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::EndOfFile);
              }
              
              /// <summary> 
              /// Отправка события Fail по адресу
              /// </summary>
              /// <param name="result">Причина ошибки -1 - ошибка машины,</param>
              void SendFail(address target, TesterErrors result)
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Fail самому себе
              /// </summary>
              /// <param name="result">Причина ошибки -1 - ошибка машины,</param>
              void RaiseFail(TesterErrors result)
              {
                G1::Fail cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события InstallInterceptor по адресу
              /// </summary>
              /// <param name="module">Модуль, в который будет осуществлена инъекция перехватчиков вызовов функций api платформы</param>
              void SendInstallInterceptor(address target, const string & module)
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события InstallInterceptor самому себе
              /// </summary>
              /// <param name="module">Модуль, в который будет осуществлена инъекция перехватчиков вызовов функций api платформы</param>
              void RaiseInstallInterceptor(const string & module)
              {
                G1::InstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события InstallInterceptorAnswer по адресу
              /// </summary>
              /// <param name="installed">- Подключился ли интерцептор</param>
              /// <param name="module">- Модуль</param>
              void SendInstallInterceptorAnswer(address target, bool installed, const string & module)
              {
                G1::InstallInterceptorAnswer cmd;
                cmd.SetInstalled(installed);
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события InstallInterceptorAnswer самому себе
              /// </summary>
              /// <param name="installed">- Подключился ли интерцептор</param>
              /// <param name="module">- Модуль</param>
              void RaiseInstallInterceptorAnswer(bool installed, const string & module)
              {
                G1::InstallInterceptorAnswer cmd;
                cmd.SetInstalled(installed);
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Intercept по адресу
              /// </summary>
              void SendIntercept(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Intercept);
              }
              /// <summary> 
              /// Отправка события Intercept самому себе
              /// </summary>
              void RaiseIntercept()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Intercept);
              }
              
              /// <summary> 
              /// Отправка события Intercepted по адресу
              /// </summary>
              /// <param name="methodName">Имя перехваченного метода</param>
              void SendIntercepted(address target, const string & methodName)
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Intercepted самому себе
              /// </summary>
              /// <param name="methodName">Имя перехваченного метода</param>
              void RaiseIntercepted(const string & methodName)
              {
                G1::Intercepted cmd;
                cmd.SetMethodName(methodName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события InterceptorFailed по адресу
              /// </summary>
              /// <param name="reason">- Причина ошибки</param>
              /// <param name="message">- Описание ошибки</param>
              void SendInterceptorFailed(address target, InterceptorErrors reason, const string & message = "")
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события InterceptorFailed самому себе
              /// </summary>
              /// <param name="reason">- Причина ошибки</param>
              /// <param name="message">- Описание ошибки</param>
              void RaiseInterceptorFailed(InterceptorErrors reason, const string & message = "")
              {
                G1::InterceptorFailed cmd;
                cmd.SetMessage(message);
                cmd.SetReason(reason);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события InterceptorInstalled по адресу
              /// </summary>
              void SendInterceptorInstalled(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::InterceptorInstalled);
              }
              /// <summary> 
              /// Отправка события InterceptorInstalled самому себе
              /// </summary>
              void RaiseInterceptorInstalled()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorInstalled);
              }
              
              /// <summary> 
              /// Отправка события InterceptorUninstalled по адресу
              /// </summary>
              void SendInterceptorUninstalled(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::InterceptorUninstalled);
              }
              /// <summary> 
              /// Отправка события InterceptorUninstalled самому себе
              /// </summary>
              void RaiseInterceptorUninstalled()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InterceptorUninstalled);
              }
              
              /// <summary> 
              /// Отправка события Observe по адресу
              /// </summary>
              void SendObserve(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Observe);
              }
              /// <summary> 
              /// Отправка события Observe самому себе
              /// </summary>
              void RaiseObserve()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Observe);
              }
              
              /// <summary> 
              /// Отправка события ObserveOutput по адресу
              /// </summary>
              void SendObserveOutput(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ObserveOutput);
              }
              /// <summary> 
              /// Отправка события ObserveOutput самому себе
              /// </summary>
              void RaiseObserveOutput()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ObserveOutput);
              }
              
              /// <summary> 
              /// Отправка события Receive по адресу
              /// </summary>
              void SendReceive(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Receive);
              }
              /// <summary> 
              /// Отправка события Receive самому себе
              /// </summary>
              void RaiseReceive()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Receive);
              }
              
              /// <summary> 
              /// Отправка события ReceiveAsync по адресу
              /// </summary>
              void SendReceiveAsync(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ReceiveAsync);
              }
              /// <summary> 
              /// Отправка события ReceiveAsync самому себе
              /// </summary>
              void RaiseReceiveAsync()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ReceiveAsync);
              }
              
              /// <summary> 
              /// Отправка события ScriptUpdated по адресу
              /// </summary>
              void SendScriptUpdated(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::ScriptUpdated);
              }
              /// <summary> 
              /// Отправка события ScriptUpdated самому себе
              /// </summary>
              void RaiseScriptUpdated()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ScriptUpdated);
              }
              
              /// <summary> 
              /// Отправка события Send по адресу
              /// </summary>
              void SendSend(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Send);
              }
              /// <summary> 
              /// Отправка события Send самому себе
              /// </summary>
              void RaiseSend()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Send);
              }
              
              /// <summary> 
              /// Отправка события SetFunctionInterceptMode по адресу
              /// </summary>
              /// <param name="function">Имя функции PlatformApi, для которой устанавливается режим перехвата</param>
              /// <param name="mode">Режим перехвата функции</param>
              void SendSetFunctionInterceptMode(address target, const string & function, PlatformInterceptMode mode)
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события SetFunctionInterceptMode самому себе
              /// </summary>
              /// <param name="function">Имя функции PlatformApi, для которой устанавливается режим перехвата</param>
              /// <param name="mode">Режим перехвата функции</param>
              void RaiseSetFunctionInterceptMode(const string & function, PlatformInterceptMode mode)
              {
                G1::SetFunctionInterceptMode cmd;
                cmd.SetFunction(function);
                cmd.SetMode(mode);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Skip по адресу
              /// </summary>
              void SendSkip(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Skip);
              }
              /// <summary> 
              /// Отправка события Skip самому себе
              /// </summary>
              void RaiseSkip()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skip);
              }
              
              /// <summary> 
              /// Отправка события Skipped по адресу
              /// </summary>
              void SendSkipped(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::Skipped);
              }
              /// <summary> 
              /// Отправка события Skipped самому себе
              /// </summary>
              void RaiseSkipped()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Skipped);
              }
              
              /// <summary> 
              /// Отправка события StartTimer по адресу
              /// </summary>
              void SendStartTimer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G1::Codes::StartTimer);
              }
              /// <summary> 
              /// Отправка события StartTimer самому себе
              /// </summary>
              void RaiseStartTimer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::StartTimer);
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
              /// Отправка события UninstallInterceptor по адресу
              /// </summary>
              /// <param name="module">Модуль, в который будет отключена инъекция перехватчиков вызовов функций api платформы</param>
              void SendUninstallInterceptor(address target, const string & module)
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UninstallInterceptor самому себе
              /// </summary>
              /// <param name="module">Модуль, в который будет отключена инъекция перехватчиков вызовов функций api платформы</param>
              void RaiseUninstallInterceptor(const string & module)
              {
                G1::UninstallInterceptor cmd;
                cmd.SetModule(module);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события UninstallInterceptorAnswer по адресу
              /// </summary>
              /// <param name="uninstalled">- Отключено или нет</param>
              void SendUninstallInterceptorAnswer(address target, bool uninstalled)
              {
                G1::UninstallInterceptorAnswer cmd;
                cmd.SetUninstalled(uninstalled);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UninstallInterceptorAnswer самому себе
              /// </summary>
              /// <param name="uninstalled">- Отключено или нет</param>
              void RaiseUninstallInterceptorAnswer(bool uninstalled)
              {
                G1::UninstallInterceptorAnswer cmd;
                cmd.SetUninstalled(uninstalled);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          

          BEGIN_PROTOCOL(2, 2)
            
            #pragma region Enumerations
            /// <summary> 
            /// Ошибки перехватчика
            /// </summary>
            /// <summary> 
            /// Режим перехвата функции platform-api
            /// </summary>
            /// <summary> 
            /// Коды ошибок средства тестирования
            /// </summary>
            #pragma endregion
            
            //Структуры
            #pragma region Messages and wrappers
            
            //Сообщения
            // Отправляется в момент получения в скрипте команды изменения фильтра входящих сообщений от некоторого модуля (SetFilter)
            BEGIN_MESSAGE(ChangeFilter,25,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ChangeFilter

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Отправляется в момент получения в скрипте команды изменения фильтра входящих сообщений от некоторого модуля (SetFilter)
              /// </summary>
              void ChangeFilter() const
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ChangeFilter, 2); 
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события ChangeFilter по адресу
              /// </summary>
              void SendChangeFilter(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::ChangeFilter, 2); 
              }
              /// <summary> 
              /// Отправка события ChangeFilter самому себе
              /// </summary>
              void RaiseChangeFilter()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ChangeFilter, 2); 
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // пространство имен Protocol
        } // пространство имен Tester
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
#pragma region Macro
#ifdef USE_KERNEL_TESTER_HELPERS
#define FAIL_IF(cond, code) if (cond) {\
                             m_Protocol.RaiseFail(Protocol::G1::TesterErrors::code);\
                             return;\
                           }
#endif
#pragma endregion
