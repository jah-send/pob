// Copyrith POB-Technology, 2006. All rights reserved.

import com.pobtechnology.pobeye.* ;
import com.pobtechnology.poblcd.* ;

/**
 * Test menu class. Allow test motor and servo on the pob proto board
 *
 */
public class YourTest
{
	final static int X_SERVO = 15;
	final static int Y_SERVO = 5;

	final static int X_ENGINE = 30 ;
	final static int Y_ENGINE = 32;

	public static void init(Icone TabOfIcone[], GraphicBuffer gb)
	{
		int i ;
		for (i=0;i<12;i+=2)		//this loop creats the +/- icons to manage the 6 servomotors
		{	
			TabOfIcone[i].X=X_SERVO+13*(i/2);
			TabOfIcone[i].Y=Y_SERVO;
			TabOfIcone[i].Id=Bitmap.MORE_BMP;
			TabOfIcone[i].W=gb.getWidth(TabOfIcone[i].Id,"Bitmap");
			TabOfIcone[i].H=gb.getHeight(TabOfIcone[i].Id,"Bitmap");
	
	
			TabOfIcone[i+1].X=X_SERVO+13*(i/2);
			TabOfIcone[i+1].Y=Y_SERVO+TabOfIcone[i].H;
			TabOfIcone[i+1].Id=Bitmap.LESS_BMP;
			TabOfIcone[i+1].W=gb.getWidth(TabOfIcone[i+1].Id,"Bitmap");
			TabOfIcone[i+1].H=gb.getHeight(TabOfIcone[i+1].Id,"Bitmap");
		}

		//icon to manage the back icon, to exit from this menu
		TabOfIcone[12].X=95;
		TabOfIcone[12].Y=32;
		TabOfIcone[12].Id=Bitmap.BACK_BMP;
		TabOfIcone[12].W=gb.getWidth(TabOfIcone[12].Id,"Bitmap");
		TabOfIcone[12].H=gb.getWidth(TabOfIcone[12].Id,"Bitmap");

		//icon to gear the left forward wheel
		TabOfIcone[13].X=X_ENGINE;
		TabOfIcone[13].Y=Y_ENGINE;
		TabOfIcone[13].Id=Bitmap.UP_BMP;
		TabOfIcone[13].W=gb.getWidth(TabOfIcone[13].Id,"Bitmap");
		TabOfIcone[13].H=gb.getHeight(TabOfIcone[13].Id,"Bitmap");

		//icon to gear the left back wheel
		TabOfIcone[14].X=X_ENGINE;
		TabOfIcone[14].Y=Y_ENGINE+gb.getHeight(Bitmap.MOTOR_BMP,"Bitmap")-gb.getHeight(Bitmap.DOWN_BMP,"Bitmap");
		TabOfIcone[14].Id=Bitmap.DOWN_BMP;
		TabOfIcone[14].W=gb.getWidth(TabOfIcone[14].Id,"Bitmap");
		TabOfIcone[14].H=gb.getHeight(TabOfIcone[14].Id,"Bitmap");
	
		//icon to gear the right forward wheel
		TabOfIcone[15].X=X_ENGINE+gb.getWidth(Bitmap.MOTOR_BMP,"Bitmap")-gb.getWidth(Bitmap.UP_BMP,"Bitmap");;
		TabOfIcone[15].Y=Y_ENGINE;
		TabOfIcone[15].Id=Bitmap.UP_BMP;
		TabOfIcone[15].W=gb.getWidth(TabOfIcone[15].Id,"Bitmap");
		TabOfIcone[15].H=gb.getHeight(TabOfIcone[15].Id,"Bitmap");
	
		//icon to gear the right back wheel
		TabOfIcone[16].X=X_ENGINE+gb.getWidth(Bitmap.MOTOR_BMP,"Bitmap")-gb.getWidth(Bitmap.UP_BMP,"Bitmap");
		TabOfIcone[16].Y=Y_ENGINE+gb.getHeight(Bitmap.MOTOR_BMP,"Bitmap")-gb.getHeight(Bitmap.DOWN_BMP,"Bitmap");
		TabOfIcone[16].Id=Bitmap.DOWN_BMP;
		TabOfIcone[16].W=gb.getWidth(TabOfIcone[16].Id,"Bitmap");
		TabOfIcone[16].H=gb.getHeight(TabOfIcone[16].Id,"Bitmap");
			
		//icon to draw the to DC motor
		TabOfIcone[17].X=X_ENGINE;
		TabOfIcone[17].Y=Y_ENGINE;
		TabOfIcone[17].Id=Bitmap.MOTOR_BMP;
		TabOfIcone[17].W=gb.getWidth(TabOfIcone[17].Id,"Bitmap");
		TabOfIcone[17].H=gb.getHeight(TabOfIcone[17].Id,"Bitmap");
	}
	
