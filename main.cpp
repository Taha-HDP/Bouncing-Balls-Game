//welocome to Dr balls !!
//      1- put this folder on your drive C => "C:\taha_hdp&mahdi_minaii_project\...".
//      2- if you want to increase or decrease the ball speed , change the "w" value in line "1687" .
//developers :
//      Taha Hoveidapour
//      Mahdi Minaii
//<-----------------------------------library ---------------------------------->
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
using namespace std;
//<-------------------------------- display numbers -------------------------------->
string SM="0", ST="0", SF="0";
unsigned  M=100, T=0, t=50, F=100 ;
void changeObject(string &S, unsigned n);
//<-------------------------------- data structure --------------------------------->
#define DATA_SIZE 10
int score[DATA_SIZE] , mainScore=0 , accountNumber=-1 , scoreLine=-1;
string user[DATA_SIZE] , mainAccount="";
bool noAccount=true ;
void getScoreAndUsers();
int signUp(string name);
bool changeScore(int newScore);
//<-------------------------------------- play ------------------------------------->
#define PI 3.1415926535897932
#define Radius 30
#define shotBall_X 400
#define shotBall_Y 900
int freezeBallCount = 3 , slowBallCount = 3 , laserBallCount = 2 , bombBallCount = 3 ;
float ballSpeed = 0.35;
bool freeze = false , slow = false ;
struct topBall{
    double x, y;
    short int r, g, b ,mode , r2,g2,b2;
} ;
struct launchBall{
    double  x = shotBall_X, y = shotBall_Y;
    short int r, g, b;
};
struct RGB{
    short int r, g, b;
};
void shotLine(int X , int Y, double &theta, int A[]);
void shotBall(SDL_Event * event, double theta,int A[],vector<launchBall> launched, vector<topBall> &balls, bool &flag, vector<topBall> &forReturn, vector<topBall> &fallBall, int r[180], int T, topBall R , bool back, bool &countTop);
RGB randColor ();
void randomBall(bool &flag, vector<topBall> &balls );
void addBalls( vector<topBall> &balls);
bool checkCenter(vector<launchBall> launched, vector<topBall> &balls);
RGB checkColorSet(vector<topBall> balls);
bool pauseGame();
int destroyBall( vector<topBall> &balls, vector<topBall> &forReturn, int r[180], int &T, topBall R);
int lowestBall(vector<topBall> balls);
int highestBall(vector<topBall> balls);
int bombBall(vector<topBall> &balls);
int laserBall(vector<topBall> &balls);
bool onlyblack(vector<topBall> &balls);
int dropBall(vector<topBall> &balls, vector<topBall> &fallBall, int r[180], bool &countTop);
void fallingBall(vector<topBall> &fallBall);
void bombPic(vector<launchBall> launched);
void laserPic(vector<launchBall> launched);
//<-------------------------------- menue function --------------------------------->
void setTheme (string themeNumber );
void setSettingBoard(int x, int y, double w, double h);
void setSetting (int t, string SF);
void setScore (int t, string SF);
//<------------------------------------- singUp ------------------------------------->
void setLogin(int t, string SF);
void clearLoginBox();
//<------------------------------------- music -------------------------------------->
void setMusic(string musicNumber);
void setSoundEffect(string soundEffectName);
//<------------------------------------- text --------------------------------------->
void betterText(string S, int x, int y, int r, int g, int b, int a, int size, string fontNumber);
void refreshText(SDL_Renderer *renderer,SDL_Surface *surface,SDL_Texture *texture, string S, int x, int y, int r, int g, int b, int a, int size, string fontNumber);
void drawBG(int X , int Y , int W , int H , int R , int G , int B , int A);
void lable();
//<------------------------------------ motions  ------------------------------------>
void motionMenuLeft(int x, int v, int t , string SF);
void motionPlayLeft(int x, int v, int t , string SF);
//<----------------------------------- scores -------------------------------------->
int makeScore(int balls);
void printScore();
//<----------------------------------- classes ------------------------------------->
class btn{
public :
    int x , y , width , height ;
    string path ;
    btn(int X, int Y, int w , int h , string p){
        x = X ;
        y = Y ;
        width = w ;
        height = h ;
        path = p ;

    }
    void display(SDL_Renderer *m_renderer, int X,int Y){
        SDL_Texture * m_img;
        m_img = IMG_LoadTexture(m_renderer,path.c_str());
        int img_w,img_h;
        SDL_Rect img_rect;
        SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
        img_rect.x=X;
        x=X ;
        img_rect.y=Y;
        img_rect.w=img_w *0.6;
        img_rect.h=img_h *0.6;
        SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
        SDL_DestroyTexture(m_img);
    }
    void settingDisplay(SDL_Renderer * m_renderer, int X,int Y){
        SDL_Texture * m_img;
        m_img = IMG_LoadTexture(m_renderer,path.c_str());
        int img_w,img_h;
        SDL_Rect img_rect;
        x=X ;
        y=Y ;
        SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
        img_rect.x=X;
        img_rect.y=Y;
        img_rect.w=img_w *1;
        img_rect.h=img_h *1;
        SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
        SDL_DestroyTexture(m_img);
    }
    bool click(int X, int Y){
        if(X>x && X< x+width && Y>y && Y< y+height){
            setSoundEffect("click") ;
            return true ;
        }else
            return false ;
    }
};
//<--------------------------------- play buttons ---------------------------------->
btn *randomBtn = new btn(-560,185,500,200,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
btn *infinityBtn = new btn(-560*2,185+200,500,200,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
btn *timerBtn = new btn(-560*3,185+400,500,200,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
btn *backBtn = new btn(-560*4,185+600,500,200,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png");
btn *logoutBtn = new btn(700,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\refresh.png");
btn *PauseBtn = new btn(700,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\pause.png");
btn *ResumeBtn = new btn(600,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\resume.png");

btn *BombBtn = new btn(600,900,50,50,"C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\bomb.png");
btn *LaserBtn = new btn(600,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\laser.png");
btn *FreezeBtn = new btn(600,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\freeze.png");
btn *SlowBtn = new btn(600,900,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\slow.png");
//<---------------------------------- game over ----------------------------------->
btn *restartBtn = new btn(250,600,70,70,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\refresh.png");
//<--------------------------------- menu button ---------------------------------->
btn *playBtn = new btn(-560,185,500,100,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
btn *settingBtn = new btn(-560*2,185+200,500,100,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
btn *scoreBtn = new btn(-560*3,185+400,500,100,"C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\menu_2.png") ;
//<------------------------------- setting buttons --------------------------------->
int X=-75,Y=180,W=70,volume=20 ;
bool mute = false ,soundEffectMute = false;
btn *MenuBtn = new btn(X+445,Y+550,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\menu.png");
btn *MusicBtn = new btn(X+615,Y+190,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png");
btn *SoundBtn = new btn(X+615,Y+360,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound.png");
btn *VolumePlusBtn = new btn(X+655,Y+270,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\plus.png");
btn *VolumeMinusBtn = new btn(X+575,Y+270,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\minus.png");
btn *ThemeNextBtn = new btn(X+360,Y+270,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\next.png");
btn *BallPreviousBtn = new btn(X+225,Y+270,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\previous.png");
btn *MusicNextBtn = new btn(X+655,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\next.png");
btn *MusicPreviousBtn = new btn(X+575,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\previous.png");
btn *FontNextBtn = new btn(X+405,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\next.png");
btn *FSizePlusBtn = new btn(X+315,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\plus.png");
btn *FSizeMinusBtn = new btn(X+225,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\minus.png");
btn *SignUpBtn = new btn(X+225,Y+440,W,W,"C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\pause.png");
//<------------------------------------ SDL init ----------------------------------->
SDL_Window *m_window = SDL_CreateWindow("Dr Balls !!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 1000, SDL_WINDOW_SHOWN);
SDL_Renderer * m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
SDL_Texture * m_texture= SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,800,1000);
//<----------------------------------- timer --------------------------------------->
int secound =00 , minute=00 , newTime=0 , startTime =0 , deltaTime = 0;
string TimePrint = "" ;
void checkTime(bool back);
//<-------------------------------------- main ------------------------------------->
int main(int argc, char **argv) {
    srand(time(NULL));
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
    setMusic(SM);
    setTheme(ST);
    //login
    SDL_Surface* inputSurface = NULL;
    SDL_Texture* inputTexture = NULL;

    setSoundEffect("start") ;
    int mode = 1 ;
    while(mode != 0){
        SDL_Event e;
        bool Display = false;
        // menu
        while(mode == 1){
            if(Display == false){
                motionMenuLeft(-560,30,t,SF);
                Display = true ;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    mode = 0 ;
                }else if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.motion.x , mouseY = e.motion.y;
                    if(playBtn->click(mouseX,mouseY)){
                        if(accountNumber==-1)
                            mode = 8;
                        else
                            mode = 2;
                        Display = false;
                        break ;
                    }else if (settingBtn->click(mouseX,mouseY)){
                        mode = 3 ;
                        Display = false;
                        break ;
                    }else if(scoreBtn->click(mouseX,mouseY)){
                        mode = 4 ;
                        Display = false;
                        break ;
                    }
                }
            }
        }
        //play
        while(mode == 2) {
            if(Display == false) {
                motionPlayLeft(-560, 40, t,SF);
                Display = true;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    mode = 0 ;
                }else if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.motion.x , mouseY = e.motion.y;
                    if(randomBtn->click(mouseX,mouseY)){
                        mode = 5 ;
                        Display = false;
                        break ;
                    }else if (infinityBtn->click(mouseX,mouseY)){
                        mode = 6 ;
                        Display = false;
                        break ;
                    }else if(timerBtn->click(mouseX,mouseY)){
                        mode = 7 ;
                        Display = false;
                        break ;
                    }
                    else if(backBtn->click(mouseX,mouseY)) {
                        mode = 1 ;
                        Display = false;
                        break;
                    }else if(logoutBtn->click(mouseX,mouseY)){
                        mode = 1 ;
                        mainScore=0 ;
                        accountNumber=-1 ;
                        scoreLine=-1;
                        mainAccount="";
                        Display = false;
                        break;
                    }
                }
            }
        }
        //setting
        while(mode == 3) {
            if(Display == false) {
                setSetting(t, SF);
                Display = true;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    mode = 0 ;
                }else if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.motion.x , mouseY = e.motion.y;
                    if (MenuBtn->click(mouseX,mouseY)) {
                        mode = 1;
                        break ;
                    }else if (SoundBtn->click(mouseX,mouseY)) {
                        if(soundEffectMute==false){
                            soundEffectMute = true ;
                            SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound_mute.png" ;
                            SoundBtn->settingDisplay(m_renderer, X+615,Y+460);
                            SDL_RenderPresent(m_renderer);
                        }else {
                            soundEffectMute = false;
                            SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound.png" ;
                            SoundBtn->settingDisplay(m_renderer, X+615,Y+460);
                            SDL_RenderPresent(m_renderer);
                        }
                    }else if (MusicBtn->click(mouseX,mouseY)) {
                        if(mute==false){
                            Mix_VolumeMusic(0) ;
                            MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music_mute.png" ;
                            MusicBtn->settingDisplay(m_renderer, X+615,Y+170);
                            SDL_RenderPresent(m_renderer);
                            mute = true ;
                        }else{
                            if(volume==0)
                                volume=20 ;
                            Mix_VolumeMusic(volume) ;
                            MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                            MusicBtn->settingDisplay(m_renderer, X+615,Y+170);
                            SDL_RenderPresent(m_renderer);
                            mute = false ;
                        }

                    }else if (VolumePlusBtn->click(mouseX,mouseY)) {
                        if(mute==true)
                            mute=false ;
                        if(volume< MIX_MAX_VOLUME-5)
                            volume+=5 ;
                        Mix_VolumeMusic(volume);
                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                        MusicBtn->settingDisplay(m_renderer, X+615,Y+170);
                        SDL_RenderPresent(m_renderer);
                    }else if (VolumeMinusBtn->click(mouseX,mouseY)) {
                        if(volume>=5)
                            volume-=5 ;
                        if(mute==false)
                            Mix_VolumeMusic(volume);

                    }else if (ThemeNextBtn->click(mouseX,mouseY)) {
                        T++;
                        changeObject(ST,T);
                        setTheme(ST);
                        setSetting(t, SF);
                    }else if (BallPreviousBtn->click(mouseX,mouseY)) {
                        setSoundEffect("ballTheme") ;
                    }else if (MusicNextBtn->click(mouseX,mouseY)) {
                        M++;
                        changeObject(SM,M);
                        setMusic(SM);
                    }else if (MusicPreviousBtn->click(mouseX,mouseY)) {
                        M--;
                        changeObject(SM,M);
                        setMusic(SM);
                    }else if (FontNextBtn->click(mouseX,mouseY)) {
                        F++;
                        changeObject(SF,F);
                        setSetting(t,SF);
                    }else if (FSizePlusBtn->click(mouseX,mouseY)) {
                        if(t<60)
                            t+=5;
                        setSetting(t,SF);
                    }else if (FSizeMinusBtn->click(mouseX,mouseY)) {
                        if(t>40)
                            t-=5;
                        setSetting(t,SF);
                    }
                }
            }
        }
        //score
        while(mode == 4) {
            if(Display == false) {
                setScore(t,SF);
                setSoundEffect("play") ;
                Display = true;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    mode = 0 ;
                }else if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.motion.x , mouseY = e.motion.y;
                    if (MenuBtn->click(mouseX,mouseY)) {
                        mode = 1;
                        break ;
                    }
                }
            }
        }
        //random mode
        start_random:
        minute = 0 ;
        secound =0;
        freezeBallCount = 3 ;
        slowBallCount = 3 ;
        laserBallCount = 2 ;
        bombBallCount = 3 ;
        int Mx=0, My=0, lowest_Y=0 , slowTimer , freezeTimer = SDL_GetTicks();
        bool flagcolor=true, flagcolor2=true, flagrandomball=true, countTop= true ;
        freeze = false ;
        slow = false;
        vector<topBall> balls(180);
        vector<launchBall> launched(2);
        vector<topBall>forReturn;
        vector<topBall> fallBall;
        topBall R;
        double theta;
        startTime = SDL_GetTicks() ;
        while(mode == 5) {
            int r[180]={0}, A[100], K=0 ;
            SDL_Event * event = new SDL_Event ();
            SDL_PollEvent(event);
            if (event->type == SDL_QUIT) {
                mode = 0 ;
            }else if(event->type == SDL_MOUSEBUTTONDOWN || event->type== SDL_QUIT ){
                int mouseX = event->motion.x , mouseY = event->motion.y;
                if(PauseBtn->click(mouseX,mouseY)){
                    bool pause = pauseGame() ;
                    while (pause) {
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                mode = 0 ;
                                pause = false ;
                            }else if(e.type == SDL_MOUSEBUTTONDOWN){
                                int mouseX = e.motion.x , mouseY = e.motion.y;
                                if(ResumeBtn->click(mouseX,mouseY)){
                                    pause = false ;
                                }else if (MenuBtn->click(mouseX,mouseY)) {
                                    mode = 1;
                                    pause = false ;
                                    break ;
                                }else if (SoundBtn->click(mouseX,mouseY)) {
                                    if(soundEffectMute==false){
                                        soundEffectMute = true ;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound_mute.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }else {
                                        soundEffectMute = false;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }
                                }else if (MusicBtn->click(mouseX,mouseY)) {
                                    if(mute==false){
                                        Mix_VolumeMusic(0) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music_mute.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = true ;
                                    }else{
                                        if(volume==0)
                                            volume=20 ;
                                        Mix_VolumeMusic(volume) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = false ;
                                    }

                                }else if (VolumePlusBtn->click(mouseX,mouseY)) {
                                    if(mute==true)
                                        mute=false ;
                                    if(volume< MIX_MAX_VOLUME-5)
                                        volume+=5 ;
                                    Mix_VolumeMusic(volume);
                                    MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                    MusicBtn->settingDisplay(m_renderer, 700,100);
                                    SDL_RenderPresent(m_renderer);
                                }else if (VolumeMinusBtn->click(mouseX,mouseY)) {
                                    if(volume>=5)
                                        volume-=5 ;
                                    if(mute==false)
                                        Mix_VolumeMusic(volume);

                                }else if (MusicNextBtn->click(mouseX,mouseY)) {
                                    M++;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }else if (MusicPreviousBtn->click(mouseX,mouseY)) {
                                    M--;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }
                            }
                        }
                    }
                }else if(BombBtn->click(mouseX,mouseY)){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(LaserBtn->click(mouseX,mouseY)){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(SlowBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("score") ;
                    }
                }else if(FreezeBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("freeze") ;

                    }
                }
            }
            if(SDL_GetTicks()-freezeTimer >= 5000 && freeze == true){
                freeze = false ;
                ballSpeed = 0.35 ;
            }else if(SDL_GetTicks()-slowTimer >= 7000 && slow == true){
                slow = false ;
                ballSpeed = 0.35 ;
            }
            SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
            drawBG(0,800,800,200,0,0,0,70) ;
            aalineRGBA(m_renderer,0,800,800,800,255,10,10,255);
            printScore();
            if(freeze==true){
                drawBG(0,0,800,800,100,100,200,40) ;
            }else if(slow==true){
                drawBG(0,0,800,800,200,200,200,50) ;
            }
            if(event->motion.x != 0 && event->motion.y != 0){
                Mx = event->motion.x ;
                My = event->motion.y ;
                shotLine(Mx,My, theta,A);
            }else{
                shotLine(Mx,My, theta,A);
            }
            randomBall(flagrandomball,balls);
            if(flagcolor){
                lowest_Y=lowestBall(balls);
                RGB B=checkColorSet(balls);
                launched[0].r=launched[1].r;
                launched[0].g=launched[1].g;
                launched[0].b=launched[1].b;
                launched[1].r= B.r;
                launched[1].g= B.g;
                launched[1].b= B.b;
                if(flagcolor2){
                    RGB Q=checkColorSet(balls);
                    launched[0].r= Q.r;
                    launched[0].g= Q.g;
                    launched[0].b= Q.b;
                    flagcolor2= false;
                }
                flagcolor=false;
            }
            if(event->type==SDL_KEYDOWN) {
                if (event->key.keysym.sym == SDLK_SPACE) {
                    launchBall L;
                    L = launched[0];
                    launched[0].r = launched[1].r;
                    launched[0].g = launched[1].g;
                    launched[0].b = launched[1].b;
                    launched[1].r = L.r;
                    launched[1].g = L.g;
                    launched[1].b = L.b;
                }else if(event->key.keysym.sym == SDLK_l){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(event->key.keysym.sym == SDLK_b){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(event->key.keysym.sym == SDLK_f && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("freeze") ;
                    }
                }else if(event->key.keysym.sym == SDLK_s && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("score") ;
                    }
                }
            }
            fallingBall(fallBall);
            shotBall(event,theta, A, launched, balls, flagcolor, forReturn, fallBall, r, K, R,false,countTop);
            PauseBtn->settingDisplay(m_renderer,700,900) ;
            checkTime(false);
            SDL_RenderPresent(m_renderer);
            if(balls[lowest_Y].y>800 && balls[lowest_Y].mode != 3){
                drawBG(200,300,400,400,100,100,100,255);
                betterText("Game Over",300,320,255,0,0,255,t-10,SF);
                betterText(TimePrint,250,420,0,255,0,255,t-10,SF);
                betterText("Total Score : " + to_string(mainScore),250,500,255,255,255,255,t-10,SF);
                restartBtn->settingDisplay(m_renderer,265,600) ;
                MenuBtn->settingDisplay(m_renderer,465,600) ;
                setSoundEffect("lose");
                SDL_RenderPresent(m_renderer);
                bool pause = true ;
                while (pause) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            mode = 0;
                            pause = false;
                        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX = e.motion.x, mouseY = e.motion.y;
                            if (restartBtn->click(mouseX, mouseY)) {
                                goto start_random;
                                pause = false ;
                            } else if (MenuBtn->click(mouseX, mouseY)) {
                                mode = 1;
                                pause = false;
                                break;
                            }
                        }
                    }
                }
            }else if(balls.empty() || onlyblack(balls)){
                drawBG(200,300,400,400,100,100,100,255);
                betterText("You Win",300,320,0,255,0,255,t-10,SF);
                betterText(TimePrint,250,420,0,255,0,255,t-10,SF);
                betterText("Total Score : " + to_string(mainScore),250,500,255,255,255,255,t-10,SF);
                restartBtn->settingDisplay(m_renderer,265,600) ;
                MenuBtn->settingDisplay(m_renderer,465,600) ;
                setSoundEffect("win");
                SDL_RenderPresent(m_renderer);
                bool pause = true ;
                while (pause) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            mode = 0;
                            pause = false;
                        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX = e.motion.x, mouseY = e.motion.y;
                            if (restartBtn->click(mouseX, mouseY)) {
                                goto start_random;
                                pause = false ;
                            } else if (MenuBtn->click(mouseX, mouseY)) {
                                mode = 1;
                                pause = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
        //infinity mode
        startTime = SDL_GetTicks() ;
        while(mode == 6) {
            int r[400]={0}, A[100], K=0 ;
            SDL_Event * event = new SDL_Event ();
            SDL_PollEvent(event);
            if (event->type == SDL_QUIT) {
                mode = 0 ;
            }else if(event->type == SDL_MOUSEBUTTONDOWN || event->type== SDL_QUIT ){
                int mouseX = event->motion.x , mouseY = event->motion.y;
                if(PauseBtn->click(mouseX,mouseY)){
                    bool pause = pauseGame() ;
                    while (pause) {
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                mode = 0 ;
                                pause = false ;
                            }else if(e.type == SDL_MOUSEBUTTONDOWN){
                                int mouseX = e.motion.x , mouseY = e.motion.y;
                                if(ResumeBtn->click(mouseX,mouseY)){
                                    pause = false ;
                                }else if (MenuBtn->click(mouseX,mouseY)) {
                                    mode = 1;
                                    pause = false ;
                                    break ;
                                }else if (SoundBtn->click(mouseX,mouseY)) {
                                    if(soundEffectMute==false){
                                        soundEffectMute = true ;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound_mute.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }else {
                                        soundEffectMute = false;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }
                                }else if (MusicBtn->click(mouseX,mouseY)) {
                                    if(mute==false){
                                        Mix_VolumeMusic(0) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music_mute.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = true ;
                                    }else{
                                        if(volume==0)
                                            volume=20 ;
                                        Mix_VolumeMusic(volume) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = false ;
                                    }

                                }else if (VolumePlusBtn->click(mouseX,mouseY)) {
                                    if(mute==true)
                                        mute=false ;
                                    if(volume< MIX_MAX_VOLUME-5)
                                        volume+=5 ;
                                    Mix_VolumeMusic(volume);
                                    MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                    MusicBtn->settingDisplay(m_renderer, 700,100);
                                    SDL_RenderPresent(m_renderer);
                                }else if (VolumeMinusBtn->click(mouseX,mouseY)) {
                                    if(volume>=5)
                                        volume-=5 ;
                                    if(mute==false)
                                        Mix_VolumeMusic(volume);

                                }else if (MusicNextBtn->click(mouseX,mouseY)) {
                                    M++;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }else if (MusicPreviousBtn->click(mouseX,mouseY)) {
                                    M--;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }
                            }
                        }
                    }
                }else if(BombBtn->click(mouseX,mouseY)){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(LaserBtn->click(mouseX,mouseY)){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(SlowBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("freeze") ;
                    }
                }else if(FreezeBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("score") ;
                    }
                }
            }
            if(SDL_GetTicks()-freezeTimer >= 5000 && freeze == true){
                freeze = false ;
                ballSpeed = 0.35 ;
            }else if(SDL_GetTicks()-slowTimer >= 7000 && slow == true){
                slow = false ;
                ballSpeed = 0.35 ;
            }
            SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
            drawBG(0,800,800,200,0,0,0,70) ;
            aalineRGBA(m_renderer,0,800,800,800,255,10,10,255);
            printScore();
            if(freeze==true){
                drawBG(0,0,800,800,100,100,200,40) ;
            }else if(slow==true){
                drawBG(0,0,800,800,200,200,200,50) ;
            }
            if(event->motion.x != 0 && event->motion.y != 0){
                Mx = event->motion.x ;
                My = event->motion.y ;
                shotLine(Mx,My, theta,A);
            }else{
                shotLine(Mx,My, theta,A);
            }
            randomBall(flagrandomball,balls);
            if(flagcolor){
                lowest_Y=lowestBall(balls);
                RGB B=checkColorSet(balls);
                launched[0].r=launched[1].r;
                launched[0].g=launched[1].g;
                launched[0].b=launched[1].b;
                launched[1].r= B.r;
                launched[1].g= B.g;
                launched[1].b= B.b;
                if(flagcolor2){
                    RGB Q=checkColorSet(balls);
                    launched[0].r= Q.r;
                    launched[0].g= Q.g;
                    launched[0].b= Q.b;
                    flagcolor2= false;
                }
                flagcolor=false;
            }
            if(event->type==SDL_KEYDOWN) {
                if (event->key.keysym.sym == SDLK_SPACE) {
                    launchBall L;
                    L = launched[0];
                    launched[0].r = launched[1].r;
                    launched[0].g = launched[1].g;
                    launched[0].b = launched[1].b;
                    launched[1].r = L.r;
                    launched[1].g = L.g;
                    launched[1].b = L.b;
                }else if(event->key.keysym.sym == SDLK_l){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(event->key.keysym.sym == SDLK_b){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(event->key.keysym.sym == SDLK_f && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("freeze") ;
                    }
                }else if(event->key.keysym.sym == SDLK_s && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("score") ;
                    }
                }
            }
            fallingBall(fallBall);
            shotBall(event,theta, A, launched, balls, flagcolor, forReturn,fallBall, r, K, R,false,countTop);
            PauseBtn->settingDisplay(m_renderer,700,900) ;
            checkTime(false);
            SDL_RenderPresent(m_renderer);
            if(balls[lowest_Y].y>800 && balls[lowest_Y].mode != 3){
                drawBG(200,300,400,400,100,100,100,255);
                betterText("Game Over",300,320,255,0,0,255,t-10,SF);
                betterText(TimePrint,250,420,0,255,0,255,t-10,SF);
                betterText("Total Score : " + to_string(mainScore),250,500,255,255,255,255,t-10,SF);
                restartBtn->settingDisplay(m_renderer,265,600) ;
                MenuBtn->settingDisplay(m_renderer,465,600) ;
                setSoundEffect("lose");
                SDL_RenderPresent(m_renderer);
                bool pause = true ;
                while (pause) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            mode = 0;
                            pause = false;
                        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX = e.motion.x, mouseY = e.motion.y;
                            if (restartBtn->click(mouseX, mouseY)) {
                                goto start_random;
                                pause = false ;
                            } else if (MenuBtn->click(mouseX, mouseY)) {
                                mode = 1;
                                pause = false;
                                break;
                            }
                        }
                    }
                }
            }
            int highestBallNum = highestBall(balls) ;
            if(balls[highestBallNum].y>=0){
                vector<topBall> newBall(180);
                addBalls(newBall);
                balls.insert(balls.begin(), newBall.begin(), newBall.end());
            }
        }
        //timer mode
        startTime = SDL_GetTicks() ;
        while(mode == 7) {
            int r[400]={0}, A[100], K=0 ;
            SDL_Event * event = new SDL_Event ();
            SDL_PollEvent(event);
            if (event->type == SDL_QUIT) {
                mode = 0 ;
            }else if(event->type == SDL_MOUSEBUTTONDOWN || event->type== SDL_QUIT ){
                int mouseX = event->motion.x , mouseY = event->motion.y;
                if(PauseBtn->click(mouseX,mouseY)){
                    bool pause = pauseGame() ;
                    while (pause) {
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                mode = 0 ;
                                pause = false ;
                            }else if(e.type == SDL_MOUSEBUTTONDOWN){
                                int mouseX = e.motion.x , mouseY = e.motion.y;
                                if(ResumeBtn->click(mouseX,mouseY)){
                                    pause = false ;
                                }else if (MenuBtn->click(mouseX,mouseY)) {
                                    mode = 1;
                                    pause = false ;
                                    break ;
                                }else if (SoundBtn->click(mouseX,mouseY)) {
                                    if(soundEffectMute==false){
                                        soundEffectMute = true ;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound_mute.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }else {
                                        soundEffectMute = false;
                                        SoundBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\sound.png" ;
                                        SoundBtn->settingDisplay(m_renderer, 700,600);
                                        SDL_RenderPresent(m_renderer);
                                    }
                                }else if (MusicBtn->click(mouseX,mouseY)) {
                                    if(mute==false){
                                        Mix_VolumeMusic(0) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music_mute.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = true ;
                                    }else{
                                        if(volume==0)
                                            volume=20 ;
                                        Mix_VolumeMusic(volume) ;
                                        MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                        MusicBtn->settingDisplay(m_renderer, 700,100);
                                        SDL_RenderPresent(m_renderer);
                                        mute = false ;
                                    }

                                }else if (VolumePlusBtn->click(mouseX,mouseY)) {
                                    if(mute==true)
                                        mute=false ;
                                    if(volume< MIX_MAX_VOLUME-5)
                                        volume+=5 ;
                                    Mix_VolumeMusic(volume);
                                    MusicBtn->path = "C:\\taha_hdp&mahdi_minaii_project\\texture\\setting\\music.png" ;
                                    MusicBtn->settingDisplay(m_renderer, 700,100);
                                    SDL_RenderPresent(m_renderer);
                                }else if (VolumeMinusBtn->click(mouseX,mouseY)) {
                                    if(volume>=5)
                                        volume-=5 ;
                                    if(mute==false)
                                        Mix_VolumeMusic(volume);

                                }else if (MusicNextBtn->click(mouseX,mouseY)) {
                                    M++;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }else if (MusicPreviousBtn->click(mouseX,mouseY)) {
                                    M--;
                                    changeObject(SM,M);
                                    setMusic(SM);
                                }
                            }
                        }
                    }
                }else if(BombBtn->click(mouseX,mouseY)){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(LaserBtn->click(mouseX,mouseY)){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(SlowBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("score") ;
                    }
                }else if(FreezeBtn->click(mouseX,mouseY) && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("freeze") ;
                    }
                }
            }
            if(SDL_GetTicks()-freezeTimer >= 5000 && freeze == true){
                freeze = false ;
                ballSpeed = 0.35 ;
            }else if(SDL_GetTicks()-slowTimer >= 7000 && slow == true){
                slow = false ;
                ballSpeed = 0.35 ;
            }
            SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
            drawBG(0,800,800,200,0,0,0,70) ;
            aalineRGBA(m_renderer,0,800,800,800,255,10,10,255);
            printScore();
            if(freeze==true){
                drawBG(0,0,800,800,100,100,200,40) ;
            }else if(slow==true){
                drawBG(0,0,800,800,200,200,200,50) ;
            }
            if(event->motion.x != 0 && event->motion.y != 0){
                Mx = event->motion.x ;
                My = event->motion.y ;
                shotLine(Mx,My, theta,A);
            }else{
                shotLine(Mx,My, theta,A);
            }
            randomBall(flagrandomball,balls);
            if(flagcolor){
                lowest_Y=lowestBall(balls);
                RGB B=checkColorSet(balls);
                launched[0].r=launched[1].r;
                launched[0].g=launched[1].g;
                launched[0].b=launched[1].b;
                launched[1].r= B.r;
                launched[1].g= B.g;
                launched[1].b= B.b;
                if(flagcolor2){
                    RGB Q=checkColorSet(balls);
                    launched[0].r= Q.r;
                    launched[0].g= Q.g;
                    launched[0].b= Q.b;
                    flagcolor2= false;
                }
                flagcolor=false;
            }
            if(event->type==SDL_KEYDOWN) {
                if (event->key.keysym.sym == SDLK_SPACE) {
                    launchBall L;
                    L = launched[0];
                    launched[0].r = launched[1].r;
                    launched[0].g = launched[1].g;
                    launched[0].b = launched[1].b;
                    launched[1].r = L.r;
                    launched[1].g = L.g;
                    launched[1].b = L.b;
                }else if(event->key.keysym.sym == SDLK_l){
                    if(laserBallCount>0){
                        laserBallCount-- ;
                        launched[0].r = 200;
                        launched[0].g = 200;
                        launched[0].b = 200;
                    }
                }else if(event->key.keysym.sym == SDLK_b){
                    if (bombBallCount > 0) {
                        bombBallCount--;
                        launched[0].r = 250;
                        launched[0].g = 0;
                        launched[0].b = 0;
                    }
                }else if(event->key.keysym.sym == SDLK_f && freeze == false && slow == false){
                    if(freezeBallCount>0){
                        freezeBallCount-- ;
                        ballSpeed = 0.00 ;
                        freezeTimer = SDL_GetTicks();
                        freeze = true ;
                        setSoundEffect("freeze") ;
                    }
                }else if(event->key.keysym.sym == SDLK_s && freeze == false && slow == false){
                    if(slowBallCount>0){
                        slowBallCount-- ;
                        ballSpeed = 0.05 ;
                        slowTimer = SDL_GetTicks();
                        slow = true ;
                        setSoundEffect("score") ;
                    }
                }
            }
            fallingBall(fallBall);
            shotBall(event,theta, A, launched, balls, flagcolor, forReturn,fallBall, r, K, R,true,countTop);
            PauseBtn->settingDisplay(m_renderer,700,900) ;
            checkTime(true);
            SDL_RenderPresent(m_renderer);
            if(minute>= 5||( balls[lowest_Y].y>800 && balls[lowest_Y].mode != 3)){
                drawBG(200,300,400,400,100,100,100,255);
                betterText("Game Over",300,320,255,0,0,255,t-10,SF);
                betterText(TimePrint,250,420,0,255,0,255,t-10,SF);
                betterText("Total Score : " + to_string(mainScore),250,500,255,255,255,255,t-10,SF);
                restartBtn->settingDisplay(m_renderer,265,600) ;
                MenuBtn->settingDisplay(m_renderer,465,600) ;
                setSoundEffect("lose");
                SDL_RenderPresent(m_renderer);
                bool pause = true ;
                while (pause) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            mode = 0;
                            pause = false;
                        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX = e.motion.x, mouseY = e.motion.y;
                            if (restartBtn->click(mouseX, mouseY)) {
                                goto start_random;
                                pause = false ;
                            } else if (MenuBtn->click(mouseX, mouseY)) {
                                mode = 1;
                                pause = false;
                                break;
                            }
                        }
                    }
                }
            }
            int highestBallNum = highestBall(balls) ;
            if(balls[highestBallNum].y>=0){
                vector<topBall> newBall(180);
                addBalls(newBall);
                balls.insert(balls.begin(), newBall.begin(), newBall.end());
            }
        }
        //sign up page
        string inputName = "" ;
        while(mode == 8) {
            if(Display == false) {
                setLogin(t,SF);
                Display = true;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    mode = 0 ;
                }else if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.motion.x , mouseY = e.motion.y;
                    if (MenuBtn->click(mouseX,mouseY)) {
                        mode = 1;
                        break ;
                    }else if (SignUpBtn->click(mouseX,mouseY)) {
                        if(inputName.length()>3 && inputName.length()<=10){
                            signUp(inputName) ;
                            mode = 2;
                        }else{
                            inputName = "" ;
                            clearLoginBox();
                            refreshText(m_renderer,inputSurface,inputTexture,inputName,370,570,0,0,0,255,t,SF);
                            betterText("you need to write a inputName with letters between 4 and 10" ,50,780,255,100,100,255,t-20,SF);
                            SDL_RenderPresent(m_renderer);
                        }
                        break ;
                    }
                }else if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && inputName.length()>0){
                    inputName = inputName.substr(0,inputName.length()-1);
                    clearLoginBox();
                    refreshText(m_renderer,inputSurface,inputTexture,inputName,370,570,0,0,0,255,t,SF);
                }else if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
                    if(inputName.length()>3 && inputName.length()<=10){
                        signUp(inputName) ;
                        mode = 2;
                    }else{
                        inputName = "" ;
                        //cout << inputName ;
                        clearLoginBox();
                        refreshText(m_renderer,inputSurface,inputTexture,inputName,370,570,0,0,0,255,t,SF);
                        betterText("you need to write a inputName with letters between 4 and 10" ,50,780,255,100,100,255,t-20,SF);
                        SDL_RenderPresent(m_renderer);
                    }
                    break ;
                }else if(e.type == SDL_TEXTINPUT && inputName.length()<=10){
                    inputName += e.text.text;
                    int l = inputName.length();
                    int c = count(inputName.begin(), inputName.end(),' ');
                    remove(inputName.begin(), inputName.end(),' ');
                    inputName.resize(l - c);
                    refreshText(m_renderer,inputSurface,inputTexture,inputName,370,570,0,0,0,255,t,SF);
                }

            }
        }
    }
    //close SDL
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    Mix_CloseAudio();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
//<-------------------------------- data structure --------------------------------->
void getScoreAndUsers(){
    fstream dataFile( "data.txt", ios::in ) ;
    //check to open file
    if ( !dataFile ) {
        noAccount = true ;
    }else{
        noAccount = false ;
        for(int i = 0; i < DATA_SIZE ; i++){
            dataFile >> user[i] ;
            dataFile >> score[i] ;
        }
    }
    dataFile.close();
}
int signUp(string name){
    getScoreAndUsers();
    for(int i = 0; i < DATA_SIZE ; i++){
        if(name==user[i] && noAccount==false){
            mainScore = score[i] ;
            mainAccount = user[i] ;
            accountNumber = i ;
            scoreLine = (2*i)+1 ;
            return 0 ;
        }
    }
    noAccount = false ;
    fstream dataFile;
    dataFile.open("data.txt", ios::app) ;
    if ( !dataFile ) {
        cout << "some thing wrong during opening file!\n" ;
        return 1 ;
    }
    dataFile << name << '\n' ;
    dataFile << 0 << '\n' ;
    dataFile.close();
    getScoreAndUsers();
    for(int i = 0; i < DATA_SIZE ; i++){
        if(name==user[i] && noAccount==false){
            cout << "account find\n" ;
            mainScore = score[i] ;
            mainAccount = user[i] ;
            accountNumber = i ;
            scoreLine = (2*i)+1 ;
            return 0 ;
        }
    }
    getScoreAndUsers();
    return 0 ;
}
bool changeScore(int newScore){
    if(accountNumber == -1){
        cout << "you must to login first\n" ;
        return false ;
    }
    fstream dataFile ;
    dataFile.open("data.txt") ;
    vector<string> lines ;
    string line ;
    while(getline(dataFile,line)){
        lines.push_back(line) ;
    }
    dataFile.close();

    ofstream writeFile;
    writeFile.open("data.txt") ;
    for(int i=0 ; i<lines.size() ; i++){
        if(i!= scoreLine)
            writeFile << lines[i] << '\n' ;
        else
            writeFile << newScore << '\n' ;
    }
    writeFile.close();
    getScoreAndUsers();
    return true ;
}
//<------------------------------------ motions  ------------------------------------>
void motionMenuLeft(int x, int v, int t , string SF){
    //-560
    string S1="", S2="", S3="";
    S1="play";
    S2="setting";
    S3="score";
    bool flag= true, FLAG1= false, FLAG2= false, FLAG3= false;
    int x1=x, x2=x*2, x3=x*3;
    int v1=v, v2=v, v3=v;

    while (flag){
        SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
        if (x1>=200){
            v1=-v1;
            FLAG1= true;
        }
        if (x2>=200){
            v2=-v2;
            FLAG2= true;
        }
        if (x3>=200){
            v3=-v3;
            FLAG3= true;
        }
        if (x1<=100&&FLAG1){
            v1=0;
            FLAG1=false;
        }
        if (x2<=100&&FLAG2){
            v2=0;
            FLAG2=false;
        }
        if (x3<=100&&FLAG3){
            v3=0;
            FLAG3=false;
            flag=false;
        }
        SDL_Texture * m_img ;
        playBtn->display(m_renderer, x1 ,-50) ;
        settingBtn->display(m_renderer, x2+20 ,150) ;
        scoreBtn->display(m_renderer, x3+10 ,350) ;
        betterText(S1,x1+230,175,0,0,0,255,t,SF);
        betterText(S2,x2+240,375,0,0,0,255,t,SF);
        betterText(S3,x3+240,575,0,0,0,255,t,SF);
        lable();
        x1+=v1;
        x2+=v2;
        x3+=v3;

        SDL_RenderPresent(m_renderer);
    }
}
void motionPlayLeft(int x, int v, int t , string SF){
    //-560
    SDL_RenderPresent(m_renderer);
    string S1="random", S2="infinity", S3="timer", S4="back";
    bool flag= true, FLAG1= false, FLAG2= false, FLAG3= false, FLAG4= false;
    int x1=x, x2=x*2, x3=x*3, x4=x*4;
    int v1=v, v2=v, v3=v, v4=v;
    string welcome = "welcome " + mainAccount + " , to Dr balls !" ;
    while (flag){
        SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
        if (x1>=200){
            v1=-v1;
            FLAG1= true;
        }
        if (x2>=200){
            v2=-v2;
            FLAG2= true;
        }
        if (x3>=200){
            v3=-v3;
            FLAG3= true;
        }
        if (x4>=200){
            v4=-v4;
            FLAG4= true;
        }
        if (x1<=100&&FLAG1){
            v1=0;
            FLAG1=false;
        }
        if (x2<=100&&FLAG2){
            v2=0;
            FLAG2=false;
        }
        if (x3<=100&&FLAG3){
            v3=0;
            FLAG3=false;
        }
        if (x4<=100&&FLAG4) {
            v4=0;
            FLAG4=false;
            flag=false;
        }
        SDL_Texture * m_img ;
        randomBtn->display(m_renderer, x1+20 ,-50) ;
        infinityBtn->display(m_renderer, x2+20 ,150) ;
        timerBtn->display(m_renderer, x3+20 ,350) ;
        backBtn->display(m_renderer, x4+20 , 550);
        betterText(S1,x1+230,175,0,0,0,255,t,SF);
        betterText(S2,x2+240,375,0,0,0,255,t,SF);
        betterText(S3,x3+245,575,0,0,0,255,t,SF);
        betterText(S4,x4+255,780,0,0,0,255,t,SF);
        drawBG(0,55,800,90,255,255,255,70) ;
        betterText(welcome,120,50,0,0,0,255,t,SF);
        x1+=v1;
        x2+=v2;
        x3+=v3;
        x4+=v4;
        lable();
        logoutBtn->settingDisplay(m_renderer,700,900) ;
        betterText("logout",580,895,0,0,0,255,t-14,SF);
        SDL_RenderPresent(m_renderer);
    }

}
//<-------------------------------- menu function --------------------------------->
void setTheme (string themeNumber){
    string address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\theme\\"+themeNumber+".jpg";
    SDL_Texture * m_img;
    SDL_SetRenderTarget(m_renderer,m_texture);
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    SDL_RenderCopy(m_renderer,m_img,NULL,NULL);
    boxRGBA (m_renderer,800,0,0,1000,0,0,0,120);
    SDL_SetRenderTarget(m_renderer,NULL);
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    SDL_DestroyTexture(m_img);
}
void setSettingBoard( int x, int y, double w, double h){
    string address ="C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\setting.png";
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=x;
    img_rect.y=y;
    img_rect.w=img_w *w;
    img_rect.h=img_h *h;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
}
void setSetting (int t, string SF){
    const int X=-75, Y=180;
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    setSettingBoard(X+140,Y+15,0.5,0.5);

    betterText("Back", X+530, Y+550,255,204,0,255, t-22, SF);
    MenuBtn->settingDisplay(m_renderer, X+445,Y+550 );

    betterText("Sound Effect", X+580, Y+410,255,204,0,255, t-22, SF);
    SoundBtn->settingDisplay(m_renderer, X+615,Y+460);

    betterText("Music", X+610, Y+120,255,204,0,255, t-22, SF);
    MusicBtn->settingDisplay(m_renderer, X+615,Y+170);
    VolumePlusBtn->settingDisplay(m_renderer, X+655,Y+250);
    VolumeMinusBtn->settingDisplay(m_renderer, X+575,Y+250);
    MusicNextBtn->settingDisplay(m_renderer, X+655,Y+330);
    MusicPreviousBtn->settingDisplay(m_renderer, X+575,Y+330);

    betterText("Ball Theme", 170, 180+200,255,204,0,255, t-15, SF);
    ThemeNextBtn->settingDisplay(m_renderer, X+360,Y+270);
    BallPreviousBtn->settingDisplay(m_renderer, X+225,Y+270);

    betterText("Font Setting", X+245, Y+355,255,204,0,255, t-15, SF);
    FSizePlusBtn->settingDisplay(m_renderer, X+315,Y+440);
    FSizeMinusBtn->settingDisplay(m_renderer, X+225,Y+440);
    FontNextBtn->settingDisplay(m_renderer, X+405,Y+440);
    lable();
    SDL_RenderPresent(m_renderer);
}
void setScore (int t, string SF){
    const int X=-5, Y=20;
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    string address ="C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\score.png";
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=X;
    img_rect.y=Y;
    img_rect.w=img_w * 0.8;
    img_rect.h=img_h * 0.8;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
    MenuBtn->settingDisplay(m_renderer, X+370,Y+800 );
    getScoreAndUsers();
    for(int i=0 ; i<5 ; i++){
        betterText(user[i], 150, 415+(i*65),0,0,0,255, t-15, SF);
        betterText(to_string(score[i]), 300, 415+(i*65),0,0,0,255, t-15, SF);
    }for(int i=0 ; i<5 ; i++){
        betterText(user[i+5], 420, 415+(i*65),0,0,0,255, t-15, SF);
        betterText(to_string(score[i+5]), 600, 415+(i*65),0,0,0,255, t-15, SF);
    }
    lable();
    SDL_RenderPresent(m_renderer);
}
//<------------------------------------- singUp ------------------------------------->
void setLogin(int t, string SF){
    const int X=-5, Y=20;
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    string address ="C:\\taha_hdp&mahdi_minaii_project\\texture\\menu\\signUp.png";
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=X;
    img_rect.y=Y;
    img_rect.w=img_w * 0.8;
    img_rect.h=img_h * 0.8;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
    MenuBtn->settingDisplay(m_renderer, X+270,Y+675 );
    SignUpBtn->settingDisplay(m_renderer, X+470,Y+675 );
    SDL_RenderPresent(m_renderer);
}
void clearLoginBox(){
    SDL_Rect a;
    a.x = 370;
    a.y = 590;
    a.w = 290;
    a.h = 70;
    SDL_SetRenderDrawColor(m_renderer, 255, 242, 0, 255);
    SDL_RenderFillRect(m_renderer, &a);
}
//<------------------------------------- music -------------------------------------->
void setMusic (string musicNumber){
    string address ="C:\\taha_hdp&mahdi_minaii_project\\music\\"+musicNumber+".mp3";
    Mix_Music * bgMusic= Mix_LoadMUS(address.c_str());
    Mix_PlayMusic(bgMusic,-1);
    Mix_VolumeMusic(volume);
}
void setSoundEffect (string soundEffectName){
    string address ="C:\\taha_hdp&mahdi_minaii_project\\soundeffect\\"+soundEffectName+".mp3";
    Mix_Chunk * soundEffect= Mix_LoadWAV(address.c_str());
    int channel = Mix_PlayChannel(-1,soundEffect,0);
    if(soundEffectMute==false){
        Mix_Volume(-1, 40);
    }else{
        Mix_Volume(-1, 0);
    }
}
//<------------------------------------ text ---------------------------------------->
void betterText(string S, int x, int y, int r, int g, int b, int a, int size, string fontNumber){
    if(fontNumber=="1" || fontNumber=="2"){
        y+=20 ;
    }else if(fontNumber=="3"){
        y+=25 ;
    }
    switch (t) {
        case 40 :
            y+=10 ;
            break ;
        case 45 :
            y+=5 ;
            break ;
        case 55 :
            y-=5 ;
            x-=4 ;
            break ;
        case 60 :
            y-=10 ;
            x-=7 ;
            break ;
    }
    if (!TTF_WasInit())
        TTF_Init();
    string fontDir = "C:\\taha_hdp&mahdi_minaii_project\\font\\"+fontNumber+".ttf";
    TTF_Font *font = TTF_OpenFont(fontDir.c_str(), size);
    SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, S.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_Rect rect;
    int h, w;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.h = h;
    rect.w = w;
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(m_renderer, texture, NULL, &rect);
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void refreshText(SDL_Renderer *renderer,SDL_Surface *surface,SDL_Texture *texture, string S, int x, int y, int r, int g, int b, int a, int size, string fontNumber){
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    if (!TTF_WasInit())
        TTF_Init();
    string fontDir = "C:\\taha_hdp&mahdi_minaii_project\\font\\"+fontNumber+".ttf";
    TTF_Font *font = TTF_OpenFont(fontDir.c_str(), size);
    SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255};
    surface = TTF_RenderText_Solid(font, S.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (surface != NULL && texture != NULL) {
        SDL_Rect rect;
        rect.h = surface->h;
        rect.w = surface->w;
        rect.x = x;
        rect.y = y;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    SDL_RenderPresent(renderer);
}
void drawBG(int X , int Y , int W , int H , int R , int G , int B , int A){
    SDL_Rect a;
    a.x = X;
    a.y = Y;
    a.w = W;
    a.h = H;
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, R, G, B, A);
    SDL_RenderFillRect(m_renderer, &a);
}
void lable(){
    drawBG(0,920,500,50,255,255,255,70) ;
    betterText("created by Mahdi_Minaii & Taha_HDP",30,920,0,0,0,255,t-25,SF);
}
//<----------------------- changing theme and music anf font ------------------------>
void changeObject(string &S, unsigned n){
    short mod ;
    mod= n%4;
    switch (mod) {
        case 0:
            S="0";
            break;
        case 1:
            S="1";
            break;
        case 2:
            S="2";
            break;
        case 3:
            S="3";
            break;
    }
}
//<-------------------------------------- play ------------------------------------->
void shotLine(int X , int Y, double &theta, int A[]) {
    const int x = shotBall_X, y = shotBall_Y;
    int j=0;
    double mouseX, mouseY, alpha, x1, y1;
    double y2 = 1;
    mouseX = X;
    mouseY = Y;
    if (mouseX > x && mouseY <= y-100) {
        x1 = 800;
        theta = atan((mouseY - y) / (mouseX - x));
        y1 = mouseY + (800 - mouseX) * tan(theta);
        aalineRGBA(m_renderer, x, y, mouseX, mouseY, 255, 0, 0, 255);
        aalineRGBA(m_renderer, mouseX, mouseY, x1, y1, 255, 0, 0, 255);
        A[j++] = y1;
        while (y2 > 0){
            alpha = theta;
            theta = -PI - theta;
            y2 = (y1 + (x) * (-tan(theta)));
            aalineRGBA(m_renderer, x1, y1, x, y2, 255, 0, 0, 255);
            x1 = x;
            y1 = y2;
            y2 = (y1 + (x) * (-tan(theta)));
            aalineRGBA(m_renderer, x1, y1, 0, y2, 255, 0, 0, 255);
            A[j++] = y2;
            theta = alpha;
            x1 = 0;
            y1 = y2;
            y2 = (y1 + (x) * tan(theta));
            aalineRGBA(m_renderer, x1, y1, x, y2, 255, 0, 0, 255);
            x1 = x;
            y1 = y2;
            y2 = (y1 + (x) * (tan(theta)));
            aalineRGBA(m_renderer, x1, y1, 800, y2, 255, 0, 0, 255);
            A[j++] = y2;
            x1 = 800;
            y1 = y2;
        }
    }
    else if (mouseX<x && mouseY <= y-100) {
        x1 = 0;
        theta = atan(-(mouseX - x) / (mouseY - y)) - PI / 2;
        y1 = (mouseY + (mouseX) * (-tan(theta)));
        aalineRGBA(m_renderer, x, y, mouseX, mouseY, 255, 0, 0, 255);
        aalineRGBA(m_renderer, mouseX, mouseY, x1, y1, 255, 0, 0, 255);
        A[j++] = y1;
        while (y2 > 0) {
            alpha = theta;
            theta = -PI - theta;
            y2 = (y1 + (x) * tan(theta));
            aalineRGBA(m_renderer, x1, y1, x, y2, 255, 0, 0, 255);
            x1 = x;
            y1 = y2;
            y2 = (y1 + (x) * (tan(theta)));
            aalineRGBA(m_renderer, x1, y1, 800, y2, 255, 0, 0, 255);
            A[j++] = y2;
            x1 = 800;
            y1 = y2;
            theta = alpha;
            y2 = (y1 + (x) * (-tan(theta)));
            aalineRGBA(m_renderer, x1, y1, x, y2, 255, 0, 0, 255);
            x1 = x;
            y1 = y2;
            y2 = (y1 + (x) * (-tan(theta)));
            aalineRGBA(m_renderer, x1, y1, 0, y2, 255, 0, 0, 255);
            A[j++] = y2;
            x1 = 0;
            y1 = y2;
        }
    }
}
void shotBall(SDL_Event * event, double theta,int A[],vector<launchBall> launched, vector<topBall> &balls, bool &flag, vector<topBall> &forReturn, vector<topBall> &fallBall, int r[180], int T, topBall R , bool back, bool &countTop){
    double dy=-tan(-theta), w, dx=1;
    int j=0;
    w = 20 ;
    w=-w/dy;
    dy*=w;
    dx*=w;
    bool FLAG=false;
    if(FLAG==false) {
        filledCircleRGBA(m_renderer, shotBall_X, shotBall_Y+65, Radius-7, launched[1].r, launched[1].g, launched[1].b, 255);
        filledCircleRGBA(m_renderer, shotBall_X, shotBall_Y, Radius, launched[0].r, launched[0].g, launched[0].b, 255);
        bombPic(launched);
        laserPic(launched);
    }
    if(event->type==SDL_MOUSEBUTTONDOWN && event->motion.y<=launched[0].y-100) {
        FLAG = true;
        countTop= true;
        setSoundEffect("cannon") ;
        SDL_PollEvent(event);
    }
    while(FLAG && launched[0].y>=Radius) {
        launched[0].x += dx;
        launched[0].y += dy;
        if (launched[0].x>=800) {
            launched[0].x=800;
            launched[0].y=A[j++];
            dx = -dx;
        }
        if (launched[0].x<=0) {
            launched[0].x=0;
            launched[0].y=A[j++];
            dx = -dx;
        }

        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        fallingBall((fallBall));
        drawBG(0,800,800,200,0,0,0,70) ;
        filledCircleRGBA(m_renderer, shotBall_X, shotBall_Y+65, Radius-7, launched[1].r, launched[1].g, launched[1].b, 255);
        aalineRGBA(m_renderer,0,800,800,800,255,10,10,255);
        printScore();
        if(freeze==true){
            drawBG(0,0,800,800,100,100,200,40) ;
        }else if(slow==true){
            drawBG(0,0,800,800,200,200,200,50) ;
        }
        PauseBtn->settingDisplay(m_renderer,700,900) ;
        //copied from second part of randomBall function
        for(int i=0; i<balls.size(); i++){
            balls[i].y+=ballSpeed;
            filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius, balls[i].r, balls[i].g, balls[i].b, 255);
            if(balls[i].mode==1)
                filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius-15, balls[i].r2, balls[i].g2, balls[i].b2, 255);
            else if(balls[i].mode==2){
                filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius-15, 0, 0, 0, 255);
            }
        }
        if(checkCenter(launched,balls)){
            //score calculation and remove balls
            if(launched[0].r==200){
                int ballsNumber = laserBall(balls)+dropBall(balls,fallBall,r,countTop);
                if(ballsNumber != 0)
                    makeScore(ballsNumber) ;
                flag=true;
                break;
            }else if(launched[0].r==250){
                int ballsNumber = bombBall(balls)+dropBall(balls,fallBall,r,countTop) ;
                if(ballsNumber != 0)
                    makeScore(ballsNumber) ;
                flag=true;
                break;
            }else{
                int ballsNumber = destroyBall(balls,forReturn,r,T,R)+dropBall(balls,fallBall,r,countTop) ;
                if(ballsNumber != 0)
                    makeScore(ballsNumber) ;
                flag=true;
                break;
            }
        }
        filledCircleRGBA(m_renderer, launched[0].x, launched[0].y, Radius, launched[0].r, launched[0].g, launched[0].b, 255);
        bombPic(launched);
        laserPic(launched);
        checkTime(back);
        SDL_RenderPresent(m_renderer);
        //SDL_Delay(10);
    }
}
RGB randColor (){
    RGB A;
    switch (rand()%4) {
        case 0:
            A.r=0;
            A.g=100;
            A.b=250;
            break;
        case 1:
            A.r=50;
            A.g=60;
            A.b=120;
            break;
        case 2:
            A.r=100;
            A.g=200;
            A.b=20;
            break;
        case 3:
            A.r=150;
            A.g=30;
            A.b=100;
            break;
    }
    return A;
}
void randomBall( bool &flag, vector<topBall> &balls ) {
    int y1 = 30-632, y2 = 82-632, z = 0;
    if(flag) {
        for (int j = 0; j <= 5; j++) {
            for (int i = 0; i <= 12; i++) {
                RGB A = randColor() , B = randColor();
                balls[z].x = 40 + (2 * i * 30);
                balls[z].y = y1;
                balls[z].r = A.r;
                balls[z].g = A.g;
                balls[z].b = A.b;
                balls[z].mode = 0 ;
                filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius, balls[z].r, balls[z].g, balls[z].b, 255);
                int createMode = rand()%15 ;
                switch (createMode){
                    case 2 :
                        balls[z].mode = 1 ;
                        balls[z].r2 = B.r;
                        balls[z].g2 = B.g;
                        balls[z].b2 = B.b;
                        filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius-15, balls[z].r2, balls[z].g2, balls[z].b2, 255);
                        break ;
                    case 3 :
                        balls[z].mode = 2 ;
                        //cout << z << endl;
                        break ;
                    case 4 :
                        balls[z].mode = 3 ;
                        balls[z].r = 20;
                        balls[z].g = 20;
                        balls[z].b = 20;
                        break ;
                }
                z++;
            }
            y1 += 104;
            for (int i = 1; i <= 12; i++) {
                RGB A = randColor() , B = randColor();
                balls[z].x = 10 + (2 * i * 30);
                balls[z].y = y2;
                balls[z].r = A.r;
                balls[z].g = A.g;
                balls[z].b = A.b;
                balls[z].mode = 0 ;
                filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius, balls[z].r, balls[z].g, balls[z].b, 255);
                int createMode = rand()%15 ;
                switch (createMode){
                    case 2 :
                        balls[z].mode = 1 ;
                        balls[z].r2 = B.r;
                        balls[z].g2 = B.g;
                        balls[z].b2 = B.b;
                        filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius-15, balls[z].r2, balls[z].g2, balls[z].b2, 255);
                        break ;
                    case 3 :
                        balls[z].mode = 2 ;
                        //cout << z << endl;
                        break ;
                    case 4 :
                        balls[z].mode = 3 ;
                        balls[z].r = 20;
                        balls[z].g = 20;
                        balls[z].b = 20;
                        break ;
                }
                z++;
            }
            y2 += 104;
        }
        balls.resize(z);
    }
    else{
        for(int i=0; i<balls.size(); i++){
            balls[i].y+=ballSpeed;
            filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius, balls[i].r, balls[i].g, balls[i].b, 255);
            if(balls[i].mode==1)
                filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius-15, balls[i].r2, balls[i].g2, balls[i].b2, 255);
            else if(balls[i].mode==2){
                filledCircleRGBA(m_renderer, balls[i].x, balls[i].y, Radius-15, 0, 0, 0, 255);
            }
        }
    }
    flag=false;
}
void addBalls( vector<topBall> &balls){
    int y1 = 30-655, y2 = 82-655 , z=0;
    for (int j = 0; j <= 5; j++) {
        for (int i = 0; i <= 12; i++) {
            RGB A = randColor() , B = randColor();
            balls[z].x = 40 + (2 * i * 30);
            balls[z].y = y1;
            balls[z].r = A.r;
            balls[z].g = A.g;
            balls[z].b = A.b;
            balls[z].mode = 0 ;
            filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius, balls[z].r, balls[z].g, balls[z].b, 255);
            int createMode = rand()%15 ;
            switch (createMode){
                case 2 :
                    balls[z].mode = 1 ;
                    balls[z].r2 = B.r;
                    balls[z].g2 = B.g;
                    balls[z].b2 = B.b;
                    filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius-15, balls[z].r2, balls[z].g2, balls[z].b2, 255);
                    break ;
                case 3 :
                    balls[z].mode = 2 ;
                    //cout << z << endl;
                    break ;
                case 4 :
                    balls[z].mode = 3 ;
                    balls[z].r = 20;
                    balls[z].g = 20;
                    balls[z].b = 20;
                    break ;
            }
            z++;
        }
        y1 += 104;
        for (int i = 1; i <= 12; i++) {
            RGB A = randColor() , B = randColor();
            balls[z].x = 10 + (2 * i * 30);
            balls[z].y = y2;
            balls[z].r = A.r;
            balls[z].g = A.g;
            balls[z].b = A.b;
            balls[z].mode = 0 ;
            filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius, balls[z].r, balls[z].g, balls[z].b, 255);
            int createMode = rand()%15 ;
            switch (createMode){
                case 2 :
                    balls[z].mode = 1 ;
                    balls[z].r2 = B.r;
                    balls[z].g2 = B.g;
                    balls[z].b2 = B.b;
                    filledCircleRGBA(m_renderer, balls[z].x, balls[z].y, Radius-15, balls[z].r2, balls[z].g2, balls[z].b2, 255);
                    break ;
                case 3 :
                    balls[z].mode = 2 ;
                    //cout << z << endl;
                    break ;
                case 4 :
                    balls[z].mode = 3 ;
                    balls[z].r = 20;
                    balls[z].g = 20;
                    balls[z].b = 20;
                    break ;
            }
            z++;
        }
        y2 += 104;
    }
    balls.resize(z);
}
bool checkCenter(vector<launchBall> launched, vector<topBall> &balls){
    for(int i=0; i<balls.size(); i++){
        if(abs(launched[0].y-balls[i].y)<=60) {
            if(sqrt((launched[0].x-balls[i].x)*(launched[0].x-balls[i].x)+(launched[0].y-balls[i].y)*(launched[0].y-balls[i].y))<=43){
                topBall T;
                T.r=launched[0].r;
                T.g=launched[0].g;
                T.b=launched[0].b;
                if((launched[0].y>balls[i].y)){
                    if((launched[0].x>balls[i].x)){//down_right
                        T.x=balls[i].x+30;
                        T.y=balls[i].y+52;
                    }else{//down_left
                        T.x=balls[i].x-30;
                        T.y=balls[i].y+52;
                    }
                }else{
                    if((launched[0].x>balls[i].x)){//up_right
                        T.x=balls[i].x+30;
                        T.y=balls[i].y-52;
                    }else{//up_left
                        T.x=balls[i].x-30;
                        T.y=balls[i].y-52;
                    }
                }
                balls.push_back(T);
                return true;
            }

        }
    }
}
RGB checkColorSet(vector<topBall> balls){
    bool purple=false, blue=false, green=false, red=false;
    for(int i=0; i<balls.size(); i++){
        if(!blue && balls[i].r==0){
//            cout<<"blue"<<endl;
            blue= true;
        } if(!purple && balls[i].r==50){
//            cout<<"purple"<<endl;
            purple= true;
        } if(!green && balls[i].r==100){
//            cout<<"green"<<endl;
            green= true;
        } if(!red && balls[i].r==150){
//            cout<<"red"<<endl;
            red= true;
        }
    }
    while(true) {
        RGB A;
        int R= rand();
        if (R % 4 == 0 && blue) {
            A.r = 0;
            A.g = 100;
            A.b = 250;
            return A;
        } else if (R % 4 == 1 && purple) {
            A.r=50;
            A.g=60;
            A.b=120;
            return A;
        } else if (R % 4 == 2 && green) {
            A.r=100;
            A.g=200;
            A.b=20;
            return A;
        } else if (R % 4 == 3 && red) {
            A.r=150;
            A.g=30;
            A.b=100;
            return A;
        }
    }
}
bool pauseGame(){
    for(int i=0 ; i<=130 ; i+=5){
        drawBG(800-i,0,130,1000,255,242,0,255) ;
        if(i>=30){
            MusicBtn->settingDisplay(m_renderer,830-i,100);
            VolumePlusBtn->settingDisplay(m_renderer,830-i,200);
            VolumeMinusBtn->settingDisplay(m_renderer,830-i,300);
            MusicNextBtn->settingDisplay(m_renderer,830-i,400);
            MusicPreviousBtn->settingDisplay(m_renderer,830-i,500);
            SoundBtn->settingDisplay(m_renderer,830-i,600);
            MenuBtn->settingDisplay(m_renderer,830-i,800);
            ResumeBtn->settingDisplay(m_renderer,830-i,900);
        }
        SDL_RenderPresent(m_renderer);
    }
    return true ;
}
int destroyBall( vector<topBall> &balls, vector<topBall> &forReturn, int r[400], int &T, topBall R){
    for(int i=0 ; i<balls.size() ; i++) {
        int t=sqrt((balls.back().x - balls[i].x) * (balls.back().x - balls[i].x)+(balls.back().y - balls[i].y) * (balls.back().y - balls[i].y));
        if (t>0 && t<65 && r[i] == 0 && balls.back().r == balls[i].r && balls[i].mode == 2) {
            balls[i].mode = 0 ;
        }else if (t>0 && t<65 && r[i] == 0 && balls.back().r == balls[i].r) {
            R.x = balls.back().x;
            R.y = balls.back().y;
            R.r = balls.back().r;
            R.g = balls.back().g;
            R.b = balls.back().b;
            if(r[balls.size()-1]==0)
                r[balls.size()-1]=1;
            r[i] = 1;
            forReturn.push_back(R);
            balls.back().x = balls[i].x;
            balls.back().y = balls[i].y;
            return destroyBall( balls, forReturn, r, T, R);
        }else if(t>0 && t<65 && balls[i].mode == 1 && r[i] == 0 && balls.back().r == balls[i].r2){
            R.x = balls.back().x;
            R.y = balls.back().y;
            R.r = balls.back().r;
            R.g = balls.back().g;
            R.b = balls.back().b;
            if(r[balls.size()-1]==0)
                r[balls.size()-1]=1;
            r[i] = 1;
            forReturn.push_back(R);
            balls.back().x = balls[i].x;
            balls.back().y = balls[i].y;
            return destroyBall( balls, forReturn, r, T, R);
        }

    }
    bool flag=false;
    for (int j=0 ; j<balls.size() ; j++){
        if(r[j]==1) {
            T += r[j];
            r[j]=2;
        }
    }
    if(T<3) {
        flag = true;
        if (T == 2) {
            balls.back() = forReturn.front();
            forReturn.clear();
        }
    }
    if (flag)
        return 0;
    else {
        forReturn.pop_back();
        if (forReturn.empty()) {
            int s=balls.size(), I=0;
            topBall C;
            for(int i=0 ; i<s ; i++) {
                if (r[i] != 0) {
                    //cout << "vector erase = " << i<< endl ;
                    balls.erase(balls.begin() + i);
                    balls.insert(balls.begin(),C);
                    I++;
                }
            }
            for(int i=0 ; i<I ; i++){
                balls.erase(balls.begin());
            }
            setSoundEffect("explode") ;
            return T;
        } else {
            balls.back().x = forReturn.back().x;
            balls.back().y = forReturn.back().y;
            return destroyBall(balls, forReturn, r, T, R);
        }
    }
}
int lowestBall(vector<topBall> balls){
    int i=0, max, j=0;
    max=balls[i].y;
    i++;
    for(i ; i<balls.size() ; i++)
        if(max<balls[i].y && balls[i].mode != 3) {
            max = balls[i].y;
            j=i;
        }
    return j;
}
int highestBall(vector<topBall> balls){
    int i=balls.size()-1, max, j=0;
    max=balls[i].y;
    i--;
    for(i ; i>0 ; i--)
        if(max>balls[i].y) {
            max = balls[i].y;
            j=i;
        }
    return j;
}
int bombBall(vector<topBall> &balls){
    setSoundEffect("bomb") ;
    int I=0;
    topBall C;


    string address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\bombEffect.png";
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=balls.back().x-70;
    img_rect.y=balls.back().y-70;
    img_rect.w=img_w*1.4;
    img_rect.h=img_h*1.4 ;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(100) ;
    for(int i=0 ; i<balls.size() ; i++){
        int t=sqrt((balls.back().x - balls[i].x) * (balls.back().x - balls[i].x)+(balls.back().y - balls[i].y) * (balls.back().y - balls[i].y));
        if(t<=125){
            balls.erase(balls.begin() + i);
            balls.insert(balls.begin(),C);
            I++;
        }
    }
    for(int i=0 ; i<I ; i++){
        balls.erase(balls.begin());
    }
    return I;
}
int laserBall(vector<topBall> &balls){
    setSoundEffect("laser") ;
    int I=0;
    topBall C;
    string address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\lasereffect.png";
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=balls.back().x-245;
    img_rect.y=-100;
    img_rect.w=img_w * 0.7;
    img_rect.h=img_h;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(100) ;
    for(int i=0 ; i<balls.size() ; i++){
        int t=abs((balls.back().x - balls[i].x));
        if(t<=35){
            balls.erase(balls.begin() + i);
            balls.insert(balls.begin(),C);
            I++;
        }

    }
    for(int i=0 ; i<I ; i++){
        balls.erase(balls.begin());
    }
    return I;
}
bool onlyblack(vector<topBall> &balls){
    for(int i=0 ; i<balls.size() ; i++){
        if(balls[i].mode!=3)
            return false ;
    }
    return true ;
}
int dropBall(vector<topBall> &balls, vector<topBall> &fallBall, int r[400], bool &countTop) {
    int I=0;
    for (int i = 0; i < balls.size() && countTop; i++) {
        if (balls[i].y == balls[highestBall(balls)].y) {
            r[i] = 10;
        }
    }
    countTop= false;
    for (int i = 0; i < balls.size(); i++) {
        if (r[i] != 10) {
            for (int j = 0; j < balls.size(); j++) {
                int t = sqrt((balls[i].x - balls[j].x) * (balls[i].x - balls[j].x) + (balls[i].y - balls[j].y) * (balls[i].y - balls[j].y));
                if (t > 0 && t < 65 && r[j]==10) {
                    r[i]=10;
                    I++;
                    break;
                }
            }
        }
    }
    if(I!=0){
        return dropBall(balls,fallBall,r,countTop);
    }else{
        topBall C;
        int P=0;
        for (int i = 0; i < balls.size() ; i++)
            if(r[i]!=10){
                fallBall.push_back(balls[i]);
                balls.erase(balls.begin() + i);
                balls.insert(balls.begin(),C);
                P++;
            }
        for(int i=0 ; i<P ; i++){
            balls.erase(balls.begin());
        }
        if(P!=0)
            setSoundEffect("falling") ;
        return P;
    }
}
void fallingBall(vector<topBall> &fallBall){
    int dY=7,I=0;
    topBall C;
    for(int i=0 ; i<fallBall.size() ; i++){
        if(fallBall[i].y>=1030){
            fallBall.erase(fallBall.begin() + i);
            fallBall.insert(fallBall.begin(),C);
            I++;
        }else{
            fallBall[i].y+=dY;
            filledCircleRGBA(m_renderer,fallBall[i].x,fallBall[i].y,30,fallBall[i].r,fallBall[i].g,fallBall[i].b,255);
        }
    }
    for(int i=0 ; i<I ; i++)
        fallBall.erase(fallBall.begin());
}
void bombPic(vector<launchBall> launched){
    string address;
    if(launched[0].r==250) {
        int J=rand()%2;
        if(J==0)
            address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\bomb.png";
        else
            address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\bomb.png";
    }
    SDL_Texture * m_img;
    m_img = IMG_LoadTexture(m_renderer,address.c_str());
    int img_w,img_h;
    SDL_Rect img_rect;
    SDL_QueryTexture(m_img,NULL,NULL,&img_w,&img_h);
    img_rect.x=launched[0].x-45;
    img_rect.y=launched[0].y-51;
    img_rect.w=img_w *1.7;
    img_rect.h=img_h *1.7;
    SDL_RenderCopy(m_renderer,m_img,NULL,&img_rect);
    SDL_DestroyTexture(m_img);
}
void laserPic(vector<launchBall> launched){
    string address;
    if(launched[0].r==200) {
        address = "C:\\taha_hdp&mahdi_minaii_project\\texture\\ball\\laser.png";
        SDL_Texture *m_img;
        m_img = IMG_LoadTexture(m_renderer, address.c_str());
        int img_w, img_h;
        SDL_Rect img_rect;
        SDL_QueryTexture(m_img, NULL, NULL, &img_w, &img_h);
        img_rect.x = launched[0].x - 28;
        img_rect.y = launched[0].y - 28;
        img_rect.w = img_w * 1.2;
        img_rect.h = img_h * 1.2;
        SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);
        SDL_DestroyTexture(m_img);
    }
}
//<-------------------------------------- timer ------------------------------------->
void checkTime(bool back){
    newTime = SDL_GetTicks() ;
    if(newTime - startTime >= 1000){
        secound++ ;
        if(secound==60){
            minute++ ;
            secound =0 ;
        }
        startTime = newTime ;
        if(back) {
            int m = 4 - minute, s = 60 - secound;
            TimePrint = "Time : " + to_string(m) + " : " + to_string(s);
        }else
            TimePrint = "Time : " + to_string(minute) + " : " + to_string(secound) ;
    }
    betterText(TimePrint,500,900,255,242,0,255,t-17,SF);
}
//<-------------------------------------- scores ------------------------------------->
int makeScore(int balls){
    int times = minute*60 + secound , scoreTime = (times-deltaTime)*5 , newScore=0 ;
    if(((balls*50) - (scoreTime)) > 0)
        newScore = (balls*50) - (scoreTime) ;
    else
        newScore = (balls*50);
    deltaTime  = times ;
    mainScore+=newScore ;
    changeScore(mainScore) ;
    return newScore ;
}
void printScore(){
    string scorePrint = "score : " + to_string(mainScore) ;
    betterText(scorePrint , 500 , 840 , 255,242,0,255,t-17,SF);
    betterText("[B] Bomb : "+ to_string(bombBallCount) , 85 , 800 , 255,242,0,255,t-25,SF);
    BombBtn->settingDisplay(m_renderer,25,800) ;
    betterText("[S] Slow(7s) : "+ to_string(slowBallCount) , 85 , 850 , 255,242,0,255,t-25,SF);
    SlowBtn->settingDisplay(m_renderer,25,850) ;
    betterText("[L] Laser : "+ to_string(laserBallCount) , 85 , 900 , 255,242,0,255,t-25,SF);
    LaserBtn->settingDisplay(m_renderer,25,900) ;
    betterText("[F] Freeze(5s) : "+ to_string(freezeBallCount) , 85 , 950 , 255,242,0,255,t-25,SF);
    FreezeBtn->settingDisplay(m_renderer,25,950) ;
    betterText("[Space] : switch ball" , 500 , 800 , 255,242,0,255,t-25,SF);
}