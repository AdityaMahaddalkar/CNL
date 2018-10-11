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
	int msg_len;
	char hello[MAXLINE];
	
	
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0 )
	{
		perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}
	
	servaddr.sin_family = AF_INET;
   	servaddr.sin_port = htons(LPORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));  
    	
   	int n,len;
     
    cout<<"\nEnter Filename:";
	char filename[100];
	cin>>filename;
	fstream fout;
	fout.open(filename,ios::in|ios::out|ios::binary);
	fout.seekg(0,ios::end);
	int filesize=fout.tellg(); //get file size
	char *filebuff=new char[filesize];
	fout.seekg(0,ios::beg);
	fout.read(filebuff,filesize); //reading file content

	msg_len=sendto(sockfd,filename,strlen(filename),0,(struct sockaddr *)&servaddr,sizeof(servaddr)); //send filename
				if(msg_len==-1)
					cout << "Filename error";

	msg_len=sendto(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&servaddr,sizeof(servaddr)); //send filesize
	if(msg_len==-1)
		cout << "Filesize error";



	msg_len=sendto(sockfd,filebuff,filesize,0,(struct sockaddr *)&servaddr,sizeof(servaddr)); //send file conetents
	if(msg_len==-1)
		cout << "File transmission error";
	else
		cout<<"Transmission Successful";
	fout.close();
    
    close(sockfd);
	return 0;
}

