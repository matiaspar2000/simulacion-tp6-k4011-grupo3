#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define HV 2000000

long int TPLL = 0, NS = 0, TF = 1350000, NT = 0, T = 0, STE = 0, STLL = 0, STA = 0, STS = 0, ARR = 0, SPS = 0, SEC = 0, STO = 0; 
float IA = 0, TA = 0;
int puesto;

float randomn(int min, int max){
    float r = 0;
    while(r == 0 || r == 1){
        r = (float)rand()/(float)RAND_MAX;
    }
    return r;
}

int arrepentimiento(){
    float r = randomn(0,1);
        if( r < 0.075){
            return 0;
        }
    return 1;
}

float intervaloArrivos(float random){
    float alfaIA = 0.73013f;
    float betaIA = 303.16f;
    float gammaIA = 2.0f; 
   
    return betaIA * pow((-log(1-random)),1/alfaIA) + gammaIA;
}
   
float intervaloAtencion(float random){
    float alfaTA = 1.038f;
    float betaTA = 996.15f;
    float gammaTA = 280.42f; 
   
    return betaTA * pow((-log(1-random)),1/alfaTA) + gammaTA;
}

float generar_ia(){
    float r = randomn(0,1);
    return intervaloArrivos(r);
}

float generar_ta(){
    float r = randomn(0,1);
    return intervaloAtencion(r);
}

int menor_tps(long tps[], int cantidad){
    long min = tps[0];
    int imin;
            
    for (int i = 0; i < cantidad; i++) {    
       if(tps[i] <= min){    
           min = tps[i]; 
           imin = i;   
       }
    }      
    return imin;     
}

long int menor_ns(long int ns[], int cantidad){
    long int min = ns[0];
    int imin;
            
    for (int i = 0; i < cantidad; i++) {    
       if(ns[i] <= min){    
           min = ns[i]; 
           imin = i;   
       }
    }      
    return imin;     
}

int puesto_libre(long tps[], int cantidad){
    long min = tps[0];
    int libre = 0;

    for (int i = 0; i < cantidad; i++) {       
       if(tps[i] == HV){    
           libre = i;   
       }
    }      
    return libre;     
}

long int siendo_atendidas(long tps[], int cantidad){
    long int atendidos = 0;

    for (int i = 0; i < cantidad; i++) {       
       if(tps[i] != HV){    
           atendidos++;   
       }
    }      
    return atendidos;     
}

int n_puestos_1_cola(int cantidad){
    long tps[cantidad];
    for (int i = 0; i < cantidad; i++) {       
       tps[i] = HV;
    } 

    long ito[cantidad];
    for (int i = 0; i < cantidad; i++) {       
       ito[i] = T;
    } 

    while ( T < TF){
        puesto = menor_tps(tps,cantidad);

        if(TPLL <= tps[puesto]){
            SEC = SEC + (TPLL - T) * (NS - siendo_atendidas(tps,cantidad));
            T = TPLL;
            IA = generar_ia();
            TPLL = T + IA;
            NT++;
            if(arrepentimiento()){
                NS++;
                if(NS <= cantidad){
                    int i = puesto_libre(tps,cantidad);
                    TA = generar_ta();
                    tps[i] = T + TA;
                    STO += T - ito[i];
                }
            }else{
                ARR++;
            }
        }else{
            SEC = SEC + (tps[puesto] - T) * (NS - siendo_atendidas(tps,cantidad));
            T = tps[puesto];
            NS--;
            if(NS >= cantidad){
                TA = generar_ta();
                tps[puesto] = T + TA;
            }else{
                tps[puesto] = HV;
                ito[puesto] = T;
            }
        }
    }
    
    printf("%lu \n", NT);
    printf("%lu \n", ARR);
    printf("%ld \n", SEC);
    printf("%lu \n", STO);
    return 0;
}

long int sumatoria(long int ns[], int cantidad){
    long int sumatoria = 0;

    for (int i = 0; i < cantidad; i++) {         
        sumatoria += ns[i];   
    }      
    return sumatoria;     
}

int n_puestos_n_colas(int cantidad){
    long tps[cantidad];
    long int ns[cantidad];
    int menos_gente;
    
    for (int i = 0; i < cantidad; i++) {       
       tps[i] = HV;
       ns[i] = 0;
    } 

    long ito[cantidad];
    for (int i = 0; i < cantidad; i++) {       
       ito[i] = T;
    } 

    while ( T < TF){
        puesto = menor_tps(tps,cantidad);
        if(TPLL < tps[puesto]){
            SEC += (TPLL - T) * (sumatoria(ns,cantidad) - siendo_atendidas(tps,cantidad));
            T = TPLL;
            IA = generar_ia();
            TPLL = T + IA;
            NT++;
            if(arrepentimiento() == 1){
                menos_gente = menor_ns(ns,cantidad);
                ns[menos_gente] += 1;
                if(ns[menos_gente] == 1){
                    TA = generar_ta();
                    tps[menos_gente] = T + TA;
                    STO += T - ito[menos_gente];
                }
            }else{
                ARR++;
            }
        }else{
            SEC += (tps[puesto] - T) * (sumatoria(ns,cantidad) - siendo_atendidas(tps,cantidad));
            T = tps[puesto];
            ns[puesto] = ns[puesto] - 1;
            if(ns[puesto] > 0){
                TA = generar_ta();
                tps[puesto] = T + TA;
            }else{
                tps[puesto] = HV;
                ito[puesto] = T;
            }
        }
    }

    printf("%lu \n", NT);
    printf("%lu \n", ARR);
    printf("%ld \n", SEC);
    printf("%lu \n", STO);
    return 0;
}

time_t t;

int main() {
    srand((unsigned) time(&t));
    printf(" =============================== N PUESTOS 1 COLA =============================== \n");
        for (int a = 2; a < 11; a++) { 
            printf("%d PUESTOS 1 COLA ==========================================================  \n", a); 
            n_puestos_1_cola(a);
            TPLL = 0, NS = 0, TF = 1350000, NT = 0, T = 0, STE = 0, STLL = 0, STA = 0, STS = 0, IA = 0, TA = 0, ARR = 0, SPS = 0, SEC = 0, STO = 0;  
        } 
    printf(" \n");
    printf(" \n");
    printf(" \n");
    printf(" =============================== N PUESTOS N COLAS =============================== \n");
        for (int a = 2; a < 11; a++) { 
            printf("%d PUESTOS %d COLAS ==========================================================  \n", a, a);      
            n_puestos_n_colas(a);
            TPLL = 0, NS = 0, TF = 1350000, NT = 0, T = 0, STE = 0, STLL = 0, STA = 0, STS = 0, IA = 0, TA = 0, ARR = 0, SPS = 0, SEC = 0, STO = 0;  
        } 

    return 0;
}
