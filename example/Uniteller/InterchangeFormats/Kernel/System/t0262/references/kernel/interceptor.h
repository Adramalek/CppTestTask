// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию модуля-перехватчика (interceptor)

#pragma once

#include <condition_variable>
#include "kernel/iexportable.h"
#include "kernel/exportable.h"
#include "kernel/globalpointer.h"

#ifndef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
#define IMPLEMENT_INTERCEPTORS
#else
#ifdef PORTABLE_COMPILE
#define IMPLEMENT_INTERCEPTORS
#endif
#endif



#ifdef IMPLEMENT_INTERCEPTORS
#include "Uniteller.Framework.Kernel.Tester.h"
#endif

#define PLATFORMAPI_ENDPOINT(Namespace) if (strcmp(szHive, Namespace::ApiId)==0) {\
  IExportable* old = Namespace::Platform.Detach();\
  if (api!=NULL)\
    Namespace::Platform = api;\
  else \
    Namespace::Platform.Create(); \
  return old; }

#define PLATFORMAPI(Namespace, Pointer) if (strcmp(szHive, Namespace::ApiId)==0) {\
  IExportable* old = Pointer.Detach();\
  if (api!=NULL)\
    Pointer = api;\
  else \
    Pointer.Create(); \
  return old; }

#define BEGIN_PLATFORMAPI_MAP() IExportable * SetPlatformApiEndpoint(const char * szHive, IExportable * api) {
#define END_PLATFORMAPI_MAP() return NULL; }

#define BEGIN_PLATFORMAPI_ENDPOINTS() extern "C" { KERNEL_EXPORT IExportable * ApiEndpoint(const char * szHive, IExportable * api) { 

#define END_PLATFORMAPI_ENDPOINTS() return NULL; } }

#ifdef IMPLEMENT_INTERCEPTORS
namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 
      typedef IExportable* (*InterceptedFunc)(const char * hive, IExportable* api);

      template <class T> 
      class ApiHandler : public Exportable<T>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;
      protected:
        Tester::Protocol::G1::Implementation* m_TesterProtocol;
        std::condition_variable m_Lock;
        std::mutex m_Mutex;
        int m_Res;
        std::string m_PeerId; // Адрес объекта, установившего интерцептор
        bool m_IsBlocked;
        bool m_IsInterceptorFailed;
      public:
        ApiHandler() : m_IsBlocked(false), m_IsInterceptorFailed(false)
        {
        }
        void Uninitialize()
        {
          m_IsBlocked = true;
          m_Res = 0;
          m_IsInterceptorFailed = true;
        }
        /// <summary>
        /// Снимает блокировку интерцептора
        /// </summary>
        void Unlock(bool fail = false)
        {
          m_IsInterceptorFailed = fail;          
          m_Lock.notify_all();
        }

        /// <summary>
        /// Блокировать
        /// </summary>
        void Lock()
        {
          m_IsInterceptorFailed = false;
          if (!m_IsBlocked)
          {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_Lock.wait(lock);
          }
        }

        void SetResultCode( int code )
        {
          m_Res = code;
        }

        void SetPeerId(const char * szId)
        {
          m_PeerId = szId;
        }
        const std::string GetPeerId()
        {
          return m_PeerId;
        }
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
#endif