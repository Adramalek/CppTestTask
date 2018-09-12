// Водяной знак компонента Uniteller.CrossroadController
// Данный файл запрещается исправлять вручную

#include "stdafx.h"

// Водяной знак, прошиваемый в бинарники
const char * g_Uniteller_CrossroadController_Watermark = "[WM] Uniteller.CrossroadController version: 1.0.0 generation: 1 revision: 641 Release 20.01.2014 9:46:21";

// Чтобы водяной знак не вырезался в Release-компиляции, а также, чтобы была возможность быстро опознать DLL
__declspec(dllexport) const char * Uniteller_CrossroadController_Watermark()
{
  return g_Uniteller_CrossroadController_Watermark;
}