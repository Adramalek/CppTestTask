// Uniteller.Framework.Kernel.FileSystem.Interceptor

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
      namespace FileSystem
      {
        namespace Interceptor
        {
          namespace Protocol
          {

            BEGIN_PROTOCOL(11, 1)
              
              #pragma region Enumerations
              /// <summary> 
              /// Специфичные ошибки при работе с файловой системой
              /// </summary>
              enum class FileSystemApiErrors
              {
                ErrorAccessDenied = 5, // Диск недоступен
                ErrorCurrentDirectory = 16, // Папка не может быть удалена
                ErrorDevNotExist = 55, // Устройство недоступно
                ErrorDiskFull = 112, // Недостаточно свободного места на диске
                ErrorFileNotFound = 2, // Файл не найден
                ErrorHandleDiskFull = 39, // Диск переполнен
                ErrorInvalidDrive = 15, // Диск не существует
                ErrorNetworkAccessDenied = 65, // Сетевой диск недоступен
                ErrorNoMoreFiles = 18, // Больше нет файлов, удовлетворяющих критерию выборки
                ErrorPathNotFound = 3 // Путь к файлу не найден
              };
              
              /// <summary> 
              /// Режим чтений
              /// </summary>
              /// <summary>
              /// Валидатор корректности значения для перечислимого типа FileSystemApiErrors
              /// </summary>
              inline bool IsValidFileSystemApiErrorsValue(const int value)
              {
                return ((value >= 2)&&(value < 4)) || ((value >= 5)&&(value < 6)) || ((value >= 15)&&(value < 17)) || ((value >= 18)&&(value < 19)) || ((value >= 39)&&(value < 40)) || ((value >= 55)&&(value < 56)) || ((value >= 65)&&(value < 66)) || ((value >= 112)&&(value < 113));
              }
              
              /// <summary>
              /// Следует использовать для преобразования числовых значений к перечислимому типу FileSystemApiErrors
              /// </summary>
              inline FileSystemApiErrors ConvertToFileSystemApiErrors(const int value)
              {
                switch (value)
                {
                  case 5:
                    return FileSystemApiErrors::ErrorAccessDenied;
                  case 16:
                    return FileSystemApiErrors::ErrorCurrentDirectory;
                  case 55:
                    return FileSystemApiErrors::ErrorDevNotExist;
                  case 112:
                    return FileSystemApiErrors::ErrorDiskFull;
                  case 2:
                    return FileSystemApiErrors::ErrorFileNotFound;
                  case 39:
                    return FileSystemApiErrors::ErrorHandleDiskFull;
                  case 15:
                    return FileSystemApiErrors::ErrorInvalidDrive;
                  case 65:
                    return FileSystemApiErrors::ErrorNetworkAccessDenied;
                  case 18:
                    return FileSystemApiErrors::ErrorNoMoreFiles;
                  case 3:
                    return FileSystemApiErrors::ErrorPathNotFound;
                  default: throw KernelException("Невозможно преобразовать числовое значение %d к типу FileSystemApiErrors", value);
                  }
              }
              
              #pragma endregion
              
              #pragma region Flags
              
              /// <summary> 
              /// Константы WinAPI для файловых атрибутов
              /// </summary>
              enum class WinApiAttr
              {
                Archive = 32, //Архивный
                Folder = 16, //Папка
                Hidden = 2, //Скрытый
                Normal = 128, //Не имеет других атрибутов
                ReadOnly = 1, //Только чтение
                System = 4 //Системный
              };
              
              /// <summary>
              /// Оператор, позволяющий формировать маски для флагов WinApiAttr
              /// </summary>
              inline WinApiAttr operator|(WinApiAttr a, WinApiAttr b)
              {
                return static_cast<WinApiAttr>(static_cast<int>(a), static_cast<int>(b));
              }
              
              /// <summary>
              /// Позволяет проверить установлена ли маска mask в WinApiAttr
              /// </summary>
              /// <param name="variable">Переменная</param>
              /// <param name="mask">Маска для проверки</param>
              inline bool IsFlagSet(WinApiAttr variable, WinApiAttr mask)
              {
                int m = static_cast<int>(mask);
                return (static_cast<int>(variable) & m)==m;
              }
              
              /// <summary>
              /// Валидатор корректности значения для флага WinApiAttr
              /// </summary>
              /// <param name="value">Значение для проверки</param>
              inline bool IsValidWinApiAttrValue(const int value)
              {
                return value <= 183;
              }
              #pragma endregion
              
              //Структуры
              #pragma region Messages and wrappers
              
              //Сообщения
              // Присылается после успешного срабатывания тестирующего метода и возврата из тестируемой функции
              BEGIN_MESSAGE(CompletedTest,1,6)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetAttributes((WinApiAttr)WinApiAttr::Normal);
                  SetParamInt(0);
                  SetParamStr("");
                  SetResult(false);
                  SetTimeCreated(std::chrono::system_clock::time_point(std::chrono::milliseconds(0)));
                  SetTimeModified(std::chrono::system_clock::time_point(std::chrono::milliseconds(0)));
                }
                // Возвращаемые атрибуты
                FLAG(0, WinApiAttr, Attributes);
                // Числовой параметр
                ARGUMENT(1, int, ParamInt);
                // Строковый параметр
                ARGUMENT(2, string, ParamStr);
                // Результат работы функции он же результат теста
                ARGUMENT(3, bool, Result);
                // Дата создания
                ARGUMENT(4, timestamp_t, TimeCreated);
                // Дата изменения
                ARGUMENT(5, timestamp_t, TimeModified);
              END_MESSAGE(); // CompletedTest

              // Сообщение о перехвате вызова функции WindowsApi CopyFileA
              BEGIN_MESSAGE(CopyFileAIntercepted,27,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к целевому файлу
                ARGUMENT(0, string, PathDst);
                // Путь к копируемому файлу
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // CopyFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi CopyFileA
              BEGIN_MESSAGE(CopyFileA_Answer,28,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CopyFileA_Answer

              // Сообщение о перехвате вызова функции WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(CreateDirectoryAIntercepted,24,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // CreateDirectoryAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(CreateDirectoryA_Answer,25,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreateDirectoryA_Answer

              // Сообщение о перехвате вызова функции WindowsApi CreateFileA
              BEGIN_MESSAGE(CreateFileAIntercepted,30,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // CreateFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi CreateFileA
              BEGIN_MESSAGE(CreateFileA_Answer,31,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // CreateFileA_Answer

              // Сообщение о перехвате вызова функции WindowsApi DeleteFileA
              BEGIN_MESSAGE(DeleteFileAIntercepted,33,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // DeleteFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi DeleteFileA
              BEGIN_MESSAGE(DeleteFileA_Answer,34,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // DeleteFileA_Answer

              // Ответ на сообщение о перехвате вызова функции fclose
              BEGIN_MESSAGE(FcloseAnswer,65,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // true - файл успешно закрыт false - ошибка
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FcloseAnswer

              // Сообщение о перехвате вызова функции fclose
              BEGIN_MESSAGE(FcloseIntercepted,64,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FcloseIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi Feof
              BEGIN_MESSAGE(FeofAnswer,61,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // true - конец файла false - еще нет
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FeofAnswer

              // Сообщение о перехвате вызова функции WindowsApi Feof
              BEGIN_MESSAGE(FeofIntercepted,60,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FeofIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi FindClose
              BEGIN_MESSAGE(FindCloseAnswer,74,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // FindCloseAnswer

              // Сообщение о перехвате вызова функции WindowsApi FindClose
              BEGIN_MESSAGE(FindCloseIntercepted,73,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FindCloseIntercepted

              // Сообщение о перехвате вызова функции WindowsApi FindFirstFileA
              BEGIN_MESSAGE(FindFirstFileAIntercepted,18,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Маска поиска
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // FindFirstFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi FindFirstFileA
              BEGIN_MESSAGE(FindFirstFileA_Answer,19,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла как в WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // Название найденного файла
                ARGUMENT(1, string, Filename);
                // false - функция вернет INVALID_ARGUMENT true - вернется виртуальный хэндлер
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindFirstFileA_Answer

              // Сообщение о перехвате вызова функции WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(FindFirstFileExAIntercepted,15,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Маска поиска
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // FindFirstFileExAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(FindFirstFileExA_Answer,16,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла как в WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // Название найденного файла
                ARGUMENT(1, string, Filename);
                // false - функция вернет INVALID_ARGUMENT true - вернется виртуальный хэндлер
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindFirstFileExA_Answer

              // Сообщение о перехвате вызова функции WindowsApi FindNextFileA
              BEGIN_MESSAGE(FindNextFileAIntercepted,42,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FindNextFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi FindNextFileA
              BEGIN_MESSAGE(FindNextFileA_Answer,43,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла как в WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // Название найденного файла
                ARGUMENT(1, string, Filename);
                // Результат работы функции
                ARGUMENT(2, bool, Result);
              END_MESSAGE(); // FindNextFileA_Answer

              // Ответ на сообщение о перехвате вызова функции fopen_s
              BEGIN_MESSAGE(Fopen_sAnswer,55,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат
                ARGUMENT(0, int, Errno);
              END_MESSAGE(); // Fopen_sAnswer

              // Сообщение о перехвате вызова функции fopen_s
              BEGIN_MESSAGE(Fopen_sIntercepted,54,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Режим
                ARGUMENT(0, string, Mode);
                // Путь к файлу
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // Fopen_sIntercepted

              // Ответ на сообщение о перехвате вызова функции fread
              BEGIN_MESSAGE(FreadAnswer,58,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // прочитанные символы
                ARGUMENT(0, string, Buffer);
              END_MESSAGE(); // FreadAnswer

              // Сообщение о перехвате вызова функции fread
              BEGIN_MESSAGE(FreadIntercepted,57,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Количество элементов
                ARGUMENT(0, int, Count);
                // Файловая переменнаяия
                ARGUMENT(1, int, Handle);
                // Размер элемента
                ARGUMENT(2, int, ItemSize);
              END_MESSAGE(); // FreadIntercepted

              // Сообщение о перехвате вызова функции WindowsApi GetFileAttributesA
              BEGIN_MESSAGE(GetFileAttributesAIntercepted,51,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // GetFileAttributesAIntercepted

              // Ответ на сообщение о перехвате вызова функции GetFileAttributesA
              BEGIN_MESSAGE(GetFileAttributesA_Answer,52,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла
                FLAG(0, WinApiAttr, Attributes);
              END_MESSAGE(); // GetFileAttributesA_Answer

              // Ответ на сообщение о перехвате вызова функции WindowsApi GetFileSize
              BEGIN_MESSAGE(GetFileSizeAnswer,49,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Размер файла
                ARGUMENT(0, int, Size);
              END_MESSAGE(); // GetFileSizeAnswer

              // Сообщение о перехвате вызова функции WindowsApi GetFileSize
              BEGIN_MESSAGE(GetFileSizeIntercepted,48,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // GetFileSizeIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi GetFileTime
              BEGIN_MESSAGE(GetFileTimeAnswer,46,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
                // Дата создания файла
                ARGUMENT(1, timestamp_t, TimeCreate);
                // Дата изменения файла
                ARGUMENT(2, timestamp_t, TimeModify);
              END_MESSAGE(); // GetFileTimeAnswer

              // Сообщение о перехвате вызова функции WindowsApi GetFileTime
              BEGIN_MESSAGE(GetFileTimeIntercepted,45,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // GetFileTimeIntercepted

              // Сообщение о перехвате вызова функции WindowsApi MoveFileA
              BEGIN_MESSAGE(MoveFileAIntercepted,39,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к целевому файлу
                ARGUMENT(0, string, PathDst);
                // Путь к перемещаемому файлу
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // MoveFileAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi MoveFileA
              BEGIN_MESSAGE(MoveFileA_Answer,40,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // MoveFileA_Answer

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(PathCanonicalizeAIntercepted,6,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Форматируемый путь
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathCanonicalizeAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(PathCanonicalizeA_Answer,7,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результирующий путь
                ARGUMENT(0, string, Path);
                // true - успешно false - неуспешно
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // PathCanonicalizeA_Answer

              // Сообщение о перехвате вызова функции PathCombineA
              BEGIN_MESSAGE(PathCombineAIntercepted,3,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Исходная строка
                ARGUMENT(0, string, PathIn);
                // Добавочная строка
                ARGUMENT(1, string, PathMore);
              END_MESSAGE(); // PathCombineAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathCombineA
              BEGIN_MESSAGE(PathCombineA_Answer,4,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Склееный путь
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathCombineA_Answer

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(PathFindFileNameAIntercepted,9,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathFindFileNameAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(PathFindFileNameA_Answer,10,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Имя файла
                ARGUMENT(0, string, Filename);
              END_MESSAGE(); // PathFindFileNameA_Answer

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(PathRemoveFileSpecAIntercepted,12,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь с именем файла
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // PathRemoveFileSpecAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(PathRemoveFileSpecA_Answer,13,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь без имени файла
                ARGUMENT(0, string, Path);
                // Результат работы функции
                ARGUMENT(1, bool, Result);
              END_MESSAGE(); // PathRemoveFileSpecA_Answer

              // Сообщение о перехвате вызова функции WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(RemoveDirectoryAIntercepted,36,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // RemoveDirectoryAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(RemoveDirectoryA_Answer,37,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // RemoveDirectoryA_Answer

              // Сообщение о перехвате вызова функции WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(SHCreateDirectoryExAIntercepted,67,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // SHCreateDirectoryExAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(SHCreateDirectoryExA_Answer,68,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Код ошибки (тот же что и для GetLastError)
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // SHCreateDirectoryExA_Answer

              // Сообщение о перехвате вызова функции WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(SetFileAttributesAIntercepted,21,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла
                FLAG(0, WinApiAttr, Attributes);
                // Путь к файлу
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // SetFileAttributesAIntercepted

              // Ответ на сообщение о перехвате вызова функции WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(SetFileAttributesA_Answer,22,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат работы функции
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetFileAttributesA_Answer

              // Инициирует тестовый вызов функции WindowsApi CopyFileA
              BEGIN_MESSAGE(TestCopyFileA,26,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу в который копируем
                ARGUMENT(0, string, PathDst);
                // Путь к копируемому файлу
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // TestCopyFileA

              // Инициирует тестовый вызов функции WindowsApi CreateDirectoryA
              BEGIN_MESSAGE(TestCreateDirectoryA,23,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к создаваемой папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestCreateDirectoryA

              // Инициирует тестовый вызов функции WindowsApi CreateFileA
              BEGIN_MESSAGE(TestCreateFileA,29,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к создаваемому файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestCreateFileA

              // Инициирует тестовый вызов функции WindowsApi DeleteFileA
              BEGIN_MESSAGE(TestDeleteFileA,32,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к удаляемому файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestDeleteFileA

              // Инициирует тестовый вызов функции fclose
              BEGIN_MESSAGE(TestFclose,63,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFclose

              // Инициирует тестовый вызов функции feof
              BEGIN_MESSAGE(TestFeof,59,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFeof

              // Инициирует тестовый вызов функции WindowsApi FindClose
              BEGIN_MESSAGE(TestFindClose,72,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFindClose

              // Инициирует тестовый вызов функции WindowsApi FindFirstFileA
              BEGIN_MESSAGE(TestFindFirstFileA,17,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Маска поиска
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // TestFindFirstFileA

              // Инициирует тестовый вызов функции WindowsApi FindFirstFileExA
              BEGIN_MESSAGE(TestFindFirstFileExA,14,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Маска поиска
                ARGUMENT(0, string, Mask);
              END_MESSAGE(); // TestFindFirstFileExA

              // Инициирует тестовый вызов функции WindowsApi FindNextFileA
              BEGIN_MESSAGE(TestFindNextFileA,41,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFindNextFileA

              // Инициирует тестовый вызов функции fopen_s
              BEGIN_MESSAGE(TestFopen_s,53,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Режим
                ARGUMENT(0, string, Mode);
                // Путь к файлу
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // TestFopen_s

              // Инициирует тестовый вызов функции fread
              BEGIN_MESSAGE(TestFread,56,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                  SetItemSize(1);
                }
                // Количество элементов
                ARGUMENT(0, int, Count);
                // Размер элемента
                ARGUMENT(1, int, ItemSize);
              END_MESSAGE(); // TestFread

              // Инициирует тестовый вызов функции WindowsApi GetFileAttributesA
              BEGIN_MESSAGE(TestGetFileAttributesA,50,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestGetFileAttributesA

              // Инициирует тестовый вызов функции WindowsApi GetFileSize
              BEGIN_MESSAGE(TestGetFileSize,47,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetFileSize

              // Инициирует тестовый вызов функции WindowsApi GetFileTime
              BEGIN_MESSAGE(TestGetFileTime,44,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetFileTime

              // Инициирует тестовый вызов функции WindowsApi MoveFileA
              BEGIN_MESSAGE(TestMoveFileA,38,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу в который перемещаем
                ARGUMENT(0, string, PathDst);
                // Путь к перемещаемому файлу
                ARGUMENT(1, string, PathSrc);
              END_MESSAGE(); // TestMoveFileA

              // Инициирует тестовый вызов функции WindowsApi PathCanonicalizeA
              BEGIN_MESSAGE(TestPathCanonicalizeA,5,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Форматируемый путь
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathCanonicalizeA

              // Инициирует тестовый вызов функции WindowsApi PathCombineA
              BEGIN_MESSAGE(TestPathCombineA,2,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Исходная строка
                ARGUMENT(0, string, PathIn);
                // Добавочная строка
                ARGUMENT(1, string, PathMore);
              END_MESSAGE(); // TestPathCombineA

              // Инициирует тестовый вызов функции WindowsApi PathFindFileNameA
              BEGIN_MESSAGE(TestPathFindFileNameA,8,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к файлу
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathFindFileNameA

              // Инициирует тестовый вызов функции WindowsApi PathRemoveFileSpecA
              BEGIN_MESSAGE(TestPathRemoveFileSpecA,11,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь с именем файла
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestPathRemoveFileSpecA

              // Инициирует тестовый вызов функции WindowsApi RemoveDirectoryA
              BEGIN_MESSAGE(TestRemoveDirectoryA,35,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к удаляемой папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestRemoveDirectoryA

              // Инициирует тестовый вызов функции WindowsApi SHCreateDirectoryExA
              BEGIN_MESSAGE(TestSHCreateDirectoryExA,66,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Путь к папке
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestSHCreateDirectoryExA

              // Инициирует тестовый вызов функции WindowsApi SetFileAttributesA
              BEGIN_MESSAGE(TestSetFileAttributesA,20,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Атрибуты файла как в WinAPI
                FLAG(0, WinApiAttr, Attributes);
                // Путь к файлу
                ARGUMENT(1, string, Path);
              END_MESSAGE(); // TestSetFileAttributesA

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// Присылается после успешного срабатывания тестирующего метода и возврата из тестируемой функции
                /// </summary>
                /// <param name="Attributes">Возвращаемые атрибуты</param>
                /// <param name="ParamInt">Числовой параметр</param>
                /// <param name="ParamStr">Строковый параметр</param>
                /// <param name="Result">Результат работы функции, он же результат теста</param>
                /// <param name="TimeCreated">Дата создания</param>
                /// <param name="TimeModified">Дата изменения</param>
                void CompletedTest(WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, string paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0))) const
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi CopyFileA
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void CopyFileAIntercepted(const string & pathDst, const string & pathSrc) const
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi CreateDirectoryA
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void CreateDirectoryAIntercepted(const string & path) const
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi CreateFileA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void CreateFileAIntercepted(const string & path) const
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi DeleteFileA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void DeleteFileAIntercepted(const string & path) const
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fclose
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void FcloseIntercepted(int handle) const
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi Feof
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void FeofIntercepted(int handle) const
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi FindClose
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void FindCloseIntercepted(int handle) const
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi FindFirstFileA
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void FindFirstFileAIntercepted(const string & mask) const
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi FindFirstFileExA
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void FindFirstFileExAIntercepted(const string & mask) const
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi FindNextFileA
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void FindNextFileAIntercepted(int handle) const
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fopen_s
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void Fopen_sIntercepted(const string & mode, const string & path) const
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fread
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="handle">Файловая переменнаяия</param>
                /// <param name="itemSize">Размер элемента</param>
                void FreadIntercepted(int count, int handle, int itemSize) const
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi GetFileAttributesA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void GetFileAttributesAIntercepted(const string & path) const
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi GetFileSize
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void GetFileSizeIntercepted(int handle) const
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi GetFileTime
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void GetFileTimeIntercepted(int handle) const
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi MoveFileA
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void MoveFileAIntercepted(const string & pathDst, const string & pathSrc) const
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Ответ на сообщение о перехвате вызова функции WindowsApi PathCanonicalizeA
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void PathCanonicalizeAIntercepted(const string & path) const
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции PathCombineA
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void PathCombineAIntercepted(const string & pathIn, const string & pathMore) const
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Ответ на сообщение о перехвате вызова функции WindowsApi PathFindFileNameA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void PathFindFileNameAIntercepted(const string & path) const
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Ответ на сообщение о перехвате вызова функции WindowsApi PathRemoveFileSpecA
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void PathRemoveFileSpecAIntercepted(const string & path) const
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi RemoveDirectoryA
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void RemoveDirectoryAIntercepted(const string & path) const
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi SHCreateDirectoryExA
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void SHCreateDirectoryExAIntercepted(const string & path) const
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции WindowsApi SetFileAttributesA
                /// </summary>
                /// <param name="attributes">Атрибуты файла</param>
                /// <param name="path">Путь к файлу</param>
                void SetFileAttributesAIntercepted(WinApiAttr attributes, const string & path) const
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi CopyFileA
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который копируем</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void TestCopyFileA(const string & pathDst, const string & pathSrc) const
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi CreateDirectoryA
                /// </summary>
                /// <param name="path">Путь к создаваемой папке</param>
                void TestCreateDirectoryA(const string & path) const
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi CreateFileA
                /// </summary>
                /// <param name="path">Путь к создаваемому файлу</param>
                void TestCreateFileA(const string & path) const
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi DeleteFileA
                /// </summary>
                /// <param name="path">Путь к удаляемому файлу</param>
                void TestDeleteFileA(const string & path) const
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции fclose
                /// </summary>
                void TestFclose() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFclose);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции feof
                /// </summary>
                void TestFeof() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFeof);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi FindClose
                /// </summary>
                void TestFindClose() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindClose);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi FindFirstFileA
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void TestFindFirstFileA(const string & mask) const
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi FindFirstFileExA
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void TestFindFirstFileExA(const string & mask) const
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi FindNextFileA
                /// </summary>
                void TestFindNextFileA() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindNextFileA);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции fopen_s
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void TestFopen_s(const string & mode, const string & path) const
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции fread
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="ItemSize">Размер элемента</param>
                void TestFread(int count, int itemSize = 1) const
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi GetFileAttributesA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void TestGetFileAttributesA(const string & path) const
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi GetFileSize
                /// </summary>
                void TestGetFileSize() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileSize);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi GetFileTime
                /// </summary>
                void TestGetFileTime() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileTime);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi MoveFileA
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который перемещаем</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void TestMoveFileA(const string & pathDst, const string & pathSrc) const
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi PathCanonicalizeA
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void TestPathCanonicalizeA(const string & path) const
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi PathCombineA
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void TestPathCombineA(const string & pathIn, const string & pathMore) const
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi PathFindFileNameA
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void TestPathFindFileNameA(const string & path) const
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi PathRemoveFileSpecA
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void TestPathRemoveFileSpecA(const string & path) const
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi RemoveDirectoryA
                /// </summary>
                /// <param name="path">Путь к удаляемой папке</param>
                void TestRemoveDirectoryA(const string & path) const
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi SHCreateDirectoryExA
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void TestSHCreateDirectoryExA(const string & path) const
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции WindowsApi SetFileAttributesA
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="path">Путь к файлу</param>
                void TestSetFileAttributesA(WinApiAttr attributes, const string & path) const
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// Отправка события CompletedTest по адресу
                /// </summary>
                /// <param name="attributes">Возвращаемые атрибуты</param>
                /// <param name="paramInt">Числовой параметр</param>
                /// <param name="paramStr">Строковый параметр</param>
                /// <param name="result">Результат работы функции, он же результат теста</param>
                /// <param name="timeCreated">Дата создания</param>
                /// <param name="timeModified">Дата изменения</param>
                void SendCompletedTest(address target, WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, const string & paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)))
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CompletedTest самому себе
                /// </summary>
                /// <param name="attributes">Возвращаемые атрибуты</param>
                /// <param name="paramInt">Числовой параметр</param>
                /// <param name="paramStr">Строковый параметр</param>
                /// <param name="result">Результат работы функции, он же результат теста</param>
                /// <param name="timeCreated">Дата создания</param>
                /// <param name="timeModified">Дата изменения</param>
                void RaiseCompletedTest(WinApiAttr attributes = (WinApiAttr)WinApiAttr::Normal, int paramInt = 0, const string & paramStr = "", bool result = false, timestamp_t timeCreated = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)), timestamp_t timeModified = std::chrono::system_clock::time_point(std::chrono::milliseconds(0)))
                {
                  G1::CompletedTest cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetParamInt(paramInt);
                  cmd.SetParamStr(paramStr);
                  cmd.SetResult(result);
                  cmd.SetTimeCreated(timeCreated);
                  cmd.SetTimeModified(timeModified);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CopyFileAIntercepted по адресу
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void SendCopyFileAIntercepted(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CopyFileAIntercepted самому себе
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void RaiseCopyFileAIntercepted(const string & pathDst, const string & pathSrc)
                {
                  G1::CopyFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CopyFileA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendCopyFileA_Answer(address target, bool result)
                {
                  G1::CopyFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CopyFileA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseCopyFileA_Answer(bool result)
                {
                  G1::CopyFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateDirectoryAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void SendCreateDirectoryAIntercepted(address target, const string & path)
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateDirectoryAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void RaiseCreateDirectoryAIntercepted(const string & path)
                {
                  G1::CreateDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateDirectoryA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendCreateDirectoryA_Answer(address target, bool result)
                {
                  G1::CreateDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateDirectoryA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseCreateDirectoryA_Answer(bool result)
                {
                  G1::CreateDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateFileAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendCreateFileAIntercepted(address target, const string & path)
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateFileAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaiseCreateFileAIntercepted(const string & path)
                {
                  G1::CreateFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события CreateFileA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendCreateFileA_Answer(address target, bool result)
                {
                  G1::CreateFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события CreateFileA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseCreateFileA_Answer(bool result)
                {
                  G1::CreateFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события DeleteFileAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendDeleteFileAIntercepted(address target, const string & path)
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события DeleteFileAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaiseDeleteFileAIntercepted(const string & path)
                {
                  G1::DeleteFileAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события DeleteFileA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendDeleteFileA_Answer(address target, bool result)
                {
                  G1::DeleteFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события DeleteFileA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseDeleteFileA_Answer(bool result)
                {
                  G1::DeleteFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FcloseAnswer по адресу
                /// </summary>
                /// <param name="result">true - файл успешно закрыт, false - ошибка</param>
                void SendFcloseAnswer(address target, bool result)
                {
                  G1::FcloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FcloseAnswer самому себе
                /// </summary>
                /// <param name="result">true - файл успешно закрыт, false - ошибка</param>
                void RaiseFcloseAnswer(bool result)
                {
                  G1::FcloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FcloseIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendFcloseIntercepted(address target, int handle)
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FcloseIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseFcloseIntercepted(int handle)
                {
                  G1::FcloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FeofAnswer по адресу
                /// </summary>
                /// <param name="result">true - конец файла, false - еще нет</param>
                void SendFeofAnswer(address target, bool result)
                {
                  G1::FeofAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FeofAnswer самому себе
                /// </summary>
                /// <param name="result">true - конец файла, false - еще нет</param>
                void RaiseFeofAnswer(bool result)
                {
                  G1::FeofAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FeofIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendFeofIntercepted(address target, int handle)
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FeofIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseFeofIntercepted(int handle)
                {
                  G1::FeofIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindCloseAnswer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendFindCloseAnswer(address target, bool result)
                {
                  G1::FindCloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindCloseAnswer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseFindCloseAnswer(bool result)
                {
                  G1::FindCloseAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindCloseIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendFindCloseIntercepted(address target, int handle)
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindCloseIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseFindCloseIntercepted(int handle)
                {
                  G1::FindCloseIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindFirstFileAIntercepted по адресу
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void SendFindFirstFileAIntercepted(address target, const string & mask)
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindFirstFileAIntercepted самому себе
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void RaiseFindFirstFileAIntercepted(const string & mask)
                {
                  G1::FindFirstFileAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindFirstFileA_Answer по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">false - функция вернет INVALID_ARGUMENT, true - вернется виртуальный хэндлер</param>
                void SendFindFirstFileA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindFirstFileA_Answer самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">false - функция вернет INVALID_ARGUMENT, true - вернется виртуальный хэндлер</param>
                void RaiseFindFirstFileA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindFirstFileExAIntercepted по адресу
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void SendFindFirstFileExAIntercepted(address target, const string & mask)
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindFirstFileExAIntercepted самому себе
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void RaiseFindFirstFileExAIntercepted(const string & mask)
                {
                  G1::FindFirstFileExAIntercepted cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindFirstFileExA_Answer по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">false - функция вернет INVALID_ARGUMENT, true - вернется виртуальный хэндлер</param>
                void SendFindFirstFileExA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileExA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindFirstFileExA_Answer самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">false - функция вернет INVALID_ARGUMENT, true - вернется виртуальный хэндлер</param>
                void RaiseFindFirstFileExA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindFirstFileExA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindNextFileAIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendFindNextFileAIntercepted(address target, int handle)
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindNextFileAIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseFindNextFileAIntercepted(int handle)
                {
                  G1::FindNextFileAIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FindNextFileA_Answer по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">Результат работы функции</param>
                void SendFindNextFileA_Answer(address target, WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindNextFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FindNextFileA_Answer самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="filename">Название найденного файла</param>
                /// <param name="result">Результат работы функции</param>
                void RaiseFindNextFileA_Answer(WinApiAttr attributes, const string & filename, bool result)
                {
                  G1::FindNextFileA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetFilename(filename);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события Fopen_sAnswer по адресу
                /// </summary>
                /// <param name="errno">Результат</param>
                void SendFopen_sAnswer(address target, int errno)
                {
                  G1::Fopen_sAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события Fopen_sAnswer самому себе
                /// </summary>
                /// <param name="errno">Результат</param>
                void RaiseFopen_sAnswer(int errno)
                {
                  G1::Fopen_sAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события Fopen_sIntercepted по адресу
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void SendFopen_sIntercepted(address target, const string & mode, const string & path)
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события Fopen_sIntercepted самому себе
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void RaiseFopen_sIntercepted(const string & mode, const string & path)
                {
                  G1::Fopen_sIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FreadAnswer по адресу
                /// </summary>
                /// <param name="buffer">прочитанные символы</param>
                void SendFreadAnswer(address target, const string & buffer)
                {
                  G1::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FreadAnswer самому себе
                /// </summary>
                /// <param name="buffer">прочитанные символы</param>
                void RaiseFreadAnswer(const string & buffer)
                {
                  G1::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FreadIntercepted по адресу
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="handle">Файловая переменнаяия</param>
                /// <param name="itemSize">Размер элемента</param>
                void SendFreadIntercepted(address target, int count, int handle, int itemSize)
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FreadIntercepted самому себе
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="handle">Файловая переменнаяия</param>
                /// <param name="itemSize">Размер элемента</param>
                void RaiseFreadIntercepted(int count, int handle, int itemSize)
                {
                  G1::FreadIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileAttributesAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendGetFileAttributesAIntercepted(address target, const string & path)
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileAttributesAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaiseGetFileAttributesAIntercepted(const string & path)
                {
                  G1::GetFileAttributesAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileAttributesA_Answer по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла</param>
                void SendGetFileAttributesA_Answer(address target, WinApiAttr attributes)
                {
                  G1::GetFileAttributesA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileAttributesA_Answer самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла</param>
                void RaiseGetFileAttributesA_Answer(WinApiAttr attributes)
                {
                  G1::GetFileAttributesA_Answer cmd;
                  cmd.SetAttributes(attributes);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileSizeAnswer по адресу
                /// </summary>
                /// <param name="size">Размер файла</param>
                void SendGetFileSizeAnswer(address target, int size)
                {
                  G1::GetFileSizeAnswer cmd;
                  cmd.SetSize(size);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileSizeAnswer самому себе
                /// </summary>
                /// <param name="size">Размер файла</param>
                void RaiseGetFileSizeAnswer(int size)
                {
                  G1::GetFileSizeAnswer cmd;
                  cmd.SetSize(size);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileSizeIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendGetFileSizeIntercepted(address target, int handle)
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileSizeIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseGetFileSizeIntercepted(int handle)
                {
                  G1::GetFileSizeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileTimeAnswer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                /// <param name="timeCreate">Дата создания файла</param>
                /// <param name="timeModify">Дата изменения файла</param>
                void SendGetFileTimeAnswer(address target, bool result, timestamp_t timeCreate, timestamp_t timeModify)
                {
                  G1::GetFileTimeAnswer cmd;
                  cmd.SetResult(result);
                  cmd.SetTimeCreate(timeCreate);
                  cmd.SetTimeModify(timeModify);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileTimeAnswer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                /// <param name="timeCreate">Дата создания файла</param>
                /// <param name="timeModify">Дата изменения файла</param>
                void RaiseGetFileTimeAnswer(bool result, timestamp_t timeCreate, timestamp_t timeModify)
                {
                  G1::GetFileTimeAnswer cmd;
                  cmd.SetResult(result);
                  cmd.SetTimeCreate(timeCreate);
                  cmd.SetTimeModify(timeModify);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetFileTimeIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendGetFileTimeIntercepted(address target, int handle)
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetFileTimeIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseGetFileTimeIntercepted(int handle)
                {
                  G1::GetFileTimeIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события MoveFileAIntercepted по адресу
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void SendMoveFileAIntercepted(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события MoveFileAIntercepted самому себе
                /// </summary>
                /// <param name="pathDst">Путь к целевому файлу</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void RaiseMoveFileAIntercepted(const string & pathDst, const string & pathSrc)
                {
                  G1::MoveFileAIntercepted cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события MoveFileA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendMoveFileA_Answer(address target, bool result)
                {
                  G1::MoveFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события MoveFileA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseMoveFileA_Answer(bool result)
                {
                  G1::MoveFileA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathCanonicalizeAIntercepted по адресу
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void SendPathCanonicalizeAIntercepted(address target, const string & path)
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathCanonicalizeAIntercepted самому себе
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void RaisePathCanonicalizeAIntercepted(const string & path)
                {
                  G1::PathCanonicalizeAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathCanonicalizeA_Answer по адресу
                /// </summary>
                /// <param name="path">Результирующий путь</param>
                /// <param name="result">true - успешно, false - неуспешно</param>
                void SendPathCanonicalizeA_Answer(address target, const string & path, bool result)
                {
                  G1::PathCanonicalizeA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathCanonicalizeA_Answer самому себе
                /// </summary>
                /// <param name="path">Результирующий путь</param>
                /// <param name="result">true - успешно, false - неуспешно</param>
                void RaisePathCanonicalizeA_Answer(const string & path, bool result)
                {
                  G1::PathCanonicalizeA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathCombineAIntercepted по адресу
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void SendPathCombineAIntercepted(address target, const string & pathIn, const string & pathMore)
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathCombineAIntercepted самому себе
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void RaisePathCombineAIntercepted(const string & pathIn, const string & pathMore)
                {
                  G1::PathCombineAIntercepted cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathCombineA_Answer по адресу
                /// </summary>
                /// <param name="path">Склееный путь</param>
                void SendPathCombineA_Answer(address target, const string & path)
                {
                  G1::PathCombineA_Answer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathCombineA_Answer самому себе
                /// </summary>
                /// <param name="path">Склееный путь</param>
                void RaisePathCombineA_Answer(const string & path)
                {
                  G1::PathCombineA_Answer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathFindFileNameAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendPathFindFileNameAIntercepted(address target, const string & path)
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathFindFileNameAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaisePathFindFileNameAIntercepted(const string & path)
                {
                  G1::PathFindFileNameAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathFindFileNameA_Answer по адресу
                /// </summary>
                /// <param name="filename">Имя файла</param>
                void SendPathFindFileNameA_Answer(address target, const string & filename)
                {
                  G1::PathFindFileNameA_Answer cmd;
                  cmd.SetFilename(filename);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathFindFileNameA_Answer самому себе
                /// </summary>
                /// <param name="filename">Имя файла</param>
                void RaisePathFindFileNameA_Answer(const string & filename)
                {
                  G1::PathFindFileNameA_Answer cmd;
                  cmd.SetFilename(filename);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathRemoveFileSpecAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void SendPathRemoveFileSpecAIntercepted(address target, const string & path)
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathRemoveFileSpecAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void RaisePathRemoveFileSpecAIntercepted(const string & path)
                {
                  G1::PathRemoveFileSpecAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события PathRemoveFileSpecA_Answer по адресу
                /// </summary>
                /// <param name="path">Путь без имени файла</param>
                /// <param name="result">Результат работы функции</param>
                void SendPathRemoveFileSpecA_Answer(address target, const string & path, bool result)
                {
                  G1::PathRemoveFileSpecA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события PathRemoveFileSpecA_Answer самому себе
                /// </summary>
                /// <param name="path">Путь без имени файла</param>
                /// <param name="result">Результат работы функции</param>
                void RaisePathRemoveFileSpecA_Answer(const string & path, bool result)
                {
                  G1::PathRemoveFileSpecA_Answer cmd;
                  cmd.SetPath(path);
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события RemoveDirectoryAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void SendRemoveDirectoryAIntercepted(address target, const string & path)
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события RemoveDirectoryAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void RaiseRemoveDirectoryAIntercepted(const string & path)
                {
                  G1::RemoveDirectoryAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события RemoveDirectoryA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendRemoveDirectoryA_Answer(address target, bool result)
                {
                  G1::RemoveDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события RemoveDirectoryA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseRemoveDirectoryA_Answer(bool result)
                {
                  G1::RemoveDirectoryA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SHCreateDirectoryExAIntercepted по адресу
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void SendSHCreateDirectoryExAIntercepted(address target, const string & path)
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SHCreateDirectoryExAIntercepted самому себе
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void RaiseSHCreateDirectoryExAIntercepted(const string & path)
                {
                  G1::SHCreateDirectoryExAIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SHCreateDirectoryExA_Answer по адресу
                /// </summary>
                /// <param name="code">Код ошибки (тот же, что и для GetLastError)</param>
                void SendSHCreateDirectoryExA_Answer(address target, int code)
                {
                  G1::SHCreateDirectoryExA_Answer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SHCreateDirectoryExA_Answer самому себе
                /// </summary>
                /// <param name="code">Код ошибки (тот же, что и для GetLastError)</param>
                void RaiseSHCreateDirectoryExA_Answer(int code)
                {
                  G1::SHCreateDirectoryExA_Answer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetFileAttributesAIntercepted по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла</param>
                /// <param name="path">Путь к файлу</param>
                void SendSetFileAttributesAIntercepted(address target, WinApiAttr attributes, const string & path)
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetFileAttributesAIntercepted самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла</param>
                /// <param name="path">Путь к файлу</param>
                void RaiseSetFileAttributesAIntercepted(WinApiAttr attributes, const string & path)
                {
                  G1::SetFileAttributesAIntercepted cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetFileAttributesA_Answer по адресу
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void SendSetFileAttributesA_Answer(address target, bool result)
                {
                  G1::SetFileAttributesA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetFileAttributesA_Answer самому себе
                /// </summary>
                /// <param name="result">Результат работы функции</param>
                void RaiseSetFileAttributesA_Answer(bool result)
                {
                  G1::SetFileAttributesA_Answer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestCopyFileA по адресу
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который копируем</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void SendTestCopyFileA(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestCopyFileA самому себе
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который копируем</param>
                /// <param name="pathSrc">Путь к копируемому файлу</param>
                void RaiseTestCopyFileA(const string & pathDst, const string & pathSrc)
                {
                  G1::TestCopyFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestCreateDirectoryA по адресу
                /// </summary>
                /// <param name="path">Путь к создаваемой папке</param>
                void SendTestCreateDirectoryA(address target, const string & path)
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestCreateDirectoryA самому себе
                /// </summary>
                /// <param name="path">Путь к создаваемой папке</param>
                void RaiseTestCreateDirectoryA(const string & path)
                {
                  G1::TestCreateDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestCreateFileA по адресу
                /// </summary>
                /// <param name="path">Путь к создаваемому файлу</param>
                void SendTestCreateFileA(address target, const string & path)
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestCreateFileA самому себе
                /// </summary>
                /// <param name="path">Путь к создаваемому файлу</param>
                void RaiseTestCreateFileA(const string & path)
                {
                  G1::TestCreateFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestDeleteFileA по адресу
                /// </summary>
                /// <param name="path">Путь к удаляемому файлу</param>
                void SendTestDeleteFileA(address target, const string & path)
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestDeleteFileA самому себе
                /// </summary>
                /// <param name="path">Путь к удаляемому файлу</param>
                void RaiseTestDeleteFileA(const string & path)
                {
                  G1::TestDeleteFileA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFclose по адресу
                /// </summary>
                void SendTestFclose(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFclose);
                }
                /// <summary> 
                /// Отправка события TestFclose самому себе
                /// </summary>
                void RaiseTestFclose()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFclose);
                }
                
                /// <summary> 
                /// Отправка события TestFeof по адресу
                /// </summary>
                void SendTestFeof(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFeof);
                }
                /// <summary> 
                /// Отправка события TestFeof самому себе
                /// </summary>
                void RaiseTestFeof()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFeof);
                }
                
                /// <summary> 
                /// Отправка события TestFindClose по адресу
                /// </summary>
                void SendTestFindClose(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFindClose);
                }
                /// <summary> 
                /// Отправка события TestFindClose самому себе
                /// </summary>
                void RaiseTestFindClose()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindClose);
                }
                
                /// <summary> 
                /// Отправка события TestFindFirstFileA по адресу
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void SendTestFindFirstFileA(address target, const string & mask)
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFindFirstFileA самому себе
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void RaiseTestFindFirstFileA(const string & mask)
                {
                  G1::TestFindFirstFileA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFindFirstFileExA по адресу
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void SendTestFindFirstFileExA(address target, const string & mask)
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFindFirstFileExA самому себе
                /// </summary>
                /// <param name="mask">Маска поиска</param>
                void RaiseTestFindFirstFileExA(const string & mask)
                {
                  G1::TestFindFirstFileExA cmd;
                  cmd.SetMask(mask);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFindNextFileA по адресу
                /// </summary>
                void SendTestFindNextFileA(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestFindNextFileA);
                }
                /// <summary> 
                /// Отправка события TestFindNextFileA самому себе
                /// </summary>
                void RaiseTestFindNextFileA()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestFindNextFileA);
                }
                
                /// <summary> 
                /// Отправка события TestFopen_s по адресу
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void SendTestFopen_s(address target, const string & mode, const string & path)
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFopen_s самому себе
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="path">Путь к файлу</param>
                void RaiseTestFopen_s(const string & mode, const string & path)
                {
                  G1::TestFopen_s cmd;
                  cmd.SetMode(mode);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFread по адресу
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="itemSize">Размер элемента</param>
                void SendTestFread(address target, int count, int itemSize = 1)
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFread самому себе
                /// </summary>
                /// <param name="count">Количество элементов</param>
                /// <param name="itemSize">Размер элемента</param>
                void RaiseTestFread(int count, int itemSize = 1)
                {
                  G1::TestFread cmd;
                  cmd.SetCount(count);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestGetFileAttributesA по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendTestGetFileAttributesA(address target, const string & path)
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestGetFileAttributesA самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaiseTestGetFileAttributesA(const string & path)
                {
                  G1::TestGetFileAttributesA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestGetFileSize по адресу
                /// </summary>
                void SendTestGetFileSize(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestGetFileSize);
                }
                /// <summary> 
                /// Отправка события TestGetFileSize самому себе
                /// </summary>
                void RaiseTestGetFileSize()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileSize);
                }
                
                /// <summary> 
                /// Отправка события TestGetFileTime по адресу
                /// </summary>
                void SendTestGetFileTime(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G1::Codes::TestGetFileTime);
                }
                /// <summary> 
                /// Отправка события TestGetFileTime самому себе
                /// </summary>
                void RaiseTestGetFileTime()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::TestGetFileTime);
                }
                
                /// <summary> 
                /// Отправка события TestMoveFileA по адресу
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который перемещаем</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void SendTestMoveFileA(address target, const string & pathDst, const string & pathSrc)
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestMoveFileA самому себе
                /// </summary>
                /// <param name="pathDst">Путь к файлу, в который перемещаем</param>
                /// <param name="pathSrc">Путь к перемещаемому файлу</param>
                void RaiseTestMoveFileA(const string & pathDst, const string & pathSrc)
                {
                  G1::TestMoveFileA cmd;
                  cmd.SetPathDst(pathDst);
                  cmd.SetPathSrc(pathSrc);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestPathCanonicalizeA по адресу
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void SendTestPathCanonicalizeA(address target, const string & path)
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestPathCanonicalizeA самому себе
                /// </summary>
                /// <param name="path">Форматируемый путь</param>
                void RaiseTestPathCanonicalizeA(const string & path)
                {
                  G1::TestPathCanonicalizeA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestPathCombineA по адресу
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void SendTestPathCombineA(address target, const string & pathIn, const string & pathMore)
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestPathCombineA самому себе
                /// </summary>
                /// <param name="pathIn">Исходная строка</param>
                /// <param name="pathMore">Добавочная строка</param>
                void RaiseTestPathCombineA(const string & pathIn, const string & pathMore)
                {
                  G1::TestPathCombineA cmd;
                  cmd.SetPathIn(pathIn);
                  cmd.SetPathMore(pathMore);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestPathFindFileNameA по адресу
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void SendTestPathFindFileNameA(address target, const string & path)
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestPathFindFileNameA самому себе
                /// </summary>
                /// <param name="path">Путь к файлу</param>
                void RaiseTestPathFindFileNameA(const string & path)
                {
                  G1::TestPathFindFileNameA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestPathRemoveFileSpecA по адресу
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void SendTestPathRemoveFileSpecA(address target, const string & path)
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestPathRemoveFileSpecA самому себе
                /// </summary>
                /// <param name="path">Путь с именем файла</param>
                void RaiseTestPathRemoveFileSpecA(const string & path)
                {
                  G1::TestPathRemoveFileSpecA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestRemoveDirectoryA по адресу
                /// </summary>
                /// <param name="path">Путь к удаляемой папке</param>
                void SendTestRemoveDirectoryA(address target, const string & path)
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestRemoveDirectoryA самому себе
                /// </summary>
                /// <param name="path">Путь к удаляемой папке</param>
                void RaiseTestRemoveDirectoryA(const string & path)
                {
                  G1::TestRemoveDirectoryA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestSHCreateDirectoryExA по адресу
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void SendTestSHCreateDirectoryExA(address target, const string & path)
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestSHCreateDirectoryExA самому себе
                /// </summary>
                /// <param name="path">Путь к папке</param>
                void RaiseTestSHCreateDirectoryExA(const string & path)
                {
                  G1::TestSHCreateDirectoryExA cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestSetFileAttributesA по адресу
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="path">Путь к файлу</param>
                void SendTestSetFileAttributesA(address target, WinApiAttr attributes, const string & path)
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestSetFileAttributesA самому себе
                /// </summary>
                /// <param name="attributes">Атрибуты файла как в WinAPI</param>
                /// <param name="path">Путь к файлу</param>
                void RaiseTestSetFileAttributesA(WinApiAttr attributes, const string & path)
                {
                  G1::TestSetFileAttributesA cmd;
                  cmd.SetAttributes(attributes);
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            

            BEGIN_PROTOCOL(11, 2)
              
              #pragma region Enumerations
              /// <summary> 
              /// Специфичные ошибки при работе с файловой системой
              /// </summary>
              enum class FileSystemApiErrors
              {
                ErrorAccessDenied = 5, // Диск недоступен
                ErrorCurrentDirectory = 16, // Папка не может быть удалена
                ErrorDevNotExist = 55, // Устройство недоступно
                ErrorDiskFull = 112, // Недостаточно свободного места на диске
                ErrorFileNotFound = 2, // Файл не найден
                ErrorHandleDiskFull = 39, // Диск переполнен
                ErrorInvalidDrive = 15, // Диск не существует
                ErrorNetworkAccessDenied = 65, // Сетевой диск недоступен
                ErrorNoMoreFiles = 18, // Больше нет файлов, удовлетворяющих критерию выборки
                ErrorPathNotFound = 3 // Путь к файлу не найден
              };
              
              /// <summary> 
              /// Режим чтений
              /// </summary>
              enum class ReadMode
              {
                ReadLine = 2, // - Читать построчно
                ReadWord = 1 // - Читать слово
              };
              
              /// <summary>
              /// Валидатор корректности значения для перечислимого типа FileSystemApiErrors
              /// </summary>
              inline bool IsValidFileSystemApiErrorsValue(const int value)
              {
                return ((value >= 2)&&(value < 4)) || ((value >= 5)&&(value < 6)) || ((value >= 15)&&(value < 17)) || ((value >= 18)&&(value < 19)) || ((value >= 39)&&(value < 40)) || ((value >= 55)&&(value < 56)) || ((value >= 65)&&(value < 66)) || ((value >= 112)&&(value < 113));
              }
              
              /// <summary>
              /// Следует использовать для преобразования числовых значений к перечислимому типу FileSystemApiErrors
              /// </summary>
              inline FileSystemApiErrors ConvertToFileSystemApiErrors(const int value)
              {
                switch (value)
                {
                  case 5:
                    return FileSystemApiErrors::ErrorAccessDenied;
                  case 16:
                    return FileSystemApiErrors::ErrorCurrentDirectory;
                  case 55:
                    return FileSystemApiErrors::ErrorDevNotExist;
                  case 112:
                    return FileSystemApiErrors::ErrorDiskFull;
                  case 2:
                    return FileSystemApiErrors::ErrorFileNotFound;
                  case 39:
                    return FileSystemApiErrors::ErrorHandleDiskFull;
                  case 15:
                    return FileSystemApiErrors::ErrorInvalidDrive;
                  case 65:
                    return FileSystemApiErrors::ErrorNetworkAccessDenied;
                  case 18:
                    return FileSystemApiErrors::ErrorNoMoreFiles;
                  case 3:
                    return FileSystemApiErrors::ErrorPathNotFound;
                  default: throw KernelException("Невозможно преобразовать числовое значение %d к типу FileSystemApiErrors", value);
                  }
              }
              
              /// <summary>
              /// Валидатор корректности значения для перечислимого типа ReadMode
              /// </summary>
              inline bool IsValidReadModeValue(const int value)
              {
                return ((value >= 1)&&(value < 3));
              }
              
              /// <summary>
              /// Следует использовать для преобразования числовых значений к перечислимому типу ReadMode
              /// </summary>
              inline ReadMode ConvertToReadMode(const int value)
              {
                switch (value)
                {
                  case 2:
                    return ReadMode::ReadLine;
                  case 1:
                    return ReadMode::ReadWord;
                  default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ReadMode", value);
                  }
              }
              
              #pragma endregion
              
              #pragma region Flags
              
              /// <summary> 
              /// Константы WinAPI для файловых атрибутов
              /// </summary>
              enum class WinApiAttr
              {
                Archive = 32, //Архивный
                Folder = 16, //Папка
                Hidden = 2, //Скрытый
                Normal = 128, //Не имеет других атрибутов
                ReadOnly = 1, //Только чтение
                System = 4 //Системный
              };
              
              /// <summary>
              /// Оператор, позволяющий формировать маски для флагов WinApiAttr
              /// </summary>
              inline WinApiAttr operator|(WinApiAttr a, WinApiAttr b)
              {
                return static_cast<WinApiAttr>(static_cast<int>(a), static_cast<int>(b));
              }
              
              /// <summary>
              /// Позволяет проверить установлена ли маска mask в WinApiAttr
              /// </summary>
              /// <param name="variable">Переменная</param>
              /// <param name="mask">Маска для проверки</param>
              inline bool IsFlagSet(WinApiAttr variable, WinApiAttr mask)
              {
                int m = static_cast<int>(mask);
                return (static_cast<int>(variable) & m)==m;
              }
              
              /// <summary>
              /// Валидатор корректности значения для флага WinApiAttr
              /// </summary>
              /// <param name="value">Значение для проверки</param>
              inline bool IsValidWinApiAttrValue(const int value)
              {
                return value <= 183;
              }
              #pragma endregion
              
              //Структуры
              #pragma region Messages and wrappers
              
              //Сообщения
              // Ответ на сообщение о перехвате вызова функции fflush
              BEGIN_MESSAGE(FFlushAnswer,86,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Код ошибки
                ARGUMENT(0, int, Error);
              END_MESSAGE(); // FFlushAnswer

              // Сообщение о перехвате вызова функции fflush
              BEGIN_MESSAGE(FFlushIntercepted,85,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // FFlushIntercepted

              // Ответ на сообщение о перехвате вызова функции fseek
              BEGIN_MESSAGE(FSeekAnswer,71,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Результат
                ARGUMENT(0, int, Errno);
              END_MESSAGE(); // FSeekAnswer

              // Сообщение о перехвате вызова функции fseek
              BEGIN_MESSAGE(FSeekIntercepted,70,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, FileHandle);
                // Количество байтов от Origin
                ARGUMENT(1, int, Offset);
                // Начальная позиция указателя
                ARGUMENT(2, int, Origin);
              END_MESSAGE(); // FSeekIntercepted

              // Ответ на сообщение о перехвате вызова функции ftell
              BEGIN_MESSAGE(FTellAnswer,77,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Размер файла
                ARGUMENT(0, int, FilePosition);
              END_MESSAGE(); // FTellAnswer

              // Сообщение о перехвате вызова функции ftell
              BEGIN_MESSAGE(FTellIntercepted,76,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, FileHandle);
              END_MESSAGE(); // FTellIntercepted

              // Ответ на сообщение о перехвате вызова функции fwrite
              BEGIN_MESSAGE(FWriteAnswer,83,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Число записаных элементов
                ARGUMENT(0, int, BytesWritten);
              END_MESSAGE(); // FWriteAnswer

              // Сообщение о перехвате вызова функции fwrite
              BEGIN_MESSAGE(FWriteIntercepted,82,4)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Число элементов
                ARGUMENT(0, int, Count);
                // Данные для записи
                ARGUMENT(1, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(1, data, len);
                }
                // Файловая переменная
                ARGUMENT(2, int, Handle);
                // Размер элемента
                ARGUMENT(3, int, ItemSize);
              END_MESSAGE(); // FWriteIntercepted

              // Ответ на сообщение о перехвате вызова функции fread
              BEGIN_MESSAGE(FreadAnswer,58,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // прочитанные символы
                ARGUMENT(0, ByteVector, Buffer);
                void SetBuffer(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(0, data, len);
                }
              END_MESSAGE(); // FreadAnswer

              // Ответ на перехваченный вызов функции GetCurrentDirectory
              BEGIN_MESSAGE(GetCurrentDirectoryAnswer,95,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Путь к текущей рабочей директории
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // GetCurrentDirectoryAnswer

              // Перехвачен вызов функции GetCurrentDirectory
              BEGIN_MESSAGE(GetCurrentDirectoryIntercepted,94,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // GetCurrentDirectoryIntercepted

              // Ответ на сообщение о перехвате вызова функции geterrno
              BEGIN_MESSAGE(GetErrNoAnswer,90,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Код ошибки
                ARGUMENT(0, int, Code);
              END_MESSAGE(); // GetErrNoAnswer

              // Сообщение о перехвате вызова функции geterrno
              BEGIN_MESSAGE(GetErrNoIntercepted,89,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // GetErrNoIntercepted

              // Ответ на сообщение о перехвате вызова функции read
              BEGIN_MESSAGE(ReadAnswer,92,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Прочитанный текст
                ARGUMENT(0, string, Text);
              END_MESSAGE(); // ReadAnswer

              // Сообщение о перехвате вызова функции read
              BEGIN_MESSAGE(ReadIntercepted,91,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
                // Режим чтения
                ENUM(1, ReadMode, Mode);
              END_MESSAGE(); // ReadIntercepted

              // Ответ на сообщение о перехвате вызова функции rewind
              BEGIN_MESSAGE(RewindAnswer,80,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // RewindAnswer

              // Сообщение о перехвате вызова функции rewind
              BEGIN_MESSAGE(RewindIntercepted,79,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // RewindIntercepted

              // Отправляется
              BEGIN_MESSAGE(SetCurrentDirectoryAnswer,98,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Код результата
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // SetCurrentDirectoryAnswer

              // Отправляется
              BEGIN_MESSAGE(SetCurrentDirectoryIntercepted,97,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Путь для установки текущей рабочей директории
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // SetCurrentDirectoryIntercepted

              // инициирует тестовый вызов fflush
              BEGIN_MESSAGE(TestFFlush,84,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Файловая переменная
                ARGUMENT(0, int, Handle);
              END_MESSAGE(); // TestFFlush

              // Инициирует тестовый вызов функции fseek
              BEGIN_MESSAGE(TestFSeek,69,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Количество байтов от Origin
                ARGUMENT(0, int, Offset);
                // Начальная позиция указателя
                ARGUMENT(1, int, Origin);
              END_MESSAGE(); // TestFSeek

              // Инициирует тестовый вызов функции ftell
              BEGIN_MESSAGE(TestFTell,75,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestFTell

              // инициирует тестовый вызов функции fwrite
              BEGIN_MESSAGE(TestFWrite,81,3)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Число элементов
                ARGUMENT(0, int, Count);
                // Данные для записи
                ARGUMENT(1, ByteVector, Data);
                void SetData(const unsigned char * data, const size_t len)
                {
                  SetArgument_ByteVector(1, data, len);
                }
                // Размер элемента
                ARGUMENT(2, int, ItemSize);
              END_MESSAGE(); // TestFWrite

              // Тестирование работы функции GetCurrentDirectory
              BEGIN_MESSAGE(TestGetCurrentDirectory,93,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestGetCurrentDirectory

              // Инициирует тестовый вызов функции rewind
              BEGIN_MESSAGE(TestRewind,78,0)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
              END_MESSAGE(); // TestRewind

              // Отправляется
              BEGIN_MESSAGE(TestSetCurrentDirectory,96,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // - Путь для установки текущей рабочей директории
                ARGUMENT(0, string, Path);
              END_MESSAGE(); // TestSetCurrentDirectory

              // Ответ на сообщение о перехвате вызова функции fsopen
              BEGIN_MESSAGE(_fsopenAnswer,88,1)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Код результата
                ARGUMENT(0, bool, Result);
              END_MESSAGE(); // _fsopenAnswer

              // Сообщение о перехвате вызова функции fsopen
              BEGIN_MESSAGE(_fsopenIntercepted,87,2)
                /// <summary>
                /// Инициализация сообщений
                /// </summary>
                void InitializeMessage()
                {
                }
                // Режим
                ARGUMENT(0, string, Mode);
                // Тип совместного использования.
                ARGUMENT(1, int, ShFlag);
              END_MESSAGE(); // _fsopenIntercepted

              
              BEGIN_WRAPPER()
                /// <summary> 
                /// Сообщение о перехвате вызова функции fflush
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void FFlushIntercepted(int handle) const
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fseek
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void FSeekIntercepted(int fileHandle, int offset, int origin) const
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции ftell
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                void FTellIntercepted(int fileHandle) const
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fwrite
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="itemSize">Размер элемента</param>
                void FWriteIntercepted(int count, const ByteVector & data, int handle, int itemSize) const
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Перехвачен вызов функции GetCurrentDirectory
                /// </summary>
                void GetCurrentDirectoryIntercepted() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции geterrno
                /// </summary>
                void GetErrNoIntercepted() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetErrNoIntercepted, 2); 
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции read
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="mode">Режим чтения</param>
                void ReadIntercepted(int handle, ReadMode mode) const
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции rewind
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RewindIntercepted(int handle) const
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправляется
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void SetCurrentDirectoryIntercepted(const string & path) const
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// инициирует тестовый вызов fflush
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void TestFFlush(int handle) const
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции fseek
                /// </summary>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void TestFSeek(int offset, int origin) const
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции ftell
                /// </summary>
                void TestFTell() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestFTell, 2); 
                }
                
                /// <summary> 
                /// инициирует тестовый вызов функции fwrite
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="itemSize">Размер элемента</param>
                void TestFWrite(int count, const ByteVector & data, int itemSize) const
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Тестирование работы функции GetCurrentDirectory
                /// </summary>
                void TestGetCurrentDirectory() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestGetCurrentDirectory, 2); 
                }
                
                /// <summary> 
                /// Инициирует тестовый вызов функции rewind
                /// </summary>
                void TestRewind() const
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestRewind, 2); 
                }
                
                /// <summary> 
                /// Отправляется
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void TestSetCurrentDirectory(const string & path) const
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Сообщение о перехвате вызова функции fsopen
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="shFlag">Тип совместного использования.</param>
                void _fsopenIntercepted(const string & mode, int shFlag) const
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_WRAPPER();
              
              BEGIN_IMPLEMENTATION()
                /// <summary> 
                /// Отправка события FFlushAnswer по адресу
                /// </summary>
                /// <param name="error">Код ошибки</param>
                void SendFFlushAnswer(address target, int error)
                {
                  G2::FFlushAnswer cmd;
                  cmd.SetError(error);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FFlushAnswer самому себе
                /// </summary>
                /// <param name="error">Код ошибки</param>
                void RaiseFFlushAnswer(int error)
                {
                  G2::FFlushAnswer cmd;
                  cmd.SetError(error);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FFlushIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendFFlushIntercepted(address target, int handle)
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FFlushIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseFFlushIntercepted(int handle)
                {
                  G2::FFlushIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FSeekAnswer по адресу
                /// </summary>
                /// <param name="errno">Результат</param>
                void SendFSeekAnswer(address target, int errno)
                {
                  G2::FSeekAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FSeekAnswer самому себе
                /// </summary>
                /// <param name="errno">Результат</param>
                void RaiseFSeekAnswer(int errno)
                {
                  G2::FSeekAnswer cmd;
                  cmd.SetErrno(errno);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FSeekIntercepted по адресу
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void SendFSeekIntercepted(address target, int fileHandle, int offset, int origin)
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FSeekIntercepted самому себе
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void RaiseFSeekIntercepted(int fileHandle, int offset, int origin)
                {
                  G2::FSeekIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FTellAnswer по адресу
                /// </summary>
                /// <param name="filePosition">Размер файла</param>
                void SendFTellAnswer(address target, int filePosition)
                {
                  G2::FTellAnswer cmd;
                  cmd.SetFilePosition(filePosition);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FTellAnswer самому себе
                /// </summary>
                /// <param name="filePosition">Размер файла</param>
                void RaiseFTellAnswer(int filePosition)
                {
                  G2::FTellAnswer cmd;
                  cmd.SetFilePosition(filePosition);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FTellIntercepted по адресу
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                void SendFTellIntercepted(address target, int fileHandle)
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FTellIntercepted самому себе
                /// </summary>
                /// <param name="fileHandle">Файловая переменная</param>
                void RaiseFTellIntercepted(int fileHandle)
                {
                  G2::FTellIntercepted cmd;
                  cmd.SetFileHandle(fileHandle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FWriteAnswer по адресу
                /// </summary>
                /// <param name="bytesWritten">Число записаных элементов</param>
                void SendFWriteAnswer(address target, int bytesWritten)
                {
                  G2::FWriteAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FWriteAnswer самому себе
                /// </summary>
                /// <param name="bytesWritten">Число записаных элементов</param>
                void RaiseFWriteAnswer(int bytesWritten)
                {
                  G2::FWriteAnswer cmd;
                  cmd.SetBytesWritten(bytesWritten);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FWriteIntercepted по адресу
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="itemSize">Размер элемента</param>
                void SendFWriteIntercepted(address target, int count, const ByteVector & data, int handle, int itemSize)
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FWriteIntercepted самому себе
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="itemSize">Размер элемента</param>
                void RaiseFWriteIntercepted(int count, const ByteVector & data, int handle, int itemSize)
                {
                  G2::FWriteIntercepted cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetHandle(handle);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события FreadAnswer по адресу
                /// </summary>
                /// <param name="buffer">прочитанные символы</param>
                void SendFreadAnswer(address target, const ByteVector & buffer)
                {
                  G2::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события FreadAnswer самому себе
                /// </summary>
                /// <param name="buffer">прочитанные символы</param>
                void RaiseFreadAnswer(const ByteVector & buffer)
                {
                  G2::FreadAnswer cmd;
                  cmd.SetBuffer(buffer);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetCurrentDirectoryAnswer по адресу
                /// </summary>
                /// <param name="path">- Путь к текущей рабочей директории</param>
                void SendGetCurrentDirectoryAnswer(address target, const string & path)
                {
                  G2::GetCurrentDirectoryAnswer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetCurrentDirectoryAnswer самому себе
                /// </summary>
                /// <param name="path">- Путь к текущей рабочей директории</param>
                void RaiseGetCurrentDirectoryAnswer(const string & path)
                {
                  G2::GetCurrentDirectoryAnswer cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetCurrentDirectoryIntercepted по адресу
                /// </summary>
                void SendGetCurrentDirectoryIntercepted(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                /// <summary> 
                /// Отправка события GetCurrentDirectoryIntercepted самому себе
                /// </summary>
                void RaiseGetCurrentDirectoryIntercepted()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetCurrentDirectoryIntercepted, 2); 
                }
                
                /// <summary> 
                /// Отправка события GetErrNoAnswer по адресу
                /// </summary>
                /// <param name="code">Код ошибки</param>
                void SendGetErrNoAnswer(address target, int code)
                {
                  G2::GetErrNoAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события GetErrNoAnswer самому себе
                /// </summary>
                /// <param name="code">Код ошибки</param>
                void RaiseGetErrNoAnswer(int code)
                {
                  G2::GetErrNoAnswer cmd;
                  cmd.SetCode(code);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события GetErrNoIntercepted по адресу
                /// </summary>
                void SendGetErrNoIntercepted(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::GetErrNoIntercepted, 2); 
                }
                /// <summary> 
                /// Отправка события GetErrNoIntercepted самому себе
                /// </summary>
                void RaiseGetErrNoIntercepted()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::GetErrNoIntercepted, 2); 
                }
                
                /// <summary> 
                /// Отправка события ReadAnswer по адресу
                /// </summary>
                /// <param name="text">Прочитанный текст</param>
                void SendReadAnswer(address target, const string & text)
                {
                  G2::ReadAnswer cmd;
                  cmd.SetText(text);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ReadAnswer самому себе
                /// </summary>
                /// <param name="text">Прочитанный текст</param>
                void RaiseReadAnswer(const string & text)
                {
                  G2::ReadAnswer cmd;
                  cmd.SetText(text);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события ReadIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="mode">Режим чтения</param>
                void SendReadIntercepted(address target, int handle, ReadMode mode)
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события ReadIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                /// <param name="mode">Режим чтения</param>
                void RaiseReadIntercepted(int handle, ReadMode mode)
                {
                  G2::ReadIntercepted cmd;
                  cmd.SetHandle(handle);
                  cmd.SetMode(mode);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события RewindAnswer по адресу
                /// </summary>
                void SendRewindAnswer(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::RewindAnswer, 2); 
                }
                /// <summary> 
                /// Отправка события RewindAnswer самому себе
                /// </summary>
                void RaiseRewindAnswer()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::RewindAnswer, 2); 
                }
                
                /// <summary> 
                /// Отправка события RewindIntercepted по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendRewindIntercepted(address target, int handle)
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события RewindIntercepted самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseRewindIntercepted(int handle)
                {
                  G2::RewindIntercepted cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetCurrentDirectoryAnswer по адресу
                /// </summary>
                /// <param name="result">Код результата</param>
                void SendSetCurrentDirectoryAnswer(address target, bool result)
                {
                  G2::SetCurrentDirectoryAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetCurrentDirectoryAnswer самому себе
                /// </summary>
                /// <param name="result">Код результата</param>
                void RaiseSetCurrentDirectoryAnswer(bool result)
                {
                  G2::SetCurrentDirectoryAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события SetCurrentDirectoryIntercepted по адресу
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void SendSetCurrentDirectoryIntercepted(address target, const string & path)
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события SetCurrentDirectoryIntercepted самому себе
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void RaiseSetCurrentDirectoryIntercepted(const string & path)
                {
                  G2::SetCurrentDirectoryIntercepted cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFFlush по адресу
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void SendTestFFlush(address target, int handle)
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFFlush самому себе
                /// </summary>
                /// <param name="handle">Файловая переменная</param>
                void RaiseTestFFlush(int handle)
                {
                  G2::TestFFlush cmd;
                  cmd.SetHandle(handle);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFSeek по адресу
                /// </summary>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void SendTestFSeek(address target, int offset, int origin)
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFSeek самому себе
                /// </summary>
                /// <param name="offset">Количество байтов от Origin</param>
                /// <param name="origin">Начальная позиция указателя</param>
                void RaiseTestFSeek(int offset, int origin)
                {
                  G2::TestFSeek cmd;
                  cmd.SetOffset(offset);
                  cmd.SetOrigin(origin);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestFTell по адресу
                /// </summary>
                void SendTestFTell(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestFTell, 2); 
                }
                /// <summary> 
                /// Отправка события TestFTell самому себе
                /// </summary>
                void RaiseTestFTell()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestFTell, 2); 
                }
                
                /// <summary> 
                /// Отправка события TestFWrite по адресу
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="itemSize">Размер элемента</param>
                void SendTestFWrite(address target, int count, const ByteVector & data, int itemSize)
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestFWrite самому себе
                /// </summary>
                /// <param name="count">Число элементов</param>
                /// <param name="data">Данные для записи</param>
                /// <param name="itemSize">Размер элемента</param>
                void RaiseTestFWrite(int count, const ByteVector & data, int itemSize)
                {
                  G2::TestFWrite cmd;
                  cmd.SetCount(count);
                  cmd.SetData(data);
                  cmd.SetItemSize(itemSize);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события TestGetCurrentDirectory по адресу
                /// </summary>
                void SendTestGetCurrentDirectory(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestGetCurrentDirectory, 2); 
                }
                /// <summary> 
                /// Отправка события TestGetCurrentDirectory самому себе
                /// </summary>
                void RaiseTestGetCurrentDirectory()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestGetCurrentDirectory, 2); 
                }
                
                /// <summary> 
                /// Отправка события TestRewind по адресу
                /// </summary>
                void SendTestRewind(address target)
                {
                  m_RequestDispatcher->SendEvent(target, G2::Codes::TestRewind, 2); 
                }
                /// <summary> 
                /// Отправка события TestRewind самому себе
                /// </summary>
                void RaiseTestRewind()
                {
                  m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::TestRewind, 2); 
                }
                
                /// <summary> 
                /// Отправка события TestSetCurrentDirectory по адресу
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void SendTestSetCurrentDirectory(address target, const string & path)
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события TestSetCurrentDirectory самому себе
                /// </summary>
                /// <param name="path">- Путь для установки текущей рабочей директории</param>
                void RaiseTestSetCurrentDirectory(const string & path)
                {
                  G2::TestSetCurrentDirectory cmd;
                  cmd.SetPath(path);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события _fsopenAnswer по адресу
                /// </summary>
                /// <param name="result">Код результата</param>
                void Send_fsopenAnswer(address target, bool result)
                {
                  G2::_fsopenAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события _fsopenAnswer самому себе
                /// </summary>
                /// <param name="result">Код результата</param>
                void Raise_fsopenAnswer(bool result)
                {
                  G2::_fsopenAnswer cmd;
                  cmd.SetResult(result);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
                /// <summary> 
                /// Отправка события _fsopenIntercepted по адресу
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="shFlag">Тип совместного использования.</param>
                void Send_fsopenIntercepted(address target, const string & mode, int shFlag)
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(target, cmd);
                }
                /// <summary> 
                /// Отправка события _fsopenIntercepted самому себе
                /// </summary>
                /// <param name="mode">Режим</param>
                /// <param name="shFlag">Тип совместного использования.</param>
                void Raise_fsopenIntercepted(const string & mode, int shFlag)
                {
                  G2::_fsopenIntercepted cmd;
                  cmd.SetMode(mode);
                  cmd.SetShFlag(shFlag);
                  m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
                }
                
              END_IMPLEMENTATION();
              
              #pragma endregion
            END_PROTOCOL()
            
            } // пространство имен Protocol
          } // пространство имен Interceptor
        } // пространство имен FileSystem
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
