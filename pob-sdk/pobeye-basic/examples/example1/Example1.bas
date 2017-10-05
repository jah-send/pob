; Example 1
; Draw frame camera On the LCD screen

Procedure ProcedureMain()

	; init the LCD
	LCDInit()
		
	; create a new graphic buffer
	GraphicId.l = NewGraphic( 128,64, FASTGRAPHIC )
	
	; create a new camera frame
	NewRGBFrame()
		
	; Clear the graphic buffer
	ClearGraphic( GraphicId)
	
	
	While 0=0
		; grab a camera frame and binary the frame
		GrabRGBFrame()
		BinaryFrame()
		
		k.l = 0
		For i.l = 0 To 64

			For j.l = 0 To 120 
				; Get frame pixel
				pixel.b = GetRedPixel( i+(j*88) )
				; and Set pixel of the graphic buffer
				SetGraphicPixel( GraphicId , k , pixel )
				k = k +1
			Next	
			k+=8;
		Next
		
		; Draw the graphic buffer in the LCD
		LCDDraw(GraphicId)
	Wend

EndProcedure