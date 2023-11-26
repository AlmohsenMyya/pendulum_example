#include <GL/glut.h>
#include <cmath>
#include <iostream>

GLfloat threadLength = 200.0f;
GLfloat stringSpacing = 100.0f;
GLfloat stringSpacing1 = -100.0f;
GLfloat ballRadius = 30.0f;
GLfloat ballSpeed = 1.0f;
GLfloat ballAngle = 45.0f;
GLfloat ballPositions[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };


void construct() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // background color
    glColor3f(0.0f, 0.0f, 0.0f); // line and ball color
    glPointSize(1.0f); // pixel size
    gluOrtho2D(-250.0f, 250.0f, -600.0f, 0.0f); // Orthographic Projection
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the thread and balls
    for (int i = 0; i < 5; i++) {
        GLfloat stringX = i * stringSpacing - 200.0f;
        GLfloat ballX = stringX + ballPositions[i];
        GLfloat threadStartY = 0.0f;
        GLfloat threadEndY = -threadLength;

        // Draw the thread
        glBegin(GL_LINES);
        glVertex2f(stringX, threadStartY);
        glVertex2f(ballX, threadEndY);
        glEnd();

        // Draw the ball
        glPushMatrix();
        glTranslatef(ballX, threadEndY - ballRadius, 0.0f);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j++) {
            GLfloat theta = j * 3.14159 / 180;
            GLfloat x = ballRadius * cos(theta);
            GLfloat y = ballRadius * sin(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }

    glutSwapBuffers();
}

void Timer(int value) {
    glutTimerFunc(10, Timer, 0);
    glutPostRedisplay();

    static int currentBall = 0;
    static bool ball4Moving = true;
    static bool ball0Moving = true;


    // Update ball positions
    if (currentBall == 4) {
        if (ball4Moving) {
           ballPositions[0] -= ballSpeed * -cos(ballAngle * 3.14159 / 180);
            if (ballPositions[0] >= 0.0f) {
                std::cout << "The current 0  ";
                ballPositions[0] = 0.0f;
                ball4Moving = false;
                ball0Moving = true;
                currentBall = 0;
            }
        }
        else {
            ballPositions[0] += ballSpeed * -cos(ballAngle * 3.14159 / 180);
            if (ballPositions[0] <= stringSpacing1) {
                std::cout << "The current 1 ";
                ballPositions[0] = stringSpacing1;
                ball4Moving = true;
                ball0Moving = false;
                
            }
        }
    }
    else if (currentBall == 0  ) {
        if (!ball0Moving) {

            ballPositions[4] -= ballSpeed * cos(ballAngle * 3.14159 / 180);
            if (ballPositions[4] <= 0.0f) {
                std::cout << "The current 2 ";
                ballPositions[4] = 0.0f;
                ball4Moving = false;
                ball0Moving = true;
                currentBall = 4;
            }
        }
        else {
            ballPositions[4] += ballSpeed * cos(ballAngle * 3.14159 / 180);
            if (ballPositions[4] >= stringSpacing) {
                std::cout << "The current 3 ";
                ballPositions[4] = stringSpacing;
                ball4Moving = true;
                ball0Moving = false;

            }
          
         
        }
    }
}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Five-Ball Pendulum");
    glutDisplayFunc(display);
    construct();
    Timer(0);
    glutMainLoop();

    return 0;
}