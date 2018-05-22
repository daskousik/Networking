#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
int main()
{
	unsigned char toSend[2][102],mac[2][6];
	int i,j;
	int udpSocket;
	struct sockaddr_in udpClient, udpServer;
	int broadcast =1 ;
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1)
	{
	    perror("setsockopt (SO_BROADCAST)");
	    exit(EXIT_FAILURE);
	}
	udpClient.sin_family = AF_INET;
	udpClient.sin_addr.s_addr = INADDR_ANY;
	udpClient.sin_port = 0;	
	bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient));
	udpServer.sin_family = AF_INET;
	udpServer.sin_addr.s_addr = inet_addr("10.24.255.255"); // Braodcast address
	udpServer.sin_port = htons(9);
	for(j=0;j<2;j++)
	{
		for(i=0;i<6;i++)
		{
			toSend[j][i] = 0xFF;
		}
	}
	mac[0][0] = 0x8c;
	mac[0][1] = 0xdc;
	mac[0][2] = 0xd4;
	mac[0][3] = 0x31;
	mac[0][4] = 0x13;
	mac[0][5] = 0x6a;
	
	mac[1][0] = 0x8c;
	mac[1][1] = 0xdc;
	mac[1][2] = 0xd4;
	mac[1][3] = 0x33;
	mac[1][4] = 0x46;
	mac[1][5] = 0x83;
	for(j=0;j<2;j++)
	{
		for(i=1;i<=16;i++)
		{
			memcpy(&toSend[j][i*6], &mac [j], 6*sizeof(unsigned char));
			sendto(udpSocket, &toSend[j], sizeof(unsigned char) * 102, 0, (struct sockaddr*)&udpServer, sizeof(udpServer));
		}
	}
	return 0;
}
