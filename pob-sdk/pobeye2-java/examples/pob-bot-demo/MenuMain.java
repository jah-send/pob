// Copyrith POB-Technology, 2006. All rights reserved.


import com.pobtechnology.pobeye.* ;
import com.pobtechnology.poblcd.* ;

/**
 * Main menu class
 *
 * @author Baptiste Burles & Pierre Séguin POB-Technology
 */
class MenuMain
{
	
	/**
	 * Draw icons on a graphic buffer
	 *
	 * @param TabOfIcone : array of icons
	 * @param gb         : graphic buffer
	 */
	public static void draw(Icone TabOfIcone[], GraphicBuffer gb )
	{
		int i=0;
		
		gb.clear();
		
		// title of menu is draw
		gb.draw(0,0,Bitmap.POBBOT_BMP,"Bitmap");
	
		// icons of menu
		for (i=0 ; i < 3 ; i++)
		{
			gb.draw(TabOfIcone[i].X,TabOfIcone[i].Y,TabOfIcone[i].Id,"Bitmap");
		}
		
		// cursor
		gb.draw(Pad.X,Pad.Y,Bitmap.ARROW_BMP,"Bitmap");
		
		// at the end, graphic buffer draw on lcd
		lcd.draw(gb);
	}
	
	/**
	 * main menu init
	 *
	 * @param TabOfIcone : array of icons
	 * @param gb         : graphic buffer
	 */
	public static void init(Icone TabOfIcone[], GraphicBuffer gb)
	{	
		// all icons are stored :
		// X Y position, identity of bitmap
		// and width/height of bitmap
		
		TabOfIcone[0].X=10;
		TabOfIcone[0].Y=20;
		// identity is created by pob-java in pob-bitmap. 
		// Clic on 'Create bitmap file' for create the identity file
		TabOfIcone[0].Id=Bitmap.FINDANDFOLLOW_BMP ; 
		TabOfIcone[0].W=gb.getWidth(TabOfIcone[0].Id,"Bitmap");
		TabOfIcone[0].H=gb.getHeight(TabOfIcone[0].Id,"Bitmap");
	
		TabOfIcone[1].X=52;
		TabOfIcone[1].Y=20;
		TabOfIcone[1].Id=Bitmap.FINDANDMOVEHEAD_BMP ; 
		TabOfIcone[1].W=gb.getWidth(TabOfIcone[1].Id,"Bitmap");
		TabOfIcone[1].H=gb.getHeight(TabOfIcone[1].Id,"Bitmap");
		
		TabOfIcone[2].X=90;
		TabOfIcone[2].Y=22;
		TabOfIcone[2].Id=Bitmap.YOURTEST_BMP; 
		TabOfIcone[2].W=gb.getWidth(TabOfIcone[2].Id,"Bitmap");
		TabOfIcone[2].H=gb.getHeight(TabOfIcone[2].Id,"Bitmap");
	}
	
	/**
	 * Menu management
	 *
	 * @param TabOfIcone : array of icons
	 * @param gb         : graphic buffer (size of 128x64 pixels)
	 * @param fast       : graphic buffer for draw the camera frame
	 */
	public static void manage(Icone TabOfIcone[], Icone yourTestIcons[], GraphicBuffer gb, GraphicBuffer fast)
	{
	int i = 0;
	Form ListOfForm[] = null ;
		
	int head=128 ;
	byte follow=0;
	int FormToFind ;
	
	if( Pad.getButton()==true && Main.OnIcone!=0 )
	{	
		// if cursor is on a menu icon 
		switch(Main.OnIcone)
		{
			/* 3 actions sont gérées dans le menu principal :
			 *  - suivi de forme "triangle" par la tête (pilotage moteur de la caméra)
			 *  - suivi de forme "croix" par le robot (pilotage chenille)
			 *  - une action libre que vous pouvez définir
			 */
			 
			// look a form and move the head 
			case Bitmap.FINDANDMOVEHEAD_BMP :
			
				// form to look is a triangle
				FormToFind = Pattern.TRIANGLE_BMP ;
				
				// draw a 'return' button
				gb.clear();
				gb.draw(70,10,Bitmap.TORETURN_BMP,"Bitmap");
				lcd.draw(gb);
				
				// init camera frame
				RGBFrame.init();
				
				do
				{
					// grab a frame and binary it
					RGBFrame.grab();
					RGBFrame.binary();
					// draw the camera frame
					Main.drawCameraFrame(fast);
		
					// identify form
					ListOfForm = RGBFrame.identify("Pattern");
					
					follow = 0 ;
					/* 
					 * Warning, always verify if object is not null
					 */
					if( ListOfForm != null )
					{
						for( i=0 ; i < ListOfForm.length ; i++ )
						{
							// if the form is a triangle :
							if(ListOfForm[i].id==FormToFind)
							{	
								// increment/decrement head position
								if(ListOfForm[i].y>65)
								{
									head+=2 ;
								}
								else if(ListOfForm[i].y<55)
								{
									head-=2 ;
								}
								// and move the bot to center the form on the camera
								if(ListOfForm[i].x>55)				
								{										
									follow=Bot.MOVE_RIGHT;
								}
								else if( ListOfForm[i].x < 35 )
								{
									follow=Bot.MOVE_LEFT;
								}
							}
						}
					}
					
					
					if( head == 256 )
						head = 255 ;
					if( head < 0 )
						head = 0 ;
					
					// finally, move bot and head
					if( follow == Bot.MOVE_LEFT || follow == Bot.MOVE_RIGHT )
					{
						Bot.move(follow);
						System.wait(200);
						Bot.move((byte)0);
					}
					Bot.setHead(head);
					
				}while(Pad.getButton() == false);
		
				while(Pad.getButton()==true);
				draw(TabOfIcone,gb);
					
			break ;
		
			// follow a form
			case Bitmap.FINDANDFOLLOW_BMP :
			
				// form to follow is a cross
				FormToFind = Pattern.CROSS_BMP ;
				
				gb.clear();
				gb.draw(70,10,Bitmap.TORETURN_BMP,"Bitmap");
				lcd.draw(gb);
				
				RGBFrame.init();
				Bot.setHead(135);

				do
				{
					RGBFrame.grab();
					RGBFrame.binary();
					
					Main.drawCameraFrame(fast);
		
					ListOfForm = RGBFrame.identify("Pattern");
							
					follow=0;
					/* 
					 * Warning, always verify if object is not null
					 */
					if( ListOfForm != null )
					{
						
						for( i=0 ; i < ListOfForm.length ; i++ )
						{
							if(ListOfForm[i].id==FormToFind)
							{	
								// verify the position of form 
								// and set correct movement for the bot
								if(ListOfForm[i].x>55)				
								{										
									follow=Bot.MOVE_RIGHT;
								}
								else if( ListOfForm[i].x < 35 )
								{
									follow=Bot.MOVE_LEFT;
								}
								else
								{ 
									follow=Bot.MOVE_RUN; 
								}
							}
						}
					}
					
					// finally move the bot
					if( follow == Bot.MOVE_LEFT || follow == Bot.MOVE_RIGHT )
					{
						Bot.move(follow);
						System.wait(200);
						Bot.move((byte)0);
					}
					else 
					{ 
						Bot.move(follow);
					}
					
					
				}while(Pad.getButton() == false);
		
				while(Pad.getButton()==true);
				draw(TabOfIcone,gb);
						
			break;
			
			// user action :
			case Bitmap.YOURTEST_BMP :
			
			// set your own code here !
			
				YourTest.draw(yourTestIcons,gb);
				YourTest.manage(yourTestIcons,gb);
			
			break;

			
		}//switch(MenuManager.OnIcone)
		
	}//if( Pad.getButton()!=0 && MenuManager.OnIcone!=0 )
	}
	


}