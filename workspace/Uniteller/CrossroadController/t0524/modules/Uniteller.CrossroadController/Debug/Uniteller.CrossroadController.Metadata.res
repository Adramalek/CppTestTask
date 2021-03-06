        ��  ��                  �      �� ��e     0 	        ; ���������� ��������� ����������-���������� �����-����
; ������: 1.0.0
; ���������: 1
; �������� ��������� ����������-���������� �����-���� � �������� �������
<root>: Uniteller\Images
Uniteller.CrossroadController
  Version : 1.0.0  ; ������
  Generations : {1}     ; �������������� ������� ���������    
  Module : Uniteller.CrossroadController.dll
  Protocols ; �������������� ������� ���������
    CrossroadController : 1
  Dependencies ; �����������  
    Uniteller.InterchangeFormats.Kernel : 1
    Uniteller.InterchangeFormats.DeviceController : 1
    Uniteller.InterchangeFormats.MainLogic : 1
    Uniteller.InterchangeFormats.CrossroadController : 1
  Description:
    ������ ���������� ����� ������������ ������� ���������
 �      �� ��f     0 	        ; ������������� �������� ������ ��������� ������
; Uniteller.CrossroadController
; Copyright (c) Unitecsys, 2018
;
; ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
; �������� ����������. ��� ������������� ��������� ������� ��������� ������ � ����� ��������� ���� ��������� �������������� �������� �� ������
;
; �������� �������� Uniteller.CrossroadController
;
<root>: Kernel/StateMachines
Uniteller.CrossroadController
  States                  ; ���������
    StartState
      IsEndState  : False ; ��������� �� �������� ��������
      Transitions : 1     ; �������� (� ����������� �������)
        Kernel.Start : Pause
        Kernel.Stop : End
    End
      IsEndState  : True  ; ��������� �������� ��������
      Transitions : 0     ; �������� (��� ���������� �������)
    Pause
      IsEndState  : False ; ��������� �� �������� ��������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.Stop : End
        MainLogic.Shutdown : End
        MainLogic.Start : Pause
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            CrossroadController.SetNextLight
        CrossroadController.SetNextLight : LightTurningOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
    RedLight
      IsEndState  : False ; ��������� �� �������� ��������
      TimeOut     : 30000 ; ������������ �������� ���������� � ������ ���������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.TimeOut : RedLight
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            CrossroadController.SetNextLight
        CrossroadController.SetNextLight : LightTurningOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
        Kernel.Stop : End
    YellowLight
      IsEndState  : False ; ��������� �� �������� ��������
      TimeOut     : 5000 ; ������������ �������� ���������� � ������ ���������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.TimeOut : YellowLight
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            CrossroadController.SetNextLight
        CrossroadController.SetNextLight : LightTurningOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
        Kernel.Stop : End
    GreenLight
      IsEndState  : False ; ��������� �� �������� ��������
      TimeOut     : 40000 ; ������������ �������� ���������� � ������ ���������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.TimeOut : GreenLight
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            CrossroadController.SetNextLight
        CrossroadController.SetNextLight : LightTurningOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
        Kernel.Stop : End
    LightTurningOn
      IsEndState  : False ; ��������� �� �������� ��������
      TimeOut     : 100 ; ������������ �������� ���������� � ������ ���������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.TimeOut : Pause
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            MainLogic.ProblemDetected
        DeviceController.Fail : Pause
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            MainLogic.ProblemDetected
        DeviceController.Success : LightTurningOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            CrossroadController.CountDownRed
            CrossroadController.CountDownYellow
            CrossroadController.CountDownGreen
        Kernel.Stop : End
        CrossroadController.CountDownRed : RedLight
        CrossroadController.CountDownYellow : YellowLight
        CrossroadController.CountDownGreen : GreenLight
  Options                 ; ��������� ������
    StartState : StartState
 