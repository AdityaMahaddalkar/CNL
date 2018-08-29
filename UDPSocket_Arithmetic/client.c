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

void main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
       
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    
    // File transfer
    char buffer2[10];
    FILE *fp;
    fp = fopen("file", "r");
    fscanf(fp, "%s", &buffer2);
    send(sock, buffer2, strlen(buffer2), 0);
    fclose(fp);
    
    // Arithmetic 
    
    printf("\n[1]To add\n[2]To sub\n[3]To mul\n[4]To div:");
    int option;
    scanf("%d", &option);
    int converted = htonl(option);
    
    send(sock, &converted, sizeof(converted), 0);
    
    printf("Enter num1: ");
    int num1;
    scanf("%d", &num1);
    converted = htonl(num1);
    send(sock, &converted, sizeof(converted), 0);
    
    printf("Enter num2: ");
    int num2;
    scanf("%d", &num2);
    converted = htonl(num2);
    send(sock, &converted, sizeof(converted), 0);
    
    int valread2 = read(sock, &converted, sizeof(converted));
    int answer = ntohl(converted);
    printf("Answer : %d\n", answer);
     
}
