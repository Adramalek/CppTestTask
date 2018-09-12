// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ����� �������

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
      /// ��������� ���������, ��������������� ����� ������ �������
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
      /// ��������� ����� �������
      /// </summary>
      interface IRegistryKey : public IExportable
      {
      public:
        // ��� �����
        PROPERTY_DECLARATION_STRING(Name);
        // �������� �����
        POINTER_PROPERTY_DECLARATION(IVariant, Value);

      #pragma region Subkeys management functions

        /// <summary>
        /// ��������� �������� �������� ����
        /// </summary>
        /// <param name="child">�������� ����.</param>
        virtual void AddChild(IRegistryKey * child) = 0;

        /// <summary>
        /// ��������� ��������� ���������� �� ����.
        /// </summary>
        /// <param name="name">��� ��������.</param>
        /// <returns>���������� �� ���� (true - ��, false - ���).</returns>
        virtual bool IsSubKeyExists(const char * name) const = 0;
        /// <summary>
        /// ���������� ������� �� �����.
        /// </summary>
        /// <param name="name">��� ��������.</param>
        /// <returns>��������� �� �������, ���� �� ����������, NULL - �����.</returns>
        virtual IRegistryKey * GetSubKey(const char * name) = 0;
        /// <summary>
        /// ������� ����� �������.
        /// </summary>
        /// <param name="name">��� ��������.</param>
        /// <param name="value">�������� ��������.</param>
        virtual void CreateSubKey(const char * name, IVariant * value) = 0;
        /// <summary>
        /// ��������� ������� �������.
        /// </summary>
        /// <param name="name">��� �������� ��� ��������.</param>
        virtual void RemoveSubKey(const char * name) = 0;
        /// <summary>
        /// ���������� �������� ��������
        /// </summary>
        /// <param name="name">��� ��������.</param>
        /// <returns>�������� �������� (���� �� ���������� ��� NULL �����).</returns>
        virtual IVariant * GetSubKeyValue(const char * name) const = 0;
        /// <summary>
        /// ������������� �������� ��������
        /// </summary>
        /// <param name="name">��� ��������.</param>
        /// <param name="value">�������� ��������.</param>
        /// <description>
        /// ������������ ��� ��������� ����� �������� � ��������. ���� �������� ��� �� ������������� ��������,
        /// �� �� ����� ������ � ��� ����� ����������� �������� <paramref name="value"/>.
        /// </description>
        virtual void SetSubKeyValue(const char * name, IVariant * value) = 0;

        /// <summary>
        /// ��������� �������� ����� ��������� ������� �����
        /// </summary>
        /// <returns>����� ���������</returns>
        virtual size_t GetSubKeysCount() const = 0;

        /// <summary>
        /// ��������� �������� �������� ������� �����
        /// </summary>
        /// <returns>���������, ���������� ��� �������� ������� �����.</returns>
        virtual IEnumeration<IRegistryKey *> * GetSubKeys() = 0;
      #pragma endregion

      #pragma region Query functions
        /// <summary>
        /// ��������� ��������� ���������� �� ����.
        /// </summary>
        /// <param name="name">���� � �����.</param>
        /// <returns>���������� �� ���� (true - ��, false - ���).</returns>
        virtual bool IsKeyExists(const char * path) = 0;
        /// <summary>
        /// ���������� ���� �� ����.
        /// </summary>
        /// <param name="name">���� � �����.</param>
        /// <returns>��������� �� ����, ���� �� ����������, NULL - �����.</returns>
        virtual IRegistryKey * GetKey(const char * path) = 0;
        /// <summary>
        /// ������� ����
        /// </summary>
        /// <param name="path">���� � �����.</param>
        /// <param name="value">�������� �����.</param>
        virtual void CreateKey(const char * path, IVariant * value) = 0;
        /// <summary>
        /// ������� ����.
        /// </summary>
        /// <param name="path">���� � �����.</param>
        virtual void RemoveKey(const char * path) = 0;
        /// <summary>
        /// ���������� �������� �����
        /// </summary>
        /// <param name="path">���� � �����.</param>
        /// <returns>�������� ����� (���� �� ���������� ��� NULL �����).</returns>
        virtual IVariant * GetKeyValue(const char * path)  = 0;
        /// <summary>
        /// ������������� �������� �����
        /// </summary>
        /// <param name="path">���� � �����.</param>
        /// <param name="value">�������� �����</param>
        /// <description>
        /// ������������ ��� ��������� ����� �������� � �����. ���� �������� ��� �� ������������� �����,
        /// �� �� ����� ������ (���� ���� � ������������� �������) � ��� ����� ����������� �������� <paramref name="value"/>.
        /// </description>
        virtual void SetKeyValue(const char * path, IVariant * value) = 0;

        /// <summary>
        /// ��������� �������� ����� ��������� ������� �����
        /// </summary>
        /// <param name="path">���� � �����.</param>
        /// <returns>����� ���������</returns>
        virtual size_t GetSubKeysCount(const char * path) = 0;

        /// <summary>
        /// ��������� �������� �������� ������� �����
        /// </summary>
        /// <param name="path">���� � �����.</param>
        /// <returns>���������, ���������� ��� �������� ������� �����.</returns>
        virtual IEnumeration<IRegistryKey *> * GetSubKeys(const char * path) = 0;

      #pragma endregion

        /// <summary>
        /// ������� ��� �������� �������
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// ��������� �������� ��������, ����������� �� ������ ������� ������� �����
        /// </summary>
        /// <returns>��������� �� ��������, ����������� �� ������ ������� ������� �����</returns>
        virtual IRegistryKeyIterator * Begin() = 0;
        /// <summary>
        /// ��������� �������� ��������, ����������� �� ����� ��������� ������� �����
        /// </summary>
        /// <returns>��������� �� ��������, ����������� �� ����� ��������� ������� �����</returns>
        virtual IRegistryKeyIterator * End() = 0;

        // ������� �������� �������
	      virtual IVariant * PeekValue() = 0;
	      /// <summary>
	      /// ���������� �������� �����
	      /// </summary>
	      /// <param name="path">���� � �����.</param>
	      /// <returns>�������� ����� (���� �� ���������� ��� NULL �����).</returns>
	      virtual IVariant * PeekKeyValue(const char * path) = 0;
	      /// <summary>
	      /// ���������� �������� ��������
	      /// </summary>
	      /// <param name="name">��� ��������.</param>
	      /// <returns>�������� �������� (���� �� ���������� ��� NULL �����).</returns>
	      virtual IVariant * PeekSubKeyValue(const char * name) const = 0;
	      virtual IRegistryKey * PeekSubKey(const char * name) = 0;

        /// <summary>
        /// ��������� ����� ������� ���������� � ������ xpath ���� � �������
        /// </summary>
        /// <param name="xpath">����� ���� ���� ��� ������, ����� ��������� *, ���������� ������������ ��� ����</param>
        /// <returns>��������� �� ������ ��������� ���� ��� NULL.</returns>
        virtual IRegistryKey * SelectFirst(const char * xpath) = 0;
      };

      typedef SmartPointer<IRegistryKey> RegistryKeyPtr;
      typedef SmartPointer<IEnumeration<IRegistryKey *>> RegKeyCollectionPtr;


    } // ������������ ���� Kernel
  } // ������������ ���� Framework
} // ������������ ���� Uniteller
