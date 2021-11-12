#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **npv)
{
	if(argc>0)
	{
		int lcliente, puerto, fd1, fd2;
		puerto=atoi(npv[1]);
		
		int nbyte;
		char buf[100];
		
		struct sockaddr_in server, cliente;
		memset(&server, 0 , sizeof(server));
		server.sin_family	=AF_INET;
		server.sin_port		=htons(puerto);
		server.sin_addr.s_addr	=INADDR_ANY;

		if((fd1=socket(AF_INET, SOCK_STREAM,0))<0)
		{
			printf("Error al abrir el sockets \n");
			return -1;
		}
		if(bind(fd1,(struct sockaddr*)&server, sizeof(server))==-1)
		{
			printf("Error al asignar IP y numero de puerto al socket \n");
			return -1;
		}
		if(listen (fd1,3)==-1)
		{
			printf("Error al definir el socket compo pasivo \n");
			return -1;
		}
		while(1)
		{
			fd2=accept(fd1,(struct sockaddr *)&cliente, &lcliente);
			if(fd2<0)
			{
				printf("Error al aceptar conexion \n");
				return -1;
			}
			send(fd2,"Bienvenido al servidor \n",26,0);
			if((nbyte=recv(fd2,buf,100,0))==-1)
			{
				printf("Error al recibir mensaje \n");
			}
			buf[nbyte]='\0';
			printf("Mensaje del cliente: %s \n",buf);
			close(fd2);
		}
	}else
	{
		printf("No se ingreso el numero de puesto \n");
	}
	return 0;
}
