// udp client driver program 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100];  
	int sockfd, n; 
	char* mess="YARR";
	struct sockaddr_in servaddr, sevaddr; //made sevaddr for taking the address
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); //Assigning NULL values to structure 
	servaddr.sin_addr.s_addr = inet_addr("172.20.10.6"); 
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
	/////////////////////////////////////////////CODING BELOW/////////////////////////////////////////
	sendto(sockfd, mess, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	// waiting for response 
	recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, NULL); 
	puts(buffer); 

	printf("Order Received by ClinetA!%s",buffer);

	//int cost_arr[5]={'500','850','920','320','1700'};
	int cost_arr[5]={'5','8','9','3','7'};
	int total_cost=0;

	for (int x = 0; x < 5 ; x++)
	{
		total_cost+=(int)buffer[x]*cost_arr[x];	
	}
	
	printf("CLIENTA: Processing Total Cost\n");

	char* send_cost="hello";
	sleep(5);

	printf("CLIENTA: Sending Total Cost of %d to Server\n",total_cost);

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
	sendto(sockfd, send_cost, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	
	// close the descriptor 
	close(sockfd); 
} 

