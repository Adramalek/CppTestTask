// ������� ���� ���������� Uniteller.Framework.Kernel.System
// ������ ���� ����������� ���������� �������

#ifndef __GNUG__
#include "stdafx.h"
#endif

#include "kernel/autoproperty.h"

// ������� ����, ����������� � ���������

const char * g_Uniteller_Framework_Kernel_System_Watermark = "[WM] Uniteller.Framework.Kernel.System version: t0262 generation: 1 revision: 29334 Release 2017.03.28 16:27:58";

// ����� ������� ���� �� ��������� � Release-����������, � �����, ����� ���� ����������� ������ �������� DLL
KERNEL_EXPORT const char * Uniteller_Framework_Kernel_System_Watermark()
{
  return g_Uniteller_Framework_Kernel_System_Watermark;
}

