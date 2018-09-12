// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит базовую реализацию источника мета-данных

#pragma once

#ifndef __GNUG__
#include "stdafx.h"
#else
#include "kernel/linux/libraryapi.h"
#endif // __GNUG__

#include "ikernelapi.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   
      
      #define BEGIN_VENDOR_DATASOURCE() extern "C" { KERNEL_EXPORT IRegistryDataSource * QueryVendorMetaData(HMODULE module, IKernelApi * api) { \
        SmartPointer<IVendorDataSource> dataSource; \
        dataSource.Attach(api->CreateVendorDataSource());
      #define END_VENDOR_DATASOURCE() return dataSource.Detach();} }

      #define VENDOR_DATASOURCE(x) dataSource->Connect(module, x);

      typedef IRegistryDataSource * TQueryVendorMetaData(HMODULE module, IKernelApi * api);

      #define VENDOR_METADATA(x, len) dataSource->ConnectData(x, len);

      // Определяет стандартный источник метаданных в формате UTC
#ifndef __GNUG__
#define IMPLEMENT_VENDOR_DATASOURCE() BEGIN_VENDOR_DATASOURCE()  dataSource->ConnectUtc(module, IDR_VENDORMETADATA); END_VENDOR_DATASOURCE()
#else
      #define IMPLEMENT_VENDOR_DATASOURCE() extern uint8_t metadata[]; extern int metadata_size; BEGIN_VENDOR_DATASOURCE() VENDOR_METADATA(metadata, metadata_size); END_VENDOR_DATASOURCE()
#endif

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller