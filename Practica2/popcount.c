//Patricia Córdoba Hidalgo
//2º DGIIM

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE (1<<16)	// tamaño suficiente para tiempo apreciable
unsigned lista[SIZE];
int resultado=0;

int popcountv1(unsigned *array, int len){

  int k,j;
  int result=0;     //nº de bits activados del array

  for(j=0; j<len; j++){        //recorre el array
    for(k=0; k<32;k++){        //recorre los bits de un elemento del array
      unsigned mask=1<<k;      //crea una máscara con un 1 en la posición del bit a comprobar si está activado
      result+=(array[j] &mask) !=0;  //guarda en resultado 1 si el bit de la pos. k está activado y 0 si no
    }
  }
  return result;  //devuelve el resultado (nº de unos del array)
}

int popcountv2(unsigned *array, int len){
  int j;
  int result=0;    //nº de bits activados del array

  for(j=0; j<len; j++){
    unsigned mask= array[j];  //la máscara es el elemento del array sobre el que operamos
    do{
      result+=(mask &0x1)!=0; //resultado almacena 1 si el último bit está activado, 0 si no
      mask>>=1;               //desplaza mask a la derecha
    } while (mask);           //realiza la operación hasta que la máscara sea 0
  }
  return result;   //devuelve el resultado (nº de unos del array)
}

int popcountv3(unsigned *array, int len){
  int j;
  int result=0;   //nº de bits activados del array

  for(j=0; j<len; j++){   //recorre el array
    unsigned x= array[j]; //x es el elemento del array sobre el que operamos
    asm("\n"  //código ensamblador
	"init3:       \n\t"  //inicio del bucle
	"shr %[x]     \n\t"  //desplaza a la derecha x 1 bit
	"adc $0, %[r] \n\t"  //suma el acarreo originado al desplazar x a resultado
	"cmp $0, %[x] \n\t"  //compara x con 0
	"jne init3"          //si x no es 0, vuelve al bucle
	
	:[r]"+r" (result)    //r es resultado (entrada y salida)
	:[x] "r" (x)         //x es x (entrada)
	);
  }
  return result;     //devuelve el resultado (nº de unos del array)
}

int popcountv4(unsigned *array, int len){
  int val = 0;
  int result=0;   //nº de bits activados del array
  int i,j;
  
  for (j=0; j<len; j++){         //recorre el array
    unsigned mask= array[j];     //mask es el elemento del array sobre el que operamos
    val=0;                       //inicializa val a 0
    for (i = 0; i < 8; i++) {    //opera sobre los 8 bits de cada bloque
      val += mask & 0x01010101;  //aplica un máscara donde solo deja activo el último bit de cada bloque
      mask >>= 1;                //desplaza la máscara 1 bit
    }
    val += (val >> 16);          //suma el 1º con el 3º bloque, y el 2º con el 4º bloque
    val += (val >> 8);           //suma el resultado del 1º y 3º bloque con el del 2º y 4º bloque
    result+= val & 0x1f;         //el resultado final son los 5 últimos bits
  }
  return result;   //devuelve el resultado (nº de unos del array)
}

int popcountv5(unsigned *array, int len){
  int i;
  int val, result = 0;
  int SSE_mask[] = {0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f};  //máscara que deja activa la parte menos significativa de cada byte
  int SSE_LUTb[] = {0x02010100, 0x03020201, 0x03020201, 0x04030302};  //cada byte almacena el nº de 1s de los números del 1 al 15 en binario

  for(i = 0; i < len; i += 4){   //recorre el array
    asm("movdqu %[x], %%xmm0       \n\t"
	"movdqa %%xmm0, %%xmm1     \n\t" // dos copias de x
	"movdqu %[m], %%xmm6       \n\t" // máscara
	"psrlw $4, %%xmm1          \n\t" 
	"pand %%xmm6, %%xmm0   \n\t" //; xmm0 - nibbles inferiores
	"pand %%xmm6, %%xmm1   \n\t" //; xmm1 -nibbles superiores

	"movdqu %[l], %%xmm2       \n\t" //; ...como pshufb sobrescribe LUT
	"movdqa %%xmm2, %%xmm3     \n\t" //; ...queremos 2 copias
	"pshufb %%xmm0, %%xmm2 \n\t" //; xmm2 = vector popcount inferiores
	"pshufb %%xmm1, %%xmm3 \n\t" //; xmm3 = vector popcount superiores

	"paddb   %%xmm2, %%xmm3 \n\t"  //xmm3 - vector popcount bytes
	"pxor    %%xmm0, %%xmm0 \n\t"  //xmm0= 0, 0, 0, 0
	"psadbw  %%xmm0, %%xmm3 \n\t"  //xmm3= [pcnt bytes..7|pcnt bytes8..15]
	"movhlps %%xmm3, %%xmm0 \n\t"  //xmm3= 0|pcnt bytes0..7]
	"paddd   %%xmm3, %%xmm0 \n\t"  //xmm3= [no usado|pcnt bytes0..15]
	"movd    %%xmm0, %[val] \n\t"
	: [val] "=r" (val)        //registro de salida
	: [x] "m" (array[i]),     //operando de memoria
	  [m] "m" (SSE_mask[0]),  //operando de memoria
	  [l] "m" (SSE_LUTb[0])   //operando de memoria
	);
    result += val;
  }
  return result;  //devuelve el resultado (nº de unos del array)
}

int popcountv6(unsigned *array, int len){
  int i;
  unsigned x;
  int val, result=0;

  for (int i=0; i<len; i++){  //recorre el array
    x=array[i];               //x es el elemento del array sobre el que operamos
    asm("popcnt %[x], %[val]" //la función calcula el nº de bits activos de el número entero x, y lo guarda en variable
	:[val]"=r" (val)
	:[x]"r"(x)
    );
    result+=val;
  }
  return result; //devuelve el resultado (nº de unos del array)
}

int popcountv7(unsigned *array, int len){
  int i;
  unsigned x1, x2;
  int val, result=0;


  if(len & 0x1) //comprueba que la longitud del vector sea un número par
    printf("leer 64b y len impar?\n");
  for (int i=0; i<len; i+=2){ //recorre el array seleccionando 2 elementos a la vez
    x1=array[i];
    x2=array[i+1];
    asm("popcnt %[x1], %[val] \n\t" //calcula el nº de bits activos de el número entero x1, y lo guarda en variable
	"popcnt %[x2], %%edi \n\t"  //calcula el nº de bits activos de el número entero x2, y lo guarda en %edi
	"add %%edi, %[val] \n\t"    //suma los valores de %edi y variable
	:[val]"=&r" (val)  //registro de salida
	:[x1]"r"(x1),      //elemento sobre el que se opera
	 [x2]"r"(x2)       //elemento sobre el que se opera
	:"edi"             //registro
    );
    result+=val;
  }
  return result;   //devuelve el resultado (nº de unos del array)
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

    crono(popcountv1, "Versión 1");
    crono(popcountv2, "Version 2");
    crono(popcountv3, "Version 3");
    crono(popcountv4, "Version 4");
    crono(popcountv5, "Version 5");
    crono(popcountv6, "Version 6");
    crono(popcountv7, "Version 7");

    exit(0);
}
