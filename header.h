#include <stdbool.h>
void updateBtns();

char aiDiff;
bool ai;
int delayByDifficulty();
double ballSpeedModifierX(double ballSpeed);


void calculateBallImpact();

double ballSpeedY;
double ballSpeedX;

void mainMenu();
char displayState;//What should be displayed? 0 = mainMenu, 1 = Leaderboard, 2 = Difficulty, 3 = game
void game();
void difficulty();
void leaderBoard();
void gameMode();
void displayGame();

int btnTimeoutCounter;

int getBtn(int btnNumber);
int getbtns(void);
int getsw(void);
int getPlayerBtns(int btnNumber);

int getPlayerPosition(int playerNumber);

void initGame();

void display_image(int x, const uint8_t *data, int width, int sectionStart, int sectionEnd);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char *itoaconv(int num);
void labwork(void);
int nextprime(int inval);
void quicksleep(int cyc);
void tick(unsigned int *timep);

void display_debug(volatile int *const addr);

/* Declare bitmap array containing font */
extern const uint8_t const font[128 * 8];
/* Declare bitmap array containing icon */
extern uint8_t icon[128 * 4];
extern const uint8_t const goal[128 * 3];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

void delay(int);
void time2string(char *, int);
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
void enable_interrupt(void);
void enablePixel(int x, int y);
int myPow(int base, int exp);

void user_isr(void);
void timer2(void);
void clearIcon();

bool isTicked;
double playerHeight;

void displayPlayer(int playerNumber, int posY);

void updatePlayerPos(double offset, int playerNumber);

void displayBall(int posX, int posY);

int getBallPositionX();
int getBallSize();
int getBallPositionY();
bool getServeDelay();
void setServeDelay(bool b);
void startGame();
void tickGame();




char* itoa(int num, char* str, int base);
void reverse(char str[], int length);
int getBase10Expo(int num);