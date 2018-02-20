//Patricia Córdoba Hidalgo
//2º DGIIM

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE (1<<16)	// tamaño suficiente para tiempo apreciable
unsigned lista[SIZE];
int resultado=0;

int paridadv1(unsigned *array, int len){

  int i,j, val;
  int result=0;     //nº de bits activados del array
  unsigned dato;
  
  for(i=0; i<len; i++){        //recorre el array
    dato=array[i];             //dato es el elemento del array sobre el que operamos
    val=0;
    for(j=0; j<32; j++){        //recorre los bits de un elemento del array
      val^=(dato & 0x1);        //guardamos el XOR de dato AND 0x1 (guarda 1 si el último bit de dato es 1, 0 en caso contrario)
      dato >>=1;                //desplaza 1 bit dato
    }
    result+=val;   //suma 1 si el nº es impar, 0 en caso contrario
  }
  return result;  //devuelve nº de elementos impares del array
}

int paridadv2(unsigned *array, int len){

  int i, val;
  int result=0;     //nº de bits activados del array
  unsigned dato;
  
  for(i=0; i<len; i++){        //recorre el array
    dato=array[i];             //dato es el elemento del array sobre el que operamos
    val=0;
    while(dato!=0){        //mientras que dato sea distinto de 0
      val^=(dato & 0x1);   //guardamos el XOR de dato AND 0x1 (guarda 1 si el último bit de dato es 1, 0 en caso contrario)
      dato >>=1;           //desplaza 1 bit dato
    }
    result+=val;  //suma 1 si el nº es impar, 0 en caso contrario
  }
  return result;  //devuelve nº de elementos impares del array
}

int paridadv3(unsigned *array, int len){

  int result=0;
  int i, val=0;
  unsigned dato;
  for(i=0; i<len; i++){        //recorre el array
    dato=array[i];             //dato es el elemento del array sobre el que operamos
    val=0;
    while(dato){        //mientras que dato sea distinto de 0
      val^=dato;        //guardamos el XOR de dato y val
      dato>>=1;         //desplaza 1 bit dato
    }
    result+=(val & 0x1);  //guarda 1 si el último bit de dato es 1, 0 en caso contrario
  }
  return result;  //devuelve nº de elementos impares del array
}

int paridadv4(unsigned *array, int len){

  int result=0;
  int i, val=0;
  unsigned dato;

  for(i=0; i<len; i++){        //recorre el array
    dato=array[i];             //dato es el elemento del array sobre el que operamos
    val=0;
    asm("\n"
	"ini3:   \n\t"  //seguir mientras x!=0
	"xor %[x], %[v] \n\t"  //realmente solo nos interesa LSB
	"shr $1, %[x] \n\t"    //desplaza el dato un bit a la derecha
	"cmp $0, %[x] \n\t"    //compara 0 con x
	"jne ini3  \n\t"       //si x!=0, vuelve a ini3(bucle)
	"and $0x1, %[v] \n\t"

	:[v]"+r" (val)     //e/s: entrada 0, salida paridad elemento
	:[x]"r" (dato)     //entrada: valor elemento
	);
    result+=val;  //suma 1 si el nº es impar, 0 en caso contrario
  }
  return result;  //devuelve nº de elementos impares del array
}

int paridadv5(unsigned *array, int len){
  int result=0;
  int i, j;
  unsigned dato;

  for(i=0; i<len; i++){        //recorre el array
    dato=array[i];             //dato es el elemento del array sobre el que operamos
    for(j=16; j>0; j/=2){      
      dato^=dato>>j;           //desplaza dato j bits y hace un XOR con su valor inicial. 
    }
    result+=(dato & 0x1);   //guarda 1 si el último bit de dato es 1, 0 en caso contrario
  }
  return result;  //devuelve nº de elementos impares del array
}

int paridadv6(unsigned *array, int len){
  int result=0;
  int i, j;
  unsigned dato;

  for(i=0; i<len; i++){
    dato=array[i];
    asm(
	"mov %[x], %%edx   \n\t"  //sacar copia para XOR. Controlar el registro
	"shr $16, %[x] \n\t"      //desplaza 16 bits a la derecha el dato
	"xor %[x], %%edx \n\t"    //hace un xor del dato, guardado en edx, y el dato desplazado
	"xor %%dh, %%dl \n\t"     //hace xor entre los 2 registros de 8 bits que hay en edx
	"setpo %%dl \n\t"         //paridad de los 8 bits (PF=0 si la paridad es impar)
	"movzx %%dl, %[x]  \n\t"  //devolver en 32 bits
	:[x]"+r" (dato)           //e/s: entrada valor elemento, salida paridad
	:
       	:"edx"  //clobber
    );
    result+=dato;
  }
  return result;  //devuelve nº de elementos impares del array
}

void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
}

int main()
{
    int i;			// inicializar array
    for (i=0; i<SIZE; i++)	// se queda en cache
	 lista[i]=i;

    crono(paridadv1, "Versión 1");
    crono(paridadv2, "Versión 2");
    crono(paridadv3, "Versión 3");
    crono(paridadv4, "Versión 4");
    crono(paridadv5, "Versión 5");
    crono(paridadv6, "Versión 6");
    

    exit(0);
}
