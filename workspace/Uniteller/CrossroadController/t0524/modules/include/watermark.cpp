// ������� ���� ���������� Uniteller.CrossroadController
// ������ ���� ����������� ���������� �������

#include "stdafx.h"

// ������� ����, ����������� � ���������
const char * g_Uniteller_CrossroadController_Watermark = "[WM] Uniteller.CrossroadController version: 1.0.0 generation: 1 revision: 641 Release 20.01.2014 9:46:21";

// ����� ������� ���� �� ��������� � Release-����������, � �����, ����� ���� ����������� ������ �������� DLL
__declspec(dllexport) const char * Uniteller_CrossroadController_Watermark()
{
  return g_Uniteller_CrossroadController_Watermark;
}