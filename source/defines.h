
#include "unit.h"


#define SINGLE 0
#define CLIENT 1
#define SERVER 2

const float FOV = 55.0f;

int g_packetId = 0;
enum ViewMode{ FIRST, THIRD,  MAP};

int connType = SINGLE;
int viewMode = FIRST;

float frustum[6][4];

GLuint 	box;
enum Side  {LEFT, RIGHT,  FORWARD, BACK, UP, DOWN, ALL};


#include <stdio.h>
#include "main.h"
#include "loadtexture.h"
#include "genlists.h"


bool fonar=false;

float density =   0.05f;



const int CUBES_I = 150;
const int CUBES_J = 150;
const int CUBES_K = 50;

float solangle = M_PI/2;

float game_changeTurn = 0;
float whoTurn = SERVER;
int maxStepsTurn = 3;


#define NVERTS 4


struct Wave{
	float x,y,z;
	float lavang;
}
w[201][201];


double dt=0;
double medium_dt=0;
double olddt = 0;
double iters = 2;




std::vector<GameObject> objects;

float litPos[4] = {-3, -3, -3, 1.0};

float lx=0,ly=0,lz=0;

bool move_forward=false;
bool move_back=false;
bool move_left=false;
bool move_right=false;



float myDistanse=0;

Player player1, player2;
PlayerState myState, oppState;


bool onfloor=false;
bool inwater=false;

float tmpX=0, tmpY=0, tmpZ=0;

Cube cubes[CUBES_I][CUBES_J][CUBES_K];


double t0 = 0.0;
double dtms = 0.0;

#include "actions.h"

float 	go_is_born = 0,
		go_type,
		go_x,
		go_y,
		go_z,
   	 	go_r,
   	    go_dir_x,
		go_dir_y,
		go_dir_z;


GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR }; // ’ранит три типа тумана
GLuint fogfilter= 0;                    // “ип используемого тумана
//GLfloat fogColor[4]= {0.8f, 0.9f, 1, 1}; // ÷вет тумана


// GLfloat fogColor[4]= {0, 0, 0.05f, 1}; // ÷вет тумана
//GLfloat fogColor[4]= {1.0f, 0.8f, 0.5f, 1}; // ÷вет тумана
GLfloat fogColor[4]= {0.65f, 0.7f, 1.0f, 1}; // ÷вет тумана

class Camera: public Point3d{
	public:
		float tx,ty,tz;
} camera;
