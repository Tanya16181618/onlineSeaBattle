#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

using namespace std;

struct Ship {
	int i;
	int j;
};

class Game
{
	bool flag;
	int ij[2];
	char table_player[10][10];
	char table_enemy[10][10];
	int yach;
	char win;
	WSAData wsaData;
	WORD DLLVersion;
	SOCKADDR_IN addr;
	SOCKET newConnection;

public:
	Game();
	~Game() {};
	void game();
	char get_win() {
		return win;
	}
	int get_yach() {
		return yach;
	}
	bool checkb(int i, int j);
	bool check1(int i, int j);
	bool check2(int i, int j);
	void per(int ch, struct Ship* ship);
	void preobr();

	void print1();
	void print2();
	void reDraw();
	void reset(int i, int j);
	char attack(int i, int j);
	char prov();


	bool set_ship_pos(int i, int j, bool flag_ap);

	char get_table(int i, int j) {
		return table_player[i][j];
	};

	char get_enemy(int i, int j) {
		return table_enemy[i][j];
	};
};
