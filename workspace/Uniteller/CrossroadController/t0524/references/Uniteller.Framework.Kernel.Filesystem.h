// Uniteller.Framework.Kernel.FileSystem

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText, 
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

// Используемые протоколы
#include "Uniteller.Framework.Kernel.FileSystem.Interceptor.h"
using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace FileSystem
      {
        namespace Protocol
        {
          // Подключаем используемые внешние типы из других протоколов
          using Uniteller::Framework::Kernel::FileSystem::Interceptor::Protocol::G1::WinApiAttr;
          using Uniteller::Framework::Kernel::FileSystem::Interceptor::Protocol::G1::IsValidWinApiAttrValue;

          BEGIN_PROTOCOL(8, 1)
            
            #pragma region Enumerations
            /// <summary> 
            /// Специфичные ошибки при работе с файловой системой
            /// </summary>
            #pragma endregion
            
            #pragma region Flags
            
            /// <summary> 
            /// Файловые атрибуты. На разных некоторые из атрибутов отсутствуют
            /// </summary>
            /// <summary> 
            /// Какие проверки выполнять при сравнении папок
            /// </summary>
            #pragma endregion
            
            //Структуры
            #pragma region Messages and wrappers
            
            //Сообщения
            
            BEGIN_WRAPPER()
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          

          BEGIN_PROTOCOL(8, 2)
            
            #pragma region Enumerations
            /// <summary> 
            /// Специфичные ошибки при работе с файловой системой
            /// </summary>
            enum class Errors
            {
              AccessDenied = 1, // Система запретила доступ к указанному файлу или директории (из-за прав доступа или из-за того, что он используется другим процессом)
              AlreadyExists = 2, // Файл или папка уже существует
              FileSystemFailure = 3, // Отказ файловой системы
              InvalidArgument = 4, // Неправильный аргумент
              NotExist = 5, // Файл или папка не существует
              OutOfSpace = 6 // Недостаточно дискового пространства для исполнения операции
            };
            
            /// <summary>
            /// Валидатор корректности значения для перечислимого типа Errors
            /// </summary>
            inline bool IsValidErrorsValue(const int value)
            {
              return ((value >= 1)&&(value < 7));
            }
            
            /// <summary>
            /// Следует использовать для преобразования числовых значений к перечислимому типу Errors
            /// </summary>
            inline Errors ConvertToErrors(const int value)
            {
              switch (value)
              {
                case 1:
                  return Errors::AccessDenied;
                case 2:
                  return Errors::AlreadyExists;
                case 3:
                  return Errors::FileSystemFailure;
                case 4:
                  return Errors::InvalidArgument;
                case 5:
                  return Errors::NotExist;
                case 6:
                  return Errors::OutOfSpace;
                default: throw KernelException("Невозможно преобразовать числовое значение %d к типу Errors", value);
                }
            }
            
            #pragma endregion
            
            #pragma region Flags
            
            /// <summary> 
            /// Файловые атрибуты. На разных некоторые из атрибутов отсутствуют
            /// </summary>
            enum class Attributes
            {
              Archive = 1, //Windows
              GroupExecute = 2, //UNIX
              GroupRead = 4, //UNIX
              GroupWrite = 8, //UNIX
              Hidden = 16, //Windows
              OthersExecute = 32, //UNIX
              OthersRead = 64, //UNIX
              OthersWrite = 128, //UNIX
              OwnerExecute = 256, //UNIX
              OwnerRead = 512, //UNIX
              OwnerWrite = 1024, //UNIX
              ReadOnly = 2048, //Windows
              System = 4096 //Windows
            };
            
            /// <summary>
            /// Оператор, позволяющий формировать маски для флагов Attributes
            /// </summary>
            inline Attributes operator|(Attributes a, Attributes b)
            {
              return static_cast<Attributes>(static_cast<int>(a), static_cast<int>(b));
            }
            
            /// <summary>
            /// Позволяет проверить установлена ли маска mask в Attributes
            /// </summary>
            /// <param name="variable">Переменная</param>
            /// <param name="mask">Маска для проверки</param>
            inline bool IsFlagSet(Attributes variable, Attributes mask)
            {
              int m = static_cast<int>(mask);
              return (static_cast<int>(variable) & m)==m;
            }
            
            /// <summary>
            /// Валидатор корректности значения для флага Attributes
            /// </summary>
            /// <param name="value">Значение для проверки</param>
            inline bool IsValidAttributesValue(const int value)
            {
              return value <= 8191;
            }
            /// <summary> 
            /// Какие проверки выполнять при сравнении папок
            /// </summary>
            enum class CompareTests
            {
              Content = 1, //Сравнить по содержимому
              Date = 2, //Сравнить по дате
              Recursive = 4, //Сравнивать подкаталоги рекурсивно
              Size = 8 //Сравнить по размеру
            };
            
            /// <summary>
            /// Оператор, позволяющий формировать маски для флагов CompareTests
            /// </summary>
            inline CompareTests operator|(CompareTests a, CompareTests b)
            {
              return static_cast<CompareTests>(static_cast<int>(a), static_cast<int>(b));
            }
            
            /// <summary>
            /// Позволяет проверить установлена ли маска mask в CompareTests
            /// </summary>
            /// <param name="variable">Переменная</param>
            /// <param name="mask">Маска для проверки</param>
            inline bool IsFlagSet(CompareTests variable, CompareTests mask)
            {
              int m = static_cast<int>(mask);
              return (static_cast<int>(variable) & m)==m;
            }
            
            /// <summary>
            /// Валидатор корректности значения для флага CompareTests
            /// </summary>
            /// <param name="value">Значение для проверки</param>
            inline bool IsValidCompareTestsValue(const int value)
            {
              return value <= 15;
            }
            #pragma endregion
            
            //Структуры
            #pragma region Messages and wrappers
            
            //Сообщения
            // Склеить путь из двух отдельных путей (InvalidArgument)
            BEGIN_MESSAGE(AppendPath,3,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Только относительный путь
              ARGUMENT(0, string, PathEnd);
              // Абсолютный или относительный путь (наличие в конце разделителя не имеет значения)
              ARGUMENT(1, string, PathStart);
            END_MESSAGE(); // AppendPath

            // Ответ на AppendPath
            BEGIN_MESSAGE(AppendPathAnswer,4,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Готовый путь с текущими символами разделителя
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // AppendPathAnswer

            // Удаляет все файлы и директории из указанной директории (InvalidArgument, AccessDenied, NotExist)
            BEGIN_MESSAGE(ClearFolder,11,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMask("*");
              }
              // Маска для имени файла или директории. Астериском "*" заменяются несколько символов. Удаляются только те директории и файлы которые соответствуют маске.
              ARGUMENT(0, string, Mask);
              // Путь (абсолютный или относительный) с системными символами разделителя
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // ClearFolder

            // Отправляется в случае успешной очистки папки
            BEGIN_MESSAGE(ClearFolderAnswer,42,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // ClearFolderAnswer

            // Сравнивает два файла (InvalidArgument,NotExist,AccessDenied)
            BEGIN_MESSAGE(CompareFiles,22,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь (абсолютный или относительный) к первому файлу для сравнения
              ARGUMENT(0, string, File1);
              // Путь (абсолютный или относительный) ко второму файлу для сравнения
              ARGUMENT(1, string, File2);
            END_MESSAGE(); // CompareFiles

            // Ответ на CompareFiles
            BEGIN_MESSAGE(CompareFilesAnswer,23,5)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Возвращает true если атрибуты файлов совпадают иначе false
              ARGUMENT(0, bool, EqAttributes);
              // Возвращает true если содержимое файлов совпадает иначе false
              ARGUMENT(1, bool, EqContent);
              // Возвращает true если дата создания файлов совпадает иначе false
              ARGUMENT(2, bool, EqDateCreation);
              // Возвращает true если даты изменения файлов совпадают иначе false
              ARGUMENT(3, bool, EqDateMod);
              // Возвращает true если размеры файлов совпадают иначе false
              ARGUMENT(4, bool, EqSize);
            END_MESSAGE(); // CompareFilesAnswer

            // Сравнивает две папки в соответствии с параметрами (InvalidArgument,NotExist,AccessDenied). Все символьные ссылки игнорируются и не участвуют в проверке.
            BEGIN_MESSAGE(CompareFolders,24,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь (абсолютный или относительный) к первой папке
              ARGUMENT(0, string, File1);
              // Путь (абсолютный или относительный) ко второй папке
              ARGUMENT(1, string, File2);
              // Какие проверки выполнять. Если не указана ни одна сравниваются только имена файлов
              FLAG(2, CompareTests, Test);
            END_MESSAGE(); // CompareFolders

            // CompareFolders
            BEGIN_MESSAGE(CompareFoldersAnswer,25,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // даты создания папок указанных в параметрах совпадают
              ARGUMENT(0, bool, EqDateCreation);
              // даты изменения папок указанных в параметрах совпадают
              ARGUMENT(1, bool, EqDateMod);
              // true - в соответствии с указанными во входных параметрах критериями папки совпадают
              ARGUMENT(2, bool, Equal);
            END_MESSAGE(); // CompareFoldersAnswer

            // Копирует файл. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(CopyFile,16,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к файлу куда надо копировать с системными символами разделителя. Если файл существует то он будет перезаписан.
              ARGUMENT(0, string, DestPath);
              // Путь к файлу (абсолютный или относительный) который надо копировать с системными символами разделителя. Использование "*" запрещено.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFile

            // Отправляется в случае, если файл был успешно скопирован
            BEGIN_MESSAGE(CopyFileAnswer,31,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFileAnswer

            // Копирует файл. Поддерживается символ * для замены части названия файла, при его использовании обрабатываются все соответствующие маске файлы. Существующие файлы перезаписываются. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(CopyFileToFolder,32,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к папке (абсолютный или относительный) куда надо копировать с системными символами разделителя. Использование "*" запрещено. Если файл существует то он будет перезаписан.
              ARGUMENT(0, string, DestPath);
              // Путь к файлу (абсолютный или относительный) который надо копировать с системными символами разделителя может содержать "*"
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFileToFolder

            // Отправляется в случае, если файл был успешно скопирован
            BEGIN_MESSAGE(CopyFileToFolderAnswer,33,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFileToFolderAnswer

            // Копирует папку  (InvalidArgument, AccessDenied). Всё содержимое также копируется, существующие файлы перезаписываются.
            BEGIN_MESSAGE(CopyFolder,20,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к папке (абсолютный или относительный) в которую надо копировать указанную папку с системными символами разделителя
              ARGUMENT(0, string, DestPath);
              // Путь к папке (абсолютный или относительный) которую надо копировать с системными символами разделителя
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // CopyFolder

            // Отправляется в случае, если каталог был успешно скопирован
            BEGIN_MESSAGE(CopyFolderAnswer,30,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CopyFolderAnswer

            // Создать папку по указанному пути. Если путь не существует, то он создается. (InvalidArgument, AlreadyExists)
            BEGIN_MESSAGE(CreateFolder,9,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Абсолютный путь с системными символами разделителя (InvalidArgument AccessDenied)
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // CreateFolder

            // Отправляется в случае успешного создания папки
            BEGIN_MESSAGE(CreateFolderAnswer,40,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // CreateFolderAnswer

            // Удаление файла по имени
            BEGIN_MESSAGE(DeleteFile,44,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Имя удаляемого файла
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // DeleteFile

            // Отправляется в случае успешного даления файла
            BEGIN_MESSAGE(DeleteFileAnswer,45,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат удаления
              ARGUMENT(0, bool, Result);
            END_MESSAGE(); // DeleteFileAnswer

            // Удалить файлы по маске
            BEGIN_MESSAGE(DeleteFiles,46,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Имя директории в которой будет начат поиск подходящих файлов.
              ARGUMENT(0, string, FolderName);
              // Маска для имен файлов
              ARGUMENT(1, string, Mask);
              // Удалять ли подходящие файлы в поддиректориях
              ARGUMENT(2, bool, Recursively);
            END_MESSAGE(); // DeleteFiles

            // Отправляется в случае успешного удаления файлов.
            BEGIN_MESSAGE(DeleteFilesAnswer,47,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Количество удаленных файлов
              ARGUMENT(0, int, FilesDeleted);
            END_MESSAGE(); // DeleteFilesAnswer

            // Удаляет папку вместе со всем содержимым. Если папка не существует, ошибка не возвращается.
            BEGIN_MESSAGE(DeleteFolder,10,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь (абсолютный или относительный) с системными символами разделителя
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // DeleteFolder

            // Отправляется в случае успешного удаления папки
            BEGIN_MESSAGE(DeleteFolderAnswer,41,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // DeleteFolderAnswer

            // Ответ в случае какой-либо специфической ошибки
            BEGIN_MESSAGE(Error,28,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Какая именно ошбика произошла
              ENUM(0, Errors, ErrorValue);
            END_MESSAGE(); // Error

            // Из указанного пути возвращается название файла (InvalidArgument). Название файла - это компонент пути после последнего разделителя.
            BEGIN_MESSAGE(ExtractFilename,12,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь (абсолютный или относительный) с системными символами разделителя
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractFilename

            // Ответ на ExtractFilename
            BEGIN_MESSAGE(ExtractFilenameAnswer,13,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Название файла. Может быть пустым если в запросе был передан путь без символов после последнего разделителя.
              ARGUMENT(0, string, Name);
            END_MESSAGE(); // ExtractFilenameAnswer

            // Из указанного пути удаляется название файла, после чего он возвращается (InvalidArgument)
            BEGIN_MESSAGE(ExtractPath,14,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Исходный путь (абсолютный или относительный)
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractPath

            // Ответ на ExtractPath
            BEGIN_MESSAGE(ExtractPathAnswer,15,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь с системными символами разделителя. Может быть "\\" если в запросе не было символов перед единственным разделителем.
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // ExtractPathAnswer

            // Определяет, существует ли указанный файл. Папку за файл не считает. (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(FileExists,7,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь (абсолютный или относительный) с системными символами разделителя
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // FileExists

            // Ответ на FileExists
            BEGIN_MESSAGE(FileExistsAnswer,8,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // true - существует false - не существует
              ARGUMENT(0, bool, Exists);
            END_MESSAGE(); // FileExistsAnswer

            // Закрытие поиска
            BEGIN_MESSAGE(FindClose,38,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Индекс открытого поиска
              ARGUMENT(0, int, SearchIndex);
            END_MESSAGE(); // FindClose

            // Результат закрытия поиска сообщается в этом ответе
            BEGIN_MESSAGE(FindCloseAnswer,39,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Результат закрытия поиска
              ARGUMENT(0, bool, Result);
            END_MESSAGE(); // FindCloseAnswer

            // Ищет файл или папку
            BEGIN_MESSAGE(FindFirst,34,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Маска поиска
              ARGUMENT(0, string, Mask);
              // Путь по которому осуществляется поиск (абсолютный или относительный) может содержать "*"
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // FindFirst

            // Отправляется если файл (папка) успешно найден(а)
            BEGIN_MESSAGE(FindFirstAnswer,35,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Атрибуты файла
              FLAG(0, WinApiAttr, Attributes);
              // Имя файла
              ARGUMENT(1, string, FileName);
              // Индекс открытого поиска
              ARGUMENT(2, int, SearchIndex);
            END_MESSAGE(); // FindFirstAnswer

            // Ищет следующий файл или папку
            BEGIN_MESSAGE(FindNext,36,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Индекс открытого поиска
              ARGUMENT(0, int, SearchIndex);
            END_MESSAGE(); // FindNext

            // Результат поиска следующего файла сообщается в этом ответе
            BEGIN_MESSAGE(FindNextAnswer,37,3)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Атрибуты файла
              FLAG(0, WinApiAttr, Attributes);
              // Имя файла
              ARGUMENT(1, string, FileName);
              // Результат поиска следующего файла
              ARGUMENT(2, bool, Result);
            END_MESSAGE(); // FindNextAnswer

            // Определяет, существует ли указанная папка (InvalidArgument)
            BEGIN_MESSAGE(FolderExists,5,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к папке (абсолютный или относительный) с системным символом разделителя
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // FolderExists

            // Ответ на FolderExists
            BEGIN_MESSAGE(FolderExistsAnswer,6,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // true - существует false - не существует
              ARGUMENT(0, bool, Exists);
            END_MESSAGE(); // FolderExistsAnswer

            // Получить имена поддиректорий в указанной директории
            BEGIN_MESSAGE(GetDirectories,48,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Директория где будет производиться поиск
              ARGUMENT(0, string, FolderName);
            END_MESSAGE(); // GetDirectories

            // Возврат списка поддиректорий для указанной директории
            BEGIN_MESSAGE(GetDirectoriesAnswer,49,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Список полных имен поддиректорий находящихся в указанной директории
              ARGUMENT(0, StringList, Names);
            END_MESSAGE(); // GetDirectoriesAnswer

            // Получить расширение из имени файла
            BEGIN_MESSAGE(GetExtension,54,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Полный или относительный путь к файлу и иего имя с расширением
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetExtension

            // Возврат расширения из имени файла
            BEGIN_MESSAGE(GetExtensionAnswer,55,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Расширение из имени файла
              ARGUMENT(0, string, Extension);
            END_MESSAGE(); // GetExtensionAnswer

            // Получает информацию об указанном файле или папке (InvalidArgument, NotExist)
            BEGIN_MESSAGE(GetFileInfo,26,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к файлу или папке (абсолютный или относительный) с системными разделителями
              ARGUMENT(0, string, Path);
            END_MESSAGE(); // GetFileInfo

            // Ответ на GetFileInfo
            BEGIN_MESSAGE(GetFileInfoAnswer,27,4)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Атрибуты
              FLAG(0, Attributes, Attr);
              // Дата создания файла
              ARGUMENT(1, timestamp_t, DateCreation);
              // Дата изменения файла
              ARGUMENT(2, timestamp_t, DateMod);
              // Размер файла в байтах
              ARGUMENT(3, int, Size);
            END_MESSAGE(); // GetFileInfoAnswer

            // Получить имя файла без расширения
            BEGIN_MESSAGE(GetFileNameWithoutExtension,52,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Полный или относительный путь к файлу и иего имя с расширением
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetFileNameWithoutExtension

            // Возврат полученного имени файла без расширения
            BEGIN_MESSAGE(GetFileNameWithoutExtensionAnswer,53,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Имя фаяла без расширения
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetFileNameWithoutExtensionAnswer

            // Получить имена файлов в указанной директории
            BEGIN_MESSAGE(GetFiles,50,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMask("*");
              }
              // Директория где будет производиться поиск
              ARGUMENT(0, string, FolderName);
              // Маска для имен файлов.
              ARGUMENT(1, string, Mask);
            END_MESSAGE(); // GetFiles

            // Возврат списка файлов для указанной директории
            BEGIN_MESSAGE(GetFilesAnswer,51,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Список полных имен файлов находящихся в указанной директории
              ARGUMENT(0, StringList, Names);
            END_MESSAGE(); // GetFilesAnswer

            // Получить количество файлов, удовлетворяющим заданной маске, в заданной папке
            BEGIN_MESSAGE(GetFilesCount,56,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // маска
              ARGUMENT(0, string, Mask);
              // абсолютный путь к папке
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetFilesCount

            // Возврат полученного количества файлов
            BEGIN_MESSAGE(GetFilesCountAnswer,57,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // количество файлов
              ARGUMENT(0, int, Count);
            END_MESSAGE(); // GetFilesCountAnswer

            // Получить самый новый файл в заданной папке с именем, удовлетворяющим заданной маске
            BEGIN_MESSAGE(GetMostRecentFileName,60,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // маска
              ARGUMENT(0, string, Mask);
              // абсолютный путь к папке
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetMostRecentFileName

            // Возврат имени самого нового файла
            BEGIN_MESSAGE(GetMostRecentFileNameAnswer,61,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // имя файла
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetMostRecentFileNameAnswer

            // Получить старейший файл в заданной папке с именем, удовлетворяющим заданной маске
            BEGIN_MESSAGE(GetOldestFileName,58,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
                SetMask(".");
              }
              // маска
              ARGUMENT(0, string, Mask);
              // абсолютный путь к папке
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // GetOldestFileName

            // Возврат имени старейшего файла
            BEGIN_MESSAGE(GetOldestFileNameAnswer,59,1)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // имя файла
              ARGUMENT(0, string, FileName);
            END_MESSAGE(); // GetOldestFileNameAnswer

            // Перемещает один указанный файл или папку  (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(MoveFile,17,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к существующей папке (абсолютный или относительный) в которую надо выполнить перемещение.
              ARGUMENT(0, string, DestPath);
              // Путь к файлу или папке (абсолютный или относительный) которую надо переместить с системными символами разделителя. По окончании операции этот файл будет удален.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // MoveFile

            // Результат перемещения файла сообщается в этом ответе
            BEGIN_MESSAGE(MoveFileAnswer,19,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // MoveFileAnswer

            // Перемещает или переименовывает один указанный файл или папку (InvalidArgument, AccessDenied)
            BEGIN_MESSAGE(RenameFile,18,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Путь к файлу или папке (абсолютный или относительный). Исходный файл или папка будет переименована в соответствии с этим путем.
              ARGUMENT(0, string, DestPath);
              // Путь к файлу или папке (абсолютный или относительный) которую надо переместить с системными символами разделителя. По окончании операции этот файл будет удален.
              ARGUMENT(1, string, SrcPath);
            END_MESSAGE(); // RenameFile

            // Результат перемещения файла сообщается в этом ответе
            BEGIN_MESSAGE(RenameFileAnswer,29,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // true если конечный файл был успешно создан иначе false
              ARGUMENT(0, bool, DestCreated);
              // true если исходный файл был успешно удален иначе false
              ARGUMENT(1, bool, SrcRemoved);
            END_MESSAGE(); // RenameFileAnswer

            // Устанавливает атрибуты файла, несколько атрибутов соединяются по ИЛИ (AccessDenied)
            BEGIN_MESSAGE(SetFolderContentAttributes,21,2)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
              // Атрибуты файла
              FLAG(0, WinApiAttr, Attr);
              // Путь с системными символами разделителя (абсолютный или относительный)
              ARGUMENT(1, string, Path);
            END_MESSAGE(); // SetFolderContentAttributes

            // Отправляется в случае успешной установки атрибутов
            BEGIN_MESSAGE(SetFolderContentAttributesAnswer,43,0)
              /// <summary>
              /// Инициализация сообщений
              /// </summary>
              void InitializeMessage()
              {
              }
            END_MESSAGE(); // SetFolderContentAttributesAnswer

            
            BEGIN_WRAPPER()
              /// <summary> 
              /// Склеить путь из двух отдельных путей (InvalidArgument)
              /// </summary>
              /// <param name="pathEnd">Только относительный путь</param>
              /// <param name="pathStart">Абсолютный или относительный путь (наличие в конце разделителя не имеет значения)</param>
              void AppendPath(const string & pathEnd, const string & pathStart) const
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Удаляет все файлы и директории из указанной директории (InvalidArgument, AccessDenied, NotExist)
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              /// <param name="Mask">Маска для имени файла или директории. Астериском "*" заменяются несколько символов. Удаляются только те директории и файлы, которые соответствуют маске.</param>
              void ClearFolder(const string & path, string mask = "*") const
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Сравнивает два файла (InvalidArgument,NotExist,AccessDenied)
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первому файлу для сравнения</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второму файлу для сравнения</param>
              void CompareFiles(const string & file1, const string & file2) const
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Сравнивает две папки в соответствии с параметрами (InvalidArgument,NotExist,AccessDenied). Все символьные ссылки игнорируются и не участвуют в проверке.
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первой папке</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второй папке</param>
              /// <param name="test">Какие проверки выполнять. Если не указана ни одна, сравниваются только имена файлов</param>
              void CompareFolders(const string & file1, const string & file2, CompareTests test) const
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Копирует файл. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">Путь к файлу, куда надо копировать, с системными символами разделителя. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя. Использование "*" запрещено.</param>
              void CopyFile(const string & destPath, const string & srcPath) const
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Копирует файл. Поддерживается символ * для замены части названия файла, при его использовании обрабатываются все соответствующие маске файлы. Существующие файлы перезаписываются. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), куда надо копировать, с системными символами разделителя. Использование "*" запрещено. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя, может содержать "*"</param>
              void CopyFileToFolder(const string & destPath, const string & srcPath) const
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Копирует папку  (InvalidArgument, AccessDenied). Всё содержимое также копируется, существующие файлы перезаписываются.
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), в которую надо копировать указанную папку, с системными символами разделителя</param>
              /// <param name="srcPath">Путь к папке (абсолютный или относительный), которую надо копировать, с системными символами разделителя</param>
              void CopyFolder(const string & destPath, const string & srcPath) const
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Создать папку по указанному пути. Если путь не существует, то он создается. (InvalidArgument, AlreadyExists)
              /// </summary>
              /// <param name="path">Абсолютный путь с системными символами разделителя (InvalidArgument, AccessDenied)</param>
              void CreateFolder(const string & path) const
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Удаление файла по имени
              /// </summary>
              /// <param name="fileName">Имя удаляемого файла</param>
              void DeleteFile(const string & fileName) const
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Удалить файлы по маске
              /// </summary>
              /// <param name="folderName">Имя директории, в которой будет начат поиск подходящих файлов.</param>
              /// <param name="mask">Маска для имен файлов</param>
              /// <param name="recursively">Удалять ли подходящие файлы в поддиректориях</param>
              void DeleteFiles(const string & folderName, const string & mask, bool recursively) const
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Удаляет папку вместе со всем содержимым. Если папка не существует, ошибка не возвращается.
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void DeleteFolder(const string & path) const
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ответ в случае какой-либо специфической ошибки
              /// </summary>
              /// <param name="errorValue">Какая именно ошбика произошла</param>
              void Error(Errors errorValue) const
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Из указанного пути возвращается название файла (InvalidArgument). Название файла - это компонент пути после последнего разделителя.
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void ExtractFilename(const string & path) const
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Из указанного пути удаляется название файла, после чего он возвращается (InvalidArgument)
              /// </summary>
              /// <param name="path">Исходный путь (абсолютный или относительный)</param>
              void ExtractPath(const string & path) const
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Определяет, существует ли указанный файл. Папку за файл не считает. (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void FileExists(const string & path) const
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Закрытие поиска
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void FindClose(int searchIndex) const
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ищет файл или папку
              /// </summary>
              /// <param name="mask">Маска поиска</param>
              /// <param name="path">Путь, по которому осуществляется поиск (абсолютный или относительный), может содержать "*"</param>
              void FindFirst(const string & mask, const string & path) const
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Ищет следующий файл или папку
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void FindNext(int searchIndex) const
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Определяет, существует ли указанная папка (InvalidArgument)
              /// </summary>
              /// <param name="path">Путь к папке (абсолютный или относительный) с системным символом разделителя</param>
              void FolderExists(const string & path) const
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить имена поддиректорий в указанной директории
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              void GetDirectories(const string & folderName) const
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить расширение из имени файла
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void GetExtension(const string & fileName) const
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получает информацию об указанном файле или папке (InvalidArgument, NotExist)
              /// </summary>
              /// <param name="path">Путь к файлу или папке (абсолютный или относительный) с системными разделителями</param>
              void GetFileInfo(const string & path) const
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить имя файла без расширения
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void GetFileNameWithoutExtension(const string & fileName) const
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить имена файлов в указанной директории
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              /// <param name="Mask">Маска для имен файлов.</param>
              void GetFiles(const string & folderName, string mask = "*") const
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить количество файлов, удовлетворяющим заданной маске, в заданной папке
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="Mask">маска</param>
              void GetFilesCount(const string & path, string mask = "::") const
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить самый новый файл в заданной папке с именем, удовлетворяющим заданной маске
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="Mask">маска</param>
              void GetMostRecentFileName(const string & path, string mask = "::") const
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Получить старейший файл в заданной папке с именем, удовлетворяющим заданной маске
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="Mask">маска</param>
              void GetOldestFileName(const string & path, string mask = "::") const
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Перемещает один указанный файл или папку  (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">Путь к существующей папке (абсолютный или относительный), в которую надо выполнить перемещение.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void MoveFile(const string & destPath, const string & srcPath) const
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Перемещает или переименовывает один указанный файл или папку (InvalidArgument, AccessDenied)
              /// </summary>
              /// <param name="destPath">Путь к файлу или папке (абсолютный или относительный). Исходный файл или папка будет переименована в соответствии с этим путем.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void RenameFile(const string & destPath, const string & srcPath) const
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Устанавливает атрибуты файла, несколько атрибутов соединяются по ИЛИ (AccessDenied)
              /// </summary>
              /// <param name="attr">Атрибуты файла</param>
              /// <param name="path">Путь с системными символами разделителя (абсолютный или относительный)</param>
              void SetFolderContentAttributes(WinApiAttr attr, const string & path) const
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
            END_WRAPPER();
            
            BEGIN_IMPLEMENTATION()
              /// <summary> 
              /// Отправка события AppendPath по адресу
              /// </summary>
              /// <param name="pathEnd">Только относительный путь</param>
              /// <param name="pathStart">Абсолютный или относительный путь (наличие в конце разделителя не имеет значения)</param>
              void SendAppendPath(address target, const string & pathEnd, const string & pathStart)
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события AppendPath самому себе
              /// </summary>
              /// <param name="pathEnd">Только относительный путь</param>
              /// <param name="pathStart">Абсолютный или относительный путь (наличие в конце разделителя не имеет значения)</param>
              void RaiseAppendPath(const string & pathEnd, const string & pathStart)
              {
                G2::AppendPath cmd;
                cmd.SetPathEnd(pathEnd);
                cmd.SetPathStart(pathStart);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события AppendPathAnswer по адресу
              /// </summary>
              /// <param name="path">Готовый путь с текущими символами разделителя</param>
              void SendAppendPathAnswer(address target, const string & path)
              {
                G2::AppendPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события AppendPathAnswer самому себе
              /// </summary>
              /// <param name="path">Готовый путь с текущими символами разделителя</param>
              void RaiseAppendPathAnswer(const string & path)
              {
                G2::AppendPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ClearFolder по адресу
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              /// <param name="mask">Маска для имени файла или директории. Астериском "*" заменяются несколько символов. Удаляются только те директории и файлы, которые соответствуют маске.</param>
              void SendClearFolder(address target, const string & path, const string & mask = "*")
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ClearFolder самому себе
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              /// <param name="mask">Маска для имени файла или директории. Астериском "*" заменяются несколько символов. Удаляются только те директории и файлы, которые соответствуют маске.</param>
              void RaiseClearFolder(const string & path, const string & mask = "*")
              {
                G2::ClearFolder cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ClearFolderAnswer по адресу
              /// </summary>
              void SendClearFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::ClearFolderAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события ClearFolderAnswer самому себе
              /// </summary>
              void RaiseClearFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::ClearFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события CompareFiles по адресу
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первому файлу для сравнения</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второму файлу для сравнения</param>
              void SendCompareFiles(address target, const string & file1, const string & file2)
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CompareFiles самому себе
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первому файлу для сравнения</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второму файлу для сравнения</param>
              void RaiseCompareFiles(const string & file1, const string & file2)
              {
                G2::CompareFiles cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CompareFilesAnswer по адресу
              /// </summary>
              /// <param name="eqAttributes">Возвращает true, если атрибуты файлов совпадают, иначе false</param>
              /// <param name="eqContent">Возвращает true, если содержимое файлов совпадает, иначе false</param>
              /// <param name="eqDateCreation">Возвращает true, если дата создания файлов совпадает, иначе false</param>
              /// <param name="eqDateMod">Возвращает true, если даты изменения файлов совпадают, иначе false</param>
              /// <param name="eqSize">Возвращает true, если размеры файлов совпадают, иначе false</param>
              void SendCompareFilesAnswer(address target, bool eqAttributes, bool eqContent, bool eqDateCreation, bool eqDateMod, bool eqSize)
              {
                G2::CompareFilesAnswer cmd;
                cmd.SetEqAttributes(eqAttributes);
                cmd.SetEqContent(eqContent);
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqSize(eqSize);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CompareFilesAnswer самому себе
              /// </summary>
              /// <param name="eqAttributes">Возвращает true, если атрибуты файлов совпадают, иначе false</param>
              /// <param name="eqContent">Возвращает true, если содержимое файлов совпадает, иначе false</param>
              /// <param name="eqDateCreation">Возвращает true, если дата создания файлов совпадает, иначе false</param>
              /// <param name="eqDateMod">Возвращает true, если даты изменения файлов совпадают, иначе false</param>
              /// <param name="eqSize">Возвращает true, если размеры файлов совпадают, иначе false</param>
              void RaiseCompareFilesAnswer(bool eqAttributes, bool eqContent, bool eqDateCreation, bool eqDateMod, bool eqSize)
              {
                G2::CompareFilesAnswer cmd;
                cmd.SetEqAttributes(eqAttributes);
                cmd.SetEqContent(eqContent);
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqSize(eqSize);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CompareFolders по адресу
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первой папке</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второй папке</param>
              /// <param name="test">Какие проверки выполнять. Если не указана ни одна, сравниваются только имена файлов</param>
              void SendCompareFolders(address target, const string & file1, const string & file2, CompareTests test)
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CompareFolders самому себе
              /// </summary>
              /// <param name="file1">Путь (абсолютный или относительный) к первой папке</param>
              /// <param name="file2">Путь (абсолютный или относительный) ко второй папке</param>
              /// <param name="test">Какие проверки выполнять. Если не указана ни одна, сравниваются только имена файлов</param>
              void RaiseCompareFolders(const string & file1, const string & file2, CompareTests test)
              {
                G2::CompareFolders cmd;
                cmd.SetFile1(file1);
                cmd.SetFile2(file2);
                cmd.SetTest(test);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CompareFoldersAnswer по адресу
              /// </summary>
              /// <param name="eqDateCreation">даты создания папок, указанных в параметрах, совпадают</param>
              /// <param name="eqDateMod">даты изменения папок, указанных в параметрах, совпадают</param>
              /// <param name="equal">true - в соответствии с указанными во входных параметрах критериями папки совпадают</param>
              void SendCompareFoldersAnswer(address target, bool eqDateCreation, bool eqDateMod, bool equal)
              {
                G2::CompareFoldersAnswer cmd;
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqual(equal);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CompareFoldersAnswer самому себе
              /// </summary>
              /// <param name="eqDateCreation">даты создания папок, указанных в параметрах, совпадают</param>
              /// <param name="eqDateMod">даты изменения папок, указанных в параметрах, совпадают</param>
              /// <param name="equal">true - в соответствии с указанными во входных параметрах критериями папки совпадают</param>
              void RaiseCompareFoldersAnswer(bool eqDateCreation, bool eqDateMod, bool equal)
              {
                G2::CompareFoldersAnswer cmd;
                cmd.SetEqDateCreation(eqDateCreation);
                cmd.SetEqDateMod(eqDateMod);
                cmd.SetEqual(equal);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CopyFile по адресу
              /// </summary>
              /// <param name="destPath">Путь к файлу, куда надо копировать, с системными символами разделителя. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя. Использование "*" запрещено.</param>
              void SendCopyFile(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CopyFile самому себе
              /// </summary>
              /// <param name="destPath">Путь к файлу, куда надо копировать, с системными символами разделителя. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя. Использование "*" запрещено.</param>
              void RaiseCopyFile(const string & destPath, const string & srcPath)
              {
                G2::CopyFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CopyFileAnswer по адресу
              /// </summary>
              void SendCopyFileAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFileAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события CopyFileAnswer самому себе
              /// </summary>
              void RaiseCopyFileAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFileAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события CopyFileToFolder по адресу
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), куда надо копировать, с системными символами разделителя. Использование "*" запрещено. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя, может содержать "*"</param>
              void SendCopyFileToFolder(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CopyFileToFolder самому себе
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), куда надо копировать, с системными символами разделителя. Использование "*" запрещено. Если файл существует, то он будет перезаписан.</param>
              /// <param name="srcPath">Путь к файлу (абсолютный или относительный), который надо копировать, с системными символами разделителя, может содержать "*"</param>
              void RaiseCopyFileToFolder(const string & destPath, const string & srcPath)
              {
                G2::CopyFileToFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CopyFileToFolderAnswer по адресу
              /// </summary>
              void SendCopyFileToFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFileToFolderAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события CopyFileToFolderAnswer самому себе
              /// </summary>
              void RaiseCopyFileToFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFileToFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события CopyFolder по адресу
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), в которую надо копировать указанную папку, с системными символами разделителя</param>
              /// <param name="srcPath">Путь к папке (абсолютный или относительный), которую надо копировать, с системными символами разделителя</param>
              void SendCopyFolder(address target, const string & destPath, const string & srcPath)
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CopyFolder самому себе
              /// </summary>
              /// <param name="destPath">Путь к папке (абсолютный или относительный), в которую надо копировать указанную папку, с системными символами разделителя</param>
              /// <param name="srcPath">Путь к папке (абсолютный или относительный), которую надо копировать, с системными символами разделителя</param>
              void RaiseCopyFolder(const string & destPath, const string & srcPath)
              {
                G2::CopyFolder cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CopyFolderAnswer по адресу
              /// </summary>
              void SendCopyFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CopyFolderAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события CopyFolderAnswer самому себе
              /// </summary>
              void RaiseCopyFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CopyFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события CreateFolder по адресу
              /// </summary>
              /// <param name="path">Абсолютный путь с системными символами разделителя (InvalidArgument, AccessDenied)</param>
              void SendCreateFolder(address target, const string & path)
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события CreateFolder самому себе
              /// </summary>
              /// <param name="path">Абсолютный путь с системными символами разделителя (InvalidArgument, AccessDenied)</param>
              void RaiseCreateFolder(const string & path)
              {
                G2::CreateFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события CreateFolderAnswer по адресу
              /// </summary>
              void SendCreateFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::CreateFolderAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события CreateFolderAnswer самому себе
              /// </summary>
              void RaiseCreateFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::CreateFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события DeleteFile по адресу
              /// </summary>
              /// <param name="fileName">Имя удаляемого файла</param>
              void SendDeleteFile(address target, const string & fileName)
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события DeleteFile самому себе
              /// </summary>
              /// <param name="fileName">Имя удаляемого файла</param>
              void RaiseDeleteFile(const string & fileName)
              {
                G2::DeleteFile cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события DeleteFileAnswer по адресу
              /// </summary>
              /// <param name="result">Результат удаления</param>
              void SendDeleteFileAnswer(address target, bool result)
              {
                G2::DeleteFileAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события DeleteFileAnswer самому себе
              /// </summary>
              /// <param name="result">Результат удаления</param>
              void RaiseDeleteFileAnswer(bool result)
              {
                G2::DeleteFileAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события DeleteFiles по адресу
              /// </summary>
              /// <param name="folderName">Имя директории, в которой будет начат поиск подходящих файлов.</param>
              /// <param name="mask">Маска для имен файлов</param>
              /// <param name="recursively">Удалять ли подходящие файлы в поддиректориях</param>
              void SendDeleteFiles(address target, const string & folderName, const string & mask, bool recursively)
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события DeleteFiles самому себе
              /// </summary>
              /// <param name="folderName">Имя директории, в которой будет начат поиск подходящих файлов.</param>
              /// <param name="mask">Маска для имен файлов</param>
              /// <param name="recursively">Удалять ли подходящие файлы в поддиректориях</param>
              void RaiseDeleteFiles(const string & folderName, const string & mask, bool recursively)
              {
                G2::DeleteFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                cmd.SetRecursively(recursively);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события DeleteFilesAnswer по адресу
              /// </summary>
              /// <param name="filesDeleted">Количество удаленных файлов</param>
              void SendDeleteFilesAnswer(address target, int filesDeleted)
              {
                G2::DeleteFilesAnswer cmd;
                cmd.SetFilesDeleted(filesDeleted);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события DeleteFilesAnswer самому себе
              /// </summary>
              /// <param name="filesDeleted">Количество удаленных файлов</param>
              void RaiseDeleteFilesAnswer(int filesDeleted)
              {
                G2::DeleteFilesAnswer cmd;
                cmd.SetFilesDeleted(filesDeleted);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события DeleteFolder по адресу
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void SendDeleteFolder(address target, const string & path)
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события DeleteFolder самому себе
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void RaiseDeleteFolder(const string & path)
              {
                G2::DeleteFolder cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события DeleteFolderAnswer по адресу
              /// </summary>
              void SendDeleteFolderAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::DeleteFolderAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события DeleteFolderAnswer самому себе
              /// </summary>
              void RaiseDeleteFolderAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::DeleteFolderAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события Error по адресу
              /// </summary>
              /// <param name="errorValue">Какая именно ошбика произошла</param>
              void SendError(address target, Errors errorValue)
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события Error самому себе
              /// </summary>
              /// <param name="errorValue">Какая именно ошбика произошла</param>
              void RaiseError(Errors errorValue)
              {
                G2::Error cmd;
                cmd.SetErrorValue(errorValue);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ExtractFilename по адресу
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void SendExtractFilename(address target, const string & path)
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ExtractFilename самому себе
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void RaiseExtractFilename(const string & path)
              {
                G2::ExtractFilename cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ExtractFilenameAnswer по адресу
              /// </summary>
              /// <param name="name">Название файла. Может быть пустым, если в запросе был передан путь без символов после последнего разделителя.</param>
              void SendExtractFilenameAnswer(address target, const string & name)
              {
                G2::ExtractFilenameAnswer cmd;
                cmd.SetName(name);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ExtractFilenameAnswer самому себе
              /// </summary>
              /// <param name="name">Название файла. Может быть пустым, если в запросе был передан путь без символов после последнего разделителя.</param>
              void RaiseExtractFilenameAnswer(const string & name)
              {
                G2::ExtractFilenameAnswer cmd;
                cmd.SetName(name);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ExtractPath по адресу
              /// </summary>
              /// <param name="path">Исходный путь (абсолютный или относительный)</param>
              void SendExtractPath(address target, const string & path)
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ExtractPath самому себе
              /// </summary>
              /// <param name="path">Исходный путь (абсолютный или относительный)</param>
              void RaiseExtractPath(const string & path)
              {
                G2::ExtractPath cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события ExtractPathAnswer по адресу
              /// </summary>
              /// <param name="path">Путь с системными символами разделителя. Может быть "\\", если в запросе не было символов перед единственным разделителем.</param>
              void SendExtractPathAnswer(address target, const string & path)
              {
                G2::ExtractPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события ExtractPathAnswer самому себе
              /// </summary>
              /// <param name="path">Путь с системными символами разделителя. Может быть "\\", если в запросе не было символов перед единственным разделителем.</param>
              void RaiseExtractPathAnswer(const string & path)
              {
                G2::ExtractPathAnswer cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FileExists по адресу
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void SendFileExists(address target, const string & path)
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FileExists самому себе
              /// </summary>
              /// <param name="path">Путь (абсолютный или относительный) с системными символами разделителя</param>
              void RaiseFileExists(const string & path)
              {
                G2::FileExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FileExistsAnswer по адресу
              /// </summary>
              /// <param name="exists">true - существует, false - не существует</param>
              void SendFileExistsAnswer(address target, bool exists)
              {
                G2::FileExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FileExistsAnswer самому себе
              /// </summary>
              /// <param name="exists">true - существует, false - не существует</param>
              void RaiseFileExistsAnswer(bool exists)
              {
                G2::FileExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindClose по адресу
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void SendFindClose(address target, int searchIndex)
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindClose самому себе
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void RaiseFindClose(int searchIndex)
              {
                G2::FindClose cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindCloseAnswer по адресу
              /// </summary>
              /// <param name="result">Результат закрытия поиска</param>
              void SendFindCloseAnswer(address target, bool result)
              {
                G2::FindCloseAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindCloseAnswer самому себе
              /// </summary>
              /// <param name="result">Результат закрытия поиска</param>
              void RaiseFindCloseAnswer(bool result)
              {
                G2::FindCloseAnswer cmd;
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindFirst по адресу
              /// </summary>
              /// <param name="mask">Маска поиска</param>
              /// <param name="path">Путь, по которому осуществляется поиск (абсолютный или относительный), может содержать "*"</param>
              void SendFindFirst(address target, const string & mask, const string & path)
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindFirst самому себе
              /// </summary>
              /// <param name="mask">Маска поиска</param>
              /// <param name="path">Путь, по которому осуществляется поиск (абсолютный или относительный), может содержать "*"</param>
              void RaiseFindFirst(const string & mask, const string & path)
              {
                G2::FindFirst cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindFirstAnswer по адресу
              /// </summary>
              /// <param name="attributes">Атрибуты файла</param>
              /// <param name="fileName">Имя файла</param>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void SendFindFirstAnswer(address target, WinApiAttr attributes, const string & fileName, int searchIndex)
              {
                G2::FindFirstAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindFirstAnswer самому себе
              /// </summary>
              /// <param name="attributes">Атрибуты файла</param>
              /// <param name="fileName">Имя файла</param>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void RaiseFindFirstAnswer(WinApiAttr attributes, const string & fileName, int searchIndex)
              {
                G2::FindFirstAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindNext по адресу
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void SendFindNext(address target, int searchIndex)
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindNext самому себе
              /// </summary>
              /// <param name="searchIndex">Индекс открытого поиска</param>
              void RaiseFindNext(int searchIndex)
              {
                G2::FindNext cmd;
                cmd.SetSearchIndex(searchIndex);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FindNextAnswer по адресу
              /// </summary>
              /// <param name="attributes">Атрибуты файла</param>
              /// <param name="fileName">Имя файла</param>
              /// <param name="result">Результат поиска следующего файла</param>
              void SendFindNextAnswer(address target, WinApiAttr attributes, const string & fileName, bool result)
              {
                G2::FindNextAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FindNextAnswer самому себе
              /// </summary>
              /// <param name="attributes">Атрибуты файла</param>
              /// <param name="fileName">Имя файла</param>
              /// <param name="result">Результат поиска следующего файла</param>
              void RaiseFindNextAnswer(WinApiAttr attributes, const string & fileName, bool result)
              {
                G2::FindNextAnswer cmd;
                cmd.SetAttributes(attributes);
                cmd.SetFileName(fileName);
                cmd.SetResult(result);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FolderExists по адресу
              /// </summary>
              /// <param name="path">Путь к папке (абсолютный или относительный) с системным символом разделителя</param>
              void SendFolderExists(address target, const string & path)
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FolderExists самому себе
              /// </summary>
              /// <param name="path">Путь к папке (абсолютный или относительный) с системным символом разделителя</param>
              void RaiseFolderExists(const string & path)
              {
                G2::FolderExists cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события FolderExistsAnswer по адресу
              /// </summary>
              /// <param name="exists">true - существует, false - не существует</param>
              void SendFolderExistsAnswer(address target, bool exists)
              {
                G2::FolderExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события FolderExistsAnswer самому себе
              /// </summary>
              /// <param name="exists">true - существует, false - не существует</param>
              void RaiseFolderExistsAnswer(bool exists)
              {
                G2::FolderExistsAnswer cmd;
                cmd.SetExists(exists);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetDirectories по адресу
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              void SendGetDirectories(address target, const string & folderName)
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetDirectories самому себе
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              void RaiseGetDirectories(const string & folderName)
              {
                G2::GetDirectories cmd;
                cmd.SetFolderName(folderName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetDirectoriesAnswer по адресу
              /// </summary>
              /// <param name="names">Список полных имен поддиректорий, находящихся в указанной директории</param>
              void SendGetDirectoriesAnswer(address target, const StringList & names)
              {
                G2::GetDirectoriesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetDirectoriesAnswer самому себе
              /// </summary>
              /// <param name="names">Список полных имен поддиректорий, находящихся в указанной директории</param>
              void RaiseGetDirectoriesAnswer(const StringList & names)
              {
                G2::GetDirectoriesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetExtension по адресу
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void SendGetExtension(address target, const string & fileName)
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetExtension самому себе
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void RaiseGetExtension(const string & fileName)
              {
                G2::GetExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetExtensionAnswer по адресу
              /// </summary>
              /// <param name="extension">Расширение из имени файла</param>
              void SendGetExtensionAnswer(address target, const string & extension)
              {
                G2::GetExtensionAnswer cmd;
                cmd.SetExtension(extension);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetExtensionAnswer самому себе
              /// </summary>
              /// <param name="extension">Расширение из имени файла</param>
              void RaiseGetExtensionAnswer(const string & extension)
              {
                G2::GetExtensionAnswer cmd;
                cmd.SetExtension(extension);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFileInfo по адресу
              /// </summary>
              /// <param name="path">Путь к файлу или папке (абсолютный или относительный) с системными разделителями</param>
              void SendGetFileInfo(address target, const string & path)
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFileInfo самому себе
              /// </summary>
              /// <param name="path">Путь к файлу или папке (абсолютный или относительный) с системными разделителями</param>
              void RaiseGetFileInfo(const string & path)
              {
                G2::GetFileInfo cmd;
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFileInfoAnswer по адресу
              /// </summary>
              /// <param name="attr">Атрибуты</param>
              /// <param name="dateCreation">Дата создания файла</param>
              /// <param name="dateMod">Дата изменения файла</param>
              /// <param name="size">Размер файла в байтах</param>
              void SendGetFileInfoAnswer(address target, Attributes attr, timestamp_t dateCreation, timestamp_t dateMod, int size)
              {
                G2::GetFileInfoAnswer cmd;
                cmd.SetAttr(attr);
                cmd.SetDateCreation(dateCreation);
                cmd.SetDateMod(dateMod);
                cmd.SetSize(size);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFileInfoAnswer самому себе
              /// </summary>
              /// <param name="attr">Атрибуты</param>
              /// <param name="dateCreation">Дата создания файла</param>
              /// <param name="dateMod">Дата изменения файла</param>
              /// <param name="size">Размер файла в байтах</param>
              void RaiseGetFileInfoAnswer(Attributes attr, timestamp_t dateCreation, timestamp_t dateMod, int size)
              {
                G2::GetFileInfoAnswer cmd;
                cmd.SetAttr(attr);
                cmd.SetDateCreation(dateCreation);
                cmd.SetDateMod(dateMod);
                cmd.SetSize(size);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFileNameWithoutExtension по адресу
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void SendGetFileNameWithoutExtension(address target, const string & fileName)
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFileNameWithoutExtension самому себе
              /// </summary>
              /// <param name="fileName">Полный или относительный путь к файлу и иего имя с расширением</param>
              void RaiseGetFileNameWithoutExtension(const string & fileName)
              {
                G2::GetFileNameWithoutExtension cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFileNameWithoutExtensionAnswer по адресу
              /// </summary>
              /// <param name="fileName">Имя фаяла без расширения</param>
              void SendGetFileNameWithoutExtensionAnswer(address target, const string & fileName)
              {
                G2::GetFileNameWithoutExtensionAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFileNameWithoutExtensionAnswer самому себе
              /// </summary>
              /// <param name="fileName">Имя фаяла без расширения</param>
              void RaiseGetFileNameWithoutExtensionAnswer(const string & fileName)
              {
                G2::GetFileNameWithoutExtensionAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFiles по адресу
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              /// <param name="mask">Маска для имен файлов.</param>
              void SendGetFiles(address target, const string & folderName, const string & mask = "*")
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFiles самому себе
              /// </summary>
              /// <param name="folderName">Директория, где будет производиться поиск</param>
              /// <param name="mask">Маска для имен файлов.</param>
              void RaiseGetFiles(const string & folderName, const string & mask = "*")
              {
                G2::GetFiles cmd;
                cmd.SetFolderName(folderName);
                cmd.SetMask(mask);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFilesAnswer по адресу
              /// </summary>
              /// <param name="names">Список полных имен файлов, находящихся в указанной директории</param>
              void SendGetFilesAnswer(address target, const StringList & names)
              {
                G2::GetFilesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFilesAnswer самому себе
              /// </summary>
              /// <param name="names">Список полных имен файлов, находящихся в указанной директории</param>
              void RaiseGetFilesAnswer(const StringList & names)
              {
                G2::GetFilesAnswer cmd;
                cmd.SetNames(names);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFilesCount по адресу
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void SendGetFilesCount(address target, const string & path, const string & mask = "::")
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFilesCount самому себе
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void RaiseGetFilesCount(const string & path, const string & mask = "::")
              {
                G2::GetFilesCount cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetFilesCountAnswer по адресу
              /// </summary>
              /// <param name="count">количество файлов</param>
              void SendGetFilesCountAnswer(address target, int count)
              {
                G2::GetFilesCountAnswer cmd;
                cmd.SetCount(count);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetFilesCountAnswer самому себе
              /// </summary>
              /// <param name="count">количество файлов</param>
              void RaiseGetFilesCountAnswer(int count)
              {
                G2::GetFilesCountAnswer cmd;
                cmd.SetCount(count);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetMostRecentFileName по адресу
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void SendGetMostRecentFileName(address target, const string & path, const string & mask = "::")
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetMostRecentFileName самому себе
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void RaiseGetMostRecentFileName(const string & path, const string & mask = "::")
              {
                G2::GetMostRecentFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetMostRecentFileNameAnswer по адресу
              /// </summary>
              /// <param name="fileName">имя файла</param>
              void SendGetMostRecentFileNameAnswer(address target, const string & fileName)
              {
                G2::GetMostRecentFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetMostRecentFileNameAnswer самому себе
              /// </summary>
              /// <param name="fileName">имя файла</param>
              void RaiseGetMostRecentFileNameAnswer(const string & fileName)
              {
                G2::GetMostRecentFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetOldestFileName по адресу
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void SendGetOldestFileName(address target, const string & path, const string & mask = "::")
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetOldestFileName самому себе
              /// </summary>
              /// <param name="path">абсолютный путь к папке</param>
              /// <param name="mask">маска</param>
              void RaiseGetOldestFileName(const string & path, const string & mask = "::")
              {
                G2::GetOldestFileName cmd;
                cmd.SetMask(mask);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события GetOldestFileNameAnswer по адресу
              /// </summary>
              /// <param name="fileName">имя файла</param>
              void SendGetOldestFileNameAnswer(address target, const string & fileName)
              {
                G2::GetOldestFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события GetOldestFileNameAnswer самому себе
              /// </summary>
              /// <param name="fileName">имя файла</param>
              void RaiseGetOldestFileNameAnswer(const string & fileName)
              {
                G2::GetOldestFileNameAnswer cmd;
                cmd.SetFileName(fileName);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события MoveFile по адресу
              /// </summary>
              /// <param name="destPath">Путь к существующей папке (абсолютный или относительный), в которую надо выполнить перемещение.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void SendMoveFile(address target, const string & destPath, const string & srcPath)
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события MoveFile самому себе
              /// </summary>
              /// <param name="destPath">Путь к существующей папке (абсолютный или относительный), в которую надо выполнить перемещение.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void RaiseMoveFile(const string & destPath, const string & srcPath)
              {
                G2::MoveFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события MoveFileAnswer по адресу
              /// </summary>
              void SendMoveFileAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::MoveFileAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события MoveFileAnswer самому себе
              /// </summary>
              void RaiseMoveFileAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::MoveFileAnswer, 2); 
              }
              
              /// <summary> 
              /// Отправка события RenameFile по адресу
              /// </summary>
              /// <param name="destPath">Путь к файлу или папке (абсолютный или относительный). Исходный файл или папка будет переименована в соответствии с этим путем.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void SendRenameFile(address target, const string & destPath, const string & srcPath)
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события RenameFile самому себе
              /// </summary>
              /// <param name="destPath">Путь к файлу или папке (абсолютный или относительный). Исходный файл или папка будет переименована в соответствии с этим путем.</param>
              /// <param name="srcPath">Путь к файлу или папке (абсолютный или относительный), которую надо переместить, с системными символами разделителя. По окончании операции этот файл будет удален.</param>
              void RaiseRenameFile(const string & destPath, const string & srcPath)
              {
                G2::RenameFile cmd;
                cmd.SetDestPath(destPath);
                cmd.SetSrcPath(srcPath);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события RenameFileAnswer по адресу
              /// </summary>
              /// <param name="destCreated">true, если конечный файл был успешно создан, иначе false</param>
              /// <param name="srcRemoved">true, если исходный файл был успешно удален, иначе false</param>
              void SendRenameFileAnswer(address target, bool destCreated, bool srcRemoved)
              {
                G2::RenameFileAnswer cmd;
                cmd.SetDestCreated(destCreated);
                cmd.SetSrcRemoved(srcRemoved);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события RenameFileAnswer самому себе
              /// </summary>
              /// <param name="destCreated">true, если конечный файл был успешно создан, иначе false</param>
              /// <param name="srcRemoved">true, если исходный файл был успешно удален, иначе false</param>
              void RaiseRenameFileAnswer(bool destCreated, bool srcRemoved)
              {
                G2::RenameFileAnswer cmd;
                cmd.SetDestCreated(destCreated);
                cmd.SetSrcRemoved(srcRemoved);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события SetFolderContentAttributes по адресу
              /// </summary>
              /// <param name="attr">Атрибуты файла</param>
              /// <param name="path">Путь с системными символами разделителя (абсолютный или относительный)</param>
              void SendSetFolderContentAttributes(address target, WinApiAttr attr, const string & path)
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(target, cmd);
              }
              /// <summary> 
              /// Отправка события SetFolderContentAttributes самому себе
              /// </summary>
              /// <param name="attr">Атрибуты файла</param>
              /// <param name="path">Путь с системными символами разделителя (абсолютный или относительный)</param>
              void RaiseSetFolderContentAttributes(WinApiAttr attr, const string & path)
              {
                G2::SetFolderContentAttributes cmd;
                cmd.SetAttr(attr);
                cmd.SetPath(path);
                m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
              }
              
              /// <summary> 
              /// Отправка события SetFolderContentAttributesAnswer по адресу
              /// </summary>
              void SendSetFolderContentAttributesAnswer(address target)
              {
                m_RequestDispatcher->SendEvent(target, G2::Codes::SetFolderContentAttributesAnswer, 2); 
              }
              /// <summary> 
              /// Отправка события SetFolderContentAttributesAnswer самому себе
              /// </summary>
              void RaiseSetFolderContentAttributesAnswer()
              {
                m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G2::Codes::SetFolderContentAttributesAnswer, 2); 
              }
              
            END_IMPLEMENTATION();
            
            #pragma endregion
          END_PROTOCOL()
          
          } // пространство имен Protocol
        } // пространство имен FileSystem
      } // пространство имен Kernel
    } // пространство имен Framework
  } // пространство имен Uniteller
