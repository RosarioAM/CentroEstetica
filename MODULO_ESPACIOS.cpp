#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <string.h>
#include <time.h>
struct fecha
{
	int dd,mm,aaaa;	
};
struct datoscliente
{
	char ApeNomC [60];	
	char DomicilioC [60];
	int DniCliente;	
	char LocalidadC [60];	
	fecha FechadeNacC;
	float peso;
	char TelefonoC [15];  
};
struct turnos
{
	int IdProfesional; 
	fecha Fecha;
	int DniCliente;
	char DetalledeAtencion [380];
	int atendido;
};
struct datosprofesional
{
	char Apenompro [60];
	int Idpro;
	int DNIpro;
	char Telefonopro [25];
	char contra [10];
	char usuario [10];
	int PR;
};
struct datosusuario
{
	char Usuario [10];
	char Contra [10];
	char Apenomusuario [60];		
};
void listadoEvolucionClientes(int idprofesional)
{
	int dnic,ban=0;
	char nombrepro[60];
	char nombrecliente[60];
	
	printf("\n\t\tINGRESE EL DNI DEL CLIENTE DEL QUE DESEA VER SU INFORME DE EVOLUCION:");
	scanf("%d",&dnic);
	
	FILE *arch5;
	
	turnos regt;
		
	arch5=fopen("Turnos.dat","a+b");	   
	fread(&regt,sizeof(turnos),1,arch5);
	rewind(arch5);	
		
	while (!feof(arch5) or ban==1)
	{
		if(dnic==regt.DniCliente and regt.atendido==1)	
		{
			ban==1;
			
			
		}
		fread(&regt,sizeof(turnos),1,arch5);
	}
	fclose(arch5);
	
	if(ban!=1)
	{
		printf("\n\t\tNO EXISTE EL INFOME DE EVOLUCION O EL CLIENTE.");
	}

	if(ban==1)
	{
		FILE *arch;
	
		datosprofesional regp;
			
		arch5=fopen("Profesionales.dat","rb");
			   
		fread(&regp,sizeof(datosprofesional),1,arch);
		
		while (!feof(arch))
		{
			if(idprofesional==regp.Idpro)
			{
				strcpy(nombrepro, regp.Apenompro);
			}
			fread(&regp,sizeof(datosprofesional),1,arch);
		}
		fclose(arch);
		
		
		FILE *arch3;
	
		datoscliente regc;
	
		arch3=fopen("Clientes.dat","rb");
		
		fread(&regc,sizeof(datoscliente),1,arch3);
		
		while (!feof(arch3))
		{
			if(dnic==regc.DniCliente)
			{
				strcpy(nombrecliente, regc.ApeNomC);
			}
			fread(&regc,sizeof(datoscliente),1,arch3);
		}
		fclose(arch3);
	
		FILE *arch5;
	
		turnos regt;
			
		arch5=fopen("Turnos.dat","a+b");	   
		fread(&regt,sizeof(turnos),1,arch5);
		rewind(arch5);
		   
		
			
		while (!feof(arch5))
		{
			if(dnic==regt.DniCliente and regt.atendido==1)	
			{								
				printf("\n\n");
				printf("\n\t\t*********************************************");
				printf("\n\t\t***** INFORME DE EVOLUCION DEL PACIENTE *****");
				printf("\n\t\t*********************************************\n\n");
				
				printf("\n\t\t---------------------------------------\n");	
				printf("\n\t\t|NOMBRE DEL CLIENTE|FECHA DEL TURNO|PROFESIONAL QUE LO ATENDIO|\n");
				printf("\n\t\t---------------------------------------\n");
				printf("\n\t\t|%s                 |%d/%d/%d      |%s                |\n",nombrecliente,regt.Fecha.dd,regt.Fecha.mm,regt.Fecha.aaaa,nombrepro);
				printf("\n\t\t---------------------------------------\n");
			}
	
		}
		fclose(arch5);
	}
	
}
void atendidos()
{
	char ApeNomC [60];
	int dniCliente,ban=0;
	
	_flushall(); 
	printf("\n\t\tINGRESE EL NOMBRE Y APELLIDO DEL CLIENTE A ATENDER:");
	gets(ApeNomC); 
	strupr(ApeNomC);	
	
	FILE *arch3;
	
	datoscliente regc;
	
	arch3=fopen("Clientes.dat","rb");
	
	fread(&regc,sizeof(datoscliente),1,arch3);
	
	while (!feof(arch3))
	{
		strupr(regc.ApeNomC);
		
		if(strcmp(ApeNomC,regc.ApeNomC)==0)
		{
			dniCliente=regc.DniCliente;
			
			ban=1;
			/*printf("si existe");*/
		}

		fread(&regc,sizeof(datoscliente),1,arch3);	
	}
	
	fclose(arch3);
	
	if(ban!=1)
	{
		printf("\n\t\tEL CLIENTE NO EXISTE");
	}
	
	if(ban==1)
	{
		FILE *arch5;
	
		turnos regt;
		
		arch5=fopen("Turnos.dat","a+b");
		
		rewind(arch5);
		
	   fread(&regt,sizeof(turnos),1,arch5);
	   
	   
	
	
		 while (!feof(arch5))
	  	{
	
	  		if(dniCliente==regt.DniCliente)
	   	{
	   		
	   		printf("\n\n");
				printf("\n\t\t*********************************************");
				printf("\n\t\t***** REGISTRE LA EVOLUCION DEL PACIENTE *****");
				printf("\n\t\t*********************************************\n\n");	
				
	   		_flushall(); 
				printf("\n\t\tDETALLE DE ATENCION:");
				gets(regt.DetalledeAtencion); 		
				
				regt.atendido=1;
				
				fwrite(&regt,sizeof(turnos),1,arch5);
				
				printf("\n\n");
				printf("\n\t\t*********************************************");
				printf("\n\t\t***** EVOLUCION DEL PACIENTE REGISTRADA *****");
				printf("\n\t\t*********************************************\n");
				
				/*printf("%s %d",regt.DetalledeAtencion,regt.atendido);*/
			}
			
			
			
			fread(&regt,sizeof(turnos),1,arch5);
			
				
			
		}
	
		fclose(arch5);
			
	}
	system("\nPause");
	system("CLS");

};
void ListadodeTurnos (int idprofesional)
{
	time_t t;
	struct tm *tm;
  
 	char mes[100];
  	char anio[100];
  	char dia [100];
	int mesennumero;
 	int anioennumero;
 	int diaennumero;
 	int ban=0;
 	
 	
	t=time(NULL);
	tm=localtime(&t);
	 
 	strftime(dia, 100, "%d", tm);
	strftime(mes, 100, "%m", tm);
  	strftime(anio, 100, "%Y", tm);
  	sscanf(dia, "%d", &diaennumero);
	sscanf(mes, "%d", &mesennumero);
	sscanf(anio, "%d", &anioennumero);

	FILE *arch5;
	
	turnos regt;
	
   arch5=fopen("Turnos.dat","rb");
   
   fread(&regt,sizeof(turnos),1,arch5);	  	
	
	
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t************** LISTA DE ESPERA **************");
	printf("\n\t\t*********************************************");	
	
	while (!feof(arch5) )
	{
		if(regt.IdProfesional==idprofesional)		
		{
			if(regt.atendido!=1)
			{
				if(diaennumero<regt.Fecha.dd and mesennumero<=regt.Fecha.mm and anioennumero<=regt.Fecha.aaaa)
				{			
					printf("\n\t\t---------------------------------------\n");	
					printf("\n\t\t|DOCUMENTO DEL CLIENTE|FECHA DEL TURNO|\n");
					printf("\n\t\t---------------------------------------\n");
					printf("\n\t\t|%d                 |%d/%d/%d      |\n",regt.DniCliente,regt.Fecha.dd,regt.Fecha.mm,regt.Fecha.aaaa);
					printf("\n\t\t---------------------------------------\n");
					
					ban=1;
				}	
			}
			
		}
	
		
		fread(&regt,sizeof(turnos),1,arch5);	
	}
	fclose(arch5);
	
	if(ban!=1)
	{
		printf("\n\t\tNO TIENE NINGUN TURNO POR ATENDER.");
	}
	printf("\n\t\t*********************************************");
	printf("\n\t\t**************  FIN DEL LISTADO **************");
	printf("\n\t\t*********************************************");
	printf("\n\n\t\t");
	
	
	
	system("\nPause");
	system("CLS");
	

	
	
};	
void menup(int idprofesional)
{
	int opcion,registrar;
	
	do
	{
		printf("\n\t\t\t\tMODULO ESPACIOS\n");
		printf("\t\t\t\t===============\n");
		printf("\t\t[1]. VISUALIZAR LISTA DE ESPERA DE TURNOS (INFORME).\n");
		printf("\t\t[2]. REGISTRAR EVOLUCION DEL TRATAMIENTO.\n");
		printf("\t\t[3]. VISUALIZAR EVOLUCION DE UN CLIENTE.\n");
		printf("\t\t[4]. VOLVER AL MENU PRINCIPAL.\n");
		
		
		printf("\n\t\tSELECCIONE UNA OPCION:");	
		scanf("%d",&opcion); 
		
		system("CLS");
		
		switch(opcion)
		{
			case 1:
				ListadodeTurnos(idprofesional);
			break;
			
			case 2:
				printf("\n\t\tDESEA REGISTRAR LA EVOLUCION DE ALGUN PACIENTE?\n");
				printf("\t\tSeleccione [1] para aceptar y [2] para salir.\n");
				
				printf("\n\t\tSELECCIONE UNA OPCION:");
				scanf("%d",&registrar);
				
				printf("\n\n\t\t");
		
				system("\nPause");
				system("CLS");
		
				if(registrar==1)
				{
					atendidos();
				}
				
			break;
			
			case 3:
				listadoEvolucionClientes(idprofesional);
			break;				
				
		}
	}	
	while(opcion<4);

};
void login()
{
	char user [10];
	char password [32];
	int valor,valor2,e=0,i=0;
	datosprofesional regp;
	int idprofesional=0;
	FILE *arch;
	do
	{							
		_flushall(); 
		printf("\n\t\tUSUARIO:");
		gets(user);
		
						
		_flushall(); 
		printf("\n\t\tCONTRASENA:");
		gets(password);	
		
		i=i+1;
			
		arch=fopen("Profesionales.dat","rb");
		
		fread(&regp,sizeof(datosprofesional),1,arch);
		
		rewind(arch);

		while (!feof(arch) and e==0) 
		{
			valor=strcmp(user,regp.usuario);
			valor2=strcmp(password,regp.contra);
			if(valor==0 and valor2==0)
			{
				e=1;
				
				idprofesional=regp.Idpro;
				
			}
			else
			{
				e=0;
			}
			fread(&regp,sizeof(datosprofesional),1,arch);		
		}	
	
		fclose(arch);	
		
	}			
	while(i<3 and e==0);		
	
	if(e==0)
	{
		printf ("\n\n\n\t\tIntento 3 veces. Pruebe mas tarde");
		system("\nPause");
		system("CLS");
	}
	if(e==1)
	{
		system("CLS");
		
		printf("\n\n");
		printf("\n\t\t*************************************************************");
		printf("\n\t\t****** EL NOMBRE DE USUARIO Y CONTRASENA SON CORRECTOS ******");
		printf("\n\t\t*************************************************************");	
		printf("\n\n");
		
		system("\n\nPAUSE");
		
		system("CLS");
		
		menup(idprofesional);
		
		printf("\n\n\t\t");
		
		system("\nPause");
		system("CLS");
	}

};
main()
{
		printf("\n\t\t*********************************************");
		printf("\n\t\t******** INGRESAR AL MODULO ESPACIOS ********");
		printf("\n\t\t*********************************************");
		printf("\n\n\t\t");
				
		login();
				
		system("\nPAUSE");
				
		system("CLS");
}
