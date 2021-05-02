// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
#define BUFFER_SIZE 1024
#define PORT 14400

using namespace std;
void read_message(int);
void send_message(int);
int main(int argc, char const *argv[])
{
	
	int server, sock;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = "";
	bool connection = true;

	// Creating socket file descriptor
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	if (bind(server, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((sock = accept(server, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	cout<<"Connection is Established!"<<endl;
	cout<<"---Server Side---\n";
	thread read_thread(read_message,sock);
	thread send_thread(send_message, sock);
	read_thread.join();
	send_thread.join();
	close(sock);
	return 0;
}

void read_message(int _socket)
{

	char _buffer[BUFFER_SIZE]="";
	while(true)
	{
		recv(_socket, _buffer, BUFFER_SIZE, 0);
		if(!strcmp(_buffer, "exit\n"))
			exit(0);
		cout<<"From Client: "<<_buffer;
		memset(_buffer, 0, BUFFER_SIZE);
		sleep(0.01);
	}
}

void send_message(int _socket)
{
	char message[BUFFER_SIZE] = "";
	while(true)
	{
		cin.getline(message, BUFFER_SIZE);
		strcat(message, "\n");
		send(_socket , message , strlen(message) , 0 );
		if(!strcmp(message, "exit\n"))
			exit(0);
	}
}