//////////////////////////////////////////////
////										//
////	CPT205 Assignment 1					//
////	Shuchen Yuan						//
////	2036501                             //
////    Just run the program and            //
////    follow the instruction              //
////    enjoy!                              //
//////////////////////////////////////////////

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include<math.h>
#include "vector"
using namespace std;
int intWinWidth = 1200; //Default window size
int intWinHeight = 700;

float fltAnimationOffset = 0.0; //Animation offsets for various objects
float fltTreeOffset = 0.0;
float fltBuildingOffset = -2000.0;
float fltPoleOffset = 750.0;

float p1 = 500;
float p2 = 1200;
float p3 = -700;
float s1 = 10;
float s2 = 30;
float s3 = 50;
float s4 = 60;

int flag =  1;

float fltAcceleration = 3.0; //Speed of animation
float fltColourVal1 = 0.5; //First colour value
float fltColourVal2 = 0.7; //Second colour value
float fltColourVal3 = 0.4; //Third colour value

float fltFOV = 60; //Field Of View 0 - 90 is ok
float fltZoom = 1.0; //Zoom amount

float fltX0 = 0.0; //Camera position
float fltY0 = 200.0;
float fltZ0 = -1500.0;

float fltXRef = 0.0; //Look At reference point
float fltYRef = fltY0;
float fltZRef = 4000.0;

float fltXUp = 0.0; //Up vector
float fltYUp = 1.0;
float fltZUp = 0.0;

float fltViewingAngle = 0; //Used for rotating camera

float angle = 0; // the door angle to minic opening

float tyreangle1 = 0;
float tyreangle2 = 0;

void window();

void window1();

void thetopfence();

void downtheshelter();

void theadboard();

void table1();

void table2();

void stairs();

void tree();

void textureframe();

void car();

void tyre1();

void tyre2();

void material();

void adjustDisplay(unsigned char key, int x, int y)
{
	// exit the program
	if (key == 'q' || key == 'Q')
		exit(0);

	// the Movable view
	if (key == 'R' || key == 'r')
		fltXRef = 0.0; //Look At reference point
	    fltYRef = fltY0;
        fltZRef = 4000.0;
		// movement
		if (key == 'w' || key == 'W')
			if (fltZ0 < 1400)
			{
				fltZ0 += 50; 
			} // move forward
			
		if (key == 's' || key == 'S')
			if (fltZ0 >= -1500)
			{
				fltZ0 -= 50;
			}
		if (key == 'a' || key == 'A')
			if (fltX0 <= 1100)
			{
				fltX0 += 50;
			}
		
		if (key == 'd' || key == 'D')
			if (fltX0 >= -1100)
			{
				fltX0 -= 50;
			}

		if (key == 'j' || key == 'J')
			if (fltXRef <= 650)
			{
				fltXRef += 100;
				fltZRef -= 200;

			}
			
		if (key == 'l' || key == 'L')
			if (fltXRef >= -650)
			{
				fltXRef -= 100;
				fltZRef -= 200;
			}
			
		if (key == 'i' || key == 'I')
			fltYRef += 200;
		    fltZRef -= 200;
		if (key == 'k' || key == 'K')
			fltYRef -= 200;
		    fltZRef -= 200;
		if (key == 'U' || key == 'u')
			if (fltY0 <= 1070)
			{
				fltY0 += 20;
			}
		if (key == ' ')
			if (fltY0 >= 100)
			{
				fltY0 -= 20;
			}
			

	glutPostRedisplay();
}

void animateTracks()
{
	//Increments/decrements animation variables
	// the speed of the car in near-house channel
	if (p1 > 1200) {
		p1 = -1100;
		flag = 1;
	}


	if (p1 < -1100)
	{
		p1 = 1200;
		flag = 1;
		angle = 0;
	}
	
	
	if (p1 != 300 && (flag == 1)) {
		p1 -= s1;
	}
	if ((p1 == 300) && (flag == 1))

		if (angle >= 0.0) {
			angle += 2;
		}
	if (flag == 1 && angle == 60)
	{
		flag = 0;
	}
	if (angle > 0.0 && flag == 0) {
		angle -= 2;
	}
	if (angle == 0 && flag == 0)
	{
		p1 -= s1;
	}

	p2 -= s2;
	if (p2 > 1200)
		p2 = -1100;
	if (p2 < -1100)
	{
		p2 = 1200;
	}

	if (p2 > 1200)
		p2 = -1100;
	if (p2 < -1100)
	{
		p2 = 1200;
	}
	// the speed of spinning of the wheel
	tyreangle1 += 3;
	tyreangle2 += 6;


	
		glutPostRedisplay();
}

void material(GLfloat r, GLfloat g, GLfloat b) {
	GLfloat mat_ambient[] = { 0.7f * r, 0.7f * g, 0.7f * b, 1.0f };  //the ambitet
	GLfloat mat_diffuse[] = { 1,1,1, 1.0f };  //the difffuse
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };   //the specular
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0f };   //emission color  =the original color of the material
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

} // the wireframe is supposed to be black 


void textureframe() {
	// unit window can be scale at any size
	// the down part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66 , 0.66 ,0.66);
	glTranslatef(0.0, 25, -50);
	glScalef(60, 20, 5);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0,0.0,0.0);
	glutWireCube(1);
	glPopMatrix();

	// the upper part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(0.0, 105, -50);
	glScalef(60, 20, 5);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the left part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(40, 65, -50);
	glScalef(20, 100, 5);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	//// the right part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(-40, 65, -50);
	glScalef(20, 100, 5);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the plate for texture
	glPushMatrix();
	glColor3f(1.0, 0, 0.0);
	material(1.0, 0.54, 0.0);
	glTranslatef(0.0,65,-50);
	glScalef(60, 60, 2);
	glutSolidCube(1);
	glColor3f(0.0, 0.0,0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

}

