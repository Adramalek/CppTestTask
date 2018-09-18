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
        
        //Структуры
        #pragma region Messages and wrappers
        
        //Сообщения
        // Начать обратный отсчет для зелёного сигнала
        BEGIN_MESSAGE(CountDownGreen,4,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownGreen

        // Начать обратный отсчет для красного сигнала
        BEGIN_MESSAGE(CountDownRed,2,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownRed

        // Начать обратный отсчет для жёлтого сигнала
        BEGIN_MESSAGE(CountDownYellow,3,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // CountDownYellow

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
          /// Начать обратный отсчет для зелёного сигнала
          /// </summary>
          void CountDownGreen() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownGreen);
          }
          
          /// <summary> 
          /// Начать обратный отсчет для красного сигнала
          /// </summary>
          void CountDownRed() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownRed);
          }
          
          /// <summary> 
          /// Начать обратный отсчет для жёлтого сигнала
          /// </summary>
          void CountDownYellow() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownYellow);
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
          /// Отправка события CountDownGreen по адресу
          /// </summary>
          void SendCountDownGreen(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownGreen);
          }
          /// <summary> 
          /// Отправка события CountDownGreen самому себе
          /// </summary>
          void RaiseCountDownGreen()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownGreen);
          }
          
          /// <summary> 
          /// Отправка события CountDownRed по адресу
          /// </summary>
          void SendCountDownRed(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownRed);
          }
          /// <summary> 
          /// Отправка события CountDownRed самому себе
          /// </summary>
          void RaiseCountDownRed()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownRed);
          }
          
          /// <summary> 
          /// Отправка события CountDownYellow по адресу
          /// </summary>
          void SendCountDownYellow(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::CountDownYellow);
          }
          /// <summary> 
          /// Отправка события CountDownYellow самому себе
          /// </summary>
          void RaiseCountDownYellow()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::CountDownYellow);
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
