#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include<stdbool.h>

GLuint texture1, texture2,texture3,texture4,texture5,texture6,texture7, texture8;

const int screenWidth = 1000;
const int screenHeight = 600;
float treePos = 0.0;
float tree2Pos = 500.0;
float rcloudPos = 0.0;
float lcloudPos = 600.0;
float xPos = 200.0;
float yPos = 70.0f;
float yVel = 2.0f;
bool jumping = false;
float jumpDuration = 0.0f;
float stonePos = 750.0;
float greedPos = 1250.0;
int score = 0;

void init() {
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   texture1 = SOIL_load_OGL_texture("staticbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture2 = SOIL_load_OGL_texture("rightclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture3 = SOIL_load_OGL_texture("leftclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture4 = SOIL_load_OGL_texture("left trees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture5 = SOIL_load_OGL_texture("right_trees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture6 = SOIL_load_OGL_texture("character2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture7 = SOIL_load_OGL_texture("stone.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture8 = SOIL_load_OGL_texture("Greedemoji.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}
void keyCallback(unsigned char key, int x, int y) {
    if (key == ' ' && !jumping) {
        jumping = true;
        jumpDuration = 0.0f;
        yVel = 1.5f;
    }
}
void drawScore() {
    char scoreText[30];
    sprintf(scoreText, "         PUNYA = %d", score);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(790.0, 560.0);
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindTexture(GL_TEXTURE_2D, texture1);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(0.0, screenHeight);
   glTexCoord2f(1.0, 1.0); glVertex2f(screenWidth, screenHeight);
   glTexCoord2f(1.0, 0.0); glVertex2f(screenWidth,0.0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texture2);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(rcloudPos, 440.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(rcloudPos, 580.0);
   glTexCoord2f(1.0, 1.0); glVertex2f(rcloudPos+400.0, 580.0);
   glTexCoord2f(1.0, 0.0); glVertex2f(rcloudPos+400.0, 440.0);
   glEnd();
   rcloudPos-=0.3;
   if(rcloudPos+400.0<=0.0){
    rcloudPos=1000.0;
   }
   
   glBindTexture(GL_TEXTURE_2D, texture3);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(lcloudPos, 440.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(lcloudPos, 580.0);
   glTexCoord2f(1.0, 1.0); glVertex2f(lcloudPos+400.0, 580.0);
   glTexCoord2f(1.0, 0.0); glVertex2f(lcloudPos+400.0, 440.0);
   glEnd();
   lcloudPos-=0.3;
   if(lcloudPos+400.0<=0.0){
    lcloudPos=1000.0;
   }

   glBindTexture(GL_TEXTURE_2D, texture4);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(treePos, 213.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(treePos, 478.0);
   glTexCoord2f(1.0, 1.0); glVertex2f(treePos+200.0, 478.0);
   glTexCoord2f(1.0, 0.0); glVertex2f(treePos+200.0, 213.0);
   glEnd();
   treePos-=1.0;
   if(treePos+200.0<=0.0){
    treePos=1000.0;
   }

   glBindTexture(GL_TEXTURE_2D, texture5);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(tree2Pos, 213.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(tree2Pos, 478.0);
   glTexCoord2f(1.0, 1.0); glVertex2f(tree2Pos+300.0, 478.0);
   glTexCoord2f(1.0, 0.0); glVertex2f(tree2Pos+300.0, 213.0);
   glEnd();
   tree2Pos-=1.0;
   if(tree2Pos+300.0<=0.0){
    tree2Pos=1000.0;
   }
    
   glBindTexture(GL_TEXTURE_2D, texture6);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex2f(xPos, yPos);
   glTexCoord2f(1.0f, 0.0f); glVertex2f(xPos+140.0,yPos);
   glTexCoord2f(1.0f, 1.0f); glVertex2f(xPos+140.0, yPos+165.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex2f(xPos, yPos+165.0f);
   glEnd();
   if (jumping) {
        yPos += yVel;
        yVel -= 0.01f;
        jumpDuration += 0.01f;
        if (jumpDuration >= 3.0f) {
            jumping = false;
            yPos = 70.0f;
            yVel = 0.2f;
            jumpDuration = 0.0f;
        }
    }
    
   glBindTexture(GL_TEXTURE_2D, texture7);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(stonePos, 65.0f);
   glTexCoord2f(0.0, 1.0); glVertex2f(stonePos, 100.0f);
   glTexCoord2f(1.0, 1.0); glVertex2f(stonePos+55.0f, 100.0f);
   glTexCoord2f(1.0, 0.0); glVertex2f(stonePos+55.0f, 65.0f);
   glEnd();
   stonePos-=1.0;
   if(stonePos<-10){
    stonePos=1200.0;
   }
   if((yPos<=(100.0))&&(stonePos<=(xPos+140.0))&&(stonePos>=(xPos-55.0))){
    score--;
    stonePos=1050.0;
   }

   glBindTexture(GL_TEXTURE_2D, texture8);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(greedPos, 270.0f);
   glTexCoord2f(0.0, 1.0); glVertex2f(greedPos, 310.0f);
   glTexCoord2f(1.0, 1.0); glVertex2f(greedPos+45.0f, 310.0f);
   glTexCoord2f(1.0, 0.0); glVertex2f(greedPos+45.0f, 270.0f);
   glEnd();
   greedPos-=1.0;
   if(greedPos<-10){
    greedPos=850.0;
   }
   if((yPos+165.0>=270.0)&&(greedPos<=xPos+140.0)&&(greedPos>=xPos-45.0)){
    score++;
    greedPos=1350.0;
   }

   drawScore();
   glFlush();
}

int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
   glutInitWindowSize(screenWidth, screenHeight);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("BHULOKA");
   glutKeyboardFunc(keyCallback);
   init();
   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutMainLoop();
   return 0;
}