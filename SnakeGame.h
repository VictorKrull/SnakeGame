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
		easy, normal, hard, insane
	};
	enum Direction
	{
		up, down, left, right
	};
	SnakeGame();
	bool isOver(std::deque<Point>&, Point&, std::pair<int, int>&);
	void drawSnake(std::deque<Point>&, Point&, std::pair<int, int>&, unsigned int);
	Direction getDirection(SnakeGame::Direction);
	Point getNextPosition(SnakeGame::Direction, Point&);
	void drawMap(std::pair<int, int>&);
	Point showFood(std::deque<Point>&, std::pair<int, int>&);
	int getScore();	
	void displayScore(int);
	void showInstructions();
	std::string ask();
	void run();
	void close();	
};
