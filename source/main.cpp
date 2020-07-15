#define _WCHAR_T_DEFINED
#include <GL/glut.h>
#include <stdlib.h>
#include <Math.h>
#include <stdlib.h>
#include <GL/glaux.h>
#include <time.h>
#include "Network.h"
#include <vector>
#include "lib.h"
#include "fvector.h"
#include "defines.h"
#include "level.h"


#define DEBUG_MAP  1

#define ENABLE_GRAVITY		 1
#define ENABLE_COLLISION	 1
#define ENABLE_FOG			 1
#define ENABLE_OPTIMIZATION	 1

#define NORMAL_THIRD_VIEW  1

 double ww,hh;


void reshape(int w, int h)
{    ww=w;
hh=h;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	float z=200;
	//if(viewMode==FIRST)  z = 50.0f;

	gluPerspective(FOV, (double)w/(double)h, 0.05, z);
	glMatrixMode(GL_MODELVIEW);
}


void ExtractFrustum()
{
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Узнаем текущую матрицу PROJECTION */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Узнаем текущую матрицу MODELVIEW */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Комбинируем матрицы(перемножаем) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Находим A, B, C, D для ПРАВОЙ плоскости */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Приводим уравнение плоскости к нормальному виду */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Находим A, B, C, D для ЛЕВОЙ плоскости */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Приводим уравнение плоскости к нормальному виду */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Находим A, B, C, D для НИЖНЕЙ плоскости */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Приводим уравнение плоскости к нормальному */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* ВЕРХНЯЯ плоскость */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Нормальный вид */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* ЗАДНЯЯ плоскость */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Нормальный вид */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* ПЕРЕДНЯЯ плоскость */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Нормальный вид */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
}


bool CubeInFrustum( float x, float y, float z, float size )
{
   int p;

   for( p = 0; p < 6; p++ )
   {
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      return false;
   }
   return true;
}

#include "draw.h"

void keyboard(unsigned char key, int x, int y)
{
	 if(whoTurn==connType || connType==SINGLE) {
		if(key=='w' || key=='W' || key=='ц' || key=='Ц') move_forward = true;
		if(key=='s' || key=='S' || key=='ы' || key=='Ы') move_back = true;
		if(key=='a' || key=='A' || key=='ф' || key=='Ф') move_left = true;
		if(key=='d' || key=='D' || key=='в' || key=='В') move_right = true;
		if(key==' ')
		{	if(onfloor )
			  player1.dz=0.30f;

		}
	}
/*
	if(key=='g') {
		float tmpx = player1.x;
		float tmpy = player1.y;
		float tmpz = player1.z;
		generateLevel();


		player1.x =  tmpx;
		player1.y = tmpy;
		player1.z = tmpz;
	}
	*/
	if(key == 'c' || key=='C' || key == 'с' || key=='С') {
		if(viewMode == FIRST) viewMode = THIRD;
		else viewMode = FIRST;

	}

	if(key == 9) {
		  if(viewMode != MAP)
		   { viewMode = MAP;	glDisable(GL_FOG); }
		  else
		   { viewMode = FIRST;  		glEnable(GL_FOG); }
	}


	if(key=='f' || key=='а'  ) {
		fonar =!fonar;

		if(fonar) {
				glEnable(GL_LIGHT1);
			//	glEnable(GL_LIGHT2);
		}
		else {
				glDisable(GL_LIGHT1);
			//	glDisable(GL_LIGHT2);
			}
	}
	/*
	if(key =='m') {
		go_is_born = 1;
		go_x = player1.x;
		go_y = player1.y;
		go_z = player1.z-0.2f;
		go_r = 0.1f;
		go_type = (float)AMMO;
		go_dir_x = tmpX;
		go_dir_y = tmpY;
		go_dir_z = tmpZ;

		GameObject tobj(player1.x,player1.y,player1.z-0.2f,0.1f,AMMO);
		tobj.setDirection(tmpX, tmpY, tmpZ);
		objects.push_back(tobj);
	}	*/
	/*
	if(key=='g') {
			density = 0.03f+mr() * 0.1f;
		   fogColor[0] = 1.0 - mr()*0.5f;
		   fogColor[1] = 1.0 - mr()*0.5f;
		   fogColor[2] = 1.0 - mr()*0.5f;
	}*/
}

