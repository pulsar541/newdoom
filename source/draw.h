
void VVV(float x, float y, float z, float radius , int side) {


	if(side == RIGHT || side == ALL) {
	       glNormal3f( 1.0f, 0.0f, 0.0f);   // Нормаль направлена вправо
           glTexCoord2f(0.0f, 0.0f);			glVertex3f(x+ radius, (-radius)+y, (-radius)+z); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(1, 0.0f);	       glVertex3f(x+ radius,  radius+y, (-radius)+z); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(1, 1);	       glVertex3f(x+ radius,  radius+y,  radius+z); // Верх Лево на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1); 	       glVertex3f(x+ radius, y+(-radius),  radius+z); // Низ Лево на текстуре и четырехугольнике
	}
	if(side == LEFT || side == ALL) {
	       // Левая грань
	       glNormal3f((-1), 0.0f, 0.0f);   // Нормаль направлена влево
	       glTexCoord2f(1, 1); 	       glVertex3f(x+(-radius), y+(-radius), z+(-radius)); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1, 0.0f); 	       glVertex3f(x+(-radius), y+(-radius), z+ radius); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x+(-radius),  y+radius, z+ radius); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1); 	       glVertex3f(x+(-radius), y+ radius, z+(-radius)); // Верх Лево на текстуре и четырехугольнике
	}
	if(side == FORWARD || side == ALL) {
	        //Передняя грань
	       glNormal3f( 0.0f,  1, 0.0f);   // Нормаль вверх
	       glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x+(-radius),  y+ radius, z+(-radius));
	       glTexCoord2f(0.0f, 1); 	       glVertex3f(x+(-radius),  y+radius,  z+radius); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1, 1); 	       glVertex3f(x+ radius,  y+radius,  z+radius); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(1, 0.0f); 	       glVertex3f(x+ radius,  y+radius, z+(-radius)); // Верх Право на текстуре и четырехугольнике
	}
	if(side == BACK || side == ALL) {
	       // Задняя грань
	       glNormal3f( 0.0f,(-1), 0.0f);
	       glTexCoord2f(1, 0.0f); 	       glVertex3f(x+(-radius), y+(-radius), z+(-radius)); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x+ radius, y+(-radius), z+(-radius)); // Верх Лево на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1); 	       glVertex3f(x+ radius, y+(-radius),  z+radius); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1, 1); 	       glVertex3f(x+(-radius), y+(-radius), z+ radius); // Низ Право на текстуре и четырехугольнике
	}
	if(side == DOWN || side == ALL) {
      		//Нижняя грань
	       glNormal3f( 0.0f, 0.0f, (-1));   // Нормаль вперед
		   glTexCoord2f(0.0f, 1); 	       glVertex3f(x+(-radius),  y+radius,  z+(-radius)); // Верх Лево на текстуре и четырехугольнике
		   glTexCoord2f(1, 1); 	       glVertex3f(x+ radius,  y+radius,  z+(-radius)); // Верх Право на текстуре и четырехугольнике
		   glTexCoord2f(1, 0.0f); 	       glVertex3f(x+ radius, y+(-radius),  z+(-radius)); // Низ Право на текстуре и четырехугольнике
		   glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x+(-radius), y+(-radius),  z+(-radius)); // Низ Лево на текстуре и четырехугольнике
	}
	if(side == UP || side == ALL) {
	       // Верхняя грань
	       glNormal3f( 0.0f, 0.0f, 1);   // Обратная нормаль
		   glTexCoord2f(0.0f, 0.0f);  glVertex3f(x+ radius, y+(-radius), z+radius); // Низ Лево на текстуре и четырехугольнике
		   glTexCoord2f(0.0f, 1);  glVertex3f(x+ radius,  y+radius, z+radius); // Верх Лево на текстуре и четырехугольнике
		   glTexCoord2f(1, 1);   glVertex3f(x+(-radius),  y+radius, z+radius); // Верх Право на текстуре и четырехугольнике
		   glTexCoord2f(1, 0.0f);     glVertex3f(x+(-radius), y+(-radius), z+radius); // Низ Право на текстуре и четырехугольнике
	}

}


