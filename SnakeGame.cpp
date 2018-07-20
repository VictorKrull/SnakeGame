#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include "cadena_util.h"
#include "consola_util.h"
#include "Point.h"
#include "SnakeGame.h"

using namespace std;
using namespace console;

SnakeGame::SnakeGame()
{
	score = 0;
	food = Point();
}

bool SnakeGame::isOver(deque<Point> &snake, Point &target_position, pair<int, int> &size_map)
{
	if (snake.back() == target_position)
	{
		return false;
	}
	if (any_of(snake.begin(), snake.end(), [&](Point position) { return position.compare(target_position); }))
	{
		return true;
	}
	if (target_position.getX() <= 0 || target_position.getY() <= 0)
	{
		return true;
	}
	if (target_position.getX() >= size_map.first - 2 || target_position.getY() >= size_map.second - 3)
	{
		return true;
	}
	return false;
}

void SnakeGame::drawSnake(deque<Point> &snake, Point &target_position, pair<int, int> &size_map, unsigned int snake_length)
{
	if (!isOver(snake, target_position, size_map))
	{
		set_console_backgroundcolor(2);
		write_at_position(" ", snake.back().getX() + 1, snake.back().getY() + 1);
		snake.push_back(target_position);		
		set_console_backgroundcolor(9);
		write_at_position(" ", target_position.getX() + 1, target_position.getY() + 1);

		if (snake.size() > snake_length)
		{
			snake.pop_front();
			set_console_backgroundcolor(0);
			write_at_position(" ", snake.front().getX() + 1, snake.front().getY() + 1);
		}
	}
}

SnakeGame::Direction SnakeGame::getDirection(SnakeGame::Direction current_direction)
{
	char key;

	if (!iskey_hit())
	{
		return current_direction;
	}
	
	key = get_key();

	switch (key)
	{
		case 'w':
			if (current_direction != SnakeGame::Direction::down)
			{
				current_direction = SnakeGame::Direction::up;
			}
		break;

		case 's':
			if (current_direction != SnakeGame::Direction::up)
			{
				current_direction = SnakeGame::Direction::down;
			}
		break;

		case 'a':
			if (current_direction != SnakeGame::Direction::right)
			{
				current_direction = SnakeGame::Direction::left;
			}
		break;

		case 'd':
			if (current_direction != SnakeGame::Direction::left)
			{
				current_direction = SnakeGame::Direction::right;
			}
		break;		
	}	
	return current_direction;
}

Point SnakeGame::getNextPosition(SnakeGame::Direction direction, Point &current_position)
{
	Point next_position(current_position.getX(), current_position.getY());

	switch (direction)
	{
		case SnakeGame::Direction::up:
			next_position.setY(next_position.getY() - 1);
		break;

		case SnakeGame::Direction::down:
			next_position.setY(next_position.getY() + 1);
		break;

		case SnakeGame::Direction::left:
			next_position.setX(next_position.getX() - 1);
		break;

		case SnakeGame::Direction::right:
			next_position.setX(next_position.getX() + 1);
		break;
	}
	return next_position;
}

void SnakeGame::drawMap(pair<int, int> &size_map)
{
	string map_border;

	map_border.assign(size_map.first, '#');
	write_at_position(map_border, 0, 2);
	write_at_position(map_border, 0, size_map.second - 2);

	for (int i = 0; i < size_map.second - 3; i++)
	{
		write_at_position('#', 0, i + 2);
		write_at_position('#', size_map.first - 1, i + 2);
	}
}

Point SnakeGame::showFood(deque<Point> &snake, pair<int, int> &size_map)
{
	auto food_position = Point();
	auto snake_head = snake.back();	
	int x, y;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution1(4, size_map.first - 4);
	uniform_int_distribution<int> distribution2(4, size_map.second - 4);
	do
	{
		x = distribution1(gen);
		y = distribution2(gen);

		if (all_of(snake.begin(), snake.end(), [=](Point position) { return position.getX() != x || position.getY() != y; })
				&& (abs(snake_head.getX() - x) + abs(snake_head.getY() - y) > 8))
		{
			food_position.setX(x);
			food_position.setY(y);
		}
	} while (food_position.compare(Point()));

	set_console_backgroundcolor(4);
	write_at_position(" ", food_position.getX() + 1, food_position.getY() + 1);

	return food_position;
}

int SnakeGame::getScore()
{
	return score;
}

void SnakeGame::displayScore(int player_score)
{
	write_at_position("PUNTAJE:\t" + to_string(player_score), 0, 0);
}

void SnakeGame::showInstructions()
{
	char key;

	cout << "Instrucciones:\n\n";
	cout << "1. Para mover a la serpiente solo puedes usar las teclas \'a\', \'s\', \'d\' y \'w\'.\n\n";
	cout << "2. Perder\240s si la serpiente colisiona contra el borde del mapa o contra su \npropio cuerpo.\n\n";
	cout << "3. Ganar\240s 10 puntos cada vez que la serpiente coma su alimento.\n\n";
	cout << "\nPresiona la tecla <ENTER> para volver al men\243.\n";

	hide_cursor();
	do
	{
		key = console::get_key();
	} while (key != 13); //ENTER KEY
}

string SnakeGame::ask()
{
	string rpta;

	do
	{
		cout << "\250Realmente deseas salir del juego? (S)---(N):\t";
		getline(cin, rpta);

		if (!equals(rpta, "s") && !equals(rpta, "n"))
		{
			cerr << "\nERROR. Solo puede ingresar \'S\', \'s\', \'N\' o \'n\'.\n\n";
		}
	} while (!equals(rpta, "s") && !equals(rpta, "n"));

	return rpta;
}

void SnakeGame::run()
{
	SnakeGame snakegame;
	deque<Point> snake;
	Point current_position(0, 9);
	Point food_position = Point();
	SnakeGame::Direction direction = SnakeGame::Direction::right;
	pair<int, int> size_map(get_console_window_width(), get_console_window_height());	
	unsigned int snake_length = 3, snake_speed = 100, player_score = snakegame.getScore();	

	snake.push_back(current_position);
	snakegame.drawMap(size_map);
	snakegame.displayScore(player_score);	
	do
	{
		sleep_ms(snake_speed);
		snakegame.drawSnake(snake, current_position, size_map, snake_length);
		direction = snakegame.getDirection(direction);
		current_position = snakegame.getNextPosition(direction, current_position);
		if (current_position.compare(food_position))
		{
			food_position = Point();
			snake_length++;
			player_score += 10;			
			snakegame.displayScore(player_score);
		}
		if (food_position.compare(Point()))
		{
			food_position = snakegame.showFood(snake, size_map);
		}
		clear_console_input_buffer();
	} while (!snakegame.isOver(snake, current_position, size_map));
}

void SnakeGame::close()
{
	cout << "Gracias por jugar el videojuego.\nSi encuentra alg\243n bug, por favor rep\242rtelo al correo maxdr.mat\100gmail.com.\n\n";
	cout << "Presione cualquier tecla para salir.\n";
	console::get_key();
}
