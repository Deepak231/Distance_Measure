/**********************************************************
 * Header file for LCD.c file 			Date:16-06-2014
 * Created by 
 * Advanced Electronics Systems, Bengaluru.
 * Declared the functions and variables related to .c file
 **********************************************************/
#ifndef __LCD_H
#define __LCD_H

#define RS_CTRL  0x08000000  //P0.27
#define EN_CTRL  0x10000000  //P0.28
#define DT_CTRL  0x07800000  //P0.23 to P0.26 data lines

void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);						   
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char *);

extern unsigned long int temp1 , temp2;

#endif

