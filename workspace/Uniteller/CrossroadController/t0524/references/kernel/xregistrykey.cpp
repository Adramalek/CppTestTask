// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит реализацию обертки вокруг указателя на ключ реестра
#ifdef __GNUG__
#if __GNUC__ < 5 
#include <mutex>
std::mutex global_sync;
#endif
#endif

#include "xregistrykey.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {
#ifdef __GNUG__
#if __GNUC__ < 5 
      long _InterlockedIncrement(long * x)
      {
        std::lock_guard<std::mutex> lk(global_sync);
        ++(*x);
        return *x;
      }
      long _InterlockedDecrement(long * x)
      {
        std::lock_guard<std::mutex> lk(global_sync);
        --(*x);
        return (*x);
      }
#endif
#endif

      RegistryKeyWrapperIterator RegistryKeyWrapper::begin() const
      {
        RegistryKeyWrapperIterator result;
        result.Attach(Begin());
        return result;
      }

      RegistryKeyWrapperIterator RegistryKeyWrapper::end() const
      {
        RegistryKeyWrapperIterator result;
        result.Attach(End());
        return result;
      }

      RegistryKeyWrapperIterator begin(RegistryKeyWrapper & container)
      {
        RegistryKeyWrapperIterator result;
        result.Attach(container.Begin());
        return result;
      }

      RegistryKeyWrapperIterator end(RegistryKeyWrapper & container)
      {
        RegistryKeyWrapperIterator result;
        result.Attach(container.End());
        return result;
      }

      RegistryKeyWrapperIterator begin(const RegistryKeyWrapper & container)
      {
        RegistryKeyWrapperIterator result;
        result.Attach(container.Begin());
        return result;
      }

      RegistryKeyWrapperIterator end(const RegistryKeyWrapper & container)
      {
        RegistryKeyWrapperIterator result;
        result.Attach(container.End());
        return result;
      }

    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller

