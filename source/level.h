void optimizationLevel(){

	for(int i=1; i<CUBES_I-1; i++)
	for(int j=1; j<CUBES_J-1; j++)
	for(int k=1; k<CUBES_K-1; k++)
	{
		if( !cubes[i+1][j][k].deleted && !cubes[i-1][j][k].deleted &&
			!cubes[i][j+1][k].deleted && !cubes[i][j-1][k].deleted &&
			!cubes[i][j][k+1].deleted && !cubes[i][j][k-1].deleted
		)	  cubes[i][j][k].notdraw=true;

	}

	for(int i=0; i<CUBES_I; i++)
	for(int j=0; j<CUBES_J; j++)
	for(int k=0; k<CUBES_K; k++)
	{

		if(i==0 || j==0 || k==0 || i==CUBES_I-1 || j==CUBES_J-1 || k==CUBES_K-1)
			cubes[i][j][k].notdraw=true;

	}



}

void decorateLevel(){

	for(int i=1; i<CUBES_I-1; i++)
	for(int j=1; j<CUBES_J-1; j++)
	for(int k=1; k<CUBES_K-1; k++)
	{
		if( (!cubes[i+1][j][k].deleted && !cubes[i-1][j][k].deleted ||
			!cubes[i][j+1][k].deleted && !cubes[i][j-1][k].deleted  )
			&& 	!cubes[i][j][k+1].deleted && !cubes[i][j][k-1].deleted
		)	  if(mr() > 0.99) cubes[i][j][k].notdraw=true;

	}


}

/*
int summaCubes(int k0, int k1, bool e){
	int count = 0;
	for(int i=0; i<CUBES_I; i++)
	for(int j=0; j<CUBES_J; j++)
	for(int k=k0; k<k1; k++)
	{
		if(cubes[i][j][k].deleted != e)
			count ++;
	}
	return count;
}
 */

bool correctIndex(int i, int j, int k) {
	return (i>=0 && j>=0 && k>=0 && i<CUBES_I && j<CUBES_J && k<CUBES_K);
}
 /*
void generateLevel(int Seed ) {

	//	srand(time(NULL));
	srand(Seed);

	for(int i=0; i<CUBES_I; i++)
	for(int j=0; j<CUBES_J; j++)
	for(int k=0; k<CUBES_K; k++)
	{	cubes[i][j][k].deleted=false;
	 	cubes[i][j][k].notdraw=false;
	 	cubes[i][j][k].setCoord(i*2,j*2,k*2);
	}



	bool bLEFT, bRIGHT,  bFORWARD, bBACK, bUP, bDOWN;

	int di_cut = 0;
	int dj_cut = 0;

	int i_cut=CUBES_I/2, j_cut=CUBES_J/2, k_cut=CUBES_K/2;
	int max_cut = 1000;
	int steps = 0;

	int kk=0;

	int fromRoomToRoom = 16+rand()%16;


	do {
		di_cut = -1+rand()%3;
		dj_cut = -1+rand()%3;

		steps = 3+(int)(mr()*8);


		for(int st=0; st<steps; st++) {

			if(st==2) {
				player1.x = cubes[i_cut][j_cut][k_cut].x;
				player1.y = cubes[i_cut][j_cut][k_cut].y;
				player1.z = cubes[i_cut][j_cut][k_cut].z;
			}

			if(i_cut-di_cut < 0) break;
			if(j_cut-dj_cut < 0) break;
			if(i_cut+di_cut >=CUBES_I-1) break;
			if(j_cut+dj_cut >=CUBES_J-1) break;



			i_cut+=di_cut;
			j_cut+=dj_cut;

			if(correctIndex(i_cut,j_cut,k_cut))	{
				cubes[i_cut][j_cut][k_cut].deleted = true;
				cubes[i_cut][j_cut][k_cut].notdraw=true;
			}

			if(correctIndex(i_cut+1,j_cut,k_cut))
							cubes[i_cut+1][j_cut][k_cut].deleted = true;

		}

		if(--fromRoomToRoom<0)
		{		 fromRoomToRoom = 16+rand()%16;
				int roomHalfSizeX = 2+rand()%8;
				int roomHalfSizeY = 2+rand()%8;
				int roomHalfSizeZ = rand()%8;

				for(int ii=i_cut; ii<=i_cut+roomHalfSizeX; ii++)
				for(int jj=j_cut; jj<=j_cut+roomHalfSizeY; jj++)
				for(int kk=k_cut; kk<=k_cut+roomHalfSizeZ; kk++)
					if(correctIndex(ii,jj,kk)) {
						int rr = rand()%100;
						if(rr<50 || rr>52 )cubes[ii][jj][kk].deleted = true;
					}
		}

		max_cut-=steps;

	}	while(max_cut>0);

    water.z = 0;
 	optimizationLevel();

}
*/
int i_cut=CUBES_I/2, j_cut=CUBES_J/2, k_cut=CUBES_K/2;;
enum Dir { GO_LEFT, GO_RIGHT,  GO_FORWARD, GO_BACK,  GO_UP, GO_DOWN,   DIREND };

void make_doors_and_keys (){

    int levelVolume = 0;
        for(int i=0; i<CUBES_I; i++)
        for(int j=0; j<CUBES_J; j++)
        for(int k=0; k<CUBES_K; k++)
            if(cubes[i][j][k].deleted) levelVolume++;

    for(int a=0; a<3; a++)
    for( int ColorIterator = RED;   ColorIterator < MAXDOORCOLORS;  )
    {

        for(int i=1; i<CUBES_I; i++)
        for(int j=1; j<CUBES_J; j++)
        for(int k=1; k<CUBES_K-1; k++)
        {
            if(cubes[i][j][k].deleted
               && !cubes[i][j][k-1].deleted
               && !cubes[i][j][k+1].deleted
               && rand()%levelVolume == (levelVolume/2)) {

                GameObject door( DOOR);
                door.radius=1.0f;
                door.setPos(i*2,j*2,k*2 );
                door.health=1000;
                door.property[COLOR] = ColorIterator;
                objects.push_back(door);
                ColorIterator++;
                goto M2;
            }

        }
        M2:  int a=1;
    }





    for( int ColorIterator = RED;   ColorIterator < MAXDOORCOLORS;  )
    {

        for(int i=0; i<CUBES_I; i++)
        for(int j=0; j<CUBES_J; j++)
        for(int k=1; k<CUBES_K; k++)
        {
            if(cubes[i][j][k].deleted &&  !cubes[i][j][k-1].deleted && rand()%levelVolume == (levelVolume/2)) {

                GameObject key( KEY);
                key.radius=0.25f;
                key.setPos(i*2,j*2,k*2 );
                key.health=1000;
                key.property[COLOR] = ColorIterator;
                objects.push_back(key);
                ColorIterator++;
                goto M3;
            }

        }
        M3:  int a=1;
    }












}

void make_enemies() {
        for(int i=0; i<CUBES_I; i++)
        for(int j=0; j<CUBES_J; j++)
        for(int k=0; k<CUBES_K; k++)
        {
            if(cubes[i][j][k].deleted  && mr()<0.01) {

                GameObject tur(TURRET);
                tur.radius=.5f;
                tur.setPos(i*2,j*2,k*2);
                tur.health=1000;
                objects.push_back(tur);
            }
        }
}

void make_random_room(int i_cut, int j_cut, int k_cut){

        int roomHalfSizeX = 2+rand()%8;
        int roomHalfSizeY = 2+rand()%8;
        int roomHalfSizeZ = rand()%8;

        for(int ii=i_cut; ii<=i_cut+roomHalfSizeX; ii++)
        for(int jj=j_cut; jj<=j_cut+roomHalfSizeY; jj++)
        for(int kk=k_cut; kk<=k_cut+roomHalfSizeZ; kk++)
            if(correctIndex(ii,jj,kk)) {
                int rr = rand()%100;
                if(rr<50 || rr>55 )cubes[ii][jj][kk].deleted = true;
            }

}


void ProrezKoridor (int length, int dir, int maxWidth) {

        for(int st=0; st<length; st++) {

			switch(dir) {
				case GO_UP:   		if(k_cut+2<CUBES_K  	)  k_cut++; break;
				case GO_DOWN: 	 	if(k_cut>1		 		) k_cut--; break;
				case GO_FORWARD: case GO_BACK: 	if(j_cut+2<CUBES_J	)  j_cut++; break;
			//	case GO_BACK: 		case GO_BACK2: 		if(j_cut>2		 		) j_cut--; break;
				case GO_RIGHT:   	if(i_cut+2<CUBES_I	) i_cut++; break;
				case GO_LEFT: 		  	if(i_cut>2		 		) i_cut--;	break;
			}

            int width = rand()%maxWidth;

            for(int ii=i_cut; ii<=i_cut+width; ii++)
            for(int jj=j_cut; jj<=j_cut+width; jj++)
            for(int kk=k_cut; kk<=k_cut+width; kk++)
            if(correctIndex(ii,jj,kk)) {
                cubes[ii][jj][kk].deleted = true;
            }
        }
}

