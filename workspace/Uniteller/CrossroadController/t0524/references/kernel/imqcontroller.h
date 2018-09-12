// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс сообщения, передаваемого по шине передачи сообщений

#pragma once

#include "imessagebus.h"
#include "irequestdispatcher.h"
#include "apiendpointerror.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 


      /// <summary>
      /// Интерфейс контроллера логической шины. Позволяет объекту владельцу (мастеру) шины
      /// реализовывать основные функции управления логической шиной: создавать экземпляры объектов системы 
      /// и подключать их к шине, создавать логические подшины
      /// </summary>
      interface IMqController : public IMessageBus
      {        
      public:
        /// <summary>
        /// Создает и подключает к текущей шине экземпляр объекта системы типа kind
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="generation">Требуемое поколение</param>
        /// <param name="id">Если передано какое-то значение, то
        /// будет предпринята попытка установить его новому экземпляру модуля в качестве адреса. Если указанное значение
        /// уже является адресом, то в создании и подключении экземпляра объекта будет отказано и будет сгенерировано         
        /// исключение. Если ничего не передано, то шина автоматически сгенерирует адрес модуля и возвратит его в качестве результата </param>
        /// <returns>Адрес подключенного модуля</returns>
        virtual address CreateInstance(const char * kind, int generation, address id) = 0;
        /// <summary>
        /// Создает новую шину и передает права на нее мастер-модулю, заданному параметром master
        /// </summary>
        /// <param name="master">Адрес модуля, который будет назначен мастер-модулем создаваемой шины</param>
        /// <returns>Возвращает адрес созданной шины</returns>
        virtual address CreateMq(address master) = 0;
        /// <summary>
        /// Позволяет узнать есть ли на данной шине подключенный модуль с адресом id
        /// </summary>
        /// <param name="id">Адрес модуля, который нужно найти среди подключенных к шине модулей</param>
        /// <returns>Возвращает true если модуль с таким значением подключен, иначе возвращает false.</returns>
        virtual bool HasAddress(address id) const = 0;

        /// <summary>
        /// Позволяет зарегистрировать вызвавший мастер-модуль в качестве модуля-перехватчика сообщений, адресованных
        /// на адрес id. Если в качестве id передана пустая строка, то будет создан новый адрес на шине и будет установлен
        /// перехват сообщений с этого адреса. Если адрес id уже подключен к шине, то будет сгенерирована ошибка.
        /// </summary>
        /// <param name="interceptor">Адрес модуля, который нужно подключить в качестве перехватчика</param>
        /// <param name="id">Адрес модуля,  сообщения которого будут перехватываться</param>
        /// <returns>Адрес по которому осуществляется перехват сообщение</returns>
        virtual address RegisterAsInterceptor(address interceptor, address id) =0;

        /// <summary>
        /// Позволяет зарегистрировать вызвавший мастер-модуль в качестве модуля-перехватчика сообщений, адресованных
        /// на адрес id. Если в качестве id передана пустая строка, то будет создан новый адрес на шине и будет установлен
        /// перехват сообщений с этого адреса. Если адрес id уже подключен к шине, то будет сгенерирована ошибка.
        /// </summary>
        /// <param name="interceptor">Адрес модуля, который нужно подключить в качестве перехватчика</param>
        /// <param name="id">Адрес модуля,  сообщения которого будут перехватываться</param>
        /// <param name="filter">Фильтр сообщений</param>
        /// <returns>Адрес по которому осуществляется перехват сообщение</returns>
        virtual address RegisterAsInterceptor(address interceptor, address id, IMessageFilter * filter) =0;

        /// <summary>
        /// Позволяет начать наблюдение за обменом модуля с адресом id (дублирует входящие сообщения)
        /// </summary>
        /// <param name="observer">Адрес модуля, который нужно подключить в качестве получателя событий другого модуля</param>
        /// <param name="id">Адрес модуля,  сообщения которого будут дублироваться на модуль-наблюдатель observer</param>
        virtual bool RegisterObserver(address observer, address id) = 0;

        /// <summary>
        /// Позволяет начать наблюдение за обменом модуля с адресом id (дублирует входящие сообщения)
        /// </summary>
        /// <param name="observer">Адрес модуля, который нужно подключить в качестве получателя событий другого модуля</param>
        /// <param name="id">Адрес модуля,  сообщения которого будут дублироваться на модуль-наблюдатель observer</param>
        /// <param name="filter">Фильтр сообщений</param>
        virtual bool RegisterObserver(address observer, address id, IMessageFilter * filter) = 0;

        /// <summary>
        /// Позволяет начать наблюдение за обменом модуля с адресом id (дублирует исходящие сообщения)
        /// </summary>
        /// <param name="observer">Адрес модуля, который нужно подключить в качестве получателя событий другого модуля</param>
        /// <param name="observable">Адрес модуля, исходящие сообщения которого будут дублироваться на модуль-наблюдатель observer</param>
        virtual void RegisterSendTrafficObserver(address observer, address observable) = 0;

        /// <summary>
        /// Позволяет начать наблюдение за обменом модуля с адресом id (дублирует исходящие сообщения)
        /// </summary>
        /// <param name="observer">Адрес модуля, который нужно подключить в качестве получателя событий другого модуля</param>
        /// <param name="observable">Адрес модуля, исходящие сообщения которого будут дублироваться на модуль-наблюдатель observer</param>
        /// <param name="filter">Фильтр сообщений</param>
        virtual void RegisterSendTrafficObserver(address observer, address observable, IMessageFilter * filter) = 0;

        virtual void MqEmulation(address master,  address bus, IMqController * emulator) = 0;

        /// <summary>
        /// Позволяет проверить поддерживает ли модуль определенное поколение 
        /// </summary>
        virtual bool IsUnitSupportsGeneration(address unit, int generation) = 0;
        /// <summary>
        /// Позволяет проверить поддерживает ли модуль определенный протокол
        /// </summary>
        virtual bool IsUnitSupportsProtocol(address unit, const char * szProtocol, int generation) = 0;
        /// <summary>
        /// Подгружает динамическую библиотеку но не создает объект
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="generation">Требуемое поколение</param>
        virtual bool ColdLoad(const char * kind, int generation) = 0;

        virtual void Stop() = 0;

        virtual ApiEndpointError ConnectToApiEndpoint(address unit, address module) = 0;
        virtual ApiEndpointError DisconnectFromApiEndpoint(address unit, address module) = 0;
      };



    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller