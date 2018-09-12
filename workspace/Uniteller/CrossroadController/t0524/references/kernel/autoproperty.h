// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит поддержку свойств и автоматических свойств

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

// Позволяет стандартным образом определять свойства, доступные только для чтения
#define READONLY_PROPERTY(t, x) __declspec(property(get=Get##x)) t x
// Позволяет стандартным образом определять свойства
#define PROPERTY(t, x) __declspec(property(get=Get##x, put=Set##x)) t x

// Позволяет стандартным образом определять автоматически реализованные свойства
#define AUTO_PROPERTY(t, x) protected: \
  t m_##x; \
public: \
  t Get##x() const \
  { return m_##x; } \
  void Set##x(const t & value) \
  { m_##x = value; } \
  PROPERTY(t,x)

// Позволяет стандартным образом определять автоматически реализованные свойства
#define AUTO_PROPERTY_STRING(x) protected: \
  std::string m_##x; \
public: \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  void Set##x(const char * value) \
  { m_##x = value; } \
  PROPERTY(const char *,x)


// Позволяет стандартным образом определять автоматически реализованные свойства (указатели)
#define POINTER_PROPERTY(t, x) protected: \
  t * m_##x; \
public: \
  t * Get##x() const \
  { return m_##x; } \
  void Set##x(const t * value) \
  { m_##x = value; } \
  PROPERTY(t*,x)

// Позволяет стандартным образом определять автоматически реализованные свойства, доступные только для чтения
#define READONLY_AUTO_PROPERTY(t, x) protected: \
  t m_##x; \
public: \
  t Get##x() const \
  { return m_##x; } \
  READONLY_PROPERTY(t,x)

// Используется для определения свойств в интерфейсах
#define PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить x @return x*/ virtual const t Get##x() const = 0; \
  /** Позволяет установить x @param value x */ virtual void Set##x(const t & value) = 0

// Используется для определения свойств в интерфейсах
#define PROPERTY_DECLARATION_STRING(x) \
  /** Позволяет получить x @return doc*/ virtual const char * Get##x() const = 0; \
  /** Позволяет установить x @param value doc */ virtual void Set##x(const char * value) = 0

// Используется для определения свойств в интерфейсах
#define POINTER_PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить x @return x*/ virtual t * Get##x() = 0; \
  /** Позволяет установить x @param value x */ virtual void Set##x(t * value) = 0

// Используется для определения в интерфейсах свойств, доступных только для чтения
#define READONLY_PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить x @return doc*/ virtual const t Get##x() const = 0

// Позволяет стандартным образом определять автоматически реализованные свойства
#define PROPERTY_IMPLEMENTATION(t, x) protected: \
  t m_##x; \
public: \
  /** Позволяет получить x @return x*/ \
  const t Get##x() const \
  { return m_##x; } \
  /** Позволяет установить x @param value x */ \
  void Set##x(const t & value) \
  { m_##x = value; } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) t x

// Позволяет стандартным образом определять автоматически реализованные свойства
#define PROPERTY_IMPLEMENTATION_STRING(x) protected: \
  std::string m_##x; \
public: \
  /** Позволяет получить x @return x*/ \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  /** Позволяет установить x @param value x */ \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value) \
	{ m_##x = value; } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) const char * x

// Позволяет стандартным образом определять автоматически реализованные свойства
#define POINTER_PROPERTY_IMPLEMENTATION(t, x) protected: \
  t * m_##x; \
public: \
  /** Позволяет получить x @return x*/ \
  t * Get##x() const \
  { return m_##x; } \
  /** Позволяет установить x @param value x */ \
  void Set##x(t * value) \
  { m_##x = value; } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) t * x

// Позволяет стандартным образом определять автоматически реализованные свойства
#define SMART_POINTER_PROPERTY(t, x) protected: \
  SmartPointer<t> m_##x; \
public: \
  /** Позволяет получить x @return x*/ \
  t * Get##x() \
  { return m_##x.Copy(); } \
  /** Позволяет установить x @param value x */ \
  void Set##x(t * value) \
  { m_##x = value; } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) t * x

// Используется для определения в интерфейсах свойств, доступных только для чтения
#define READONLY_PROPERTY_IMPLEMENTATION(t, x) \
  protected: \
    t m_##x; \
  public: \
  /** Позволяет получить x @return x*/ \
  const t Get##x() const\
  { \
    return m_##x;\
  } \
  __declspec(property(get=Get##x)) t x

// Имплементирует делегацию реализацией свойства
#define PROPERTY_DELEGATION(t, x, object) \
  /** Позволяет получить x @return x*/ \
  const t Get##x() const \
  { return object->Get##x(); } \
  /** Позволяет установить x @param value x */ \
  void Set##x(const t & value) \
  { object->Set##x(value); } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) t x

// Имплементирует делегацию реализацией свойства
#define PROPERTY_DELEGATION_STRING(x, object) \
  /** Позволяет получить x @return x*/ \
  const char * Get##x() const \
  { return object->Get##x(); } \
  /** Позволяет установить x @param value x */ \
  void Set##x(const char * value) \
  { object->Set##x(value); } \
  /** Свойство: x*/ __declspec(property(get=Get##x, put=Set##x)) const char * x

// Имплементирует делегацию реализацией свойства
#define READONLY_PROPERTY_DELEGATION(t, x, object) \
  /** Позволяет получить x @return x*/ \
  t Get##x() const \
  { return object->Get##x(); } \
  /** Свойство: doc*/ __declspec(property(get=Get##x)) t x

#define KERNEL_EXPORT __declspec(dllexport)
#endif


// Позволяет более явно определять интерфейсы (вносим в C++ немножко синтаксического сахара)
#ifdef interface
#undef interface
#endif

#define interface class

#define string_t char *

#define foreach(__iterator__, __variable__,  __container__) __iterator__ __variable__##end = __container__.end(); for (__iterator__ __variable__ = __container__.begin(); __variable__!=__variable__##end; ++__variable__)

// Используется для организации отладочного вывода на консоль
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