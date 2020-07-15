
void generateLists() {
	box = glGenLists(3);
	glNewList(box,GL_COMPILE);

	//      VVV();

	glEndList();


//////////////////////////////////////////////////////////////////////////////////////////


	glNewList(box+1,GL_COMPILE);



		   glBegin(GL_QUADS);
      //Нижняя грань
	       glNormal3f( 0.0f, 0.0f, -1.0f);   // Нормаль вперед

		   glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f,  -1.0f); // Верх Лево на текстуре и четырехугольнике

		   glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f,  -1.0f); // Верх Право на текстуре и четырехугольнике
		   glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  -1.0f); // Низ Право на текстуре и четырехугольнике
		   glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  -1.0f); // Низ Лево на текстуре и четырехугольнике


	       glEnd();

		//   	glBindTexture(GL_TEXTURE_2D, texture[1]);



		   glBegin(GL_QUADS);
	       // Верхняя грань
	       glNormal3f( 0.0f, 0.0f, 1.0f);   // Обратная нормаль


		   glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f, 1.0f); // Низ Лево на текстуре и четырехугольнике

		   glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, 1.0f); // Верх Лево на текстуре и четырехугольнике


		   glTexCoord2f(1.0f, 1.0f);
		   glVertex3f(-1.0f,  1.0f, 1.0f); // Верх Право на текстуре и четырехугольнике

		   glTexCoord2f(1.0f, 0.0f);
		   glVertex3f(-1.0f, -1.0f, 1.0f); // Низ Право на текстуре и четырехугольнике


	       glEnd();                         // Заканчиваем рисование четырехуголь

	       glBegin(GL_QUADS);               // Начинаем рисовать четырехугольники


	       // Правая грань
	       glNormal3f( 1.0f, 0.0f, 0.0f);   // Нормаль направлена вправо
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f, -1.0f); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, -1.0f); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f,  1.0f); // Верх Лево на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  1.0f); // Низ Лево на текстуре и четырехугольнике

	       // Левая грань
	       glNormal3f(-1.0f, 0.0f, 0.0f);   // Нормаль направлена влево
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f, -1.0f); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  1.0f); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f,  1.0f); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f, -1.0f); // Верх Лево на текстуре и четырехугольнике

	     	glEnd();

//		glBindTexture(GL_TEXTURE_2D, texture[SMILE]);

		   glBegin(GL_QUADS);


	        //Передняя грань
	       glNormal3f( 0.0f,  1.0f, 0.0f);   // Нормаль вверх
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f, -1.0f); // Верх Лево на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f,  1.0f,  1.0f); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f,  1.0f,  1.0f); // Низ Право на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, -1.0f); // Верх Право на текстуре и четырехугольнике

	       // Задняя грань
	       glNormal3f( 0.0f,-1.0f, 0.0f);   // Нормаль направлена вниз
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f(-1.0f, -1.0f, -1.0f); // Верх Право на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f, -1.0f, -1.0f); // Верх Лево на текстуре и четырехугольнике
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  1.0f); // Низ Лево на текстуре и четырехугольнике
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  1.0f); // Низ Право на текстуре и четырехугольнике


		   	glEnd();


	glEndList();
















	}