void keyboardUp(unsigned char key, int x, int y)
{
	if(whoTurn==connType || connType==SINGLE) {


            if(key=='w' || key=='W' || key=='ц' || key=='Ц')move_forward = false;
            if(key=='s' || key=='S' || key=='ы' || key=='Ы') move_back = false;
            if(key=='a' || key=='A' || key=='ф' || key=='Ф')move_left = false;
            if(key=='d' || key=='D' || key=='в' || key=='В')move_right = false;

	}

	switch (key) {


	case 27:
		if (!uninitialize())
			printf("error: %s\n", getString(NETWORK_ERROR));

		exit(0);
		break;
	};
}

void special(int key, int x, int y)
{

		switch (key) {
		case GLUT_KEY_F1:
				if(connType==SINGLE) {
						generateLevel(time(NULL));
				}
			break;
		};

}


void motion(int x, int y)
{

}

double mx, my;

void passive(int x, int y)
{
	mx=x;
	my=y;

	double w = (double)glutGet(GLUT_WINDOW_WIDTH);
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT);

	player1.hrot -= (w/2.0f-mx)*0.2f *dt;


	player1.vrot += (h/2.0f-my)*0.2f *dt;


	if(player1.vrot<-89) player1.vrot=-89;
	if(player1.vrot>88) player1.vrot=88;

	if(player1.hrot>=360.0f) player1.hrot-=360.0f;
	if(player1.hrot<0) player1.hrot+=360.0f;


}

void mouse(int button, int state, int x, int y)
{
//	if (button == GLUT_RIGHT_BUTTON) {
//	}
	if ((button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON) && state==GLUT_DOWN) {

		if(whoTurn==connType || connType==SINGLE) {

			GameObject o(AMMO);
		 	o.setPos(player1.x,player1.y,player1.z-0.2f);
		 	o.side = connType;
		 	o.isMassive = true;
			o.impulse(tmpX*0.1+player1.dx*0.33, tmpY*0.1+player1.dy*0.33, tmpZ*0.1+0.03 +player1.dz*0.33, 1 );
			objects.push_back(o);

			g_packetId = 1;
			gdata = o;

	//		whoTurn = 3-connType;
	//		game_changeTurn = 1;


		}



	}
}

#include "netsend.h"
#include "netlisten.h"



void init(void)
{

	if(ENABLE_FOG)
		glEnable(GL_FOG);                       // Включает туман (GL_FOG)
	glFogi(GL_FOG_MODE, fogMode[1]);	// Выбираем тип тумана
	glFogfv(GL_FOG_COLOR, fogColor);    // Устанавливаем цвет тумана
	glFogf(GL_FOG_DENSITY, density);     // Насколько густым будет туман
	glHint(GL_FOG_HINT, GL_NICEST );    // Вспомогательная установка тумана
//		glFogf(GL_FOG_START, 3.0f);     // Глубина, с которой начинается туман
//		glFogf(GL_FOG_END, 2.0f);       // Глубина, где туман заканчивается.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//	glLighti(GL_LIGHT0, GL_LINEAR_ATTENUATION, 2);

//	float amb[4]={20,20,20,1};

//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);
//	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128);
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0f);
///	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 128);

	float spotDiff[4] = {1,1,1,1};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiff);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.09);
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDiff);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	LoadGLTextures();			// Загрузка текстур
	glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
	glEnable(GL_CULL_FACE);

	generateLists();

	int levelSeed=0;
	if (connType == SINGLE || connType == SERVER) {
		levelSeed = time(NULL);

	}



	////////////////////////////////////////////////////////////////
	myState.resources = 100;
	oppState.resources = 100;


	player1.hrot = 0;
	player1.vrot = 90;



	if ( connType == SERVER) {
		int sbuf[1];
		sbuf[0] = levelSeed;

		sendTo((const char*)sbuf, sizeof(sbuf));
	}
	else if(connType == CLIENT) {
		int rbuf[1];
		if (receive((char*)&rbuf[0], sizeof(rbuf))) {
			levelSeed = rbuf[0];
		}
	}

	generateLevel(levelSeed);


//	NetSend(0,&player1);

 /////////

 for(int i=0; i<101; i++)
 for(int j=0; j<101; j++)
 {
 	w[i][j].lavang = rand_FloatRange(0.0f, 2*3.1415926f);

 }
 ////////

	density = 0.03f+mr() * 0.03f;
	   fogColor[0] = 1.0 - mr()*0.5f;
	   fogColor[1] = 1.0 - mr()*0.5f;
	   fogColor[2] = 1.0 - mr()*0.5f;

}

int oldtime;

static int ttt1=0;
static int ttt2=0;
static float k1=1;
static float k2=1;


