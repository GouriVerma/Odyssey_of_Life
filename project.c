/* API stands for Application Programming Interface. It is a set of rules, protocols, and tools that allows different software 
   applications to communicate and interact with each other. */

#include <stdio.h>
#include <GL/glew.h>    // simplifies the use of openGl extensions
#include <GL/gl.h>      // it is the OPEN GL library
#include <GL/glu.h>     // a companion library of gl library to provide high level graphics
#include <GL/glut.h>    // creating iwndows, handling user input and performing basic input/output operations
#include <SOIL/SOIL.h>  // simplifies the work of texture loading
#include <stdbool.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>    // these three are used for adding audio to the code
#include <AL/alext.h>   // allows access to all extension functions in openAl
#include <sndfile.h>    // helps to read and write audio file texts and provides simple API to work with audio files
#include <stdlib.h>     // string management, mathematical calculations and handling input and output operations
#include <pthread.h>    // provides an API for creating and managing threads in multi threading file
#include <math.h>

// Declaring all textures and functions related to texture
// Textures for menu
GLuint introBg, menuBg, scoreBoard, help1, help2, help3; 
// Textures for Bhuloka
#define B_MAX_FRAMES 5
GLuint earthBg, rightClouds, leftClouds, leftTrees, rightTrees, spriteTexturesB[B_MAX_FRAMES], character;
//Textures for Swargloka
#define S_MAX_FRAMES 10
GLuint spalace, hanging, hanging2, spriteTexturesS[S_MAX_FRAMES];
//Textures for Pattalloka
#define P_MAX_FRAMES 8
GLuint Pstaticbg, Pmovingbg, Pmirrormovingbg, Pcharacter, nviolence, spriteTexturesP[P_MAX_FRAMES], Pjump;  
//Textures for transition
GLuint bhutrans, pataltrans, svargatrans, finaltrans;
// Textures for obstacles
GLuint honesty, meditation, pray, anger, lust, greed, sanger, slust;


// Declaring all constants
float screenWidth = 1000.0, screenHeight = 600.0;  // screen dimensions


// Declaring variables of elements in different lokas

// For bhulok position
int currentFrameB = 0;
float Brcloudpos = 0.0f, Blcloudpos = 600.0f, Blefttreepos = 0.0, Brighttreepos = 500.0;
// For bhulok Velocity
float Bvel = 1.2f , Byvel = 2.0f;
float Bjumpduration = 0.0f;

// For svarglok position
int currentFrameS = 0;
float Sbgxpos1 = -5.0f, Sbgxpos2 = 995.0f;
float degree1 = 0.0, degree2 = 0.0, radian1 = 0.0, radian2 = 0.0; 
float xHinge1 =750.0, xHinge2 =1250.0;
float xOscillate1, yOscillate1;
float xOscillate2, yOscillate2;
int changeDir1 = 0, changeDir2 = 0;
// For svarglok velocity
float Svel = 1.0f , Syvel = 2.0f;
float Sjumpduration = 0.0f;

// Pattal loka position 
float PmovingPos = 0.0, PmirrormovingPos = 1000.0;
int Pk=0;
int currentFrameP = 0;
// Paatal loka velocity 
float Pvel = 1.0, Pyvel=2.0;
float Pobvel=1.2;
float Pjumpduration = 0.0f;


// Declaring variables of positive obstacles
float Ppxpos1 = 1100.0, Ppxpos2 =1700.0, Ppypos1 = 300.0, Ppypos2 = 300.0;
float Bpxpos1 = 1100.0, Bpxpos2 = 1600.0 , Bpypos1 = 300.0, Bpypos2 = 300.0;

// Declaring variables of negative obstacles
float Pnxpos1 = 1000.0 , Pnxpos2 = 1300.0 , Pnypos1 = 60.0, Pnypos2 = 0.0;
float Bnxpos1 = 1400.0, Bnxpos2 = 1800.0, Bnypos1 = 60.0, Bnypos2 = 60.0;
float Snxpos1 = 1100.0 , Snxpos2 = 1600.0 , Snypos1 = 60.0 , Snypos2 =60.0; 


//Declaring variables of character
float Pxpos = 200.0, Pypos = 60.0;
float Bxpos = 200.0, Bypos = 70.0;
float Sxpos = 250.0 , Sypos = 60.0;


