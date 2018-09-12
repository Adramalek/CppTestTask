// Uniteller.CrossroadController

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText, 
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace CrossroadController
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(101, 1)
        
        #pragma region Enumerations
        /// <summary> 
        /// Цвет сигнала светофора. Длительность сигнала определяется цветом.
        /// </summary>
        enum class ColorType
        {
          Green = 40, // - Зелёный цвет, 40 секунд.
          Red = 30, // - Красный цвет, 30 секунд.
          Yellow = 5 // - Жёлтый цвет, 5 секунд.
        };
        
        /// <summary>
        /// Валидатор корректности значения для перечислимого типа ColorType
        /// </summary>
        inline bool IsValidColorTypeValue(const int value)
        {
          return ((value >= 5)&&(value < 6)) || ((value >= 30)&&(value < 31)) || ((value >= 40)&&(value < 41));
        }
        
        /// <summary>
        /// Следует использовать для преобразования числовых значений к перечислимому типу ColorType
        /// </summary>
        inline ColorType ConvertToColorType(const int value)
        {
          switch (value)
          {
            case 40:
              return ColorType::Green;
            case 30:
              return ColorType::Red;
            case 5:
              return ColorType::Yellow;
            default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ColorType", value);
            }
        }
        
        #pragma endregion
        
        //Структуры
        #pragma region Messages and wrappers
        
        //Сообщения
        // Поставить модуль на паузу.
        BEGIN_MESSAGE(Pause,2,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Pause

        // Следующая итерация цикла переключения сигнала светофора.
        BEGIN_MESSAGE(SetNextLight,1,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // SetNextLight

        
        BEGIN_WRAPPER()
          /// <summary> 
          /// Поставить модуль на паузу.
          /// </summary>
          void Pause() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Pause);
          }
          
          /// <summary> 
          /// Следующая итерация цикла переключения сигнала светофора.
          /// </summary>
          void SetNextLight() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::SetNextLight);
          }
          
        END_WRAPPER();
        
        BEGIN_IMPLEMENTATION()
          /// <summary> 
          /// Отправка события Pause по адресу
          /// </summary>
          void SendPause(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Pause);
          }
          /// <summary> 
          /// Отправка события Pause самому себе
          /// </summary>
          void RaisePause()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Pause);
          }
          
          /// <summary> 
          /// Отправка события SetNextLight по адресу
          /// </summary>
          void SendSetNextLight(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::SetNextLight);
          }
          /// <summary> 
          /// Отправка события SetNextLight самому себе
          /// </summary>
          void RaiseSetNextLight()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::SetNextLight);
          }
          
        END_IMPLEMENTATION();
        
        #pragma endregion
      END_PROTOCOL()
      
      } // пространство имен Protocol
    } // пространство имен CrossroadController
  } // пространство имен Uniteller
