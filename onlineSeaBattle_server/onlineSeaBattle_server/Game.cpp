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
	DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(10);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) {
		std::cout << "Error #2\n";
		system("pause");
	}
	else {
		std::cout << "Client connected!\n";
	}

}

char Game::attack(int i, int j) {
	char b;
	char a;

	char cij[2];
	ij[0] = i;
	ij[1] = j;
	if (flag == false) {
		cij[1] = ij[0] + 48;
		cij[0] = ij[1] + 48;
		send(newConnection, cij, sizeof(cij), NULL);
		recv(newConnection, (char*)&a, sizeof(a), NULL);

		if (a == 'y') {
			table_enemy[ij[0]][ij[1]] = 'x';
			flag = false;
		}
		else table_enemy[ij[0]][ij[1]] = 'o';
		reDraw();
		recv(newConnection, (char*)&b, sizeof(b), NULL);
		if (b == 'w') {
			win = 'w';
			return b;
		}
	}
	else {
		cij[0] = 'a';
		cij[1] = 'a';
		send(newConnection, cij, sizeof(cij), NULL);
	}
	a = prov();
	return a;
}

char Game::prov() {
	char a = 'z';
	char cij[2];
	recv(newConnection, cij, sizeof(cij), NULL);
	if (cij[0] != 'a' && cij[1] != 'a') {
		ij[1] = cij[0] - 48;
		ij[0] = cij[1] - 48;
		if (table_player[ij[0]][ij[1]] == 'k') {
			a = 'y';
			flag = true;
			yach--;
			table_player[ij[0]][ij[1]] = 'Q';
		}
		else {
			a = 'n';
			flag = false;
			table_player[ij[0]][ij[1]] = 'o';
		}
		reDraw();
		send(newConnection, (char*)&a, sizeof(a), NULL);
		if (yach == 0) {
			win = 'w';
		}
		a = win;
		send(newConnection, (char*)&win, sizeof(win), NULL);
	}
	return a;
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
void Game::print1() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << table_player[i][j];
		}
		cout << endl;
	}
}

void Game::print2() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << table_enemy[i][j];
		}
		cout << endl;
	}
}

void Game::reDraw() {
	system("CLS");
	print1();
	cout << endl;
	print2();
	cout << endl;
}
