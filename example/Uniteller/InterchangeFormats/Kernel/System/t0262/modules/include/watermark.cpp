// Водяной знак компонента Uniteller.InterchangeFormats.Kernel.System
// Данный файл запрещается исправлять вручную

#ifndef __GNUG__
#include "stdafx.h"
#endif

#include "kernel/autoproperty.h"

// Водяной знак, прошиваемый в бинарники

const char * g_Uniteller_InterchangeFormats_Kernel_System_Watermark = "[WM] Uniteller.InterchangeFormats.Kernel.System version: t0262 generation: 1 revision: 29334 Release 2017.03.28 16:27:45";

// Чтобы водяной знак не вырезался в Release-компиляции, а также, чтобы была возможность быстро опознать DLL
KERNEL_EXPORT const char * Uniteller_InterchangeFormats_Kernel_System_Watermark()
{
  return g_Uniteller_InterchangeFormats_Kernel_System_Watermark;
}

