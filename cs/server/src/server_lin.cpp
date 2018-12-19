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

void start_server();

std::list<std::thread> concurrent_connections;

int main(int argc, char* argv[])
{
  start_server();
  return 0;
}

void func_server(int fdSocket)
{
	printf("\n created new thread socket id : %d\n", fdSocket);
	char* buff_send = (char*)calloc( 1024, sizeof(char) );
	//char* buff_recv = (char*)calloc( 1024, sizeof(char) );
	bool bContinue = true;
	while(bContinue)
	{
		read(fdSocket, buff_send, 5);
		printf("\nReceived %s", buff_send );
		sleep(20);
		write(fdSocket, buff_send, 5);
	}
}

void start_server()
{
	int fdListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == fdListen) {
		printf("\nNot able to open Server Socket");
		return ;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = 7080;

	if( 0 != bind(fdListen, (struct sockaddr*)&serv_addr, sizeof(serv_addr) ))
	{
		printf("\nNot able to bind server socket");
		return ;
	}

	listen(fdListen, 8);
	

	bool bContinue = true;
	while(bContinue)
	{
		int fdClient = accept( fdListen, (struct sockaddr*)NULL, NULL);
		if(-1 == fdClient) {
			printf("\nNot able to accept Client Socket");
		}
		concurrent_connections.emplace_back( func_server, fdClient );
	}
	int fdClient = 0;

}