	public static void draw(Icone TabOfIcone[], GraphicBuffer gb )
	{
		int i=0;
		
		gb.clear();
		
		// icons of menu
		for (i=0 ; i < 18 ; i++)
		{
			gb.draw(TabOfIcone[i].X,TabOfIcone[i].Y,TabOfIcone[i].Id,"Bitmap");
		}
		
		// cursor
		gb.draw(Pad.X,Pad.Y,Bitmap.ARROW_BMP,"Bitmap");
		
		// at the end, graphic buffer draw on lcd
		lcd.draw(gb);
	}
	
	public static void manage(Icone TabOfIcons[], GraphicBuffer gb)
	{
		boolean out = false ;
		int WhichIcon ;
		int ServPos[] =new int[6];
		int motor ;
		int i ;
		
		for(i=0 ; i < 6 ; i++ )
			ServPos[i] = 128 ;
		
		//set servo position	
		PobProto.setServoMotor(0,128);
		PobProto.setServoMotor(1,128);
		PobProto.setServoMotor(2,128);
		PobProto.setServoMotor(3,128);
		PobProto.setServoMotor(6,128);
		PobProto.setServoMotor(7,128);
		
		do 
		{
			if( Pad.get() == true ) //if cursor move, redraw menu
				draw(TabOfIcons,gb);
			
			if( Pad.getButton() == true )//if pad press, then manage position of cursor and action
			{
				WhichIcon = isOnIcon(TabOfIcons);
				if( WhichIcon != -1 )
				{
					//if cursor is on less or up icons, then move the correct servomotor
					if( WhichIcon >= 0 && WhichIcon <= 11 )
					{
						motor = WhichIcon/2  ;
						if( (WhichIcon % 2) == 0 )
							ServPos[motor] +=4 ;
						else
							ServPos[motor] -=4;
						
						if( motor>=0 && motor<=3 )
							PobProto.setServoMotor(motor,ServPos[motor]);
						else 
							PobProto.setServoMotor(motor+2,ServPos[motor]);
					}
					//else, move the dc motor connected on the pob-proto board
					else if( WhichIcon == 13 )
					{
						Bot.move((byte)0x04);
						System.wait(100000);
						while(Pad.getButton()==true);
						Bot.move((byte)0);
					}
					else if(WhichIcon == 14)
					{
						Bot.move((byte)0x08);
						System.wait(100000);
						while(Pad.getButton()==true);
						Bot.move((byte)0);
					}
					else if(WhichIcon == 15)
					{
						Bot.move((byte)0x01);
						System.wait(100000);
						while(Pad.getButton()==true);
						Bot.move((byte)0);
					}
					else if(WhichIcon == 16)
					{
						Bot.move((byte)0x02);
						System.wait(100000);
						while(Pad.getButton()==true);
						Bot.move((byte)0);
					}
					//else, if cursor is on back icon, then exit
					else if(WhichIcon == 12)
						out=true;
				}
				
			}
				
		}while( out != true );
		
		while(Pad.getButton()==true);
	}
	
	//manage cursor position on icon
	private static int isOnIcon(Icone TabOfIcone[])
	{
		int i,w=0,h=0;
	
		for( i=0 ; i < TabOfIcone.length  ; i++ )
		{		
			w=TabOfIcone[i].X + TabOfIcone[i].W;
			h=TabOfIcone[i].Y + TabOfIcone[i].H;
			
			if( Pad.X > TabOfIcone[i].X && Pad.X < w && Pad.Y > TabOfIcone[i].Y && Pad.Y < h )
			{
				return i;
			}
		}
		
		return -1;
	}
}