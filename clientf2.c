// udp client driver program 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100]; 
	char *message = "Hello Server this is CLIENT 2"; 
	int sockfd, n; 
	struct sockaddr_in servaddr, sevaddr; //made sevaddr for taking the address
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); //Assigning NULL values to structure 
	servaddr.sin_addr.s_addr = inet_addr("192.168.43.244"); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 
	
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
	sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	
	// waiting for response 
	//recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sevaddr, NULL); 
	//puts(buffer); 

	//printf("^^^MESSAGE FROM SERVER\n THIS IS CLIENT \n SERVER IP: %s \n SERVER PORT: %d ",inet_ntoa(sevaddr.sin_addr),(sevaddr.sin_port));


	// close the descriptor 
	close(sockfd); 
} 