//Declaring variables related to time
int elapsedTime = 0;
int startTime;
int currentTime;
int minutes;
int seconds;

// Declaring all test expressions
bool help = false;
bool quit = false;
bool quit2 = false;
bool back1 = false;
bool back2 = false;
bool back3 = false;
bool next1 = false;
bool next2 = false;
bool jumping = false;
bool gameStarted = false;

//Declaring variables for score
int score = 0;

//Declaring miscellaneous variable
float winTime = 0.0;
int level = 0;

// Declaring variables for sound
ALuint backgroundSourceB, backgroundSourceP, backgroundSourceS, source;


// Declaring all functions used
// Input functions
void keyCallback(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y); 

// Two important functions
void init();
void display();

// Texture functions
void drawtexture(GLuint texture,float x,float y,float height,float width);
void drawMovingTexture(GLuint texture,float x,float y,float height,float width);
void loadTexturesB();
void loadTexturesP();
void loadTexturesS();
void updateB(int value);
void updateP(int value);
void updateS(int value);


// Control functions
void drawScore();
void drawTime();

// Game functions
void playBhulok();
void playPatallok();
void playSwarglok();

// Music Functions
void playBackgroundMusicB(const char *filename);
void playBackgroundMusicP(const char *filename);
void playBackgroundMusicS(const char *filename);
void playSound(const char *filename);


// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);  // initializes the glut library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(screenWidth, screenHeight);  // declares window size
    glutCreateWindow("ODYSSEY OF LIFE");
    alutInit(&argc, argv);
    alGetError();
    glewInit();
    glutKeyboardFunc(keyCallback);
    init();
    loadTexturesB();
    loadTexturesP();
    loadTexturesS();
    glutIdleFunc(display);
    glutTimerFunc(100, updateB, 0);
    glutTimerFunc(100, updateP, 0);
    glutTimerFunc(100, updateS, 0);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    alDeleteSources(1, &backgroundSourceB);
    alDeleteSources(1, &backgroundSourceP);
    alDeleteSources(1, &backgroundSourceS);
    alDeleteSources(1, &source);
    alutExit();
   return 0;
}

