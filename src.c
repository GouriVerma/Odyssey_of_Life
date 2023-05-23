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

GLuint texture1,texture2,texture3,texture4,texture5,texture6,texture7,texture8,texture9,texture10,texture11,texture12,texture13,texture14,texture15,texture16,texture17,texture18,texture19;

int elapsedTime = 0;
bool gameStarted = false;
bool help = false;
bool quit = false;
bool back = false;
const int screenWidth = 1000;
const int screenHeight = 600;
float treePos = 0.0;
float tree2Pos = 500.0;
float rcloudPos = 0.0;
float lcloudPos = 600.0;
float xPos = 200.0;
float yPos1 = 70.0f;
float yPos2 = 60.0;
float yVel = 2.0f;
bool jumping = false;
float jumpDuration = 0.0f;
float stonePos = 750.0;
float greedPos = 1250.0;
float Vel = 1.0;
float cVel = 0.3;
float mbg1 = 0.0;
float mbg2 = 1000.0;
int score = 0;
int startTime;
int currentTime;
int seconds;
int minutes;
float k=0.0;
int finalscore;
int level=1;
int y=0;
ALuint backgroundSource, buttonSource, positiveSource, negativeSource;

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

void playButtonSound(const char* filename) {
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
    
    alGenSources(1, &buttonSource);
    alSourcei(buttonSource, AL_BUFFER, buffer);
}
void playPos1itiveSound(const char* filename) {
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
    
    alGenSources(1, &positiveSource);
    alSourcei(positiveSource, AL_BUFFER, buffer);
}
void playNegativeSound(const char* filename) {
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
    
    alGenSources(1, &negativeSource);
    alSourcei(negativeSource, AL_BUFFER, buffer);
}


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
   texture4 = SOIL_load_OGL_texture("lefttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture5 = SOIL_load_OGL_texture("righttrees.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture6 = SOIL_load_OGL_texture("character.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture7 = SOIL_load_OGL_texture("stone.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture8 = SOIL_load_OGL_texture("Greedemoji.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture9 = SOIL_load_OGL_texture("scoreboard.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture10 = SOIL_load_OGL_texture("menutitle.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture11 = SOIL_load_OGL_texture("helpbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y); 
   texture12 = SOIL_load_OGL_texture("initialbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture13 = SOIL_load_OGL_texture("displaybg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture14 = SOIL_load_OGL_texture("staticpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture15 = SOIL_load_OGL_texture("movingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture16 = SOIL_load_OGL_texture("mirrormovingpl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture17 = SOIL_load_OGL_texture("realcloud.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture18 = SOIL_load_OGL_texture("palace2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   texture19 = SOIL_load_OGL_texture("L2transition.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
   playBackgroundMusic("music.wav");
   playButtonSound("option.wav");
   playPos1itiveSound("goodthing.wav");
   playNegativeSound("badthing.wav"); 
}
void keyCallback(unsigned char key, int x, int y) {
    if (key == ' ' && !jumping) {
        jumping = true;
        jumpDuration = 0.0f;
        yVel = 1.5f;
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
        if ((x >= 880.0 && x <= 988.0) && (y >= 10.0 && y <= 30.0)) {
           pthread_t audioThread2Id;
            alSourcePlay(buttonSource);
            back = true;
        }
    }
}
void drawScore() {
    char scoreText[30];
    sprintf(scoreText, "    PUNYA = %d", score);
    glColor3f(0.0f, 0.0f, 0.0f);
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
void finalscoretext() {
    char finalscoreText[50];
    sprintf(finalscoreText, "YOUR SCORE IS %d",score);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(380.0, 450.0);
    for (int i = 0; finalscoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, finalscoreText[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void rdltext(int level) {
    char rdlText[90];
    sprintf(rdlText, "BASED ON YOUR SCORE,YOU ARE REDIRECTED TO LEVEL-%d IN 10 SECONDS",level);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(100.0, 150.0);
    for (int i = 0; rdlText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rdlText[i]);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void drawTime() {
    char timeText[30];
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    if (currentTime - startTime >= 30.0) {
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
void texture(GLuint texture,float x,float y,float height,float width){
    glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(x,y);
        glTexCoord2f(0.0, 1.0); glVertex2f(x,y+height);
        glTexCoord2f(1.0, 1.0); glVertex2f(x+width,y+height);
        glTexCoord2f(1.0, 0.0); glVertex2f(x+width,y);
        glEnd();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   if(k<=10.0){
   k=k+0.01;
   }
   if (!gameStarted && !help && !quit && !back) {
        
        if(k>=10.0){
        texture(texture10,0.0,0.0,screenHeight,screenWidth);
        glFlush();
        }
        else{
        texture(texture12,0.0,0.0,screenHeight,screenWidth);
        glFlush();
        } 
    }
   if  (!gameStarted && help && !quit && back) {
        texture(texture10,0.0,0.0,screenHeight,screenWidth);
        help = false;
        back = false;
        glFlush();
   }
   if( help && !gameStarted && !quit && !back){
        texture(texture10,0.0,0.0,screenHeight,screenWidth);
        backtext();
        glFlush(); 
   }
   if( !help && !gameStarted && quit && !back ){
        glutSetWindow(glutGetWindow());
        glutDestroyWindow(glutGetWindow());
   }
   if(gameStarted){ 
     if (startTime == 0) {
            startTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
        }
if(level ==1 && minutes<=1 && seconds<=20.0){    
   texture(texture1,0.0,0.0,screenHeight,screenWidth);
   texture(texture2,rcloudPos,440.0,140.0,400.0);
   rcloudPos-=cVel;
   if(rcloudPos+400.0<=0.0){
    rcloudPos=1000.0;
   }
   
   texture(texture3,lcloudPos,440.0,140.0,400.0);
   lcloudPos-=cVel;
   if(lcloudPos+400.0<=0.0){
    lcloudPos=1000.0;
   }

   texture(texture4,treePos,213.0,265.0,200.0);
   treePos-=Vel;
   if(treePos+200.0<=0.0){
    treePos=1000.0;
   }

  texture(texture5,tree2Pos,213.0,265.0,300.0);
   tree2Pos-=Vel;
   if(tree2Pos+300.0<=0.0){
    tree2Pos=1000.0;
   }
    
   texture(texture6,xPos,yPos1,165.0,140.0);
   if (jumping) {
        yPos1 += yVel;
        yVel -= 0.01f;
        jumpDuration += 0.01f;
        if (jumpDuration >= 3.0f) {
            jumping = false;
            yPos1 = 70.0f;
            yVel = 0.2f;
            jumpDuration = 0.0f;
        }
    }
    
   texture(texture7,stonePos,65.0,35.0,55.0);
   stonePos-=Vel;
   if(stonePos<-10){
    stonePos=1200.0;
   }
   if((yPos1<=(100.0))&&(stonePos<=(xPos+140.0))&&(stonePos>=(xPos-55.0))){
    alSourcePlay(negativeSource);
    score-=100.0;
    stonePos=1050.0;
   }

   texture(texture8,greedPos,270.0,40.0,45.0);
   greedPos-=Vel;
   if(greedPos<-10){
    greedPos=850.0;
   }
   if((yPos1+165.0>=270.0)&&(greedPos<=xPos+140.0)&&(greedPos>=xPos-45.0)){
    alSourcePlay(positiveSource);
    score+=100.0;
    greedPos=1350.0;
   }

   texture(texture9,690.0,510.0,88.0,309.0);
    drawScore();
    drawTime();
   }
   

   if(level == 2 && minutes<=1 && seconds<=20){
   texture(texture14,0.0,0.0,screenHeight,screenWidth);

   texture(texture15,mbg1,0.0,screenHeight,screenWidth+5.0); 
   mbg1-=0.7;
   if(mbg1+screenWidth<=0.0){
    mbg1 = 1000.0;
   }

   texture(texture16,mbg2,0.0,screenHeight,screenWidth+5.0); 
   mbg2-=0.7;
   if(mbg2+screenWidth<=0.0){
    mbg2 = 1000.0;
   }

   texture(texture6,xPos,yPos2,165.0,140.0); 
   if (jumping) {
        yPos2 += yVel;
        yVel -= 0.01f;
        jumpDuration += 0.01f;
        if (jumpDuration >= 3.0f) {
            jumping = false;
            yPos2 = 70.0f;
            yVel = 0.2f;
            jumpDuration = 0.0f;
        }
    }
    texture(texture9,690.0,510.0,88.0,309.0);
    drawScore();
    drawTime();
   }

   if(level == 3 && minutes<=1 && seconds<=20){
    glBindTexture(GL_TEXTURE_2D, texture18);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(mbg1, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex2f(mbg1, screenHeight);
    glTexCoord2f(1.0, 1.0); glVertex2f(mbg1 + screenWidth+5.0, screenHeight);
    glTexCoord2f(1.0, 0.0); glVertex2f(mbg1 + screenWidth+5.0,0.0);
    glEnd();
    mbg1-=0.5;
    if(mbg1+screenWidth<=0.0){
       mbg1 = 1000.0;
    }
    glBindTexture(GL_TEXTURE_2D, texture18);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex2f(mbg2, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex2f(mbg2, screenHeight);
   glTexCoord2f(1.0, 1.0); glVertex2f(mbg2 + screenWidth+5.0, screenHeight);
   glTexCoord2f(1.0, 0.0); glVertex2f(mbg2 + screenWidth+5.0,0.0);
   glEnd();
   mbg2-=0.5;
   if(mbg2+screenWidth<=0.0){
    mbg2 = 1000.0;
   }
   texture(texture6,xPos,yPos2,165.0,140.0); 
   if (jumping) {
        yPos2 += yVel;
        yVel -= 0.01f;
        jumpDuration += 0.01f;
        if (jumpDuration >= 3.0f) {
            jumping = false;
            yPos2 = 70.0f;
            yVel = 0.2f;
            jumpDuration = 0.0f;
        }
    }
    texture(texture17,xPos-80.0,yPos2-50.0,170.0,300.0);
    drawScore();
    drawTime();
   }


   if(seconds >= 20.0 && seconds <=30.0 && minutes <=1.0) {
       drawTime();
       Vel = 0.0;
       finalscore = score;
       if(score<0){
        level=1;
        rdltext(1);
        treePos=0.0;
        tree2Pos=500.0;
        rcloudPos=0.0;
        lcloudPos=70.0;
        yPos1=70.0;
        Vel=1.0;
        stonePos=750.0;
        greedPos=1250.0;
       }
       if(score>=0&&score<150.0){
        level=2;
        texture(texture19,0.0,0.0,screenHeight,screenWidth);
        finalscoretext();
        rdltext(2);
        mbg1=0.0;
        mbg2=1000.0;
        yPos2=60.0;
       }
       else if(score>=150.0){
        level=3;
        rdltext(3);
        mbg1=0.0;
        mbg2=1000.0;
       } 
   }
   glFlush();
   } 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BHULOKA");
    alutInit(&argc, argv);
    alGetError();
    glewInit();
    glutKeyboardFunc(keyCallback);
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutIdleFunc(display);
    glutMainLoop();
    alDeleteSources(1, &backgroundSource);
    alDeleteSources(1, &buttonSource);
    alDeleteSources(1, &positiveSource);
    alDeleteSources(1, &negativeSource);
    alutExit(); // Close OpenAL device

   return 0;
}