// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ������� ���������� ���� �������


#pragma once
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// ������ ���� �������. ���������� ������������� SimpleThreadPool<std::function<void (void)>>
      /// </summary>
      template <class t>
      class SimpleThreadPool
      {
      private:
        std::vector<std::thread*> m_ThreadsList;
        std::mutex m_Lock;

      public:
        /// <summary>
        /// �����������
        /// </summary>
        SimpleThreadPool(void)
        {
        }
        /// <summary>
        /// ����������
        /// </summary>
        ~SimpleThreadPool(void)
        {
          Stop();
        }

        void Stop()
        {
          for(auto thr : m_ThreadsList)
          {
            thr->join();
            delete thr;
          }
          m_ThreadsList.clear();
        }

        /// <summary>
        /// ��������� ������ �� ����������� ����������
        /// </summary>
        void RunAsync(t work)
        {
          std::unique_lock<std::mutex> lk(m_Lock);          

          std::vector<std::thread*>::iterator i = m_ThreadsList.begin();

          while (i != m_ThreadsList.end()) 
          {
            std::thread* thr = *i;

            if (thr->joinable())
            {
              thr->join();
              i = m_ThreadsList.erase(i);

              delete thr;
            }
            else
              ++i;
          }

          m_ThreadsList.push_back(new std::thread(work));

          //m_Lock.unlock();
        }
      };

    } // ������������ ���� Kernel
  } // ������������ ���� Framework 
} // ������������ ���� Uniteller