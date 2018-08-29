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
     
    int len, n;
    n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t*)&len);
    //printf("Client : %s\n", buffer); 
     
	// Save to a new file
	
	ofstream outfile;
	outfile.open("file", ios::out);
	outfile << buffer;
	outfile.close();
    return 0;
}
