#include "Game.h"

Game::Game()
{

	ij[0] = 0;
	ij[1] = 0;
	yach = 1; // количество кораблей
	win = 'f';
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			table_player[i][j] = 'n';
			table_enemy[i][j] = 'n';
		}

}
void Game::reset(int i, int j) {
	table_player[i][j] = 'n';
}

bool Game::set_ship_pos(int i, int j, bool flag_ap) {
	if (flag_ap == true) {
		if (checkb(i, j) != true || check1(i, j) != true)
			return false;
		table_player[i][j] = 'k';
	}
	else {
		if (checkb(i, j) != false || check1(i, j) != true || check2(i, j) != true)
			return false;
		table_player[i][j] = 'k';
	}

	return true;
}

bool Game::checkb(int i, int j) {
	if (i == 0 && j == 0) {
		if (table_player[i + 1][j] != 'k' && table_player[i][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 0 && j == 9) {
		if (table_player[i + 1][j] != 'k' && table_player[i][j - 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j == 9) {
		if (table_player[i - 1][j] != 'k' && table_player[i][j - 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j == 0) {
		if (table_player[i - 1][j] != 'k' && table_player[i][j + 1] != 'k')
			return true;
		else
			return false;
	}

	if (i == 0 && j != 0) {
		if (table_player[i][j - 1] != 'k' && table_player[i + 1][j] != 'k'
			&& table_player[i][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i != 0 && j == 0) {
		if (table_player[i - 1][j] != 'k' && table_player[i][j + 1] != 'k'
			&& table_player[i + 1][j] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j != 0) {
		if (table_player[i][j - 1] != 'k' && table_player[i - 1][j] != 'k'
			&& table_player[i][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i != 0 && j == 9) {
		if (table_player[i - 1][j] != 'k' && table_player[i][j - 1] != 'k'
			&& table_player[i + 1][j] != 'k')
			return true;
		else
			return false;
	}
	if (table_player[i][j - 1] != 'k' && table_player[i][j + 1] != 'k' &&
		table_player[i - 1][j] != 'k' && table_player[i + 1][j] != 'k')
		return true;
	else
		return false;
}

bool Game::check1(int i, int j) {
	if (i == 0 && j == 0) {
		if (table_player[i + 1][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 0 && j == 9) {
		if (table_player[i + 1][j - 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j == 9) {
		if (table_player[i - 1][j - 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j == 0) {
		if (table_player[i - 1][j + 1] != 'k')
			return true;
		else
			return false;
	}

	if (i == 0 && j != 0) {
		if (table_player[i + 1][j - 1] != 'k' && table_player[i + 1][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i != 0 && j == 0) {
		if (table_player[i - 1][j + 1] != 'k' && table_player[i + 1][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i == 9 && j != 0) {
		if (table_player[i - 1][j - 1] != 'k' && table_player[i - 1][j + 1] != 'k')
			return true;
		else
			return false;
	}
	if (i != 0 && j == 9) {
		if (table_player[i - 1][j - 1] != 'k' && table_player[i + 1][j - 1] != 'k')
			return true;
		else
			return false;
	}
	if (table_player[i - 1][j - 1] != 'k' && table_player[i - 1][j + 1] != 'k' &&
		table_player[i + 1][j - 1] != 'k' && table_player[i + 1][j + 1] != 'k')
		return true;
	else
		return false;

}

bool Game::check2(int i, int j) {
	if (table_player[i][j] != '-')
		return true;
	else
		return false;
}

void Game::per(int ch, struct Ship* ship) {
	for (int g = 0; g < ch; g++) {
		if (ship[g].i == 0 && ship[g].j == 0) {
			if (table_player[ship[g].i + 1][ship[g].j + 1] != 'k') table_player[ship[g].i + 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
			continue;
		}
		if (ship[g].i == 0 && ship[g].j == 9) {
			if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j - 1] != 'k') table_player[ship[g].i + 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
			continue;
		}
		if (ship[g].i == 9 && ship[g].j == 9) {
			if (table_player[ship[g].i - 1][ship[g].j - 1] != 'k') table_player[ship[g].i - 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
			if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
			continue;
		}
		if (ship[g].i == 9 && ship[g].j == 0) {
			if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
			if (table_player[ship[g].i - 1][ship[g].j + 1] != 'k') table_player[ship[g].i - 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
			continue;
		}

		if (ship[g].i == 0 && ship[g].j != 0) {
			if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j - 1] != 'k') table_player[ship[g].i + 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
			if (table_player[ship[g].i + 1][ship[g].j + 1] != 'k') table_player[ship[g].i + 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
			continue;

		}
		if (ship[g].i != 0 && ship[g].j == 0) {
			if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
			if (table_player[ship[g].i - 1][ship[g].j + 1] != 'k') table_player[ship[g].i - 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j + 1] != 'k') table_player[ship[g].i + 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
			continue;

		}
		if (ship[g].i == 9 && ship[g].j != 0) {
			if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
			if (table_player[ship[g].i - 1][ship[g].j - 1] != 'k') table_player[ship[g].i - 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
			if (table_player[ship[g].i - 1][ship[g].j + 1] != 'k') table_player[ship[g].i - 1][ship[g].j + 1] = '-';
			if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
			continue;

		}
		if (ship[g].i != 0 && ship[g].j == 9) {
			if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
			if (table_player[ship[g].i - 1][ship[g].j - 1] != 'k') table_player[ship[g].i - 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j - 1] != 'k') table_player[ship[g].i + 1][ship[g].j - 1] = '-';
			if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
			continue;

		}
		if (table_player[ship[g].i + 1][ship[g].j + 1] != 'k') table_player[ship[g].i + 1][ship[g].j + 1] = '-';
		if (table_player[ship[g].i][ship[g].j + 1] != 'k') table_player[ship[g].i][ship[g].j + 1] = '-';
		if (table_player[ship[g].i + 1][ship[g].j] != 'k') table_player[ship[g].i + 1][ship[g].j] = '-';
		if (table_player[ship[g].i - 1][ship[g].j - 1] != 'k') table_player[ship[g].i - 1][ship[g].j - 1] = '-';
		if (table_player[ship[g].i - 1][ship[g].j] != 'k') table_player[ship[g].i - 1][ship[g].j] = '-';
		if (table_player[ship[g].i][ship[g].j - 1] != 'k') table_player[ship[g].i][ship[g].j - 1] = '-';
		if (table_player[ship[g].i - 1][ship[g].j + 1] != 'k') table_player[ship[g].i - 1][ship[g].j + 1] = '-';
		if (table_player[ship[g].i + 1][ship[g].j - 1] != 'k') table_player[ship[g].i + 1][ship[g].j - 1] = '-';

	}
}

void Game::preobr() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (table_player[i][j] != 'k')
				table_player[i][j] = 'n';
		}
	}
}

