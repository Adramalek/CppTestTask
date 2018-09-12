// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию типа Variant

#pragma once

#include "ivendordatasource.h"
#include "istatemachine.h"
#include "iregistry.h"
#include "ifactory.h"
#include "iapplicationhost.h"
#include "iuidgen.h"
#include "iprotocolreflection.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Экспортируемый интерфейс библиотеки микро-ядра Uniteller.Framework.Kernel
      /// </summary>
      interface IKernelApi : public IExportable
      {
      public:
        /// <summary>
        /// Позволяет получить загрузчик мета-данных производителя модуля
        /// </summary>
        /// <returns>Указатель на новый экземпляр загрузчика мета-данных производителя модуля</returns>
        virtual IVendorDataSource * CreateVendorDataSource() = 0;
        /// <summary>
        /// Позволяет загрузить конечный автомат по мета-описанию
        /// </summary>
        /// <param name="name">Имя конечного автомата для загрузки.</param>
        /// <returns>Указатель на конечный автомат</returns>
        virtual IStateMachine * LoadStateMachine(const char * name) = 0;
        /// <summary>
        /// Позволяет получить реестр мета-данных
        /// </summary>
        /// <returns>Указатель на реестр мета-данных</returns>
        virtual IRegistry * GetRegistry() = 0;   
        /// <summary>
        /// Возвращает стандартную для микро-ядра реализацию фабрики модулей
        /// </summary>
        /// <returns>Указатель на фабрику модулей</returns>
        virtual IFactory * GetStandardFactory() = 0;
        /// <summary>
        /// Создает стандартный хост приложений
        /// </summary>
        /// <param name="argc">Число параметров командной строки.</param>
        /// <param name="argv">Параметры командной строки.</param>
        /// <returns></returns>
        virtual IApplicationHost * StartApplication(IFactory * factory, IUnicalIdGenerator * generator, int argc, char *argv[]) = 0;

        /// <summary>
        /// Позволяет выполнить разбор текста в формате UniText
        /// </summary>
        /// <param name="szText">Текст для разбора</param>
        /// <returns>Дерево разбора</returns>
        virtual IEnumeration<IRegistryHive *> * ParseUniText(const char * szText) = 0;

        /// <summary>
        /// Останавливает ядро
        /// </summary>
        virtual void Stop() = 0;

        /// <summary>
        /// Возвращает указатель на рефлектор микро-ядра
        /// </summary>
        virtual IProtocolReflection * GetReflector() = 0;

        /// <summary>
        /// Позволяет загрузить из внешнего файла и подключить в реестр микро-ядра источник мета-данных в формате UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        virtual void LoadUniTextDataSource(const char * szFilePath) = 0;

        /// <summary>
        /// Позволяет загрузить из внешнего файла и выполнить разбор текста в формате UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        /// <returns>Дерево разбора</returns>
        virtual IEnumeration<IRegistryHive *> * LoadUniTextFile(const char * szFile) = 0;

        /// <summary>
        /// Позволяет загрузить из внешнего файла (компрессированный utc) и структуру в формате UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        /// <returns>Дерево разбора</returns>
        virtual IEnumeration<IRegistryHive *> * LoadUtcFile(const char * szFile) = 0;

        /// <summary>
        /// Позволяет записать во внешний файл (компрессированный utc) и структуру в формате UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        virtual void WriteUtcFile(const char * szFile, IEnumeration<IRegistryHive *> * hives) = 0;

        /// <summary>
        /// Позволяет загрузить из внешнего файла и подключить в реестр микро-ядра источник мета-данных в формате compressed UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        virtual void LoadUtcDataSource(const char * szFilePath) = 0;

        /// <summary>
        /// Позволяет сохранить во внешний файл (компрессированный utc) и структуру в формате UniText
        /// </summary>
        /// <param name="szFile">Файл для загрузки и разбора</param>
        virtual void WriteUniTextFile(const char * szFile, IEnumeration<IRegistryHive *> * hives) = 0;

        /// <summary>
        /// Позволяет загрузить пакет UTC
        /// </summary>   
        virtual void LoadPackage(const char * szPackName) = 0;

      };
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller