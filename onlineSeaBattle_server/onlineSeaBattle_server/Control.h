#pragma once
#include "Game.h"

class Control
{
	char pos;
	int ships[4];
	int sh;
	int p;
	bool flag;
	struct Ship* ship;
public:
	Game game;
	Control() {
		pos = 'b';
		ships[0] = 1;
		ships[1] = 0;
		ships[2] = 0;
		ships[3] = 0;
		sh = 0;
		p = 0;
		flag = true;
	};
	~Control() {};
	char get_pos() { return pos; }
	bool set_ship(char a, char b);

	bool choise_ships(char a);

	bool attack_enemy(char i, char j);

	void reset();
	int get_p() { return p; }
	int get_sh() { return sh; }
	int get_val(int a) { return ships[a]; }

};
