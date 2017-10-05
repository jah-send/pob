/*
 *
 * Copyright (c) 2006-2010, POB-Technology
 *
 * pob-basic native function.
 *
 */
#ifndef libpob_basic_h
#define libpob_basic_h


/* signed value */
#define s4 long
#define s2 short
#define s1 char

/* unsigned value */
#define u4  unsigned long
#define u2  unsigned short
#define u1  unsigned char

/* real type */
#define float32 float

/* include pob-eye function */
#include <pob-eye.h>

#include <math.h>

/* pob-basic internal function */

//math function
extern float Cos_pobbasic(float v);
extern float Sin_pobbasic(float v);
extern float Tan_pobbasic(float v);
extern float Acos_pobbasic(float v);
extern float Asin_pobbasic(float v);
extern float Atan_pobbasic(float v);
extern float Sqrt_pobbasic(float v);

// camera function
extern void NewRGBFrame_pobbasic(void);

extern void BinaryFrame_pobbasic(void);
extern void GrabRGBFrame_pobbasic(void);
extern void GrabRedFrame_pobbasic(void);
extern void GrabGreenFrame_pobbasic(void);
extern void GrabBlueFrame_pobbasic(void);

extern void GrayFrame_pobbasic(void);
extern short GrayPixel_pobbasic(int pixel);

extern char GetRedPixel_pobbasic( int indice) ;
extern char GetBluePixel_pobbasic( int indice) ;
extern char GetGreenPixel_pobbasic( int indice) ;

extern void SetRedPixel( int indice, char data );
extern void SetBluePixel( int indice, char data );
extern void SetGreenPixel( int indice, char data );


extern void NewHSLFrame_pobbasic(void);
extern void GrabHSLFrame_pobbasic(void);

extern char GetHuePixel_pobbasic(int indice);
extern char GetSaturationPixel_pobbasic(int indice);
extern char GetLightPixel_pobbasic(int indice);

#ifdef POBBASIC_NATIVE
#	define Forms Form
#endif

extern int Identify_pobbasic( Forms *ListOfForm);

extern void SendToCam_pobbasic(char Addr, char Data);


// graphic buffer function
extern int NewGraphic_pobbasic( char w, char h,char bits );
extern void ClearGraphic_pobbasic( int no);
extern void DrawBMP_pobbasic( int no,char x,char y,char id );
extern int GetBMPWidth_pobbasic(int id);
extern int GetBMPHeight_pobbasic(int id);
extern void DrawAPoint_pobbasic(int no,char X,char Y);
extern void DrawALine_pobbasic(int no,char X1, char Y1, char X2, char Y2);

extern void DrawCameraFrame_pobbasic( int no );
extern void SetGraphicPixel_pobbasic(int no, int indice, char value );

// i2c function
extern void I2CSpeed_pobbasic(int speed);
extern void I2CSetSlaveAddress_pobbasic(char adr);
extern char I2CRead_pobbasic(void);
extern void I2CWrite_pobbasic(char data);
extern void I2CStop_pobbasic(void);

// io and bus
extern void SetIOWay_pobbasic(int Value);
extern short GetInput_pobbasic(void);
extern void SetOutput_pobbasic(int Value);
extern void ClrOutput_pobbasic(int Value);
extern void ClrAndSetOuput_pobbasic( int Value);
extern void WriteByte_pobbasic(char Addr,char Data);
extern char ReadByte_pobbasic(char Addr);

// lcd function
extern void LCDInit_pobbasic(void);
extern void LCDDraw_pobbasic(int no);
extern void LCDDrawLeft_pobbasic(int no);
extern void LCDDrawRight_pobbasic(int no);

// wait function
extern void Wait_pobbasic(int time_in_miliseconde);

// uart0 function
extern void UARTInit_pobbasic( int conf);
extern void UARTSend_pobbasic(char data);
extern void UARTSendBuffer_pobbasic( char *data, int number);
extern char UARTGet_pobbasic(char *data);
extern void UARTGetBuffer_pobbasic( char *buffer, int number);

// uart1 function
extern void UART1Init_pobbasic( int conf);
extern void UART1Send_pobbasic(char data);
extern void UART1SendBuffer_pobbasic( char *data, int number);
extern char UART1Get_pobbasic(char *data);
extern void UART1GetBuffer_pobbasic( char *buffer, int number);

// pobtools debug
extern void PrintText_pobbasic( char *s);

// pobproto function
extern void ConfigPortA_pobbasic(int rx, int v);
extern void ConfigPortAnalogic_pobbasic(void);
extern void ConfigPortD_pobbasic(int rx, int v);
extern void ConfigPortC_pobbasic(int rx, int v);
extern void SetConfigPobProto_pobbasic(void);

extern char GetPortA_pobbasic(void);
extern char GetPinPortA_pobbasic(int pin);
extern char GetPortAnalog_pobbasic(char RAx);

extern void SetPortA_pobbasic(char data);
extern void SetPinPortA_pobbasic(int pin);
extern void ClearPinPortA_pobbasic(int pin);

extern char GetPortD_pobbasic(void);
extern char GetPinPortD_pobbasic(int pin);

extern void SetPortD_pobbasic(char data);
extern void SetPinPortD_pobbasic(int pin);
extern void ClearPinPortD_pobbasic(int pin);

extern char GetPortC_pobbasic(void);
extern char GetPinPortC_pobbasic(int pin);

extern void SetPortC_pobbasic(char data);
extern void SetPinPortC_pobbasic(int pin);
extern void ClearPinPortC_pobbasic(int pin);

extern void SetServoMotor_pobbasic(char RCx,char Pos);

extern void SwitchOffAll_pobbasic(void);
extern void SwitchOnAll_pobbasic(void);
extern void SwitchOn_pobbasic(int rcx);
extern void SwitchOff_pobbasic(int rcx);

extern char SendEcho_pobbasic(char test);


#endif

