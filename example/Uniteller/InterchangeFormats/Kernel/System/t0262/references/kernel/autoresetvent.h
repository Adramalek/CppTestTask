// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

//���� �������� ���������� ResetEvent ��� ����������� ������� � ��������

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
      /// ����� ���������� ����������� �������
      /// </summary>
      struct AutoResetEvent
      {
        typedef std::unique_lock<std::mutex> Lock;

        /// <summary>
        /// ��������� ���������������� ��������� ��������� <see cref="AutoResetEvent"/>
        /// </summary>
        /// <param name="state">��������� (�� ��������� false)</param>
        AutoResetEvent(bool state = false) :
          state(state)
        { }

        /// <summary>
        /// ��������� ���������� ���������� �������
        /// </summary>
        void Set()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          state = true;
          variable.notify_one();
        }

        /// <summary>
        /// ��������� ������������� ���������� �������
        /// </summary>
        void Reset()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          state = false;
        }

        /// <summary>
        /// ��������� ������������� ���������� �������
        /// </summary>
        void Reset2()
        {
          state = false;
        }

        /// <summary>
        /// ��������� ������������� ���������� ������
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
        /// ��������� ������������� ���������� �������� ������
        /// </summary>
        void Wait()
        {
          std::unique_lock<std::mutex> lock = AcquireLock();
          Wait(lock);
        }

        /// <summary>
        /// ��������� ������������� ������� 
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

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Unitelle