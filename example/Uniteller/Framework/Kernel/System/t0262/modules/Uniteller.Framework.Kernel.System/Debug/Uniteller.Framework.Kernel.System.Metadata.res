        ��  ��                  o      �� ��e     0 	        ; ���������� ��������� ����������-���������� �����-����
; ������: 1.0.0
; ���������: 1
; �������� ��������� ����������-���������� �����-���� � �������� �������
<root>: Uniteller\Images
Uniteller.Framework.Kernel.System
  Version : 1.0.0  ; ������
  Generations : {1}     ; �������������� ������� ���������    
  Protocols ; �������������� ������� ���������
    Kernel.System : 1
  Module : Uniteller.Framework.Kernel.System.dll
  Dependencies ; �����������  
    Uniteller.InterchangeFormats.Kernel : 1
    Uniteller.InterchangeFormats.Kernel.System : 1
  Description : ��������� ������ ��� ������ �� �������� 6      �� ��f     0 	        ; ������������� �������� ������ ��������� ������
; Uniteller.Framework.Kernel.System
; Copyright (c) Unitecsys, 2016
;
; ������ ���� ��� ������������ �������������! ��� ������ ��������� ��������� ���������
; �������� ����������. ��� ������������� ��������� ������� ��������� ������ � ����� ��������� ���� ��������� �������������� �������� �� ������
;
; �������� �������� Uniteller.Framework.Kernel.System
;
<root>: Kernel/StateMachines
Uniteller.Framework.Kernel.System
  States                  ; ���������
    Idle
      IsEndState  : False ; ��������� �� �������� ��������
      Transitions : 0     ; �������� (��� ���������� �������)
        Kernel.System.ReplaceAll : Idle
        Kernel.System.Split : Idle
        Kernel.System.TrimLeft : Idle
        Kernel.System.TrimRight : Idle
        Kernel.System.Trim : Idle
        Kernel.System.UnpackFirst : Idle
        Kernel.System.UnpackLast : Idle
        Kernel.System.MatchFormat : Idle
        Kernel.System.GetLength : Idle
  Options                 ; ��������� ������
    StartState : Idle
  