void init() {

    // These settings prepare the OpenGL context for rendering 2D graphics with transparency support.
    glClearColor(0.0, 0.0, 0.0, 0.0); // Sets initial colour state of pixels.
    glMatrixMode(GL_PROJECTION); // Here we are setting up the projection matrix for projecting 3D to 2D.
    glLoadIdentity(); // This resets the projection matrix to identity matrix to ensure clear starting state each time.
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight); 
    // This establishes a 2D projection matrix and establishes a coordinate system for rendering graphics.
    glEnable(GL_TEXTURE_2D); // It enables the use of 2D textures ahead
    glEnable(GL_BLEND); // It enables alpha blending of the textures.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* This function sets the parameters for blending the new and old pixels.
       GL_SRC_ALPHA specifies the source factor, which uses the alpha value of the source pixel.
       GL_ONE_MINUS_SRC_ALPHA specifies the destination factor, which uses the inverse of the source pixel's alpha value. */
    

    // loading all textures
    // Uniform Textures
    introBg = SOIL_load_OGL_texture("initialbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    menuBg = SOIL_load_OGL_texture("menu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    help1=SOIL_load_OGL_texture("help1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    help2=SOIL_load_OGL_texture("help2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    help3=SOIL_load_OGL_texture("help3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    scoreBoard = SOIL_load_OGL_texture("scoreboard.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    finaltrans = SOIL_load_OGL_texture("finaltrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Bhulok Textures
    earthBg = SOIL_load_OGL_texture("staticbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    rightClouds = SOIL_load_OGL_texture("rightclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    leftClouds = SOIL_load_OGL_texture("leftclouds.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    leftTrees = SOIL_load_OGL_texture("lefttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    rightTrees = SOIL_load_OGL_texture("righttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    character =SOIL_load_OGL_texture("ch3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Swarg Textures
    spalace = SOIL_load_OGL_texture("palace.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    hanging = SOIL_load_OGL_texture("shelp.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    hanging2 = SOIL_load_OGL_texture("skindness.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Patal Textures
    Pstaticbg = SOIL_load_OGL_texture("staticpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    Pmovingbg = SOIL_load_OGL_texture("movingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    Pmirrormovingbg = SOIL_load_OGL_texture("mirrormovingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    Pjump = SOIL_load_OGL_texture("p3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   
    // Positive Obstacles
    honesty = SOIL_load_OGL_texture("honesty.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    meditation = SOIL_load_OGL_texture("meditation.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    nviolence = SOIL_load_OGL_texture("nviolence.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    pray = SOIL_load_OGL_texture("Pray.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Negative Obstacles
    anger = SOIL_load_OGL_texture("anger.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    sanger = SOIL_load_OGL_texture("sanger.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    lust = SOIL_load_OGL_texture("lust.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    slust = SOIL_load_OGL_texture("slust.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    greed = SOIL_load_OGL_texture("pgreed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   
    // Transition Textures
    bhutrans= SOIL_load_OGL_texture("bhuloktrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    pataltrans = SOIL_load_OGL_texture("pataltrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    svargatrans = SOIL_load_OGL_texture("svargatrans.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(level == 0) {
        playBackgroundMusicB("music.wav");
        alSourcePlay(backgroundSourceB);
    }    
    else if(level == -1) {
        playBackgroundMusicP("music.wav");
        alSourcePlay(backgroundSourceP);
    }
    else if(level == 1) {
        playBackgroundMusicS("music.wav");
        alSourcePlay(backgroundSourceS);
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if(winTime <= 10.0) {            // this has been done to display menu window after some time
        winTime = winTime + 0.01;
    }
    if (!gameStarted && !help && !quit && !back1 && !next1 && !next2 && !back3 && !back2 ) {
        if(winTime >= 10.0) {
            drawtexture(menuBg, 0.0, 0.0, screenHeight, screenWidth);
            glFlush();
        }
        else{
            drawtexture(introBg, 0.0, 0.0, screenHeight, screenWidth);
            glFlush();
        } 
    }
    if  (!gameStarted && help && !quit && back1) {
        drawtexture(menuBg, 0.0, 0.0, screenHeight, screenWidth);
        help = false;
        back1 = false;
        glFlush();
    }
    if( help && !gameStarted && !quit && !back1 && !next1 && !next2) {
        drawtexture(help1, 0.0, 0.0, screenHeight, screenWidth);
        glFlush(); 
    }
    if(!gameStarted && help && !quit && !back1 && next1 && !next2) {
        drawtexture(help2, 0.0, 0.0, screenHeight, screenWidth);
        help = false;
        glFlush();
    }
    if(!gameStarted &&!help && !quit && !back1 && !next1 && next2) {
        drawtexture(help3, 0.0, 0.0, screenHeight, screenWidth);
        glFlush();
    }
    if(!gameStarted &&!help && !quit && !back1 && !next1 && !next2 && back2)  {
        back2=false;
        drawtexture(help1, 0.0, 0.0, screenHeight, screenWidth);  
        glFlush();
    }
    if(!gameStarted &&!help && !quit && !back1 && !next1 && !next2 && back3) {
        drawtexture(help2, 0.0, 0.0, screenHeight, screenWidth);
        glFlush();
    }
    if( !help && !gameStarted && quit && !back1 ) {
            glutSetWindow(glutGetWindow());
            glutDestroyWindow(glutGetWindow());  // destroys the existing window
    }

    
    if(gameStarted) {
        if (startTime == 0) {
            startTime = glutGet(GLUT_ELAPSED_TIME) / 1000; // GLUT_ELAPSED_TIME measures time in milliminutes from the points when glut was initialized
        }
        if((level == -1) && (minutes <= 2.0) ) {  // 2 minutes is game time for each level
            playPatallok();
        }
        else if((level == 1)&& (minutes <= 2.0)) {
            playSwarglok();
        }
        else if((level == 0) && (minutes <= 2.0)) {
            playBhulok();
        }  
        drawScore();
        
        if( minutes >= 2.0 ) {
            Pxpos = 200.0, Pypos = 60.0,Bxpos = 200.0, Bypos = 70.0,Sxpos = 250.0 , Sypos = 60.0;
            Ppxpos1 = 1100.0, Ppxpos2 =1700.0, Ppypos1 = 260.0, Ppypos2 = 260.0;
            Pnxpos1 = 1000.0 , Pnxpos2 = 1300.0 , Pnypos1 = 60.0, Pnypos2 = 0.0;
            Bpxpos1 = 1100.0, Bpxpos2 = 1600.0 , Bpypos1 = 260.0, Bpypos2 = 260.0;
            Bnxpos1 = 1400.0, Bnxpos2 = 1800.0, Bnypos1 = 60.0, Bnypos2 = 60.0;
            Snxpos1 = 1100.0 , Snxpos2 = 1600.0 , Snypos1 = 60.0 , Snypos2 =60.0;
            Sbgxpos1 = -5.0f, Sbgxpos2 = 995.0f;
            degree1 = 0.0, degree2 = 0.0, radian1 = 0.0, radian2 = 0.0;
            xHinge1 =750.0, xHinge2 =1250.0;
            changeDir1 = 0, changeDir2 = 0;
            Brcloudpos = 0.0f, Blcloudpos = 600.0f, Blefttreepos = 0.0, Brighttreepos = 500.0;
            PmovingPos=0.0,PmirrormovingPos=1000.0;
            Pk=0;
            drawTime();
            if(score < -2000){
                level = -1;
                drawtexture(pataltrans, 0.0, 0.0, screenHeight, screenWidth);
            }
            else if(score > 3000  && score <= 10000) {
                level = 1;
                drawtexture(svargatrans, 0.0, 0.0, screenHeight, screenWidth);
            }
            else if(score > 10000){
                level = 2;
                drawtexture(finaltrans, 0.0, 0.0, screenHeight, screenWidth);
            }
            else {
                level = 0;
                drawtexture(bhutrans, 0.0, 0.0, screenHeight, screenWidth);
            }
        }
    glFlush();
    }
}
// Control Functions
void drawScore() {
    char scoreText[30];
    sprintf(scoreText, "    PUNYA = %d", score);  // string print formatted writes the formatted string to the character array specified by score here
    glColor3f(0.0f, .0f, 0.0f);
    glRasterPos2f(755.0, 548.0);     // This function fixes the starting coordinates for printing the bitmap image data
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
        // we are using bitmap fonts where every character is displayed as a bitmap image
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void drawTime() {
    char timeText[30];
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    if ((minutes >= 2.0) && (seconds >= 8.0)) {    // After 8 seconds of ending of previous level, a new level will start
        startTime = currentTime;  
        seconds = 0;
        minutes = 0; // both minutes and seconds are readjusted to zero
    } 
    else {
        minutes = (currentTime - startTime) / 60;  // we are calculating minutes and seconds passed after the game starts
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

// Game Functions
void playBhulok() {
    drawtexture(earthBg, 0.0, 0.0, screenHeight, screenWidth);
    drawtexture(rightClouds, Brcloudpos, 440.0, 140.0, 400.0);
    Brcloudpos -= Bvel;
    if((Brcloudpos + 400.0) <= 0.0) {
        Brcloudpos = 1000.0;
    }
    
    drawtexture(leftClouds, Blcloudpos, 440.0, 140.0, 400.0);
    Blcloudpos -= Bvel;
    if((Blcloudpos + 400.0) <= 0.0) {
        Blcloudpos = 1000.0;
    }

    drawtexture(leftTrees, Blefttreepos, 213.0, 265.0, 200.0);
    Blefttreepos -= Bvel;
    if((Blefttreepos + 200.0) <= 0.0) {
        Blefttreepos = 1000.0;
    }

    drawtexture(rightTrees, Brighttreepos, 213.0, 265.0, 300.0);
    Brighttreepos -= Bvel;
    if((Brighttreepos + 300.0) <= 0.0) {
        Brighttreepos = 1000.0;
    }
        
    if(!jumping) {
        glBindTexture(GL_TEXTURE_2D, spriteTexturesB[currentFrameB]);  // moving character in bhulok
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(Bxpos,         Bypos);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(Bxpos + 140.0, Bypos);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(Bxpos + 140.0, Bypos + 165.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(Bxpos,         Bypos + 165.0f);
        glEnd();
    }
    else { 
        drawtexture(character, Bxpos, Bypos, 165.0, 140.0); // jumping charater
    }    
    if (jumping) {
        Bypos += Byvel; //character motion
        Byvel -= 0.01f;  // velocity of character changes continously to show smooth jumping
        Bjumpduration += 0.01f;
        if (Bjumpduration >= 3.0f) {
            jumping = false;
            Bypos = 70.0f;
            Byvel = 0.2f;
            Bjumpduration = 0.0f;
        }
    }

    // positive obstacles hence score will increase
    drawtexture(meditation, Bpxpos1, Bpypos1, 72.0, 72.5);  
    Bpxpos1 -= Bvel;
    if(Bpxpos1 < -60) {
        Bpxpos1 = 1100.0;
    }
    if(((Bypos + 165.0) >= 300.0) && (Bpxpos1 <= (Bxpos + 140.0)) && (Bpxpos1 >= (Bxpos - 72.5))) {
        playSound("goodthing.wav");
        alSourcePlay(source);
        score += 100.0;
        Bpxpos1 = 1300.0;
    }
    drawtexture(honesty, Bpxpos2, Bpypos2, 70.0, 72.5);
    Bpxpos2-=Bvel;
    if(Bpxpos2 < -60) {
        Bpxpos2 = 1600.0;
    }
    if(((Bypos + 165.0) >= 300.0) && (Bpxpos2 <= (Bxpos + 140.0)) && (Bpxpos2 >= (Bxpos - 72.5))) {
        playSound("goodthing.wav");
        alSourcePlay(source);
        score += 100.0;
        Bpxpos2 = 1300.0;
    }

    // negative obstacles hence score will decrease
    drawtexture(anger, Bnxpos1, Bnypos1, 50.0, 50.0);
    Bnxpos1 -= Bvel;
    if(Bnxpos1 < -50) {
        Bnxpos1 = 1200.0;
    }
    if((Bypos <= 120.0) && (Bnxpos1 <= (Bxpos + 140.0)) && (Bnxpos1 >= (Bxpos - 50.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 100.0;
        Bnxpos1 = 1400.0;
    }
    drawtexture(lust, Bnxpos2, Bnypos2, 50.0, 50.0);
    Bnxpos2 -= Bvel;
    if(Bnxpos2 < -50) {
        Bnxpos2 = 1400.0;
    }
    if((Bypos <= 120.0) && (Bnxpos2 <= (Bxpos + 140.0)) && (Bnxpos2 >= (Bxpos - 50.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 100.0;
        Bnxpos2 = 1800.0;
    }

    drawtexture(scoreBoard, 690.0, 510.0, 88.0, 309.0);
    drawTime();
}
void playPatallok() {
    drawtexture(Pstaticbg, 0.0, 0.0, screenHeight, screenWidth);

    drawMovingTexture(Pmovingbg, PmovingPos ,0.0, screenHeight, screenWidth+5.0);
    PmovingPos -= Pvel;
    if((PmovingPos + screenWidth) <= 0.0) {
        PmovingPos = 1000.0;
    }

    drawMovingTexture(Pmirrormovingbg, PmirrormovingPos, 0.0, screenHeight, screenWidth+5.0);
    PmirrormovingPos -= Pvel;
    if((PmirrormovingPos + screenWidth) <= 0.0) {
        PmirrormovingPos = 1000.0;
    }

    // character loading in patal lok
    if(!jumping) {
    glBindTexture(GL_TEXTURE_2D, spriteTexturesP[currentFrameP]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(Pxpos,         Pypos);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(Pxpos + 140.0, Pypos);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(Pxpos + 140.0, Pypos + 165.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(Pxpos,         Pypos + 165.0f);
    glEnd();
    }
    else{ 
        drawtexture(Pjump, Pxpos, Pypos, 165.0, 140.0);
    }
    if (jumping) {
        Pypos += Pyvel;
        Pyvel -= 0.01f;
        Pjumpduration += 0.01f;
        if (Pjumpduration >= 3.0f) {
            jumping = false;
            Pypos = 70.0f;
            Pyvel = 0.2f;
            Pjumpduration = 0.0f;
        }
    }

    // loading bad obstacles
    drawtexture(lust, Pnxpos1, Pnypos1,50.0,50.0); 
    Pnxpos1 -= Pobvel;
    if((Pnxpos1 + 50.0) <= 0.0) {
        Pnxpos1 = 1200.0;
    }
    if((Pypos <= 110.0) && (Pnxpos1 <= (Pxpos + 140.0)) && (Pnxpos1 >= (Pxpos - 50.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 25;
        Pnxpos1 = 1450.0;
    }
    drawtexture(greed, Pnxpos2, Pnypos2, 50.0, 50.0); 
    Pnxpos2 -= Pobvel;
    if((Pnxpos2 + 50) <= 0.0) {
        Pnxpos2 = 1200.0;
    }
    if((Pnypos2 > 100.0) || (Pnypos2 < 0.0)) {
        Pk++;
    }
    if(Pk % 2 == 0) {
        Pnypos2 += 0.5;
    }
    if(Pk % 2 == 1) {
        Pnypos2 -= 0.5;
    }
    if((Pypos <= 110.0) && (Pnxpos2 <= (Pxpos + 140.0)) && (Pnxpos2 >= (Pxpos - 50.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 25;
        Pnxpos2 = 1450.0;
    }
    
    // draw good obstacles
    drawtexture(meditation ,Ppxpos1, Ppypos1, 70.0, 72.5);
    Ppxpos1 -= Pobvel;
    if((Ppxpos1 + 72.5) <= 0.0){
        Ppxpos1 = 1100;
    }
    if(((Pypos + 165.0) >= 300.0) && (Ppxpos1 <= (Pxpos + 140.0)) && (Ppxpos1 >= (Pxpos - 72.0))) {
        playSound("goodthing.wav");
        alSourcePlay(source);
        score += 50;
        Ppxpos1 = 1300.0;
    }
    
    drawtexture(nviolence, Ppxpos2, Ppypos2, 70.0, 72.5);
    Ppxpos2 -= Pobvel;
    if((Ppxpos2 + 72.0) <= 0.0){
        Ppxpos2 = 1100;
    }
    if(((Pypos + 165.0) >= 300.0) && (Ppxpos2 <= (Pxpos + 140.0)) && (Ppxpos2 >= (Pxpos - 72.0))) {
        playSound("goodthing.wav");
        alSourcePlay(source);
        score += 50;
        Ppxpos2 = 1300.0;
    }
    drawtexture(scoreBoard, 690.0, 510.0, 88.0, 309.0);
    drawTime();
}
void playSwarglok(){
    drawMovingTexture(spalace, Sbgxpos1, 0.0, screenHeight, screenWidth +5.0);
    Sbgxpos1 -= Svel;
    if(Sbgxpos1 + screenWidth <= 0.0) {
        Sbgxpos1 = 1000.0;
    }
    drawMovingTexture(spalace, Sbgxpos2, 0.0, screenHeight, screenWidth+5.0);
    Sbgxpos2 -= Svel;
    if(Sbgxpos2 + screenWidth <= 0.0) {
        Sbgxpos2 = 1000.0;
    }

    // character loading in patal lok
    glBindTexture(GL_TEXTURE_2D, spriteTexturesS[currentFrameS]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(Sxpos,         Sypos);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(Sxpos + 140.0, Sypos);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(Sxpos + 140.0, Sypos + 165.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(Sxpos,         Sypos + 165.0f);
    glEnd();
    if (jumping) {
        Pypos += Pyvel;
        Pyvel -= 0.01f;
        Pjumpduration += 0.01f;
        if (Pjumpduration >= 3.0f) {
            jumping = false;
            Pypos = 70.0f;
            Pyvel = 0.2f;
            Pjumpduration = 0.0f;
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
        score += 100.0;
        xHinge1 = 1200;
    }

    xOscillate2 = xHinge2-(200 * sin(radian2));
    yOscillate2 = 450-(200 * cos(radian2));
    glBindTexture(GL_TEXTURE_2D, hanging2);
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
        score += 100.0;
        xHinge2 = 1450;
    }

    drawtexture(slust, Snxpos1, 60.0, 60,60);
    Snxpos1 -= 1.0;
    if((Snxpos1 + 60.0) <= 0.0) {
        Snxpos1 = 1070.0;
    }
    if((Sypos <= 120.0) && (Snxpos1 <= (Sxpos + 140.0)) && (Snxpos1 >= (Sxpos - 60.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score -= 100;
        Snxpos1 = 1050.0;
    }

    drawtexture(sanger, Snxpos2, 60.0, 60.0, 60.0);
    Snxpos2 -= 1.0;
    if((Snxpos2 + 60.0) <= 0.0) {
        Snxpos2=1500.0;
    }
    if((Sypos <= 120.0) && (Snxpos2 <= (Sxpos + 140.0)) && (Snxpos2 >= (Sxpos - 60.0))) {
        playSound("badthing.wav");
        alSourcePlay(source);
        score-= 100;
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


// Texture Functions
// For static Textures
void drawtexture(GLuint texture,float x,float y, float height, float width) {
    glBindTexture(GL_TEXTURE_2D, texture);
    // binds the texture with the ID texture to the 2D texture target in OpenGL which means that subsequent texture operations will affect this texture
    glBegin(GL_QUADS);
    // Defines a sequence of vertices for a quadrilateral
    glTexCoord2f(0.0, 0.0); glVertex2f(x,         y);
    glTexCoord2f(0.0, 1.0); glVertex2f(x,         y + height);
    glTexCoord2f(1.0, 1.0); glVertex2f(x + width, y + height);
    glTexCoord2f(1.0, 0.0); glVertex2f(x + width, y);
    // glTexCoord2f assigns the coordinates in open Gl as height and width are by default 1.
    // glVetex2f adjusts open Gl coordinates to our coordinates
    glEnd();
}
// for moving textures
void drawMovingTexture(GLuint texture, float x, float y, float height, float width){  // function for drawing textures
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* Any texture has two directions - horizontal(s) and vertical(T) - now, if the S or T texture coordinates exceeds [0,1], openGl will wrap
       them around to create a repititive pattern by itself.
       This work is done by GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T. */
     
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(x,y);
    glTexCoord2f(0.0, 1.0); glVertex2f(x,y+height);
    glTexCoord2f(1.0, 1.0); glVertex2f(x+width,y+height);
    glTexCoord2f(1.0, 0.0); glVertex2f(x+width,y);
    glEnd();
}
// for loading sprite textures
void loadTexturesB() {
    char filename[20];
    for (int i = 0; i < B_MAX_FRAMES; i++) {
        sprintf(filename, "ch%d.png", i + 1);  // Adjust the index offset
        FILE *file = fopen(filename, "rb");
        if (!file) {
            printf("Error loading sprite %d\n", i);
            exit(1);
        }
        fclose(file);

        spriteTexturesB[i] = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (!spriteTexturesB[i]) {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
    
    }
}
void loadTexturesP() {
    char filename[20];
    for (int i = 0; i < P_MAX_FRAMES; i++) {
        sprintf(filename, "p%d.png", i + 1);  // Adjust the index offset
        FILE *file = fopen(filename, "rb");
        if (!file) {
            printf("Error loading sprite %d\n", i);
            exit(1);
        }
        fclose(file);

        spriteTexturesP[i] = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (!spriteTexturesP[i]) {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
    
    }
}
void loadTexturesS() {
    char filename[20];
    for (int i = 0; i < S_MAX_FRAMES; i++) {
        sprintf(filename, "s%d.png", i + 1);  // Adjust the index offset
        FILE *file = fopen(filename, "rb");
        if (!file) {
            printf("Error loading sprite %d\n", i);
            exit(1);
        }
        fclose(file);

        spriteTexturesS[i] = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (!spriteTexturesS[i]) {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
    
    }
}
// for updating sprites
void updateB(int value) {   
    currentFrameB = (currentFrameB + 1) % B_MAX_FRAMES;
    glutPostRedisplay();
    glutTimerFunc(100, updateB, 0);
}
void updateP(int value) {   
    currentFrameP = (currentFrameP + 1) % B_MAX_FRAMES;
    glutPostRedisplay();
    glutTimerFunc(100, updateP, 0);
}
void updateS(int value) {   
    currentFrameS = (currentFrameS + 1) % S_MAX_FRAMES;
    glutPostRedisplay();
    glutTimerFunc(100, updateS, 0);
}


// Input Functions
void keyCallback(unsigned char key, int x, int y) {
    if (key == ' ' && !jumping) {  // jumping becomes true on pressing spacebar
        jumping = true;
        Bjumpduration = 0.0f;
        Sjumpduration = 0.0f;
        Pjumpduration = 0.0f;
        Byvel = 1.5f;   // initial velocities while jumping in different lok
        Syvel = 1.5f;
        Pyvel = 1.5f;
    }
    if(key == 27) {     // escape key can be pressed anywhere to quit the game
        glutSetWindow(glutGetWindow());
        glutDestroyWindow(glutGetWindow());
    }
}
void mouseClick(int button, int state, int x, int y) {
    // GLUT_LEFT_BUTTON ensures action will be taken for left button
    // Glut_DOWN ensures that the button is pressed   

    if (winTime > 10.0 && !gameStarted && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (( x >= 325.0 && x <= 655.0) && (y >= 172.0 && y <= 272.0) && !help) { 
            playSound("option.wav");
            alSourcePlay(source);
            gameStarted = true;
        }
        if ((x >= 325.0 && x <= 655.0) && (y >= 315.0 && y <= 414.0) && !help) {
            playSound("option.wav");
            alSourcePlay(source);
            help = true;
        }
        if ((x >= 325.0 && x <= 655.0) && (y >= 448.0 && y <= 549.0) && !help) {
            playSound("option.wav");
            alSourcePlay(source);
            quit = true;
        }
        if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600.0) && help) {
            playSound("option.wav");
            alSourcePlay(source);
            back1 = true;
            back3 = false;
        }
        if ((x >= 880.0 && x <= 988.0) && (y >= 540 && y <= 600) && help) {
            playSound("option.wav");
            alSourcePlay(source);
            next1 = true;
        }
        if ((x >= 880.0 && x <= 988.0) && (y >= 540 && y <= 600) && !help) {
            playSound("option.wav");
            alSourcePlay(source);
            next2 = true;
            next1 = false;
        }    
        if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600) && !next2) {
            playSound("option.wav");
            alSourcePlay(source);
            back2 = true;
            back3 = false;
            next1 = false;
            help = true;
        }    
        if ((x >= 0.0 && x <= 100.0) && (y >= 540 && y <= 600) && next2) {
            playSound("option.wav");
            alSourcePlay(source);
            back3 = true;
            next2 = false;
        } 
    }
}

// music functions
void playBackgroundMusicB(const char* filename) {   // for background music
    ALuint buffer;     // id representing buffer in OpenAl storing the audio data
    ALenum format;     // represents audio format
    ALsizei freq;      // represents frequency
    SNDFILE* sndfile;  // a pointer to SNDFILE structure
    SF_INFO sfinfo;    // a structure which contains information about sound file
    
    alGenBuffers(1, &buffer);   // generates the buffer
    
    sndfile = sf_open(filename, SFM_READ, &sfinfo);  // attempts to open the file specified by filename
    // SFM_READ will open the file in read only mode and all info about the file is stored in sfinfo structure
    if (!sndfile) {
        printf("Error opening sound file: %s\n", filename);
        return;
    }
    
    // sfinfo.channels represents the no. of channels( or sources ) in audio file
    if (sfinfo.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2)
        format = AL_FORMAT_STEREO16;
    else {
        printf("Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return;
    }
    
    //Sample rate is the number of samples per second that are taken of a waveform to create a discete digital signal.
    freq = sfinfo.samplerate; // sample rate of the audio data is assigned to frequency. Higher sample rate means good quality.
    
    ALsizei size = sfinfo.frames * sfinfo.channels * sizeof(short);
    // sfinfo.frames refers to number of audio frames in the sound file. A frame is a collection of samples for all channels at a particular point in time.
    short* samples = (short*)malloc(size);
    /* malloc(size) is dynamically allocating the required memory to samples. We are typecasting it to a short pointer from void pointer*/
    
    sf_readf_short(sndfile, samples, sfinfo.frames);  // reads the audio data and stores it in samples
    
    alBufferData(buffer, format, samples, size, freq);
    sf_close(sndfile);
    free(samples);
    
    alGenSources(1, &backgroundSourceB);
    alSourcei(backgroundSourceB, AL_BUFFER, buffer);    // sets the buffer as the audio source
    
    

}
void playBackgroundMusicP(const char* filename) {   // for background music
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
    
    alGenSources(1, &backgroundSourceP);
    alSourcei(backgroundSourceP, AL_BUFFER, buffer);    

}
void playBackgroundMusicS(const char* filename) {   // for background music
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
    
    alGenSources(1, &backgroundSourceS);
    alSourcei(backgroundSourceS, AL_BUFFER, buffer);    

}
void playSound(const char* filename) {  // for audio sounds on collisions and clicking a button
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