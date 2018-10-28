#pragma once
class Wall
{
private:
	double x, hole;
public:
	Wall();
	~Wall();

	void wallMove();

	void drawWall();

	double getX();

	bool checkCollision(double);
};

