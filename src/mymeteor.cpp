#include "mymeteor.h"

#include <iostream>
#include <math.h>
const GLfloat Meteor::COLORS[][3] =                 //ûʲô�õġ����ʺ����ɫ
{
	 {1.0f, 0.5f, 0.5f}, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f },
	 {0.75f, 1.0f, 0.5f}, { 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f },
	 {0.5f, 1.0f, 1.0f}, { 0.5f, 0.75f, 1.0f }, { 0.5f, 0.5f, 1.0f },
	 {0.75f, 0.5f, 1.0f}, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};


Meteor::Meteor(QWidget* widget)
	: widget(widget) {
	m_Rainbow = false;
	m_Color = 0;
	m_Slowdown = 2.0f;
	m_xSpeed = 0.0f;
	m_ySpeed = 0.0f;
	m_Deep = -40.0f;

	screen_width = widget->width();
	screen_height = widget->height();

	float row1 = rand() % screen_width + (rand() % 100) * 0.01;
	float col1 = rand() % screen_height + (rand() % 100) * 0.01;

	float row2 = rand() % screen_width + (rand() % 100) * 0.01;
	float col2 = rand() % screen_height + (rand() % 100) * 0.01;

	float rand_y = rand() % 500 * 0.1;


	for (int i = 0; i < MAX_PARTICLES; i++)                 //ѭ����ʼ����������
	{
		m_Particles[i].active = true;						//ʹ��������Ϊ����״̬
		m_Particles[i].life = 1.0f;							//������������ֵΪ���
		//�������˥������
		m_Particles[i].fade = float(rand() % 1000) / 1000.0f + 0.001;

		//���ӵ���ɫ������ɫ
		m_Particles[i].r = 1.0f;
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;

		//���ӵĳ�ʼλ�á�������

		if (i < MAX_PARTICLES / 10) {
			m_Particles[i].x = row1;
			m_Particles[i].y = col1;
			m_Particles[i].z = -5.0f;

			//�������x��y��z�᷽���ٶ�
			m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
			m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		}
		else if (i < MAX_PARTICLES / 10 * 2) {
			m_Particles[i].x = row2;
			m_Particles[i].y = col2;
			m_Particles[i].z = 5.0f;

			//�������x��y��z�᷽���ٶ�
			m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
			m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		}
		else {
			m_Particles[i].fade = float(rand() % 1000) / 1000.0f + 0.001;
			m_Particles[i].x = 5 + rand() % 10 -5;
			m_Particles[i].y = rand_y + rand() % 10 + 10;
			m_Particles[i].z = 0.0f;

			m_Particles[i].xi = fabs(float((rand() % 50) - 26.0f) * 10.0f);
			m_Particles[i].yi = -fabs(float((rand() % 50) - 25.0f) * 10.0f);
		}


		m_Particles[i].xg = 2.0f;                       //����x������ٶ�Ϊ2.0
		m_Particles[i].yg = -0.8f;                      //����y������ٶ�Ϊ-0.8
		m_Particles[i].zg = 0.0f;                       //����z������ٶ�Ϊ0
	}
}

void Meteor::initMeteor() {
	glEnable(GL_TEXTURE_2D);                            //��������ӳ��
	glShadeModel(GL_SMOOTH);                            //������Ӱƽ��
	glClearDepth(1.0);                                  //������Ȼ���
	glDisable(GL_DEPTH_TEST);                           //��ֹ��Ȳ���
	glEnable(GL_BLEND);                                 //�����ں�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//�����ں�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //����ϵͳ��͸�ӽ�������
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void Meteor::drawMeteor() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����Ļ����Ȼ���
	glLoadIdentity();                                   //����ģ�͹۲����


	for (int i = 0; i < 1000; i++)                 //1000�����ӵ�һ��һ��������
	{
		if (m_Particles[i].active)                      //�������Ϊ�����
		{
			float x = m_Particles[i].x;                 //x��λ��
			float y = m_Particles[i].y;                 //y��λ��
			float z = m_Particles[i].z + m_Deep;        //z��λ��
			//����������ɫ
			glColor4f(m_Particles[i].r, m_Particles[i].g,
				m_Particles[i].b, m_Particles[i].life);
			glBegin(GL_TRIANGLE_STRIP);                 //���������δ�
			glTexCoord2d(1, 1);
			glVertex3f(x + 0.5f, y + 0.5f, z);
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);
			glEnd();

			//���¸��������꼰�ٶ�
			m_Particles[i].x += m_Particles[i].xi / (m_Slowdown * 1000);
			m_Particles[i].y += m_Particles[i].yi / (m_Slowdown * 1000);
			m_Particles[i].z += m_Particles[i].zi / (m_Slowdown * 1000);
			m_Particles[i].xi += m_Particles[i].xg;
			m_Particles[i].yi += m_Particles[i].yg;
			m_Particles[i].zi += m_Particles[i].zg;

			m_Particles[i].life -= m_Particles[i].fade; //�������ӵ�����ֵ
			
			if (m_Particles[i].life < 0.0f)             //�����������ֵС��0
			{
				m_Particles[i].life = 1.0f;             //����һ��������
				m_Particles[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

				m_Particles[i].r = 1.0f;  //������ɫ
				m_Particles[i].g = 1.0f;
				m_Particles[i].b = 1.0f;

				float row = rand() % screen_width + (rand() % 100) * 0.01;
				float col = rand() % screen_height + (rand() % 100) * 0.01;

				m_Particles[i].x = row;                //�����������
				m_Particles[i].y = col;
				m_Particles[i].z = 0.0f;

				//������������ٶ�
				m_Particles[i].xi = m_xSpeed + float((rand() % 60) - 32.0f);
				m_Particles[i].yi = m_ySpeed + float((rand() % 60) - 30.0f);
				m_Particles[i].zi = float((rand() % 60) - 30.0f);
			}
		}
	}
	if (m_Rainbow)                                      //���Ϊ�ʺ�ģʽ
	{
		m_Color++;                                      //������ɫ�ı任
		if (m_Color > 11)
		{
			m_Color = 0;
		}
	}
}

