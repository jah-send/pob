// Copyrith POB-Technology, 2006. All rights reserved.

import com.pobtechnology.pobeye.* ;


/**
 * Bot method.
 *
 * @author Baptiste Burles & Pierre Séguin POB-Technology
 */
class Bot
{


	/**
	 * Move order
	 */
	public final static byte MOVE_RUN=(byte)0x05;
	public final static byte MOVE_BACK=(byte)0x0A;
	public final static byte MOVE_LEFT=(byte)0x09;
	public final static byte MOVE_RIGHT=(byte)0x06;

	/**
	 * Init the pob-proto board on the bot.
	 */
	public static void init()
	{		 
		// PORTA set to analogic
		PobProto.configPortAAsAnalogic();
		
		// pin 0 to 3 of PORTD : output for motor
		PobProto.configPortDAs(0,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(1,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(2,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(3,PobProto.DIGITAL_OUTPUT);
		
		// pin 4 to 7 of PORTD : output for motor
		PobProto.configPortDAs(4,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(5,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(6,PobProto.DIGITAL_OUTPUT);
		PobProto.configPortDAs(7,PobProto.DIGITAL_OUTPUT);
		
		// pin 0 to 7 of PORTC set as servomotor
		// Warning : pin 4 and 5 are reserved
		PobProto.configPortCAs(0,PobProto.AS_SERVO);
		PobProto.configPortCAs(1,PobProto.AS_SERVO);
		PobProto.configPortCAs(2,PobProto.AS_SERVO);
		PobProto.configPortCAs(3,PobProto.AS_SERVO);
		PobProto.configPortCAs(6,PobProto.AS_SERVO);
		PobProto.configPortCAs(7,PobProto.AS_SERVO);
		
		// PORT configuration is set to the pob-proto
		PobProto.writeConfig();
	}
	
	/**
	 * Set the bot head
	 *
	 * @param m0  : Head position
	 */
	public static void setHead(int m0)
	{
		PobProto.setServoMotor(0,m0);
	}

	/**
	 * Move the bot
	 *
	 * @param Move : move order (motor to activate)
	 */
	public static void move(byte Move)
	{
		PobProto.setPortD(Move);
	}
	
	
	private Bot()
	{
	}
}
