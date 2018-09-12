// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ������� � �������������� ������� ��� Linux

#pragma once

#include "linuxsprt.h"

// ��������� ����������� ������� ���������� ��������, ��������� ������ ��� ������
#define READONLY_PROPERTY(t, x)
// ��������� ����������� ������� ���������� ��������
#define PROPERTY(t, x)

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define AUTO_PROPERTY(t, x) public: \
  t Get##x() const \
    { return m_##x; } \
  void Set##x(const t & value) \
    { m_##x = value; } \
  protected: t m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define AUTO_PROPERTY_STRING(x) public: \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value)\
  {m_##x = value; }\
  protected: std::string m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� �������� (���������)
#define POINTER_PROPERTY(t, x) public: \
  t * Get##x() const \
    { return m_##x; } \
  void Set##x(t * value) \
    { m_##x = value; } \
  protected: t * m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� ��������, ��������� ������ ��� ������
#define READONLY_AUTO_PROPERTY(t, x) public: \
  t Get##x() const \
  { return m_##x; }\
  protected: t m_##x; public:

// ������������ ��� ����������� ������� � �����������
#define PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� doc @return doc*/ virtual const t Get##x() const = 0; \
  /** ��������� ���������� doc @param value doc */ virtual void Set##x(const t & value) = 0

// ������������ ��� ����������� ������� � �����������
#define PROPERTY_DECLARATION_STRING(x) \
  /** ��������� �������� doc @return doc*/ virtual const char * Get##x() const = 0; \
  /** ��������� ���������� doc @param value doc */ virtual void Set##x(const char * value) = 0

// ������������ ��� ����������� ������� � �����������
#define POINTER_PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� doc @return doc*/ virtual t * Get##x() = 0; \
  /** ��������� ���������� doc @param value doc */ virtual void Set##x(t * value) = 0

// ������������ ��� ����������� � ����������� �������, ��������� ������ ��� ������
#define READONLY_PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� doc @return doc*/ virtual const t Get##x() const = 0

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define PROPERTY_IMPLEMENTATION(t, x) public: \
  /** ��������� �������� doc @return doc*/ \
  const t Get##x() const \
        { return m_##x; } \
  /** ��������� ���������� doc @param value doc */ \
  void Set##x(const t & value) \
        { m_##x = value; } \
  protected: t m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define PROPERTY_IMPLEMENTATION_STRING(x) public: \
  /** ��������� �������� doc @return doc*/ \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  /** ��������� ���������� doc @param value doc */ \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value) \
	{ m_##x = value; } \
  protected: std::string m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define POINTER_PROPERTY_IMPLEMENTATION(t, x) public: \
  public: \
  t * Get##x() const\
  { return m_##x; } \
  void Set##x(t * value)\
  { m_##x = value; } \
  protected: t * m_##x; public:

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define SMART_POINTER_PROPERTY(t, x) protected: \
  SmartPointer<t> m_##x; \
public: \
  /** ��������� �������� doc @return doc*/ \
  t * Get##x() \
  { return m_##x.Copy(); } \
  /** ��������� ���������� doc @param value doc */ \
  void Set##x(t * value) \
  { m_##x = value; }

// ������������ ��� ����������� � ����������� �������, ��������� ������ ��� ������
#define READONLY_PROPERTY_IMPLEMENTATION(t, x) \
  public: \
  /** ��������� �������� doc @return x*/ \
  const t Get##x() const\
  { return m_##x; } \
  protected: t m_##x; \
  public:

// �������������� ��������� ����������� ��������
#define PROPERTY_DELEGATION(t, x, object) \
  /** ��������� �������� doc @return doc*/ \
  const t Get##x() const \
  { return object->Get##x(); } \
  /** ��������� ���������� doc @param value doc */ \
  void Set##x(const t & value) \
  { object->Set##x(value); }

// �������������� ��������� ����������� ��������
#define PROPERTY_DELEGATION_STRING(x, object) \
  /** ��������� �������� doc @return doc*/ \
  const char * Get##x() const \
  { return object->Get##x(); } \
  /** ��������� ���������� doc @param value doc */ \
  void Set##x(const char * value) \
  { object->Set##x(value); }

// �������������� ��������� ����������� ��������
#define READONLY_PROPERTY_DELEGATION(t, x, object) \
  /** ��������� �������� doc @return doc*/ \
  t Get##x() const \
  { return object->Get##x(); }