void display( void )
{

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();




  	glEnable(GL_TEXTURE_2D);
  	glEnable(GL_LIGHTING);


	float addEpsLook;

	if(myDistanse>M_PI) myDistanse-=(M_PI);
	addEpsLook =  sin(myDistanse)*0.1;

	if(!onfloor)
		addEpsLook  = 0;

	if(viewMode == FIRST)	{
		camera.x = player1.x;
		camera.y = player1.y;
		camera.z = player1.z+ addEpsLook;
		camera.tx = player1.x+ tmpX ;
		camera.ty = player1.y+ tmpY;
		camera.tz = player1.z+ tmpZ+ addEpsLook;


	}

	else {
		int far_tview ;
 		if(NORMAL_THIRD_VIEW) far_tview = 2;
 		else far_tview = 100;

 		if(viewMode== MAP) far_tview = 70;
		camera.x =	player1.x - tmpX*far_tview ;
		camera.y =	player1.y - tmpY*far_tview;
		camera.z =	player1.z - tmpZ*far_tview;

		camera.tx = player1.x + tmpX ;
		camera.ty = player1.y + tmpY;
		camera.tz = player1.z + tmpZ ;
	}

		gluLookAt(
			camera.x ,
			camera.y ,
			camera.z ,

			camera.tx ,
			camera.ty ,
			camera.tz ,

			0, 0, 1);



	float solx = CUBES_I+60.0f * cos(solangle);
	float soly = CUBES_J+60.0f * sin(solangle);
	float solz = soly-CUBES_J-5;

	float myLightPos1[4] = {player1.x, player1.y, player1.z, 1};



	float litPos[4] = {solx, soly, solz, 0.0};

	glLightfv(GL_LIGHT0, GL_POSITION, litPos);
 	glLightfv(GL_LIGHT1, GL_POSITION, myLightPos1);
 //	glLightfv(GL_LIGHT0, GL_POSITION, myLightPos1);

//	float spotDirection[3] = {tmpX, tmpY, tmpZ};
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection );


 	/*
 	glFogf(GL_FOG_DENSITY, 0.025f);
 	//sol
	glPushMatrix();
		glDisable(GL_LIGHTING);
		//glDisable(GL_FOG);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,0.5+sin(solangle),sin(solangle));
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(solx, soly, solz);
		glutSolidSphere(3,32,32);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		//glEnable(GL_FOG);
	glPopMatrix();
	*/


	glFogf(GL_FOG_DENSITY,density);




////////////////////////////////////////////////////////////
	solangle+=0.0001*dt;
	if(solangle>2*M_PI) solangle-=2*M_PI;

   	float tmpFogColor[4] = {
	   fogColor[0]*(sin(solangle)+0.3f),
	   fogColor[1]*(sin(solangle)+0.3f),
	   fogColor[2]*(sin(solangle)+0.3f), 1};

	glClearColor(tmpFogColor[0], tmpFogColor[1], tmpFogColor[2] , 1);

	glFogfv(GL_FOG_COLOR, tmpFogColor);

	float diff[4]={sin(solangle)*1.5f,sin(solangle)*1.5f,sin(solangle)*1.5f,1};
	if(diff[0]>1) diff[0]=diff[1]=diff[2]=1;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

	float amb[4]={0.2f+sin(solangle)*0.8f,0.2f+sin(solangle)*0.8f,0.2f+sin(solangle)*0.8f,1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	//////////////////////////////////////////////////////////////

	glFogi(GL_FOG_MODE, fogMode[1]);
/*
	if(inwater) 	 {

		 float tmpFogColor2[4] = { 0, .5, .4 , 1};
		glFogf(GL_FOG_DENSITY, 0.08);
		 	glFogfv(GL_FOG_COLOR, tmpFogColor2);
		 	glFogi(GL_FOG_MODE, fogMode[0]);
			 glClearColor(tmpFogColor2[0], tmpFogColor2[1], tmpFogColor2[2] , 1);
	}
*/




	int opt_i = (int)(player1.x*0.5);
   	int opt_j = (int)(player1.y*0.5);
   	int opt_k = (int)(player1.z*0.5);



	glPushMatrix();

	//  РИСУЕМ ВСЕ КУБЫ СТАРЫМ СПОСОБОМ

		ExtractFrustum();

				glDisable(GL_LIGHTING);
                glBindTexture(GL_TEXTURE_2D, texture[DOOR_TEX]);
                glBegin(GL_QUADS);
                for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
                    if((*i).type==DOOR)  (*i).draw();
                }
                glEnd();

                glBindTexture(GL_TEXTURE_2D, texture[KEY_TEX]);
                glBegin(GL_QUADS);
                for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
                    if((*i).type==KEY)  (*i).draw();
                }
                glEnd();


			 	glEnable(GL_LIGHTING);



		glCullFace(GL_BACK);

	 	glDisable(GL_CULL_FACE);

		if(viewMode == THIRD)	glEnable(GL_CULL_FACE);
		if(viewMode== MAP) {
			//	glDisable(GL_LIGHTING);
//				glBindTexture(GL_TEXTURE_2D, texture[GRASS]);
				glDisable(GL_FOG);
				glBegin(GL_QUADS);
				glEnable(GL_BLEND);
				glEnable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);
		 		glCullFace(GL_FRONT);
                glEnable(GL_TEXTURE_2D);
				glColor4f(0,0,0,0.5);
				for(int i=0; i<CUBES_I; i++)
				for(int j=0; j<CUBES_J; j++)
				for(int k=0; k<CUBES_K; k++)
				{
					if(!correctIndex(i,j,k))  continue;
					if(!DEBUG_MAP) if(!cubes[i][j][k].researched) continue;
					if(!cubes[i][j][k].deleted) continue;
				 	cubes[i][j][k].draw(ALL);
				}

				glEnd();


		}
		else {
            glEnable(GL_FOG);


                glDisable(GL_LIGHTING);
//                glBindTexture(GL_TEXTURE_2D, texture[SMILE]);
                glPushMatrix();
                glBegin(GL_QUADS);
                for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
                    if((*i).type==TURRET)  (*i).draw();
                }
                glEnd();
                glPopMatrix();
                glEnable(GL_LIGHTING);

    ///////////////
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
            glEnable(GL_TEXTURE_GEN_S);
        //    glEnable(GL_TEXTURE_GEN_T);
            glDisable(GL_LIGHTING);
