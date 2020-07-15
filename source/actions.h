void AmmoAction()
{
//	return;



	for(std::vector<GameObject>::iterator I=objects.begin(); I!=objects.end(); ++I)
	{

		if(I->type!=AMMO) continue;

	//	I->update(medium_dt);

	    int opt_i = (int)(I->x*0.5);
	   	int opt_j = (int)(I->y*0.5);
	   	int opt_k = (int)(I->z*0.5);

		float new_x = I->x+I->dx*dt;
		float new_y = I->y+I->dy*dt;
		float new_z = I->z+I->dz*dt;

	   	for(int i=opt_i-1; i<=opt_i+1; i++)
		for(int j=opt_j-1; j<=opt_j+1; j++)
		for(int k=opt_k-1; k<=opt_k+1; k++)
		{


			if( i>=0 && i<CUBES_I && j>=0 && j<CUBES_J&& k>=0 && k<CUBES_K)
			{
				if(cubes[i][j][k].deleted) continue;

				if(cubes[i][j][k].collizion(new_x, I->y, I->z, 0)) { I->invert_dx(dt);   I->health-=13; }
			 	if(cubes[i][j][k].collizion(I->x, new_y, I->z, 0)) { I->invert_dy(dt);   I->health-=13; }
			 	if(cubes[i][j][k].collizion(I->x, I->y, new_z, 0)) { I->invert_dz(dt);   I->health-=13; }
			}
		}


 		for(std::vector<GameObject>::iterator J=objects.begin(); J!=objects.end(); ++J) {
			if(J==I) continue;

			if(I->side!=J->side && collizion(*I,*J)) {
				J->health-=I->health;
				I->health=0;
			}

		}


		if(I->x<-CUBES_I || I->x>CUBES_I*4 ||
			I->y<-CUBES_J || I->y>CUBES_J*4 ||
			I->z<-CUBES_K || I->z>CUBES_K*4
		)
		{
			 I->health=0;
		}
	}

	for(std::vector<GameObject>::iterator I=objects.begin(); I!=objects.end(); ++I) {
		if(I->health<=0)
			 {objects.erase(I); break;}
	}
}


void TurretAction()
{

	for(std::vector<GameObject>::iterator I=objects.begin(); I!=objects.end(); ++I)
	{
		if(I->type!=TURRET) continue;
	//	I->update(medium_dt);

		I->timer += dtms;

		if(I->timer > 2000.0) {
            float tr = rasst(I->x,I->y,I->z,  player1.x, player1.y,player1.z);


            if(tr < 40) {
                I->timer = 0.0;
                GameObject o(AMMO);
                o.setPos(I->x,I->y,I->z);
                o.side = I->side;
                o.isMassive=false;
                o.impulseTo(player1.x, player1.y,player1.z, .3f, medium_dt);
        //		else
        //			 o.impulseTo(player1.x, player1.y,player1.z, 0.1f);

                I->isMassive=false;
                I->impulseTo(player1.x, player1.y,player1.z, .05f, medium_dt);


                objects.push_back(o);
                break;
			 }
		}
	//	I->update(medium_dt);

	    //int opt_i = (int)(I->x*0.5);
	   	//int opt_j = (int)(I->y*0.5);
	   	//int opt_k = (int)(I->z*0.5);


	}
}
