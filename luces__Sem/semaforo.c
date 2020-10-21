
#include <xc.h>
#include "config.h"
#include"USART_libreria.h"
#include"Configuracion.h"
#define _XTAL_FREQ 32000000
//prototipos de funciones
void Avance_N(void);
void Espera_N(void);
void Avance_E(void);
void Espera_E(void);
char time;
//estructura para FSM

struct State{

    void(*funcionPt)(void);//Variable de función
    unsigned int Time;//Tiempo
    unsigned char Next[4];
};
    typedef const struct State Styp;
    //estados 
#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
    
    
//definir estructura maquina de estados
    Styp FSM[4]={
     {&Avance_N,3000,{goN,waitN,goN,waitN}},
    {&Espera_N,0,{goE,goE,goE,goE}},
    {&Avance_E,3000,{goE,goE,waitE,waitE}},
    {&Espera_E,0,{goN,goN,goN,goN}}};
    unsigned char actual;
    unsigned input;
    
   //Función para configurar el oscilador y puertos del microcontrolador
void Init_FSM(void){
//oscilador 32MHz
    OSCCONbits.IRCF=0b1110;
   OSCCONbits.SCS=0;
 
//Puertos
    ADCON1= 0x0f;//All Digital
    TRISB=0;//Puerto B como salidas
    TRISA=255;//Puerto C como entradas
    INTCONbits.GIE=1;   /* enable Global Interrupt */
    INTCONbits.PEIE=1;  /* enable Peripheral Interrupt */
    PIE1bits.RCIE=1;    /* enable Receive Interrupt */
    //Oscilador
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=00;
    
    
}

void main(void) {
    //char valor;
    USART_Init(9600);
    int x;
    Init_FSM();
    actual=goN;
    
    while(1){
    
        time = USART_Rx();
       /* USART_Tx();
        USART_Cadena();
        PORTA=USART_Rx();
        
          valor = USART_Rx();
        if( valor == 'w'){
            USART_Cadena("Hola :D ");
        }
        else{
            USART_Cadena("no :c ");
        }
        __delay_ms(500);*/
        
        //Motor de la maquina de estados
        //FSM engine
        (FSM[actual].funcionPt)();
        for(x=0;x<FSM[actual].Time;x++)
            __delay_ms(1);
        input=PORTA;
        actual=FSM[actual].Next[input];
        
       
            
    }
    
    return;
}
void Avance_N(void){
    LATB=0x21;
}

void Espera_N(void){
    LATB=0x22;
    __delay_ms(200);
    LATB=0x20;
    __delay_ms(200);
    LATB=0x22;
    __delay_ms(200);
    LATB=0x20;
    __delay_ms(200);
    LATB=0x22;
    __delay_ms(200);
}

void Avance_E(void){
    LATB=0x0C;
}

void Espera_E(void){
    LATB=0x14;
    __delay_ms(200);
    LATB=0x04;
    __delay_ms(200);
    LATB=0x14;
    __delay_ms(200);
    LATB=0x04;
    __delay_ms(200);
    LATB=0x14;
    __delay_ms(200);
}