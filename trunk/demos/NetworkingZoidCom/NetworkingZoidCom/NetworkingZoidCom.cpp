// NetworkingZoidCom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <zoidcom/zoidcom.h>
#include "Server.h"
#include "Client.h"
#include "Tree.h"
#include "Player.h"

void process_zoidcom_log(const char *_log) {
	printf("%s\n", _log);
}

void makeServer(ZoidCom* zcom) {
	// make instance of our Server class
	Server *server = new Server();
	server->ZCom_setDebugName("Server");
	Tree::registerClass(server);
	Player::registerClass(server);

	// this creates and initializes the network sockets
	// true = use udp socket, 10000 = the UDP port to use, 0 = no internal socket
	bool result = server->ZCom_initSockets(true, 10000, 0);
	// if result is false, Zoidcom had problems while initializing
	if (!result) {
		exit(255);
	}

	bool exit = false;
	while (!exit) {
		if (_kbhit()) {
			char c = _getch();
			switch (c) {
				case 'q':
				case 'Q':
					exit = true;
					break;
				case 't': 
					{
						Tree* tree = new Tree(server);
						server->addEntity(tree);
						break;
					}
				default:
					break;
			}
		}

		// tell the server to process incoming data
		//printf("Processing input...\n");
		server->ZCom_processInput();
		// tell the server to process outgoing data
		//printf("Processing output...\n");
		server->ZCom_processOutput();
		// let the program sleep for 0 msecs
		zcom->Sleep(1);
		server->update();
	}
	delete server;
}

void makeClient(ZoidCom* zcom) {
	// make instance of our Client class
	Client *client = new Client();
	client->ZCom_setDebugName("Client");
	Tree::registerClass(client);
	Player::registerClass(client);

	// this creates and initializes the network sockets
	// true = use udp socket, 0 = let OS choose UDP port, 0 = no internal socket
	bool result = client->ZCom_initSockets(true, 0, 0);
	// if result is false, Zoidcom had problems while initializing
	if (!result)
		exit(255);

	// put this into a codeblock so that server_addr gets out of scope before 
	// 'delete zcom;' get called (everything needs to be gone before the 
	// ZoidCom object gets deleted)
	{
		cout << "Connecting..." << endl;
		//// prepare bitstream
		//ZCom_BitStream *password = new ZCom_BitStream();
		//password->addString("let_me_in");
		// prepare address
		ZCom_Address server_addr;
		server_addr.setAddress( eZCom_AddressUDP, 0, "localhost:10000");
		// connect
		ZCom_ConnID connection_id = client->ZCom_Connect(server_addr, /*password*/0);
		//password = NULL;
	}

	bool exit = false;
	while (!exit && !client->canExit()) {
		if (_kbhit()) {
			char c = _getch();
			switch (c) {
				case 'q':
				case 'Q':
					exit = true;
					break;
				case 'm': 
					client->moveUp();
					break;

				default:
					break;
			}
		}

		// tell the client to process incoming data
		//printf("Processing input...\n");    
		client->ZCom_processInput();
		// tell the client to process outgoing data
		//printf("Processing output...\n");    
		client->ZCom_processOutput();
		// give up remaining cpu time
		zcom->Sleep(1);
		client->update();
	}

	delete client;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char ch;
	cout << "Start as (c)lient or (s)erver? " << endl;
	std::cin >> ch;

	bool server = true;
	switch (ch) {
	  case 'c':
	  case 'C':
		  cout << "Client" << endl;
		  server = false;
		  break;
	  case 's':
	  case 'S':
		  cout << "Server" << endl;
		  server = true;
		  break;
	  default:
		  return 1;
	}

	// create ZoidCom with logging disabled
	//ZoidCom *zcom = new ZoidCom(process_zoidcom_log); // Console logging
	ZoidCom *zcom = new ZoidCom(); // No extra console logging
	if (!zcom || !zcom->Init()) {
		return 1;
	}

	// here Zoidcom can be used
	if (server) {
		makeServer(zcom);
	} else {
		makeClient(zcom);
	}

	// remove it again
	delete zcom;
	return 0;
}

