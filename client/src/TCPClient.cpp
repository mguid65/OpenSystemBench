/*
 * This is a TCPClient implementation from kashimAstro on github
 *
 *
 */

#include "TCPClient.h"

TCPClient::TCPClient()
{
    sock = -1;
    port = 0;
	address = "";
}

bool TCPClient::setup(string address , int port)
{

    if (WSAStartup(MAKEWORD(2, 0),
      &wsaData) != 0)
    {
      fprintf(stderr,"WSAStartup() failed");
      exit();
    }
  	if(sock == -1)
	{
        sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
        if (sock == INVALID_SOCKET)
		{
            cout << "Could not create socket" << endl;
        }
    }
  	if(inet_addr(address.c_str()) == -1)
  	{
    		struct hostent *he;
    		struct in_addr **addr_list;
    		if ( (he = gethostbyname( address.c_str() ) ) == NULL)
    		{
              cout<<"Failed to resolve hostname\n";
		      return false;
    		}
	   	addr_list = (struct in_addr **) he->h_addr_list;
    		for(int i = 0; addr_list[i] != NULL; i++)
    		{
      		      server.sin_addr = *addr_list[i];
		      break;
    		}
  	}
  	else
  	{
    		server.sin_addr.s_addr = inet_addr( address.c_str() );
  	}
  	server.sin_family = AF_INET;
    server.sin_port = htons( port );
  	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  	{
    		perror("connect failed. Error");
    		return false;
  	}
  	return true;
}

bool TCPClient::Send(string data)
{
    if(sock != INVALID_SOCKET)
	{
		if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
		{
			cout << "Send failed : " << data << endl;
			return false;
		}
	}
	else
		return false;
	return true;
}

string TCPClient::receive(int size)
{
  	char buffer[size];
	memset(&buffer[0], 0, sizeof(buffer));

  	string reply;
	if( recv(sock , buffer , size, 0) < 0)
  	{
	    	cout << "receive failed!" << endl;
		return nullptr;
  	}
	buffer[size-1]='\0';
  	reply = buffer;
  	return reply;
}

string TCPClient::read()
{
  	char buffer[1] = {};
  	string reply;
  	while (buffer[0] != '\n') {
    		if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    		{
      			cout << "receive failed!" << endl;
			return nullptr;
    		}
		reply += buffer[0];
	}
	return reply;
}

void TCPClient::exit()
{
    closesocket( sock );
}
