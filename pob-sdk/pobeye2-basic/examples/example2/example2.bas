; Example2
; Draw bitmap, Line and Point in a graphic buffer and Draw it On LCD Screen

Procedure ProcedureMain()

	; Init the LCD screen
	LCDInit()

	; create a new graphic buffer
	GraphicId.l = NewGraphic( 128, 64, FASTGRAPHIC)

	ClearGraphic(GraphicId)

	; Draw at x=30, y=10 the bitmap 0
	DrawBMP(GraphicId,30,10,0)
	
	DrawBMP(GraphicId,45,10,1)
	DrawBMP(GraphicId,65,10,2)

	; Draw at x=10, y=10 to x=25, y =30 a Line
	DrawALine(GraphicId,10,10,25,30)
	
	; Draw at x=20, y=10 a Point
	DrawAPoint(GraphicId,20,10);

	; Draw the graphic buffer On the LCD screen
	LCDDraw(GraphicId)

EndProcedure