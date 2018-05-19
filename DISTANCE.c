 #include<LPC17xx.h>
 #include<stdio.h>

 #include "AN_LCD.h"
 
	unsigned char arr[10];
	unsigned int end = 0;
	float d = 0;
	
void EINT1_IRQHandler(void);

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_SC -> EXTINT = 0x02; //Clearing the prnding interrupts
	
	LPC_PINCON -> PINSEL4 = 0x00C30000; //P2.8 & P2.11 (EINT1)
	LPC_GPIO2 -> FIODIR = 0x00000100; //Setting P2.8 as Output
	
	LPC_TIM0 -> TCR = 0x02; // Timer0 Reset
	LPC_TIM0 -> PR = 2; // 1 Microsecond
	LPC_TIM0 -> MR0 = 9; // Giving 10 Microsecond delay to trigger the module
	LPC_TIM0 -> MCR = 0x02; // Reset TC 
	LPC_TIM0 -> EMR = 0x20; 
	LPC_TIM0 -> TCR = 0x01; // Timer0 Enable
	//After the delay Sensor sends 40KHz ultrasoundsignal
	while(!LPC_TIM0 -> EMR & 0x01); //wait till 10 Microseconds
	LPC_TIM0 -> TCR = 0x02; //Reset TIMER0
	NVIC_EnableIRQ(EINT1_IRQn);
	
	end=0;
	LPC_SC->EXTMODE=0x02; //edge  
	LPC_SC->EXTPOLAR=0x02; // +ve edge  
	LPC_GPIO2->FIOPIN=0x00000000; 
	delay_lcd(2);
	LPC_GPIO2->FIOPIN|=0X00000100; 
	
	while(1);

	
}
void EINT1_IRQHandler(void)
{
  LPC_SC->EXTINT=0x02;
	if(!end)
	{
		LPC_TIM1->TCR = 0x02; //Timer1 Reset
		LPC_TIM1->TCR = 0x01; // Timer1 Enable
		LPC_SC->EXTPOLAR = 0x00; // -ve edge
		end = 1;
	}
	else
	{
		d = LPC_TIM1->TC/58.0;
		sprintf(arr, "Distance : %3.1f cm ", d); //converting into string
		temp1=0x80; // Line 1
		lcd_com(); 
		lcd_puts(&arr[0]); 
		end=0;
		LPC_SC->EXTMODE=0x02;  // edge 
		LPC_SC->EXTPOLAR=0x02; // +ve edge 
		LPC_GPIO2->FIOPIN=0x00000000; 
		delay_lcd(10);
		LPC_GPIO2->FIOPIN=0X00000400; 
		LPC_TIM0->TCR=0x02; //Timer0 Reset
		LPC_TIM0->TCR=0x01; //Timer0 Enable
	}
}

 

