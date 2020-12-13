#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Control.h"
using namespace std;
using namespace sf;


// константы для текста
RenderWindow window(VideoMode(1280, 720), "Sea Battle");
Texture texture1;
Texture texture2;
Texture texture3;
Texture texture4;
Texture texture5;
Sprite sprite_ship[10][10];
Sprite sprite_enemy[10][10];
Sprite sprite_field;

Font font;
Text text("", font, 25);
Text text_1("", font, 25);
Text text_2("", font, 25);
Text text_3("", font, 25);
Text text_4("", font, 25);
Text text_5("", font, 25);
Text text_info("", font, 25);
Text text_que("", font, 25);
Text endg("", font, 50);
bool res = true;

int main()
{
	char status = 'a';
	text_que.setPosition(640, 425);
	text_info.setPosition(45, 410);
	string info;
	string inf_1;
	string inf_2;
	string inf_3;
	string inf_4;
	string inf_5;
	string que;
	texture1.loadFromFile("back.png");
	texture2.loadFromFile("ship.png");
	texture3.loadFromFile("null.png");
	texture4.loadFromFile("ship_kill.png");
	texture5.loadFromFile("miss.png");
	int k = 34;
	int l = 34;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			sprite_ship[i][j].setPosition(k, l);
			k += 30;
		}
		l += 30;
		k = 34;
	}
	k = 402;
	l = 34;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			sprite_enemy[i][j].setPosition(k, l);
			k += 30;
		}
		l += 30;
		k = 402;
	}
	sprite_field.setTexture(texture1);
	sprite_field.setPosition(0, 0);



	font.loadFromFile("AnimeAce2.ttf");
	text.setFillColor(Color::Black);
	text.setOutlineColor(Color::Black);
	text_1.setFillColor(Color::Black);
	text_1.setOutlineColor(Color::Black);
	text_2.setFillColor(Color::Black);
	text_2.setOutlineColor(Color::Black);
	text_3.setFillColor(Color::Black);
	text_3.setOutlineColor(Color::Black);
	text_4.setFillColor(Color::Black);
	text_4.setOutlineColor(Color::Black);
	text_5.setFillColor(Color::Black);
	text_5.setOutlineColor(Color::Black);
	text_info.setFillColor(Color::Black);
	text_info.setOutlineColor(Color::Black);
	text_que.setFillColor(Color::Black);
	text_que.setOutlineColor(Color::Black);
	endg.setFillColor(Color::Red);
	endg.setOutlineColor(Color::Red);

	string put_in = "";
	Control NMC;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::TextEntered && event.text.unicode != 8) {
				if (put_in.size() < 6) {
					put_in += event.text.unicode;
				}
			}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Backspace)
					if (!put_in.empty())
						put_in.resize(put_in.size() - 1);
			if (event.key.code == Keyboard::Enter) {
				if (put_in == "repeat")
				{
					NMC.reset();
				}
				if (put_in == "exit")
					window.close();
				if (put_in[0] > 40 && put_in[1] < 107) {

					if (NMC.get_pos() == 'd') {
						res = NMC.attack_enemy(put_in[1], put_in[0]);
					}
					if (NMC.get_pos() == 'c') {
						res = NMC.set_ship(put_in[1], put_in[0]);
					}
					if (NMC.get_pos() == 'b') {
						res = NMC.choise_ships(put_in[0]);
					}
				}
				put_in = "";
			}
		}

		int zk;
		char zn;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				zn = NMC.game.get_table(i, j);
				switch (zn)
				{
				case 'o':
					sprite_ship[i][j].setTexture(texture5);
					break;
				case '-':
					sprite_ship[i][j].setTexture(texture5);
					break;
				case 'k':
					sprite_ship[i][j].setTexture(texture2);
					break;
				case 'Q':
					sprite_ship[i][j].setTexture(texture4);
					break;
				case 'n':
					sprite_ship[i][j].setTexture(texture3);
					break;
				default:
					break;
				}
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				zn = NMC.game.get_enemy(i, j);
				switch (zn)
				{
				case 'o':
					sprite_enemy[i][j].setTexture(texture5);
					break;
				case 'x':
					sprite_enemy[i][j].setTexture(texture4);
					break;
				default:
					break;
				}
			}
		}


		window.clear();
		status = NMC.get_pos();

		switch (status)
		{
		case 'a':
			info = "Подключение второго игрока";
			text_info.setString(info);

			inf_1 = "";
			text_1.setPosition(744, 460);
			text_1.setString(inf_1);

			inf_2 = "";
			text_2.setPosition(744, 138);
			text_2.setString(inf_2);

			inf_3 = "";
			text_3.setPosition(744, 185);
			text_3.setString(inf_3);

			inf_4 = "";
			text_4.setPosition(744, 232);
			text_4.setString(inf_4);

			inf_5 = "";
			text_5.setPosition(744, 279);
			text_5.setString(inf_5);

			que = "Ожидайте";
			text_que.setPosition(620, 425);
			text_que.setString(que);

			text.setString(put_in);
			text.setPosition(923, 279);
			break;


		case 'b':
			text_info.setString(L"Осталось расставить");

			zk = NMC.get_val(0);
			text_1.setPosition(50, 485);
			text_1.setString(L"1-палубных: " + to_string(zk));

			zk = NMC.get_val(1);
			text_2.setPosition(50, 550);
			text_2.setString(L"2-палубных: " + to_string(zk));

			zk = NMC.get_val(2);
			text_3.setPosition(50, 620);
			text_3.setString(L"3-палубных: " + to_string(zk));

			zk = NMC.get_val(3);
			text_4.setPosition(50, 680);
			text_4.setString(L"4-палубных: " + to_string(zk));

			text_5.setPosition(30, 380);
			text_5.setString(L" ");

			if (res == false) {
				text_que.setString(L"Неверно, попробуй снова:");
			}
			else {
				text_que.setString(L"Введите число палуб + enter:");
			}
			text_que.setPosition(30, 340);

			text.setString(put_in); // текст введеный пользователем
			text.setPosition(570, 340);
			break;


		case 'c': // ФАЗА ВВОДА КООРДИНАТ КОРАБЛЯ
			text_info.setString(L"Введите координаты корабля\nНапример, a1, g3");

			inf_1 = "";
			text_1.setString(inf_1);

			zk = NMC.get_sh();
			text_2.setPosition(50, 550);
			text_2.setString(L"Осталось клеток " + to_string(zk));

			inf_3 = "";
			text_3.setString(inf_3);

			inf_4 = "";
			text_4.setString(inf_4);

			if (res == false) {
				text_que.setString(L"Неверно,попробуй снова");
			}
			else {
				text_que.setString(" ");
			}
			text_que.setPosition(50, 375);

			text_5.setPosition(45, 490);
			text_5.setString(L"Ваш ход:");

			text.setString(put_in);
			text.setPosition(220, 490);
			break;
		case 'd':
			text_info.setString(L"Укажите координаты выстрела");

			inf_1 = "";
			text_1.setString(inf_1);

			inf_2 = "";
			text_2.setString(inf_2);

			inf_3 = "";
			text_3.setString(inf_3);

			inf_4 = "";
			text_4.setString(inf_4);

			if (res == false) {
				text_que.setString(L"Неверно,попробуй снова:");
			}
			else {
				text_que.setString(" ");
			}
			text_que.setPosition(50, 375);

			text_5.setPosition(45, 490);
			text_5.setString(L"Ваш удар:");
		
			text.setString(put_in);
			text.setPosition(230, 490);
			break;
		default:
			break;
		}
		window.draw(sprite_field);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				window.draw(sprite_ship[i][j]);
			}
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				window.draw(sprite_enemy[i][j]);
			}
		}

		if (NMC.game.get_win() == 'w') {
			if (NMC.game.get_yach() != 0) {
				endg.setPosition(50, 150);
				endg.setString("Вы победили");

			}
			else {
				endg.setPosition(50, 150);
				endg.setString(L"Вы проиграли");
			}
		}

		
		window.draw(text);
		window.draw(text_info);
		window.draw(text_1);
		window.draw(text_2);
		window.draw(text_3);
		window.draw(text_4);
		window.draw(text_5);
		window.draw(text_que);
		window.draw(endg);
		window.display();
	}
	return 0;
}
