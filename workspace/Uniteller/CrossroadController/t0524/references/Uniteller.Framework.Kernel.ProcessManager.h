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
      namespace ProcessManager
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(10, 1)
            
            #pragma region Перечисления
            /// <summary> 
            /// Начальный приоритет запускаемого процесса
            /// </summary>
            enum class ProcessPriority
            {
              AboveNorm = 3, // Приоритет AboveNormal
              BelowNorm = 1, // Приоритет BelowNormal
              High = 4, // Приоритет High
              Idle = 0, // Приоритет Idle
              Normal = 2, // Приоритет Normal
              RealTime = 5 // Приоритет Realtime
            };
            
            /// <summary> 
            /// Код ошибки старта процесс
            /// </summary>
            enum class ProcessStartFailedCode
            {
              AccessDenied = 3, // Не хватает прав доступа для запуска модуля
              FileCannotBeExecuted = 4, // Указанный файл не является исполняемым модулем
              FileNotFound = 2, // Указан неверный путь к модулю либо неверное имя модуля
              NotEnoughResourses = 0, // Недостаточно ресурсов для запуска процесса
              RequiredParameterMissing = 1 // Указано некорректное имя модуля
            };
            
            /// <summary> 
            /// Код окончания работы с процессом
            /// </summary>
            enum class ProcessStatusCode
            {
              Finished = 0, // Процесс стартовал, отработал и завершился
              InternalException = 3, // Внутренняя ошибка слежения за процессом в результате которой процесс был "брошен"
              NotStarted = 4, // Процесс не стартовал
              Released = 2, // Процесс был "брошен" по сообщению Release либо в процессе остановки
              Terminated = 1 // Процесс был прерван по сообщению Terminate либо по таймауту
            };
            
            /// <summary> 
            /// Начальное положение окна запускаемого приложения
            /// </summary>
            enum class WindowState
            {
              Default = 1, // Окно по умолчанию, размер и положение окна определяется самим приложением
              Hidden = 3, // Окно не отображается
              Maximized = 0, // Окно развернутое на полный экран
              Minimized = 2 // Свернутое окно
            };
            
            // Конверторы
            inline bool IsValidProcessPriorityValue(const int value)
            {
              return ((value >= 0)&&(value < 6));
            }
            
            inline ProcessPriority ConvertToProcessPriority(const int value)
            {
              switch (value)
              {
                case 3:
                  return ProcessPriority::AboveNorm;
                case 1:
                  return ProcessPriority::BelowNorm;
                case 4:
                  return ProcessPriority::High;
                case 0:
                  return ProcessPriority::Idle;
                case 2:
                  return ProcessPriority::Normal;
                case 5:
                  return ProcessPriority::RealTime;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ProcessPriority", value);
                }
            }
            
            inline bool IsValidProcessStartFailedCodeValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            inline ProcessStartFailedCode ConvertToProcessStartFailedCode(const int value)
            {
              switch (value)
              {
                case 3:
                  return ProcessStartFailedCode::AccessDenied;
                case 4:
                  return ProcessStartFailedCode::FileCannotBeExecuted;
                case 2:
                  return ProcessStartFailedCode::FileNotFound;
                case 0:
                  return ProcessStartFailedCode::NotEnoughResourses;
                case 1:
                  return ProcessStartFailedCode::RequiredParameterMissing;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ProcessStartFailedCode", value);
                }
            }
            
            inline bool IsValidProcessStatusCodeValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            inline ProcessStatusCode ConvertToProcessStatusCode(const int value)
            {
              switch (value)
              {
                case 0:
                  return ProcessStatusCode::Finished;
                case 3:
                  return ProcessStatusCode::InternalException;
                case 4:
                  return ProcessStatusCode::NotStarted;
                case 2:
                  return ProcessStatusCode::Released;
                case 1:
                  return ProcessStatusCode::Terminated;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ProcessStatusCode", value);
                }
            }
            
            inline bool IsValidWindowStateValue(const int value)
            {
              return ((value >= 0)&&(value < 4));
            }
            
            inline WindowState ConvertToWindowState(const int value)
            {
              switch (value)
              {
                case 1:
                  return WindowState::Default;
                case 3:
                  return WindowState::Hidden;
                case 0:
                  return WindowState::Maximized;
                case 2:
                  return WindowState::Minimized;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу WindowState", value);
                }
            }
            
            #pragma endregion
            
            #pragma region Сообщения и обертки
            
            //Сообщения
            // Запрос результата выполнения внешнего процесса
            BEGIN_MESSAGE(GetResult,9,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // GetResult

            // Ответное сообщение с результатами выполнения внешнего процесса
            BEGIN_MESSAGE(GetResultAnswer,10,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, Код возвращаемый внешним процессом по его завершению в случае если процесс не был запущен либо не был корректно завершён возвращается 0);
              ENUM(1, ProcessStatusCode, StatusCode, Наш код завершения);
            END_MESSAGE(); // GetResultAnswer

            // Ответное сообщение в случае появления новой строки выведенной внешнем процессом в stdout
            BEGIN_MESSAGE(ProcessConsoleRedirect,8,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, string, Line, Строка выведенная внешним процессом в stdout);
            END_MESSAGE(); // ProcessConsoleRedirect

            // Сообщение передаваемое в случае завершения процесса
            BEGIN_MESSAGE(ProcessFinished,4,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ARGUMENT(0, int, ExitCode, Код возвращаемый внешним процессом по его завершению в случае если процесс не был запущен либо не был корректно завершён возвращается 0);
              ENUM(1, ProcessStatusCode, StatusCode, Наш код завершения);
            END_MESSAGE(); // ProcessFinished

            // "Бросание" процесса с случае отсутствия необходимости следить и управлять успешно запущенным процессом
            BEGIN_MESSAGE(ProcessRelease,7,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessRelease

            // Запуск внешнего процесса с указанными параметрами
            BEGIN_MESSAGE(ProcessStart,1,8)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                CommandLine = "";
                ConsoleRedirect = false;
                CurrentDirectory = "";
                Environment = StringMap();
                Priority = ProcessPriority::Normal;
                TimeOut = 0;
                WindowInitialState = WindowState::Default;
              }
              ARGUMENT(0, string, ApplicationName, Путь и имя запускаемого модуля);
              ARGUMENT(1, string, CommandLine, Параметры запускаемого модуля разделенные пробелами);
              ARGUMENT(2, bool, ConsoleRedirect, Параметр указывает что будет осуществляться перехват вывода приложения в консоль и построчный возврат вывода в сообщении ConsoleRedirect
Параметр игнорируется для оконного приложения);
              ARGUMENT(3, string, CurrentDirectory, Параметр указывающий рабочую директорию запускаемого приложения);
              ARGUMENT(4, StringMap, Environment, Если не указана ни одна переменная окружения то используется текущие системные переменные окружения
Если указана одна либо несколько переменных окружения и среди них есть переменная PATH то используются указанные переменные окружения
Если указана одна либо несколько переменных окружения и среди них нет переменной PATH то используются указанные переменные окружения плюс переменная PATH из текущих системных);
              ENUM(5, ProcessPriority, Priority, Начальный приоритет процесса);
              ARGUMENT(6, int, TimeOut, Таймаут в миллисекундах по истечению которого процесс завершается принудительно.);
              ENUM(7, WindowState, WindowInitialState, Начальное состояние и положение окна);
            END_MESSAGE(); // ProcessStart

            // Ответное сообщение передаваемое в случае неуспешного запуска процесса
            BEGIN_MESSAGE(ProcessStartFailed,3,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              ENUM(0, ProcessStartFailedCode, Reason, Причина по которой запуск процесса был неуспешен);
            END_MESSAGE(); // ProcessStartFailed

            // Ответное сообщение передаваемое в случае успешного запуска процесса
            BEGIN_MESSAGE(ProcessStartSuccessful,2,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessStartSuccessful

            // Прерывание процесса
            BEGIN_MESSAGE(ProcessTerminate,5,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessTerminate

            // Сообщение указывающее прерывание внешнего процесса по таймауту
            BEGIN_MESSAGE(ProcessTerminateDueToTimeOut,6,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ProcessTerminateDueToTimeOut

            // Ответное сообщение в случае успешного перезапуска машины для нового запуска внешнего процесса
            BEGIN_MESSAGE(Ready,12,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Ready

            // Сообщение использующееся внутри машины для очередного цикла работы (слежения)
            BEGIN_MESSAGE(Redo,13,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Redo

            // Перезапуск машины для нового запуска внешнего процесса
            BEGIN_MESSAGE(Reset,11,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // Reset

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Запрос результата выполнения внешнего процесса
              /// </summary>
              void GetResult()
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ответное сообщение в случае появления новой строки выведенной внешнем процессом в stdout
              /// </summary>
              /// <param name="line">Строка выведенная внешним процессом в stdout</param>
              void ProcessConsoleRedirect(const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Сообщение передаваемое в случае завершения процесса
              /// </summary>
              /// <param name="exitCode">Код возвращаемый внешним процессом по его завершению, в случае если процесс не был запущен либо не был корректно завершён возвращается 0</param>
              /// <param name="statusCode">Наш код завершения</param>
              void ProcessFinished(int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// "Бросание" процесса с случае отсутствия необходимости следить и управлять успешно запущенным процессом
              /// </summary>
              void ProcessRelease()
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Запуск внешнего процесса с указанными параметрами
              /// </summary>
              /// <param name="applicationName">Путь и имя запускаемого модуля</param>
              /// <param name="CommandLine">Параметры запускаемого модуля разделенные пробелами</param>
              /// <param name="ConsoleRedirect">Параметр указывает что будет осуществляться перехват вывода приложения в консоль и построчный возврат вывода в сообщении ConsoleRedirect
              /// Параметр игнорируется для оконного приложения</param>
              /// <param name="CurrentDirectory">Параметр указывающий рабочую директорию запускаемого приложения</param>
              /// <param name="Environment">Если не указана ни одна переменная окружения, то используется текущие системные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них есть переменная PATH, то используются указанные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них нет переменной PATH, то используются указанные переменные окружения плюс переменная PATH из текущих системных</param>
              /// <param name="Priority">Начальный приоритет процесса</param>
              /// <param name="TimeOut">Таймаут в миллисекундах по истечению которого процесс завершается принудительно.</param>
              /// <param name="WindowInitialState">Начальное состояние и положение окна</param>
              void ProcessStart(const string & applicationName, string commandLine = "", bool consoleRedirect = false, string currentDirectory = "", StringMap environment = StringMap(), ProcessPriority priority = ProcessPriority::Normal, int timeOut = 0, WindowState windowInitialState = WindowState::Default)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ответное сообщение передаваемое в случае неуспешного запуска процесса
              /// </summary>
              /// <param name="reason">Причина по которой запуск процесса был неуспешен</param>
              void ProcessStartFailed(ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ответное сообщение передаваемое в случае успешного запуска процесса
              /// </summary>
              void ProcessStartSuccessful()
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Прерывание процесса
              /// </summary>
              void ProcessTerminate()
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Сообщение указывающее прерывание внешнего процесса по таймауту
              /// </summary>
              void ProcessTerminateDueToTimeOut()
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ответное сообщение в случае успешного перезапуска машины для нового запуска внешнего процесса
              /// </summary>
              void Ready()
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Сообщение использующееся внутри машины для очередного цикла работы (слежения)
              /// </summary>
              void Redo()
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Перезапуск машины для нового запуска внешнего процесса
              /// </summary>
              void Reset()
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события GetResultпо адресу
              /// </summary>
              void SendGetResult(address target)
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetResult самому себе
              /// </summary>
              void RaiseGetResult()
              {
                G1::GetResult cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetResultAnswerпо адресу
              /// </summary>
              /// <param name="exitCode">Код возвращаемый внешним процессом по его завершению, в случае если процесс не был запущен либо не был корректно завершён возвращается 0</param>
              /// <param name="statusCode">Наш код завершения</param>
              void SendGetResultAnswer(address target, int exitCode, ProcessStatusCode statusCode)
              {
                G1::GetResultAnswer cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetResultAnswer самому себе
              /// </summary>
              /// <param name="exitCode">Код возвращаемый внешним процессом по его завершению, в случае если процесс не был запущен либо не был корректно завершён возвращается 0</param>
              /// <param name="statusCode">Наш код завершения</param>
              void RaiseGetResultAnswer(int exitCode, ProcessStatusCode statusCode)
              {
                G1::GetResultAnswer cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessConsoleRedirectпо адресу
              /// </summary>
              /// <param name="line">Строка выведенная внешним процессом в stdout</param>
              void SendProcessConsoleRedirect(address target, const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessConsoleRedirect самому себе
              /// </summary>
              /// <param name="line">Строка выведенная внешним процессом в stdout</param>
              void RaiseProcessConsoleRedirect(const string & line)
              {
                G1::ProcessConsoleRedirect cmd;
                cmd.Line = line;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessFinishedпо адресу
              /// </summary>
              /// <param name="exitCode">Код возвращаемый внешним процессом по его завершению, в случае если процесс не был запущен либо не был корректно завершён возвращается 0</param>
              /// <param name="statusCode">Наш код завершения</param>
              void SendProcessFinished(address target, int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessFinished самому себе
              /// </summary>
              /// <param name="exitCode">Код возвращаемый внешним процессом по его завершению, в случае если процесс не был запущен либо не был корректно завершён возвращается 0</param>
              /// <param name="statusCode">Наш код завершения</param>
              void RaiseProcessFinished(int exitCode, ProcessStatusCode statusCode)
              {
                G1::ProcessFinished cmd;
                cmd.ExitCode = exitCode;
                cmd.StatusCode = statusCode;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessReleaseпо адресу
              /// </summary>
              void SendProcessRelease(address target)
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessRelease самому себе
              /// </summary>
              void RaiseProcessRelease()
              {
                G1::ProcessRelease cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessStartпо адресу
              /// </summary>
              /// <param name="applicationName">Путь и имя запускаемого модуля</param>
              /// <param name="commandLine">Параметры запускаемого модуля разделенные пробелами</param>
              /// <param name="consoleRedirect">Параметр указывает что будет осуществляться перехват вывода приложения в консоль и построчный возврат вывода в сообщении ConsoleRedirect
              /// Параметр игнорируется для оконного приложения</param>
              /// <param name="currentDirectory">Параметр указывающий рабочую директорию запускаемого приложения</param>
              /// <param name="environment">Если не указана ни одна переменная окружения, то используется текущие системные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них есть переменная PATH, то используются указанные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них нет переменной PATH, то используются указанные переменные окружения плюс переменная PATH из текущих системных</param>
              /// <param name="priority">Начальный приоритет процесса</param>
              /// <param name="timeOut">Таймаут в миллисекундах по истечению которого процесс завершается принудительно.</param>
              /// <param name="windowInitialState">Начальное состояние и положение окна</param>
              void SendProcessStart(address target, const string & applicationName, const string & commandLine, bool consoleRedirect, const string & currentDirectory, StringMap environment, ProcessPriority priority, int timeOut, WindowState windowInitialState)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessStart самому себе
              /// </summary>
              /// <param name="applicationName">Путь и имя запускаемого модуля</param>
              /// <param name="commandLine">Параметры запускаемого модуля разделенные пробелами</param>
              /// <param name="consoleRedirect">Параметр указывает что будет осуществляться перехват вывода приложения в консоль и построчный возврат вывода в сообщении ConsoleRedirect
              /// Параметр игнорируется для оконного приложения</param>
              /// <param name="currentDirectory">Параметр указывающий рабочую директорию запускаемого приложения</param>
              /// <param name="environment">Если не указана ни одна переменная окружения, то используется текущие системные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них есть переменная PATH, то используются указанные переменные окружения
              /// Если указана одна либо несколько переменных окружения и среди них нет переменной PATH, то используются указанные переменные окружения плюс переменная PATH из текущих системных</param>
              /// <param name="priority">Начальный приоритет процесса</param>
              /// <param name="timeOut">Таймаут в миллисекундах по истечению которого процесс завершается принудительно.</param>
              /// <param name="windowInitialState">Начальное состояние и положение окна</param>
              void RaiseProcessStart(const string & applicationName, const string & commandLine, bool consoleRedirect, const string & currentDirectory, StringMap environment, ProcessPriority priority, int timeOut, WindowState windowInitialState)
              {
                G1::ProcessStart cmd;
                cmd.ApplicationName = applicationName;
                cmd.CommandLine = commandLine;
                cmd.ConsoleRedirect = consoleRedirect;
                cmd.CurrentDirectory = currentDirectory;
                cmd.Environment = environment;
                cmd.Priority = priority;
                cmd.TimeOut = timeOut;
                cmd.WindowInitialState = windowInitialState;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessStartFailedпо адресу
              /// </summary>
              /// <param name="reason">Причина по которой запуск процесса был неуспешен</param>
              void SendProcessStartFailed(address target, ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessStartFailed самому себе
              /// </summary>
              /// <param name="reason">Причина по которой запуск процесса был неуспешен</param>
              void RaiseProcessStartFailed(ProcessStartFailedCode reason)
              {
                G1::ProcessStartFailed cmd;
                cmd.Reason = reason;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessStartSuccessfulпо адресу
              /// </summary>
              void SendProcessStartSuccessful(address target)
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessStartSuccessful самому себе
              /// </summary>
              void RaiseProcessStartSuccessful()
              {
                G1::ProcessStartSuccessful cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessTerminateпо адресу
              /// </summary>
              void SendProcessTerminate(address target)
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessTerminate самому себе
              /// </summary>
              void RaiseProcessTerminate()
              {
                G1::ProcessTerminate cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ProcessTerminateDueToTimeOutпо адресу
              /// </summary>
              void SendProcessTerminateDueToTimeOut(address target)
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ProcessTerminateDueToTimeOut самому себе
              /// </summary>
              void RaiseProcessTerminateDueToTimeOut()
              {
                G1::ProcessTerminateDueToTimeOut cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Readyпо адресу
              /// </summary>
              void SendReady(address target)
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Ready самому себе
              /// </summary>
              void RaiseReady()
              {
                G1::Ready cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Redoпо адресу
              /// </summary>
              void SendRedo(address target)
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Redo самому себе
              /// </summary>
              void RaiseRedo()
              {
                G1::Redo cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Resetпо адресу
              /// </summary>
              void SendReset(address target)
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Reset самому себе
              /// </summary>
              void RaiseReset()
              {
                G1::Reset cmd;
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // пространство имен Protocol
        } // пространство имен ProcessManager
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
