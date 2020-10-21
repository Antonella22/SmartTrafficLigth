/* 
 * File:   main.c
 * Author: Antonella
 *
 * Created on 13 de octubre de 2020, 12:36 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "Configuracion.h"
#include "USART_libreria.h"
#include "lcd.h"
#include "teclado.h"

//Variables Globales
char K = 0;
unsigned char time[3]={0,0,0};
unsigned char i=0; 
unsigned char read=0;
unsigned char pos=1;
unsigned int numero=0;
char DEC, UNI, VAL; //int8==unsigned
unsigned char item[10];

void TECLADO() {
    K = teclado_getc(); //Llamar la función del teclado y almacenar
    //el valor digitado en una variable tipo
    //carácter. Si no se oprime ninguna tecla el
    //teclado retornara el carácter nulo.*/
    while (K == '\0') //si no se oprime ninguna tecla sigue llamando al teclado.
    {
        K = teclado_getc();
    }
    if ((K != '\0')) {
        if (K == '0')//Si K es igual a cero
            VAL = 0; //Val es igual a cero
        if (K == '1')
            VAL = 1;
        if (K == '2')
            VAL = 2;
        if (K == '3')
            VAL = 3;
        if (K == '4')
            VAL = 4;
        if (K == '5')
            VAL = 5;
        if (K == '6')
            VAL = 6;
        if (K == '7')
            VAL = 7;
        if (K == '8')
            VAL = 8;
        if (K == '9')
            VAL = 9;        
    }
}

void read_time(){
    long num = 0, d, u;
    while(read){
        TECLADO();
        
        switch(pos){
            case 1:
                LCD_gotoxy(10, 1); //Se ubica en la posición 2,1
                LCD_putc(K);
                DEC = VAL;
                d = DEC * 10;
                break;
            case 2:
                LCD_gotoxy(11, 1); //Se ubica en la posición 2,1
                LCD_putc(K);
                UNI = VAL;
                u = UNI;
                num= d + u;
                time[0]=num;
                break;
            case 3:
                LCD_gotoxy(10, 2); //Se ubica en la posición 2,1
                LCD_putc(K);
                DEC = VAL;
                d = DEC * 10;
                break;
            case 4:
                LCD_gotoxy(11, 2); //Se ubica en la posición 2,1
                LCD_putc(K);
                UNI = VAL;
                u = UNI;
                num= d + u;
                time[1]=num;
                break;
            case 5:
                LCD_clear();
                LCD_gotoxy(1, 1); 
                LCD_puts("Verde", 5);
                LCD_gotoxy(10, 1); //Se ubica en la posición 2,1
                LCD_putc(K);
                DEC = VAL;
                d = DEC * 10;
                break;
            case 6:
                LCD_gotoxy(11, 1); //Se ubica en la posición 2,1
                LCD_putc(K);
                UNI = VAL;
                u = UNI;
                num= d + u;
                time[2]=num;
                
                //LCD_gotoxy(1, 2); 
                //sprintf(item,"Time %02d",num);
                //LCD_puts(item,10);
                
                USART_Tx(time);
              
                break;
                
        }
        pos++;
        if(pos>6){
            pos=1;
        }
        i++;
        if (K == '#'){
            read=0;
        }
    }
}

//Función para configurar el oscilador y puertos del microcontrolador
void Init_FSM(void){
    TRISC=255;//Puerto C como entradas
//oscilador 32MHz
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=0;
 
//Puertos
    ADCON1= 0x0f;//All Digital

    INTCONbits.GIE=1;   /* enable Global Interrupt */
    INTCONbits.PEIE=1;  /* enable Peripheral Interrupt */
    PIE1bits.RCIE=1;    /* enable Receive Interrupt */
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=00;
    //Oscilador
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=00;
    
}    

void main() {
    //INICIO: 
    //Puerto C como Salida
    TRISC = 0;
    TRISD = 0;
    PORTC = 0; //Limpia Puerto C

    USART_Init(9600);
    LCD_init(); //Inicializa el LCD
    teclado_init(); //Inicializa KeyPad 4x4

    while (1) {
        
        if(read==0){
            LCD_clear();
            LCD_gotoxy(5, 1);
            LCD_puts("    STL   ", 8);
            LCD_gotoxy(2, 2); //Se ubica en la posición 2,1
            LCD_puts("1.Conf Time   ", 15);
        }
        
        TECLADO();
        if(K == '1'){
            LCD_clear();
            LCD_gotoxy(1, 1); 
            LCD_puts("Rojo", 5);
            LCD_gotoxy(1, 2); 
            LCD_puts("Amarillo", 8);
            read=1;
            read_time();    
        }
        
        
    }
}