#include <stdio.h>
#include <stdlib.h>
#include <math.h> //porque tengo que sacar la raiz cuadrada dentro de mi funcio

typedef struct {
    double tension;
    double corriente;
    double tiempo;
} datos;

void potencias(datos *motor, int cantidad, double *P, double *S, int numero_de_motor) //motor por referencia, cantidad por valor
{
    //primero calculo la potencia activa
    //hago las sumas de la multiplicacion de el voltaje por la corriente
    double multiplicacion;
    double suma=0;
    for(int i=0; i<cantidad; i++)
    {
        multiplicacion= motor[i].corriente*motor[i].tension;
        suma= suma+multiplicacion; 
    } //al final de este for, voy a tener la sumatoria de todas las multiplicaciones de tension y corriente
    double diferencia_tiempo = motor[cantidad-1].tiempo - motor[0].tiempo; //hago la diferencia del final menos el inicial 
    //pongo cantidad-1 ya que, cantidad es justamente la cantidad total de grupos de 3 doubles. pero tambien contemplo el cero, asi que hago cantida-1

    *P= suma/diferencia_tiempo; //diferencia de tiempo lo puedo reutilizar en los RMS
    printf("\nLa potencia (P) del motor %d es igual a: %.2lf",numero_de_motor, *P);


    //ahora paso a calcular la potencia aparente, para hacerlo tengo que calcular voltajeRMS por corrienteRMS
    //para hacerlo tengo que calcular cada uno.


    //voltaje RMS
    double voltajeRMS;
    double voltaje_al_cuadrado;
    double suma_voltaje=0;
    for(int i=0; i<cantidad; i++)
    {
        //hago la sumatoria de los voltajes al cuadrado
        voltaje_al_cuadrado = motor[i].tension * motor[i].tension;
        suma_voltaje= suma_voltaje+voltaje_al_cuadrado;

    }
    double valor_dentro_raiz =suma_voltaje/diferencia_tiempo;
    //la raiz cuadrada de valor_dentro_raiz la cual sera el resultado final para voltajeRMS
    voltajeRMS = sqrt(valor_dentro_raiz);


    //corriente RMS (repito los mismos pasos)
    double corrienteRMS;
    double corriente_al_cuadrado;
    double suma_corriente=0;
    for(int i=0; i<cantidad; i++)
    {
        corriente_al_cuadrado = motor[i].corriente * motor[i].corriente;
        suma_corriente= suma_corriente+corriente_al_cuadrado;
    }
    double valor_dentro_raiz2 =suma_corriente/diferencia_tiempo;
    corrienteRMS = sqrt(valor_dentro_raiz2);
    *S= voltajeRMS * corrienteRMS; //valor final para la potencia aparente 
    printf("\nLa potencia (S) del motor %d es igual a: %.2lf", numero_de_motor, *S);
    
}

