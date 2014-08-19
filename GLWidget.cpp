#include "GLWidget.h"
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <cmath>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    timer = new QTimer(this);
    color = 0;
    circRad = 0;

}

void
GLWidget::initializeGL()
{
    // black background
    glClearColor(0,0,0,0);

}

void
GLWidget::limitCircle()
{
        if(circRad >= 1)
        {
                circRad = 0.01;
                // circRadd = 0.01;
                color = (color +1)%6;
        }
}

void
GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(color == 0)      glColor3f(0,0,1);   // blue
    else if(color == 1) glColor3f(1,0,0);   // red
    else if(color == 5) glColor3f(0,1,0);   // green
    else if(color == 3) glColor3f(1,1,0);   // yellow
    else if(color == 4) glColor3f(0,1,1);   // birght blue
    else if(color == 2) glColor3f(0.5,1.0,0.5); // light green


    glPointSize(2.0);
    glBegin(GL_POINTS);
// 8 sine functions
//
    for( double i = -1; i <= 1 ; i+= 0.01)
    {
        double y = sin(8*i);
        glVertex2f((i+=circRad),y);
        y = sin(8*i);
        glVertex2f(0.06+(i+=circRad),y);

        y = sin(8*i);
        glVertex2f(0.12+(i+=circRad),y);

        y = sin(8*i);
        glVertex2f(0.18+(i+=(circRad)),y);

    }
    glEnd();




//Sine Functions Moving to the Left

    glBegin(GL_POINTS);
    for( double i = 1; i >= -1 ; i-= 0.01)
    {
        double y = sin(8*i);
        glVertex2f(-0.06+(i-=circRad),y);

        y = sin(8*i);
        glVertex2f(-0.12+(i-=circRad),y);

        y = sin(8*i);
        glVertex2f(-0.18+(i-=circRad),y);

        y = sin(8*i);
        glVertex2f(-0.24+(i-=(circRad)),y);
    }
    glEnd();


    // rate of change
    if(circRad < 0.1039)       circRad += 0.0001; // Every 30ms, the circRad increases
    //if(circRad < 0.1039)       circRad += 0.0001;

    else   circRad += 0.01;
    limitCircle();
}
void
GLWidget::resizeGL(int width, int height)
{

        glViewport(0,0,width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}


void GLWidget::startTime()
{

    if(timer->isActive())
        return;
    timer->start(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));

}

void GLWidget::endTime()
{

    if(timer->isActive())
        timer->stop();
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
}
void GLWidget::repaint()
{
        paintGL();
        update();
}