void make_random_corridor(int i_start,
                          int j_start,
                          int k_start,
                          int startDir,
                          int commonLength) {
	int i_cut=i_start,
        j_cut=j_start,
        k_cut=k_start;
	int max_cut = commonLength;
	int steps = 0;

	int kk=0;
	int dir = startDir;
	do {


		steps = 1+(int)(mr()*7);
	// 	if(dir==UP || dir==DOWN) steps=1;

		for(int st=0; st<steps; st++) {

			switch(dir) {
				case GO_UP:   		if(k_cut+2<CUBES_K  	)  k_cut++; break;
				case GO_DOWN: 	 	if(k_cut>1		 		) k_cut--; break;
				case GO_FORWARD:   	if(j_cut+2<CUBES_J	)  j_cut++; break;
				case GO_BACK: 		 if(j_cut>2		 		) j_cut--; break;
				case GO_RIGHT:   	if(i_cut+2<CUBES_I	) i_cut++; break;
				case GO_LEFT: 	 	if(i_cut>2		 		) i_cut--;	break;
			}

             cubes[i_cut][j_cut][k_cut].deleted = true;

             if(dir==GO_UP || dir==GO_DOWN)
               {
                    cubes[i_cut][j_cut][k_cut].water = true;
                 //   cubes[i_cut][j_cut][k_cut].radius = 0.33f;
                 //   cubes[i_cut][j_cut][k_cut].x=i_cut*2-0.7f;
                 //   cubes[i_cut][j_cut][k_cut].y=j_cut*2-0.7f;
                 //   cubes[i_cut][j_cut][k_cut].z=k_cut*2+0.5f;
               }

		}


		max_cut-=steps;
		dir = rand()%DIREND;

	}	while(max_cut>0);



				int roomHalfSizeX = 2+rand()%8;
				int roomHalfSizeY = 2+rand()%8;
				int roomHalfSizeZ = rand()%8;

				for(int ii=i_cut-roomHalfSizeX; ii<=i_cut+roomHalfSizeX; ii++)
				for(int jj=j_cut-roomHalfSizeY; jj<=j_cut+roomHalfSizeY; jj++)
				for(int kk=k_cut; kk<=k_cut+roomHalfSizeZ; kk++)
					if(correctIndex(ii,jj,kk)) {
						int rr = rand()%100;
						if(rr<50 || rr>55 )cubes[ii][jj][kk].deleted = true;
					}

  //  make_random_room(i_cut,j_cut,k_cut);
}


void generateLevel(int Seed ) {

	//	srand(time(NULL));
	srand(Seed);

	for(int i=0; i<CUBES_I; i++)
	for(int j=0; j<CUBES_J; j++)
	for(int k=0; k<CUBES_K; k++)
	{	cubes[i][j][k].deleted=false;
	 	cubes[i][j][k].notdraw=false;
	 	cubes[i][j][k].researched=false;
	 	cubes[i][j][k].setCoord(i*2,j*2,k*2);
	}
	objects.clear();

	int di_cut = 0;
	int dj_cut = 0;
    i_cut=CUBES_I/2, j_cut=CUBES_J/2, k_cut=CUBES_K/2;;


    player1.x = cubes[i_cut][j_cut][k_cut].x;
    player1.y = cubes[i_cut][j_cut][k_cut].y;
    player1.z = cubes[i_cut][j_cut][k_cut].z;
cubes[i_cut][j_cut][k_cut].deleted = true;

	int max_cut = 100;
	int temp_max_cut = max_cut;
	int steps = 0;
	int kk=0;
	int fromRoomToRoom = 16, door_door = 16;


	do {
		int dir = rand()%DIREND;
		steps = 6+rand()%16;
	 	if(dir==UP || dir==DOWN) steps=rand()%4;

        ProrezKoridor(steps, dir, 4);

		fromRoomToRoom-=steps;
		if(fromRoomToRoom<0)
		{	 fromRoomToRoom =   rand()%(temp_max_cut/4);
             make_random_corridor(i_cut,j_cut,k_cut,rand()%DIREND,100);
		}


		door_door-=steps;
		if(door_door <0) {
            door_door =  rand()%(temp_max_cut/3);
            ProrezKoridor(4, dir, 1);
		}

		max_cut-=steps;

	}	while(max_cut>0);



/*
	int roomsCount =  1+rand()%10;

	for(int rc=0; rc<roomsCount; rc++)
	{

 		int ii = rand()%CUBES_I;
 		int jj = rand()%CUBES_J;
 		int kk = rand()%CUBES_K;

		int roomHalfSize = 1+rand()%8;
		for(int i_cut=ii-roomHalfSize; i_cut<=ii+roomHalfSize; i_cut++)
		for(int j_cut=jj-roomHalfSize; j_cut<=jj+roomHalfSize; j_cut++)
		for(int k_cut=kk-roomHalfSize; k_cut<=kk+roomHalfSize; k_cut++)
			if(correctIndex(i_cut,j_cut,k_cut))
				cubes[i_cut][j_cut][k_cut].deleted = true;



	}
*/


    water.z = 0;



    make_doors_and_keys();
  //  make_enemies();

 	optimizationLevel();
 	decorateLevel();




}

