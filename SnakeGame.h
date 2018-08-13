#pragma once
#include <deque>
#include <utility>
#include "Point.h"

class SnakeGame
{
private:
	int score;	
	Point food;

public:
	enum Level
	{
		EASY = 1, NORMAL, HARD, INSANE
	};
	enum Direction
	{
		UP, DOWN, LEFT, RIGHT
	};
	SnakeGame();
	bool isOver(std::deque<Point> &snake, Point &target_position, std::pair<int, int> &size_map);
	void drawSnake(std::deque<Point> &snake, Point &target_position, std::pair<int, int> &size_map, unsigned int snake_length);
	Direction getDirection(SnakeGame::Direction current_direction);
	Point getNextPosition(SnakeGame::Direction direction, Point &current_position);
	void drawMap(std::pair<int, int> &size_map);
	Point showFood(std::deque<Point> &snake, std::pair<int, int> &size_map);
	int getScore();	
	void displayScore(int player_score);	
	void showInstructions();
	std::string askUser();
	void run(int snake_speed);
	void reload();
	void close();	
};
