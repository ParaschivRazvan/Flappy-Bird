#include <windows.h>
#include <gl/freeglut.h>
#include <Wall.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "SOIL.h"

using namespace std;

#define checkImageWidth 17
#define checkImageHeight 12

short int gameState = 0;
int rotateAng = 0, maxScore = 0, currScore = 0;
double birdY = 0; 
int flapUnits = 0;
vector<Wall> wallV;


static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;
static GLuint texture;

void drawBackground();

void drawScore(int, int, int);

void LoadTexture(void)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image("bg.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

void makeImage(void)
{
	for (int i = 0; i < checkImageHeight; i++) {
		for (int j = 0; j < checkImageWidth; j++) {
			checkImage[i][j][0] = (GLubyte)0;
			checkImage[i][j][1] = (GLubyte)0;
			checkImage[i][j][2] = (GLubyte)0;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}


	for (int j = 0; j < checkImageWidth; j++) {


		if (j < 7 || j > 10) {

			checkImage[0][j][0] = (GLubyte)0;
			checkImage[0][j][1] = (GLubyte)153;
			checkImage[0][j][2] = (GLubyte)204;
			checkImage[0][j][3] = (GLubyte)0;
		}

		if (j < 5 || j > 15) {

			checkImage[1][j][0] = (GLubyte)0;
			checkImage[1][j][1] = (GLubyte)153;
			checkImage[1][j][2] = (GLubyte)204;
			checkImage[1][j][3] = (GLubyte)0;
		}

		if (j > 6 && j < 11) {

			checkImage[1][j][0] = (GLubyte)204;
			checkImage[1][j][1] = (GLubyte)204;
			checkImage[1][j][2] = (GLubyte)0;
			checkImage[1][j][3] = (GLubyte)255;
		}

		if (j < 4 || j > 15) {

			checkImage[2][j][0] = (GLubyte)0;
			checkImage[2][j][1] = (GLubyte)153;
			checkImage[2][j][2] = (GLubyte)204;
			checkImage[2][j][3] = (GLubyte)0;
		}

		if (j > 4 && j < 10) {

			checkImage[2][j][0] = (GLubyte)204;
			checkImage[2][j][1] = (GLubyte)204;
			checkImage[2][j][2] = (GLubyte)0;
			checkImage[2][j][3] = (GLubyte)255;

		}

		if (j > 10 && j < 15) {

			checkImage[2][j][0] = (GLubyte)255;
			checkImage[2][j][1] = (GLubyte)140;
			checkImage[2][j][2] = (GLubyte)0;
			checkImage[2][j][3] = (GLubyte)255;

		}

		if (j < 2 || j > 15) {

			checkImage[3][j][0] = (GLubyte)0;
			checkImage[3][j][1] = (GLubyte)153;
			checkImage[3][j][2] = (GLubyte)204;
			checkImage[3][j][3] = (GLubyte)0;

		}

		if (j > 4 && j < 9) {

			checkImage[3][j][0] = (GLubyte)204;
			checkImage[3][j][1] = (GLubyte)204;
			checkImage[3][j][2] = (GLubyte)0;
			checkImage[3][j][3] = (GLubyte)255;
		}

		if (j < 1) {

			checkImage[4][j][0] = (GLubyte)0;
			checkImage[4][j][1] = (GLubyte)153;
			checkImage[4][j][2] = (GLubyte)204;
			checkImage[4][j][3] = (GLubyte)0;

		}

		if (j > 10 && j < 16) {

			checkImage[4][j][0] = (GLubyte)255;
			checkImage[4][j][1] = (GLubyte)140;
			checkImage[4][j][2] = (GLubyte)0;
			checkImage[4][j][3] = (GLubyte)255;

		}

		if (j > 1 && j != 5 && j < 10) {

			checkImage[4][j][0] = (GLubyte)255;
			checkImage[4][j][1] = (GLubyte)255;
			checkImage[4][j][2] = (GLubyte)0;
			checkImage[4][j][3] = (GLubyte)255;
		}

		if (j > 1 && j < 5) {

			checkImage[5][j][0] = (GLubyte)255;
			checkImage[5][j][1] = (GLubyte)255;
			checkImage[5][j][2] = (GLubyte)255;
			checkImage[5][j][3] = (GLubyte)255;

		}
		if (j > 15) {
			checkImage[5][j][0] = (GLubyte)0;
			checkImage[5][j][1] = (GLubyte)153;
			checkImage[5][j][2] = (GLubyte)204;
			checkImage[5][j][3] = (GLubyte)0;


		}
		if (j > 6 && j < 11) {

			checkImage[5][j][0] = (GLubyte)255;
			checkImage[5][j][1] = (GLubyte)255;
			checkImage[5][j][2] = (GLubyte)0;
			checkImage[5][j][3] = (GLubyte)255;

		}

		if (j > 14) {
			checkImage[6][j][0] = (GLubyte)0;
			checkImage[6][j][1] = (GLubyte)153;
			checkImage[6][j][2] = (GLubyte)204;
			checkImage[6][j][3] = (GLubyte)0;
			checkImage[7][j][0] = (GLubyte)0;
			checkImage[7][j][1] = (GLubyte)153;
			checkImage[7][j][2] = (GLubyte)204;
			checkImage[7][j][3] = (GLubyte)0;

		}

		if ((j > 0 && j < 6) || (j > 10 && j < 14)) {

			checkImage[6][j][0] = (GLubyte)255;
			checkImage[6][j][1] = (GLubyte)255;
			checkImage[6][j][2] = (GLubyte)255;
			checkImage[6][j][3] = (GLubyte)255;

		}

		if (j > 6 && j < 10) {

			checkImage[6][j][0] = (GLubyte)255;
			checkImage[6][j][1] = (GLubyte)255;
			checkImage[6][j][2] = (GLubyte)0;
			checkImage[6][j][3] = (GLubyte)255;

		}

		if ((j > 0 && j < 5) || (j > 9 && j < 12) || (j > 12 && j < 14)) {

			checkImage[7][j][0] = (GLubyte)255;
			checkImage[7][j][1] = (GLubyte)255;
			checkImage[7][j][2] = (GLubyte)255;
			checkImage[7][j][3] = (GLubyte)255;
		}

		if (j > 5 && j < 9) {

			checkImage[7][j][0] = (GLubyte)255;
			checkImage[7][j][1] = (GLubyte)255;
			checkImage[7][j][2] = (GLubyte)0;
			checkImage[7][j][3] = (GLubyte)255;

		}

		if ((j > 9 && j < 12) || (j > 12 && j < 14)) {

			checkImage[8][j][0] = (GLubyte)255;
			checkImage[8][j][1] = (GLubyte)255;
			checkImage[8][j][2] = (GLubyte)255;
			checkImage[8][j][3] = (GLubyte)255;

		}

		if (j > 4 && j < 9) {

			checkImage[8][j][0] = (GLubyte)255;
			checkImage[8][j][1] = (GLubyte)255;
			checkImage[8][j][2] = (GLubyte)0;
			checkImage[8][j][3] = (GLubyte)255;


		}

		if (j < 1 || j > 14) {

			checkImage[8][j][0] = (GLubyte)0;
			checkImage[8][j][1] = (GLubyte)153;
			checkImage[8][j][2] = (GLubyte)204;
			checkImage[8][j][3] = (GLubyte)0;

		}

		if (j < 3 || j > 13) {
			checkImage[9][j][0] = (GLubyte)0;
			checkImage[9][j][1] = (GLubyte)153;
			checkImage[9][j][2] = (GLubyte)204;
			checkImage[9][j][3] = (GLubyte)0;

		}
		if (j > 9 && j < 13) {

			checkImage[9][j][0] = (GLubyte)255;
			checkImage[9][j][1] = (GLubyte)255;
			checkImage[9][j][2] = (GLubyte)255;
			checkImage[9][j][3] = (GLubyte)255;



		}

		if (j > 3 && j < 9) {

			checkImage[9][j][0] = (GLubyte)255;
			checkImage[9][j][1] = (GLubyte)255;
			checkImage[9][j][2] = (GLubyte)0;
			checkImage[9][j][3] = (GLubyte)255;
		}

		if (j < 4 || j > 12) {

			checkImage[10][j][0] = (GLubyte)0;
			checkImage[10][j][1] = (GLubyte)153;
			checkImage[10][j][2] = (GLubyte)204;
			checkImage[10][j][3] = (GLubyte)0;
		}

		if (j > 5 && j < 10) {

			checkImage[10][j][0] = (GLubyte)255;
			checkImage[10][j][1] = (GLubyte)255;
			checkImage[10][j][2] = (GLubyte)0;
			checkImage[10][j][3] = (GLubyte)255;
		}

		if (j < 6 || j > 11) {

			checkImage[11][j][0] = (GLubyte)0;
			checkImage[11][j][1] = (GLubyte)153;
			checkImage[11][j][2] = (GLubyte)204;
			checkImage[11][j][3] = (GLubyte)0;

		}
	}

	checkImage[10][11][0] = (GLubyte)255;
	checkImage[10][11][1] = (GLubyte)255;
	checkImage[10][11][2] = (GLubyte)255;
	checkImage[10][11][3] = (GLubyte)255;

	checkImage[3][10][0] = (GLubyte)255;
	checkImage[3][10][1] = (GLubyte)140;
	checkImage[3][10][2] = (GLubyte)0;
	checkImage[3][10][3] = (GLubyte)255;

	checkImage[5][1][0] = (GLubyte)255;
	checkImage[5][1][1] = (GLubyte)255;
	checkImage[5][1][2] = (GLubyte)0;
	checkImage[5][1][3] = (GLubyte)255;

	checkImage[5][5][0] = (GLubyte)255;
	checkImage[5][5][1] = (GLubyte)255;
	checkImage[5][5][2] = (GLubyte)0;
	checkImage[5][5][3] = (GLubyte)255;

}

void init(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW); 
	gluOrtho2D(0.0, 1600.0, 980.0, 720.0); 
	makeImage(); //create texture
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	LoadTexture();

	glutIgnoreKeyRepeat(true); 
}


void DrawImage(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground();

	if (gameState == 0) {
		const unsigned char* text = reinterpret_cast<const unsigned char* >("Press space to start...");
		glRasterPos3f(700, 500, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, text);

		text = reinterpret_cast<const unsigned char* >("HIGH SCORE: ");
		glRasterPos3f(710, 400, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, text);

		drawScore(880, 400, maxScore);

		glutSwapBuffers();
		glFlush();
	}

	if (gameState == 1) {
		
		glMatrixMode(GL_PROJECTION);

		glPushMatrix();
		glLoadIdentity();

		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glLoadIdentity();

		glDisable(GL_LIGHTING);


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName);

		// Draw a textured quad

		glPushMatrix();
		glTranslated(0, birdY, 0);


		glPushMatrix();
		glTranslated(150, 350, 0);
		glRotated(rotateAng, 0, 0, 1);
		glTranslated(-150, -350, 0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(100, 300);
		glTexCoord2f(0, 1); glVertex2f(100, 400);
		glTexCoord2f(1, 1); glVertex2f(200, 400);
		glTexCoord2f(1, 0); glVertex2f(200, 300);
		glEnd();

		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);

		
		for (int i = 0; i < wallV.size(); i++) {
			wallV[i].drawWall();
		}


		glColor3f(0, 0, 0);
		drawScore(800, 900, currScore);

		glMatrixMode(GL_MODELVIEW);
		glutSwapBuffers();
		glFlush();
	}

	if (gameState == 2) {

		const unsigned char* text = reinterpret_cast<const unsigned char* >("GAME OVER!");
		glRasterPos3f(700, 500, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, text);

		text = reinterpret_cast<const unsigned char* >("Your score: ");
		glRasterPos3f(700, 400, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, text);

		drawScore(830, 400, currScore);

		glutSwapBuffers();
		glFlush();
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1600.0, 0.0, 980.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void myKeyboardFunc(unsigned char Key, int x, int y)
{
	if (gameState == 0) {
		if (Key == ' ') {
			wallV.clear();
			birdY = 0;
			currScore = 0;
			gameState = 1;
		}
	}

	if (gameState == 1) {
		if (Key == ' ') {
			flapUnits += 100;

		}
	}

	if (gameState == 2) {
		if (Key == ' ') {
			if (maxScore < currScore) {
				maxScore = currScore;
			}
			gameState = 0;
		}
	}
}


void timer(int) {
	if (gameState == 1) {
		static time_t t = time(&t);

		if (birdY + 300 < 880  && flapUnits) {
			birdY++;
			flapUnits--;
		}
		else if (flapUnits == 0) {
			birdY -= 1.4;
		}
		else if (birdY + 300 >= 880 && flapUnits) {
			flapUnits = 0;
		}

		//bird rotation
		if (flapUnits && rotateAng < 45) {
			rotateAng += 1;
		}
		if (flapUnits == 0 && rotateAng > -45) {
			rotateAng -= 1;
		}

		//walls movement
		if (difftime(time(0), t) > 2) {
			wallV.push_back(Wall());
			time(&t);
		}
		for (int i = 0; i < wallV.size(); i++) {
			wallV[i].wallMove();
		}

		//delete the walls that leave the window
		if (wallV.size() && wallV[0].getX() < -200) {
			wallV.erase(wallV.begin());
		}

		//add to current score
		if (wallV.size() && wallV[0].getX() == 100) {
			currScore++;
		}

		//check collision
		if (wallV.size() && wallV[0].checkCollision(birdY + 300)) {
			gameState = 2;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(1, timer, 0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // use a single buffer | coloring mode RGB
	glutInitWindowPosition(150, 10); // initial pozition of the main window
	glutInitWindowSize(1600, 980); // window size
	glutCreateWindow("Flappy Bird"); // create window with proper name

	init(); // execute intialization pozition
	glClear(GL_COLOR_BUFFER_BIT); // reprezentation and coloring of the main window
	glutDisplayFunc(DrawImage); // call DrawImage
	glutKeyboardFunc(myKeyboardFunc);
	glutTimerFunc(1, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop(); 
}


void drawBackground() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	//glTranslated(0, 120, 0);
	//glRotatef(60.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 120.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1600.0, 120.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1600.0, 980.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 980.0, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	

	glColor3f(221.0 / 255, 216.0 / 255, 148.0 / 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(1600, 0);
	glVertex2f(1600, 120);
	glVertex2f(0, 120);
	glEnd();

	for (int i = -20; i < 1600; i = i + 27) {
		if (i % 2) {
			glColor3f(116.0 / 255, 191.0 / 255, 49.0 / 255);
		}
		else {
			glColor3f(154.0 / 255, 229.0 / 255, 87.0 / 255);
		}
		glBegin(GL_POLYGON);
		glVertex2f(i, 95);
		glVertex2f(i + 20, 115);
		glVertex2f(i + 48, 115);
		glVertex2f(i + 28, 95);
		glEnd();
	}

	glBegin(GL_LINES);
	glColor3f(82.0 / 255, 117.0 / 255, 13.0 / 255);
	glVertex2f(0, 94);
	glVertex2f(1600, 94);
	glColor3f(197.0 / 255, 176.0 / 255, 87.0 / 255);
	glVertex2f(0, 91);
	glVertex2f(1600, 91);
	glEnd();


	glColor3f(0, 0, 0);
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(1600, 0);
	glVertex2f(1600, 120);
	glVertex2f(0, 120);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void drawScore(int x, int y, int score) {
	do {
		glRasterPos3f(x, y, 0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)score % 10 + '0');
		score /= 10;
		x -= 11;
	} while (score);
}
