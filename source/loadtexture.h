// Загрузка картинки и конвертирование в текстуру

enum ETex {
    //SMILE,
//STONES,
WALL,
//LAVA,
FLOOR,
//GRASS ,
DOOR_TEX,
 WATER,
  KEY_TEX,
  MAXTEX};
GLuint	texture[MAXTEX];

GLvoid LoadGLTextures()
{
	int max_anisotropy;
	glGetIntegerv(0x84FE, &max_anisotropy);
	glGenTextures(MAXTEX, texture);

	AUX_RGBImageRec *texture_aux[MAXTEX];

//	texture_aux[SMILE] = auxDIBImageLoad("img/smile.bmp");
//	texture_aux[STONES] = auxDIBImageLoad("img/stones.bmp");
//	texture_aux[LAVA] = auxDIBImageLoad("img/lava.bmp");
	texture_aux[FLOOR] = auxDIBImageLoad("img/floor.bmp");
	texture_aux[WALL] = auxDIBImageLoad("img/wall.bmp");
//	texture_aux[GRASS] = auxDIBImageLoad("img/grass.bmp");
	texture_aux[WATER] = auxDIBImageLoad("img/water.bmp");
	texture_aux[DOOR_TEX] = auxDIBImageLoad("img/door.bmp");
	texture_aux[KEY_TEX] = auxDIBImageLoad("img/key.bmp");

	for(int i=0; i<MAXTEX; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, 0x84FE, max_anisotropy);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
			texture_aux[i]->sizeX,
			texture_aux[i]->sizeY,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			texture_aux[i]->data);
	}
}
