#ifndef F_VECTOR_H
#define F_VECTOR_H

#define SLOMO_K 1.0f

	/// <summary>
	/// Summary description for FVector.
	/// </summary>
	class FVector
	{
		
		public: float x0,y0,z0,  // откуда смотрит вектор
					 x1,y1,z1;  // куда смотрит вектор

		public: float r;
		public: float R;
		  float gravity;
	 
		FVector()
		{
 				gravity = 0.05f;
		}
		void calc_kas(float oldx,    
					  float oldy,   
					  float oldz,
					  float x,    
					  float y,    
					  float z,
					  double dt)  
		{ 

			x0=x;
			y0=y;
			z0=z;
			 
			x1=x+(x-oldx)*dt;
			y1=y+(y-oldy)*dt;
			z1=z+(z-oldz)*dt;
		}
		
		void  add_gravity(double dt)
		{
			z1-=gravity*dt;
		}

		void  add_antigravity()
		{
			z1+=gravity;
		}
/*
		void  calc_in_water( double dt)
		{	
			z1+= dt*(gravity + gravity*0.4);
		} */
		/*
		void  calc_veter(float massa, float xa,float ya )
		{
			x1+=gravity/SLOMO_K;
		}
*/
/*
		void addImpulse(float impx, float impy, float impz)
		{
			this->x1 += impx; 
			this->y1 += impy;
			this->z1 += impz;			
		} */

	};


	void ResultofAddVect(FVector *FRES,FVector A,FVector  B)
	{

		FRES->x0=A.x0;
		FRES->y0=A.y0;
		FRES->z0=A.z0;		
 		FRES->x1=A.x1+B.x1-FRES->x0;
		FRES->y1=A.y1+B.y1-FRES->y0;
		FRES->z1=A.z1+B.z1-FRES->z0;		
	}


#endif