int main()
{
    FILE *motor1 = fopen("motor1.dat","rb");
    if(!motor1)
    {
        printf("\nerror: no se pudo abrir archivos del motor 1.");
        return 1;
    }
    //principio del archivo para motor uno
    fseek(motor1,0,SEEK_END); //me muevo al final del archivo
    long contenido_motor1 = ftell(motor1); //esto me dice el tamaño del archivo en bytes
    int cantidad_doubles1 =contenido_motor1 / sizeof(double); //esto me dice cuantos datos tipo double hay en el motor1.dat
    int cantidad_grupos1 = cantidad_doubles1/3; //esto me va a decir cuantos grupos de tres hay dentro del archivo motor1.dat

    //como ya tengo la cantidad de grupos, puedo saber que esa cantidad es la que necesito para mi vector struct
    printf("\nla cantidad de registros del motor 1 es: %d", cantidad_grupos1); //lo compile hasta esta parte y me dice que son 1000 registros (de a grupos de 3)
    
    //ya puedo declarar un vector tipo struct 
    datos *motor_n1 = malloc(cantidad_grupos1 * sizeof(datos)); 
    if(motor_n1 == NULL)
    {
        printf("\nerror: no se pudo reservar memoria para guardar datos del motor 1.");
        fclose(motor1);
        return 1;
    }
    fseek(motor1,0, SEEK_SET); //vuelvo al principio del archivo para empezar a leer los datos
    for(int i=0; i<cantidad_grupos1; i++)
    {
        fread(&motor_n1[i].tension, sizeof(double), 1, motor1);
        fread(&motor_n1[i].corriente, sizeof(double), 1, motor1);
        fread(&motor_n1[i].tiempo, sizeof(double), 1, motor1);
    }
    fclose(motor1);
    //ya tengo mi primer vector motor_n1 armado, ahora paso con los demas motores

    FILE *motor2 = fopen("motor2.dat","rb"); //para motor 2
    if(!motor2)
    {
        printf("\nerror: no se pudo abrir archivos del motor 2.");
        free(motor_n1); //libero la memoria del primer vector
        return 1;
    }
    fseek(motor2,0,SEEK_END);
    long contenido_motor2 = ftell(motor2);
    int cantidad_doubles2= contenido_motor2/sizeof(double);
    int cantidad_grupos2 = cantidad_doubles2/3;

    printf("\nla cantidad de registros del motor 2 es: %d", cantidad_grupos2); //para verificar 
    datos *motor_n2 = malloc(cantidad_grupos2*sizeof(datos));
    if(motor_n2== NULL)
    {
        printf("\nerror: no se pudo reservar memoria para guardar datos del motor 2.");
        free(motor_n1);
        fclose(motor2);
        return 1;
    }
    fseek(motor2,0,SEEK_SET);
    for(int i=0; i<cantidad_grupos2; i++)
    {
        fread(&motor_n2[i].tension, sizeof(double), 1, motor2);
        fread(&motor_n2[i].corriente, sizeof(double), 1, motor2);
        fread(&motor_n2[i].tiempo, sizeof(double), 1, motor2);
    }
    fclose(motor2);

    //por ultimo hago lo mismo para el tercer motor
    FILE *motor3 = fopen("motor3.dat","rb");
    if(!motor3)
    {
        printf("\nerror: no se pudo abrir archivos del motor 3.");
        free(motor_n1); 
        free(motor_n2);
        return 1;
    }
    fseek(motor3,0,SEEK_END);
    long contenido_motor3 = ftell(motor3);
    int cantidad_doubles3= contenido_motor3/sizeof(double);
    int cantidad_grupos3 = cantidad_doubles3/3;

    printf("\nla cantidad de registros del motor 3 es: %d", cantidad_grupos3); 
    datos *motor_n3 = malloc(cantidad_grupos3*sizeof(datos));
    if(motor_n3== NULL)
    {
        printf("\nerror: no se pudo reservar memoria para guardar datos del motor 3.");
        free(motor_n1);
        free(motor_n2);
        fclose(motor3);
        return 1;
    }
    fseek(motor3,0,SEEK_SET);
    for(int i=0; i<cantidad_grupos3; i++)
    {
        fread(&motor_n3[i].tension, sizeof(double), 1, motor3);
        fread(&motor_n3[i].corriente, sizeof(double), 1, motor3);
        fread(&motor_n3[i].tiempo, sizeof(double), 1, motor3);
    }
    fclose(motor3);

    //ya tengo los tres vectores armados, ahora puedo hacer lo que quiera con ellos
    //motor_n1[i], motor_n2[i], motor_n3[i] y tengo cantidad_grupos1/2/3 como contadores para recorrerlos

    //voy a calcular la potencia activa y la potencia aparente en un procedimiento
    double P1, P2, P3;
    double S1, S2, S3; //luego voy a comparar estas variables
    int numero1=1;
    int numero2=2;
    int numero3=3;//es re tonto, pero lo hago porque me sirve dentro del void
    potencias(motor_n1, cantidad_grupos1, &P1, &S1, numero1); 
    potencias(motor_n2, cantidad_grupos2, &P2, &S2, numero2); 
    potencias(motor_n3, cantidad_grupos3, &P3, &S3, numero3); 

    //por ultimo me queda buscar el motor que tenga el mayor valor de P y al mismo tiempo el menor valor de S 
    int motor_mas_eficiente; //el que tenga mayor P y menor S
    //si el enunciado me pide el mayor valor de P y al mismo tiempo el menor valor de S, al compilar el codigo me di cuenta de que 
    //no hay uno en especifico, pero tambien vi que los valores por cada motor andan en numeros medios parecidos, pero entre motores cambia mucho
    //vi que hay un motor con numeros bajos, otro con numeros intermedios y otro con valores altos (para S y P)
    //entonces lo correcto seria tomar el motor con los valores intermedios

    //para no dar tantas vuelta pienso en hacer lo siguiente, sumar los P y S de cada motor, y comparar esos valores
    double suma1= P1+S1;
    double suma2 =P2+S2;
    double suma3= P3+S3;

    //voy a buscar los maximos y minimos para descartalos
    double max, min, intermedio;

    if(suma1<suma2&&suma1<suma3)
    {
        min=suma1; //descarto a suma1
        if(suma2>suma3){
            max=suma2; //descarto a suma2
            intermedio=suma3;
        }else if(suma3>suma2){
            max=suma3;//descarto a suma3
            intermedio=suma2;
        }
    }else if(suma2<suma1&&suma2<suma3){
        min=suma2; //descarto a suma2
        if(suma1>suma3){
            max=suma1;//descarto suma1
            intermedio=suma3;
        }else if(suma3>suma1){
            max=suma3;//descarto suma3
            intermedio=suma1;
        }
    }else if(suma3<suma1&&suma3<suma2){
        min=suma3;//descarto a suma3
        if(suma2>suma1){
            max=suma2;//descarto suma2
            intermedio=suma1;
        }else if(suma1>suma2){
            max=suma1; //descarto suma1
            intermedio=suma2;
        }
    }

    if(P1+S1==intermedio){
        printf("\nel motor que cumple la condicion es el motor 1.");
    }else if(P2+S2==intermedio){
        printf("\nel motor que cumple la condicion es el motor 2.");
    }else if(P3+S3==intermedio){
        printf("\nel motor que cumple la condicion es el motor 3.");
    }



    free(motor_n1);
    free(motor_n2);
    free(motor_n3);
    printf("\nel programa cerro con exito");
    return 0;
}