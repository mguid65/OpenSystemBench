#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <winsock2.h>
#include <vector>
/*
 * This is a tcp client implementation from kashimAstro on github
 */
using namespace std;

class TCPClient
{
  private:
    int sock;
    std::string address;
    unsigned short port;
    struct sockaddr_in server;
    WSADATA wsaData;
  public:
    TCPClient();
    bool setup(string address, int port);
    bool Send(string data);
    string receive(int size = 4096);
    string read();
    void exit();
};

#endif