/*

bool getNearCubeIndex(float x, float y, float z, float* m) {
	float i,j,k;
	...


	m[0] = i;
	m[1] = j;
	m[2] = k;
}
*/

/*
float min3(float a, float b, float c) {
	float minAB = min(a,b);
	return min(minAB,c);
}
*/


void Collizions(Unit *u){


	float new_x = u->x+u->dx;
	float new_y = u->y+u->dy;
	float new_z = u->z+u->dz;


    int opt_i = (int)(u->x*0.5);
   	int opt_j = (int)(u->y*0.5);
   	int opt_k = (int)(u->z*0.5);


 	if(ENABLE_COLLISION)
 	{
	   	for(int i=opt_i-1; i<=opt_i+1; i++)
		for(int j=opt_j-1; j<=opt_j+1; j++)
		for(int k=opt_k-1; k<=opt_k+1; k++)
		{
			if(!correctIndex(i,j,k))  continue;

			if(cubes[i][j][k].deleted) continue;

		 	if(cubes[i][j][k].collizion(new_x, u->y, u->z,u->radius)) u->dx=0;
		 	if(cubes[i][j][k].collizion(u->x, new_y, u->z,u->radius)) u->dy=0;
		 	if(cubes[i][j][k].collizion(u->x, u->y, new_z,u->radius)) u->dz=0;


		}




	}

}

void idle()
{
	//printf("%f\n",mr());
	whoTurn = connType; ////////////////////////////////////////////



 /*
	for(int i=0; i<101; i++)
	for(int j=0; j<101; j++)
	{
		if((w[i][j].lavang+=0.02*dt) > 2*M_PI) w[i][j].lavang-=2*M_PI;
		w[i][j].z = 0.1f*cos(w[i][j].lavang)+ water.z;
		w[i][j].x = (i*2-100+(float)CUBES_I)+0.1*cos(w[i][j].lavang);
		w[i][j].y = (j*2-100+(float)CUBES_J)+0.2*sin(w[i][j].lavang);
	}

 	*/
 	if(connType!=SINGLE) {
		NetSend();
		NetListen();
	}

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
  	glutWarpPointer(w/2, h/2);





	medium_dt = (dt + olddt)*0.5f;

	AmmoAction();



    for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
         if((*i).type==TURRET) Collizions(&(*i) );
    }


	TurretAction();

    for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
         (*i).update(medium_dt);
    }


//	if(player.x<5)
//		de


	double elapsed = (double)glutGet(GLUT_ELAPSED_TIME) ;
	glutPostRedisplay();


	dtms  =  elapsed - t0 ;
	t0 += dtms;


	olddt = dt;
	dt = dtms * 0.05f;





   //	Sleep(10);
}




