// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию интерфейса экспортируемого из dll объекта
#pragma once

#include <list>
#include "istartable.h"
#include "exportable.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      /// <summary>
      /// Базовая реализация запускаемого объекта
      /// <summary>
      template <class T, class C>
      class Startable : public Exportable<T>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsStartable OnlyExportable;

      public: // Свойства
        // запущен ли
        READONLY_PROPERTY_IMPLEMENTATION(bool, IsStarted);
      public:
        /// <summary>
        /// Конструктор, устанавливает счетчик ссылок в единицу
        /// </summary>
        Startable() : m_IsStarted(false)
        {
        }
        /// <summary>
        /// Запускает запускаемый объект
        /// </summary>
        void Start(C * context)
        {
          if (!m_IsStarted)
            m_IsStarted = OnStart(context);
        }
        /// <summary>
        /// Останавливает запускаемый объект
        /// </summary>
        void Stop()
        {
          if (m_IsStarted)
            m_IsStarted = !OnStop();
        }

        /// <summary>
        /// Позволяет перекрыть поведение в момент запуска
        /// </summary>
        /// <returns>Возвращает флаг - удачен ли был запуск (true - запустить удалось, false - запустить не удалось).</returns>
        virtual bool OnStart(C * /*context*/)
        {
          return true;
        }
        /// <summary>
        /// Позволяет перекрыть поведение в момент остановки
        /// </summary>
        /// <returns>Возвращает флаг - удачно ли прошла остановка (true - остановить удалось, false - остановить не удалось).</returns>
        virtual bool OnStop()
        {
          return false;
        }       
      };


      /// <summary>
      /// Базовая реализация запускаемого объекта
      /// <summary>
      template <class T>
      class Startable<T, void> : public Exportable<T>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsStartable OnlyExportable;

      public: // Свойства
        // запущен ли
        READONLY_PROPERTY_IMPLEMENTATION(bool, IsStarted);
      public:
        /// <summary>
        /// Конструктор, устанавливает счетчик ссылок в единицу
        /// </summary>
        Startable() : m_IsStarted(false)
        {
        }
        /// <summary>
        /// Запускает запускаемый объект
        /// </summary>
        void Start()
        {
          if (!m_IsStarted)
            m_IsStarted = OnStart();
        }
        /// <summary>
        /// Останавливает запускаемый объект
        /// </summary>
        void Stop()
        {
          if (m_IsStarted)
            m_IsStarted = !OnStop();
        }

        /// <summary>
        /// Позволяет перекрыть поведение в момент запуска
        /// </summary>
        /// <returns>Возвращает флаг - удачен ли был запуск (true - запустить удалось, false - запустить не удалось).</returns>
        virtual bool OnStart()
        {
          return true;
        }
        /// <summary>
        /// Позволяет перекрыть поведение в момент остановки
        /// </summary>
        /// <returns>Возвращает флаг - удачно ли прошла остановка (true - остановить удалось, false - остановить не удалось).</returns>
        virtual bool OnStop()
        {
          return true;
        }       
      };

      template <class T>
      class startable_list : public std::list<T>
      {
      public:
        void clear()
        {
          typename std::list<T>::const_iterator e = std::list<T>::end();
          typename std::list<T>::const_iterator i = std::list<T>::begin();
          while (i!=e)
          {
            T startable = *i;
            startable->Stop();
            startable->Release();
            ++i;
          }
          std::list<T>::clear();
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller