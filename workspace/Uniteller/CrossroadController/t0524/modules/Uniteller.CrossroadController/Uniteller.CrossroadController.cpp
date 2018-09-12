// Uniteller.CrossroadController.cpp : Defines the exported functions for the DLL application.
//

#include "resource.h"
#include "stdafx.h"
#include "kernel/kernel.h"
#include "kernel/metadatasource.h"
#include "kernel/moduleexport.h"
#include "machine.h"

using namespace Uniteller::Framework::Kernel;

BEGIN_VENDOR_DATASOURCE()
  VENDOR_DATASOURCE(IDR_METADATA)
  VENDOR_DATASOURCE(IDR_STATEMACHINE)
END_VENDOR_DATASOURCE()

EXPORT_SYSTEM_OBJECT(Uniteller::CrossroadController::Machine);

