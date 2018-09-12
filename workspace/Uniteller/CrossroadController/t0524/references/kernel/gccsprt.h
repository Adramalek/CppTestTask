// Uniteller.Framework.Kernel
// Version: 1.0.0
// Generation: 1

// Файл содержит поддержку свойств и автоматических свойств для Linux

#pragma once

#include "linuxsprt.h"

// Позволяет стандартным образом определять свойства, доступные только для чтения
#define READONLY_PROPERTY(t, x)
// Позволяет стандартным образом определять свойства
#define PROPERTY(t, x)

// Позволяет стандартным образом определять автоматически реализованные свойства
#define AUTO_PROPERTY(t, x) public: \
  t Get##x() const \
    { return m_##x; } \
  void Set##x(const t & value) \
    { m_##x = value; } \
  protected: t m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства
#define AUTO_PROPERTY_STRING(x) public: \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value)\
  {m_##x = value; }\
  protected: std::string m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства (указатели)
#define POINTER_PROPERTY(t, x) public: \
  t * Get##x() const \
    { return m_##x; } \
  void Set##x(t * value) \
    { m_##x = value; } \
  protected: t * m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства, доступные только для чтения
#define READONLY_AUTO_PROPERTY(t, x) public: \
  t Get##x() const \
  { return m_##x; }\
  protected: t m_##x; public:

// Используется для определения свойств в интерфейсах
#define PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить doc @return doc*/ virtual const t Get##x() const = 0; \
  /** Позволяет установить doc @param value doc */ virtual void Set##x(const t & value) = 0

// Используется для определения свойств в интерфейсах
#define PROPERTY_DECLARATION_STRING(x) \
  /** Позволяет получить doc @return doc*/ virtual const char * Get##x() const = 0; \
  /** Позволяет установить doc @param value doc */ virtual void Set##x(const char * value) = 0

// Используется для определения свойств в интерфейсах
#define POINTER_PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить doc @return doc*/ virtual t * Get##x() = 0; \
  /** Позволяет установить doc @param value doc */ virtual void Set##x(t * value) = 0

// Используется для определения в интерфейсах свойств, доступных только для чтения
#define READONLY_PROPERTY_DECLARATION(t, x) \
  /** Позволяет получить doc @return doc*/ virtual const t Get##x() const = 0

// Позволяет стандартным образом определять автоматически реализованные свойства
#define PROPERTY_IMPLEMENTATION(t, x) public: \
  /** Позволяет получить doc @return doc*/ \
  const t Get##x() const \
        { return m_##x; } \
  /** Позволяет установить doc @param value doc */ \
  void Set##x(const t & value) \
        { m_##x = value; } \
  protected: t m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства
#define PROPERTY_IMPLEMENTATION_STRING(x) public: \
  /** Позволяет получить doc @return doc*/ \
  const char * Get##x() const \
  { return m_##x.c_str(); } \
  /** Позволяет установить doc @param value doc */ \
  void Set##x(const char * value) \
  { m_##x = value; } \
  void Set##x(const std::string & value) \
	{ m_##x = value; } \
  protected: std::string m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства
#define POINTER_PROPERTY_IMPLEMENTATION(t, x) public: \
  public: \
  t * Get##x() const\
  { return m_##x; } \
  void Set##x(t * value)\
  { m_##x = value; } \
  protected: t * m_##x; public:

// Позволяет стандартным образом определять автоматически реализованные свойства
#define SMART_POINTER_PROPERTY(t, x) protected: \
  SmartPointer<t> m_##x; \
public: \
  /** Позволяет получить doc @return doc*/ \
  t * Get##x() \
  { return m_##x.Copy(); } \
  /** Позволяет установить doc @param value doc */ \
  void Set##x(t * value) \
  { m_##x = value; }

// Используется для определения в интерфейсах свойств, доступных только для чтения
#define READONLY_PROPERTY_IMPLEMENTATION(t, x) \
  public: \
  /** Позволяет получить doc @return x*/ \
  const t Get##x() const\
  { return m_##x; } \
  protected: t m_##x; \
  public:

// Имплементирует делегацию реализацией свойства
#define PROPERTY_DELEGATION(t, x, object) \
  /** Позволяет получить doc @return doc*/ \
  const t Get##x() const \
  { return object->Get##x(); } \
  /** Позволяет установить doc @param value doc */ \
  void Set##x(const t & value) \
  { object->Set##x(value); }

// Имплементирует делегацию реализацией свойства
#define PROPERTY_DELEGATION_STRING(x, object) \
  /** Позволяет получить doc @return doc*/ \
  const char * Get##x() const \
  { return object->Get##x(); } \
  /** Позволяет установить doc @param value doc */ \
  void Set##x(const char * value) \
  { object->Set##x(value); }

// Имплементирует делегацию реализацией свойства
#define READONLY_PROPERTY_DELEGATION(t, x, object) \
  /** Позволяет получить doc @return doc*/ \
  t Get##x() const \
  { return object->Get##x(); }

