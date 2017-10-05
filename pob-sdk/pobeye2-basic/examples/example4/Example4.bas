; Example4
; Identify form, Draw form and camera frame

Procedure ProcedureMain()

; Array to store the form
Dim form.Forms(10)

LCDInit()
NewRGBFrame()

; Create 2 graphic buffer : the Left For the camera frame, the Right For display recognized form
Left.l = NewGraphic( 64 ,64 ,FASTGRAPHIC )
Right.l = NewGraphic(64,64, SLOWGRAPHIC)

ClearGraphic(Left)
ClearGraphic(Right)

While 0 = 0
	
	; Get camera frame and binary it
	GrabRGBFrame()
	BinaryFrame()

	XPic.l=8
	YPic.l=8
	
	DrawBMP(Right,0,0,8 );
	
	; Draw current camera frame in the Left graphic buffer
	DrawCameraFrame( Left )
	
	; Identify form in the current camera frame
	nbform.l = Identify( form )
	
	For i.l = 0 To nbform 
		
		DrawBMP(Right,XPic, YPic,9);
		
		; to Get menber of Array : form(i) Get the form at index i, form(i)\id Get the ID of the form at index i
		DrawBMP(Right,XPic+3, YPic+3, form(i)\id -1 )
		
		XPic = XPic + 28 
		If (XPic+28) > 64
			YPic += 26
			XPic = 8
		EndIf
	Next
	
	; Draw On the LCD the 2 graphic buffer
	LCDDrawRight( Right )
	LCDDrawLeft( Left )
	
	
Wend

EndProcedure