void house()
{
	// the left wall
	
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0.0 , 0.19 , 0.0);
	glTranslatef(1000, 110.0, 500.0);// (1000, 10, 500)
	glScalef(20, 1000, 1000);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	// the right wall
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0,0.19 ,0);
	glTranslatef(-1000, 110.0, 500.0);
	glScalef(20, 1000, 1000);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();


	// the upper wall
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0,0.19,0);
	glTranslatef(0, 110.0, 1000);
	glScalef(2000, 2500, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	// the stair
	glPushMatrix();
	glTranslatef(110, 0, 1000);
	glScalef(1.0, 1.0, 1.0);
	//glRotatef(90, 0.0, 1.0, 0.0);
	stairs();
	glPopMatrix();

	// table in the 1st floor
	glPushMatrix();
	glTranslatef(-800, -90, 200);
	glScalef(1.0, 1.0, 1.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-500, -90, 200);
	glScalef(1.0, 1.0, 1.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, -90, 200);
	glScalef(1.0, 1.0, 1.0);
	table1();
	glPopMatrix();
	
	// the long table in the 1st door
	glPushMatrix();
	glTranslatef(-530, -90, 630);
	glScalef(0.8, 1.0, 0.7);
	table2();
	glPopMatrix();

	// bar table
	//the side one
	glPushMatrix();
	glColor3f(0.66,0.66,0.66);
	material(0.66, 0.66,0.66);
	glTranslatef(375, 220, 675);
	glScalef(50, 20, 450);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	//// the front one
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(700, 220, 500);
	glScalef(600, 20, 100);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	for (size_t i = 0; i < 30; i++)
	{
		glPushMatrix();
		glColor3f(1.0, 0.54, 0.0);
		material(1.0 ,0.54 , 0.0);
		glTranslatef(980 - i * 20, 100, 470);
		glScalef(10, 210, 10);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
	 	material(0,0,0);
		glutWireCube(1);
		glPopMatrix();
	}
	for (size_t i = 0; i <23; i++)
	{
		glPushMatrix();
		glColor3f(1.0, 0.54, 0.0);
		material(1.0, 0.54, 0.0);
		glTranslatef(380, 100, 470 + 20 *i);
		glScalef(10, 210, 10);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
	 	material(0,0,0);
		glutWireCube(1);
		glPopMatrix();
	}
	 
	// draw the texture frame for 1f
	// the texture on the back-front wall
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(300 ,400, 1000);
	glScalef(1.0, 2.0, 0.5);
	textureframe();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(50, 300, 1000);
	glScalef(1.0, 2.0, 0.5);
	textureframe();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(550, 500, 1000);
	glScalef(1.0, 2.0, 0.5);
	textureframe();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(800, 600, 1000);
	glScalef(1.0, 2.0, 0.5);
	textureframe();
	glPopMatrix();

	// the texture frame on the right side wall of 1st floor
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(-500, 170, 1000);
	glScalef(4, 2, 0.5);
	textureframe();
	glPopMatrix();

	// the texture frame on the right side wall of 2nd floor
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(-500, 900, 1000);
	glScalef(5, 3, 0.5);
	textureframe();
	glPopMatrix();


	// the texture frame on the right side wall
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(700, 200, 1000);
	glScalef(4, 2, 0.5);
	textureframe();
	glPopMatrix();


	// the texture on the left hand side wall of 1st floor
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(1000, 200 ,200);
	glScalef(0.5, 2 , 2);
	glRotatef(90, 0,1,0);
	textureframe();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(1000, 200, 800);
	glScalef(0.5, 2, 2);
	glRotatef(90, 0, 1, 0);
	textureframe();
	glPopMatrix();

	// the texture frame of the lef hand side in 2nd floor
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(1000, 800, 600);
	glScalef(0.5, 3, 5);
	glRotatef(90, 0, 1, 0);
	textureframe();
	glPopMatrix();

	// the textrue frame on the right hand side wall
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	glTranslatef(-955, 0, 500);
	glScalef(0.5, 5, 8);
	glRotatef(90, 0, 1, 0);
	textureframe();
	glPopMatrix();

	// the front door of the 1st floor
	// the down side
	// the wall
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66 , 0.66);
	glTranslatef(-840, 110.0, 0.0);
	glScalef(300, 1000, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the upper board on the wall
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54 ,0.0);
	glTranslatef(-840, 460.0, -20.0);
	glScalef(300, 170, 10);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the down board on the wall
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);
	glTranslatef(-840, 200, -20.0);
	glScalef(300, 290, 10);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0,0.0,0.0);
	glutWireCube(1);
	glPopMatrix();


	// the second right glass wall
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(-570, -25.0, 40.0);
	glScalef(1.5, 3.05, 1.0);
	window();
	glPopMatrix();

	//// to fill in the door
	for (size_t i = 0; i < 10; i++)
	{
		//for the most right
		glPushMatrix();
		material(1.0, 0.54, 0.0);
		glColor3f(1.0, 0.54, 0.0);
		glTranslatef(-570, 100 + i * 40, -10);
		glScalef(180, 25, 10);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0,0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();

		// for the most left
		glPushMatrix();
		glColor3f(1.0, 0.54, 0.0);
		material(1.0, 0.54, 0.0);
		glTranslatef(535, 100 + i * 40, -10);
		glScalef(180, 25, 10);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
	}


	// the glass door in the front side
	// gap x = 210
	for (size_t j = 0; j < 2; j++)
	{
		glPushMatrix();
		glColor3f(0.66, 0.66, 0.66);
		material(0.66,0.66,0.66);
		glTranslatef(535 - 210 * j, -25.0, 40.0);
		glScalef(1.5, 3.05, 1.0);
		window();
		glPopMatrix();
	}

	// the door that can be open
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66,0.66,0.66);

	glTranslatef(535 - 210 * 2 - 30 - 60 - 30, -25.0, -10.0);
	glScalef(1.5, 3.05, 1.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	window1();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);
	glTranslatef(535 - 210 * 2 - 30 - 210, -25.0, 40.0);
	glScalef(1.5, 3.05, 1.0);
	window();
	glPopMatrix();


	glPushMatrix();

	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(535 - 210 * 2 - 30 - 210 - 210, -25.0, 40.0);
	glScalef(1.5, 3.05, 1.0);
	window();
	glPopMatrix();
	
	// the front side which contains the wall and the window
	// the left stripper board (gap x = 60)
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0 ,0.54, 0.0);
	glTranslatef(980, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);
	glTranslatef(920, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(860, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(800, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(740, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(680, 660, -25);
	glScalef(40, 1350, 40);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	// the board on the left
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66,0.66);

	glTranslatef(-810, 480, -175);
	glScalef(210, 400, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	
	// upper floor
	// the frame of the total floor
	glPushMatrix();
	glTranslatef(0.0, 600, 422);
	glScalef(2070, 100, 1170);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2);
	glutWireCube(1);
	material(0, 0, 0);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.96, 1.0, 0.98);
	material(1.0, 1.0, 1.0);

	glTranslatef(0.0, 600, 280);
	glScalef(2070, 100, 870);
	glutSolidCube(1);
	glPopMatrix();

	//  compensate block
	glPushMatrix();
	glColor3f(0.96,1.0,0.98);
	material(1.0, 1.0, 1.0);
	 
	glTranslatef(1010, 598, 800);
	glScalef(45, 100, 400);
	glutSolidCube(1);

	glPopMatrix();

	glPushMatrix();
	glColor3f(0.96, 1.0, 0.98);
	material(1.0, 1.0, 1.0);
	 
	glTranslatef(-433, 598, 800);
	glScalef(1200, 100, 400);
	glutSolidCube(1);
	glPopMatrix();


	// the left wall of the 2nd floor
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0.0, 0.19, 0.0);

	glTranslatef(1000, 950.0, 500.0);// (1000, 10, 500)
	glScalef(20, 800, 1000);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0,0.0,0);
	glutWireCube(1);
	glPopMatrix();

	// the right wall
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0.0, 0.19, 0.0);
	glTranslatef(-1000, 950.0, 500.0);// (1000, 10, 500)
	glScalef(20, 800, 1000);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0);
	glutWireCube(1);
	glPopMatrix();


	//	the right part of stripper board
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);
	glTranslatef(-610, 680, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 750, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 820, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 890, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 960, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 1030, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 1100, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 1170, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 1240, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(-610, 1310, -20);
	glScalef(800, 40, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);


	glutWireCube(1);
	glPopMatrix();

	// the board on the stripper 

	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66,0.66,0.66);

	glTranslatef(-610, 1000, -50);
	glScalef(700, 390, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the whole outter frame of the window in the 2ne floor
	glPushMatrix();
	material(0.66, 0.66, 0.66);

	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(293, 600, 170);
	glScalef(6.35, 4.0, 3.00);
	window();
	glPopMatrix();


	// the left window
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(70, 718, 90);
	glScalef(2.0, 2.8, 1.0);
	window();
	glPopMatrix();

	// the right window
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(510, 718, 90);
	glScalef(2.0, 2.8, 1.0);
	window();
	glPopMatrix();

	// the stripper in between
	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54 ,0.0);
	glTranslatef(250, 1000, 30);
	glScalef(20, 480, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0,0.0,0.0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(280, 1000, 30);
	glScalef(20, 480, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0,0,0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);
	glTranslatef(310, 1000, 30);
	glScalef(20, 480, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.54, 0.0);
	material(1.0, 0.54, 0.0);

	glTranslatef(340, 1000, 30);
	glScalef(20, 480, 20);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	// the upper floor scence
	// the table in the top right corner
	glPushMatrix();
	glTranslatef(-750, 550, 780);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-750, 550, 430);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-300, 550, 450);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	table2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(130, 550, 320);
	glScalef(1.0, 1.0, 1.0);
	//glRotatef(90, 0.0, 1.0, 0.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400, 550, 320);
	glScalef(1.0, 1.0, 1.0);
	//glRotatef(90, 0.0, 1.0, 0.0);
	table1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(670, 550, 320);
	glScalef(1.0, 1.0, 1.0);
	//glRotatef(90, 0.0, 1.0, 0.0);
	table1();
	glPopMatrix();

	// the upperest floor
	glPushMatrix();
	glColor3f(0.0, 0.19,0.0);     
	material(0, 0.19, 0);

	glTranslatef(0.0, 1400, 500);
	glScalef(2100, 100, 1150);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glLineWidth(3);
	glutWireCube(1);
	glPopMatrix();
	
	// the flag
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66,0.66,0.66);
	glTranslatef(1500,345,470);
	glScalef(1.0, 3, 1.0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(10, 500, 20, 70 );
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	//glutWireCylinder(10, 100, 20, 70);
	glPopMatrix();

	// the board of the flag
	glPushMatrix();
	glColor3f(0.96, 1.0, 0.98);
	material(1.0, 0.54,0.0);
	glTranslatef(1500, 600, 500);
	glRotatef(-30,0,1,0);
	glScalef(500, 500, 30);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);

	glutWireCube(1);
	glPopMatrix();

	// the lefr side need two windows and two rain shelters and an ad board and two windows down for saling food
	// the upper windows on the wall
	// the first window
	glPushMatrix();
	glColor3f(0, 0, 0);
	material(0, 0, 0);

	glTranslatef(1120, 770, 230);
	glScalef(2.0, 2.0, 1.7);
	glRotatef(90, 0, 1, 0);
	window();
	glPopMatrix();

	// the second window
	glPushMatrix();
	glColor3f(0, 0, 0);
	material(0, 0, 0);

	glTranslatef(1120, 770, 730);
	glScalef(2.0, 2.0, 1.7);
	glRotatef(90, 0, 1, 0);
	window();
	glPopMatrix();

	// the rain shelter
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	material(1.0, 1.0, 1.0);

	glTranslatef(1080, 610, 220);
	glScalef(100, 30, 230.0);
	glRotatef(0, 0, 0, 0);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.96, 1.0, 0.98);
	material(1.0, 1.0, 1.0);

	glTranslatef(1080, 610, 720);
	glScalef(100, 30, 230.0);
	glRotatef(0, 0, 0, 0);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	// the down part
	// food entry for driver
	
	glPushMatrix();
	glTranslatef(1000, -0.0, 740);
	glScalef(1.0 , 1.0, 1.0);
	glRotatef(270, 0, 1, 0);
	glColor3f(0.0, 0.19, 0.0);
	downtheshelter();
	glPopMatrix();

	// take-out container
	glPushMatrix();
	glTranslatef(1000, -0.0, 240);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(270, 0, 1, 0);
	glColor3f(0.0, 0.19, 0.0);
	downtheshelter();
	glPopMatrix();

}

