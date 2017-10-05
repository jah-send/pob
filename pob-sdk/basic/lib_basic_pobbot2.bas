Structure Forms
	id.b
	x.b
	y.b
	width.b
	height.b
EndStructure


Global Const FASTGRAPHIC.b = 1
Global Const SLOWGRAPHIC.b = 0

Global Const DIGITALINPUT.l = 0x00001   ; Digital Input
Global Const DIGITALOUTPUT.l = 0x00000  ; Digital Output
Global Const ASSERVO.l = 0x0100         ; ServoMotor

;
; Robot sapien orders
;
Global Const SAPIENWALKFORWARD.l  = 0x86
Global Const SAPIENWALKBACKWARD.l = 0x87
Global Const SAPIENWALKSTOP.l     = 0x8E
Global Const SAPIENTURNRIGHT.l    = 0x80
Global Const SAPIENTURNLEFT.l     = 0x88
Global Const SAPIENRIGHTARMUP.l  = 0x81
Global Const SAPIENRIGHTARMDOWN.l= 0x84
Global Const SAPIENRIGHTARMOUT.l = 0x82
Global Const SAPIENRIGHTARMIN.l  = 0x85
Global Const SAPIENLEFTARMUP.l   = 0x89
Global Const SAPIENLEFTARMDOWN.l = 0x8C
Global Const SAPIENLEFTARMOUT.l  = 0x8A
Global Const SAPIENLEFTARMIN.l   = 0x8D
Global Const SAPIENTILTBODYLEFT.l= 0x8B
Global Const SAPIENTILTBODYRIGHT.l=0x83



;
; Constant for INIT UART
;
; Example for init uart to 115200:
; UARTInit( B_115200 | DATA_8_BIT | STOP_ONE_BIT | PARITY_NO )
;
Global Const B_230400.w =      	0x4000
Global Const B_115200.w =		0x1
Global Const B_57600.w =		0x2
Global Const B_38400.w =		0x4
Global Const B_19200.w =		0x8
Global Const B_9600.w =			0x10
Global Const B_4800.w =			0x8000


Global Const DATA_5_BIT.w =	0x20	
Global Const DATA_6_BIT.w =	0x40
Global Const DATA_7_BIT.w =	0x80
Global Const DATA_8_BIT.w =	0x100	

Global Const STOP_ONE_BIT.w =	0x200
Global Const STOP_TWO_BIT.w =	0x400

Global Const PARITY_NO.w =		0x800
Global Const PARITY_ODD.w =		0x1000
Global Const PARITY_EVEN.w =	0x2000

