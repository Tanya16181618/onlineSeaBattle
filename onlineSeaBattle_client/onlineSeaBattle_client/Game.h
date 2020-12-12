#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#ifndef GAME_H
#define GAME_H


#include <iostream>


using namespace std;

class Game
{
	int ij[2];
	bool flag;
	struct Ship {
		int i;
		int j;
	}*ship;

	char table_player[10][10];
	char table_enemy[10][10];
	int ships = 1;// всего кораблей
	char win;
	WSAData wsaData;
	WORD DLLVersion;
	SOCKADDR_IN addr;
	SOCKET newConnection;

public:
	Game();
	~Game() {};
	void game();
	void begin();
	bool checkb(int i, int j);
	bool check1(int i, int j);
	bool check2(int i, int j);
	void per(int ch);
	void preobr();
	void print1();
	void print2();
	void reset();
	char attack();
	char prov();
	void reDraw();
};



#endif // GAME_H