#pragma once

#include <vector>
#include "ienumeration.h"
#include "ivariant.h"

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel 
    {   

      template <class X>
      inline X VariantPtrTo(IVariant * value);

      /// <summary>
      /// Реализация экспортируемого перечисления
      /// </summary>
      template <class T>
      class ExportableEnumeration : public Exportable<IEnumeration<T *>>
      {
        // В качестве параметра следует передавать интерфейс, наследующий IExportable
        typedef typename T::IsExportable OnlyExportable;

        // Используется для хранения данных
        std::vector<T *> m_Data;
      public: // Свойства
        /// <summary>
        /// Возвращает число элементов в перечислении
        /// </summary>
        /// <returns></returns>
        const size_t GetCount() const
        {
          return m_Data.size();
        }
      public:
        /// <summary>
        /// Конструктор
        /// </summary>
        ExportableEnumeration()
        {
        }
				ExportableEnumeration(const ExportableEnumeration & src)
				{
					size_t max = src.m_Data.size();
					m_Data.resize(max);
					for (size_t i = 0; i < max; ++i)
					{
						m_Data[i] = src.m_Data[i];
						m_Data[i]->AddRef();
					}
				}
        ~ExportableEnumeration()
        {
          Clear();
        }
      public: // Методы
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        T * GetItem(int index) 
        {
          T * p = m_Data[index];
          if (p)
            p->AddRef();
          return p;
        }          
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу с преобразованием к требуемому типу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        template <class Y>
        const Y GetItem(int index)
        {
          T * p = m_Data[index];
          if (p)
            return VariantPtrTo<Y>(p);
          return Y();
        }
        /// <summary>
        /// Позволяет получить элемент из перечисления по индексу с преобразованием к требуемому типу
        /// </summary>
        /// <param name="index">Индекс элемента перечисления</param>
        /// <param name="defvl">Значение по-умолчанию</param>
        /// <returns>Элемент перечесления с индексом index</returns>
        template <class Y>
        const Y GetItem(int index, const Y & defvl)
        {
          T * p = m_Data[index];
          if (p)
            return VariantPtrTo<Y>(p);
          return defvl;
        } 
        /// <summary>
        /// Позволяет очистить перечисление
        /// </summary>
        void Clear()
        {
          size_t max = m_Data.size();
          for (size_t i = 0; i<max; ++i)
          {
            T * p = m_Data[i];
            //if (p) - Пустым быть не может
              p->Release();
          }
          m_Data.resize(0);
        }
        /// <summary>
        /// Позволяет добавить элемент в перечисление (в конец)
        /// </summary>
        /// <param name="value">Значение, добавляемое в перечисление</param>
        void Add(T * value)
        {
          if (value)
          {
            value->AddRef();
            m_Data.push_back(value);
          }
        }  
        /// <summary>
        /// Позволяет объединить два перечисления в одно
        /// </summary>
        /// <param name="other">Перечисление для объединения с данным.</param>
        void MergeWith(IEnumeration<T *> * other)
        {
          size_t max = other->GetCount();
          for (size_t i = 0; i<max; ++i)
            m_Data.push_back(other->GetItem(i));
        }

        ExportableEnumeration<T> & operator=(const ExportableEnumeration<T>& src)
        {
          size_t max = src.m_Data.size();
          m_Data.resize(max);
          for (size_t i = 0; i < max; ++i)
          {
            m_Data[i] = src.m_Data[i];
            m_Data[i]->AddRef();
          }
          return *this;
        }

      };


    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller