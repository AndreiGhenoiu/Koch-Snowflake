#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//Program by Andrei Ghenoiu
//Fall 2011 - Vermont Technical College - Computer Graphics
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#define PI 3.14

int depth = 0;

void fc(){
    if(depth<5){
      depth++;
      Sleep(1000);
      glutPostRedisplay();
    }
}

void findMid2(float startX, float startY, float endX, float endY, float *midX, float *midY, float normal){
    float side1 = pow(startX - endX, 2);
    float side2 = pow(startY - endY,2);
    float segment = sqrt(side1+side2);
   printf("segment length is %f", segment);
   float newPointX = endX+segment*cos(normal*PI/180);
   float newPointY = endY+segment*sin(normal*PI/180);
   *midX = newPointX;
    *midY = newPointY;
}

int drawLine(float startX, float startY, float endX, float endY, int depth, float normal){
    if(depth == 0){
        glBegin(GL_LINE_STRIP);
        glVertex2f(startX, startY);
        glVertex2f(endX, endY);
        glEnd();
        return 0;
    }
        else{
   float verticSegm = (endY-startY)/3;
//    printf("vertical segment %f", verticSegm);
    float horizSegm = (endX-startX)/3;
    float startX1 = startX;
    float startY1 = startY;
    float startX2 = horizSegm+startX;
    float startY2 = verticSegm + startY;
    float startX3 = 2*horizSegm + startX;
    float startY3 = 2*verticSegm + startY;
    float midX;
    float midY;

    findMid2(startX2, startY2, startX3, startY3, &midX, &midY, normal);

    drawLine(startX,startY, startX2, startY2, depth-1, normal);
     drawLine(startX2, startY2, midX, midY, depth-1, normal+60);
     drawLine(midX, midY, startX3, startY3, depth-1, normal-60);
     drawLine(startX3, startY3, endX, endY, depth-1, normal);
     //Sleep(1000);
     //
    }
}

void drawTriangle(float x, float y, int length){

    float height = sqrt(pow(2,length)- pow(2,length/2));
    float x2 = sqrt(pow(2,length) - pow(2, height));
    float y2 = -(height - y);
    float y3 = y2;
    float x3 = -x2;
    drawLine(x,y,x2,y2, depth, 60);
    drawLine(x2,y2,x3,y3,depth, -60);
    drawLine(x3,y3,x,y,depth,180);

}

void display()
{

 glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0, 0 , 0);
   drawTriangle(0.0,2.0,4);
    //glFlush();
     glutSwapBuffers();
}
void init()
{
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-3.0,3.0,-3.0,3.0);
}

int main(int argc,char ** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500,500);
  glutCreateWindow("simple");
  glutIdleFunc(fc);
  glutDisplayFunc(display);
  init();

  glutMainLoop();
  return 0;

}

