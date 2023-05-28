#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdbool.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <AL/alext.h>
#include <sndfile.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//Declaring all textures and functions related to texture
//Textures for menu
GLuint introBg, initialBg, scoreBoard; 
//Textures for Bhuloka
GLuint earthBg, rightClouds, leftClouds, leftTrees, rightTrees, character, honesty, meditation, anger, lust, greed;
//Textures for Swargloka
GLuint spalace, hanging;
//Textures for Pattalloka
GLuint Pstaticbg, Pmovingbg, Pmirrormovingbg, Pcharacter, nviolence;  


//Declaring all constants
float screenWidth = 1000.0, screenHeight = 600.0;

//Declaring variables of character
float Pxpos, Pypos;
float Bxpos = 200.0, Bypos = 70.0;
float Sxpos = 250.0 , Sypos = 60.0;

//Declaring variables of positive obstacles
float Ppxpos1, Ppxpos2, Ppypos1, Ppypos2;
float Bpxpos1 = 1100.0, Bpxpos2 = 1600.0 , Bpypos1 = 260.0, Bpypos2 = 260.0;
float Spxpos1, Spxpos2, Spypos1, Spypos2;

//Declaring variables of negative obstacles
float Pnxpos1, Pnxpos2, Pnypos1, Pnypos2;
float Bnxpos1 = 1400.0, Bnxpos2 = 1800.0, Bnypos1 = 70.0, Bnypos2 = 70.0;
float Snxpos1 = 1100.0 , Snxpos2 = 1600.0 , Snypos1 = 60.0 , Snypos2 =60.0;

//Declaring variables of elements in different lokas
/*For bhulok position*/
float Brcloudpos = 0.0f, Blcloudpos = 600.0f, Blefttreepos = 0.0, Brighttreepos = 500.0;
/*For bhulok Velocity*/
float Bvel = 1.0f , Byvel = 2.0f;
float Bjumpduration = 0.0f;
/*For svarglok position*/
float Sbgxpos1 = -5.0f, Sbgxpos2 = 995.0f;
float degree1 = 0.0, degree2 = 0.0, radian1 = 0.0, radian2 = 0.0; 
float xHinge1 =750.0, xHinge2 =1250.0;
float xOscillate1, yOscillate1;
float xOscillate2, yOscillate2;
int changeDir1 = 0, changeDir2 = 0;
/*Pattal loka position*/
float PmovingPos=0.0,PmirrormovingPos=1000.0;
int Pk=0;
/*Pattal loka velocity*/
float Pvel = 1.0, Pyvel=2.0;
float Pobvel=1.0;
float Pjumpduration = 0.0f;

/*For svarglok velocity*/
float Svel = 1.0f , Syvel = 2.0f;
float Sjumpduration = 0.0f;


//Declaring all boolean expression
bool jumping = false;


//Declaring variables for sound
ALuint backgroundSource, source;

//Declaring variables for score
int score = 0;


//Declaring all functions used
/*Texture functions*/
void drawtexture(GLuint texture,float x,float y,float height,float width);
void drawSwargTexture(GLuint texture, float x, float y, float height, float width);

/*Music functions*/
void playBackgroundMusic(const char* filename);
void playSound(const char* filename);

/*Score functions*/
void drawScore();
void finalscoretext();

/*Level functions*/
void rdltext(int level);
void playBhulok();
void playPatallok();
void playSwarglok();

/*Input functions*/
void keyCallback(unsigned char key, int x, int y);
void mouseClick();


/*Other important functions*/
void init();
void display();

/*Main function*/
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("ODYSSEY OF LIFE");
    alutInit(&argc, argv);
    alGetError();
    glewInit();
    glutKeyboardFunc(keyCallback);
    init();
    glutIdleFunc(display);
    glutMainLoop();
    alDeleteSources(1, &backgroundSource);
    alDeleteSources(1, &source);
    
    alutExit();

   return 0;
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   //playBhulok();
   //playSwarglok();
   playPatallok();
   glFlush();
}

void playBhulok(){
    drawtexture(earthBg,0.0,0.0,screenHeight,screenWidth);
   drawtexture(rightClouds,Brcloudpos,440.0,140.0,400.0);
   Brcloudpos-=Bvel;
   if(Brcloudpos+400.0<=0.0){
    Brcloudpos=1000.0;
   }
   
   drawtexture(leftClouds,Blcloudpos,440.0,140.0,400.0);
   Blcloudpos-=Bvel;
   if(Blcloudpos+400.0<=0.0){
    Blcloudpos=1000.0;
   }

   drawtexture(leftTrees,Blefttreepos,213.0,265.0,200.0);
   Blefttreepos-=Bvel;
   if(Blefttreepos+200.0<=0.0){
    Blefttreepos=1000.0;
   }

  drawtexture(rightTrees,Brighttreepos,213.0,265.0,300.0);
   Brighttreepos-=Bvel;
   if(Brighttreepos+300.0<=0.0){
    Brighttreepos=1000.0;
   }
    
   drawtexture(character,Bxpos,Bypos,165.0,140.0);
   if (jumping) {
        Bypos += Byvel;
        Byvel -= 0.01f;
        Bjumpduration += 0.01f;
        if (Bjumpduration >= 3.0f) {
            jumping = false;
            Bypos = 70.0f;
            Byvel = 0.2f;
            Bjumpduration = 0.0f;
        }
    }

    drawtexture(meditation,Bpxpos1,Bpypos1,35.0,55.0);
    Bpxpos1-=Bvel;
    if(Bpxpos1<-60){
    Bpxpos1=1100.0;
    }
    if((Bypos+165.0>=270.0)&&(Bpxpos1<=Bxpos+140.0)&&(Bpxpos2>=Bxpos-45.0)){
    score+=100.0;
    Bpxpos1=1300.0;
    }

    drawtexture(honesty,Bpxpos2,Bpypos2,35.0,55.0);
    Bpxpos2-=Bvel;
    if(Bpxpos2<-60){
    Bnxpos2=1600.0;
    }
    if((Bypos+165.0>=270.0)&&(Bpxpos2<=Bxpos+140.0)&&(Bpxpos2>=Bxpos-45.0)){
    score+=100.0;
    Bpxpos2=1300.0;
    }

    
    drawtexture(anger,Bnxpos1,Bnypos1,35.0,55.0);
    Bnxpos1-=Bvel;
    if(Bnxpos1<-60){
    Bnxpos1=1200.0;
    }
    if((Bypos<=(100.0))&&(Bnxpos1<=(Bxpos+140.0))&&(Bnxpos1>=(Bxpos-55.0))){
    score-=100.0;
    Bnxpos1=1400.0;
    }

    drawtexture(lust,Bnxpos2,Bnypos2,35.0,55.0);
    Bnxpos2-=Bvel;
    if(Bnxpos2<-60){
    Bnxpos2=1400.0;
    }
    if((Bypos<=(100.0))&&(Bnxpos2<=(Bxpos+140.0))&&(Bnxpos2>=(Bxpos-55.0))){
    score-=100.0;
    Bnxpos2=1800.0;
    }
    drawtexture(scoreBoard,690.0,510.0,88.0,309.0);
    drawScore();
    // drawTime();
    }
void playSwarglok(){
    drawSwargTexture(spalace, Sbgxpos1, 0.0, screenHeight, screenWidth +5.0);
    Sbgxpos1 -= Svel;
    if(Sbgxpos1 + screenWidth <= 0.0) {
        Sbgxpos1 = 1000.0;
    }
    drawSwargTexture(spalace, Sbgxpos2, 0.0, screenHeight, screenWidth+5.0);
    Sbgxpos2 -= Svel;
    if(Sbgxpos2 + screenWidth <= 0.0) {
        Sbgxpos2 = 1000.0;
    }

    drawtexture(character, Sxpos, Sypos, 165.0, 140.0);

    xOscillate1 = xHinge1-(200 * sin(radian1));
    yOscillate1 = 450-(200 * cos(radian1));
    glBindTexture(GL_TEXTURE_2D, hanging);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(xOscillate1-(150 * cos(radian1)), yOscillate1+150*sin(radian1));
    glTexCoord2f(1.0f, 0.0f); glVertex2f(xOscillate1+(150 * cos(radian1)), yOscillate1-150*sin(radian1));
    glTexCoord2f(1.0f, 1.0f); glVertex2f(xHinge1+(150 * cos(radian1)),     450-150*sin(radian1));
    glTexCoord2f(0.0f, 1.0f); glVertex2f(xHinge1-(150 * cos(radian1)),     450+150*sin(radian1));
    glEnd();
    if((degree1 >= 60.0) || (degree1 <= -60.0)) {
        changeDir1++;
    }
    if(changeDir1 % 2 == 0) {
        degree1 += 0.2;
        radian1= (degree1 * 3.14)/180.0;
    }
    else {
        degree1 -= 0.2;
        radian1= (degree1 * 3.14)/180.0;
    }
    xHinge1 -= 0.5;
    if(xHinge1 +  50.0 <= 0.0) {
        xHinge1 = 1100.0;
    }
    if(((Sypos + 165.0) >= yOscillate1) && (xOscillate1 <= (Sxpos + 140.0)) && (xOscillate1 >= (Sxpos - 45.0))) {
        score+=50.0;
        xHinge1 = 1200;
    }

    xOscillate2 = xHinge2-(200 * sin(radian2));
    yOscillate2 = 450-(200 * cos(radian2));
    glBindTexture(GL_TEXTURE_2D, hanging);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(xOscillate2-(150 * cos(radian2)), yOscillate2+(150 * sin(radian2)));
    glTexCoord2f(1.0f, 0.0f); glVertex2f(xOscillate2+(150 * cos(radian2)), yOscillate2-(150 * sin(radian2)));
    glTexCoord2f(1.0f, 1.0f); glVertex2f(xHinge2+(150 * cos(radian2)),     450-(150 * sin(radian2)));
    glTexCoord2f(0.0f, 1.0f); glVertex2f(xHinge2-(150 * cos(radian2)),     450+(150 * sin(radian2)));
    glEnd();
    if((degree2 >= 60.0) || (degree2 <= -60.0)) {
        changeDir2++;
    } 
    if(changeDir2 % 2 == 0) {
        degree2 += 0.2;
        radian2 = (degree2 * 3.14)/180.0;
    }
    else {
        degree2 -= 0.2;
        radian2 = (degree1 * 3.14)/180.0;
    }
    xHinge2 -= 0.5;
    if(xHinge2 + 50.0 <= 0.0) {
        xHinge2 = 1400.0;
    }
    if(((Sypos + 165.0) >= yOscillate2) && (xOscillate2 <= (Sxpos + 140.0)) && (xOscillate2 >= (Sxpos - 45.0))) {
        score += 50.0;
        xHinge2 = 1450;
    }

    drawtexture(lust, Snxpos1, 60.0, 40.0, 45.0);
    Snxpos1 -= 1.0;
    if((Snxpos1 + 45.0) <= 0.0) {
        Snxpos1 = 1000.0;
    }
    if((Sypos <= 100.0) && ((Sxpos + 140.0) >= Snxpos1) && (Sxpos <= (Snxpos1 + 45.0))) {
        score -= 25;
        Snxpos1 = 50.0;
    }

    drawtexture(anger, Snxpos2, 60.0, 40.0, 45.0);
    Snxpos2 -= 1.2;
    if((Snxpos2 + 45.0) <= 0.0) {
        Snxpos2=1500.0;
    }
    if((Sypos <= 100.0) && ((Sxpos + 140.0) >= Snxpos2) && (Sxpos <= (Snxpos2 + 45.0))) {
        score-=25;
        Snxpos2=1450.0;
    }
    if((Snxpos2 + 45.0) < Snxpos1) {
        Snxpos1 -= 0.8;
        if(Snxpos1 <= 0.0) {
            Snxpos1 -= 1.0;
        }
    }

    if (jumping) {
        Sypos += Syvel;
        Syvel -= 0.01f;
        Sjumpduration += 0.01f;
        if (Sjumpduration >= 3.0f) {
            jumping = false;
            Sypos = 70.0f;
            Syvel = 1.0f;
            Sjumpduration = 0.0f;
        }
    }
    drawtexture(scoreBoard, 690.0, 510.0, 88.0, 309.0);
    drawScore();
    //drawTime(); 

}
void playPatallok(){
   drawtexture(Pstaticbg,0.0,0.0,screenHeight,screenWidth);

   drawtexture(Pmovingbg,PmovingPos,0.0,screenHeight,screenWidth);
   PmovingPos -= Pvel;
   if(PmovingPos+screenWidth<=0.0){
    PmovingPos = 1000.0;
   }

   drawtexture(Pmirrormovingbg,PmirrormovingPos,0.0,screenHeight,screenWidth);
   PmirrormovingPos -= Pvel;
   if(PmirrormovingPos+screenWidth<=0.0){
    PmirrormovingPos = 1000.0;
   }
   
   drawtexture(Pcharacter,Pxpos,Pypos,165.0,140.0);
   if (jumping) {
        Pypos += Pyvel;
        Pyvel -= 0.01f;
        Pjumpduration += 0.01f;
        if (Pjumpduration>= 3.0f) {
            jumping = false;
            Pypos = 70.0f;
            Pyvel = 0.2f;
            Pjumpduration = 0.0f;
        }
    }

   drawtexture(lust,Pnxpos1,Pnypos1,40.0,45.0); 
   Pnxpos1-=Pobvel;
   if(Pnxpos1+45.0<=0.0){
    Pnxpos1=1200.0;
   }
   if(Pypos<=100.0 && Pxpos + 140.0>=Pnxpos1 && Pxpos<=Pnxpos1 +45.0){
    score-=25;
    Pnxpos1=1450.0;
   }

   drawtexture(greed,Pnxpos2,Pnypos2,40.0,45.0); 
   Pnxpos2-=Pobvel;
   if(Pnxpos2+45.0<=0.0){
    Pnxpos2=1200.0;
   }
   if(Pnypos2>100.0 || Pnypos2<0.0){
    Pk++;
   }
   if(Pk%2==0){
    Pnypos2+=0.5;
   }
   if(Pk%2==1){
    Pnypos2-=0.5;
   }
   if(Pypos<=Pnypos2+40.0 && Pxpos + 140.0>=Pnxpos2 && Pxpos<=Pnxpos2 +45.0){
    score-=25;
    Pnxpos2=1450.0;
   }
   
   drawtexture(meditation ,Ppxpos1,Ppypos1,40.0,45.0);
   Ppxpos1-=Pobvel;
   if(Ppxpos1+45.0<=0.0){
    Ppxpos1=1100;
   }
   if((Pypos+165.0>=260.0)&&(Ppxpos1<=Pxpos+140.0)&&(Ppxpos1>=Pxpos-45.0)){
    score+=50;
    Ppxpos1=1300.0;
   }
   
   drawtexture(nviolence,Ppxpos2,Ppypos2,40.0,45.0);
   Ppxpos2-=Pobvel;
   if(Ppxpos2+45.0<=0.0){
    Ppxpos2=1100;
   }
   if((Pypos+165.0>=260.0)&&(Ppxpos2<=Pxpos+140.0)&&(Ppxpos2>=Pxpos-45.0)){
    score+=50;
    Ppxpos2=1300.0;
   }
 
}
void drawtexture(GLuint texture,float x,float y,float height,float width){
    glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(x,y);
        glTexCoord2f(0.0, 1.0); glVertex2f(x,y+height);
        glTexCoord2f(1.0, 1.0); glVertex2f(x+width,y+height);
        glTexCoord2f(1.0, 0.0); glVertex2f(x+width,y);
        glEnd();
}
void drawSwargTexture(GLuint texture, float x, float y, float height, float width){  // function for drawing textures
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(x,y);
    glTexCoord2f(0.0, 1.0); glVertex2f(x,y+height);
    glTexCoord2f(1.0, 1.0); glVertex2f(x+width,y+height);
    glTexCoord2f(1.0, 0.0); glVertex2f(x+width,y);
    glEnd();
}
void drawScore() {
    char scoreText[30];
    sprintf(scoreText, "    PUNYA = %d", score);
    glColor3f(0.0f, .0f, 0.0f);
    glRasterPos2f(755.0, 548.0);
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void init() {

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   earthBg = SOIL_load_OGL_texture("staticbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   rightClouds = SOIL_load_OGL_texture("rightclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   leftClouds = SOIL_load_OGL_texture("leftclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   leftTrees = SOIL_load_OGL_texture("lefttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   rightTrees = SOIL_load_OGL_texture("righttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   character =SOIL_load_OGL_texture("character.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   honesty = SOIL_load_OGL_texture("honesty.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   meditation = SOIL_load_OGL_texture("meditation.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   anger = SOIL_load_OGL_texture("anger.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   lust = SOIL_load_OGL_texture("lust.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   scoreBoard = SOIL_load_OGL_texture("scoreboard.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   spalace = SOIL_load_OGL_texture("palace.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   hanging = SOIL_load_OGL_texture("Hanging.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pstaticbg = SOIL_load_OGL_texture("staticpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pmovingbg = SOIL_load_OGL_texture("movingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pmirrormovingbg = SOIL_load_OGL_texture("mirrormovingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pcharacter = SOIL_load_OGL_texture("character.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   nviolence = SOIL_load_OGL_texture("nviolence.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   greed = SOIL_load_OGL_texture("pgreed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}
void keyCallback(unsigned char key, int x, int y) {
    if (key == ' ' && !jumping) {
        jumping = true;
        Bjumpduration = 0.0f;
        Sjumpduration = 0.0f;
        Pjumpduration = 0.0f;
        Byvel = 1.5f;
        Syvel = 1.5f;
        Pyvel = 1.5f;
    }
}