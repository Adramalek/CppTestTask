// Uniteller.Framework.Kernel.System.cpp : Defines the exported functions for the DLL application.
//
#ifndef __GNUG__
#include "resource.h"
#include "stdafx.h"
#endif
#include "kernel/kernel.h"
#include "kernel/metadatasource.h"
#include "kernel/moduleexport.h"
#include "machine.h"

using namespace Uniteller::Framework::Kernel;

#ifdef __GNUG__
IMPLEMENT_VENDOR_DATASOURCE() 
#else
BEGIN_VENDOR_DATASOURCE()
  VENDOR_DATASOURCE(IDR_METADATA)
  VENDOR_DATASOURCE(IDR_STATEMACHINE)
END_VENDOR_DATASOURCE()
#endif

EXPORT_SYSTEM_OBJECT(Uniteller::Framework::Kernel::System::Machine);

