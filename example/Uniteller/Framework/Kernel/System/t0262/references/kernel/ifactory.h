// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс абстрактной  фабрики модулей

#pragma once

#include "iobject.h" // IObject
#include "apiendpointerror.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      class IExtension;

      /// <summary>
      /// Интерфейс абстрактной  фабрики модулей
      /// </summary>
      interface IFactory : public IExportable
      {
      public:
        /// <summary>
        /// путь к папке установки системы
        /// </summary>
        PROPERTY_DECLARATION_STRING(SystemRoot);
        /// <summary>
        /// Создает и возвращает экземпляр объекта системы типа kind
        /// </summary>
        /// <param name="kind">Тип объекта для создания</param>
        /// <param name="generation">Требуемое поколение</param>
        /// <returns>Указатель на объект (если он успешно создан) или NULL </returns>
        virtual IObject * CreateInstance(const char * kind, int generation)=0;

        /// <summary>
        /// Подгружает динамическую библиотеку но не создает объект
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="generation">Требуемое поколение</param>
        virtual bool ColdLoad(const char * kind, int generation)=0;        

        virtual ApiEndpointError ConnectToApiEndpoint(const char * EndPoint, IExportable * interceptor, const char * unit) = 0;
        virtual ApiEndpointError ConnectToApiEndpoint(const char * EndPoint, IExportable * interceptor, IExportable * unit) = 0;

        /// <summary>
        /// Позволяет загрузить пакет приложений UTC
        /// </summary>
        virtual void LoadApplicationPackage(const char * szName) = 0;

        /// <summary>
        /// Позволяет зарегистрировать расширение фабрики, позволяющее создавать продукты типа kind
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="extension">Расширение-производитель объекта типа kind</param>
        virtual void AddExtension(const char * kind, IExtension * extension) = 0;
        /// <summary>
        /// Очистка ресурсов фабрики
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// Активирует загруженный в реестры тип модуля для возможности его создания
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="generation">Требуемое поколение</param>
        virtual bool ActivateLoadedUnit(const char * kind, int generation)=0;        
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller