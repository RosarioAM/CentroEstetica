#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <string.h>

struct fecha
{
	int dd,mm,aaaa;	
};
struct turnos
{
	int IdProfesional; 
	fecha Fecha;
	int DniCliente;
	char DetalledeAtencion [380];
	int atendido;
};
struct datosusuario
{
	char Usuario [10];
	char Contra [10];
	char Apenomusuario [60];		
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
void ListadodeAtenciones()
{
	FILE *arch5;
	
	turnos regt;
	
   arch5=fopen("Turnos.dat","rb");
   fread(&regt,sizeof(turnos),1,arch5);
	
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t** INICIO DE LISTADO **");
	printf("\n\t\t************************************************************");	
	
	while (!feof(arch5))
	{		
		printf("\n\t\tIDENTIFICACION PERSONAL DEL PROFESIONAL: [%d]",regt.IdProfesional);
							
		printf("\n\t\tFECHA DEL TURNO: [%d/%d/%d]", regt.Fecha.dd,regt.Fecha.mm,regt.Fecha.aaaa);
		
		printf("\n\t\tDNI DEL CLIENTE: [%d]", regt.DniCliente);	
		

		fread(&regt,sizeof(turnos),1,arch5);

	}
	fclose(arch5);
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t** F I N D E L L I S T A D O **");
	printf("\n\t\t************************************************************");
	printf("\n\n\t\t");
	
	fclose(arch5); 

};	
void registrarTurno()
{
	FILE *arch5;
	
	turnos regt;
	
	arch5=fopen("Turnos.dat","a+b");		
	
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t**REGISTRAR TURNO**");
	printf("\n\t\t************************************************************");
	printf("\n\n");
		
	printf("\n\t\tIDENTIFICACION PERSONAL DEL PROFESIONAL:");
	scanf("%d",&regt.IdProfesional);		
	
	printf("\n\t\tINGRESE LA FECHA DEL TURNO");
	
	printf("\n\t\t\tDIA:");
	scanf("%d",&regt.Fecha.dd);
	
	printf("\n\t\t\tMES:");
	scanf("%d",&regt.Fecha.mm);
	
	printf("\n\t\t\tANO:");
	scanf("%d",&regt.Fecha.aaaa);	
		
	printf("\n\t\t\tDNI DEL CLIENTE:");
	scanf("%d",&regt.DniCliente);	
								
	regt.atendido=0;

	
	fwrite(&regt,sizeof(turnos),1,arch5);	
	
	fclose(arch5); 
					
	printf("\n\n");
	printf("\n\t\t***********************************************************");
	printf("\n\t\t**EL TURNO SE ENCUENTRA CORRECTAMENTE REGISTRADO**");
	printf("\n\t\t***********************************************************");
	printf("\n\n\t");
	system("PAUSE");
		
	
	system("CLS");		
			
		
};

void registrarClientes()
{
	FILE *arch3;
	
	datoscliente regc;
	
	arch3=fopen("Clientes.dat","a+b");		
	
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t**INGRESE LOS DATOS DEL CLIENTE**");
	printf("\n\t\t************************************************************");
	printf("\n\n");
					
	_flushall(); 
	printf("\n\t\tNOMBRE Y APELLIDO:");
	gets(regc.ApeNomC); 				
	
	
	_flushall(); 
	printf("\n\t\tDOMICILIO:");
	gets(regc.DomicilioC); 	
																		
	printf("\t\tDNI:");
	scanf("%d",&regc.DniCliente);		

	_flushall(); 
	printf("\n\t\tLOCALIDAD:");
	gets(regc.LocalidadC); 	
	
	printf("\n\t\tINGRESE SU FECHA DE NACIMIENTO");
	
	printf("\n\t\t\tDIA:");
	scanf("%d",&regc.FechadeNacC.dd);
	
	printf("\n\t\t\tMES:");
	scanf("%d",&regc.FechadeNacC.aaaa);
	
	printf("\n\t\t\tANO:");
	scanf("%d",&regc.FechadeNacC.aaaa);	
	
	printf("\t\tPESO:");
	scanf("%f",&regc.peso);		
									
	_flushall(); 
	printf("\t\tTELEFONO:");
	gets(regc.TelefonoC); 	
				
	fwrite(&regc,sizeof(datoscliente),1,arch3);
				
	printf("\n\n");
	printf("\n\t\t***********************************************************");
	printf("\n\t\t**EL CLIENTE SE ENCUENTRA CORRECTAMENTE REGISTRADO**");
	printf("\n\t\t***********************************************************");
	printf("\n\n\t");
	system("PAUSE");
	
	system("CLS");		
			
	fclose(arch3); 	
		
};
void menur()
{
	int opcion;
	do
	{
		printf("\n\t\tM\242dulo del recepcionista\n");
		printf("\n\t\t==============================\n");
		printf("\t\t[1].Registrar Cliente.\n");
		printf("\t\t[2].Registrar Turno.\n");
		printf("\t\t[3].Listado de Atenciones por Profesional y Fecha.\n");
		printf("\t\t[4].Volver al men\243 principal.\n");	
		
		printf("\n\t\tIngrese una opci\242n:");
		scanf("%d",&opcion);	
		
		system("CLS");
				
		switch(opcion)
		{
			case 1:
				registrarClientes();
			break;
			
			case 2:
				registrarTurno();
			break;
			
			case 3:
				ListadodeAtenciones();
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
	datosusuario regu;
	FILE *arch1;
	do
	{							
		_flushall(); 
		printf("\n\t\tUSUARIO:");
		gets(user);
		
						
		_flushall(); 
		printf("\n\t\tCONTRASENA:");
		gets(password);	
		
		i=i+1;
			
		arch1=fopen("Recepcionistas.dat","rb");
		
		fread(&regu,sizeof(datosusuario),1,arch1);
		
		rewind(arch1);

		while (!feof(arch1) and e==0) 
		{
			valor=strcmp(user,regu.Usuario);
			valor2=strcmp(password,regu.Contra);
			if(valor==0 and valor2==0)
			{
				e=1;
				printf("si existe");
				
			}
			else
			{
				e=0;
			}
			fread(&regu,sizeof(datosusuario),1,arch1);		
		}	
	
		fclose(arch1);	
		
	}			
	while(i<3 and e==0);		
	
	if(e==0)
	{
		printf ("\n\n\n\t\tIntento 3 veces. Pruebe mas tarde");
		system("Pause");
		system("CLS");
	}
	if(e==1)
	{
		printf("EL NOMBRE DE USUARIO Y CONTRASEÑA SON CORRECTOS");
		menur();
	}

};
main()
{

	
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t** INGRESO AL MENU RECEPCIONISTA **");
	printf("\n\t\t************************************************************");	
		
	login();
		 

}


