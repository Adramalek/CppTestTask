// Uniteller.Framework.Kernel.System

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
      namespace System
      {
        namespace Protocol
        {

          BEGIN_PROTOCOL(1, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// Коды для использования разделителя Delim в сообщениях Split,Unpack
            /// </summary>
            enum class DelimMode
            {
              AnyOf = 0, // - Использовать любой из символов, указанных в Delim
              Sequence = 1 // - Использовать указанную в Delim подстроку
            };
            
            /// <summary> 
            /// Коды статуса ответа на сообщение MatchFormat
            /// </summary>
            enum class Matching
            {
              Fail = 1, // - Сравнение неуспешно
              Success = 0, // - Сравнение успешно
              WrongFormat = 2 // - Некорректно задан формат
            };
            
            /// <summary> 
            /// Коды статуса ответа на сообщения Unpack
            /// </summary>
            enum class UnpackAnswerStatus
            {
              Error = 4, // - Ошибка (неверные параметры сообщения, пустой разделитель, пустая строка source и др)
              IsDivider = 3, // - Строка совпала с разделителем, возвращаемые аргументы пусты
              NoHead = 2, // - Не существует головной части строки для UnpackLast
              NoTail = 1, // - Не существует хвостовой части строки для UnpackFirst
              Success = 0 // - Успешное завершение
            };
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа DelimMode
            /// </summary>
            inline bool IsValidDelimModeValue(const int value)
            {
              return ((value >= 0)&&(value < 2));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу DelimMode
            /// </summary>
            inline DelimMode ConvertToDelimMode(const int value)
            {
              switch (value)
              {
                case 0:
                  return DelimMode::AnyOf;
                case 1:
                  return DelimMode::Sequence;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу DelimMode", value);
                }
            }
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа Matching
            /// </summary>
            inline bool IsValidMatchingValue(const int value)
            {
              return ((value >= 0)&&(value < 3));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу Matching
            /// </summary>
            inline Matching ConvertToMatching(const int value)
            {
              switch (value)
              {
                case 1:
                  return Matching::Fail;
                case 0:
                  return Matching::Success;
                case 2:
                  return Matching::WrongFormat;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу Matching", value);
                }
            }
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа UnpackAnswerStatus
            /// </summary>
            inline bool IsValidUnpackAnswerStatusValue(const int value)
            {
              return ((value >= 0)&&(value < 5));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу UnpackAnswerStatus
            /// </summary>
            inline UnpackAnswerStatus ConvertToUnpackAnswerStatus(const int value)
            {
              switch (value)
              {
                case 4:
                  return UnpackAnswerStatus::Error;
                case 3:
                  return UnpackAnswerStatus::IsDivider;
                case 2:
                  return UnpackAnswerStatus::NoHead;
                case 1:
                  return UnpackAnswerStatus::NoTail;
                case 0:
                  return UnpackAnswerStatus::Success;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу UnpackAnswerStatus", value);
                }
            }
            
            #pragma endregion
            
            //Структуры
            #pragma region Messages and wrappers
            
            //Сообщения
            // Команда GetLength. Позволяет подать команду на получение длины строки
            BEGIN_MESSAGE(GetLength,17,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Исходная строка
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // GetLength

            // Результат выполнения GetLength
            BEGIN_MESSAGE(GetLengthAnswer,18,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Длина строки
              ARGUMENT(0, int, Result);
            END_MESSAGE(); // GetLengthAnswer

            // Команда MatchFormat. Позволяет подать команду, проверяющую соответствие строки Source формату Format и возвращающая подстроки, соответствующие формату
            BEGIN_MESSAGE(MatchFormat,15,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Формат сопоставления
              ARGUMENT(0, string, Format);
              // Исходная строка
              ARGUMENT(1, string, Source);
            END_MESSAGE(); // MatchFormat

            // Результат выполнения команды MatchFormat
            BEGIN_MESSAGE(MatchFormatAnswer,16,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Успешно ли сравнение
              ENUM(0, Matching, MatchResult);
              // Список строк которые успешно прошли сопоставление с форматом
              ARGUMENT(1, StringList, Result);
            END_MESSAGE(); // MatchFormatAnswer

            // Команда ReplaceAll. Позволяет подать команду, осуществляющую замену всех вхождений подстроки Pattern на значение строки Value в строке Source.
            BEGIN_MESSAGE(ReplaceAll,1,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Строка для поиска
              ARGUMENT(0, string, Pattern);
              // Строка в которой будет осуществляться замена вхождений подстроки Pattern значениями Value
              ARGUMENT(1, string, Source);
              // Строка для вставки
              ARGUMENT(2, string, Value);
            END_MESSAGE(); // ReplaceAll

            // Сообщение ReplaceAllAnswer (ответ на команду ReplaceAll). Содержит результат замены всех вхождений подстроки Pattern на значение строки Value в строке Source, переданной в команде ReplaceAll.
            BEGIN_MESSAGE(ReplaceAllAnswer,2,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат выполнения команды ReplaceAll
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // ReplaceAllAnswer

            // Команда Split. Позволяет подать команду, осуществляющую разбиение указанной строки Source по разделителю Delim
            BEGIN_MESSAGE(Split,3,4)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetAllowEmpty(false);
                SetMode((DelimMode)DelimMode::AnyOf);
              }
              // Допускаются ли пустые строки в ответе
              ARGUMENT(0, bool, AllowEmpty);
              // Символ или последовательность символов которые служат разделителем
              ARGUMENT(1, string, Delim);
              // Режим работы команды
              ENUM(2, DelimMode, Mode);
              // Строка которая будет разбиваться
              ARGUMENT(3, string, Source);
            END_MESSAGE(); // Split

            // Сообщение SplitAnswer (ответ на команду Split)
            BEGIN_MESSAGE(SplitAnswer,4,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат выполнения команды Split
              ARGUMENT(0, StringList, Result);
            END_MESSAGE(); // SplitAnswer

            // Команда Trim. Позволяет подать команду, удаляющую лидирующие пробелы в начале и в конце строки Source
            BEGIN_MESSAGE(Trim,13,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Исходная строка
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // Trim

            // Команда TrimAnswer
            BEGIN_MESSAGE(TrimAnswer,14,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат выполнения команды Trim
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimAnswer

            // Команда TrimLeft. Позволяет подать команду, удаляющую лидирующие пробелы в начале строки Source
            BEGIN_MESSAGE(TrimLeft,9,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Исходная строка
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // TrimLeft

            // Команда TrimLeftAnswer
            BEGIN_MESSAGE(TrimLeftAnswer,10,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат выполнения команды TrimLeft
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimLeftAnswer

            // Команда TrimRight. Позволяет подать команду, удаляющую лидирующие пробелы в конце строки Source
            BEGIN_MESSAGE(TrimRight,11,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Исходная строка
              ARGUMENT(0, string, Source);
            END_MESSAGE(); // TrimRight

            // Команда TrimRightAnswer
            BEGIN_MESSAGE(TrimRightAnswer,12,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат выполнения команды TrimRight
              ARGUMENT(0, string, Result);
            END_MESSAGE(); // TrimRightAnswer

            // Команда UnpackFirst. Позволяет подать команду, осуществляющую разбиение строки Source на "голову" и "хвост" по первому вхождению разделителя Delim
            BEGIN_MESSAGE(UnpackFirst,5,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMode((DelimMode)DelimMode::Sequence);
              }
              // Символ-разделитель
              ARGUMENT(0, string, Delim);
              // Режим работы команды
              ENUM(1, DelimMode, Mode);
              // Строка для разбиения
              ARGUMENT(2, string, Source);
            END_MESSAGE(); // UnpackFirst

            // Результат выполнения команды UnpackFirst
            BEGIN_MESSAGE(UnpackFirstAnswer,6,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Головная часть строки
              ARGUMENT(0, string, Head);
              // Флаг выполнения команды UnpackFirst
              ENUM(1, UnpackAnswerStatus, Status);
              // Хвостовая часть строки
              ARGUMENT(2, string, Tail);
            END_MESSAGE(); // UnpackFirstAnswer

            // Команда UnpackEntry. Позволяет подать команду, осуществляющую разбиение строки Source на "голову" и "хвост" по последнему вхождению разделителя Delim
            BEGIN_MESSAGE(UnpackLast,7,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMode((DelimMode)DelimMode::Sequence);
              }
              // Символ-разделитель
              ARGUMENT(0, string, Delim);
              // Режим работы команды
              ENUM(1, DelimMode, Mode);
              // Строка для разбиения
              ARGUMENT(2, string, Source);
            END_MESSAGE(); // UnpackLast

            // Результат выполнения команды UnpackLast
            BEGIN_MESSAGE(UnpackLastAnswer,8,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Головная часть строки
              ARGUMENT(0, string, Head);
              // | Флаг выполнения команды UnpackLast
              ENUM(1, UnpackAnswerStatus, Status);
              // Хвостовая часть строки
              ARGUMENT(2, string, Tail);
            END_MESSAGE(); // UnpackLastAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Команда GetLength. Позволяет подать команду на получение длины строки
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void GetLength(const string & source) const
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда MatchFormat. Позволяет подать команду, проверяющую соответствие строки Source формату Format и возвращающая подстроки, соответствующие формату
              /// </summary>
              /// <param name="format">Формат сопоставления</param>
              /// <param name="source">Исходная строка</param>
              void MatchFormat(const string & format, const string & source) const
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда ReplaceAll. Позволяет подать команду, осуществляющую замену всех вхождений подстроки Pattern на значение строки Value в строке Source.
              /// </summary>
              /// <param name="pattern">Строка для поиска</param>
              /// <param name="source">Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">Строка для вставки</param>
              void ReplaceAll(const string & pattern, const string & source, const string & value) const
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда Split. Позволяет подать команду, осуществляющую разбиение указанной строки Source по разделителю Delim
              /// </summary>
              /// <param name="delim">Символ или последовательность символов, которые служат разделителем</param>
              /// <param name="source">Строка, которая будет разбиваться</param>
              /// <param name="AllowEmpty">Допускаются ли пустые строки в ответе</param>
              /// <param name="Mode">Режим работы команды</param>
              void Split(const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf) const
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда Trim. Позволяет подать команду, удаляющую лидирующие пробелы в начале и в конце строки Source
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void Trim(const string & source) const
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда TrimLeft. Позволяет подать команду, удаляющую лидирующие пробелы в начале строки Source
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void TrimLeft(const string & source) const
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда TrimRight. Позволяет подать команду, удаляющую лидирующие пробелы в конце строки Source
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void TrimRight(const string & source) const
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда UnpackFirst. Позволяет подать команду, осуществляющую разбиение строки Source на "голову" и "хвост" по первому вхождению разделителя Delim
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="Mode">Режим работы команды</param>
              void UnpackFirst(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence) const
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Команда UnpackEntry. Позволяет подать команду, осуществляющую разбиение строки Source на "голову" и "хвост" по последнему вхождению разделителя Delim
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="Mode">Режим работы команды</param>
              void UnpackLast(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence) const
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события GetLength по адресу
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void SendGetLength(address target, const string & source)
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetLength самому себе
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void RaiseGetLength(const string & source)
              {
                G1::GetLength cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetLengthAnswer по адресу
              /// </summary>
              /// <param name="result">Длина строки</param>
              void SendGetLengthAnswer(address target, int result)
              {
                G1::GetLengthAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetLengthAnswer самому себе
              /// </summary>
              /// <param name="result">Длина строки</param>
              void RaiseGetLengthAnswer(int result)
              {
                G1::GetLengthAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события MatchFormat по адресу
              /// </summary>
              /// <param name="format">Формат сопоставления</param>
              /// <param name="source">Исходная строка</param>
              void SendMatchFormat(address target, const string & format, const string & source)
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события MatchFormat самому себе
              /// </summary>
              /// <param name="format">Формат сопоставления</param>
              /// <param name="source">Исходная строка</param>
              void RaiseMatchFormat(const string & format, const string & source)
              {
                G1::MatchFormat cmd;
                cmd.SetFormat(format);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события MatchFormatAnswer по адресу
              /// </summary>
              /// <param name="matchResult">Успешно ли сравнение</param>
              /// <param name="result">Список строк, которые успешно прошли сопоставление с форматом</param>
              void SendMatchFormatAnswer(address target, Matching matchResult, const StringList & result)
              {
                G1::MatchFormatAnswer cmd;
                cmd.SetMatchResult(matchResult);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события MatchFormatAnswer самому себе
              /// </summary>
              /// <param name="matchResult">Успешно ли сравнение</param>
              /// <param name="result">Список строк, которые успешно прошли сопоставление с форматом</param>
              void RaiseMatchFormatAnswer(Matching matchResult, const StringList & result)
              {
                G1::MatchFormatAnswer cmd;
                cmd.SetMatchResult(matchResult);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ReplaceAll по адресу
              /// </summary>
              /// <param name="pattern">Строка для поиска</param>
              /// <param name="source">Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">Строка для вставки</param>
              void SendReplaceAll(address target, const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ReplaceAll самому себе
              /// </summary>
              /// <param name="pattern">Строка для поиска</param>
              /// <param name="source">Строка, в которой будет осуществляться замена вхождений подстроки Pattern значениями Value</param>
              /// <param name="value">Строка для вставки</param>
              void RaiseReplaceAll(const string & pattern, const string & source, const string & value)
              {
                G1::ReplaceAll cmd;
                cmd.SetPattern(pattern);
                cmd.SetSource(source);
                cmd.SetValue(value);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ReplaceAllAnswer по адресу
              /// </summary>
              /// <param name="result">Результат выполнения команды ReplaceAll</param>
              void SendReplaceAllAnswer(address target, const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ReplaceAllAnswer самому себе
              /// </summary>
              /// <param name="result">Результат выполнения команды ReplaceAll</param>
              void RaiseReplaceAllAnswer(const string & result)
              {
                G1::ReplaceAllAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Split по адресу
              /// </summary>
              /// <param name="delim">Символ или последовательность символов, которые служат разделителем</param>
              /// <param name="source">Строка, которая будет разбиваться</param>
              /// <param name="allowEmpty">Допускаются ли пустые строки в ответе</param>
              /// <param name="mode">Режим работы команды</param>
              void SendSplit(address target, const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf)
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Split самому себе
              /// </summary>
              /// <param name="delim">Символ или последовательность символов, которые служат разделителем</param>
              /// <param name="source">Строка, которая будет разбиваться</param>
              /// <param name="allowEmpty">Допускаются ли пустые строки в ответе</param>
              /// <param name="mode">Режим работы команды</param>
              void RaiseSplit(const string & delim, const string & source, bool allowEmpty = false, DelimMode mode = (DelimMode)DelimMode::AnyOf)
              {
                G1::Split cmd;
                cmd.SetAllowEmpty(allowEmpty);
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события SplitAnswer по адресу
              /// </summary>
              /// <param name="result">Результат выполнения команды Split</param>
              void SendSplitAnswer(address target, const StringList & result)
              {
                G1::SplitAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события SplitAnswer самому себе
              /// </summary>
              /// <param name="result">Результат выполнения команды Split</param>
              void RaiseSplitAnswer(const StringList & result)
              {
                G1::SplitAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события Trim по адресу
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void SendTrim(address target, const string & source)
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Trim самому себе
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void RaiseTrim(const string & source)
              {
                G1::Trim cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события TrimAnswer по адресу
              /// </summary>
              /// <param name="result">Результат выполнения команды Trim</param>
              void SendTrimAnswer(address target, const string & result)
              {
                G1::TrimAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события TrimAnswer самому себе
              /// </summary>
              /// <param name="result">Результат выполнения команды Trim</param>
              void RaiseTrimAnswer(const string & result)
              {
                G1::TrimAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события TrimLeft по адресу
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void SendTrimLeft(address target, const string & source)
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события TrimLeft самому себе
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void RaiseTrimLeft(const string & source)
              {
                G1::TrimLeft cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события TrimLeftAnswer по адресу
              /// </summary>
              /// <param name="result">Результат выполнения команды TrimLeft</param>
              void SendTrimLeftAnswer(address target, const string & result)
              {
                G1::TrimLeftAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события TrimLeftAnswer самому себе
              /// </summary>
              /// <param name="result">Результат выполнения команды TrimLeft</param>
              void RaiseTrimLeftAnswer(const string & result)
              {
                G1::TrimLeftAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события TrimRight по адресу
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void SendTrimRight(address target, const string & source)
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события TrimRight самому себе
              /// </summary>
              /// <param name="source">Исходная строка</param>
              void RaiseTrimRight(const string & source)
              {
                G1::TrimRight cmd;
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события TrimRightAnswer по адресу
              /// </summary>
              /// <param name="result">Результат выполнения команды TrimRight</param>
              void SendTrimRightAnswer(address target, const string & result)
              {
                G1::TrimRightAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события TrimRightAnswer самому себе
              /// </summary>
              /// <param name="result">Результат выполнения команды TrimRight</param>
              void RaiseTrimRightAnswer(const string & result)
              {
                G1::TrimRightAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события UnpackFirst по адресу
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="mode">Режим работы команды</param>
              void SendUnpackFirst(address target, const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UnpackFirst самому себе
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="mode">Режим работы команды</param>
              void RaiseUnpackFirst(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackFirst cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события UnpackFirstAnswer по адресу
              /// </summary>
              /// <param name="head">Головная часть строки</param>
              /// <param name="status">Флаг выполнения команды UnpackFirst</param>
              /// <param name="tail">Хвостовая часть строки</param>
              void SendUnpackFirstAnswer(address target, const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackFirstAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UnpackFirstAnswer самому себе
              /// </summary>
              /// <param name="head">Головная часть строки</param>
              /// <param name="status">Флаг выполнения команды UnpackFirst</param>
              /// <param name="tail">Хвостовая часть строки</param>
              void RaiseUnpackFirstAnswer(const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackFirstAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события UnpackLast по адресу
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="mode">Режим работы команды</param>
              void SendUnpackLast(address target, const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UnpackLast самому себе
              /// </summary>
              /// <param name="delim">Символ-разделитель</param>
              /// <param name="source">Строка для разбиения</param>
              /// <param name="mode">Режим работы команды</param>
              void RaiseUnpackLast(const string & delim, const string & source, DelimMode mode = (DelimMode)DelimMode::Sequence)
              {
                G1::UnpackLast cmd;
                cmd.SetDelim(delim);
                cmd.SetMode(mode);
                cmd.SetSource(source);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события UnpackLastAnswer по адресу
              /// </summary>
              /// <param name="head">Головная часть строки</param>
              /// <param name="status">| Флаг выполнения команды UnpackLast</param>
              /// <param name="tail">Хвостовая часть строки</param>
              void SendUnpackLastAnswer(address target, const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackLastAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события UnpackLastAnswer самому себе
              /// </summary>
              /// <param name="head">Головная часть строки</param>
              /// <param name="status">| Флаг выполнения команды UnpackLast</param>
              /// <param name="tail">Хвостовая часть строки</param>
              void RaiseUnpackLastAnswer(const string & head, UnpackAnswerStatus status, const string & tail)
              {
                G1::UnpackLastAnswer cmd;
                cmd.SetHead(head);
                cmd.SetStatus(status);
                cmd.SetTail(tail);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // пространство имен Protocol
        } // пространство имен System
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
