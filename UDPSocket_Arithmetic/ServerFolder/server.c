#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#define PORT 8099
void main(){

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	printf("Enter message: ");
	scanf("%s", &buffer);

	if( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
        exit(EXIT_FAILURE);
	}

	if( setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
	{
		perror("setsockopt");
        exit(EXIT_FAILURE);
	}
	memset(&address, 0, addrlen);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
   	{
        	perror("bind failed");
        	exit(EXIT_FAILURE);
   	}
    	if (listen(server_fd, 3) < 0)
    	{
        	perror("listen");
        	exit(EXIT_FAILURE);
    	}
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
   	{
        	perror("accept");
        	exit(EXIT_FAILURE);
    	}
	
    	valread = read(new_socket, buffer, 1024);
    	printf("%s\n", buffer);

	//File transfer
	FILE *fp;
	fp = fopen("file", "w+");
	char buffer2[10];
	valread = read(new_socket, buffer2, 10);
	fprintf(fp, "%s", buffer2);
	fclose(fp);
	
	// Arithmetic
	char option[1], num1[1], num2[1], answer[2];
	valread = read(new_socket, option, 1);
	valread = read(new_socket, num1, 1);
	valread = read(new_socket, num2, 1);
	
	printf("%s %s %s",option[1], num1[1], num2[1]); 
	
}
