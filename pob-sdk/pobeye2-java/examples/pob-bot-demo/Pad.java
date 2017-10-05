// Copyrith POB-Technology, 2006. All rights reserved.

import com.pobtechnology.pobeye.* ;

/**
 * Joystick and cursor management.
 *
 * @author Baptiste Burles & Pierre Séguin POB-Technology
 */
class Pad
{
	/**
	 * x position cursor
	 */
	public static int X;
	/**
	 * y position cursor
	 */
	public static int Y;	


	/**
	 * Init cursor
	 */	
	public static void init()
	{
		Pad.X=100;
		Pad.Y=32;
	}
	
	/**
	 * Get new position of joystick 
	 *
	 * @return true if joystick has moved
	 */
	public static boolean get()
	{
		boolean result=false;	

		int up_down = PobProto.getPortAnalog(UP_DOWN_AXE);
		if ( up_down >200)
		{
			X+=2;
			result=true;
		}
		else if(up_down<50)
		{
			X-=2;
			result=true;
		}
		
		int right_left = PobProto.getPortAnalog(RIGHT_LEFT_AXE);
		if ( right_left > 200)
		{
			Y-=2;
			result=true;
		}
		else if ( right_left < 50 )
		{
			Y+=2;
			result=true;
		}
		
		if( Pad.Y > 60 )
			Pad.Y = 60 ;
		if( Pad.X > 125 )
			Pad.X = 125 ;
		if( Pad.Y < 0 )
			Pad.Y = 0 ;
		if( Pad.X < 0 )
			Pad.X = 0;
			
		return result ;
	}

	/**
	 * Get button pressed 
	 *
	 * @return true if button pressed on joystick
	 */
	public static boolean getButton()
	{
	
		if( PobProto.getPortAnalog(BUTTON)<100)
		{
			return true;
		}
		else
		{		
			return false;
		}
	}
	
	private Pad()
	{
	}
	
	// internal order for get joystick position and button pressed
	private final static int RIGHT_LEFT_AXE	=0;
	private final static int UP_DOWN_AXE	=1;
	private final static int BUTTON	=4;
	
}