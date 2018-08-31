#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
using namespace std;

#define LPORT 6000
#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;
	
	ifstream infile;
	char hello[MAXLINE];
	infile.open("file");
	infile.seekg(0);
	
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0 )
	{
		perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}
	
	servaddr.sin_family = AF_INET;
   	servaddr.sin_port = htons(LPORT);
    servaddr.sin_addr.s_addr = inet_addr("10.10.14.173");
    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));  
    	
   	int n,len;
     
    infile.read(buffer, 45);
   	sendto(sockfd, (const char *)buffer, strlen(buffer),
                       0, (const struct sockaddr *) &servaddr, 
                       sizeof(servaddr));
    
    close(sockfd);
    infile.close();
	return 0;
}

