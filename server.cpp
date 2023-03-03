// server program for udp connection 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100]; 
	char* message = "Hello"; 
	int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

	// send the response 
	sendto(listenfd, message, MAXLINE, 0, 
		(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	
	//receive the datagram 
	socklen_t lent = sizeof(cliaddr); 
	int n = recvfrom(listenfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr,&lent); //receive message from client
	buffer[n] = '\0'; 
	puts(buffer); 

	printf("^^^MESSAGE FROM CLIENT\n THIS IS SERVER \n CLIENT IP: %s \n CLIENT PORT: %d ",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);	


}





