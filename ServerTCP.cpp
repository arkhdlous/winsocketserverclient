#include <iostream>
#include <winsock2.h>
#include <time.h>
 
using namespace std;

void get_current_num_time(int int_time[6]);
int main()
{
	int curtime[6] = {0};

    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
 
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
 
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
 
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);
 
    cout << "Listening for incoming connections..." << endl;
 
    char buffer[1024];

	int clientAddrSize = sizeof(clientAddr);
	if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
	{
		cout << "Client connected!" << endl;
	

		get_current_num_time(curtime);
		
		printf("[%04d/%02d/%02d %02d:%02d:%02d]  Receive Sucess\n",
					curtime[0], curtime[1], curtime[2],	
		            curtime[3], curtime[4], curtime[5]);

		recv(client, buffer, sizeof(buffer), 0);
		cout << "Client says: " << buffer << endl;
		memset(buffer, 0, sizeof(buffer));

		closesocket(client);
		cout << "Client disconnected." << endl;
  }
	
}

void get_current_num_time(int int_time[6])
{
	time_t timer;
	struct tm newtime;

	timer = time(NULL);

	localtime_s(&newtime, &timer);
	int_time[0] = newtime.tm_year + 1900;
	int_time[1] = newtime.tm_mon + 1;
	int_time[2] = newtime.tm_mday;
	int_time[3] = newtime.tm_hour;
	int_time[4] = newtime.tm_min;
	int_time[5] = newtime.tm_sec;
}
