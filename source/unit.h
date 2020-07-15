#ifndef UNIT_H
#define UNIT_H

#include "fvector.h"

class Point3d
{
	public:
 	float x,y,z;
 	Point3d () {}
	Point3d(float x,float y,float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

};

struct vec3f {
    float x, y, z;

};

vec3f normalize(float x, float y, float z)
{

    float inv_length = 1.0f / sqrt(x*x + y*y + z*z);
    vec3f tmpV;
    tmpV.x = x*inv_length;
    tmpV.y = y*inv_length;
    tmpV.z = z*inv_length;

    return tmpV;
}


class Unit
	{
	public:
		float x,y,z;
		float dx,dy,dz;
		float oldx,oldy,oldz;
	    bool inWater;
		bool onHard;

		float radius;
		bool isMassive;
		//FVector FMove;
		bool friction;
		bool spirit;
		float inertion;
		Unit()
		{
			x=0;
			y=0;
			z=0;
			oldx=x;
			oldy=y;
			oldz=z;
			dx=0;
			dy=0;
			dz=0;
			radius = 0;
			isMassive = false;
			friction = true;
			spirit = false;
			inWater = false;
			inertion = 1;


		}


		void setPos(float tx, float ty, float tz )
		{
			oldx = x = tx;
			oldy = y = ty;
			oldz = z = tz;
		}



		void impulse (float dx, float dy, float dz, double medium_dt) {
			if(isMassive) {
			 oldx=x-dx*medium_dt;
			 oldy=y-dy*medium_dt;
			 oldz=z-dz*medium_dt;
			}
			else {
				this->dx = dx;
				this->dy = dy;
				this->dz = dz;
			}
		}

		void impulseTo(float tx, float ty, float tz, float speed , double medium_dt) {
			float k = rasst(x,y,z,tx,ty,tz);

			vec3f tmpV = normalize((tx-x), (ty-y), (tz-z));

			this->impulse (tmpV.x*speed,  tmpV.y*speed, tmpV.z*speed, medium_dt);
		}

		void invert_dx ( double dt) {
			dx=-dx;
			if(isMassive) dx*=0.75;
			move(1);
		}
		void invert_dy ( double dt) {
			dy=-dy;
			if(isMassive) dy*=0.75;
			move(1);
		}
		void invert_dz (double dt ) {
			dz=-dz;
			if(isMassive) dz*=0.75;
			move(1);
		}


 		void update(double medium_dt)
		{

			if(isMassive) {
				float x_next=x+(x-oldx);
				float y_next=y+(y-oldy);
				float z_next=z+(z-oldz);

				z_next-=0.001f*medium_dt;

				dx = (x_next - x);
				dy = (y_next - y);
				dz = (z_next - z);



				move(1);
			}
			else {
				move(medium_dt)	;
			}

		}

		void move(double medium_dt) {

				oldx=x;
				oldy=y;
				oldz=z;
				x+=dx*medium_dt;
				y+=dy*medium_dt;
				z+=dz*medium_dt;
		}
};


bool collizion(Unit u1, Unit u2) {
	return(	   fabs(u1.x - u2.x) < (u1.radius+u2.radius)
		&& fabs(u1.y - u2.y) < (u1.radius+u2.radius)
		&& fabs(u1.z - u2.z) < (u1.radius+u2.radius)
	) ;
}
#endif
