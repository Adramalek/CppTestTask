// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс хоста приложений микро-ядра

#pragma once

#include "iapplicationstartupinfo.h"
#include "istartable.h"
#include "imessage.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс хоста приложений
      /// </summary>      
      interface IApplicationHost : public IStartable<IApplicationStartupInfo>
      {
      public: // Методы        
        /// <summary>
        /// Активирует цикл ожидания выхода основного приложения, размещенного в хосте
        /// <summary>
        virtual void WaitForExist() = 0;
        /// <summary>
        /// Позволяет направить из внешнего кода (хост-оболочки) сообщение главному мастер-модулю хоста
        /// <summary>
        virtual bool TransmitMessage(IMessage * message) = 0;

        /// <summary>
        /// Подгружает динамическую библиотеку но не создает объект
        /// </summary>
        /// <param name="kind">Тип объекта для создания и подключения к шине</param>
        /// <param name="generation">Требуемое поколение</param>
        /// <returns>Результат загрузки</returns>
        virtual bool ColdLoad(const char * kind, int generation) = 0;

        /// <summary>
        /// Останавливает приложение
        /// </summary>
        virtual void Terminate() = 0;
        /// <summary>
        /// Активирует цикл ожидания выхода основного приложения, размещенного в хосте
        /// <summary>
        /// <param name="timeout">Тайм-аут в миллисекундах</param>
        /// <returns>Активно ли ядро</returns>
        virtual bool WaitForExist(size_t timeout) = 0;
      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller