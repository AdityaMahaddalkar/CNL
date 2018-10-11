#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
using namespace std; 
#define PORT    6000
#define MAXLINE 9
 
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char hello[1024];
    int msg_len;
    struct sockaddr_in servaddr, cliaddr;
     
    
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
     
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
   
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");		
    servaddr.sin_port = htons(PORT);
     
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    socklen_t cli=sizeof(cliaddr);
    char filename[100];
	bzero((char *)filename,sizeof(filename));
	msg_len=recvfrom(sockfd,filename,99,0,(struct sockaddr*)&cliaddr,&cli);
	if(msg_len==-1)
		cout << "Filename error";
	cout<<"\nFilename:"<<filename;

	int filesize;
	msg_len=recvfrom(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr*)&cliaddr,&cli);
	cout<<"\nFileSize:"<<filesize;
	char *filebuff=new char[filesize];


	bzero((char *)filebuff,sizeof(filebuff));
	msg_len=recvfrom(sockfd,filebuff,filesize,0,(struct sockaddr*)&cliaddr,&cli);
	ofstream fout1;
	fout1.open(filename,ios::out|ios::binary);
	if(!fout1)
		cout << "CANNOT CREATE FILE";
	else
	{
		fout1.write(filebuff,filesize);
		fout1.close();
		cout<<"File received";
	}
    return 0;
}
