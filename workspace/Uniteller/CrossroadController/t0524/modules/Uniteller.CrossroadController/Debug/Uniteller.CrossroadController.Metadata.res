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
 �	      �� ��f     0 	        ; ������������� �������� ������ ��������� ������
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
        MainLogic.Start : TurningLightOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
        MainLogic.Shutdown : End
    TurningLightOn
      IsEndState  : False ; ��������� �� �������� ��������
      TimeOut     : 100 ; ������������ �������� ���������� � ������ ���������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.TimeOut : Pause
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            MainLogic.ProblemDetected
        DeviceController.Success : LightTurnedOn
        Kernel.Stop : End
        Kernel.Stop : End
        MainLogic.Shutdown : End
        MainLogic.Shutdown : End
        DeviceController.Fail : Pause
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            MainLogic.ProblemDetected
    LightTurnedOn
      IsEndState  : False ; ��������� �� �������� ��������
      Transitions : 0     ; �������� (��� ���������� �������)
        CrossroadController.SetNextLight : TurningLightOn
          CanRaise : 1    ; ������������ �������, ������� ����� ���� ������������� ������� � ������ ��������
            DeviceController.SetLight
        Kernel.Stop : End
        MainLogic.Shutdown : End
  Options                 ; ��������� ������
    StartState : StartState
 