//             glBindTexture(GL_TEXTURE_2D, texture[LAVA]);
                for(std::vector<GameObject>::iterator i=objects.begin(); i!=objects.end(); ++i) {
                    if((*i).type==AMMO)  (*i).draw();
                }
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glEnable(GL_LIGHTING);
///////////////

			glBindTexture(GL_TEXTURE_2D, texture[WALL]);
			glBegin(GL_QUADS);




			for(int i=opt_i-25; i<=opt_i+25; i++)
			for(int j=opt_j-25; j<=opt_j+25; j++)
			for(int k=opt_k-25; k<=opt_k+25; k++)
			{

				if(!correctIndex(i,j,k))  continue;
				if(cubes[i][j][k].deleted) continue;
			  	if(cubes[i][j][k].notdraw) continue;
			  	if( !CubeInFrustum( cubes[i][j][k].x, cubes[i][j][k].y, cubes[i][j][k].z, 2 )) continue;

				if(correctIndex(i+1,j,k) && cubes[i+1][j][k].deleted) 	cubes[i][j][k].draw(RIGHT);
			 	if(correctIndex(i-1,j,k) && cubes[i-1][j][k].deleted) 	cubes[i][j][k].draw(LEFT);
			 	if(correctIndex(i,j+1,k) && cubes[i][j+1][k].deleted) 	cubes[i][j][k].draw(FORWARD);
			 	if(correctIndex(i,j-1,k) && cubes[i][j-1][k].deleted) 	cubes[i][j][k].draw(BACK);

			}

			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture[FLOOR]);
			glBegin(GL_QUADS);
				for(int i=opt_i-25; i<=opt_i+25; i++)
				for(int j=opt_j-25; j<=opt_j+25; j++)
				for(int k=opt_k-25; k<=opt_k+25; k++)
			   {
			 		if(!correctIndex(i,j,k))  continue;
					if(cubes[i][j][k].deleted) continue;
				  	if(cubes[i][j][k].notdraw) continue;
				  	if( !CubeInFrustum( cubes[i][j][k].x, cubes[i][j][k].y, cubes[i][j][k].z, 2 )) continue;
				 	if(correctIndex(i,j,k+1) && cubes[i][j][k+1].deleted)	cubes[i][j][k].draw(UP);
				 	if(correctIndex(i,j,k-1) && cubes[i][j][k-1].deleted)	cubes[i][j][k].draw(DOWN);
			   }
			glEnd();

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthFunc(GL_LEQUAL);
            glDisable(GL_FOG);
            glDisable(GL_CULL_FACE);
            glCullFace(GL_BACK);
			glBindTexture(GL_TEXTURE_2D, texture[WATER]);
			glBegin(GL_QUADS);
				for(int i=opt_i-25; i<=opt_i+25; i++)
				for(int j=opt_j-25; j<=opt_j+25; j++)
				for(int k=opt_k-25; k<=opt_k+25; k++)
			   {
			 		if(!correctIndex(i,j,k))  continue;
				  	if(!cubes[i][j][k].water) continue;
				  	if(!CubeInFrustum( cubes[i][j][k].x, cubes[i][j][k].y, cubes[i][j][k].z, 2 )) continue;
                    cubes[i][j][k].draw(ALL);


			   }
			glEnd();
		  glEnable(GL_CULL_FACE);
			glEnable(GL_FOG);
            glDisable(GL_BLEND);
        //    glDisable(GL_CULL_FACE);

		}




		 glEnable(GL_CULL_FACE);

	glPopMatrix();

			glEnable(GL_LIGHTING);

		//	glColor3f(1,1,1);



	if(connType != SINGLE) {
		glPushMatrix();
				glTranslatef(player2.x,player2.y,player2.z-0.7);
			 	glRotatef(-player2.hrot, 0, 0, 1);
			   	glScalef(0.2,0.2,0.7);
			 	glutSolidCube(1.0f);
		glPopMatrix();

		glPushMatrix();
				glTranslatef(player2.x,player2.y,player2.z-0.2);
				glRotatef(-player2.hrot, 0, 0, 1);
				glRotatef(player2.vrot, 1, 0, 0);
				glTranslatef(0,0,0.2);
				glScalef(0.1,0.1,0.1);
			 	glCallList(box+1);
		glPopMatrix();
	}


	if(viewMode != FIRST) {
		glDisable(GL_DEPTH_TEST);
		glPushMatrix();
				glTranslatef(player1.x,player1.y,player1.z-0.7);
			 	glRotatef(-player1.hrot, 0, 0, 1);
			   	glScalef(0.2,0.2,0.7);
			 	glutSolidCube(1.0f);
		glPopMatrix();

		glPushMatrix();
				glTranslatef(player1.x,player1.y,player1.z-0.2);
				glRotatef(-player1.hrot, 0, 0, 1);
				glRotatef(player1.vrot, 1, 0, 0);
				glTranslatef(0,0,0.2);
				glScalef(0.1,0.1,0.1);
			 	glCallList(box+1);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

//////////////////////////////////////////
/*	glDisable(GL_LIGHTING);
				 glBindTexture(GL_TEXTURE_2D, texture[PLITKA]);
		   glColor4f(1,.5,0,1);
		glPushMatrix();
			 glBegin(GL_QUADS);
		     	glTexCoord2f(0, 0); 	glVertex3f(-1000,1000,-1);
			 	glTexCoord2f(0, 600); 	glVertex3f(-1000,-1000,-1);
			 	glTexCoord2f(600, 600); 	glVertex3f(1000,-1000,-1);
			 	glTexCoord2f(600, 0); 	glVertex3f(1000,1000,-1);

			 glEnd();
		glPopMatrix();



	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glPushMatrix();

		   glBindTexture(GL_TEXTURE_2D, texture[WATER]);
		   glColor4f(1,1,1,0.8);
	       glBegin(GL_QUADS);               // Начинаем рисовать четырехугольники

      		glNormal3f( 0.0f, 0.0f, -1.0f);   // Обратная нормаль
      		for(int i=0; i<100; i++)
			for(int j=0; j<100; j++)
			{
		       // Верхняя грань

		       float tx0, tx1, ty0, ty1;

		       if((j%2)==0)	 {tx0 = 0.0f; tx1 = 0.5f;}
		       else		{tx0 = 0.5f; tx1 = 1.0f;}

		       if((i%2)==0)	 {ty0 = 0.0f; ty1 = 0.5f;}
		       else		{ty0 = 0.5f; ty1 = 1.0f;}

			   glTexCoord2f(tx0, ty0);
		       glVertex3f( w[i][j].x, w[i][j].y, w[i][j].z); // Низ Лево на текстуре и четырехугольнике

			   glTexCoord2f(tx0, ty1);
		       glVertex3f( w[i+1][j].x,  w[i+1][j].y, w[i+1][j].z); // Верх Лево на текстуре и четырехугольнике

			   glTexCoord2f(tx1, ty1);
			   glVertex3f(w[i+1][j+1].x,  w[i+1][j+1].y, w[i+1][j+1].z); // Верх Право на текстуре и четырехугольнике

			   glTexCoord2f(tx1, ty0);
			   glVertex3f(w[i][j+1].x,  w[i][j+1].y, w[i][j+1].z); // Низ Право на текстуре и четырехугольнике

			}

	       glEnd();                         // Заканчиваем рисование четырехуголь


 	glPopMatrix();
	glEnable(GL_CULL_FACE);

	glDisable(GL_BLEND);
	*/





  	glFlush();
	glutSwapBuffers();
}
