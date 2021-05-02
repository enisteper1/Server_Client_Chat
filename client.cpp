#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#define BUFFER_SIZE 1024
#define PORT 14400

using namespace std;
void read_message(int);
void send_message(int);
int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char ip_addr[20] = "127.0.0.1";
	if(argc>1)
		strcpy(ip_addr, argv[1]);

	char buffer[BUFFER_SIZE] = "";
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout<<"\n Could not create socket \n";
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
	{
		cout<<"\nInvalid address/ Address not supported \n";
		exit(EXIT_FAILURE);
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		cout<<"\nConnection Failed \n";
		exit(EXIT_FAILURE);
	}
	cout<<"Connection is Established!"<<endl;
	cout<<"---Client Side---\n";
	thread read_thread(read_message, sock);
	thread send_thread(send_message, sock);
	read_thread.join();
	send_thread.join();
	close(sock);
	return 0;
}

void read_message(int _socket)
{
	char _buffer[BUFFER_SIZE] = "";
	while(true)
	{
		recv(_socket, _buffer, BUFFER_SIZE, 0);
		if(!strcmp(_buffer, "exit\n"))
			exit(0);
		cout<<"From Server: "<<_buffer;
		memset(_buffer, 0,BUFFER_SIZE);
		sleep(0.01);
	}
}

void send_message(int _socket)
{
	char message[BUFFER_SIZE] = "";
	while(true)
	{
		cin.getline(message, BUFFER_SIZE);
		strcat(message,"\n");
		send(_socket , message , strlen(message) , 0 );
		if(!strcmp(message, "exit\n"))
			exit(0);
	}
}

