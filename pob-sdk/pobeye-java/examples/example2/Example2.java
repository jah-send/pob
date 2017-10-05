

/**
 *  Pobeye example.
 * 
 * This example identify form and print result on pob-terminal
 *
 * @author Baptiste Burles. POB-Technology
 * 
 */

/* import the pobeye package for use the RGBFrame and Form class */
import com.pobtechnology.pobeye.* ;
 
public class Example2
{
	
	int id , x , y ;
	
	public static void main( String []args)
	{
		Form form_list[] ;
		
		/* create a new rgb frame */
		RGBFrame.init();
		
		Example2 example = new Example2();
		
		while(true == true )
		{
			/* grab a frame */
			RGBFrame.grab();
			/* binary theis frame */
			RGBFrame.binary();
			
			/* identify form in the frame , the "Pattern" parameter is build by pobjava tools. */
			form_list = RGBFrame.identify("Pattern");
			
			/* ALWAYS VERIFY IF ARRAY FORM IS NOT NULL */
			if( form_list != null )
			{
				System.print( "New form" );
				
				for(int i = 0 ; i < form_list.length ; i++ )
				{
					example.id = form_list[i].id;
					example.x = form_list[i].x ;
					example.y = form_list[i].y ;
					
					System.print( System.toString(example.id) );
					System.print( System.toString(example.x) );
					System.print( System.toString(example.y) );
				}
			}
		}
	}
	
}
