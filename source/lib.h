
#define piOver180 M_PI / 180

float rand_FloatRange(float a, float b)
{
return ((b-a)*((float)rand()/RAND_MAX))+a;
}

float mr() {
	return rand_FloatRange(0.0f, 1.0f);	
}

float rasst(
	float x1,	float y1,	float z1, 
	float x2,	float y2,	float z2) {
		return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}


