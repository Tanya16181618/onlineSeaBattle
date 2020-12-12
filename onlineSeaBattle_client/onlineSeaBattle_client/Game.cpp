#pragma comment(lib, "ws2_32.lib")
#include "Game.h"

#pragma warning(disable: 4996)

Game::Game()
{
	flag = false;
	ij[0] = 0;
	ij[1] = 0;
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
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;

	newConnection = socket(AF_INET, SOCK_STREAM, NULL);

	while (connect(newConnection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
	}

}

char Game::attack() {
	char cij[2];
	char a;
	char b;
	if (flag == false) {
		cout << "choise position" << endl;
		cin >> ij[0];
		cin >> ij[1];
		cij[0] = ij[0] + '0';
		cij[1] = ij[1] + '0';
		send(newConnection, cij, sizeof(cij), NULL);
		recv(newConnection, (char*)&a, sizeof(a), NULL);

		if (a == 'y') {
			table_enemy[ij[0]][ij[1]] = 'x';
		}
		else table_enemy[ij[0]][ij[1]] = 'o';
		reDraw();

		recv(newConnection, (char*)&b, sizeof(b), NULL);
		if (b == 'w')
			return 'w';
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
		ij[0] = cij[0] - '0';
		ij[1] = cij[1] - '0';
		if (table_player[ij[0]][ij[1]] == 'k') {
			a = 'y';
			flag = true;
			ships--;
			table_player[ij[0]][ij[1]] = 'Q';
		}
		else {
			a = 'n';
			flag = false;
			table_player[ij[0]][ij[1]] = 'o';
		}
		reDraw();
		send(newConnection, (char*)&a, sizeof(a), NULL);
		if (ships == 0) {
			win = 'w';
		}
		send(newConnection, (char*)&win, sizeof(win), NULL);
		a = win;
	}
	return a;
}

void Game::game() {
	system("CLS");
	begin();
	preobr();
	reDraw();
	int ij[2];
	prov();
	while (win != 'w') {
		win = attack();
		reDraw();
	}
	if (ships != 0)
		cout << "You win!!!" << endl;
	else
		cout << "You lose" << endl;

	system("pause");
}

void Game::begin() {
	int ship1 = 1;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;
	int i;
	int j;
	int ch;
	bool tk;
	while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0) {
		print1();
		cout << "choise ship" << endl;
		cin >> ch;
		tk = false;
		switch (ch) {
		case 1:
			if (ship1 == 0) {
				cout << "not" << endl;
				continue;
			}
			else
				--ship1;
			break;
		case 2:
			if (ship2 == 0) {
				cout << "not" << endl;
				continue;
			}
			else
				--ship2;
			break;
		case 3:
			if (ship3 == 0) {
				cout << "not" << endl;
				continue;
			}
			else
				--ship3;
			break;
		case 4:
			if (ship4 == 0) {
				cout << "not" << endl;
				continue;
			}
			else
				--ship4;
			break;
		default:
			break;
		}
		ship = new Ship[ch];
		cin >> i;
		cin >> j;

		while (checkb(i, j) != true || check1(i, j) != true) {
			cout << "not, try again" << endl;
			cin >> i;
			cin >> j;
		}
		for (int z = 0; z < ch; z++) {
			ship[z].i = i;
			ship[z].j = j;
		}
		table_player[i][j] = 'k';
		for (int l = 1; l < ch; l++) {
			system("CLS");
			print1();
			cin >> i;
			cin >> j;
			while (checkb(i, j) != false || check1(i, j) != true || check2(i, j) != true) {
				cout << "not, try again" << endl;
				cin >> i;
				cin >> j;
			}
			table_player[i][j] = 'k';
			ship[l].i = i;
			ship[l].j = j;
		}
		per(ch);
		delete[]ship;
	}
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

bool Game::check1(int i, int j) { //Проверка на возможность поставить не задевая кораблии по диоганали
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

bool Game::check2(int i, int j) { //Проверка на наличие других кораблей по горизонтали и вертикали
	if (table_player[i][j] != '-')
		return true;
	else
		return false;
}

void Game::per(int ch) {
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
