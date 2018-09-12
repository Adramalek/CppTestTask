// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// ���� �������� ��������� ������� � �������������� �������

#pragma once

#ifdef __GNUG__

#include "gccsprt.h"

#define SEPARATOR "/"
#define SEPARATOR_CHAR '/'

#if __GNUC__ < 5 
#define override
#define nullptr NULL
#endif

#else

#define SEPARATOR "\\"
#define SEPARATOR_CHAR '\\'

#define KERNEL_EXPORT __declspec(dllexport)

// ��������� ����������� ������� ���������� ��������, ��������� ������ ��� ������
#define READONLY_PROPERTY(t, x) __declspec(property(get=Get##x)) t x
// ��������� ����������� ������� ���������� ��������
#define PROPERTY(t, x) __declspec(property(get=Get##x, put=Set##x)) t x

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define AUTO_PROPERTY(t, x) protected: \
  t m_##x; \
public: \
  t Get##x() const \
  { return m_##x; } \
  void Set##x(const t & value) \
  { m_##x = value; } \
  PROPERTY(t,x)

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define AUTO_PROPERTY_STRING(x) protected: \
  std::string m_##x; \
public: \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  void Set##x(const char * value) \
  { m_##x = value; } \
  PROPERTY(const char *,x)


// ��������� ����������� ������� ���������� ������������� ������������� �������� (���������)
#define POINTER_PROPERTY(t, x) protected: \
  t * m_##x; \
public: \
  t * Get##x() const \
  { return m_##x; } \
  void Set##x(const t * value) \
  { m_##x = value; } \
  PROPERTY(t*,x)

// ��������� ����������� ������� ���������� ������������� ������������� ��������, ��������� ������ ��� ������
#define READONLY_AUTO_PROPERTY(t, x) protected: \
  t m_##x; \
public: \
  t Get##x() const \
  { return m_##x; } \
  READONLY_PROPERTY(t,x)

// ������������ ��� ����������� ������� � �����������
#define PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� x @return x*/ virtual const t Get##x() const = 0; \
  /** ��������� ���������� x @param value x */ virtual void Set##x(const t & value) = 0

// ������������ ��� ����������� ������� � �����������
#define PROPERTY_DECLARATION_STRING(x) \
  /** ��������� �������� x @return doc*/ virtual const char * Get##x() const = 0; \
  /** ��������� ���������� x @param value doc */ virtual void Set##x(const char * value) = 0

// ������������ ��� ����������� ������� � �����������
#define POINTER_PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� x @return x*/ virtual t * Get##x() = 0; \
  /** ��������� ���������� x @param value x */ virtual void Set##x(t * value) = 0

// ������������ ��� ����������� � ����������� �������, ��������� ������ ��� ������
#define READONLY_PROPERTY_DECLARATION(t, x) \
  /** ��������� �������� x @return doc*/ virtual const t Get##x() const = 0

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define PROPERTY_IMPLEMENTATION(t, x) protected: \
  t m_##x; \
public: \
  /** ��������� �������� x @return x*/ \
  const t Get##x() const \
  { return m_##x; } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(const t & value) \
  { m_##x = value; } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) t x

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define PROPERTY_IMPLEMENTATION_STRING(x) protected: \
  std::string m_##x; \
public: \
  /** ��������� �������� x @return x*/ \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value) \
	{ m_##x = value; } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) const char * x

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define POINTER_PROPERTY_IMPLEMENTATION(t, x) protected: \
  t * m_##x; \
public: \
  /** ��������� �������� x @return x*/ \
  t * Get##x() const \
  { return m_##x; } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(t * value) \
  { m_##x = value; } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) t * x

// ��������� ����������� ������� ���������� ������������� ������������� ��������
#define SMART_POINTER_PROPERTY(t, x) protected: \
  SmartPointer<t> m_##x; \
public: \
  /** ��������� �������� x @return x*/ \
  t * Get##x() \
  { return m_##x.Copy(); } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(t * value) \
  { m_##x = value; } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) t * x

// ������������ ��� ����������� � ����������� �������, ��������� ������ ��� ������
#define READONLY_PROPERTY_IMPLEMENTATION(t, x) \
  protected: \
    t m_##x; \
  public: \
  /** ��������� �������� x @return x*/ \
  const t Get##x() const\
  { \
    return m_##x;\
  } \
  __declspec(property(get=Get##x)) t x

// �������������� ��������� ����������� ��������
#define PROPERTY_DELEGATION(t, x, object) \
  /** ��������� �������� x @return x*/ \
  const t Get##x() const \
  { return object->Get##x(); } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(const t & value) \
  { object->Set##x(value); } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) t x

// �������������� ��������� ����������� ��������
#define PROPERTY_DELEGATION_STRING(x, object) \
  /** ��������� �������� x @return x*/ \
  const char * Get##x() const \
  { return object->Get##x(); } \
  /** ��������� ���������� x @param value x */ \
  void Set##x(const char * value) \
  { object->Set##x(value); } \
  /** ��������: x*/ __declspec(property(get=Get##x, put=Set##x)) const char * x

// �������������� ��������� ����������� ��������
#define READONLY_PROPERTY_DELEGATION(t, x, object) \
  /** ��������� �������� x @return x*/ \
  t Get##x() const \
  { return object->Get##x(); } \
  /** ��������: doc*/ __declspec(property(get=Get##x)) t x

#define KERNEL_EXPORT __declspec(dllexport)
#endif


// ��������� ����� ���� ���������� ���������� (������ � C++ �������� ��������������� ������)
#ifdef interface
#undef interface
#endif

#define interface class

#define string_t char *

#define foreach(__iterator__, __variable__,  __container__) __iterator__ __variable__##end = __container__.end(); for (__iterator__ __variable__ = __container__.begin(); __variable__!=__variable__##end; ++__variable__)

// ������������ ��� ����������� ����������� ������ �� �������
#ifdef DUMPING
#ifndef __GNUG__
#define DUMP(format, ...) printf(format, __VA_ARGS__)
#else
#define DUMP(...) printf(__VA_ARGS__)
#endif
#else
#define DUMP(format, ...)
#endif


#ifndef __GNUG__

#define INIT_VECTOR(...) { __VA_ARGS__ }

#else

#if __GNUC__ < 5

#include <vector>

template <class T>
std::vector<T> Make_vector()
{  
  return std::vector<T>();
}

template <class ...T> 
std::vector<std::string> Make_vector(std::string argHead, T... argTail)
{
  std::vector<std::string> data;
  data.push_back(argHead);
  return Make_vector_(data, argTail...);
}

template <class T>
std::vector<T> Make_vector_(std::vector<T> & data)
{
  return data;
}

template <class ...T> 
std::vector<std::string> Make_vector_(std::vector<std::string> & data, std::string argHead, T... argTail)
{
  data.push_back(argHead);
  return Make_vector_(data, argTail...);
}

#define INIT_VECTOR(args...) Make_vector(args)

#else

#define INIT_VECTOR(args...) { args }

#endif

#endif