//Patricia Córdoba Hidalgo
//Password: t...t...
//Código: 4444

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char password[]="La contraseña es incorrecta\n";
char time[]="¡Se acabó el tiempo!";
char passcode[]="El código es incorrecto\n";
char lalala[]="";

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("·························\n");
	printf("··· bomba desactivada ···\n");
	printf("·························\n");
	exit(0);
}

int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 60
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	int code = 2020;
	
	gettimeofday(&tv1,NULL);

	for(int i=0; i<2; i++){
	  strcat(lalala,"t");
	  strcat(lalala, "...");
	  }

	strcat(lalala, "\n");

	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);
	if (strncmp(pass,lalala,strlen(lalala))){
	  printf("%s",password);
	  boom();
	}

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM){
	  printf("%s",time);
	  boom();
	}
	
	code+=2414;

     	for(int i=0; i<10; i++){
	  code+=1;
	}
	
	printf("Introduce el código: ");
	scanf("%i",&pasv);
	if (pasv!=code){
	  printf("%s", passcode);
	  boom();
	}

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM){
	  printf("%s",time);
	  boom();
	}
	
	defused();
}
