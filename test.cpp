#include<GL/glut.h>
#include<GL/freeglut.h>
#include<sstream>
#include<string>
#include<iostream>
#include<stdio.h>

void GLInit();
void My_Reshape(int w, int h);
void My_Display();
void Draw_head();
void Draw_body();
void Draw_L_hand();
void Draw_R_hand();
void Draw_leg();
void My_Key_Press(unsigned char key, int x, int y);
void timer(int value);
void scissor();
void papper();
void stone();
void hold();
void style();

static int r = 0;
static int status = 0;
static float right_hand_art[] = {0, 0, 0, 1, 1};
static float left_hand_art[] = {0, 0, 0, 1, 1};
static float left_palm[6][3];	//finger : art
static float right_palm[6][3];
static float right_leg[2][3];
static float left_leg[2][3];

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Test");

	glutKeyboardFunc(My_Key_Press);
	glutReshapeFunc(My_Reshape);	
	glutDisplayFunc(My_Display);	
	glutTimerFunc(10, timer, 1);

	GLInit();
	
	glutMainLoop();

	return 0;
}

void GLInit()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	//add ambient light
	GLfloat ambientColor[] = {20.0f, 20.0f, 20.0f, 0.0f};		
	glLightfv(GL_LIGHT0, GL_POSITION, ambientColor);//GL_AMBIENT
}


void My_Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat) h, 0.1, 150.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(100, 0, 0, 0, 0, 0, 0, 1, 0);
	
	glRotatef(-90.0f, 1, 0, 0);	

	glRotatef(r, 0, 0, 1);	
	
	glPushMatrix();
	glTranslatef(0, 0, 10);
	
	Draw_head();
	
	glPushMatrix();
	glTranslatef(0, 0, 5);
	Draw_body();
	Draw_L_hand();
	Draw_R_hand();
	glPopMatrix();
	
	Draw_leg();
	
	glPopMatrix();
	
	glutSwapBuffers();

	glutPostRedisplay();	
}


void Draw_head()
{
	glPushMatrix();
	glScalef(1, 1.4, 2);
	glTranslatef(0, 0, 15);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(4.0, 30.0, 30.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -1.0);	
	//eye
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3.3, -2.5, 32.0);
	glScalef(1, 1.5, 1);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3.3, 2.5, 32.0);
	glScalef(1, 1.5, 1);
	glutSolidCube(2.0);	
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(3.3, 0.0, 32.0);
	glScalef(1, 1, 0.1);
	glutSolidCube(2.0);
	glPopMatrix();
	
	glPopMatrix();
	//mouse
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(3.3, 0, 25);
	glScalef(1, 1, 0.2);
	glutSolidCube(2.0);
	glPopMatrix();
	
	//ear
	glPushMatrix();
	glColor3f(192.0/255.0, 192.0/255.0, 192.0/255.0);
	glTranslatef(0, 5.5, 32);
	glRotatef(90.0, 1, 0, 0);
	glutSolidCylinder(2.0, 11.0, 30.0, 30.0);
	glPopMatrix();	

	//hair mid
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 0, 37);
	glScalef(1, 0.2, 1);
	glutSolidSphere(5.0, 30.0, 30.0);
	glPopMatrix();
	//hair left
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 0, 37);
	glRotatef(45, 1, 0, 0);
	glScalef(1, 0.2, 1);
	glutSolidSphere(5.0, 30.0, 30.0);
	glPopMatrix();
	//hair right
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 0, 37);
	glRotatef(-45, 1, 0, 0);
	glScalef(1, 0.2, 1);
	glutSolidSphere(5.0, 30.0, 30.0);
	glPopMatrix();
}

void Draw_body()
{
	glPushMatrix();
		glColor3f(1.0, 1.0, 0);
		glTranslatef(0, 0, 15);
		glScalef(2, 3, 3);
		glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(1, 1.8, 2.3);
	glutSolidCube(10.0);
	glPopMatrix();	

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(2.0, 0, 5.0);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(.0, 5.0, 30.0, 30.0);
	glPopMatrix();
	
	//left shoulder
	glPushMatrix();
		glTranslatef(0, -15, 15);
		glColor3f(1, 1, 0);
		glRotatef(-30, 1, 0, 0);
		glScalef(0.5, 2, 0.5);
		glutSolidSphere(5.0, 30.0, 30.0);
	glPopMatrix();

	//right shoulder
	glPushMatrix();
		glTranslatef(0, 15, 15);
		glColor3f(1, 1, 0);
		glRotatef(30, 1, 0, 0);
		glScalef(0.5, 2, 0.5);
		glutSolidSphere(5.0, 30.0, 30.0);
	glPopMatrix();
	
}

