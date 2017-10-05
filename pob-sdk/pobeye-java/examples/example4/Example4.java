
/**
 *  Pob-eye example. This example uses 2 graphic buffer on the lcd. 
 * It draws recognized form and camera frame.
 * 
 *
 * @author Baptiste Burles. POB-Technology
 * 
 */
 
import com.pobtechnology.pobeye.* ;
import com.pobtechnology.poblcd.* ;


public class Example4
{
	static final int BUFFER_WIDTH = 64;
	static final int BUFFER_HEIGHT = 64;
	
	public static void main(String []args)
	{
		int i , j ;
		int tmp ;
		int X_Pic, Y_Pic ;
		GraphicBuffer left ,right ;
		Form list_of_form[];
		
		lcd.init();
		
		RGBFrame.init();
		left = new GraphicBuffer(BUFFER_WIDTH,BUFFER_HEIGHT,false);
		right = new GraphicBuffer(BUFFER_WIDTH,BUFFER_HEIGHT,true);
		
		left.clear();
		right.clear();
		
		while(true==true)
		{
			// Init the x,y of the first picture
			X_Pic=8;
			Y_Pic=8;
			
			// draw a frame in right buffer
			right.draw(0,0,8, "Bitmap" );			
	
			// Grab the RGB components
			RGBFrame.grab();
			
			// Binary the three RGB Buffer
			RGBFrame.binary();
	
			// copy the video buffer on the left Lcd Screen
			for ( i=0 ; i < BUFFER_HEIGHT ; i++)
			{
				for (j=1;j<BUFFER_WIDTH;j++)
				{
					tmp = ((i*480)>>8)*88; // manage Y
					tmp += ((j*352)>>8);   // manage X
					
					if(RGBFrame.getRedPixel(tmp) != 0 )
						left.buffer[i*BUFFER_WIDTH+j]=(byte)0xFF;	
					else 
						left.buffer[i*BUFFER_WIDTH+j]=0;
				}
			}

			// try to identify the forms and make a list of it.
			list_of_form = RGBFrame.identify("Pattern");
			if( list_of_form != null )
			{
				// Parse the list of the form
				for( i=0 ; i < list_of_form.length ; i++ )
				{
					//drawWhatisKnown( list_of_form[i],X_Pic,Y_Pic, left, right);
					
					right.draw(X_Pic, Y_Pic,9, "Bitmap");
					// the picture of what is known in the frame
					right.draw( X_Pic+3, Y_Pic+3, list_of_form[i].id -1, "Bitmap"); 
		
					//manage the (x,y) To draw the next known form on the right lcd screen
					X_Pic += 28;
					if(( X_Pic+28 ) > BUFFER_WIDTH )
					{
						Y_Pic += 26;
						X_Pic = 8;
					}
		
				}
			}

			// Draw the twis LCDs screens
			lcd.drawLeft(left);   //the left for the real time video
			lcd.drawRight(right); //the right for the result
		}
		
		
	}	
	
}

