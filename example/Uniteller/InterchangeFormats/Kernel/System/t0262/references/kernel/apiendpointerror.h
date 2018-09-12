#pragma once

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 


      enum class ApiEndpointError
      {
        Success = 0,
        NotInterceptor = 1,
        Failed = 2,
        CouldNotLoadLibrary = 3,
        ModuleHaveNoEndPoint = 4,
        AddressNotExists = 5
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller