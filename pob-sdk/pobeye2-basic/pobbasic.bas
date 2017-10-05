;
; POB-Basic Function
; 
; POB-Technology, 2006

;;;;;;;;;;;;;;;;;;;  math funcion  ;;;;;;;;;;;;;;;;

; Get Cos/Sin/Tan...
; Syntax :
;        Value.f = Cos( AngleRadian.f )
Declare Cos
Declare Sin
Declare Tan
Declare Acos
Declare Asin
Declare Atan
Declare Sqrt

;;;;;;;;;;;;;;;; Camera frame funcion ;;;;;;;;;;;;;

; Create a new RGB Frame
; Syntax : 
; 	NewRGBFrame()
Declare NewRGBFrame

; Grab a RGB Frame from camera
; Syntax :
;	GrabRGBFrame()
Declare GrabRGBFrame

; Grab only the red component
; Syntax :
;	GrabRedFrame()
Declare GrabRedFrame

; Grab only the green component
; Syntax :
;	GrabGreenFrame()
Declare GrabGreenFrame

; Grab only the blue component
; Syntax :
;	GrabBlueFrame()
Declare GrabBlueFrame

; Send a parameter to the camera (see documentation of camera provides in cdrom)
; Syntax :
; 	SendToCam( address.b , data.b )
Declare SendToCam

; Get a pixel (red, blue or green) from camera
; Syntax :
;	pixel.b = GetRedPixel(indice.l)
Declare GetRedPixel
Declare GetBluePixel
Declare GetGreenPixel

; Set a pixel (red, blue or green) from camera
; Syntax :
;	SetRedPixel( IndexInBuffer.l , Data.b )
Declare SetRedPixel
Declare SetBluePixel
Declare SetGreenPixel

; Binary the RGB frame
; Syntax :
;	BinaryFrame()
Declare BinaryFrame

; Gray the RGB frame
; Syntax :
;	GrayFrame()
Declare GrayFrame

; Return a gray pixel
; Syntax :
; 	pixel.w = GrayPixel( index.l )
Declare GrayPixel

; Form structure
Structure Forms
	id.b     ; id of the form
	x.b      ; center x of the form
	y.b      ; center y of the form
	width.b  ; form's witdth
	height.b ; form's height
EndStructure

; make a list of forms known in a binary picture
; Syntax :
; 	Dim ArrayOfForm.Forms(10)
; 	NbForm.l = Identify( ArrayOfForm )
Declare Identify

; create a new hsl frame
Declare NewHSLFrame

; grab a hsl frame
Declare GrabHSLFrame

; Get a pixel from HSL frame
; Syntax ;
;        pixel.w = GetHuePixel( indice.l)
Declare GetHuePixel
Declare GetSaturationPixel
Declare GetLightPixel


;;;;;;;;;;;;;;;; Graphic buffer funcion ;;;;;;;;;;;;;

Global Const FASTGRAPHIC.b = 1  ; Fast graphic buffer 
Global Const SLOWGRAPHIC.b = 0  ; Slow graphic buffer

; Create a new graphic buffer
; Syntax :
;	GraphicId.l = NewGraphic( Width.b , Height.b , FASTGRAPHIC or SLOWGRAPHIC )
Declare NewGraphic

; Clear a graphic buffer
; Syntax :
;	ClearGraphic( GraphicId.l )
Declare ClearGraphic

; Draw a Bitmap in a graphic buffer
; Syntax :
;	DrawBMP( GraphicId.l , x.b , y.b , BitmapId.b )
Declare DrawBMP

; Get the width (or the heigth) of a bitmap
; Syntax :
;	Width.l = GetBMPWidth( BitmapId.b )
;	Height.l = GetBMPHeight( BitmapId.b )
Declare GetBMPWidth
Declare GetBMPHeight

; Draw a Point in a graphic buffer
; Syntax :
;	DrawAPoint( GraphicId.l, x.b, y.b )
Declare DrawAPoint

; Draw a Line in a graphic buffer
; Syntax :
;	DrawALine( GraphicId.l, x1.b, y1.b, x2.b, y2.b )
Declare DrawALine

; Set a pixel value in a graphic buffer
; Syntax :
;	SetGraphicPixel( GraphicId.l , PixelIndex.l, PixelValue.l )
Declare SetGraphicPixel

; Draw camera frame in a graphic buffer. the graphic buffer must be 64x64 
; Syntax :
;	DrawCameraFrame( GraphicId.l )
Declare DrawCameraFrame

;;;;;;;;;;;;;;;; I2C Bus funcion ;;;;;;;;;;;;;

; Set the speed of the i2c bus
; Syntax :
;	I2CSpeed( speed.l )
Declare I2CSpeed

; Send slave adress through the bus
; Syntax :
;	I2CSetSlaveAddress( address.b )
Declare I2CSetSlaveAddress

; Read a byte from a slave device
; Syntax :
;	Data.b = I2CRead()
Declare I2CRead

; Write a byte on the I2C bus to the slave device
; Syntax :
;	I2CWrite( Data.b )
Declare I2CWrite

; Stop I2C communication
; Syntax :
;	I2CStop()
Declare I2CStop


;;;;;;;;;;;;;;;; IO funcion ;;;;;;;;;;;;;

; Set the way of the general purpose I/O
; Syntax :
;	SetIOWay( Value.l )
Declare SetIOWay

; Get the value of the Input
; Syntax :
;	Value.w = GetInput()
Declare GetInput

; Set the value of an Output
; Syntax :
;	SetOutput( Data.l )
Declare SetOutput

; Clear the output
; Syntax :
; 	ClrOutput( Data.l )
Declare ClrOutput

; Set and clear output
; Syntax :
;	ClrAndSetOuput( Data.l )
Declare ClrAndSetOuput

; Send a byte to a device On the pobeye bus
; Syntax :
;	WriteByte( Address.b , Data.b )
Declare WriteByte

; Read a byte from a device On the pobeye bus
; Syntax :
;	Data.b = ReadByte( Adress.b )
Declare ReadByte


;;;;;;;;;;;;;;;; LCD funcion ;;;;;;;;;;;;;

; Initialize the LCD screen
; Syntax :
;	LCDInit()
Declare LCDInit

; Draw graphic buffer to the LCD screen (128*64 pixels)
; Syntax :
;	LCDDraw( GraphicId.l )
Declare LCDDraw

; Draw the left side of the LCD screen (64*64 pixels)
; Syntax :
;	LCDDrawLeft( GraphicId.l )
Declare LCDDrawLeft

; Draw the right side of the LCD screen (64*64 pixels)
; Syntax :
;	LCDDrawRight( GraphicId.l )
Declare LCDDrawRight


;;;;;;;;;;;;;;;; UART funcion ;;;;;;;;;;;;;

; Init the UART
; Syntax :
;	UARTInit( Baudrate.w )
; With Baudrate between 15200, 57600, 38400, 19200, 9600
Declare UARTInit

; Send a byte with the UART
; Syntax :
;	UARTSend( Data.b )
Declare UARTSend

; Send a byte's array through the UART
; Syntax :
;	Dim Buffer.b(16)
;	UARTSendBuffer( Buffer , 16 )
Declare UARTSendBuffer

; Get a byte from the UART
; Syntax :
;   Dim aByte.b(1)
;	isByteOk.b = UARTGet(aByte)
Declare UARTGet

; Get an array of bytes from the UART
; Syntax :
;	Dim Buffer.b(8)
;	UARTGetBuffer( Buffer, 8 )
Declare UARTGetBuffer

;;;;;;;;;;;;;;;; UART1 Function ;;;;;;;;;;;;;;;;

Declare UART1Init
Declare UART1Send
Declare UART1SendBuffer
Declare UART1Get
Declare UART1GetBuffer

;;;;;;;;;;;;;;;; POB-Terminal funcion ;;;;;;;;;;;;;

; Print text on POB Terminal
; Syntax :
;	Str.s = "Hello World"
;	PrintText( Str )
Declare PrintText

; Wait
; Syntax :
;	Wait( MilliSeconds.l )
Declare Wait


;;;;;;;;;;;;;;;; POB-Proto funcion ;;;;;;;;;;;;;

Global Const DIGITALINPUT.l = 0x00001   ; Digital Input
Global Const DIGITALOUTPUT.l = 0x00000  ; Digital Output
Global Const ASSERVO.l = 0x0100         ; ServoMotor

; Configure a pin of PORTA (or PORTD or PORTC)
; PORTD : Set only as DIGITALASINPUT or DIGITALASOUTPUT
; PORTC : Set only as DIGITALASINPUT, DIGITALASOUTPUT or ASSERVO
; WARNING : DO NOT SET THE 4 AND 5 PINS OF PORTC
; Syntax :
;	ConfigPortA( PinNumber.l , Value.l )
Declare ConfigPortA
Declare ConfigPortD
Declare ConfigPortC

; Configure all the pin of PORTA as analogic
; Syntax :
;	ConfigPortAnalogic()
Declare ConfigPortAnalogic

; Write the current configuration of PortA,PortC and PortD on the pob-proto board
; Syntax :
;	SetConfigPobProto()
Declare SetConfigPobProto
Declare SetConfigTinyPobProto

; Set value of PORTA,PORTD or PORTC
; Syntax :
;	SetPortA( Data.b )
Declare SetPortA
Declare SetPortD
Declare SetPortC

; Set value of PORTA,PORTD or PORTC pin
; Syntax :
;        SetPinPortA( Pin.l )
Declare SetPinPortA
Declare SetPinPortD
Declare SetPinPortC

; Clear value of PORTA,PORTD or PORTC pin
; Syntax :
;        ClearPinPortA( Pin.l )
Declare ClearPinPortA
Declare ClearPinPortD
Declare ClearPinPortC

; Get analogic value from a PORTA pin 
; Syntax :
;	Data.b = GetPortAnalog( PinNumber.l )
Declare GetPortAnalog

; Get value from PORTA,PORTD or PORTC
; Syntax :
;	Data.b = GetPortA()
Declare GetPortA
Declare GetPortD
Declare GetPortC

; Get value from PORTA,PORTD or PORTC pin
; Syntax :
;        Data.b = GetPinPortA( Pin.l )
Declare GetPinPortA
Declare GetPinPortD
Declare GetPinPortC

; Set position of a servomotor
; Syntax :
;	SetServoMotor( ServoMotorNumber.b , Position.b )
Declare SetServoMotor

; Switch off/On all the servomotor
; Syntax :
;	SwitchOffAll() or SwitchOnAll()
Declare SwitchOffAll
Declare SwitchOnAll

; Switch off/On a servomotor
; Syntax :
;	SwitchOff( ServoMotorNumber.b ) or SwitchOn( ServoMotorNumber.b )
Declare SwitchOff
Declare SwitchOn


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

; Send order to robot sapien
; Syntax :
; 	SendToSapien( Order.b )
Declare SendToSapien




