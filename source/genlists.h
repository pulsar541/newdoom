
void generateLists() {
	box = glGenLists(3);
	glNewList(box,GL_COMPILE);

	//      VVV();

	glEndList();


//////////////////////////////////////////////////////////////////////////////////////////


	glNewList(box+1,GL_COMPILE);



		   glBegin(GL_QUADS);
      //������ �����
	       glNormal3f( 0.0f, 0.0f, -1.0f);   // ������� ������

		   glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f,  -1.0f); // ���� ���� �� �������� � ����������������

		   glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f,  -1.0f); // ���� ����� �� �������� � ����������������
		   glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  -1.0f); // ��� ����� �� �������� � ����������������
		   glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  -1.0f); // ��� ���� �� �������� � ����������������


	       glEnd();

		//   	glBindTexture(GL_TEXTURE_2D, texture[1]);



		   glBegin(GL_QUADS);
	       // ������� �����
	       glNormal3f( 0.0f, 0.0f, 1.0f);   // �������� �������


		   glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f, 1.0f); // ��� ���� �� �������� � ����������������

		   glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, 1.0f); // ���� ���� �� �������� � ����������������


		   glTexCoord2f(1.0f, 1.0f);
		   glVertex3f(-1.0f,  1.0f, 1.0f); // ���� ����� �� �������� � ����������������

		   glTexCoord2f(1.0f, 0.0f);
		   glVertex3f(-1.0f, -1.0f, 1.0f); // ��� ����� �� �������� � ����������������


	       glEnd();                         // ����������� ��������� ������������

	       glBegin(GL_QUADS);               // �������� �������� ����������������


	       // ������ �����
	       glNormal3f( 1.0f, 0.0f, 0.0f);   // ������� ���������� ������
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f, -1.0f); // ��� ����� �� �������� � ����������������
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, -1.0f); // ���� ����� �� �������� � ����������������
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f,  1.0f); // ���� ���� �� �������� � ����������������
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  1.0f); // ��� ���� �� �������� � ����������������

	       // ����� �����
	       glNormal3f(-1.0f, 0.0f, 0.0f);   // ������� ���������� �����
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f, -1.0f); // ��� ���� �� �������� � ����������������
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  1.0f); // ��� ����� �� �������� � ����������������
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f,  1.0f); // ���� ����� �� �������� � ����������������
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f, -1.0f); // ���� ���� �� �������� � ����������������

	     	glEnd();

//		glBindTexture(GL_TEXTURE_2D, texture[SMILE]);

		   glBegin(GL_QUADS);


	        //�������� �����
	       glNormal3f( 0.0f,  1.0f, 0.0f);   // ������� �����
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f(-1.0f,  1.0f, -1.0f); // ���� ���� �� �������� � ����������������
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f(-1.0f,  1.0f,  1.0f); // ��� ���� �� �������� � ����������������
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f( 1.0f,  1.0f,  1.0f); // ��� ����� �� �������� � ����������������
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f( 1.0f,  1.0f, -1.0f); // ���� ����� �� �������� � ����������������

	       // ������ �����
	       glNormal3f( 0.0f,-1.0f, 0.0f);   // ������� ���������� ����
	       glTexCoord2f(1.0f, 1.0f);
	       glVertex3f(-1.0f, -1.0f, -1.0f); // ���� ����� �� �������� � ����������������
	       glTexCoord2f(0.0f, 1.0f);
	       glVertex3f( 1.0f, -1.0f, -1.0f); // ���� ���� �� �������� � ����������������
	       glTexCoord2f(0.0f, 0.0f);
	       glVertex3f( 1.0f, -1.0f,  1.0f); // ��� ���� �� �������� � ����������������
	       glTexCoord2f(1.0f, 0.0f);
	       glVertex3f(-1.0f, -1.0f,  1.0f); // ��� ����� �� �������� � ����������������


		   	glEnd();


	glEndList();
















	}
