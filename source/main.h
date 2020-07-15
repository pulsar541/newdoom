

enum Type {
    AMMO,
    TURRET,
    DOOR,
    KEY
    };


enum PropertyType {
    FULLNESS,
    COMPLETENESS,
    COLOR ,
    MAXPROPTYPES};

enum DoorColors { RED, GREEN, BLUE, MAXDOORCOLORS};

void VVV(float,float,float,float, int);

int ivn=0;
int it=0;

class Cube {
	    public:
      		float x,y,z;
      		float dx,dy,dz;

      		bool deleted;
      		bool notdraw;
      		bool onfloor;
      		bool water;
      		float radius;
      	//	CubeType cubeType;
      		bool researched;
            Cube(){
				this->deleted=false;
				this->notdraw=false;
				this->researched=false;
				this->water=false;
				dx=dy=dz=0;
				radius=1.0f;
			//	cubeType = SIMPLE;
			}
			//void setCubeType(CubeType ct) {
			//	cubeType = ct;
			//}

            void draw(int side)
            {

			  VVV(x,y,z,radius, side);

			}

			void setCoord(float x, float y, float z) {
				this->x=x;
				this->y=y;
				this->z=z;

			}

			bool contains(float x, float y, float z) {
					if(x > this->x - this->radius - 0.1f &&  x < this->x  + this->radius + 0.1f &&
						y> this->y  - this->radius - 0.1f &&  y < this->y + this->radius + 0.1f &&
						z > this->z  - this->radius - 0.1f &&  z < this->z + this->radius + 1.0f
					 ) return true;
				return false;
			}
			bool collizion(float x, float y, float z , float radius) {
					if(x > this->x - 1.0f-radius &&  x < this->x + 1.0f+radius &&
						y> this->y - 1.0f-radius &&  y < this->y + 1.0f+radius &&
						z > this->z - 1.0f-radius &&  z < this->z + 1.0f+radius
					 ) return true;
				return false;
			}


};

struct NetPacket {
	int nextPacketId;
};

void getDoorColor(int color){
    switch(color) {
        case RED: glColor3f(1,.3,.3); break;
        case GREEN: glColor3f(.3,1,.3); break;
        case BLUE: glColor3f(.3,.3,1); break;
    }
}

class GameObject: public Unit, public NetPacket {
	public:


	int type;
	float speed;
	float health;
	float property[MAXPROPTYPES];

	bool mustDelete;
	int side;
	double timer;

	GameObject() {
		mustDelete = false;
	}
	GameObject(int type) {
		this->type = type;
		this->radius = 0.1f;
		this->speed = 0.5f;
		this->health = 100;
		this->timer = 0;
			mustDelete = false;
	}

	void setDirection(float vx, float vy, float vz) {
	//	impulse(vx*speed, vy*speed, vz*speed );
	}

	void draw() {
	//	if(health > 0)
		//	glDisable(GL_LIGHTING);


			switch(type) {
				case AMMO:
				     glPushMatrix();
				     glTranslatef(x,y,z);
					 glutSolidSphere(radius, 8,8);
					 glPopMatrix();
					break;
				case TURRET:

                       glNormal3f( 0.0f,  1.0f, 0.0f);   // Нормаль вверх
                       glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x-radius,  y, z-radius);
                       glTexCoord2f(0.0f, 1.0f); 	       glVertex3f(x-radius,  y, z+radius); // Низ Лево на текстуре и четырехугольнике
                       glTexCoord2f(1.0f, 1.0f); 	       glVertex3f(x+radius,  y, z+radius); // Низ Право на текстуре и четырехугольнике
                       glTexCoord2f(1.0f, 0.0f); 	       glVertex3f(x+radius,  y, z-radius); // Верх Право на текстуре и четырехугольнике

                       glNormal3f((-1.0f), 0.0f, 0.0f);   // Нормаль направлена влево
                       glTexCoord2f(1.0f, 0.0f); 	       glVertex3f(x, y+(-radius), z+(-radius)); // Низ Лево на текстуре и четырехугольнике
                       glTexCoord2f(1.0f, 1.0f); 	       glVertex3f(x, y+(-radius), z+ radius); // Низ Право на текстуре и четырехугольнике
                       glTexCoord2f(0.0f, 1.0f); 	       glVertex3f(x,  y+radius, z+ radius); // Верх Право на текстуре и четырехугольнике
                       glTexCoord2f(0.0f, 0.0f); 	       glVertex3f(x, y+ radius, z+(-radius)); // Верх Лево на текстуре и четырехугольнике

					break;

				case DOOR:
                    getDoorColor(property[COLOR]);
                    VVV(x,y,z,radius, ALL);
					break;
				case KEY:
                    getDoorColor(property[COLOR]);
                    VVV(x,y,z,radius, ALL);
					break;

			}


	//	if(health > 0)
	//		glEnable(GL_LIGHTING);
	}


};

struct Water {
	float z;
}water;


struct Player: NetPacket {

	float dx,dy,dz;
	float x,y,z;
	double hrot, vrot;
	Player() {  dx=dy=dz = 0;}
};


struct PlayerState: NetPacket{
	int resources;
	int health;
};


GameObject gdata;


