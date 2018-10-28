#include "Wall.h"
#include <gl/freeglut.h>
#include <time.h>
#include <iostream>

void drawWallSegment(double, double, double, double);
int random(int, int);

Wall::Wall() {
	hole = random(470, 880);
	x = 1800;
}

Wall::~Wall() {}

void Wall::wallMove() {
	x--;
}

void Wall::drawWall() {
	drawWallSegment(x - 150, hole + 75, x, 980);
	drawWallSegment(x - 175, hole, x + 25, hole + 75);
	drawWallSegment(x - 175, hole - 325, x + 25, hole - 250);
	drawWallSegment(x - 150, 120, x, hole - 325);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

double Wall::getX() {
	return x;
}

bool Wall::checkCollision(double bY) {
	if (bY <= 120) {
		return true;
	}
	if (x - 175 > 200 || x + 25 < 100) {
		return false;
	}
	if (bY + 100 > hole || bY < hole - 250) {
		return true;
	}
	return false;
}

void drawWallSegment(double x1, double y1, double x2, double y2) {
	
	glColor3f(155.0 / 255, 230.0 / 255, 86.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 3, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 3, y2);
	glVertex2f(x1, y2);
	glEnd();

	glColor3f(215.0 / 255, 251.0 / 255, 129.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 3, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 6, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 6, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 3, y2);
	glEnd();

	glColor3f(155.0 / 255, 230.0 / 255, 86.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 6, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 12, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 12, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 6, y2);
	glEnd();

	glColor3f(117.0 / 255, 190.0 / 255, 47.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 12, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 15, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 15, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 12, y2);
	glEnd();

	glColor3f(155.0 / 255, 230.0 / 255, 86.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 15, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 18, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 18, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 15, y2);
	glEnd();

	glColor3f(117.0 / 255, 190.0 / 255, 47.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 18, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 46, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 46, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 18, y2);
	glEnd();

	glColor3f(82.0 / 255, 129.0 / 255, 35.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 46, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 49, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 49, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 46, y2);
	glEnd();

	glColor3f(117.0 / 255, 190.0 / 255, 47.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 49, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 52, y1);
	glVertex2f(x1 + (x2 - x1) / 60 * 52, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 49, y2);
	glEnd();

	glColor3f(82.0 / 255, 129.0 / 255, 35.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(x1 + (x2 - x1) / 60 * 52, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1 + (x2 - x1) / 60 * 52, y2);
	glEnd();

	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

int random(int min, int max) {
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}