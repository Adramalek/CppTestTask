// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс ключа реестра

#pragma once

#include "iregistrydatasource.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      /// <summary>
      /// Интерфейс источника данных производителя модуля
      /// </summary>
      interface IVendorDataSource : public IRegistryDataSource
      {
      public:       
        /// <summary>
        /// Подключает источник к указанному ресурсу в формате UNITEXT в указанном модуле
        /// </summary>
        /// <param name="module">Модуль из которого будет загружен ресурс в формате UNITEXT.</param>
        /// <param name="resid">Идентификатор ресурса для загрузки.</param>
        virtual void Connect(void * module, int resid) = 0;        
        /// <summary>
        /// Подключает источник к указанному бинарным данным в формате UTC
        /// </summary>
        /// <param name="data">Данные источника.</param>
        /// <param name="len">Длина данных.</param>
        virtual void ConnectData(unsigned char data[], int len) = 0;
        /// <summary>
        /// Подключает источник к указанному бинарному ресурсу (содержимое передается как буфер) в формате UTC
        /// </summary>
        /// <param name="data">Данные источника.</param>
        /// <param name="len">Длина данных.</param>
        virtual void ConnectUtc(void * module, int resid) = 0;
      };

      typedef SmartPointer<IVendorDataSource> VendorDataSourcePtr;


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller

