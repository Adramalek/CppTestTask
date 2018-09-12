// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

//‘айл содержит реализацию ResetEvent дл€ уведомлени€ потоков о событи€х

#pragma once

#include <mutex>
#include <condition_variable>

#ifdef __GNUG__

#if __GNUC__ < 5
#define NEWPOS
#endif

#endif

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
      
      /// <summary>
      ///  ласс управлени€ блокировкой потоков
      /// </summary>
      struct AutoResetEvent
      {
        typedef std::unique_lock<std::mutex> Lock;

        /// <summary>
        /// ѕозвол€ет инициализировать начальное состо€ние <see cref="AutoResetEvent"/>
        /// </summary>
        /// <param name="state">—осто€ние (по умолчанию false)</param>
        AutoResetEvent(bool state = false) :
          state(state)
        { }

        /// <summary>
        /// ѕозвол€ет продолжить выполнение потоков
        /// </summary>
        void Set()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          state = true;
          variable.notify_one();
        }

        /// <summary>
        /// ѕозвол€ет заблокировать выполнение потоков
        /// </summary>
        void Reset()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          state = false;
        }

        /// <summary>
        /// ѕозвол€ет заблокировать выполнение потоков
        /// </summary>
        void Reset2()
        {
          state = false;
        }

        /// <summary>
        /// ѕозвол€ет заблокировать выполнение потока
        /// </summary>
        /// <param name="lock">unique_lock</param>
        void Wait(Lock& lock)
        {
#ifndef NEWPOS
          variable.wait(lock, [this] () { return this->state; });
#else
          variable.wait(lock, std::bind(&AutoResetEvent::CheckState, this)); //[this] () { return this->state; });
#endif
          state = false;
        }

#ifdef NEWPOS
        bool CheckState()
        {
          return this->state;
        }
#endif

        /// <summary>
        /// ѕозвол€ет заблокировать выполнение текущего потока
        /// </summary>
        void Wait()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          Wait(lock);
        }

        /// <summary>
        /// ѕозвол€ет заблокировать мьютекс 
        /// </summary>
        /// <returns></returns>
        Lock AcquireLock()
        {
          return Lock(mutex);
        }
      private:

        bool state;
        std::condition_variable variable;
        std::mutex mutex;
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Unitelle