void downtheshelter() {
	
	// the frame of the window
	// the upper part
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	material(0.0,0.19,0.0);
	glTranslatef(0.0, 352, -50);
	glScalef(120, 25, 70);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0.0,0.0,0.0);
	glutWireCube(1);
	glPopMatrix();

	// the left part
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	glTranslatef(70 , 190, -50);
	glScalef(20, 350, 70);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	// the right part
	glPushMatrix();
	glColor3f(0.0, 0.19, 0.0);
	glTranslatef(-70, 190, -50);
	glScalef(20, 350, 70);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	
	// the platform
	 glPushMatrix();
	 glColor3f(0.0, 0.19, 0.0);
	glTranslatef(0.0,100,-60);
	glScalef(120, 170, 50);
	glRotatef(90, 0, 1, 0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	

	glPushMatrix();
	glTranslatef(-70, 170, -80);
	glScalef(1.4, 1, 1);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.44, 0.44, 0.44);
	material(0.44,0.44,0.44);
	glutSolidCylinder(10, 100, 20, 70);
	glPopMatrix();

	// the bar
	glPushMatrix();
	glTranslatef(-70, 170, -80);
	glScalef(1.4, 1, 1);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.44, 0.44, 0.44);
	material(0.44, 0.44, 0.44);

	glutSolidCylinder(10, 100, 20, 70);
	glPopMatrix();

	// the plate inside
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	material(1.0,1.0,0.0);
	glTranslatef(0.0, 265, -50);
	glScalef(140, 140, 7);
	glutSolidCube(1);
	glColor3f(0.0,0.0,0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

}

