// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит интерфейс ключа реестра

#pragma once

#include "ivariant.h"
#include "ienumeration.h"

#ifdef __GNUG__
#include "linuxsprt.h"
#endif // __GNUG__

namespace Uniteller
{
  namespace Framework
  {
    namespace Kernel
    {

      class IRegistryKey;

      /// <summary>
      /// Интерфейс итератора, обеспечивающего обход ключей реестра
      /// <summary>
      interface IRegistryKeyIterator : public IExportable
      {
      public:
        virtual bool IsEqualTo(IRegistryKeyIterator * iterator) = 0;
        virtual IRegistryKeyIterator * MoveNext() = 0;
        virtual IRegistryKey * GetValue() = 0;
        virtual IRegistryKeyIterator * Advance(int x) = 0;
      };

      /// <summary>
      /// Интерфейс ключа реестра
      /// </summary>
      interface IRegistryKey : public IExportable
      {
      public:
        // имя ключа
        PROPERTY_DECLARATION_STRING(Name);
        // значение ключа
        POINTER_PROPERTY_DECLARATION(IVariant, Value);

      #pragma region Subkeys management functions

        /// <summary>
        /// Позволяет добавить дочерний узел
        /// </summary>
        /// <param name="child">Дочерний узел.</param>
        virtual void AddChild(IRegistryKey * child) = 0;

        /// <summary>
        /// Позволяет проверить существует ли ключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Существует ли ключ (true - да, false - нет).</returns>
        virtual bool IsSubKeyExists(const char * name) const = 0;
        /// <summary>
        /// Возвращает подключ по имени.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Указатель на подключ, если он существует, NULL - иначе.</returns>
        virtual IRegistryKey * GetSubKey(const char * name) = 0;
        /// <summary>
        /// Создает новый подключ.
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        virtual void CreateSubKey(const char * name, IVariant * value) = 0;
        /// <summary>
        /// Позволяет удалить подключ.
        /// </summary>
        /// <param name="name">Имя подключа для удаления.</param>
        virtual void RemoveSubKey(const char * name) = 0;
        /// <summary>
        /// Возвращает значение подключа
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <returns>Значение подключа (если он существует или NULL иначе).</returns>
        virtual IVariant * GetSubKeyValue(const char * name) const = 0;
        /// <summary>
        /// Устанавливает значение подключа
        /// </summary>
        /// <param name="name">Имя подключа.</param>
        /// <param name="value">Значение подключа.</param>
        /// <description>
        /// Используется для установки новых значений в подключи. Если передать имя не существующего подключа,
        /// то он будет создан и ему будет установлено значение <paramref name="value"/>.
        /// </description>
        virtual void SetSubKeyValue(const char * name, IVariant * value) = 0;

        /// <summary>
        /// Позволяет получить число подключей данного ключа
        /// </summary>
        /// <returns>Число подключей</returns>
        virtual size_t GetSubKeysCount() const = 0;

        /// <summary>
        /// Позволяет получить подключи данного ключа
        /// </summary>
        /// <returns>Контейнер, содержащий все подключи данного ключа.</returns>
        virtual IEnumeration<IRegistryKey *> * GetSubKeys() = 0;
      #pragma endregion

      #pragma region Query functions
        /// <summary>
        /// Позволяет проверить существует ли ключ.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Существует ли ключ (true - да, false - нет).</returns>
        virtual bool IsKeyExists(const char * path) = 0;
        /// <summary>
        /// Возвращает ключ по пути.
        /// </summary>
        /// <param name="name">Путь к ключу.</param>
        /// <returns>Указатель на ключ, если он существует, NULL - иначе.</returns>
        virtual IRegistryKey * GetKey(const char * path) = 0;
        /// <summary>
        /// Создает ключ
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа.</param>
        virtual void CreateKey(const char * path, IVariant * value) = 0;
        /// <summary>
        /// Удаляет ключ.
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        virtual void RemoveKey(const char * path) = 0;
        /// <summary>
        /// Возвращает значение ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Значение ключа (если он существует или NULL иначе).</returns>
        virtual IVariant * GetKeyValue(const char * path)  = 0;
        /// <summary>
        /// Устанавливает значение ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <param name="value">Значение ключа</param>
        /// <description>
        /// Используется для установки новых значений в ключи. Если передать имя не существующего ключа,
        /// то он будет создан (если надо с родительскими ключами) и ему будет установлено значение <paramref name="value"/>.
        /// </description>
        virtual void SetKeyValue(const char * path, IVariant * value) = 0;

        /// <summary>
        /// Позволяет получить число подключей данного ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Число подключей</returns>
        virtual size_t GetSubKeysCount(const char * path) = 0;

        /// <summary>
        /// Позволяет получить подключи данного ключа
        /// </summary>
        /// <param name="path">Путь к ключу.</param>
        /// <returns>Контейнер, содержащий все подключи данного ключа.</returns>
        virtual IEnumeration<IRegistryKey *> * GetSubKeys(const char * path) = 0;

      #pragma endregion

        /// <summary>
        /// Очищает все подключи данного
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// Позволяет получить итератор, указывающий на первый подключ данного ключа
        /// </summary>
        /// <returns>Указатель на итератор, указывающий на первый подключ данного ключа</returns>
        virtual IRegistryKeyIterator * Begin() = 0;
        /// <summary>
        /// Позволяет получить итератор, указывающий на конец подключей данного ключа
        /// </summary>
        /// <returns>Указатель на итератор, указывающий на конец подключей данного ключа</returns>
        virtual IRegistryKeyIterator * End() = 0;

        // Функции быстрого доступа
	      virtual IVariant * PeekValue() = 0;
	      /// <summary>
	      /// Возвращает значение ключа
	      /// </summary>
	      /// <param name="path">Путь к ключу.</param>
	      /// <returns>Значение ключа (если он существует или NULL иначе).</returns>
	      virtual IVariant * PeekKeyValue(const char * path) = 0;
	      /// <summary>
	      /// Возвращает значение подключа
	      /// </summary>
	      /// <param name="name">Имя подключа.</param>
	      /// <returns>Значение подключа (если он существует или NULL иначе).</returns>
	      virtual IVariant * PeekSubKeyValue(const char * name) const = 0;
	      virtual IRegistryKey * PeekSubKey(const char * name) = 0;

        /// <summary>
        /// Выполняет поиск первого совпавшего с маской xpath узла в реестре
        /// </summary>
        /// <param name="xpath">Маска пути узла для поиска, может содержать *, означающее произвольное имя узла</param>
        /// <returns>Указатель на первый найденный ключ или NULL.</returns>
        virtual IRegistryKey * SelectFirst(const char * xpath) = 0;
      };

      typedef SmartPointer<IRegistryKey> RegistryKeyPtr;
      typedef SmartPointer<IEnumeration<IRegistryKey *>> RegKeyCollectionPtr;


    } // пространство имен Kernel
  } // пространство имен Framework
} // пространство имен Uniteller
