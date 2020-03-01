#include <lcd.h>
#include <intrins.h>
#include <stdio.h>
sbit HX711_DOUT=P2^1; 
sbit HX711_SCK=P2^0; 
char buf1[10];


//***************Code by LE XUAN ANH*******************//
 void delay_ms(unsigned int t)
 {
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);
}
void Delay__hx711_us(void)
{
	_nop_();
	_nop_();
}
//************************//
unsigned long HX711_Read(void)	
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	Delay__hx711_us();
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
	} 
 	HX711_SCK=1; 
    count=count^0x800000;
	Delay__hx711_us();
	HX711_SCK=0;  
	return(count);
}

void main()
{
unsigned int temp,i;
float gram=0,k,a1,a2,a3,a4;
    Init_LCD1602();								
	LCD1602_write_com(0x80);					
	LCD1602_write_word("Can dien tu-VXL");
  	for(i=0;i<20;i++) 			// LAY MAU LAN 1
  {
  
	temp= HX711_Read();			//DOC VE ADC

	 a1+=temp;
	 delay_ms(20);
  }
  
 a2=a1/20;
	 
	 
  
 			

 while(1)
 {
 LCD1602_write_com(0x80+0x40+8);
  	 a3 =0;
	
	for(i=0;i<30;i++)	   //LAY MAU LAN 2
	  {
		temp= HX711_Read();
		a3+=temp;
		delay_ms(20);
	  }
	  a4=a3/30;
	  k=a4-a2;	 	 			//MAU LAN 2-LAN1
	  if(k<0) k=0;
	  gram=71428.5*(float)(k/16777216.0);	//CHUYEN DOI RA GRAM
	  sprintf(buf1,"%.0f g   ",gram);	   //HIEN THI LCD
	  LCD1602_write_word(buf1);      		
			
	

 
 }
}