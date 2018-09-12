// Uniteller.Framework.Kernel.Host

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText, 
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace Host
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(5, 1)
            
            #pragma region Перечисления
            /// <summary> 
            /// Коды ошибок хост-модуля микро-ядра
            /// </summary>
            enum class HostErrors
            {
              FailedToCreateModule = 1, // - Не удалось создать и подключить к шине запрошенный модуль
              MasterModuleDoesNotSet = 2 // - Не удалось определить какой мастер-модуль следовало запустить.
            };
            
            /// <summary> 
            /// Тип наблюдателя
            /// </summary>
            enum class ObserverKind
            {
              Both = 2, // - Наблюдение за исходящим и входящим трафиком
              Inbox = 1, // - Наблюдение за входящим трафиком
              Outbox = 0 // - Наблюдение за исходящим трафиком
            };
            
            // Конверторы
            inline bool IsValidHostErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 3));
            }
            
            inline HostErrors ConvertToHostErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return HostErrors::FailedToCreateModule;
                case 2:
                  return HostErrors::MasterModuleDoesNotSet;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу HostErrors", value);
                }
            }
            
            inline bool IsValidObserverKindValue(const int value)
            {
              return ((value >= 0)&&(value < 3));
            }
            
            inline ObserverKind ConvertToObserverKind(const int value)
            {
              switch (value)
              {
                case 2:
                  return ObserverKind::Both;
                case 1:
                  return ObserverKind::Inbox;
                case 0:
                  return ObserverKind::Outbox;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ObserverKind", value);
                }
            }
            
            #pragma endregion
            
            #pragma region Сообщения и обертки
            
            //Сообщения
            // Комадна для остановки хост-модуля ядра (и как следствие обычно и хост-процесса)
            BEGIN_MESSAGE(CloseHost,13,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CloseHost

            // Команда CreateInstance позволяет инициировать создание и подключение к шине передачи сообщений экземпляров новых объектов
            BEGIN_MESSAGE(CreateInstance,12,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, Generation, - Требуемое поколение модуля (0 - любое));
              ARGUMENT(1, string, ModuleId, - Желаемый уникальный идентификатор модуля);
              ARGUMENT(2, string, ModuleType, - Тип модуля для создания);
            END_MESSAGE(); // CreateInstance

            // Ответ на команду CreateInstance
            BEGIN_MESSAGE(CreateInstanceAnswer,19,4)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, Generation, - Требуемое поколение модуля (0 - любое));
              ARGUMENT(1, bool, IsCreated, - Создан ли модуль);
              ARGUMENT(2, string, ModuleId, - Назначенный уникальный идентификатор модуля);
              ARGUMENT(3, string, ModuleType, - Тип модуля для создания);
            END_MESSAGE(); // CreateInstanceAnswer

            // Команда хосту позволяет создать перехватчика сообщений
            BEGIN_MESSAGE(CreateInterceptor,17,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Intercepted, - Модуль сообщения которого будут перехватываться);
              ARGUMENT(1, string, Interceptor, - Модуль который получит функции перехватчика сообщений);
            END_MESSAGE(); // CreateInterceptor

            // Инициирует создание подшины
            BEGIN_MESSAGE(CreateLogicBus,15,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Master, - Идентификатор мастер-модуля);
            END_MESSAGE(); // CreateLogicBus

            // Ответное сообщение, высылаемое в случае успешного создания логической шины
            BEGIN_MESSAGE(CreateLogicBusAnswer,16,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, LogicBusId, - Идентификатор созданной логической шины);
            END_MESSAGE(); // CreateLogicBusAnswer

            // Данная команда хосту позволяет создать подписчика сообщений (модуль-observer, получающий копии сообщений другого модуля)
            BEGIN_MESSAGE(CreateObserver,18,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, ObserverKind, Mode, - Режим наблюдения);
              ARGUMENT(1, string, Observed, - Модуль сообщения которого будут направляться также и подписчикам);
              ARGUMENT(2, string, Observer, - Модуль который получит функции подписчика сообщений);
            END_MESSAGE(); // CreateObserver

            // Ошибка хост-модуля ядра
            BEGIN_MESSAGE(Fail,14,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, HostErrors, ErrorCode, - Код ошибки);
            END_MESSAGE(); // Fail

            // Получает значение опции командной строки
            BEGIN_MESSAGE(GetCommandLineOption,10,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Option, - Имя опции для получения);
            END_MESSAGE(); // GetCommandLineOption

            // Получает значение опции командной строки
            BEGIN_MESSAGE(GetCommandLineOptionAnswer,11,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, IsOptionSet, - Установлена ли опция);
              ARGUMENT(1, string, Option, - Имя опции);
              ARGUMENT(2, string, OptionValue, - Значение опции);
            END_MESSAGE(); // GetCommandLineOptionAnswer

            // Команда QueryKey. Позволяет запросить значение ключа реестра мета-данных.
            BEGIN_MESSAGE(QueryRegistryKey,3,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Path, - Путь в реестре мета-данных для чтения);
            END_MESSAGE(); // QueryRegistryKey

            // Сообщение QueryRegistryKeyAnswer (ответ на команду QueryRegistryKey).
            BEGIN_MESSAGE(QueryRegistryKeyAnswer,4,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, KeyExists, - Указывает существует ли ключ);
              ARGUMENT(1, variant, Value, - Указывает значение ключа);
            END_MESSAGE(); // QueryRegistryKeyAnswer

            // Команда QuerySubKeysCount. Позволяет получить число подключей указанного в параметре Path ключа реестра мета-данных.
            BEGIN_MESSAGE(QuerySubKeysCount,7,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Path, - Путь в реестре мета-данных для чтения подключей);
            END_MESSAGE(); // QuerySubKeysCount

            // Сообщений QuerySubKeysCountAnswer (ответ на команду QuerySubKeysCount).
            BEGIN_MESSAGE(QuerySubKeysCountAnswer,8,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, bool, KeyExists, - Указывает существует ли ключ);
              ARGUMENT(1, int, Value, - Множество имен подключей);
            END_MESSAGE(); // QuerySubKeysCountAnswer

            // Команда ReplaceAll. Позволяет подать команду, осуществляющую замену всех вхождений подстроки Pattern на значение строки Value в строке Source.
            BEGIN_MESSAGE(ReplaceAll,1,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Pattern, - Строка для поиска);
              ARGUMENT(1, string, Source, - Строка в которой будет осуществляться замена вхождений подстроки Pattern значениями Value);
              ARGUMENT(2, string, Value, - Строка для вставки);
            END_MESSAGE(); // ReplaceAll

            // Сообщение ReplaceAllAnswer (ответ на команду ReplaceAll). Содержит результат замены всех вхождений подстроки Pattern на значение строки Value в строке Source, переданной в команде ReplaceAll.
            BEGIN_MESSAGE(ReplaceAllAnswer,2,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Result, - Результат выполнения команды ReplaceAll);
            END_MESSAGE(); // ReplaceAllAnswer

            // Устанавливает код возврата из хост-процесса
            BEGIN_MESSAGE(SetHostProcessExitCode,9,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, - Код возврата);
            END_MESSAGE(); // SetHostProcessExitCode

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Комадна для остановки хост-модуля ядра (и как следствие обычно и хост-процесса)
              /// </summary>
              void CloseHost()
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда CreateInstance позволяет инициировать создание и подключение к шине передачи сообщений экземпляров новых объектов
              /// </summary>
              /// <param name="generation">- Требуемое поколение модуля (0 - любое)</param>
              /// <param name="moduleId">- Желаемый уникальный идентификатор модуля</param>
              /// <param name="moduleType">- Тип модуля для создания</param>
              void CreateInstance(int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда хосту позволяет создать перехватчика сообщений
              /// </summary>
              /// <param name="intercepted">- Модуль, сообщения которого будут перехватываться</param>
              /// <param name="interceptor">- Модуль, который получит функции перехватчика сообщений</param>
              void CreateInterceptor(const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Инициирует создание подшины
              /// </summary>
              /// <param name="master">- Идентификатор мастер-модуля</param>
              void CreateLogicBus(const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Данная команда хосту позволяет создать подписчика сообщений (модуль-observer, получающий копии сообщений другого модуля)
              /// </summary>
              /// <param name="mode">- Режим наблюдения</param>
              /// <param name="observed">- Модуль, сообщения которого будут направляться также и подписчикам</param>
              /// <param name="observer">- Модуль, который получит функции подписчика сообщений</param>
              void CreateObserver(ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ошибка хост-модуля ядра
              /// </summary>
              /// <param name="errorCode">- Код ошибки</param>
              void Fail(HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получает значение опции командной строки
              /// </summary>
              /// <param name="option">- Имя опции для получения</param>
              void GetCommandLineOption(const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда QueryKey. Позволяет запросить значение ключа реестра мета-данных.
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения</param>
              void QueryRegistryKey(const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда QuerySubKeysCount. Позволяет получить число подключей указанного в параметре Path ключа реестра мета-данных.
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения подключей</param>
              void QuerySubKeysCount(const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда ReplaceAll. Позволяет подать команду, осуществляющую замену всех вхождений подстроки Pattern на значение строки Value в строке Source.
              /// </summary>
              /// <param name="pattern">- Строка для поиска</param>
              /// <param name="source">- Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">- Строка для вставки</param>
              void ReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Устанавливает код возврата из хост-процесса
              /// </summary>
              /// <param name="exitCode">- Код возврата</param>
              void SetHostProcessExitCode(int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события CloseHostпо адресу
              /// </summary>
              void SendCloseHost(address target)
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CloseHost самому себе
              /// </summary>
              void RaiseCloseHost()
              {
                G1::CloseHost cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateInstanceпо адресу
              /// </summary>
              /// <param name="generation">- Требуемое поколение модуля (0 - любое)</param>
              /// <param name="moduleId">- Желаемый уникальный идентификатор модуля</param>
              /// <param name="moduleType">- Тип модуля для создания</param>
              void SendCreateInstance(address target, int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateInstance самому себе
              /// </summary>
              /// <param name="generation">- Требуемое поколение модуля (0 - любое)</param>
              /// <param name="moduleId">- Желаемый уникальный идентификатор модуля</param>
              /// <param name="moduleType">- Тип модуля для создания</param>
              void RaiseCreateInstance(int generation, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstance cmd;
                cmd.Generation = generation;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateInstanceAnswerпо адресу
              /// </summary>
              /// <param name="generation">- Требуемое поколение модуля (0 - любое)</param>
              /// <param name="isCreated">- Создан ли модуль</param>
              /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
              /// <param name="moduleType">- Тип модуля для создания</param>
              void SendCreateInstanceAnswer(address target, int generation, bool isCreated, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstanceAnswer cmd;
                cmd.Generation = generation;
                cmd.IsCreated = isCreated;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateInstanceAnswer самому себе
              /// </summary>
              /// <param name="generation">- Требуемое поколение модуля (0 - любое)</param>
              /// <param name="isCreated">- Создан ли модуль</param>
              /// <param name="moduleId">- Назначенный уникальный идентификатор модуля</param>
              /// <param name="moduleType">- Тип модуля для создания</param>
              void RaiseCreateInstanceAnswer(int generation, bool isCreated, const string & moduleId, const string & moduleType)
              {
                G1::CreateInstanceAnswer cmd;
                cmd.Generation = generation;
                cmd.IsCreated = isCreated;
                cmd.ModuleId = moduleId;
                cmd.ModuleType = moduleType;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateInterceptorпо адресу
              /// </summary>
              /// <param name="intercepted">- Модуль, сообщения которого будут перехватываться</param>
              /// <param name="interceptor">- Модуль, который получит функции перехватчика сообщений</param>
              void SendCreateInterceptor(address target, const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateInterceptor самому себе
              /// </summary>
              /// <param name="intercepted">- Модуль, сообщения которого будут перехватываться</param>
              /// <param name="interceptor">- Модуль, который получит функции перехватчика сообщений</param>
              void RaiseCreateInterceptor(const string & intercepted, const string & interceptor)
              {
                G1::CreateInterceptor cmd;
                cmd.Intercepted = intercepted;
                cmd.Interceptor = interceptor;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateLogicBusпо адресу
              /// </summary>
              /// <param name="master">- Идентификатор мастер-модуля</param>
              void SendCreateLogicBus(address target, const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateLogicBus самому себе
              /// </summary>
              /// <param name="master">- Идентификатор мастер-модуля</param>
              void RaiseCreateLogicBus(const string & master)
              {
                G1::CreateLogicBus cmd;
                cmd.Master = master;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateLogicBusAnswerпо адресу
              /// </summary>
              /// <param name="logicBusId">- Идентификатор созданной логической шины</param>
              void SendCreateLogicBusAnswer(address target, const string & logicBusId)
              {
                G1::CreateLogicBusAnswer cmd;
                cmd.LogicBusId = logicBusId;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateLogicBusAnswer самому себе
              /// </summary>
              /// <param name="logicBusId">- Идентификатор созданной логической шины</param>
              void RaiseCreateLogicBusAnswer(const string & logicBusId)
              {
                G1::CreateLogicBusAnswer cmd;
                cmd.LogicBusId = logicBusId;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateObserverпо адресу
              /// </summary>
              /// <param name="mode">- Режим наблюдения</param>
              /// <param name="observed">- Модуль, сообщения которого будут направляться также и подписчикам</param>
              /// <param name="observer">- Модуль, который получит функции подписчика сообщений</param>
              void SendCreateObserver(address target, ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateObserver самому себе
              /// </summary>
              /// <param name="mode">- Режим наблюдения</param>
              /// <param name="observed">- Модуль, сообщения которого будут направляться также и подписчикам</param>
              /// <param name="observer">- Модуль, который получит функции подписчика сообщений</param>
              void RaiseCreateObserver(ObserverKind mode, const string & observed, const string & observer)
              {
                G1::CreateObserver cmd;
                cmd.Mode = mode;
                cmd.Observed = observed;
                cmd.Observer = observer;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Failпо адресу
              /// </summary>
              /// <param name="errorCode">- Код ошибки</param>
              void SendFail(address target, HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Fail самому себе
              /// </summary>
              /// <param name="errorCode">- Код ошибки</param>
              void RaiseFail(HostErrors errorCode)
              {
                G1::Fail cmd;
                cmd.ErrorCode = errorCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetCommandLineOptionпо адресу
              /// </summary>
              /// <param name="option">- Имя опции для получения</param>
              void SendGetCommandLineOption(address target, const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetCommandLineOption самому себе
              /// </summary>
              /// <param name="option">- Имя опции для получения</param>
              void RaiseGetCommandLineOption(const string & option)
              {
                G1::GetCommandLineOption cmd;
                cmd.Option = option;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetCommandLineOptionAnswerпо адресу
              /// </summary>
              /// <param name="isOptionSet">- Установлена ли опция</param>
              /// <param name="option">- Имя опции</param>
              /// <param name="optionValue">- Значение опции</param>
              void SendGetCommandLineOptionAnswer(address target, bool isOptionSet, const string & option, const string & optionValue)
              {
                G1::GetCommandLineOptionAnswer cmd;
                cmd.IsOptionSet = isOptionSet;
                cmd.Option = option;
                cmd.OptionValue = optionValue;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetCommandLineOptionAnswer самому себе
              /// </summary>
              /// <param name="isOptionSet">- Установлена ли опция</param>
              /// <param name="option">- Имя опции</param>
              /// <param name="optionValue">- Значение опции</param>
              void RaiseGetCommandLineOptionAnswer(bool isOptionSet, const string & option, const string & optionValue)
              {
                G1::GetCommandLineOptionAnswer cmd;
                cmd.IsOptionSet = isOptionSet;
                cmd.Option = option;
                cmd.OptionValue = optionValue;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события QueryRegistryKeyпо адресу
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения</param>
              void SendQueryRegistryKey(address target, const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события QueryRegistryKey самому себе
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения</param>
              void RaiseQueryRegistryKey(const string & path)
              {
                G1::QueryRegistryKey cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события QueryRegistryKeyAnswerпо адресу
              /// </summary>
              /// <param name="keyExists">- Указывает существует ли ключ</param>
              /// <param name="value">- Указывает значение ключа</param>
              void SendQueryRegistryKeyAnswer(address target, bool keyExists, variant value)
              {
                G1::QueryRegistryKeyAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события QueryRegistryKeyAnswer самому себе
              /// </summary>
              /// <param name="keyExists">- Указывает существует ли ключ</param>
              /// <param name="value">- Указывает значение ключа</param>
              void RaiseQueryRegistryKeyAnswer(bool keyExists, variant value)
              {
                G1::QueryRegistryKeyAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события QuerySubKeysCountпо адресу
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения подключей</param>
              void SendQuerySubKeysCount(address target, const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события QuerySubKeysCount самому себе
              /// </summary>
              /// <param name="path">- Путь в реестре мета-данных для чтения подключей</param>
              void RaiseQuerySubKeysCount(const string & path)
              {
                G1::QuerySubKeysCount cmd;
                cmd.Path = path;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события QuerySubKeysCountAnswerпо адресу
              /// </summary>
              /// <param name="keyExists">- Указывает существует ли ключ</param>
              /// <param name="value">- Множество имен подключей</param>
              void SendQuerySubKeysCountAnswer(address target, bool keyExists, int value)
              {
                G1::QuerySubKeysCountAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события QuerySubKeysCountAnswer самому себе
              /// </summary>
              /// <param name="keyExists">- Указывает существует ли ключ</param>
              /// <param name="value">- Множество имен подключей</param>
              void RaiseQuerySubKeysCountAnswer(bool keyExists, int value)
              {
                G1::QuerySubKeysCountAnswer cmd;
                cmd.KeyExists = keyExists;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ReplaceAllпо адресу
              /// </summary>
              /// <param name="pattern">- Строка для поиска</param>
              /// <param name="source">- Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">- Строка для вставки</param>
              void SendReplaceAll(address target, const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ReplaceAll самому себе
              /// </summary>
              /// <param name="pattern">- Строка для поиска</param>
              /// <param name="source">- Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">- Строка для вставки</param>
              void RaiseReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.Pattern = pattern;
                cmd.Source = source;
                cmd.Value = value;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ReplaceAllAnswerпо адресу
              /// </summary>
              /// <param name="result">- Результат выполнения команды ReplaceAll</param>
              void SendReplaceAllAnswer(address target, const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.Result = result;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ReplaceAllAnswer самому себе
              /// </summary>
              /// <param name="result">- Результат выполнения команды ReplaceAll</param>
              void RaiseReplaceAllAnswer(const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.Result = result;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события SetHostProcessExitCodeпо адресу
              /// </summary>
              /// <param name="exitCode">- Код возврата</param>
              void SendSetHostProcessExitCode(address target, int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события SetHostProcessExitCode самому себе
              /// </summary>
              /// <param name="exitCode">- Код возврата</param>
              void RaiseSetHostProcessExitCode(int exitCode)
              {
                G1::SetHostProcessExitCode cmd;
                cmd.ExitCode = exitCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // пространство имен Protocol
        } // пространство имен Host
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
