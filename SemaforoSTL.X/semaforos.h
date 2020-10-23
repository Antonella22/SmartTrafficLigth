  
#ifndef semaforos_H
#define	semaforos_H

#include <xc.h> 

#define R1 PORTAbits.RA0
#define A1 PORTAbits.RA1
#define V1 PORTAbits.RA2

#define R2 PORTAbits.RA3
#define A2 PORTAbits.RA4
#define V2 PORTAbits.RA5

#define R3 PORTEbits.RE0
#define A3 PORTEbits.RE1
#define V3 PORTEbits.RE2

extern char estados;

extern char tiempo, t_ra,t_a,t_v;

void validar_estados(){
    
    R1=R2=R3 = 1;
    
    switch(estados){
        case 0: R1=1; A1=0; V1=0; 
                tiempo = t_ra;
                break;
        case 1: if(tiempo==0){
                   tiempo=t_v;
                   R1=1; A1=1; V1=0;
                }
                else{    
                    R1=1; A1=1; V1=0;
                    estados--;
                    tiempo--;
                }
                break;
        case 2: if(tiempo==0){
                   tiempo=t_a;
                   R1=0; A1=0; V1=1;
                }
                else{    
                    R1=0; A1=0; V1=1;
                    estados--;
                    tiempo--;
                }
                break;
        case 3: if(tiempo!=0){    
                    R1=0; A1=1; V1=0;
                    estados--;
                    tiempo--;
                }
                else{
                    R1=1; A1=0; V1=0;
                }
                break;
        case 4: R1=1; A1=0; V1=0; break;
        ////////////////////////////////////////////////////
        // SEGUNDO SEMAFORO
        //////////////////////////////////////////////////
        case 5: R2=1; A2=0; V2=0; 
                tiempo = t_ra;
                break;
        case 6: if(tiempo==0){
                   tiempo=t_v;
                   R2=1; A2=1; V2=0;
                }
                else{    
                    R2=1; A2=1; V2=0;
                    estados--;
                    tiempo--;
                }
                break;
        case 7: if(tiempo==0){
                   tiempo=t_a;
                   R2=0; A2=0; V2=1;
                }
                else{    
                    R2=0; A2=0; V2=1;
                    estados--;
                    tiempo--;
                }
                break;
        case 8: if(tiempo!=0){    
                    R2=0; A2=1; V2=0;
                    estados--;
                    tiempo--;
                }
                else{
                    R2=1; A2=0; V2=0;
                }
                break;
        case 9: R2=1; A2=0; V2=0; break;
        
        ////////////////////////////////////////////////////
        // TERCER SEMAFORO
        //////////////////////////////////////////////////
        
        case 10: R3=1; A3=0; V3=0; 
                tiempo = t_ra;
                break;
        case 11: if(tiempo==0){
                   tiempo=t_v;
                   R3=1; A3=1; V3=0;
                }
                else{    
                    R3=1; A3=1; V3=0;
                    estados--;
                    tiempo--;
                }
                break;
        case 12: if(tiempo==0){
                   tiempo=t_a;
                   R3=0; A3=0; V3=1;
                }
                else{    
                    R3=0; A3=0; V3=1;
                    estados--;
                    tiempo--;
                }
                break;
        case 13: if(tiempo!=0){    
                    R3=0; A3=1; V3=0;
                    estados--;
                    tiempo--;
                }
                else{
                    R3=1; A3=0; V3=0;
                }
                break;
        case 14: R3=1; A3=0; V3=0; break;
    }
    estados++;
    if(estados>14)
        estados=0;
    return;
}



#endif	/* XC_HEADER_TEMPLATE_H */

