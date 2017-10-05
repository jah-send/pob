// Copyrith POB-Technology, 2006. All rights reserved.

import com.pobtechnology.pobeye.* ;
import com.pobtechnology.poblcd.* ;

/**
 * Demonstration program
 *
 * @author Baptiste Burles & Pierre Séguin POB-Technology
 */
class Main
{

	/**
	 * Draw introduction screen.
	 * animation is make with methods draw and System.wait
	 *
	 *  @param LCD_Buffer_Video : Graphic buffer
	 */
	static void IntroPOB(GraphicBuffer LCD_Buffer_Video)
	{
		LCD_Buffer_Video.clear();
			
		
		LCD_Buffer_Video.draw(20,5,Bitmap.POB_BMP,"Bitmap" );
		
		lcd.draw(LCD_Buffer_Video);

		System.wait(1000);
		
		LCD_Buffer_Video.draw(20,47,Bitmap.TECHNO_BMP,"Bitmap");	
		
		lcd.draw(LCD_Buffer_Video);	
	
		System.wait(2000);
		
		LCD_Buffer_Video.clear();
		LCD_Buffer_Video.draw(8,5,Bitmap.POB_BMP,"Bitmap" );		
		LCD_Buffer_Video.draw(8,47,Bitmap.TECHNO_BMP,"Bitmap");	
		lcd.draw(LCD_Buffer_Video);	
	
		System.wait(2000);
		
		LCD_Buffer_Video.draw(93,10,Bitmap.POBJAVA_BMP,"Bitmap");	
		
		lcd.draw(LCD_Buffer_Video);	
	
		System.wait(1000);	
	}
	
	// Static variable for store the icon id
	static int OnIcone;
	
	/**
	 * Main method
	 */
	public static void main(String []args)
	{
		GraphicBuffer LCD_Buffer_Video, LCD_Fast_Buffer_Video;
		
		// Create 2 graphics buffer
		LCD_Buffer_Video = new GraphicBuffer(128,64,true);
		LCD_Fast_Buffer_Video = new GraphicBuffer(64,64,false);
		
		// lcd init
		lcd.init();
		
		// draw animation
		IntroPOB(LCD_Buffer_Video);
		
		// pob-proto board init
		Bot.init();
		
		Bot.setHead(135);
		
		// joystick init
		Pad.init();
		
		PobProto.setServoMotor(0,128);
		PobProto.setServoMotor(1,128);
		PobProto.setServoMotor(2,128);
		PobProto.setServoMotor(3,128);
		PobProto.setServoMotor(6,128);
		PobProto.setServoMotor(7,128);
		
		// create the icons array
		Icone icons[] = new Icone[3];
		Icone yourtest[] = new Icone[18] ;
		
		System.print("begin main loop");
		
		// init, draw and manage the main menu
		MenuMain.init( icons, LCD_Buffer_Video );
		MenuMain.draw( icons, LCD_Buffer_Video );
		
		YourTest.init(yourtest,LCD_Buffer_Video);
		
		MenuMain.manage( icons,yourtest, LCD_Buffer_Video, LCD_Fast_Buffer_Video );
		
		// main loop
		while(true)
		{
			if( Pad.get() ) // if jostick move, then : 
			{
				// draw main menu
				MenuMain.draw(icons,LCD_Buffer_Video);
				// and verify the position of cursor on a icon
				OnIcone = isOnIcon(icons);
			}
			
			// manage the action
			MenuMain.manage( icons, yourtest,LCD_Buffer_Video,LCD_Fast_Buffer_Video );
		}
	}
	
	/**
	 * Detect position of cursor on icon
	 *
	 * @param TabOfIcon : Array of icons
	 */
	public static int isOnIcon(Icone TabOfIcone[])
	{
		int i,w=0,h=0;
	
		for( i=0 ; i < TabOfIcone.length  ; i++ )
		{		
			w=TabOfIcone[i].X + TabOfIcone[i].W;
			h=TabOfIcone[i].Y + TabOfIcone[i].H;
			
			if( Pad.X > TabOfIcone[i].X && Pad.X < w && Pad.Y > TabOfIcone[i].Y && Pad.Y < h )
			{
				return TabOfIcone[i].Id;
			}
		}
		
		return 0;
	}
	
	/**
	 * Draw camera frame on a graphic buffer and lcd
	 *
	 * @param fast : A fast graphic buffer (64x64 pixels)
	 */
	public static void drawCameraFrame(GraphicBuffer fast)
	{
		int i=0,j=0;
		int tmp=0;
	
		for ( i=0 ; i < 64 ; i++)
		{
			for (j=1;j<64;j++)
			{
				tmp = ((i*480)>>8)*160; // manage Y
				tmp += ((j*640)>>8);   // manage X
					
				if(RGBFrame.getRedPixel(tmp) != 0 )
					fast.buffer[i*64+j]=(byte)0xFF;	
				else 
					fast.buffer[i*64+j]=0;
			}
		}
		
		lcd.drawLeft(fast);
	}
	
}