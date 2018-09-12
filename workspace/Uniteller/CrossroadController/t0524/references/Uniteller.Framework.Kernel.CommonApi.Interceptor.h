// Uniteller.Framework.Kernel.CommonApi.Interceptor

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
      namespace CommonApi
      {
        namespace Interceptor
        {
          namespace Protocol
          {

            BEGIN_PROTOCOL(23, 1)
              
              #pragma region Enumerations
              /// <summary> 
              /// Функции, которые может перехватить перехватчик
              /// </summary>
              enum class InterceptedFunctions
              {
                CloseHandle = 1, // Функция WinApi CloseHandle
                CreateEvent = 7, // Функция WinApi CreateEvent
                CreatePipe = 4, // Функция WinApi CreatePipe
                GetLastError = 2, // Функция WinApi GetLastError
                InvalidHandleTest = 12, // Тест неверного обращения с Handle
                LeakTest = 11, // Тест утечки
                PeekNamedPipe = 5, // Функция WinApi PeekNamedPipe
                ReadFile = 6, // Функция WinApi ReadFile
                ResetEvent = 9, // Функция WinApi ResetEvent
                SetEvent = 8, // Функция WinApi SetEvent
                WaitForMultipleObjects = 3, // Функция WinApi WaitForMultipleObjects
                WaitForSingleObject = 10, // Функция WinApi WaitForSingleObject
                WriteFile = 13 // Функция WinApi WriteFile
              };
              
              /// <summary>
              /// Валидатор корректности значения для перечислимого типа InterceptedFunctions
              /// </summary>
              inline bool IsValidInterceptedFunctionsValue(const int value)
              {
                return ((value >= 1)&&(value < 14));
              }
              
              /// <summary>
              /// Следует использовать для преобразования числовых значений к перечислимому типу InterceptedFunctions
              /// </summary>
              inline InterceptedFunctions ConvertToInterceptedFunctions(const int value)
              {
                switch (value)
                {
                  case 1:
                    return InterceptedFunctions::CloseHandle;
                  case 7:
                    return InterceptedFunctions::CreateEvent;
                  case 4:
                    return InterceptedFunctions::CreatePipe;
                  case 2:
                    return InterceptedFunctions::GetLastError;
                  case 12:
                    return InterceptedFunctions::InvalidHandleTest;
                  case 11:
                    return InterceptedFunctions::LeakTest;
                  case 5:
                    return InterceptedFunctions::PeekNamedPipe;
                  case 6:
                    return InterceptedFunctions::ReadFile;
                  case 9:
                    return InterceptedFunctions::ResetEvent;
                  case 8:
                    return InterceptedFunctions::SetEvent;
                  case 3:
                    return InterceptedFunctions::WaitForMultipleObjects;
                  case 10:
                    return InterceptedFunctions::WaitForSingleObject;
                  case 13:
                    return InterceptedFunctions::WriteFile;
                  default: throw KernelException("Невозможно преобразовать числовое значение %d к типу InterceptedFunctions", value);
                  }
              }
              
              #pragma endregion
              
              //Структуры
              #pragma region Messages and wrappers
              
              //Сообщения
              // Приходит в момент обнаружения ошибки работы с handle (попытка освобождения уже освобожденного ресурса)
              BEGIN_MESSAGE(AlreadyReleasedHandle,26,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // AlreadyReleasedHandle

              // Присылается в момент перехвата вызвова функции CloseHandle
              BEGIN_MESSAGE(CloseHandleIntercepted,3,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Закрываемый Handle
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // CloseHandleIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции CloseHandle
              BEGIN_MESSAGE(CloseHandleInterceptedAnswer,4,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Удалось ли удалить объект
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CloseHandleInterceptedAnswer

              // Присылается после успешного срабатывания тестирующего метода и возврата из тестируемой функции
              BEGIN_MESSAGE(CompletedTest,2,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Возвращенные параметры
                ARGUMENT(0, StringList, Parameters);
                // - Результат теста
                ARGUMENT(1, int, Result);
              END_MESSAGE(); // CompletedTest

              // Присылается в момент перехвата вызвова функции CreateEvent
              BEGIN_MESSAGE(CreateEventIntercepted,13,4)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Найден ли такой Event по имени
                ARGUMENT(0, bool, AlreadyExist);
                // - Начальное состояние
                ARGUMENT(1, bool, InitialState);
                // - Ручная переустановка
                ARGUMENT(2, bool, ManualReset);
                // - Имя
                ARGUMENT(3, string, Name);
              END_MESSAGE(); // CreateEventIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции CreateEvent
              BEGIN_MESSAGE(CreateEventInterceptedAnswer,14,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetAllocHandle(true);
                }
                // - Разрешить ли распределение Handle события
                ARGUMENT(0, bool, AllocHandle);
              END_MESSAGE(); // CreateEventInterceptedAnswer

              // Команда на распределение handle
              BEGIN_MESSAGE(CreateHandle,21,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Отладочная информация (используется для определения причины утечек памяти)
                ARGUMENT(0, string, DebugInfo);
              END_MESSAGE(); // CreateHandle

              // Ответ на команду на распределение handle
              BEGIN_MESSAGE(CreateHandleAnswer,22,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Распределенный handle
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // CreateHandleAnswer

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции CreatePipe
              BEGIN_MESSAGE(CreatePipeInterceptedAnswer,8,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Удалось ли создать
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreatePipeInterceptedAnswer

              // Позволяет подключить режим контроль утечек памяти
              BEGIN_MESSAGE(EnableLeaksControl,24,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Модуль (обычно модуль-интерцептор) распределяющий ресурсы
                ARGUMENT(0, string, Module);
              END_MESSAGE(); // EnableLeaksControl

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции GetLastError
              BEGIN_MESSAGE(GetLastErrorInterceptedAnswer,5,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Код ошибки
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // GetLastErrorInterceptedAnswer

              // Приходит в момент обнаружения ошибки работы с handle (использование)
              BEGIN_MESSAGE(InvalidHandle,25,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // InvalidHandle

              // Информация об утечках памяти
              BEGIN_MESSAGE(LeaksInformation,23,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Число обнаруженых ошибок (утечек handle)
                ARGUMENT(0, int, HandleLeaksCount);
                // - Информация об утечках памяти
                ARGUMENT(1, StringList, LeaksData);
                // - Обнаружены ли утечки
                ARGUMENT(2, bool, LeaksDetected);
              END_MESSAGE(); // LeaksInformation

              // Присылается в момент перехвата вызвова функции PeekNamedPipe
              BEGIN_MESSAGE(PeekNamedPipeIntercepted,9,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Размер буфера
                ARGUMENT(0, int, BufferSize);
                // - Handle пайпа
                ARGUMENT(1, int, PipeHandle);
              END_MESSAGE(); // PeekNamedPipeIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции PeekNamedPipe
              BEGIN_MESSAGE(PeekNamedPipeInterceptedAnswer,10,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Доступно байт для чтения (Всего)
                ARGUMENT(0, int, BytesAvail);
                // - Имеющиеся данные (считанные)
                ARGUMENT(1, string, Data);
                // - Удачен ли вызов
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // PeekNamedPipeInterceptedAnswer

              // Присылается в момент перехвата вызвова функции ReadFile
              BEGIN_MESSAGE(ReadFileIntercepted,11,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle для чтения
                ARGUMENT(0, int, Handle);
                // - Указатель на структуру Overlapped
                ARGUMENT(1, int, Overlapped);
                // - Число байт для чтения
                ARGUMENT(2, int, ToRead);
              END_MESSAGE(); // ReadFileIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции ReadFile
              BEGIN_MESSAGE(ReadFileInterceptedAnswer,12,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Считанные данные
                ARGUMENT(0, string, Data);
                // - Удачен ли вызов
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // ReadFileInterceptedAnswer

              // Присылается в момент перехвата вызвова функции ResetEvent
              BEGIN_MESSAGE(ResetEventIntercepted,17,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle события
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // ResetEventIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции ResetEvent
              BEGIN_MESSAGE(ResetEventInterceptedAnswer,18,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - Удачен ли вызов
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // ResetEventInterceptedAnswer

              // Присылается в момент перехвата вызвова функции SetEvent
              BEGIN_MESSAGE(SetEventIntercepted,15,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Handle события
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // SetEventIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции SetEvent
              BEGIN_MESSAGE(SetEventInterceptedAnswer,16,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - Удачен ли вызов
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetEventInterceptedAnswer

              // Инициирует тестирование перехваченной функции
              BEGIN_MESSAGE(TestInterceptedFunc,1,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Функция для тестирования перехватчика
                ENUM(0, InterceptedFunctions, Func);
              END_MESSAGE(); // TestInterceptedFunc

              // Присылается в момент перехвата вызвова функции WaitForMultipleObjects
              BEGIN_MESSAGE(WaitForMultipleObjectsIntercepted,6,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Число объектов для ожидания
                ARGUMENT(0, int, Count);
                // - Тайм-аут для ожидания
                ARGUMENT(1, int, Milliseconds);
                // - Ждать ли всех
                ARGUMENT(2, bool, WaitAll);
              END_MESSAGE(); // WaitForMultipleObjectsIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции WaitForMultipleObjects
              BEGIN_MESSAGE(WaitForMultipleObjectsInterceptedAnswer,7,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Ответ для WaitForMultipleObjects (причина возврата)
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // WaitForMultipleObjectsInterceptedAnswer

              // Присылается в момент перехвата вызвова функции WaitForSingleObject
              BEGIN_MESSAGE(WaitForSingleObjectIntercepted,19,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Тайм-аут для ожидания
                ARGUMENT(0, int, Milliseconds);
                // - Объект для ожидания
                ARGUMENT(1, int, Object);
              END_MESSAGE(); // WaitForSingleObjectIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции WaitForSingleObject
              BEGIN_MESSAGE(WaitForSingleObjectInterceptedAnswer,20,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Ответ для WaitForSingleObject (причина возврата)
                ARGUMENT(0, int, Result);
              END_MESSAGE(); // WaitForSingleObjectInterceptedAnswer

              // Приходит в момент перехвата функции WriteFile
              BEGIN_MESSAGE(WriteFileIntercepted,27,4)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Буфер
                ARGUMENT(0, ByteVector, Buffer);
                void SetBuffer(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
                // - Число байт для записи
                ARGUMENT(1, int, BytesToWrite);
                // - Handle файла
                ARGUMENT(2, int, FileHandle);
                // - Буфер в HEX
                ARGUMENT(3, string, HexBuffer);
              END_MESSAGE(); // WriteFileIntercepted

              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции WriteFileIntercepted
              BEGIN_MESSAGE(WriteFileInterceptedAnswer,28,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetResult(true);
                }
                // - Число записанных данных
                ARGUMENT(0, int, BytesWritten);
                // - Удачен ли вызов
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // WriteFileInterceptedAnswer

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// Приходит в момент обнаружения ошибки работы с handle (попытка освобождения уже освобожденного ресурса)
                /// </summary>
                void AlreadyReleasedHandle() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::AlreadyReleasedHandle);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции CloseHandle
                /// </summary>
                /// <param name="handle">- Закрываемый Handle</param>
                void CloseHandleIntercepted(int handle) const
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается после успешного срабатывания тестирующего метода и возврата из тестируемой функции
                /// </summary>
                /// <param name="parameters">- Возвращенные параметры</param>
                /// <param name="result">- Результат теста</param>
                void CompletedTest(const StringList & parameters, int result) const
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции CreateEvent
                /// </summary>
                /// <param name="alreadyExist">- Найден ли такой Event по имени</param>
                /// <param name="initialState">- Начальное состояние</param>
                /// <param name="manualReset">- Ручная переустановка</param>
                /// <param name="name">- Имя</param>
                void CreateEventIntercepted(bool alreadyExist, bool initialState, bool manualReset, const string & name) const
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Команда на распределение handle
                /// </summary>
                /// <param name="debugInfo">- Отладочная информация (используется для определения причины утечек памяти)</param>
                void CreateHandle(const string & debugInfo) const
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Позволяет подключить режим контроль утечек памяти
                /// </summary>
                /// <param name="module">- Модуль (обычно модуль-интерцептор), распределяющий ресурсы</param>
                void EnableLeaksControl(const string & module) const
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Приходит в момент обнаружения ошибки работы с handle (использование)
                /// </summary>
                void InvalidHandle() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InvalidHandle);
                }
                
                /// <summary> 
                /// Информация об утечках памяти
                /// </summary>
                /// <param name="handleLeaksCount">- Число обнаруженых ошибок (утечек handle)</param>
                /// <param name="leaksData">- Информация об утечках памяти</param>
                /// <param name="leaksDetected">- Обнаружены ли утечки</param>
                void LeaksInformation(int handleLeaksCount, const StringList & leaksData, bool leaksDetected) const
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции PeekNamedPipe
                /// </summary>
                /// <param name="bufferSize">- Размер буфера</param>
                /// <param name="pipeHandle">- Handle пайпа</param>
                void PeekNamedPipeIntercepted(int bufferSize, int pipeHandle) const
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции ReadFile
                /// </summary>
                /// <param name="handle">- Handle для чтения</param>
                /// <param name="overlapped">- Указатель на структуру Overlapped</param>
                /// <param name="toRead">- Число байт для чтения</param>
                void ReadFileIntercepted(int handle, int overlapped, int toRead) const
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции ResetEvent
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void ResetEventIntercepted(int handle) const
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции SetEvent
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void SetEventIntercepted(int handle) const
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестирование перехваченной функции
                /// </summary>
                /// <param name="func">- Функция для тестирования перехватчика</param>
                void TestInterceptedFunc(InterceptedFunctions func) const
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции WaitForMultipleObjects
                /// </summary>
                /// <param name="count">- Число объектов для ожидания</param>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="waitAll">- Ждать ли всех</param>
                void WaitForMultipleObjectsIntercepted(int count, int milliseconds, bool waitAll) const
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Присылается в момент перехвата вызвова функции WaitForSingleObject
                /// </summary>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="object">- Объект для ожидания</param>
                void WaitForSingleObjectIntercepted(int milliseconds, int object) const
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Приходит в момент перехвата функции WriteFile
                /// </summary>
                /// <param name="buffer">- Буфер</param>
                /// <param name="bytesToWrite">- Число байт для записи</param>
                /// <param name="fileHandle">- Handle файла</param>
                /// <param name="hexBuffer">- Буфер в HEX</param>
                void WriteFileIntercepted(const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer) const
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// Отправка события AlreadyReleasedHandle по адресу
                /// </summary>
                void SendAlreadyReleasedHandle(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::AlreadyReleasedHandle);
                }
                /// <summary> 
                /// Отправка события AlreadyReleasedHandle самому себе
                /// </summary>
                void RaiseAlreadyReleasedHandle()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::AlreadyReleasedHandle);
                }
                
                /// <summary> 
                /// Отправка события CloseHandleIntercepted по адресу
                /// </summary>
                /// <param name="handle">- Закрываемый Handle</param>
                void SendCloseHandleIntercepted(address target, int handle)
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CloseHandleIntercepted самому себе
                /// </summary>
                /// <param name="handle">- Закрываемый Handle</param>
                void RaiseCloseHandleIntercepted(int handle)
                {
                  G1::CloseHandleIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CloseHandleInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Удалось ли удалить объект</param>
                void SendCloseHandleInterceptedAnswer(address target, bool result)
                {
                  G1::CloseHandleInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CloseHandleInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Удалось ли удалить объект</param>
                void RaiseCloseHandleInterceptedAnswer(bool result)
                {
                  G1::CloseHandleInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CompletedTest по адресу
                /// </summary>
                /// <param name="parameters">- Возвращенные параметры</param>
                /// <param name="result">- Результат теста</param>
                void SendCompletedTest(address target, const StringList & parameters, int result)
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CompletedTest самому себе
                /// </summary>
                /// <param name="parameters">- Возвращенные параметры</param>
                /// <param name="result">- Результат теста</param>
                void RaiseCompletedTest(const StringList & parameters, int result)
                {
                  G1::CompletedTest cmd;
                  cmd.SetParameters(parameters);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateEventIntercepted по адресу
                /// </summary>
                /// <param name="alreadyExist">- Найден ли такой Event по имени</param>
                /// <param name="initialState">- Начальное состояние</param>
                /// <param name="manualReset">- Ручная переустановка</param>
                /// <param name="name">- Имя</param>
                void SendCreateEventIntercepted(address target, bool alreadyExist, bool initialState, bool manualReset, const string & name)
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateEventIntercepted самому себе
                /// </summary>
                /// <param name="alreadyExist">- Найден ли такой Event по имени</param>
                /// <param name="initialState">- Начальное состояние</param>
                /// <param name="manualReset">- Ручная переустановка</param>
                /// <param name="name">- Имя</param>
                void RaiseCreateEventIntercepted(bool alreadyExist, bool initialState, bool manualReset, const string & name)
                {
                  G1::CreateEventIntercepted cmd;
                  cmd.SetAlreadyExist(alreadyExist);
                  cmd.SetInitialState(initialState);
                  cmd.SetManualReset(manualReset);
                  cmd.SetName(name);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateEventInterceptedAnswer по адресу
                /// </summary>
                /// <param name="allocHandle">- Разрешить ли распределение Handle события</param>
                void SendCreateEventInterceptedAnswer(address target, bool allocHandle = true)
                {
                  G1::CreateEventInterceptedAnswer cmd;
                  cmd.SetAllocHandle(allocHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateEventInterceptedAnswer самому себе
                /// </summary>
                /// <param name="allocHandle">- Разрешить ли распределение Handle события</param>
                void RaiseCreateEventInterceptedAnswer(bool allocHandle = true)
                {
                  G1::CreateEventInterceptedAnswer cmd;
                  cmd.SetAllocHandle(allocHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateHandle по адресу
                /// </summary>
                /// <param name="debugInfo">- Отладочная информация (используется для определения причины утечек памяти)</param>
                void SendCreateHandle(address target, const string & debugInfo)
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateHandle самому себе
                /// </summary>
                /// <param name="debugInfo">- Отладочная информация (используется для определения причины утечек памяти)</param>
                void RaiseCreateHandle(const string & debugInfo)
                {
                  G1::CreateHandle cmd;
                  cmd.SetDebugInfo(debugInfo);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateHandleAnswer по адресу
                /// </summary>
                /// <param name="result">- Распределенный handle</param>
                void SendCreateHandleAnswer(address target, int result)
                {
                  G1::CreateHandleAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateHandleAnswer самому себе
                /// </summary>
                /// <param name="result">- Распределенный handle</param>
                void RaiseCreateHandleAnswer(int result)
                {
                  G1::CreateHandleAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreatePipeInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Удалось ли создать</param>
                void SendCreatePipeInterceptedAnswer(address target, bool result)
                {
                  G1::CreatePipeInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreatePipeInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Удалось ли создать</param>
                void RaiseCreatePipeInterceptedAnswer(bool result)
                {
                  G1::CreatePipeInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события EnableLeaksControl по адресу
                /// </summary>
                /// <param name="module">- Модуль (обычно модуль-интерцептор), распределяющий ресурсы</param>
                void SendEnableLeaksControl(address target, const string & module)
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события EnableLeaksControl самому себе
                /// </summary>
                /// <param name="module">- Модуль (обычно модуль-интерцептор), распределяющий ресурсы</param>
                void RaiseEnableLeaksControl(const string & module)
                {
                  G1::EnableLeaksControl cmd;
                  cmd.SetModule(module);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetLastErrorInterceptedAnswer по адресу
                /// </summary>
                /// <param name="code">- Код ошибки</param>
                void SendGetLastErrorInterceptedAnswer(address target, int code)
                {
                  G1::GetLastErrorInterceptedAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetLastErrorInterceptedAnswer самому себе
                /// </summary>
                /// <param name="code">- Код ошибки</param>
                void RaiseGetLastErrorInterceptedAnswer(int code)
                {
                  G1::GetLastErrorInterceptedAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события InvalidHandle по адресу
                /// </summary>
                void SendInvalidHandle(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::InvalidHandle);
                }
                /// <summary> 
                /// Отправка события InvalidHandle самому себе
                /// </summary>
                void RaiseInvalidHandle()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::InvalidHandle);
                }
                
                /// <summary> 
                /// Отправка события LeaksInformation по адресу
                /// </summary>
                /// <param name="handleLeaksCount">- Число обнаруженых ошибок (утечек handle)</param>
                /// <param name="leaksData">- Информация об утечках памяти</param>
                /// <param name="leaksDetected">- Обнаружены ли утечки</param>
                void SendLeaksInformation(address target, int handleLeaksCount, const StringList & leaksData, bool leaksDetected)
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события LeaksInformation самому себе
                /// </summary>
                /// <param name="handleLeaksCount">- Число обнаруженых ошибок (утечек handle)</param>
                /// <param name="leaksData">- Информация об утечках памяти</param>
                /// <param name="leaksDetected">- Обнаружены ли утечки</param>
                void RaiseLeaksInformation(int handleLeaksCount, const StringList & leaksData, bool leaksDetected)
                {
                  G1::LeaksInformation cmd;
                  cmd.SetHandleLeaksCount(handleLeaksCount);
                  cmd.SetLeaksData(leaksData);
                  cmd.SetLeaksDetected(leaksDetected);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PeekNamedPipeIntercepted по адресу
                /// </summary>
                /// <param name="bufferSize">- Размер буфера</param>
                /// <param name="pipeHandle">- Handle пайпа</param>
                void SendPeekNamedPipeIntercepted(address target, int bufferSize, int pipeHandle)
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PeekNamedPipeIntercepted самому себе
                /// </summary>
                /// <param name="bufferSize">- Размер буфера</param>
                /// <param name="pipeHandle">- Handle пайпа</param>
                void RaisePeekNamedPipeIntercepted(int bufferSize, int pipeHandle)
                {
                  G1::PeekNamedPipeIntercepted cmd;
                  cmd.SetBufferSize(bufferSize);
                  cmd.SetPipeHandle(pipeHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PeekNamedPipeInterceptedAnswer по адресу
                /// </summary>
                /// <param name="bytesAvail">- Доступно байт для чтения (Всего)</param>
                /// <param name="data">- Имеющиеся данные (считанные)</param>
                /// <param name="result">- Удачен ли вызов</param>
                void SendPeekNamedPipeInterceptedAnswer(address target, int bytesAvail, const string & data, bool result)
                {
                  G1::PeekNamedPipeInterceptedAnswer cmd;
                  cmd.SetBytesAvail(bytesAvail);
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PeekNamedPipeInterceptedAnswer самому себе
                /// </summary>
                /// <param name="bytesAvail">- Доступно байт для чтения (Всего)</param>
                /// <param name="data">- Имеющиеся данные (считанные)</param>
                /// <param name="result">- Удачен ли вызов</param>
                void RaisePeekNamedPipeInterceptedAnswer(int bytesAvail, const string & data, bool result)
                {
                  G1::PeekNamedPipeInterceptedAnswer cmd;
                  cmd.SetBytesAvail(bytesAvail);
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события ReadFileIntercepted по адресу
                /// </summary>
                /// <param name="handle">- Handle для чтения</param>
                /// <param name="overlapped">- Указатель на структуру Overlapped</param>
                /// <param name="toRead">- Число байт для чтения</param>
                void SendReadFileIntercepted(address target, int handle, int overlapped, int toRead)
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ReadFileIntercepted самому себе
                /// </summary>
                /// <param name="handle">- Handle для чтения</param>
                /// <param name="overlapped">- Указатель на структуру Overlapped</param>
                /// <param name="toRead">- Число байт для чтения</param>
                void RaiseReadFileIntercepted(int handle, int overlapped, int toRead)
                {
                  G1::ReadFileIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetOverlapped(overlapped);
                  cmd.SetToRead(toRead);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события ReadFileInterceptedAnswer по адресу
                /// </summary>
                /// <param name="data">- Считанные данные</param>
                /// <param name="result">- Удачен ли вызов</param>
                void SendReadFileInterceptedAnswer(address target, const string & data, bool result)
                {
                  G1::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ReadFileInterceptedAnswer самому себе
                /// </summary>
                /// <param name="data">- Считанные данные</param>
                /// <param name="result">- Удачен ли вызов</param>
                void RaiseReadFileInterceptedAnswer(const string & data, bool result)
                {
                  G1::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события ResetEventIntercepted по адресу
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void SendResetEventIntercepted(address target, int handle)
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ResetEventIntercepted самому себе
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void RaiseResetEventIntercepted(int handle)
                {
                  G1::ResetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события ResetEventInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Удачен ли вызов</param>
                void SendResetEventInterceptedAnswer(address target, bool result = true)
                {
                  G1::ResetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ResetEventInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Удачен ли вызов</param>
                void RaiseResetEventInterceptedAnswer(bool result = true)
                {
                  G1::ResetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetEventIntercepted по адресу
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void SendSetEventIntercepted(address target, int handle)
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetEventIntercepted самому себе
                /// </summary>
                /// <param name="handle">- Handle события</param>
                void RaiseSetEventIntercepted(int handle)
                {
                  G1::SetEventIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetEventInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Удачен ли вызов</param>
                void SendSetEventInterceptedAnswer(address target, bool result = true)
                {
                  G1::SetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetEventInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Удачен ли вызов</param>
                void RaiseSetEventInterceptedAnswer(bool result = true)
                {
                  G1::SetEventInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestInterceptedFunc по адресу
                /// </summary>
                /// <param name="func">- Функция для тестирования перехватчика</param>
                void SendTestInterceptedFunc(address target, InterceptedFunctions func)
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestInterceptedFunc самому себе
                /// </summary>
                /// <param name="func">- Функция для тестирования перехватчика</param>
                void RaiseTestInterceptedFunc(InterceptedFunctions func)
                {
                  G1::TestInterceptedFunc cmd;
                  cmd.SetFunc(func);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WaitForMultipleObjectsIntercepted по адресу
                /// </summary>
                /// <param name="count">- Число объектов для ожидания</param>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="waitAll">- Ждать ли всех</param>
                void SendWaitForMultipleObjectsIntercepted(address target, int count, int milliseconds, bool waitAll)
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WaitForMultipleObjectsIntercepted самому себе
                /// </summary>
                /// <param name="count">- Число объектов для ожидания</param>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="waitAll">- Ждать ли всех</param>
                void RaiseWaitForMultipleObjectsIntercepted(int count, int milliseconds, bool waitAll)
                {
                  G1::WaitForMultipleObjectsIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetWaitAll(waitAll);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WaitForMultipleObjectsInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Ответ для WaitForMultipleObjects (причина возврата)</param>
                void SendWaitForMultipleObjectsInterceptedAnswer(address target, int result)
                {
                  G1::WaitForMultipleObjectsInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WaitForMultipleObjectsInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Ответ для WaitForMultipleObjects (причина возврата)</param>
                void RaiseWaitForMultipleObjectsInterceptedAnswer(int result)
                {
                  G1::WaitForMultipleObjectsInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WaitForSingleObjectIntercepted по адресу
                /// </summary>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="object">- Объект для ожидания</param>
                void SendWaitForSingleObjectIntercepted(address target, int milliseconds, int object)
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WaitForSingleObjectIntercepted самому себе
                /// </summary>
                /// <param name="milliseconds">- Тайм-аут для ожидания</param>
                /// <param name="object">- Объект для ожидания</param>
                void RaiseWaitForSingleObjectIntercepted(int milliseconds, int object)
                {
                  G1::WaitForSingleObjectIntercepted cmd;
                  cmd.SetMilliseconds(milliseconds);
                  cmd.SetObject(object);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WaitForSingleObjectInterceptedAnswer по адресу
                /// </summary>
                /// <param name="result">- Ответ для WaitForSingleObject (причина возврата)</param>
                void SendWaitForSingleObjectInterceptedAnswer(address target, int result)
                {
                  G1::WaitForSingleObjectInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WaitForSingleObjectInterceptedAnswer самому себе
                /// </summary>
                /// <param name="result">- Ответ для WaitForSingleObject (причина возврата)</param>
                void RaiseWaitForSingleObjectInterceptedAnswer(int result)
                {
                  G1::WaitForSingleObjectInterceptedAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WriteFileIntercepted по адресу
                /// </summary>
                /// <param name="buffer">- Буфер</param>
                /// <param name="bytesToWrite">- Число байт для записи</param>
                /// <param name="fileHandle">- Handle файла</param>
                /// <param name="hexBuffer">- Буфер в HEX</param>
                void SendWriteFileIntercepted(address target, const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer)
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WriteFileIntercepted самому себе
                /// </summary>
                /// <param name="buffer">- Буфер</param>
                /// <param name="bytesToWrite">- Число байт для записи</param>
                /// <param name="fileHandle">- Handle файла</param>
                /// <param name="hexBuffer">- Буфер в HEX</param>
                void RaiseWriteFileIntercepted(const ByteVector & buffer, int bytesToWrite, int fileHandle, const string & hexBuffer)
                {
                  G1::WriteFileIntercepted cmd;
                  cmd.SetBuffer(buffer);
                  cmd.SetBytesToWrite(bytesToWrite);
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetHexBuffer(hexBuffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события WriteFileInterceptedAnswer по адресу
                /// </summary>
                /// <param name="bytesWritten">- Число записанных данных</param>
                /// <param name="result">- Удачен ли вызов</param>
                void SendWriteFileInterceptedAnswer(address target, int bytesWritten, bool result = true)
                {
                  G1::WriteFileInterceptedAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события WriteFileInterceptedAnswer самому себе
                /// </summary>
                /// <param name="bytesWritten">- Число записанных данных</param>
                /// <param name="result">- Удачен ли вызов</param>
                void RaiseWriteFileInterceptedAnswer(int bytesWritten, bool result = true)
                {
                  G1::WriteFileInterceptedAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            

            BEGIN_PROTOCOL(23, 2)
              
              #pragma region Enumerations
              /// <summary> 
              /// Функции, которые может перехватить перехватчик
              /// </summary>
              #pragma endregion
              
              //Структуры
              #pragma region Messages and wrappers
              
              //Сообщения
              // Присылается из скрипта тестирования в ответ на сообщение о вызове перехваченной функции ReadFile
              BEGIN_MESSAGE(ReadFileInterceptedAnswer,12,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Считанные данные
                ARGUMENT(0, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
                // - Удачен ли вызов
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // ReadFileInterceptedAnswer

              
              BEGIN_WRAPPER()
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// Отправка события ReadFileInterceptedAnswer по адресу
                /// </summary>
                /// <param name="data">- Считанные данные</param>
                /// <param name="result">- Удачен ли вызов</param>
                void SendReadFileInterceptedAnswer(address target, const ByteVector & data, bool result)
                {
                  G2::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ReadFileInterceptedAnswer самому себе
                /// </summary>
                /// <param name="data">- Считанные данные</param>
                /// <param name="result">- Удачен ли вызов</param>
                void RaiseReadFileInterceptedAnswer(const ByteVector & data, bool result)
                {
                  G2::ReadFileInterceptedAnswer cmd;
                  cmd.SetData(data);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            
            } // пространство имен Protocol
          } // пространство имен Interceptor
        } // пространство имен CommonApi
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
