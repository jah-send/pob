

/**
 *  Poblcd example.
 * 
 *
 * @author Baptiste Burles. POB-Technology
 * 
 */

/* import the lcd package for use the graphic buffer and lcd class */
import com.pobtechnology.poblcd.* ;

public class Example3
{
	
	public static void main(String []args)
	{
		/* init the pob-lcd */
		lcd.init();
		
		/* create a new graphic buffer of 128 x 64 pixel */
		GraphicBuffer gb = new GraphicBuffer(128,64,true);

		/* clear the graphic buffer */
		gb.clear();
		
		/* draw picture */
		gb.draw(30,10,0, "Bitmap");
		gb.draw(45,10,1, "Bitmap");
		gb.draw(65,10,2, "Bitmap");
		
		/* draw a line */
		gb.drawLine(10,10,25,30);
		
		/* draw a plot */
		gb.plotAPoint(20,10);
		
		/* draw the graphic buffer on the pob-lcd */
		lcd.draw(gb);
		
	}
}
