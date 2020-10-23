/* 
 * File:   main.c
 * Author: Antonella
 *
 * Created on 21 de octubre de 2020, 10:55 PM
 */

#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "TMR0.h"
/*
 * 
 */

#define R1 PORTAbits.RA0
#define A1 PORTAbits.RA1
#define V1 PORTAbits.RA2

#define R2 PORTAbits.RA3
#define A2 PORTAbits.RA4
#define V2 PORTAbits.RA5

#define R3 PORTEbits.RE0
#define A3 PORTEbits.RE1
#define V3 PORTEbits.RE2

char estados=0;
int t_ra=4,t_a=2,t_v=4;
int time1 = 0, time2 = 0, time3 = 0;

void validar_estados(){
    
    R1=R2=R3 = 1;
    
    switch(estados){
        case 0: 
            R1=1; A1=0; V1=0; 
            time1 = t_ra;
            break;
            
        case 1: 
            if(time1==0){
                time1=t_v;
                R1=1; A1=1; V1=0;
            }
            else{    
                R1=1; A1=1; V1=0;
                estados--;
                time1--;
            }
            break;
            
        case 2: 
            if(time1==0){
                time1=t_a;
                R1=0; A1=0; V1=1;
            }
            else{    
                R1=0; A1=0; V1=1;
                estados--;
                time1--;
            }
            break;
            
        case 3: 
            if(time1!=0){    
                R1=0; A1=1; V1=0;
                estados--;
                time1--;
            }
            else{
                R1=1; A1=0; V1=0;
            }
            break;
        case 4: 
            R1=1; A1=0; V1=0; 
            break;
        
        // SEGUNDO SEMAFORO
        case 5: 
            R2=1; A2=0; V2=0; 
            time2 = t_ra;
            break;
            
        case 6: 
            if(time2==0){
                time2=t_v;
                R2=1; A2=1; V2=0;
            }
            else{    
                R2=1; A2=1; V2=0;
                estados--;
                time2--;
            }
            break;
        case 7: 
            if(time2==0){
               time2=t_a;
               R2=0; A2=0; V2=1;
            }
            else{    
                R2=0; A2=0; V2=1;
                estados--;
                time2--;
            }
            break;
            
        case 8: 
            if(time2!=0){    
                R2=0; A2=1; V2=0;
                estados--;
                time2--;
            }
            else{
                R2=1; A2=0; V2=0;
            }
            break;
        case 9: 
            R2=1; A2=0; V2=0;
            break;
        
        
        // TERCER SEMAFORO
        case 10: 
            R3=1; A3=0; V3=0; 
            time3 = t_ra;
            break;
            
        case 11: 
            if(time3==0){
                time3=t_v;
                R3=1; A3=1; V3=0;
            }
            else{    
                R3=1; A3=1; V3=0;
                estados--;
                time3--;
            }
            break;
            
        case 12: 
            if(time3==0){
                time3=t_a;
                R3=0; A3=0; V3=1;
            }
            else{    
                R3=0; A3=0; V3=1;
                estados--;
                time3--;
            }
            break;
            
        case 13: 
            if(time3!=0){    
                R3=0; A3=1; V3=0;
                estados--;
                time3--;
            }
            else{
                R3=1; A3=0; V3=0;
            }
            break;
            
        case 14: 
            R3=1; A3=0; V3=0; 
            break;
        }
    estados++;
    if(estados>14)
        estados=0;
    return;
}

void seven(int numero, int posicion){

    int deco[]={
        0b10000000, //0  
        0b11111001, //1
        0b01000100, //2
        0b01100000, //3
        0b00111001, //4
        0b00101010, //5
        0b00001010, //6
        0b11111000, //7
        0b00000000, //8
        0b00110000, //9
    };
    
    
    int pos[]={
        0b00000000,
        0b00000001, 
        0b00000010,
        0b00000100,
        0b00001000,
    };
        
    PORTC = deco[numero];
    PORTD = pos[posicion];
    __delay_ms(1);
    PORTD = 0;
}

void __interrupt() tmr0(){
    
    TMR0H = (57723&0xFF00)>>8;
    TMR0L = 57723&0x00FF;
    
    validar_estados();
    
    TMR0IF = 0;
}

void main(void) {

    ADCON1= 0x0F;
    TRISA = 0x00;
    TRISE = 0x00;
    TRISC = 0x00;
    myTMR0_CONF(_T0_TEMP,_T0_BIT_16,_T0_R_UP,
                  _T0_PREES_ON,_T0_PRE_128,_T0_ON);
    
    TMR0H = (57723&0xFF00)>>8;
    TMR0L = 57723&0x00FF;
    
    TRISC = 0;      //Salida
    TRISD = 0;      //Salida
    PORTC = 0;
    PORTD = 0;
    
    GIE = 1;
    PEIE = 1;
    TMR0IE = 1;
    
    R1=R2=R3 = 1;
    A1=A2=A3 = 0;
    V1=V2=V3 = 0;
    
    while(1){
        seven(0, 1);
        seven(time1, 2);
        seven(0, 3);
        seven(time2, 4);
        seven(0, 5);
        seven(time3, 6);
    }
}