void Meteor::meteor_run() {

	float speed_x = fabs(float((rand() % 50) - 26.0f) * 10.0f + 5);;
	float speed_y = -fabs(float((rand() % 50) - 25.0f) * 10.0f + 5);
	

	float pos_x = -10;	//�ڻ������
	float pos_y = rand() % 50 + 50;		//�����y����

	int num_meteor = MAX_PARTICLES * 2 / 3;
	for (int i = 0; i < MAX_PARTICLES; i++){
	

		if (i < num_meteor / 10) {
			m_Particles[i].x = pos_x;
			m_Particles[i].y = pos_y;
			m_Particles[i].z = 0;

			
		}
		else if (i < num_meteor / 10 * 2) {
			m_Particles[i].x = pos_x - 1;
			m_Particles[i].y = pos_y + 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
			m_Particles[i].z = 0.0f;



		}
		else if (i < num_meteor / 10 * 3) {
			m_Particles[i].x = pos_x ;
			m_Particles[i].y = pos_y + 2;
			m_Particles[i].z = 0.0f;



		}
		else if (i < num_meteor / 10 * 4) {
			m_Particles[i].x = pos_x - 2  ;
			m_Particles[i].y = pos_y ;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 5) {
			m_Particles[i].x = pos_x - 2;
			m_Particles[i].y = pos_y + 2;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 6) {
			m_Particles[i].x = pos_x - 3;
			m_Particles[i].y = pos_y + 3;
			m_Particles[i].z = 0.0f;

		}
		else if (i < num_meteor / 10 * 7) {
			m_Particles[i].x = pos_x - 4;
			m_Particles[i].y = pos_y + 4;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 8) {
			m_Particles[i].x = pos_x - 5;
			m_Particles[i].y = pos_y + 5;
			m_Particles[i].z = 0.0f;


		}
		else if (i < num_meteor / 10 * 9) {
			m_Particles[i].x = pos_x - 1;
			m_Particles[i].y = pos_y + 3;
			m_Particles[i].z = 0.0f;

		}
		else if (i < num_meteor) {
			m_Particles[i].x = pos_x - rand()%5;
			m_Particles[i].y = pos_y + rand()%5;
			m_Particles[i].z = 0.0f;

		}
		else {
			float row = rand() % screen_width + (rand() % 100) * 0.01;
			float col = rand() % screen_height + (rand() % 100) * 0.01;

			m_Particles[i].x = row;                //�����������
			m_Particles[i].y = col;
			m_Particles[i].z = 0.0f;
		}

		m_Particles[i].xi = speed_x * 2 + fabs(rand() % 100 - 50);
		m_Particles[i].yi = speed_y * 2 + fabs(rand() % 100 - 50);
		m_Particles[i].zi = 0;

		m_Particles[i].xg = 35.0f;                       //����x������ٶ�Ϊ2.0
		m_Particles[i].yg = -30.5f;                      //����y������ٶ�Ϊ-0.8
		m_Particles[i].zg = 0.0f;

		m_Particles[i].r = 1.0f;  //������ɫ
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;
		                   

	}
}


void Meteor::explode() {					//����������ը��Ч��

	float row1 = rand() % 100 + (rand() % 100) * 0.01;
	float col1 = rand() % 100 + (rand() % 100) * 0.01;

	float row2 = rand() % 100 + (rand() % 100) * 0.01;
	float col2 = rand() % 100 + (rand() % 100) * 0.01;

	int num_explode = 500;

	for (int i = 0; i < num_explode; i++)
	{
		m_Particles[i].fade = fabs(rand() % 50 - 25) * 0.01;

		if (i < num_explode / 2) {
			m_Particles[i].x = row1;
			m_Particles[i].y = col1;
			m_Particles[i].z = 0;
			
		}
		else {
			m_Particles[i].x = row2;
			m_Particles[i].y = col2;
			m_Particles[i].z = 0.0f;

		}


		//��������ٶ�
		m_Particles[i].xi = float((rand() % 50) - 26.0f) * 10.0f;
		m_Particles[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		m_Particles[i].zi = float((rand() % 50) - 25.0f) * 10.0f;

		m_Particles[i].xg = 0.0f;                       //����x������ٶ�Ϊ2.0
		m_Particles[i].yg = -0.8f;                      //����y������ٶ�Ϊ-0.8
		m_Particles[i].zg = 0.0f;                       //����z������ٶ�Ϊ0

		//�������ӵ���ɫ

		m_Particles[i].r = 1.0f;
		m_Particles[i].g = 1.0f;
		m_Particles[i].b = 1.0f;

		
	}
}

void Meteor::change_rainbow() {
	m_Rainbow = !m_Rainbow;
}

void Meteor::change_color() {

		m_Rainbow = false;
		m_Color++;
		if (m_Color > 11)
		{
			m_Color = 0;
		}
}