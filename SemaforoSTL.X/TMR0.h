
#ifndef myTMR0_H
#define	myTMR0_H

#include <xc.h>

// VALORES DE CONFIGURACION
#define  _T0_CONT       1
#define  _T0_TEMP       0
#define  _T0_BIT_8      1
#define  _T0_BIT_16     0
#define  _T0_R_UP       0
#define  _T0_R_DOWN     1
#define  _T0_PREES_ON   0
#define  _T0_PREES_OFF  1
#define  _T0_ON         1
#define  _T0_OFF        0  

// VALORES DEL PREESCALADOR
#define  _T0_PRE_256     7
#define  _T0_PRE_128     6
#define  _T0_PRE_64      5
#define  _T0_T0_PRE_32   4
#define  _T0_PRE_16      3
#define  _T0_PRE_8       2
#define  _T0_PRE_4       1
#define  _T0_PRE_2       0


void myTMR0_CONF(char modo, char n_bits,
                  char flanco, char preesc_E, 
                   char valor_preescaler, char ON_OFF){
    T0CONbits.TMR0ON = ON_OFF;
    T0CONbits.T0CS = modo;
    T0CONbits.T08BIT = n_bits;
    T0CONbits.T0SE = flanco;
    T0CONbits.PSA = preesc_E;
    T0CONbits.T0PS = valor_preescaler;
    
    if(T0CONbits.T0CS){
        TRISAbits.RA4 = 1;
    }
}

#endif	/* XC_HEADER_TEMPLATE_H */

