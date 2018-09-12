#pragma once

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    { 

      /// <summary>
      /// Результат загрузки модуля-расширения (плагина)
      /// </summary>
      enum class ExtensionLoadResult
      {
        Success = 0,
        Fail = 1,
        NotExist = 2
      };

    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller