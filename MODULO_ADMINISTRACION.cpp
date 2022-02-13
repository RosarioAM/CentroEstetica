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
int comprobarusuario(char vUsuario[10],datosusuario regu,int &r);
int comprobarcontra(char vContra[32],datosusuario regu,int &rc);
int comprobarusuarioP(char vusuariop[10],datosprofesional regp,int &r);
int comprobarcontraP(char vcontrap[32],datosprofesional regp,int &rc);

void ranking()
{
	

	time_t t;
	struct tm *tm;
  
 	char mes[100];
  	char anio[100];
	int mesennumero;
 	int anioennumero;
 	
	t=time(NULL);
	tm=localtime(&t);
	strftime(mes, 100, "%m", tm);
  	strftime(anio, 100, "%Y", tm);
/*	printf ("mes: %s\n", fechayhora);	*/
	sscanf(mes, "%d", &mesennumero);
	sscanf(anio, "%d", &anioennumero);
	
	int prm = 0;
	int idProfesionalVa;
	
	FILE *arch5;
	
	turnos regt;
	
   arch5=fopen("Turnos.dat","rb");
	
	rewind(arch5); //Ubica el puntero en el primer registro del archivo.
 	fread(&regt, sizeof(regt), 1, arch5); //Lee el primer registro.
	idProfesionalVa = regt.IdProfesional;
	
	while(!feof(arch5))//Repetir hasta el último registro.

	{
		if(mesennumero==regt.Fecha.mm and anioennumero==regt.Fecha.aaaa)
		{
			
		
				
			if(idProfesionalVa ==regt.IdProfesional)
			{
				prm = prm + 1;	
				idProfesionalVa = regt.IdProfesional;
			}
						
				fread(&regt,sizeof(regt),1,arch5);
			
				
		}
		fread(&regt,sizeof(turnos),1,arch5);
	
	}
   
	fclose(arch5); 

	printf("\n\t\tIDENTIFICACION PERSONAL DEL PROFESIONAL QUE MAS ATENCIONES DIO EN EL MES Y AL CUAL SE LE OTORGARA EL BONO: [%d]\n",idProfesionalVa);
	system("\nPAUSE");
	
}

void atenciones()
{

	
	time_t t;
	struct tm *tm;
  
 	char mes[100];
  	char anio[100];
	int mesennumero;
 	int anioennumero;
 	int ban=0;
 	
	t=time(NULL);
	tm=localtime(&t);
	strftime(mes, 100, "%m", tm);
  	strftime(anio, 100, "%Y", tm);
/*	printf ("mes: %s\n", fechayhora);	*/
	sscanf(mes, "%d", &mesennumero);
	sscanf(anio, "%d", &anioennumero);

	  	
	FILE *arch5;
	
	turnos regt;
	arch5=fopen("Turnos.dat","rb");
   fread(&regt,sizeof(turnos),1,arch5);
	
	printf("\n\n");
	printf("\n\t\t**********************************************");
	printf("\n\t\t************* INICIO DEL LISTADO *************");
	printf("\n\t\t**********************************************");	
	
	while (!feof(arch5))
	{		
		if(mesennumero==regt.Fecha.mm and anioennumero==regt.Fecha.aaaa)
		{
			printf("\n\t\tIDENTIFICACION PERSONAL DEL PROFESIONAL: [%d]",regt.IdProfesional);
			
			printf("\n\t\tATENDIO EN LAS SIGUIENTES FECHAS:");	
			printf("\n\t\t=================================");			
			printf("\n\t\t[%d/%d/%d]", regt.Fecha.dd,regt.Fecha.mm,regt.Fecha.aaaa);
			
			ban=1;

		}

		fread(&regt,sizeof(turnos),1,arch5);	
	}
	
	if(ban!=1)
	{
		printf("\n\t\tESTA VACIO.");
	}
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t************** FIN DEL LISTADO **************");
	printf("\n\t\t*********************************************");	
	printf("\n\n");
	
	fclose(arch5); 

	system("\nPAUSE");
	system("CLS");
};
void registrarUsuarios()
{
	int	r=0, rc=0, re=0,valor;
	char vUsuario[10];
	char vContra[32];
	
	datosusuario regu;
	
	FILE *arch1;
	
	do				
	{
				
		printf("\n\n");
		printf("\n\t\t*********************************************");
		printf("\n\t\t************* REGISTRAR USUARIO *************");
		printf("\n\t\t*********************************************");		
		printf("\n");
		
		printf("\n\t\tCONDICIONES PARA EL NOMBRE DE USUARIO:\n\t\t1. Ser único para cada usuario registrado.\n\t\t2. Comenzar con una letra minúscula.\n\t\t3. Tener al menos 2 letras mayúsculas.\n\t\t4. Tener como máximo 3 dígitos\n");	
		printf("\n\n");						
		_flushall(); 
		printf("\t\tCREAR USUARIO:");
		gets(vUsuario); 	

		comprobarusuario(vUsuario,regu,r);	
				
		arch1=fopen("Recepcionistas.dat","a+b");	
	
		fread(&regu,sizeof(datosusuario),1,arch1);
			
		rewind(arch1); 
			
		while (!feof(arch1))
		{
			valor=strcmp(vUsuario,regu.Usuario);
				
			if(valor==0)
			{
					r=1;
			}
			fread(&regu,sizeof(datosusuario),1,arch1);
		}
		fclose(arch1);
		
		
		
	}
	while(r==1 or re==1 );
			
	arch1=fopen("Recepcionistas.dat","a+b");	
			
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t***** EL NOMBRE DE USUARIO ES CORRECTO ******");
	printf("\n\t\t*********************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");
			
	strcpy(regu.Usuario, vUsuario);	
					
	do				
	{			
		printf("\n");		
		printf("\n\t\tCONDICIONES PARA LA CONTRASEÑA:\n\t\t1. Deberá contener al menos una letra mayúscula, una letra minúscula y un número.\n\t\t2. No podrá contener ningún carácter de puntuación, ni acentos, ni espacios. Sólo caracteresalfanuméricos.\n\t\t3. Deberá tener entre 6 y 32 caracteres.\n\t\t4. No debe tener más de 3 caracteres numéricos consecutivos.\n\t\t5. No debe tener 2 caracteres consecutivos que refieran a letras alfabéticamente consecutivas(ascendentemente). Este criterio es válido tanto para letras mayúsculas, minúsculas o combinación de ambas.\n");		
		printf("\n\n");	
		_flushall(); 
		printf("\t\tCREAR CONTRASENA:");
		gets(vContra);
					
		comprobarcontra( vContra, regu, rc);				
	}
	while(rc==1);
		
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t******** LA CONTRASENA ES CORRECTA *********");
	printf("\n\t\t*********************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");
	
	strcpy(regu.Contra, vContra);
					
	_flushall(); 
	printf("\n\t\tNOMBRE Y APELLIDO:");
	gets(regu.Apenomusuario); 	
				
	fwrite(&regu,sizeof(datosusuario),1,arch1);
	
	
	system("CLS");	
			
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t***** EL USUARIO SE ENCUENTRA CORRECTAMENTE REGISTRADO *****");
	printf("\n\t\t************************************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");		
				
	fclose(arch1);		
};
					
