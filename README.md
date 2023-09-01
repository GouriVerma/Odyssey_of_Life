## Description
This project is a game completely made using C. The game is "Odyssey of Life", a multi-levelled game of three levels, which revolves around your punya gained(points scored) and 3 lokas i.e. bhu-loka , pathal-loka, swarg-loka. You start the game in bhu-loka and based on your punya you either get promoted to swarg-lok or get demoted to pathal-lok. There
are some virtuous objects which increase your punya and also there are some bad objects which can decrease your punya. 

![Alt text](bhuloktrans.png)
![Alt text](pataltrans.png)

![WhatsApp Video 2023-08-30 at 5 24 52 PM 00_00_03_18 Still001](https://github.com/GouriVerma/Odyssey_of_Life/assets/122892114/9354748e-4602-4c5c-b7d4-cf0632078b3d)









## Libraries
OpenGL and OpenAL are the two libraries which are used in making the project. OpenGL is a graphics library which is and abstarct API to draw 2D and 3D graphics and OpenAL is an environmental 3D audio library which is cross-platform audio API.
The header files used under OpenGL library are glut,gl,glew,glu and under OpenAL, header files used are al,alc,alext and alut. Except these header files used are sndfiile and pthread.


## Installation instructions 
For cloning repository- 
```Ubuntu
git clone https://github.com/GouriVerma/Game.git
``` 

For libraries installation
- For OpenGl :
  ```Ubuntu
  sudo apt install mesa-utils libgl1-mesa-dev
  ```
- For glut :
  ```Ubuntu
  sudo apt install freeglut3-dev
- For glew :
  ```Ubuntu
  sudo apt install libglew-dev
  ```
- For OpenAL :
  ```Ubuntu
  sudo apt install libopenal-dev
  ```
- For alut :
  ```Ubuntu
  sudo apt install libalut-dev
  ```
- For sndfile :
  ```Ubuntu
  sudo apt install libsndfile1-dev
- For soil :
  ```Ubuntu
  sudo apt-get install libsoil-dev
  ```
  
  Compiling the file
  
  ```Ubuntu
  cd Game
  gcc -o project project.c -lglut -lGL -lGLEW -lGLU -lglfw -lm -lSOIL -lpthread -lopenal -lsndfile -lalut
  ```
  
 ## Game Insights
 There are 3 levels in this game- Bhu-loka (level 0) from where the game starts, Patal-loka (level -1) and Svarga-loka (level 1). The character runs and      encounter the obstacles in the course of its run and its score i.e punya decreases if it collides with obstacles on ground and its score i.e punya increases if it catches the things in air. If the score at the end of 2 minute is less than -1000 it gets teleported to level -1 and if  it is greater than 2000, it gets teleported to level 1, else stays on the same level i.e level 0.  
 
## Game Controls
There are two things by which you can control the game- spacebar and left mouseclick. If spacebar is pressed, the character jumps and with the help of mouseclick you can navigate to different options on menupage- start, help or quit.

## Code Insights
### For displaying textures and graphics
- drawTexture() : It binds the texture with the ID texture to the 2D texture target in OpenGL which means that subsequent texture operations will affect this texture. It specifies the coordinates of the quadrilateral in which the texture is displayed.
- drawMovingTexture() : It is used to display the textures in loop on the screen. It is used to display the level 1 background and the moving part of level -1 background i.e rocks and platform.
- loadTextures() : It is for loading and displaying the character where there are the sprites of the character in loop in different levels.
- update() : It is a function which sets the framerate for the loadTextures()- the rate at which the different sprites of a character is dispalyed.

### For displaying score and time
- drawTime() : It displays the timer on the top left on the screen. Its main work is to measure the time from the point game started and display it there.
- drawScore() : It displays the updated score on the top right theroughout the course  of game. 

### For user-input
- keyCallback() : It takes the input of the spacebar press and makes the jumping to be true and accordingly set all the variables and make the character readty to jump.
- mouseClick() : It detects the mouseclick of the user and according to the region where user clicked-start,help,quit,next or back; it specifies the menu and help screens.

### For rendering the different levels on screen
- playBhulok() : It is a group of functions which collectively displays background, character, obstacles, score and time of level 0. drawTexture() displays the static background, moving clouds, moving trees and obstacles. A snippet of code displays the sprites of character in loop.
- playPatallok() : Like the above, it is also a group of functions which is rendering background, character, obstacles, score and time of level -1 on screen. drawMovingTexture() is used to display the two mirror images of moving rocks and platform in loop, where one image moves to left and other is displayed next to it. A snippet of code displays the sprites of character in loop.
- playSwarglok() : As above two, the functions in it also collectively displays background, character, obstacles, score and time of level 1. drawMovingTexture() displays the level 1 background in loop, where one image moves to left and again it is rendered. 

### For loading textures in program and displaying it
- init() : It sets the the screen ready to display textures and loads all the images in the program which are being displayed during the game. It also loads the music file in the program.
- display() : This function checks some conditions and display the menu page and help pages accordingly. It checks the level and call the playBhulok(), playSwarglok() and playPatallok() accordingly. Also it displays all the transition screens between the levels.

### For sound
- playBackgroundMusic() : It loads the sound file for background music and play it in loop until the game ends.
- playSound() : It loads the sound for obstacles and mouseclick and play it accordingly.

## Contributors

- Ankit Kumar Singh ([@ankitsingh37](https://github.com/ankitsingh37))
- Sai Nikhita Palisetty ([@SaiNikhita-P](https://github.com/SaiNikhita-P))
- Saurav Kumar Singh  ([@sauravgithub-web](https://github.com/sauravatgithub-web))
- Sreekar Vetsa  ([@SreekarVetsa](https://github.com/SreekarVetsa))
- Gouri Verma  ([@GouriVerma](https://github.com/GouriVerma))




  
  

  
  
  
  

  
  
