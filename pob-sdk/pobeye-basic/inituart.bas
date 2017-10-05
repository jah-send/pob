;
; Constant for INIT UART
;
; Example for init uart to 115200:
; UARTInit( B_115200 | DATA_8_BIT | STOP_ONE_BIT | PARITY_NO )
;
Global Const B_230400.w =      0x4000
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
Global Const PARITY_EVEN.w =		0x2000
