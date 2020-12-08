#include "Control.h"

bool Control::set_ship(char i, char j) {
	if (i < 48 || i > 58 || j < 97 || j > 107)
		return false;
	int ii = i - 48;
	int jj = j - 97;
	if (game.set_ship_pos(ii, jj, flag) == false)
		return false;
	for (int n = sh - 1; n >= 0; n--) {
		ship[n].i = ii;
		ship[n].j = jj;
	}
	sh--;
	flag = false;
	if (sh == 0) {
		game.per(p + 1, ship);
		pos = 'b';
		ships[p] -= 1;
		if (ships[0] == 0 && ships[1] == 0 && ships[2] == 0 && ships[3] == 0) {
			pos = 'd';
			game.preobr();
		}
		p = 0;
		delete[]ship;
	}
	return true;
}

bool Control::choise_ships(char a) {
	int aa = a - 49;
	if (aa < 0 || aa > 3)
		return false;
	if (ships[aa] == 0)
		return false;
	pos = 'c';
	sh = aa + 1;
	p = aa;
	flag = true;
	ship = new Ship[sh];
	return true;
}

bool Control::attack_enemy(char i, char j) {
	if (i < 48 || i > 58 || j < 97 || j > 107)
		return false;
	int ii = i - 48;
	int jj = j - 97;
	game.attack(ii, jj);
	if (game.get_win() == 'w') {
		pos = 'v';
	}
	return true;
}

void Control::reset() {
	if (p != 0) {
		for (int v = p; v >= 0; v--) {
			game.reset(ship[v].i, ship[v].j);
		}
	}
	pos = 'b';
}