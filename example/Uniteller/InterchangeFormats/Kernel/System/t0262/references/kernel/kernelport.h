// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит внешний интерфейс динамической библиотеки Uniteller.Framework.Kernel.dll 

#pragma once
#include "ikernelapi.h"
#include "inprocuidgen.h"
#include "xregistrykey.h"

#ifdef __GNUG__
#include "linux/libraryapi.h"
#endif // __GNUG__

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

#ifndef __GNUG__        
  #define KERNEL_DYNAMIC        
#else
  #ifndef PORTABLE_COMPILE
    #define KERNEL_DYNAMIC        
  #endif      
#endif      

#ifdef KERNEL_DYNAMIC        
      typedef IKernelApi * TLoadKernelApi();
      typedef void TUnloadKernelApi();
#endif      
      
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
      /// <summary>
      /// Валидация источника данных
      /// <summary>
      IEnumeration<IRegistryHive *> * ValidateDataSource(IRegistryDataSource * source, const char * szKind, const std::string & path);

      extern "C"
      {
        IRegistryDataSource * QueryVendorMetaData(HMODULE module, IKernelApi * api);
#ifndef KERNEL_DYNAMIC
      IKernelApi * LoadKernelApi();
      void UnloadKernelApi();        
#endif        
      }
#endif

      class KernelPort
      {
      private:
        SmartPointer<IKernelApi> m_Api;    
#ifdef KERNEL_DYNAMIC        
        HMODULE m_Library;
#endif        
        std::string m_SystemRoot;
      public:
        KernelPort()
        {
        }
        bool Load(const char * root)
        {          
          m_SystemRoot = root;
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
  #ifdef KERNEL_DYNAMIC
          m_Library = GetModuleHandle(NULL);
  #endif
#else
  #ifndef __GNUG__
          std::string sFilePath = m_SystemRoot + "\\Uniteller.Framework.Kernel.dll";
  #else
          std::string sFilePath = m_SystemRoot + "/Uniteller.Framework.Kernel.so";
  #endif
  #ifdef KERNEL_DYNAMIC          
          m_Library = LoadLibraryA(sFilePath.c_str());
          if (!m_Library)
          {
    #ifdef __GNUG__
            printf("[KERNEL] Load error: %s\r\n", dlerror());
    #endif
            return false;
          }
  #endif
#endif
#ifdef KERNEL_DYNAMIC
          TLoadKernelApi * api = (TLoadKernelApi *)GetProcAddress(m_Library, "LoadKernelApi");
          if (!api)
          {
#ifdef __GNUG__
            printf("[KERNEL] Function location error: %s\r\n", dlerror());
#endif
            return false;
          }
          m_Api <<= api();
#else
          m_Api <<= LoadKernelApi();
#endif
          return true;
        }
        /// <summary>
        /// Создает стандартный хост приложений
        /// </summary>
        /// <param name="argc">Число параметров командной строки.</param>
        /// <param name="argv">Параметры командной строки.</param>
        /// <returns></returns>
        IApplicationHost * StartApplication(int argc, char *argv[])
        {
          SmartPointer<IFactory> factory;
          SmartPointer<IUnicalIdGenerator> generator;
          factory <<= m_Api->GetStandardFactory();
          generator.Create<InprocUnicalIdGenerator>();

          factory->SetSystemRoot(m_SystemRoot.c_str());

#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
          SmartPointer<IRegistryDataSource> dataSource;
#ifdef KERNEL_DYNAMIC
          dataSource <<= QueryVendorMetaData(m_Library, m_Api.p);
#else
          dataSource <<= QueryVendorMetaData(NULL, m_Api.p);
#endif

          SmartPointer<IEnumeration<IRegistryHive *>> hive;
          hive <<= ValidateDataSource(dataSource.p, "Метаданные плеера", "$-$-$-$");

          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          registry->AddHives(hive.p);
#endif

          return m_Api->StartApplication(factory, generator, argc, argv);
        }
        void Unload()
        {
          m_Api.Release();
#ifndef KERNEL_DYNAMIC
          UnloadKernelApi();
#else          
          TUnloadKernelApi * api = (TUnloadKernelApi *)GetProcAddress(m_Library, "UnloadKernelApi");
          if (api)
            api();
          FreeLibrary(m_Library);
#endif          
        }
        int GetProcessExitCode()
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          RegistryKeyWrapper wrapper;
          wrapper <<= registry->Open("Kernel/Host/Environment");
          return wrapper.GetSubKeyValue<int>("ExitCode", 0);
        }
        std::string GetErrorDetails()
        {
          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();
          RegistryKeyWrapper wrapper;
          wrapper <<= registry->Open("Kernel/Host/Environment");
          return wrapper.GetSubKeyValue<std::string>("ErrorDetails", "");
        }
#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
        IFactory * QueryFactory()
        {
          return m_Api->GetStandardFactory();
        }
#endif
        std::string PrintProductVersionInfo(const char * szName)
        {
          SmartPointer<IFactory> factory;
          SmartPointer<IUnicalIdGenerator> generator;
          factory <<= m_Api->GetStandardFactory();
          generator.Create<InprocUnicalIdGenerator>();

          factory->SetSystemRoot(m_SystemRoot.c_str());

          SmartPointer<IRegistry> registry;
          registry <<= m_Api->GetRegistry();

#ifdef UNITELLER_FRAMEWORK_KERNEL_EXPORTS
          SmartPointer<IRegistryDataSource> dataSource;
#ifdef KERNEL_DYNAMIC
          dataSource <<= QueryVendorMetaData(m_Library, m_Api.p);
#else
          dataSource <<= QueryVendorMetaData(NULL, m_Api.p);
#endif

          SmartPointer<IEnumeration<IRegistryHive *>> hive;
          hive <<= ValidateDataSource(dataSource.p, "Метаданные плеера", "$-$-$-$");

          registry->AddHives(hive.p);
#endif
          factory->ColdLoad(szName, 1);

          std::string path = "Uniteller/ImageInfo/";
          path += szName;

          RegistryKeyWrapper wrapper;
          wrapper <<= registry->Open(path.c_str());

          if (wrapper.p)
          {
            std::string result = "Продукт ";
            result += wrapper.GetSubKeyValue<std::string>("ProductName", "Uniteller.Framework.Kernel.ConsoleHost");
            result += " ";
            result += wrapper.GetSubKeyValue<std::string>("ProductGoal", "t0500");
            result += " Версия: ";
            result += wrapper.GetSubKeyValue<std::string>("ProductVersion");
            return result;
          }
          else
            return "Error";
        }

      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller
