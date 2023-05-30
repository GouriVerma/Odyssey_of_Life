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
GLuint introBg, menuBg, scoreBoard,helpBg,help1,help2,help3;
//Textures for Bhuloka
GLuint earthBg, rightClouds, leftClouds, leftTrees, rightTrees, character, honesty,pray, meditation, anger, lust, greed,Bjump,spriteTextures[5];
//Textures for Swargloka
GLuint spalace, hanging;
//Textures for Pattalloka
#define MAX_FRAMES 8
GLuint Pstaticbg, Pmovingbg, Pmirrormovingbg, Pcharacter, nviolence, spriteTexturesp[MAX_FRAMES], Pjump; 
//Textures for transition
GLuint bhutrans, pataltrans, svargatrans;

//Declaring all constants
float screenWidth = 1000.0, screenHeight = 600.0;

//Declaring variables related to time
int elapsedTime = 0;
int startTime;
int currentTime;
int seconds;
int minutes;
//Declaring variables of character
float Pxpos = 200.0, Pypos = 60.0;
float Bxpos = 200.0, Bypos = 70.0;
float Sxpos = 250.0 , Sypos = 60.0;

//Declaring variables of positive obstacles
float Ppxpos1 = 1100.0, Ppxpos2 =1700.0, Ppypos1 = 260.0, Ppypos2 = 260.0;
float Bpxpos1 = 1100.0, Bpxpos2 = 1600.0 , Bpypos1 = 300.0, Bpypos2 = 300.0;

//Declaring variables of negative obstacles
float Pnxpos1 = 1000.0 , Pnxpos2 = 1300.0 , Pnypos1 = 60.0, Pnypos2 = 0.0;
float Bnxpos1 = 1400.0, Bnxpos2 = 1800.0, Bnypos1 = 70.0, Bnypos2 = 70.0;
float Snxpos1 = 1100.0 , Snxpos2 = 1600.0 , Snypos1 = 60.0 , Snypos2 =60.0;

//Declaring variables of elements in different lokas
/*For bhulok position*/
float Brcloudpos = 0.0f, Blcloudpos = 600.0f, Blefttreepos = 0.0, Brighttreepos = 500.0;
/*For bhulok Velocity*/
float Bvel = 1.5f , Byvel = 2.0f;
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
int currentFrame = 0;
/*Pattal loka velocity*/
float Pvel = 1.0, Pyvel=2.0;
float Pobvel=1.0;
float Pjumpduration = 0.0f;

/*For svarglok velocity*/
float Svel = 1.0f , Syvel = 2.0f;
float Sjumpduration = 0.0f;


//Declaring all boolean expression
bool jumping = false;
bool gameStarted = false;
bool help = false;
bool quit = false;
bool back1 = false;
bool next1=false;
bool next2=false;
bool back2=false;
bool back3=false;


//Declaring variables for sound
ALuint backgroundSource, source,buttonSource;

//Declaring variables for score
int score = 0;

//Declaring miscellaneous variable
float k=0.0;
int level = 0;
//Declaring all functions used
/*Texture functions*/
void drawtexture(GLuint texture,float x,float y,float height,float width);
void drawSwargTexture(GLuint texture, float x, float y, float height, float width);
void loadTextures();


void update(int value);

/*Time functions*/
void drawTime();
/*Music functions*/
void playBackgroundMusic(const char* filename);
void playSound(const char* filename);

/*Score functions*/
void drawScore();
void finalscoretext();
void backtext();
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
    loadTextures();
    glutIdleFunc(display);
    glutTimerFunc(100, update, 0);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    alDeleteSources(1, &backgroundSource);
    alDeleteSources(1, &source);
    
    alutExit();

   return 0;
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   if(k<=10.0){
   k=k+0.01;
   }
  
    if (!gameStarted && !help && !quit && !back1&&!next1&&!next2&&!back3&&!back2) {
        
        if(k>=10.0){
        drawtexture(menuBg,0.0,0.0,screenHeight,screenWidth);
        glFlush();
        }
        else{
        drawtexture(introBg,0.0,0.0,screenHeight,screenWidth);
        glFlush();
        } 
    }
   if  (!gameStarted && help && !quit && back1) {
        drawtexture(menuBg,0.0,0.0,screenHeight,screenWidth);
        help = false;
        back1 = false;
    
        glFlush();
   }
  
   if( help && !gameStarted && !quit && !back1&&!next1&&!next2){
        drawtexture(help1,0.0,0.0,screenHeight,screenWidth);
        backtext();
       
        glFlush(); 
   }
   if(!gameStarted && help && !quit && !back1 && next1&&!next2){
    
    drawtexture(help2,0.0,0.0,screenHeight,screenWidth);
       help = false;
        
        glFlush();
   }
  

  if(!gameStarted &&!help && !quit && !back1 && !next1&&next2){
     
      
    drawtexture(help3,0.0,0.0,screenHeight,screenWidth);
       
       
        glFlush();
   }
    if(!gameStarted &&!help && !quit && !back1 && !next1&&!next2&&back2){
     
      
      back2=false;
    drawtexture(help1,0.0,0.0,screenHeight,screenWidth);
       
       
        glFlush();
   }
   if(!gameStarted &&!help && !quit && !back1 && !next1&&!next2&&back3){
    
    drawtexture(help2,0.0,0.0,screenHeight,screenWidth);
       
       
        glFlush();
   }
   if( !help && !gameStarted && quit && !back1 ){
        glutSetWindow(glutGetWindow());
        glutDestroyWindow(glutGetWindow());
   }
   if(gameStarted){ 
     if (startTime == 0) {
            startTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
        }
    if((level == -1) && (minutes <= 1.0)){
        playPatallok();
    }
    else if((level == 1)&& (minutes <= 1.0)){
        playSwarglok();
    }
    else if((level == 0)&& (minutes <= 1.0)){
        playBhulok();
    }  
    drawScore();
    if( minutes >=1.0){
        Pxpos = 200.0, Pypos = 60.0,Bxpos = 200.0, Bypos = 70.0,Sxpos = 250.0 , Sypos = 60.0;
        Ppxpos1 = 1100.0, Ppxpos2 =1700.0, Ppypos1 = 260.0, Ppypos2 = 260.0;
        Pnxpos1 = 1000.0 , Pnxpos2 = 1300.0 , Pnypos1 = 60.0, Pnypos2 = 0.0;
        Bpxpos1 = 1100.0, Bpxpos2 = 1600.0 , Bpypos1 = 260.0, Bpypos2 = 260.0;
        Bnxpos1 = 1400.0, Bnxpos2 = 1800.0, Bnypos1 = 70.0, Bnypos2 = 70.0;
        Snxpos1 = 1100.0 , Snxpos2 = 1600.0 , Snypos1 = 60.0 , Snypos2 =60.0;
        Sbgxpos1 = -5.0f, Sbgxpos2 = 995.0f;
        degree1 = 0.0, degree2 = 0.0, radian1 = 0.0, radian2 = 0.0;
        xHinge1 =750.0, xHinge2 =1250.0;
        changeDir1 = 0, changeDir2 = 0;
        Brcloudpos = 0.0f, Blcloudpos = 600.0f, Blefttreepos = 0.0, Brighttreepos = 500.0;
        PmovingPos=0.0,PmirrormovingPos=1000.0;
        Pk=0;
        if(score <-300){
            level = -1;
            drawtexture(pataltrans,0.0,0.0,screenHeight,screenWidth);
        }else if(score > 300){
            level = 1;
            drawtexture(svargatrans,0.0,0.0,screenHeight,screenWidth);
        } else{
            level = 0;
            drawtexture(bhutrans,0.0,0.0,screenHeight,screenWidth);
        }
    }
    glFlush();
    }
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
    
   
   if(!jumping) {
   glBindTexture(GL_TEXTURE_2D, spriteTextures[currentFrame]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex2f(Pxpos, Pypos);
   glTexCoord2f(1.0f, 0.0f); glVertex2f(Pxpos+140.0,Pypos);
   glTexCoord2f(1.0f, 1.0f); glVertex2f(Pxpos+140.0, Pypos+165.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex2f(Pxpos, Pypos+165.0f);
   glEnd();
       }
    else{ 
        drawtexture(Bjump,Bxpos,Bypos, 165.0,140.0 );
    }
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

    drawtexture(meditation,Bpxpos1,Bpypos1,70.0,72.5);
    Bpxpos1-=Bvel;
    if(Bpxpos1<-60){
    Bpxpos1=1100.0;
    }
    if((Bypos+165.0>=300.0)&&(Bpxpos1<=Bxpos+140.0)&&(Bpxpos1>=Bxpos-72.0)){
    playSound("goodthing.wav");
    alSourcePlay(source);
    score+=100.0;
    Bpxpos1=1300.0;
    }

    drawtexture(pray,Bpxpos2,Bpypos2,70.0,72.5);
    Bpxpos2-=Bvel;
    if(Bpxpos2<-60){
    Bnxpos2=1600.0;
    }
    if((Bypos+165.0>=300.0)&&(Bpxpos2<=Bxpos+140.0)&&(Bpxpos2>=Bxpos-72.5)){
    playSound("goodthing.wav");
    alSourcePlay(source);
    score+=100.0;
    Bpxpos2=1300.0;
    }

    
    drawtexture(anger,Bnxpos1,Bnypos1,70.0,75.0);
    Bnxpos1-=Bvel;
    if(Bnxpos1<-60){
    Bnxpos1=1200.0;
    }
    if((Bypos<=(100.0))&&(Bnxpos1<=(Bxpos+140.0))&&(Bnxpos1>=(Bxpos-75.0))){
    playSound("badthing.wav");
    alSourcePlay(source);
    score-=100.0;
    Bnxpos1=1400.0;
    }

    drawtexture(lust,Bnxpos2,Bnypos2,70.0,75.0);
    Bnxpos2-=Bvel;
    if(Bnxpos2<-60){
    Bnxpos2=1400.0;
    }
    if((Bypos<=(100.0))&&(Bnxpos2<=(Bxpos+140.0))&&(Bnxpos2>=(Bxpos-75.0))){
    playSound("badthing.wav");
    alSourcePlay(source);
    score-=100.0;
    Bnxpos2=1800.0;
    }
    drawtexture(scoreBoard,690.0,510.0,88.0,309.0);
    drawTime();
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

    
    
   glBindTexture(GL_TEXTURE_2D, spriteTextures[currentFrame]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex2f(Pxpos, Pypos);
   glTexCoord2f(1.0f, 0.0f); glVertex2f(Pxpos+140.0,Pypos);
   glTexCoord2f(1.0f, 1.0f); glVertex2f(Pxpos+140.0, Pypos+165.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex2f(Pxpos, Pypos+165.0f);
   glEnd();
       
   
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
        playSound("goodthing.wav");
        alSourcePlay(source);
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
        playSound("goodthing.wav");
        alSourcePlay(source);
        score += 50.0;
        xHinge2 = 1450;
    }

    drawtexture(lust, Snxpos1, 60.0, 40.0, 45.0);
    Snxpos1 -= 1.0;
    if((Snxpos1 + 45.0) <= 0.0) {
        Snxpos1 = 1000.0;
    }
    if((Sypos <= 100.0) && ((Sxpos + 140.0) >= Snxpos1) && (Sxpos <= (Snxpos1 + 45.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 25;
        Snxpos1 = 50.0;
    }

    drawtexture(anger, Snxpos2, 60.0, 40.0, 45.0);
    Snxpos2 -= 1.2;
    if((Snxpos2 + 45.0) <= 0.0) {
        Snxpos2=1500.0;
    }
    if((Sypos <= 100.0) && ((Sxpos + 140.0) >= Snxpos2) && (Sxpos <= (Snxpos2 + 45.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score-=25;
        Snxpos2=1450.0;
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
    drawTime();
}
void playPatallok(){
   drawtexture(Pstaticbg,0.0,0.0,screenHeight,screenWidth);

   drawSwargTexture(Pmovingbg,PmovingPos,0.0,screenHeight,screenWidth +5.0);
   PmovingPos -= Pvel;
   if(PmovingPos+screenWidth<=0.0){
    PmovingPos = 1000.0;
   }

   drawSwargTexture(Pmirrormovingbg,PmirrormovingPos,0.0,screenHeight,screenWidth +5.0);
   PmirrormovingPos -= Pvel;
   if(PmirrormovingPos+screenWidth<=0.0){
    PmirrormovingPos = 1000.0;
   }
   if(!jumping) {
   glBindTexture(GL_TEXTURE_2D, spriteTexturesp[currentFrame]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex2f(Pxpos, Pypos);
   glTexCoord2f(1.0f, 0.0f); glVertex2f(Pxpos+140.0,Pypos);
   glTexCoord2f(1.0f, 1.0f); glVertex2f(Pxpos+140.0, Pypos+165.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex2f(Pxpos, Pypos+165.0f);
   glEnd();
       }
    else{ 
        drawtexture(Pjump,Pxpos,Pypos, 165.0,140.0 );
    }
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
    playSound("badthing.wav");
    alSourcePlay(source);
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
    playSound("badthing.wav");
    alSourcePlay(source);
    score-=25;
    Pnxpos2=1450.0;
   }
   
   drawtexture(meditation ,Ppxpos1,Ppypos1,40.0,45.0);
   Ppxpos1-=Pobvel;
   if(Ppxpos1+45.0<=0.0){
    Ppxpos1=1100;
   }
   if((Pypos+165.0>=260.0)&&(Ppxpos1<=Pxpos+140.0)&&(Ppxpos1>=Pxpos-45.0)){
    playSound("goodthing.wav");
    alSourcePlay(source);
    score+=50;
    Ppxpos1=1300.0;
   }
   
   drawtexture(nviolence,Ppxpos2,Ppypos2,40.0,45.0);
   Ppxpos2-=Pobvel;
   if(Ppxpos2+45.0<=0.0){
    Ppxpos2=1100;
   }
   if((Pypos+165.0>=260.0)&&(Ppxpos2<=Pxpos+140.0)&&(Ppxpos2>=Pxpos-45.0)){
    playSound("goodthing.wav");
    alSourcePlay(source);
    score+=50;
    Ppxpos2=1300.0;
   }
   drawtexture(scoreBoard,690.0,510.0,88.0,309.0);
   drawTime();
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

void backtext() {
    char backText[30];
    sprintf(backText, "GO BACK");
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(880.0, 570.0);
    for (int i = 0; backText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, backText[i]);
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
   pray = SOIL_load_OGL_texture("Pray283,290.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

   meditation = SOIL_load_OGL_texture("Meditation283,290.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   anger = SOIL_load_OGL_texture("panger602,500.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   lust = SOIL_load_OGL_texture("plust602,511.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   scoreBoard = SOIL_load_OGL_texture("scoreboard.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   spalace = SOIL_load_OGL_texture("palace.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   hanging = SOIL_load_OGL_texture("Hanging.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pstaticbg = SOIL_load_OGL_texture("staticpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pmovingbg = SOIL_load_OGL_texture("movingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pmirrormovingbg = SOIL_load_OGL_texture("mirrormovingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pcharacter = SOIL_load_OGL_texture("character.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   nviolence = SOIL_load_OGL_texture("nviolence.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   greed = SOIL_load_OGL_texture("pgreed602,516.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   introBg = SOIL_load_OGL_texture("initialbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   menuBg = SOIL_load_OGL_texture("menu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   helpBg = SOIL_load_OGL_texture("helpbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   bhutrans= SOIL_load_OGL_texture("bhuloktrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   pataltrans = SOIL_load_OGL_texture("pataltrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   svargatrans = SOIL_load_OGL_texture("svargatrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Pjump = SOIL_load_OGL_texture("PJump.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   Bjump=SOIL_load_OGL_texture("ch4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   help1=SOIL_load_OGL_texture("help1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   help2=SOIL_load_OGL_texture("help2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   help3=SOIL_load_OGL_texture("help3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   playBackgroundMusic("music.wav");
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


void mouseClick(int button, int state, int x, int y) {
    if (!gameStarted && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Check if the click is within the "Start Game" text region
        if ((x >= 325.0 && x <= 655.0) && (y >= 172.0 && y <= 272.0) && !help) {
            alSourcePlay(buttonSource);
            gameStarted = true;
        }
        if ((x >= 325.0 && x <= 655.0) && (y >= 315.0 && y <= 414.0) && !help) {
            alSourcePlay(buttonSource);
            help = true;
        }
        if ((x >= 325.0 && x <= 655.0) && (y >= 448.0 && y <= 549.0) && !help) {
            alSourcePlay(buttonSource);
            quit = true;
        }
        if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600.0)&&help) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            back1 = true;
            back3=false;
           
        }
        if ((x >= 880.0 && x <= 988.0) && (y >= 540 && y <= 600)&&help) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            next1 = true;
        }
        if ((x >= 880.0 && x <= 988.0) && (y >= 540 && y <= 600)&&!help) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            next2 = true;
            next1=false;
        }    
       
         if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600)&&!next2) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            back2 = true;
            back3=false;
            next1=false;
            help=true;
        }    
         if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600)&&next2) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            
            back3 = true;
            next2=false;
           // next=true;
        }    
    }
}
void drawTime() {
    char timeText[30];
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    if (((minutes >= 1.0) && (seconds > 10.0) )) {
        startTime = currentTime;  
        seconds = 0;
        minutes = 0;
    } else {
        minutes = (currentTime - startTime) / 60;
        seconds = (currentTime - startTime) % 60;
    }
    sprintf(timeText, "    Time: %02d:%02d", minutes, seconds);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(18.0, 560.0);
    for (int i = 0; timeText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeText[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}

void playBackgroundMusic(const char* filename) {
    ALuint buffer;
    ALenum format;
    ALsizei freq;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    
    alGenBuffers(1, &buffer);
    
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile) {
        printf("Error opening sound file: %s\n", filename);
        return;
    }
    
    if (sfinfo.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2)
        format = AL_FORMAT_STEREO16;
    else {
        printf("Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return;
    }
    
    freq = sfinfo.samplerate;
    
    ALsizei size = sfinfo.frames * sfinfo.channels * sizeof(short);
    short* samples = (short*)malloc(size);
    
    sf_readf_short(sndfile, samples, sfinfo.frames);
    
    alBufferData(buffer, format, samples, size, freq);
    sf_close(sndfile);
    free(samples);
    
    alGenSources(1, &backgroundSource);
    alSourcei(backgroundSource, AL_BUFFER, buffer);
    alSourcei(backgroundSource, AL_LOOPING, AL_TRUE);
    alSourcePlay(backgroundSource);
    
}
void playSound(const char* filename) {
    ALuint buffer;
    ALenum format;
    ALsizei freq;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    
    alGenBuffers(1, &buffer);
    
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile) {
        printf("Error opening sound file: %s\n", filename);
        return;
    }
    
    if (sfinfo.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2)
        format = AL_FORMAT_STEREO16;
    else {
        printf("Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return;
    }
    
    freq = sfinfo.samplerate;
    
    ALsizei size = sfinfo.frames * sfinfo.channels * sizeof(short);
    short* samples = (short*)malloc(size);
    
    sf_readf_short(sndfile, samples, sfinfo.frames);
    
    alBufferData(buffer, format, samples, size, freq);
    sf_close(sndfile);
    free(samples);
    
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
}
void loadTextures() {
    if(level==-1){
 
        char filename[20];
        for (int i = 0; i < MAX_FRAMES; i++)
        {
            sprintf(filename, "PRun%d.png", i + 1);  // Adjust the index offset
            FILE *file = fopen(filename, "rb");
            if (!file)
            {
                printf("Error loading sprite %d\n", i);
                exit(1);
            }
            fclose(file);

            spriteTexturesp[i] = SOIL_load_OGL_texture(
                filename,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_INVERT_Y);
            if (!spriteTexturesp[i])
            {
                printf("Error loading texture %d\n", i);
                exit(1);
            }
        }
    }
    else if(level==0){
        char filename[20];
    for (int i = 0; i < 5; i++)
    {
        sprintf(filename, "ch%d.png", i + 1);  // Adjust the index offset
        FILE *file = fopen(filename, "rb");
        if (!file)
        {
            printf("Error loading sprite %d\n", i);
            exit(1);
        }
        fclose(file);

        spriteTextures[i] = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y);
        if (!spriteTextures[i])
        {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
    }
    }
    else{
        char filename[20];
    for (int i = 0; i < 2; i++)
    {
        sprintf(filename, "A%d.png", i + 1);  // Adjust the index offset
        FILE *file = fopen(filename, "rb");
        if (!file)
        {
            printf("Error loading sprite %d\n", i);
            exit(1);
        }
        fclose(file);

        spriteTextures[i] = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y);
        if (!spriteTextures[i])
        {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
    }

    }
}

void update(int value)
{if(level==-1){
    currentFrame = (currentFrame + 1) % MAX_FRAMES;
    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}
else if(level==0){
     currentFrame = (currentFrame + 1) % 5;
    glutPostRedisplay();
    glutTimerFunc(60, update, 0);

}
else{
    currentFrame = (currentFrame + 1) % 2;
    glutPostRedisplay();
    glutTimerFunc(200, update, 0);


}
}