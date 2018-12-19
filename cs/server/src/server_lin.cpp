#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <list>
#include <thread>
#include <fcntl.h>

#define SERVER_PORT htons(7080)
#define SERVER_IP   "192.168.1.203"

void start_server();
bool make_socket_nonblocking(int fdSocket);

std::list<std::thread> concurrent_connections;

int main(int argc, char* argv[])
{
  start_server();
  printf("\n Returning from main");
  return 0;
}

bool receiveMessage(int fdSocket, char* buff, int buff_len)
{
	//read(fdSocket, buff_send, 4);
	bool connClosed = false;
	int total_receive = 0;
	int currRead =0;
	do {
		currRead = recv(fdSocket, buff + total_receive, buff_len - total_receive, 0);
		if( 0 < currRead) {
			total_receive += currRead;
			printf("\n receive : %d for socket : %d", currRead, fdSocket);
		} else if( 0 == currRead ) {
			connClosed = true;
		} else if( (EAGAIN == errno) || ( EWOULDBLOCK == errno) ) {
			//this read is complete
			if( 0 < total_receive )
			  break;
		} else {
			connClosed = true;
		}
	}while( !connClosed && ( 0 < buff_len - total_receive) );
	return connClosed;
}

void setReply(const char* src, char* dest)
{
	int iVal = atoi(src);
	++iVal;
	sprintf(dest,"%d", iVal);
	//itoa(iVal, dest, 10);
}

void func_server(int fdSocket)
{
	printf("\n created new thread socket id : %d\n", fdSocket);
	char* buff_send = (char*)calloc( 1024, sizeof(char) );
	char* buff_recv = (char*)calloc( 1024, sizeof(char) );
	make_socket_nonblocking(fdSocket);
	bool bContinue = true;
	while(bContinue)
	{
		printf("\n going for receive : %d", fdSocket);
		if(receiveMessage(fdSocket, buff_recv, 1023)) {
			printf("\n Connection is closed or some error Receive");
			bContinue = false;
		}
		if( 0 < strlen(buff_recv) ) {
			printf("\nReceived %s", buff_recv );
			setReply(buff_recv, buff_send);
			if( 0 < send(fdSocket, buff_send, strlen(buff_send), 0) ) {
				printf("\nSending %s", buff_send );
				memset(buff_send, 0, 1024);
			} else {
				printf("\n Connection is closed or some error Sending");
				bContinue = false;
			}
			memset(buff_recv, 0, 1024);
		}
	}
	close(fdSocket);
	printf("\n returning from thread socket id : %d", fdSocket);
}

void start_server()
{
	printf("\n Creating Socket");
	int fdListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == fdListen) {
		printf("\nNot able to open Server Socket");
		return ;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =inet_addr(SERVER_IP);// htonl(INADDR_ANY);
	serv_addr.sin_port = SERVER_PORT;

	printf("\n bindig to port %d", SERVER_PORT);
	if( 0 != bind(fdListen, (struct sockaddr*)&serv_addr, sizeof(serv_addr) ))
	{
		printf("\nNot able to bind server socket");
		return ;
	}

	printf("\n Listning ...");
	listen(fdListen, 8);

	bool bContinue = true;
	while(bContinue)
	{
		printf("\n going for accept...");
		int fdClient = accept( fdListen, (struct sockaddr*)NULL, NULL);
		if(-1 == fdClient) {
			printf("\nNot able to accept Client Socket");
		}
		printf("\n accepted connection...");
		concurrent_connections.emplace_back( func_server, fdClient );
	}
	printf("\n Returning from server func");
}

bool make_socket_nonblocking(int fdSocket)
{
	bool blocking = false;
	if (fdSocket < 0) return false;

#ifdef _WIN32
	unsigned long mode = blocking ? 0 : 1;
	return (ioctlsocket(fdSocket, FIONBIO, &mode) == 0) ? true : false;
#else
	int flags = fcntl(fdSocket, F_GETFL, 0);
	if (flags == -1) return false;
	flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
	return (fcntl(fdSocket, F_SETFL, flags) == 0) ? true : false;
#endif
}