void theadboard()
{
 // the ad board is consisted of twe part
	//  the supporting pole and the board
	// the pole
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	//glTranslatef(0.0, 1710, -200);
	glTranslatef(0.0, 210, -100);
	glScalef(0.7, 2,  0.7);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(10, 100, 20, 70);
	glColor3f(0.66,0.66,0.66);
	glutWireCylinder(10, 100, 20, 70);
	glPopMatrix();

	// the plate
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(0.0, 345, -100);
	glScalef(150, 270, 1.0);
	glRotatef(90, 1, 0, 0);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
}

void thetopfence() {
	// the down part
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 25, -50);
	glScalef(120, 25, 10);
	glutSolidCube(1);

	glPopMatrix();

	// the upper part
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 175, -50);
	glScalef(120, 25, 10);
	glutSolidCube(1);


	glPopMatrix();

	// the left part
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(70, 100, -50);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glPopMatrix();

	// the right part
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-70, 100, -50);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glPopMatrix();
}

void window() {
	// unit window can be scale at any size
	// the down part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66 ,0.66 ,0.66);

	glTranslatef(0.0, 25, -50);
	glScalef(120, 25, 10);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the upper part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(0.0, 175, -50);
	glScalef(120, 25, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the left part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(70, 100, -50);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the right part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(-70, 100, -50);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

}

void window1() {
	// unit window can be scale at any size
	// the down part
	glPushMatrix();
	glTranslatef(60, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(0.0, 25, -0.0);
	glScalef(120, 25, 10);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the upper part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(0.0, 175, -0.0);
	glScalef(120, 25, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the left part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(70, 100, 0.0);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();

	// the right part
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	material(0.66, 0.66, 0.66);

	glTranslatef(-70, 100, 0.0);
	glScalef(20, 175, 10);
	glutSolidCube(1);
	glColor3f(0.66, 0.66, 0.66);
	glColor3f(0.0, 0.0, 0.0);
	material(0.0, 0.0, 0.0);

	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
}

void table1() {
		// the plate of the table 
	    glPushMatrix();
		glPushMatrix();
		glTranslatef(0.0, 200, -90);
		glScalef(100, 20, 200);
		glColor3f(1.0, 1.0, 1.0); // the SaddleBrown colour
		material(1.0, 0.74 ,0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(3);
		glPopMatrix();

		// the support of the table
		glPushMatrix();
		glTranslatef(0.0, 200, -90);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 1.0, 1.0); // the SaddleBrown colour
		material(1.0, 1.0, 1.0);
		glutSolidCylinder(1, 1, 10000, 1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(10, 100, 700, 1);
		glLineWidth(3);
		glPopMatrix();
		glPopMatrix();

		// the chair
		// the left one
		// the back
		glPushMatrix();
		glPushMatrix();
		glTranslatef(-100, 170, -85);
		glScalef(10, 100, 200);
		glRotatef(0, 0, 0, 0);
		glColor3f(1.0, 0.0, 0.0); // the Color of the chair
		material(1.0, 0.0, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0,0.0,0.0);
		glutWireCube(1);
		glLineWidth(3);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-70, 130, -85);
		glScalef(50, 20, 200);
		//glRotatef(180, 0, 0, 1);
		glColor3f(1.0, 0.0, 0.0); // the SaddleBrown colour
		material(1.0, 0.0, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(3);
		glPopMatrix();
		glPopMatrix();

		// the right one
		glPushMatrix();
		glPushMatrix();
		glTranslatef(100, 170, -85);
		glScalef(10, 100, 200);
		glRotatef(0, 0, 0, 0);
		glColor3f(1.0, 0.0, 0.0); // the SaddleBrown colour
		material(1.0, 0.0, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(3);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(70, 130, -85);
		glScalef(50, 20, 200);
		//glRotatef(180, 0, 0, 1);
		glColor3f(1.0, 0.0, 0.0); // the SaddleBrown colour
		material(1.0, 0.0, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(3);
		glPopMatrix();
		glPopMatrix();
}

void table2() {
		//the plate of the long desk
		glPushMatrix();
		glTranslatef(0.0, 230, 0.0);
		glScalef(600, 10, 200);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0, 0, 0);
		glutWireCube(1);
		glPopMatrix();

		// the support of the tables 
		glPushMatrix();
		glTranslatef(0.0, 230, -0.0);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0,0.0,0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 230, -0.0);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 230, -0.0);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);

		glLineWidth(1);
		glPopMatrix();

		// the chair
		// the plate of the chair
		glPushMatrix();
		glTranslatef(-200, 200, -200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		// the supporter of the chair
		glPushMatrix();
		glTranslatef(0.0, 200, -200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 200, -200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(+200, 200, -200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 200, 200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 200, 200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(+200, 200, 200);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0, 0.0, 0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		// the side one 
		glPushMatrix();
		glTranslatef(-400, 200, 0.0);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(0,0,0); // the color of the supporter
		material(0.0 ,0.0, 0.0);
		glutSolidCylinder(7, 70, 10000, 1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 10000, 1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(400, 200, 0.0);
		glScalef(1, 1, 1);
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(0.0,0.0,0.0);
		glutSolidCylinder(7, 70, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCylinder(7, 70, 30, 30);
		glLineWidth(1);
		glPopMatrix();

		
		glPushMatrix();
		glTranslatef(0.0, 200, -200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0,0.0,0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 200, -200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 200, 200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 200, 200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 200, 200);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(400, 200, 0.0);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-400, 200, 0.0);
		glScalef(100, 10, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();


		//the back of the chair
		glPushMatrix();
		glTranslatef(200, 230, 250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 230, 250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-200, 230, 250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 230, -250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 230, -250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-200, 230, -250);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();

		// the back of the chair

		glPushMatrix();
		glTranslatef(200, 260, 250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 260, 250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 260, 250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(200, 260, -250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 260, -250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200, 260, -250);
		glScalef(100, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		// the back of the side chair
		glPushMatrix();
		glTranslatef(-450, 260, 0.0);
		glScalef(5, 60, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0, 0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(450, 260, 0.0);
		glScalef(5, 60, 100);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0 ,0.0, 0.0);
		glutWireCube(1);
		glLineWidth(1);
		glPopMatrix();

		// the back supporter of the side chair
		glPushMatrix();
		glTranslatef(450, 230, 0.0);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-450, 230, 0.0);
		glScalef(10, 60, 5);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.7, 0.47); // the color of the supporter
		material(1.0, 0.7, 0.47);
		glutSolidCube(1);
		glPopMatrix();
}


void stairs() {
	// the stairs contains of multiple cubes with rising level
		for (size_t i = 0; i < 16; i++)
		{
		/*	for ( size_t j = 0; j < i + 1; j++)
			{*/
				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(50 * i, 200 + 30* i, -200);
				glScalef(50, 30, 200);
				//glRotatef(0,0,0,0);
				material(255.0 / 255 , 215.0 / 255 , 0.0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0 , 0.0);
				material(0,0,0);
				glutWireCube(1);
				glPopMatrix();
			/*}*/
		}

		// add a stage
		glPushMatrix();
		glColor3f(255.0 / 255, 215.0 / 255, 0.0);
		material(255.0 / 255, 215.0 / 255, 0.0);
		glTranslatef(50 * 16 + 25 , 200 + 30 * 15, -200);
		glScalef(100, 30, 200);
		//glRotatef(0,0,0,0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		material(0.0 , 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();

		for (size_t t = 0; t < 16; t++)
		{
			glPushMatrix();
			glColor3f(1.0, 0.70, 0.47);
			material(1.0, 0.70, 0.47);
			glTranslatef(-20 + 50 *t ,275 + 30* t,-295);
			glScalef(10, 120, 10);
			glutSolidCube(1);
			glRotatef(0, 0, 0, 0);
			glLineWidth(1);
			glColor3f(0, 0, 0);
			material(0.0, 0.0, 0.0);
			glutWireCube(1);
			glPopMatrix();
		}
		// the other part
			glPushMatrix();
			glColor3f(255.0 / 255, 215.0 / 255, 0.0);
			material(255.0 / 255, 215.0 / 255, 0.0);
			glTranslatef(-75 , 200 , -200);
			glScalef(100, 30, 200);
			glRotatef(0,0,0,0);
			glutSolidCube(1);
			glColor3f(0.0, 0.0, 0.0);
			material(0.0, 0.0, 0.0);
			glLineWidth(3);
			glutWireCube(1);
			glPopMatrix();

			// the fence 
			// the below one
			glPushMatrix();
			glColor3f(1.0, 0.70, 0.47);
			material(1.0, 0.70, 0.47);
			glTranslatef(-120, 275, -295);
			glScalef(10, 120, 10);
			glutSolidCube(1);
			glRotatef(0, 0, 0, 0);
			glLineWidth(3);
			glColor3f(0, 0, 0);
			material(0.0 , 0.0, 0.0);
			glutWireCube(1);
			glPopMatrix();

			// the bridge
			glPushMatrix();
			glColor3f(1.0, 0.70, 0.47);
			material(1.0, 0.70, 0.47);
			glTranslatef(-120, 340, -200);
			glRotatef(90, 1, 0, 0);
			glScalef(10, 200, 10);
			glutSolidCube(1);
			glLineWidth(3);
			glColor3f(0, 0, 0);
			material(0.0, 0.0, 0.0);
			glutWireCube(1);
			glPopMatrix();

			// the upper one 
			glPushMatrix();
			glColor3f(1.0, 0.70, 0.47);
			material(1.0, 0.70, 0.47);
			glTranslatef(-120, 275, -105);
			glScalef(10, 120, 10);
			glutSolidCube(1);
			glRotatef(0, 0, 0, 0);
			glLineWidth(3);
			glColor3f(0, 0, 0);
			material(0.0, 0.0, 0.0);
			glutWireCube(1);
			glPopMatrix();

			// THE DOWN PART
				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0/ 255, 215.0 /255, 0.0);
				glTranslatef(-50, 170 , -300);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();

				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(-50, 140, -350);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();

				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(-50, 110, -400);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();

				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(-50, 80, -450);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();

				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(-50, 50, -500);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();

				glPushMatrix();
				glColor3f(255.0 / 255, 215.0 / 255, 0.0);
				material(255.0 / 255, 215.0 / 255, 0.0);
				glTranslatef(-50, 20, -550);
				glScalef(150, 30, 100);
				glRotatef(0, 0, 0, 0);
				glutSolidCube(1);
				glColor3f(0.0, 0.0, 0.0);
				material(0.0, 0.0, 0.0);
				glutWireCube(1);
				glPopMatrix();
		// THE FENCE
					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0 ,0.70 , 0.47);
					glTranslatef(-120, 245, -345);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(3);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 215, -395);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 185, -445);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(3);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 155, -495);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 125, -545);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 95, -595);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();
		// the left part
					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 245, -345);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 215, -395);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 185, -445);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 155, -495);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 125, -545);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 95, -595);
					glScalef(10, 120, 10);
					glutSolidCube(1);
					glRotatef(0, 0, 0, 0);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();
		// the bar
					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(20, 243, -443);
					glRotatef(58.85, 1, 0, 0);
					glScalef(10, 360, 10);
					glutSolidCube(1);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(-120, 243, -443);
					glRotatef(58.85, 1, 0, 0);
					glScalef(10, 360, 10);
					glutSolidCube(1);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();

		// the upper bar
					glPushMatrix();
					glColor3f(1.0, 0.70, 0.47);
					material(1.0, 0.70, 0.47);
					glTranslatef(382.5, 575.5, -295);
					glRotatef(-58.85, 0, 0, 1);
					glScalef(10, 830, 10);
					glutSolidCube(1);
					glLineWidth(1);
					glColor3f(0, 0, 0);
					material(0.0, 0.0, 0.0);
					glutWireCube(1);
					glPopMatrix();
}