void Draw_R_hand()
{	
	glPushMatrix();
		
		glTranslatef(0, -18, 12);
		
		glRotatef(right_hand_art[0], 0, 1, 0);
		
		//shoulder articulation
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(2.0, 30.0, 30.0);
		
		glTranslatef(0, 0, -8);	//
		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glScalef(4, 4, 12);
			glutSolidCube(1.0);
		glPopMatrix();
		
		glTranslatef(0, 0, -8);
		
		glRotatef(right_hand_art[1], 0, 1, 0);
	
		//hand articulation 	
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(2.0, 30.0, 30.0);	
 	
		glTranslatef(0, 0, -8);       
		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glScalef(4, 4, 13);
			glutSolidCube(1.0);
		glPopMatrix();
		
		//palm
		glPushMatrix();
			glTranslatef(0, 0, -9.5);
			glColor3f(1.0, 0.0, 0.0);
				
			glRotatef(right_palm[5][0], 0, 0, 1);	
			glPushMatrix();
			glScalef(0.5, 1, 1);
			glutSolidSphere(3.0, 30.0, 30.0);
			glPopMatrix();
			glTranslatef(0, -3, -5);
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, -3.2, 3.3);
				glRotatef(-30, 1, 0, 0);
				glScalef(1.1, 1.1, 1.1);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[0][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[0][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, -1.3, 1.5);
				glRotatef(-15, 1, 0, 0);
				glScalef(0.9, 1, 0.9);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[1][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[1][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[1][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 0, 0.3);
				glScalef(1, 1, 1);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[2][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[2][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[2][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 1.7, 0.2);
				glRotatef(15, 1, 0, 0);
				glScalef(0.8, 1, 0.8);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[3][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[3][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[3][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 3.5, 0.5);
				glRotatef(30, 1, 0, 0);
				glScalef(0.7, 0.9, 0.7);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[4][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[4][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(right_palm[4][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////

		glPopMatrix();
	glPopMatrix();
}

void Draw_L_hand()
{
	glPushMatrix();
		
		glTranslatef(0, 18, 12);
		glRotatef(180, 0, 0, 1);
		
		glRotatef(-left_hand_art[0], 0, 1, 0);
		
		//shoulder articulation
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(2.0, 30.0, 30.0);
		
		glTranslatef(0, 0, -8);	//
		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glScalef(4, 4, 12);
			glutSolidCube(1.0);
		glPopMatrix();
		
		glTranslatef(0, 0, -8);
		
		glRotatef(-left_hand_art[1], 0, 1, 0);
	
		//hand articulation 	
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(2.0, 30.0, 30.0);	
 	
		glTranslatef(0, 0, -8);       
		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glScalef(4, 4, 13);
			glutSolidCube(1.0);
		glPopMatrix();
		
		//palm
		glPushMatrix();
			glTranslatef(0, -3, -14.5);
			glColor3f(1.0, 0.0, 0.0);
		
			glPushMatrix();
			glTranslatef(0, 3, 5);
			glScalef(0.5, 1, 1);
			glutSolidSphere(3.0, 30.0, 30.0);
			glPopMatrix();

			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, -3.2, 3.3);
				glRotatef(-30, 1, 0, 0);
				glScalef(1.1, 1.1, 1.1);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[0][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[0][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, -1.3, 1.5);
				glRotatef(-15, 1, 0, 0);
				glScalef(0.9, 1, 0.9);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[1][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[1][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[1][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 0, 0.3);
				glScalef(1, 1, 1);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[2][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[2][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[2][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 1.7, 0.2);
				glRotatef(15, 1, 0, 0);
				glScalef(0.8, 1, 0.8);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[3][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[3][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[3][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
			glPushMatrix();
				glTranslatef(0, 3.5, 0.5);
				glRotatef(30, 1, 0, 0);
				glScalef(0.7, 0.9, 0.7);
				glPushMatrix();
					glTranslatef(0, 3, 1.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[4][0], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art
							
					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();

					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[4][1], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
							
					glTranslatef(0, 0, -2.5);
					glColor3f(1, 1, 0);
					glRotatef(left_palm[4][2], 0, 1, 0);
					glutSolidSphere(0.4, 30.0, 30.0);	//art

					glPushMatrix();
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -1.2);
					glScalef(0.6, 0.6, 1.1);
					glutSolidSphere(1, 30.0, 30.0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//////////////////////////////////////////////////////
		glPopMatrix();
	glPopMatrix();
}

void Draw_leg()
{
	//Pelvisi
	glPushMatrix();
		glColor3f(1.0, 1.0, 0);
		glTranslatef(0, 0, -5.5);
		glScalef(3.5, 3.5, 4);
		glutSolidDodecahedron();
	glPopMatrix();
	
	for(int i = 0;i <= 1;i++)
	{
		glPushMatrix();
		
			if(i == 1)
				glTranslatef(0, 12, 0);
				
			glTranslatef(0, -6, -10);
				
			if(i == 0)
			{
				glRotatef(right_leg[0][0], 1, 0, 0);
				glRotatef(right_leg[0][1], 0, 1, 0);
				glRotatef(right_leg[0][2], 0, 0, 1);
			}
			else
			{
				glRotatef(left_leg[0][0], 1, 0, 0);
				glRotatef(left_leg[0][1], 0, 1, 0);
				glRotatef(left_leg[0][2], 0, 0, 1);
			}

			glPushMatrix();
				glColor3f(1.0, 0, 0);
				glutSolidSphere(3.0, 30.0, 30.0);
			glPopMatrix();
			
			glTranslatef(0, 6, 10);
			glPushMatrix();
				glColor3f(1.0, 1.0, 0);
				glTranslatef(0, -6, -21.3);
				glScalef(1, 1, 3.3);
				glutSolidCube(5.0);
			glPopMatrix();
	
			glTranslatef(0, -6, -32.5);
			
			if(i == 0)
			{
				glRotatef(right_leg[1][0], 1, 0, 0);
				glRotatef(right_leg[1][1], 0, 1, 0);
				glRotatef(right_leg[1][2], 0, 0, 1);
			}
			else
			{
				glRotatef(left_leg[1][0], 1, 0, 0);
				glRotatef(left_leg[1][1], 0, 1, 0);
				glRotatef(left_leg[1][2], 0, 0, 1);
			}
			
			glPushMatrix();
				glColor3f(1.0, 0, 0);
				glutSolidSphere(2.5, 30.0, 30.0);
			glPopMatrix();
		
			glTranslatef(0, 6, 32.5);
			glPushMatrix();
				glColor3f(1.0, 0, 0);
				glTranslatef(0, -6, -44);
				glScalef(1, 1, 3.7);
				glutSolidCube(5.0);
			glPopMatrix();
				
			glPushMatrix();
				glTranslatef(1.5, -6, -56);
				glScalef(3, 1, 1);
				glutSolidCube(5.0);
			glPopMatrix();	
	
			glPushMatrix();
				glColor3f(1.0, 1.0, 0.0);
				glTranslatef(4, -6, -52);
				glRotatef(-45, 0, 1, 0);
				glScalef(0.3, 0.8, 2);
				glutSolidCube(4.0);
			glPopMatrix();
		
		glPopMatrix();		
	}
}

void My_Key_Press(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
		case 'a':
			r += 5;
			break;
		case 'd':
			r -= 5;
			break;
		case 't':
			status = 1;
			break;
		case '1':
			status = 1;
			break;
		case '2':
			status = 2;
			break;
		case '3':
			status = 3;
			break;
		case '4':
			status = 4;
			break;
		case '5':
			status = 5;
			break;
		case '0':
			status = 0;
			break; 
	}
}

void timer(int value)
{
	switch(status)
	{
		case 1:
			hold();
			break;
		case 2:
			papper();
			break;
		case 3:
			scissor();
			break;
		case 4:
			stone();
			break;
		case 5:
			style();
			break;
	}
	glutTimerFunc(10, timer, 1);
}

void scissor()
{
	//right_hand_art[0] = 0; 
	//right_hand_art[1] = 0;
	//right_palm[1] = 0 
	//right_palm[2] = 0
	//other palm angle = 90
	if(right_hand_art[0] < -20)
	{
		right_hand_art[0] += 2;
		right_hand_art[1] += 2 * 1.5;
	}

	if(right_palm[1][0] < 0)
	{
		for(int i = 0;i < 5;i++)
		{
			if(i == 1 || i == 2)
				for(int j = 0;j < 3;j++)
					right_palm[i][j] += 3;
		}
	}
}
	
void papper()
{
	//right_hand_art[0] = 0; 
	//right_hand_art[1] = 0;
	//palm angle = 0
	if(right_hand_art[0] < -20)
	{
		right_hand_art[0] += 2;
		right_hand_art[1] += 2 * 1.5;
	}
	
	
	for(int i = 0;i < 5;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			if(right_palm[i][j] < 0)
				right_palm[i][j] += 3;	
		}
	}
	
}

void stone()
{
	//right_hand_art[0] = 0; 
	//right_hand_art[1] = 0;
	//palm angle = 90
	if(right_hand_art[0] < -20)
	{
		right_hand_art[0] += 2;
		right_hand_art[1] += 2 * 1.5;
	}
	
	if(right_palm[0][0] > -90)
	{
		for(int i = 0;i < 5;i++)
		{
			for(int j = 0;j < 3;j++)
			{
				right_palm[i][j] += (-3);
			}
		}
	}
}

void hold()
{
	//right_hand_art[0] = -80
	//right_hand_art[1] = -120
	//palm angle = 90
	if(right_hand_art[0] > -80)
	{
		right_hand_art[0] += (-2);
		right_hand_art[1] += (-2) * 1.5;
	}

	if(right_palm[5][0] < 90)
		right_palm[5][0] += 3;

	for(int i = 0;i < 5;i++)
	{	
		for(int j = 0;j < 3;j++)
		{
			if(right_palm[i][j] > -90.0)
				right_palm[i][j] += (-3);
		}
	}

	
}

void style()
{
	right_leg[0][0] = -20;	
	left_leg[0][0] = 20;	
}
