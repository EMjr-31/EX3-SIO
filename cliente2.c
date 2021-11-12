#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc,  char **ipnpv)
{
	if(argc>1)
	{
		int fd1,nbyte,puerto;
		char buf[100];
		char *ip;

		ip= ipnpv[1];
		puerto=atoi(ipnpv[2]);

		struct hostent *he;
		if((he=gethostbyname(ip))== NULL)
		{
			printf("Errror al traer datos de la direccion ip\n");
			return -1;
		}
		struct sockaddr_in server;
		memset(&server, 0, sizeof(server));
		server.sin_family 	= AF_INET;
		server.sin_port		=htons(puerto);
		server.sin_addr		=*((struct in_addr *)he->h_addr);

		if((fd1=socket(AF_INET, SOCK_STREAM, 0))==-1)
		{
			printf("Errror al crear socket \n");
			return -1;
		}
		if(connect(fd1, (struct sockaddr *)&server,sizeof(server))==-1)
		{
			printf("Errror al contactar con el servidor \n");
			return -1;
		}
		if((nbyte=recv(fd1,buf,100,0))==-1)
		{
			printf("Errror al recibir mensaje \n");
			return -1;
		}
		buf[nbyte]='\0';
		printf("mensaje recibido del servidor: %s \n", buf);
		send(fd1, "Soy el cliente 1, envio mensaje al servirdor confirmando la comunicaion \n",26,0);
	}else
	{
		printf("No se ingreso la direccion ip y el numero de  puerto");
	}
}