void car1() {

		tyre1();
		//glPopMatrix();
		glPushMatrix();
		glTranslatef(-170, 0, 0);
		glScalef(1, 1, 1);
		glRotatef(0, 0, 0, 0);
		tyre1();
		glPopMatrix();

		// the desk
		glPushMatrix();
		glTranslatef(-90, 160, 140);
		glScalef(400, 120, 280);
		glRotatef(0, 0, 0, 0);
		glColor3f(1.0, 0.74, 0);
		material(1, 0.74, 0.0);
		glutSolidCube(1);
		glColor3f(0, 0, 0);
		material(0,0,0);
		glutWireCube(1);
		glPopMatrix();

		// the top desk
		glPushMatrix();
		glTranslatef(-60, 270, 140);
		glScalef(120, 100, 280);
		glRotatef(0, 0, 0, 0);
		glColor3f(1.0, 0.74, 0);
		material(1.0 ,0.74, 0.0);
		glutSolidCube(1);
		glColor3f(0, 0, 0);
		material(0,0,0);
		glutWireCube(1);
		glPopMatrix();
}

void car2() {
	tyre2();
	//glPopMatrix();
	glPushMatrix();
	glTranslatef(-170, 0, 0);
	glScalef(1, 1, 1);
	glRotatef(0, 0, 0, 0);
	tyre2();
	glPopMatrix();

	// the desk
	glPushMatrix();
	glTranslatef(-90, 160, 140);
	glScalef(400, 120, 280);
	glRotatef(0, 0, 0, 0);
	glColor3f(1.0, 0.74, 0);
	material(1, 0.74, 0.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

	// the top desk
	glPushMatrix();
	glTranslatef(-60, 270, 140);
	glScalef(120, 100, 280);
	glRotatef(0, 0, 0, 0);
	glColor3f(1.0, 0.74, 0);
	material(1.0, 0.74, 0.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	material(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();

}

void tyre1() {
	
	// the car is consisted of the top, the door and the main body as well as the tyre
	// the tyre on the right
	material(0.0, 0.0, 0.0);// the color of the tyre
	glPushMatrix();
	glScalef(0.7, 1.2, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glRotatef(tyreangle1, 0, 0, 1);
	glScalef(10, 10, 7);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidTorus(1, 4, 30, 30);
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(1, 4, 30, 30);
	glPopMatrix();

	// the pan on the tyre
	material(105/ 255.0 , 105 / 255.0, 105 / 255.0);
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glScalef(10, 10, 1);
	glRotatef(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();

	// wheel hub bi 
	for (size_t i = 0; i < 3; i++)
	{
		//glPushMatrix();
		//glRotatef(0 + 60 * i , 0,0,1);
		material(1.0 ,1.0 ,1.0);
		glPushMatrix();
		glTranslatef(0.0, 100, 0.0);
		glRotatef(tyreangle1, 0, 0, 1);
		glScalef(0.66, 0.66, 0.66);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(0 + 120 * i, 0, 1, 0);
		glColor3f(0.66, 0.66, 0.66);
		glutSolidCylinder(1, 60, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCylinder(1, 60, 30, 30);

		glPopMatrix();
		//glPushMatrix();
	}

	// the tyre on the left
	material(0.0, 0.0, 0.0);// the color of the tyre
	glPushMatrix();
	glTranslatef(0.0, 100, 280);
	glScalef(10, 10, 7);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidTorus(1, 4, 30, 30);
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(1, 4, 30, 30);
	glPopMatrix();

	// the pan on the tyre
	material(0.66,0.66,0.66);
	glPushMatrix();
	glTranslatef(0.0, 100, 280);
	glScalef(10, 10, 1);
	glRotatef(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();

	// wheel hub bar
	for (size_t i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 100, 280);
		glRotatef(tyreangle1, 0, 0, 1);
		glScalef(0.66, 0.66, 0.66);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(0 + 120 * i, 0, 1, 0);
		glColor3f(0.66, 0.66, 0.66);
		glutSolidCylinder(1, 60, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCylinder(1, 60, 30, 30);
		glPopMatrix();
	}
	// the bridge between the tyres
	material(0.0 ,0.0 ,0.0); // the  color of the bar 
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glScalef(1, 1, 70);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();
	glPopMatrix();
}

void tyre2() {
	// the car is consisted of the top, the door and the main body as well as the tyre
	// the tyre on the right
	material(0.0, 0.0, 0.0);// the color of the tyre
	glPushMatrix();
	glScalef(0.7, 1.2, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glRotatef(tyreangle2, 0, 0, 1);
	glScalef(10, 10, 7);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidTorus(1, 4, 30, 30);
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(1, 4, 30, 30);
	glPopMatrix();

	// the pan on the tyre
	material(105 / 255.0, 105 / 255.0, 105 / 255.0);
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glScalef(10, 10, 1);
	glRotatef(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();

	// wheel hub bi 
	for (size_t i = 0; i < 3; i++)
	{
		//glPushMatrix();
		//glRotatef(0 + 60 * i , 0,0,1);
		material(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.0, 100, 0.0);
		glRotatef(tyreangle2, 0, 0, 1);
		glScalef(0.66, 0.66, 0.66);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(0 + 120 * i, 0, 1, 0);
		glColor3f(0.66, 0.66, 0.66);
		glutSolidCylinder(1, 60, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCylinder(1, 60, 30, 30);

		glPopMatrix();
		//glPushMatrix();
	}

	// the tyre on the left
	material(0.0, 0.0, 0.0);// the color of the tyre
	glPushMatrix();
	glTranslatef(0.0, 100, 280);
	glScalef(10, 10, 7);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidTorus(1, 4, 30, 30);
	glColor3f(0.0, 0.0, 0.0);
	glutWireTorus(1, 4, 30, 30);
	glPopMatrix();

	// the pan on the tyre
	material(0.66, 0.66, 0.66);
	glPushMatrix();
	glTranslatef(0.0, 100, 280);
	glScalef(10, 10, 1);
	glRotatef(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();

	// wheel hub bar
	for (size_t i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 100, 280);
		glRotatef(tyreangle2, 0, 0, 1);
		glScalef(0.66, 0.66, 0.66);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(0 + 120 * i, 0, 1, 0);
		glColor3f(0.66, 0.66, 0.66);
		glutSolidCylinder(1, 60, 30, 30);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCylinder(1, 60, 30, 30);
		glPopMatrix();
	}
	// the bridge between the tyre
	material(0.0, 0.0, 0.0); // the  color of the bar 
	glPushMatrix();
	glTranslatef(0.0, 100, 0.0);
	glScalef(1, 1, 70);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);
	glutSolidCylinder(1, 4, 30, 30);

	glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(1, 4, 30, 30);
	glPopMatrix();
	glPopMatrix();
}

void lane() {
// the car to enter the mcd house
	glPushMatrix();
	glTranslatef(p2, -10.0, -1000);
	glScalef(1.0, 1.0, 0.7);
	glRotatef(0.0, 0, 0.0, 0);
	glColor3f(0.0, 0.19, 0.0);
	car1();
	glPopMatrix();

	// the car
	glPushMatrix();
	glTranslatef(p1, -10.0, -600);
	glScalef(1.0, 1.0, 0.7);
	glRotatef(0.0, 0, 0.0, 0);
	glColor3f(0.0, 0.19, 0.0);
	car2();
	glPopMatrix();
}
vector<GLubyte*>p; // Similar to GLubyte* for program 3 but for 2 images (so a vector)
GLint imagewidth0, imagewidth1, imagewidth2, imageheight2, pixellength2, imagewidth5, imageheight5, pixellength5, imagewidth8, imageheight8, pixellength8;
GLint imageheight0, imageheight1, imagewidth3, imageheight3, pixellength3, imagewidth6, imageheight6, pixellength6, imagewidth9, imageheight9, pixellength9;
GLint pixellength0, pixellength1, imagewidth4, imageheight4, pixellength4, imagewidth7, imageheight7, pixellength7;
GLuint texture[99];
void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
	GLubyte* pixeldata;
	FILE* pfile;
	fopen_s(&pfile, path, "rb");
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);
	p.push_back(pixeldata); // Similar to glDrawPixels for program 3
	fclose(pfile);
}

void displayObject()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, 1, 0.1, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(fltX0 * fltZoom, fltY0 * fltZoom, fltZ0 * fltZoom, fltXRef, fltYRef, fltZRef, fltXUp,
		fltYUp, fltZUp);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// first, draw the back ground
	// the bg

	glPushMatrix();
	glTranslatef(0.0, -4000, 5000.0);
	glScalef(200, 120, 2000);

	//glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glScalef(0.7,0.7,0.7);

	//the floor of the ground
	glPushMatrix();
	glTranslatef(0.0, 5, -4000.0);
	glScalef(300, 30, 300);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the scene
	glPushMatrix();
	glTranslatef(-200,0,2000);

	house();
	lane();

	// texture
	// the white and yellow logo of MCD in the toppest floor
	glPushMatrix();
	glTranslatef(1510.0 ,400, 480);
	glRotatef(-30,0,1,0);
	glScalef(5,5,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the white and yellow logo of MCD on the front side (down)
	glPushMatrix();
	glTranslatef(820, 200, -50);
	glScalef(1.5, 2, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the McCafe board on the right 
	glPushMatrix();
	glTranslatef(-843, 50, -27.5);
	glScalef(3, 2.9, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the redlogo on the second floor
	glPushMatrix();
	glTranslatef(-811, 280, -186);
	glScalef(2.1, 4, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the banner in the right-hand-side of the hall
	glPushMatrix();
	glTranslatef(-500, 237, 970);
	glScalef(2.3, 1.2, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the banner in the right-hand-side of the hall
	glPushMatrix();
	glTranslatef(700, 270, 970);
	glScalef(2.35, 1.2, 1.0);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the banner in the right-hand-side of the hall
	glPushMatrix();
	glTranslatef(-500, 1012, 970);
	glScalef(2.85, 1.7, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the banner the frame on the lhs of the hall
	glPushMatrix();
	glTranslatef(970, 270, 198);
	glScalef(1, 1.2, 1.1);
	glRotatef(90, 0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(970, 270,798);
	glScalef(1, 1.2, 1.1);
	glRotatef(90, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	// the biggest board on the left and the right
	glPushMatrix();
	glTranslatef(970, 900, 600);
	glScalef(1, 1.8, 2.9);
	glRotatef(90, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// the right one
	glPushMatrix();
	glTranslatef(-978, 180, 497);
	glScalef(1, 2.9, 4.7);
	glRotatef(90, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// the texture of the side window
	// the banner in the right-hand-side of the hall
	glPushMatrix();
	glTranslatef(1020, 840, 220);
	glScalef(3.0, 2.4, 1.6);
	glRotatef(90, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1020, 840, 720);
	glScalef(3.0, 2.4, 1.6);
	glRotatef(90, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//the floor of mcd house
	glPushMatrix();
	glTranslatef(0.0, 12, 0.0);
	glScalef(20,10,10.0);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//the road
	glPushMatrix();
	glTranslatef(0.0, 15, -1300.0);
	glScalef(300, 30, 10);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(10.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//the logo on the front board
	glPushMatrix();
	glTranslatef(-565, 560.0, 1350);
	glScalef(4.7, 2.8, 1);
	//glRotatef(90, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[12]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50.0, 0.0, -0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 100.0, -0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

}

void reshapeWindow(GLint intNewWidth, GLint intNewHeight)
{
	glViewport(0, 0, intNewWidth, intNewHeight);
}



// Material properties
// Define light and material properties
void myinit(void) {
	//  the sun light  
	GLfloat sun_light_position[] = { 0.0f, 2000.0f, -1000.0f, 1.0f }; // the position of the source light
	GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // ambient light  white
	GLfloat sun_light_diffuse[] = { 1.0f, 0.74f, 0.0f, 1.0f};  //RGBA diffuse white
	GLfloat sun_light_specular[] = { 0.0f, 0.0f, 0.0f, .0f }; //RGBA specular light
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

	// Enable the light
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHT0);

	// the textures
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	ReadImage("whitelogo0.bmp", imagewidth0, imageheight0, pixellength0);
	ReadImage("McCafe.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("redlogo1.bmp", imagewidth2, imageheight2, pixellength2);
	ReadImage("biggerbanner.bmp", imagewidth3, imageheight3, pixellength3);
	ReadImage("greenlogo.bmp", imagewidth4, imageheight4, pixellength4);
	ReadImage("friesbg.bmp", imagewidth5, imageheight5, pixellength5);
	ReadImage("hamburger.bmp", imagewidth6, imageheight6, pixellength6);
	ReadImage("donasboard.bmp", imagewidth7, imageheight7, pixellength7);
	ReadImage("floor2.bmp", imagewidth8, imageheight8, pixellength8);
	ReadImage("moonlikefloor.bmp", imagewidth9, imageheight9, pixellength9);
	ReadImage("road.bmp", imagewidth9, imageheight9, pixellength9);
	ReadImage("bg1.bmp", imagewidth9, imageheight9, pixellength9);
	ReadImage("redlonglogo.bmp", imagewidth9, imageheight9, pixellength9);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
	glGenTextures(99, &texture[0]); // number of texture names to be generated and an array of texture
	glBindTexture(GL_TEXTURE_2D, texture[0]); // target to which texture is bound and name of a texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth2, imageheight2, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth3, imageheight3, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth4, imageheight4, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth5, imageheight5, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth6, imageheight6, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth7, imageheight7, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[7]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth8, imageheight8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[8]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[9]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[10]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[11]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[11]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, texture[12]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth9, imageheight9, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[12]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glDisable(GL_TEXTURE_2D);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	int cx = glutGet(GLUT_SCREEN_WIDTH);
	int cy = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((cx - intWinWidth) / 2, (cy - intWinHeight) / 2);
	glutInitWindowSize(intWinWidth, intWinHeight);
	glutCreateWindow("The McDonald daliy road trip");
	myinit();
	glutDisplayFunc(displayObject);
	glutReshapeFunc(reshapeWindow);
	glutKeyboardFunc(adjustDisplay);
	glutIdleFunc(animateTracks); 
	glutMainLoop();
}