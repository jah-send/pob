
/**
 *  Pobeye and lcd drawing.
 * 
 *
 * @author Baptiste Burles. POB-Technology
 * @version 0.1
 * 
 */

/* import all the pob package for use the pobeye/poblcd functions */
import com.pobtechnology.pobeye.* ;
import com.pobtechnology.poblcd.* ;


public class Example1
{
	
	public static void main( String args[])
	{
		double a = 1.0;

		a = a*2;

		/* lcd init */
		lcd.init();
		
		/* create a new graphic buffer */
		GraphicBuffer gb = new GraphicBuffer(128,64,false);
		
		/* create a new RGB frame */
		RGBFrame.init();
		
		/* clear the graphic buffer */
		gb.clear();

		int k=0,j=0,i=0 ;
	
		/* main loop program */
		while (true==true)
		{
			/* grab the RGB components of the pob-eye camera */
			RGBFrame.grab();
		
			/* binary the RGB frame */
			RGBFrame.binary();

			/* put the pixel from the red component which is binary, to the lcd buffer */
			for (k=0, i=64 ; i != 0 ; i-- )
			{
				for( j=0 ; j<120 ; j++, k++ )
				{
					gb.buffer[k] = (byte)RGBFrame.getRedPixel( i+(j*88) );
				}
				k+=8;
			}

			/* draw the graphic buffer on the screen */
			lcd.draw(gb);
		}
	}
	
}