void timer(int value)
{

    if(value == 0) {

              float speed;
                 tmpX = (float)sin(player1.hrot*piOver180);
                 tmpY = (float)cos(player1.hrot*piOver180);

                 float tmpXY = sqrt(tmpX*tmpX + tmpY*tmpY);
                 tmpZ = tmpXY * tanf(player1.vrot*piOver180);

                float tmpRasst = sqrt(tmpX*tmpX + tmpY*tmpY + tmpZ*tmpZ);


                tmpX/=tmpRasst;
                tmpY/=tmpRasst;
                tmpZ/=tmpRasst;

                  //  speed = 0.03f;

                  /*
                    if(onfloor )
                    { 	speed = 0.05f;
                        player1.dx*=0.7f;
                        player1.dy*=0.7f;

                        if (move_forward && move_left
                            || move_forward && move_right
                            || move_back && move_left
                            || move_back && move_right
                            )	{
                                    player1.dx/=0.7f;
                                    player1.dy/=0.7f;
                                    player1.dx/=sqrt(2);
                                    player1.dy/=sqrt(2);
                                }

                    }
                    else if( inwater) {
                        speed = 0.006f;
                        player1.dx*=0.9f;
                        player1.dy*=0.9f;
                        player1.dz*=0.9f;
                    }
                    else {
                        //speed = 0.01f;
                        player1.dx*=0.99f;
                        player1.dy*=0.99f;
                    }

                    */
                     if(onfloor || inwater)
                    {
                        player1.dx*=0.7f;
                        player1.dy*=0.7f;
                    }

                    if( onfloor)
                    {    speed = 0.05f;

                    }

                    if( inwater)
                    {    speed = 0.005f;
                    }

                 if(onfloor || inwater) {
                    if (move_forward) {
                        player1.dx += tmpX * speed;
                        player1.dy += tmpY * speed;
                        if(!onfloor) player1.dz += tmpZ * speed;

                    }
                    if (move_back) {
                        player1.dx += -tmpX * speed;
                        player1.dy += -tmpY * speed;
                        if(!onfloor) player1.dz += -tmpZ * speed;

                    }
                    if (move_left) {
                        player1.dx -= tmpY * speed;
                        player1.dy += tmpX * speed;

                    }
                    if (move_right) {
                        player1.dx += tmpY * speed;
                        player1.dy -= tmpX * speed;

                    }

                 }


                    if (move_forward || move_back || move_left || move_right)
                        myDistanse+=5*speed;


                if(ENABLE_GRAVITY) {
                    if(!inwater )
                        player1.dz-=0.015f;
                }


                float new_x = player1.x+player1.dx;
                float new_y = player1.y+player1.dy;
                float new_z = player1.z+player1.dz;

                onfloor=false;
                inwater=false;

                int opt_i = (int)(player1.x*0.5);
                int opt_j = (int)(player1.y*0.5);
                int opt_k = (int)(player1.z*0.5);


                if(ENABLE_COLLISION)
                {
                    for(int i=opt_i-1; i<=opt_i+1; i++)
                    for(int j=opt_j-1; j<=opt_j+1; j++)
                    for(int k=opt_k-1; k<=opt_k+1; k++)
                    {
                        if(!correctIndex(i,j,k))  continue;

                        if(cubes[i][j][k].deleted) continue;

                        if(cubes[i][j][k].contains(new_x, player1.y, player1.z)) player1.dx=0;
                        if(cubes[i][j][k].contains(player1.x, new_y, player1.z)) player1.dy=0;
                        if(cubes[i][j][k].contains(player1.x, player1.y, new_z)) {player1.dz=0;
                            if(new_z<player1.z) {
                                    onfloor=true;
                                    player1.z=cubes[i][j][k].z+2.0f;
                                    player1.dz= 0;

                            }
                         }

                    }

                    inwater = false;
                    for(int i=opt_i-1; i<=opt_i+1; i++)
                    for(int j=opt_j-1; j<=opt_j+1; j++)
                    for(int k=opt_k-1; k<=opt_k+1; k++)
                    {
                        if(!correctIndex(i,j,k))  continue;

                        if(!cubes[i][j][k].water) continue;

                        if(cubes[i][j][k].contains(player1.x, player1.y, player1.z )) inwater = true;



                    }

                }





                for(int i=opt_i-2; i<=opt_i+2; i++)
                for(int j=opt_j-2; j<=opt_j+2; j++)
                for(int k=opt_k-2; k<=opt_k+2; k++)
                {

                    if(!correctIndex(i,j,k))  continue;
                    if(!cubes[i][j][k].deleted) continue;
                //  	if(cubes[i][j][k].notdraw) continue;

                    cubes[i][j][k].researched = true;
                }


                player1.x+=player1.dx;
                player1.y+=player1.dy;
                player1.z+=player1.dz;


                if(player1.z<0) {
                    player1.z=0; onfloor=true;

                  }

        glutTimerFunc(17, timer, 0);
    }
}

int main(int argc, char** argv)
{

//  printf ("Single Player - 0\nClient - 1\nServer - 2\n");
//  scanf("%d",&connType);



	if (!initialize())
	printf("error: %s\n", getString(NETWORK_ERROR));

	if (connType == SERVER) {
		printf("Waiting connections...\n");
		if (!host())
			printf("error: %s\n", getString(NETWORK_ERROR));

	}
	else if (connType == CLIENT) {
		printf ("Server IP: ");
		char serverAddr[256];
		scanf("%s",serverAddr);

		if (connect(serverAddr))
			printf("Connection with %s succesfully established\n\n", serverAddr);
		else
			printf("connect error: %s\n", getString(NETWORK_ERROR));


	}

  glutInit(&argc,argv);
  glutInitWindowPosition(connType==SERVER?801:0, 100 );
  glutInitWindowSize(1280, 720 );

  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Demo");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutKeyboardUpFunc(keyboardUp);
	glutFullScreen();

	glutTimerFunc(17, timer, 0);



dt=0;
  init();
    glutIdleFunc(idle);
	dt=0;
   oldtime = glutGet(GLUT_ELAPSED_TIME);

  glutSetCursor(GLUT_CURSOR_NONE);
  glutMainLoop();
  //glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
}
