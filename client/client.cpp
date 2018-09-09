#include "Client.h"

TCPClient tcp;

Client::Client(std::string str) {
  this->data = str;
}
static void Client::sig_exit(int s)
{
	tcp.exit();
	exit(0);
}

int Client::sendResult()
{
	signal(SIGINT, sig_exit);

	tcp.setup();
	while(1)
	{
		srand(time(NULL));
		tcp.Send(data);
		string rec = tcp.receive();
		if( rec != "" )
		{
			std::cout <<"Server Response:";
			std::cout.flush();
		}
		else {
			std::cout <<"failure";
			std::cout.flush();
		}
		sleep(1);
	}
	return 0;
}