void registrarProfesionales()
{	
	char vusuariop[10];
	char vcontrap[32];
	int	r=0, rc=0, re=0,valor;
	FILE *arch;
	
	datosprofesional regp;
	
	arch=fopen("Profesionales.dat","a+b");		
	
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t***** INGRESE LOS DATOS DEL PROFESIONAL *****");
	printf("\n\t\t*********************************************");	

					
	_flushall(); 
	printf("\n\t\tNOMBRE Y APELLIDO:");
	gets(regp.Apenompro); 				
										
	printf("\t\tIDENTIFICACION PERSONAL:");
	scanf("%d",&regp.Idpro);
							
	printf("\t\tDNI:");
	scanf("%d",&regp.DNIpro);		
								
	_flushall(); 
	printf("\t\tTELEFONO:");
	gets(regp.Telefonopro); 
		
	do				
	{
		system("CLS");
				
		printf("\n\t\tREGISTRAR USUARIO");
		printf("\n\t\t==================\n\n");	
			
		printf("\n\t\tCONDICIONES PARA EL NOMBRE DE USUARIO:\n\t\t1. Ser único para cada usuario registrado.\n\t\t2. Comenzar con una letra minúscula.\n\t\t3. Tener al menos 2 letras mayúsculas.\n\t\t4. Tener como máximo 3 dígitos\n");	
								
		_flushall(); 
		printf("\n\t\tCREAR USUARIO:");
		gets(vusuariop); 

		comprobarusuarioP(vusuariop,regp,r);	
				
		arch=fopen("Profesionales.dat","a+b");	
	
		fread(&regp,sizeof(datosprofesional),1,arch);
			
		rewind(arch); 
			
		while (!feof(arch))
		{
			valor=strcmp(vusuariop,regp.usuario);
				
			if(valor==0)
			{
					r=1;
			}
			fread(&regp,sizeof(datosprofesional),1,arch);
		}
		fclose(arch);
		
		
	}
	while(r==1 or re==1 );
			
	arch=fopen("Profesionales.dat","a+b");		
			
			
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t***** EL NOMBRE DE USUARIO ES CORRECTO ******");
	printf("\n\t\t*********************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");
			
	strcpy(regp.usuario, vusuariop);	
					
	do				
	{					
		printf("\n\t\tCONDICIONES PARA LA CONTRASENA:\n\t\t1. Deberá contener al menos una letra mayúscula, una letra minúscula y un número.\n\t\t2. No podrá contener ningún carácter de puntuación, ni acentos, ni espacios. Sólo caracteresalfanuméricos.\n\t\t3. Deberá tener entre 6 y 32 caracteres.\n\t\t4. No debe tener más de 3 caracteres numéricos consecutivos.\n\t\t5. No debe tener 2 caracteres consecutivos que refieran a letras alfabéticamente consecutivas(ascendentemente). Este criterio es válido tanto para letras mayúsculas, minúsculas o combinación de ambas.\n");		

		_flushall(); 
		printf("\n\t\tCREAR CONTRASENA:");
		gets(vcontrap);
					
		comprobarcontraP( vcontrap, regp, rc);				
	}
	while(rc==1);
		
	printf("\n\n");
	printf("\n\t\t*********************************************");
	printf("\n\t\t******** LA CONTRASENA ES CORRECTA *********");
	printf("\n\t\t*********************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");
	
	strcpy(regp.contra, vcontrap);
						
	system("CLS");	
				
				
	fwrite(&regp,sizeof(datosprofesional),1,arch);
				
	fclose(arch);	

	
	printf("\n\n");
	printf("\n\t\t************************************************************");
	printf("\n\t\t*** EL PROFESIONAL SE ENCUENTRA CORRECTAMENTE REGISTRADO ***");
	printf("\n\t\t************************************************************");	
	printf("\n\n");
	
	system("\n\nPAUSE");
	
	system("CLS");	
			
	fclose(arch); 	
	
								
};
void menuadm()
{
	int opcion;
	datosprofesional regp;
	FILE *arch;
	
	do
	{
		printf("\n\t\t\t\tMODULO ADMINISTRACION\n");
		printf("\t\t\t\t=====================\n");
		
		printf("\n\t\t[1]. REGISTRAR PROFESIONAL.\n");
		printf("\t\t[2]. REGISTRAR USUARIO RECEPCIONISTA.\n");
		printf("\t\t[3]. ATENCIONES POR PROFESIONAL.\n");
		printf("\t\t[4]. RANKING DE PROFESIONALES POR ATENCIONES.\n");	
		printf("\t\t[5]. VOLVER AL MENU PRINCIPAL.\n");	
		printf("\n\t\tSELECCIONE UNA OPCION:");	
		scanf("%d",&opcion); 
		
		system("CLS");

		
		switch(opcion)
		{
			case 1:
				registrarProfesionales();	
				system("CLS");	
			break;
			
			case 2:
				registrarUsuarios();
				system("CLS");	
			break;
			
			case 3:
				atenciones();
				system("CLS");	
				
			break;
			
			case 4:
				ranking();
				system("CLS");	
			break;
			
		}		
	}
	while(opcion<5);
}
int comprobarusuario(char vUsuario[10],datosusuario regu,int &r)
{
	int digitos=0,mayusculas=0,total=0;
	r=0;


		
	for(int j=0;j<10;j++)   
	{              
		if (!vUsuario[j])
		{
			total=j;			
		}
	}

	for(int k=0;k<total;k++)
	{
		if(isupper(vUsuario[0]))
		
		r=1;
		
		if (isdigit(vUsuario[k])) digitos++; 
		

		
		if (isalpha(vUsuario[k]))  
		{
			if(isupper(vUsuario[k])) mayusculas++;  
	              
		}
	}
	if(total<6 or total>10)
	{
		r=1;
	}
	if(digitos>3)
	{
		r=1;	
	} 	        
	if(mayusculas<2)
	{
		r=1;
	}	
	return r;

}
int comprobarcontra(char vContra[32],datosusuario regu,int &rc)
{
	int digitos=0,mayusculas=0,total=0, punt=0,  espacios=0, minusculas=0, totalc, bandera, cc, banderal, cl,j;
	rc=0;
	cc=0;
	banderal=0;
	cl=0;
	
   for(int i=0;i<32;i++)  
   {              
      if (!vContra[i])
      {
         totalc=i;
         break;
      }
   }
   
	for(int j=0;j<totalc;j++)
   {
      if (isdigit(vContra[j])) digitos++;  
     
		{
			if (vContra[j] - vContra[j+1] ==1 || vContra[j] - vContra[j+1] == - 1 ||  vContra[j] - vContra[j-1] ==1 || vContra[j] - vContra[j-1] == - 1 )  
			{
				cc=cc+1;	
				bandera=1;
	
			}
			else
				bandera=0;
		}	
	      
         
      
      
      if (ispunct(vContra[j])) punt++;  
      if (isspace(vContra[j])) espacios++;  
      if (isalpha(vContra[j]))  
      {
         if(isupper(vContra[j])) mayusculas++;  
         else minusculas++;         
      }    
   }
   
    /*letras sucesivas */
    	//cambia  mayusculas

	


	for (j=0; j<strlen(vContra); j++) 
	{
	;
		
	
	   if (isalpha(vContra[j]))  
	     
			{
				if (vContra[j] - vContra[j+1] ==1 || vContra[j] - vContra[j+1] == - 1 ||  vContra[j] - vContra[j-1] ==1 || vContra[j] - vContra[j-1] == - 1 )  
				{
					cl=cl+1;	
					banderal=1;

				}
				else
					banderal=0;
			}
	
		
		}
    
    
    /* */
    
   if(mayusculas<1 or minusculas<1 or digitos<1)
	{
		rc=1;
	}	
	if(punt>0 or espacios>0)
	{
		rc=1;
	}
	if(totalc<6 or totalc>32)
	{
		rc=1;
	}
	if(cc>3)
	{
		rc=1;
	}
		if(cl>0)
	{
		rc=1;
	}
	return rc;
}
int comprobarusuarioP(char vusuariop[10],datosprofesional regp,int &r)
{
	int digitos=0,mayusculas=0,total=0;
	r=0;


		
	for(int j=0;j<10;j++)   
	{              
		if (!vusuariop[j])
		{
			total=j;			
		}
	}

	for(int k=0;k<total;k++)
	{
		if(isupper(vusuariop[0]))
		
		r=1;
		
		if (isdigit(vusuariop[k])) digitos++; 
		

		
		if (isalpha(vusuariop[k]))  
		{
			if(isupper(vusuariop[k])) mayusculas++;  
	              
		}
	}
	if(total<6 or total>10)
	{
		r=1;
	}
	if(digitos>3)
	{
		r=1;	
	} 	        
	if(mayusculas<2)
	{
		r=1;
	}	
	return r;

}
int comprobarcontraP(char vcontrap[32],datosprofesional regp,int &rc)
{
	int digitos=0,mayusculas=0,total=0, punt=0,  espacios=0, minusculas=0, totalc, bandera, cc, banderal, cl,j;
	rc=0;
	cc=0;
	banderal=0;
	cl=0;
	
   for(int i=0;i<32;i++)  
   {              
      if (!vcontrap[i])
      {
         totalc=i;
         break;
      }
   }
   
	for(int j=0;j<totalc;j++)
   {
      if (isdigit(vcontrap[j])) digitos++;  
     
		{
			if (vcontrap[j] - vcontrap[j+1] ==1 || vcontrap[j] - vcontrap[j+1] == - 1 ||  vcontrap[j] - vcontrap[j-1] ==1 || vcontrap[j] - vcontrap[j-1] == - 1 )  
			{
				cc=cc+1;	
				bandera=1;
	
			}
			else
				bandera=0;
		}	
	      
         
      
      
      if (ispunct(vcontrap[j])) punt++;  
      if (isspace(vcontrap[j])) espacios++;  
      if (isalpha(vcontrap[j]))  
      {
         if(isupper(vcontrap[j])) mayusculas++;  
         else minusculas++;         
      }    
   }
   
    /*letras sucesivas */
    	//cambia  mayusculas

	


	for (j=0; j<strlen(vcontrap); j++) 
	{
	;
		
	
	   if (isalpha(vcontrap[j]))  
	     
			{
				if (vcontrap[j] - vcontrap[j+1] ==1 || vcontrap[j] - vcontrap[j+1] == - 1 ||  vcontrap[j] - vcontrap[j-1] ==1 || vcontrap[j] - vcontrap[j-1] == - 1 )  
				{
					cl=cl+1;	
					banderal=1;

				}
				else
					banderal=0;
			}
	
		
		}
    
    
  
    
   if(mayusculas<1 or minusculas<1 or digitos<1)
	{
		rc=1;
	}	
	if(punt>0 or espacios>0)
	{
		rc=1;
	}
	if(totalc<6 or totalc>32)
	{
		rc=1;
	}
	if(cc>3)
	{
		rc=1;
	}
		if(cl>0)
	{
		rc=1;
	}
	return rc;
}
main()
{
		printf("\n\t\t*********************************************");
		printf("\n\t\t***** INGRESAR AL MODULO ADMINISTRACION *****");
		printf("\n\t\t*********************************************");
		printf("\n\n\t\t");			
				
		menuadm();
				
		system("\nPAUSE");
			
		system("CLS");	
}
