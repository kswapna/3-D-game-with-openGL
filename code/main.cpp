#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include<unistd.h>
#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;
#define M_PI 3.14159265358979323846
#define BASE_HEIGHT 2 
#define BASE_RADIUS .5
#define HEAD_RADIUS .75/2
#define HAND_HEIGHT (2)/2
#define LEG_HEIGHT (2+0.4)/2
#define HANDLEG_RADIUS .25/2 
#define pi 3.14159265
GLUquadricObj *p;
GLfloat ambient[3];
GLfloat diffuse[3];
GLfloat specular[3];
GLfloat shiness[] = {50.0f};
float angles[5]={0,60,-60,30,-30};
float xx=10;
float pox=-9,poy=0,poz=-9,ppox,ppoy,ppoz;
//float pox=-9,poy=0,poz=0;
int lcount=0;
int rnd[12],brnd[30];
float tx=25,ty=45,zz=-35;
float vv=0,ht0=0,ht1=1,ht2=2,ht3=3,ht4=4;
int kf=-1,pf=-1,tt=0,oo=0,jump=0,inc=0,incht0=0,incht1=1,incht2=0,incht3=1,incht4=0;
int cnt=0,cntr=0;
int jmpcnt=0,counttt=0,count=0;
int fallflag=0;
float ydec;
int mtiles=30;
int staticb=6;
int blockrnd[6];
int upup[6];
int side[6];
int third=0,fff=0;
int flagp=0,flagw1=0,flagw2=0;
float xi,yi,xf,yf;
int chkhover=0,flag41=0;
float inix=0,iniy=0,iniz=0,prx,pry,prz;
int drag=0;
float camx=0,camy=10,camz=20;
int camtile=0;
float tilex=-9,tiley=1,tilez=9;
int wicht[30];
int onlyhover=0;
int periodic=0;


float light_pos[4],spotDir[3];

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
void drawtrunk(){
	/*ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 0.0;
	  diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 0.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glRotatef(-90,1,0,0);
	gluQuadricDrawStyle(p, GLU_FILL);
	glColor3f(0.73,0.16,0.96); 
	//glColor3f(1,1,1);
	//glcolor3f(0,0,0);
	gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);

}
void drawhead(){
	/*ambient[0] = 1.0; ambient[1] = 0.0; ambient[2] = 1.0;
	  diffuse[0] = 1.0; diffuse[1] = 0.0; diffuse[2] = 1.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glTranslatef(0,0,HEAD_RADIUS);
	glColor3f(0.0,0.3,0.6);
	gluSphere(p,HEAD_RADIUS,20,20);
	glPushMatrix();
	glTranslatef(0,0,4*HEAD_RADIUS/5);
	glColor3f(1,1,0);
	gluCylinder (p, HEAD_RADIUS,HEAD_RADIUS/4,0.25,20, 20);
	glTranslatef(0,0,HEAD_RADIUS/5);
	gluSphere(p,0.25,20,20);
	glPopMatrix();


	glPushMatrix();//for nose

	glTranslatef(0,-(HEAD_RADIUS),0);
	glRotatef(90,1,0,0);
	glColor3f(0,1,1);
	gluCylinder (p, 0.1,0, 0.2, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.85,0.85,0.1);
	glTranslatef(HEAD_RADIUS/2,-HEAD_RADIUS/2,HEAD_RADIUS/2-0.1);
	gluSphere(p,0.12,20,20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.85,0.85,0.1);
	glTranslatef(-HEAD_RADIUS/2,-HEAD_RADIUS/2,HEAD_RADIUS/2-0.1);
	gluSphere(p,0.12,20,20);
	glPopMatrix();

}
void drawrightarm(){
	/*ambient[0] = 0; ambient[1] = 1; ambient[2] = 0;
	  diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glTranslatef(-BASE_RADIUS-HANDLEG_RADIUS,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[1],1,0,0);
	glColor3f(0.0, 1.0, 0.0);                                  /*color*/
	gluSphere(p,HANDLEG_RADIUS,20,20);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
	glTranslatef(0,0,HAND_HEIGHT);
	glColor3f(0,0,1);
	gluSphere(p,HANDLEG_RADIUS+0.05,20,20);

}
void drawleftarm(){
	/*ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
	  diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glTranslatef(BASE_RADIUS+HANDLEG_RADIUS,0,0);
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(180,1,0,0);
	glRotatef(angles[2],1,0,0);
	gluSphere(p,HANDLEG_RADIUS,20,20);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
	glTranslatef(0,0,HAND_HEIGHT);
	glColor3f(0,0,1);
	gluSphere(p,HANDLEG_RADIUS+0.05,20,20);

}
void drawrightleg(){
	/*ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
	  diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glTranslatef(BASE_RADIUS/2,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[3],1,0,0);
	glColor3f(0,1,0);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
	glTranslatef(0,0,LEG_HEIGHT);
	glRotatef(-90,1,0,0);
	glColor3f(0,0,1);
	gluCylinder (p,0.1, 0.1, 0.3, 20, 20);
	glTranslatef(0,0,0.3);
	gluSphere(p,0.1,20,20);


}
void drawleftleg(){
	/*ambient[0] = 0.0; ambient[1] = 1.0; ambient[2] = 0.0;
	  diffuse[0] = 0.0; diffuse[1] = 1.0; diffuse[2] = 0.0;
	  specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;
	  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	  glMaterialfv(GL_FRONT, GL_SHININESS, shiness);*/
	glTranslatef(-BASE_RADIUS/2,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[4],1,0,0);
	glColor3f(0,1,0);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
	glTranslatef(0,0,LEG_HEIGHT);
	glRotatef(-90,1,0,0);
	glColor3f(0,0,1);
	gluCylinder (p,0.1, 0.1, 0.3, 20, 20);
	glTranslatef(0,0,0.3);
	gluSphere(p,0.1,20,20);

}
void cuboid(float hh){
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0,1,0);
	glColor3f(0.5,0.0,0.2);
	//glColor3f(0.2,0.1,0.8);

	glVertex3f(1 ,hh,-1);
	glVertex3f(1 ,hh,1 );

	glVertex3f(1 ,hh ,1);
	glVertex3f( 1,-1,1 );

	glVertex3f(1,-1,1 );
	glVertex3f(1,-1,-1);

	glVertex3f(1,-1,-1);
	glVertex3f(1,hh ,-1 );

	glVertex3f( -1,hh,-1 );
	glVertex3f( -1,hh,1);

	glVertex3f( -1,hh,1 );
	glVertex3f(-1,-1,1  );

	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,-1  );

	glVertex3f(-1,-1,-1  );
	glVertex3f(-1,hh ,-1  );

	glVertex3f(-1,-1,-1  );
	glVertex3f( 1,-1,-1 );

	glVertex3f(-1,-1,1 );
	glVertex3f( 1,-1,1 );

	glVertex3f(-1,hh,1  );
	glVertex3f(1,hh,1  );

	glVertex3f(-1,hh,-1  );
	glVertex3f(1,hh,-1  );
	glEnd(); 
	if(cnt%2==0){
		glColor3f(1,0.2,0);
	}
	else{
		glColor3f(0.556863,0.137255,0.137255);						
	}
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);        // Draw The Cube Using quads

	glVertex3f( 1.0f, hh,-1.0f);    // Top Right Of The Quad (Top)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, hh,-1.0f);    // Top Left Of The Quad (Top)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, hh, 1.0f);    // Bottom Left Of The Quad (Top)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 1.0f, hh, 1.0f);    // Bottom Right Of The Quad (Top)
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( 1.0f, hh, 1.0f);    // Top Right Of The Quad (Front)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, hh, 1.0f);    // Top Left Of The Quad (Front)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, hh,-1.0f);    // Bottom Left Of The Quad (Back)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 1.0f, hh,-1.0f);    // Bottom Right Of The Quad (Back)
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f(-1.0f, hh, 1.0f);    // Top Right Of The Quad (Left)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, hh,-1.0f);    // Top Left Of The Quad (Left)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( 1.0f, hh,-1.0f);    // Top Right Of The Quad (Right)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( 1.0f, hh, 1.0f);    // Top Left Of The Quad (Right)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
	glTexCoord2f(0.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
}
int findcounter(int px,int pz){
	int xb,zb;
	if(px>0){
		xb=px/2+1;
	}
	if(px<0){
		xb=px/2-1;
	}
	if(pz>0){
		zb=pz/2+1;
	}
	if(pz<0){
		zb=pz/2-1;
	}
	int sum=0;
	if(zb==-5)sum+=0;
	if(zb==-4)sum+=10;
	if(zb==-3)sum+=20;
	if(zb==-2)sum+=30;
	if(zb==-1)sum+=40;
	if(zb==1)sum+=50;
	if(zb==2)sum+=60;
	if(zb==3)sum+=70;
	if(zb==4)sum+=80;
	if(zb==5)sum+=90;
	if(xb==-5)sum+=0;
	if(xb==-4)sum+=1;
	if(xb==-3)sum+=2;
	if(xb==-2)sum+=3;
	if(xb==-1)sum+=4;
	if(xb==1)sum+=5;
	if(xb==2)sum+=6;
	if(xb==3)sum+=7;
	if(xb==4)sum+=8;
	if(xb==5)sum+=9;
	//printf("%d\n",sum);
	return sum;
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(4,2,2);/*tick*/ 
	int fflag=0;
	if(oo==1){
		glTranslatef(0,0,zz);/*tick*/
		glRotatef(tx, 1.0, 0.0, 0.0 );/*tick*/
		glRotatef(ty, 0.0, 1.0, 0.0 );/*tick*/
	}
	if(fff==1){
		if(angles[0]==0)//z
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1,poz,pox,poy,poz+10,0,1,1);
		if(angles[0]==90||angles[0]==-270)//x
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1,poz,pox+10,poy,poz,1,1,0);
		if(angles[0]==180||angles[0]==-180)//-z
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1,poz,pox,poy,poz-10,0,1,1);
		if(angles[0]==270||angles[0]==-90)//-x
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1,poz,pox-10,poy,poz,1,1,0);
		fflag=1;
	}
	if(third==1){
		if(angles[0]==0)//z
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1+2,poz-2,pox,poy,poz+10,0,1,1);
		if(angles[0]==90||angles[0]==-270)//x
			gluLookAt(pox-2,poy+BASE_HEIGHT+2*HEAD_RADIUS+1+2,poz,pox+10,poy,poz,1,1,0);
		if(angles[0]==180||angles[0]==-180)//-z
			gluLookAt(pox,poy+BASE_HEIGHT+2*HEAD_RADIUS+1+2,poz+2,pox,poy,poz-10,0,1,1);
		if(angles[0]==270||angles[0]==-90)//-x
			gluLookAt(pox+2,poy+BASE_HEIGHT+2*HEAD_RADIUS+1+2,poz,pox-10,poy,poz,1,1,0);
	}
	if(tt==1){
		gluLookAt(-8,18, 15, 1.25, 0, 0.0, 0, 1,0);/*towerview1*/
	}
	if(onlyhover==1){
		gluLookAt(0,10,20,inix,iniy,iniz,0,1,0);
	}
	if(chkhover==1){
		gluLookAt(camx,camy,camz,inix,iniy,iniz,0,1,0);
	}
	if(drag==1){
		gluLookAt(camx,camy,camz,0,0,0,0,1,0);
	}
	if(camtile==1){
		int findcam=findcounter(tilex,tilez);
		int i,hhh;
		for(i=0;i<mtiles;i++){
			printf("%d\n",findcam);
			if(findcam==brnd[i]){
				hhh=wicht[i];
				printf("%d\n",hhh);
				if(hhh==0)tiley=ht0;
				if(hhh==1)tiley=ht1;
				if(hhh==2)tiley=ht2;
				if(hhh==3)tiley=ht3;
				if(hhh==4)tiley=ht4;
				break;
			}
		}
		gluLookAt(tilex,tiley,tilez,tilex,tiley,tilez-2,0,1,0);
	}

	/*gluLookAt (0, 10, 20, pox, poy,poz, 0, 1, 0);
	  light_pos[0]=0;
	  light_pos[1]=10;
	  light_pos[2]=20;
	  light_pos[3]=1.0;
	//light_pos[4] = {0, 10, 20, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//spotDir[] = {pox - 0, poy - 10, poz - 20};
	spotDir[0]=pox-0;
	spotDir[1]=poy-10;
	spotDir[2]=poz-20;
	glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);*/

	glPushMatrix();





	glTranslatef(0,-5-50,0);
	glColor3f(0.196078,0.6,0.8);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glColor3f(1.0f, 0.2f, 0.2f);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	//        glBindTexture(GL_TEXTURE_2D, theTexture[2]);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glutSolidCube(100);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);

	glPopMatrix();
	glPushMatrix();
	int i,j,g,k,rr;
	cntr=0;
	cnt=0;
	int upcntr=0;
	int findc=findcounter(pox,poz);
	//int findcam=findcounter(tilex,tiley);
	glTranslatef(-xx+1,-LEG_HEIGHT-1,-xx+1);
	/*for(i=0;i<40;i++){
	  printf("%d ",brnd[i]);
	  }
	  printf("\n");*/
	if(jump==0){
		poy=0;
	}
	int ind;
	for(k=0;k<2;k++){
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				for(ind=0;ind<staticb;ind++){
					if(cntr==blockrnd[ind]){
						if(flagp==0 &&k==0){
							if(findc==cntr){
								if(poy+1+LEG_HEIGHT<=3/*heightofblock+1(due to origindown)*/){
									poy=ppoy;
									pox=ppox;
									poz=ppoz;
								}
							}
							glPushMatrix();
							//glColor3f(0,0,1);
							glColor3f(1,1,0);
							glTranslatef(0,2,0);
							//glTranslatef(0,up[ind],side[ind]);

							glEnable(GL_TEXTURE_2D);
							glBindTexture(GL_TEXTURE_2D, _textureId);

							//Bottom
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
							//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
							//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							//	glColor3f(1.0f, 0.2f, 0.2f);
							glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
							glEnable(GL_TEXTURE_GEN_T);
							//        glBindTexture(GL_TEXTURE_2D, theTexture[2]);
							glBindTexture(GL_TEXTURE_2D, _textureId);
							glutSolidCube(1.98);
							glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
							glDisable(GL_TEXTURE_GEN_T);

							//glutSolidCube(1.98);
							glColor3f(0.5,0.1,0.1);
							glutWireCube(2);
							glPopMatrix();
							//	glTranslatef(2,0,0);
							//	cntr++;
							//	cnt++;
							//	break;
						}
						else if(flagp==1 && k==0){
							//int pqr=cntr+(side[ind]/2);
							//printf("pqr=%d cntr=%d\n",pqr,cntr);
							/*if(findc==pqr){
							  pox=ppox;
							  poy=ppoy;
							  poz=ppoz;
							  }*/
							/*if(pox==((int)((blockrnd[i]/10)-5))*2+side[i] && poz==(blockrnd[i]-(int)(blockrnd[i]/10)*10-5)*2){
							  pox=ppox;
							  poz=ppoz;
							  }*/
							/*if(findc==cntr){
							  if(poy+1+LEG_HEIGHT<=3){//heightofblock+1(due to origindown)
							  poy=ppoy;
							  pox=ppox;
							  poz=ppoz;
							  }
							  }*/
							glPushMatrix();
							glColor3f(0,0,1);
							//glTranslatef(0,2,0);
							if(cntr%10==0 && upup[ind]<0)upup[ind]=0;
							if(cntr%10==9 && upup[ind]>0)upup[ind]=0;
							if(cntr/90==1 && side[ind]>0)side[ind]=0;
							if(cntr/10==0 && side[ind]<0)side[ind]=0;
							int counterx=upup[ind]/2;
							int counterz=side[ind]/2;
							int finalc=cntr+counterx+10*counterz;
							if(finalc==findc){
								//	sleep(1);
								//	exit(0);
								pox=ppox;
								poz=ppoz;
							}
							if(finalc!=findc){
								glTranslatef(upup[ind],2,side[ind]);
								glColor3f(1,1,0);

								glEnable(GL_TEXTURE_2D);
								glBindTexture(GL_TEXTURE_2D, _textureId);

								//Bottom
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
								//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
								//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								//	glColor3f(1.0f, 0.2f, 0.2f);
								glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
								glEnable(GL_TEXTURE_GEN_T);
								//        glBindTexture(GL_TEXTURE_2D, theTexture[2]);
								glBindTexture(GL_TEXTURE_2D, _textureId);
								glutSolidCube(1.98);
								glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
								glDisable(GL_TEXTURE_GEN_T);


								glColor3f(0.5,0.1,0.1);
								glutWireCube(2);
							}
							glPopMatrix();
							//	glTranslatef(2,0,0);
							//	cntr++;
							//	cnt++;
							//	break;
						}
					}
				}
				//if(ind!=staticb)continue;
				for(rr=0;rr<mtiles;rr++){
					if(cntr==brnd[rr] && k==0){
						//fallflag=0;
						if(upcntr%5==0){
							cuboid(ht0);
							wicht[rr]=0;
							/*if(findcam==cntr){
							  tiley=ht0-1;
							  }*/
							if(findc==cntr && poy>=ht0-1){
								poy=ht0-1;
								ppox=pox;
								ppoz=poz;
							}
							else if(findc==cntr && poy<=ht0-1){
								if(pox==ppox && poz==ppoz){
									poy=ht0-1;
									printf("poy=%f ht0=%f\n",poy,ht0);
								}
								pox=ppox;
								poz=ppoz;
							}
						}
						if(upcntr%5==1){
							wicht[rr]=1;
							cuboid(ht1);
							/*if(findcam==cntr){
							  tiley=ht1-1;
							  }*/
							if(findc==cntr && poy>=ht1-1){
								poy=ht1-1;
								ppox=pox;
								ppoz=poz;
							}
							else if(findc==cntr && poy<=ht1-1){
								if(pox==ppox && poz==ppoz){
									poy=ht1-1;
									printf("poy=%f ht0=%f\n",poy,ht0);
								}
								pox=ppox;
								poz=ppoz;
							}
						}
						if(upcntr%5==2){
							wicht[rr]=2;
							cuboid(ht2);
							/*if(findcam==cntr){
							  tiley=ht2-1;
							  }*/
							if(findc==cntr && poy>=ht2-1){
								poy=ht2-1;
								ppox=pox;
								ppoz=poz;
							}
							else if(findc==cntr && poy<=ht2-1){
								if(pox==ppox && poz==ppoz){
									poy=ht2-1;
								}
								pox=ppox;
								poz=ppoz;
							}
						}
						if(upcntr%5==3){
							wicht[rr]=3;
							cuboid(ht3);
							/*if(findcam==cntr){
							  tiley=ht3-1;
							  }*/
							if(findc==cntr && poy>=ht3-1){
								poy=ht3-1;
								ppox=pox;
								ppoz=poz;
							}
							else if(findc==cntr && poy<=ht3-1){
								if(pox==ppox && poz==ppoz){
									poy=ht3-1;
								}
								pox=ppox;
								poz=ppoz;
							}
						}
						if(upcntr%5==4){
							wicht[rr]=4;
							cuboid(ht4);
							/*if(findcam==cntr){
							  tiley=ht4-1;
							  }*/
							if(findc==cntr && poy>=ht4-1){
								poy=ht4-1;
								ppox=pox;
								ppoz=poz;
							}
							else if(findc==cntr && poy<=ht4-1){
								if(pox==ppox && poz==ppoz){
									poy=ht4-1;
								}
								pox=ppox;
								poz=ppoz;
							}
						}
						upcntr++;
						glTranslatef(2,0,0);
						cntr++;
						cnt++;
						//continue;
						break;
					}
					/*else{
					  poy=0;
					  }*/
				}
				if(rr!=mtiles)continue;
				for(g=0;g<12;g++){
					if(cntr==rnd[g]){
						break;
					}
				}
				if(g==12){
					if(cnt%2==0){
						glColor3f(1,0.2,0);
					}
					else{
						glColor3f(0.556863,0.137255,0.137255);						
					}
					//fallflag=0;
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, _textureId);

					//Bottom
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					//	glColor3f(1.0f, 0.2f, 0.2f);
					glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
					glEnable(GL_TEXTURE_GEN_T);
					//        glBindTexture(GL_TEXTURE_2D, theTexture[2]);
					glBindTexture(GL_TEXTURE_2D, _textureId);
					glutSolidCube(1.96);
					glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
					glDisable(GL_TEXTURE_GEN_T);

					glColor3f(0.5,0.0,0.2);
					glutWireCube(2);
					glTranslatef(2,0,0);
				}
				else{
					glColor3f(0,0,0);
					glutSolidCube(2);
					glColor3f(0,1,0);
					glColor3f(0.5,0.0,0.2);
					glutWireCube(2);
					glTranslatef(2,0,0);
					if(cntr==findc){
						fallflag=1;
					}
				}
				cntr++;
				cnt++;
			}
			cnt++;
			glTranslatef(-2*xx,0,2*xx/10);
		}
		cnt++;
		cntr=0;
		glTranslatef(0,-2,-2*(xx));
	}
	glPopMatrix();
	if(pox > xx-1){
		fallflag=1;
		//pox=xx-1;
	}
	if(pox < -xx+1){
		fallflag=1;
		//pox=-xx+1;
	}
	if(poz > xx-1){
		fallflag=1;
		//poz=xx-1;
	}
	if(poz < -xx+1){
		fallflag=1;
		//poz=-xx+1;
	}

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	if(fallflag==1)poy=poy-ydec;
	glTranslatef (pox, poy, poz);
	glRotatef(angles[0], 0.0, 1.0, 0.0);
	if(fflag==0){
		glPushMatrix();
		drawtrunk();
		gluDisk(p,0,BASE_RADIUS,20,20);
		glPushMatrix();
		glTranslatef(0,0,BASE_HEIGHT);
		gluDisk(p,0,BASE_RADIUS,20,20);
		glPushMatrix();//head
		drawhead();
		glPopMatrix();
		glPushMatrix(); //right arm
		drawrightarm();
		glPopMatrix();
		glPushMatrix(); //left arm
		drawleftarm();
		glPopMatrix();
		glPopMatrix();
		glPushMatrix(); //right leg
		drawrightleg();
		glPopMatrix();
		glPushMatrix(); //left leg
		drawleftleg();	
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}


void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void processSpecialKeys(int key, int x, int y) {
	if(key==GLUT_KEY_UP){
		if(jump==1){
			fallflag=0;
		}
		kf=0;
		counttt=1;
		//pox -= cos(90 * pi/180 + angles[0] * pi/180);
		//poz += sin(90 * pi/180 + angles[0] * pi/180);
		//if(jump==0 || (jump==1 && jmpcnt==0)){
		if(fallflag==0){
			jmpcnt=1;
			if(angles[0]==0){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				poz=poz+2;
			}
			if(angles[0]==90 || angles[0]==-270){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				pox=pox+2;
			}
			if(angles[0]==180 || angles[0]==-180){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				poz=poz-2;
			}
			if(angles[0]==270 || angles[0]==-90 ){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				pox=pox-2;
			}
			lcount=(lcount+1)%2;
			if(lcount==0){
				angles[1]+=120;
				angles[2]-=120;
				angles[3]+=60;
				angles[4]-=60;
			}
			else{
				angles[1]-=120;
				angles[2]+=120;
				angles[3]-=60;
				angles[4]+=60;
			}
			if(pox > xx-1){
				fallflag=1;
				//pox=xx-1;
			}
			if(pox < -xx+1){
				fallflag=1;
				//pox=-xx+1;
			}
			if(poz > xx-1){
				fallflag=1;
				//poz=xx-1;
			}
			if(poz < -xx+1){
				fallflag=1;
				//poz=-xx+1;
			}
		}
	}
	if(key==GLUT_KEY_DOWN){
		if(jump==1){
			fallflag=0;
		}
		kf=1;
		counttt=1;
		//pox += cos(90 * pi/180 + angles[0] * pi/180);
		//poz -= sin(90 * pi/180 + angles[0] * pi/180);
		//if(jump==0 || (jump==1 && jmpcnt==0)){
		if(fallflag==0){
			jmpcnt=1;
			if(angles[0]==0){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				poz=poz-2;
			}
			if(angles[0]==90 || angles[0]==-270){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				pox=pox-2;
			}
			if(angles[0]==180 || angles[0]==-180){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				poz=poz+2;
			}
			if(angles[0]==270 || angles[0]==-90 ){
				ppoz=poz;
				ppox=pox;
				ppoy=poy;
				pox=pox+2;
			}
			lcount=(lcount+1)%2;
			if(lcount==0){
				angles[1]+=120;
				angles[2]-=120;
				angles[3]+=60;
				angles[4]-=60;
			}
			else{
				angles[1]-=120;
				angles[2]+=120;
				angles[3]-=60;
				angles[4]+=60;
			}
			if(pox > xx-1){
				fallflag=1;
				//pox=xx-1;
			}
			if(pox < -xx+1){
				fallflag=1;
				//pox=-xx+1;
			}
			if(poz > xx-1){
				fallflag=1;
				//poz=xx-1;
			}
			if(poz < -xx+1){
				fallflag=1;
				//poz=-xx+1;
			}
		}

	}
	if(key==GLUT_KEY_LEFT){
		angles[0]=(int)(angles[0]+90.0)%360;
	}
	if(key==GLUT_KEY_RIGHT){
		angles[0]=(int)(angles[0]-90.0)%360;
	}
	//display();
	glutPostRedisplay();
	}
	void keyboard (unsigned char key, int x, int y) {
		if(key=='i'){
			camtile=(camtile+1)%2;
		}
		if(key=='j') {
			jump=1;
		}
		if(key=='z'){
			third=(third+1)%2;
		}
		if(key=='x'){
			fff=(fff+1)%2;
		}
		if(key=='c'){
			flagp=(flagp+1)%2;
		}
		if(key=='v'){
			chkhover=(chkhover+1)%2;
			if(chkhover==1){
				camx=0;
				camy=10;
				camz=20;
				inix=0;
				iniy=0;
				iniz=0;
				flag41=0;
			}
		}
		if(key=='k'){
			onlyhover=(onlyhover+1)%2;
		}
		if(key=='b'){
			drag=(drag+1)%2;
		}

		if(key=='r'){
			tt=(tt+1)%2;
		}
		if(key=='s'){
			if(tilez+2>=-9 && tilez+2<=9)
				tilez=tilez+2;
		}
		if(key=='w'){
			if(tilez-2>=-9 && tilez-2<=9)
				tilez=tilez-2;
		}
		if(key=='a'){
			if(tilex-2>=-9 && tilex-2<=9)
				tilex=tilex-2;
		}
		if(key=='d'){
			if(tilex+2>=-9 && tilex+2<=9)
				tilex=tilex+2;
		}
		if(key=='q')exit(0);
		switch (key) {
			case 'o':oo=(oo+1)%2;
			case 't': tx=(int)(tx-5)%360;
				  break;
			case 'g': tx=(int)(tx+5)%360;
				  break;
			case 'f': ty=(int)(ty+5)%360;
				  break;
			case 'h': ty=(int)(ty-5)%360;
				  break;
			case 'm': zz=zz+0.5;
				  break;
			case 'n': zz=zz-0.5;
				  break;
		}
		glutPostRedisplay();
	}

	void update2(int value){
		int i;
		for(i=0;i<staticb;i++){
			int ppp=upup[i];
			int qqq=side[i];
			if(i%4==0){
				if(periodic%4==0)upup[i]=0;
				if(periodic%4==1)upup[i]=2;
				if(periodic%4==2)upup[i]=0;
				if(periodic%4==3)upup[i]=-2;
				/*if(pox+upup[i]>xx-1 || pox+upup[i]<-xx+1){
				  upup[i]=ppp;
				  }*/
				//if(periodic%4==4)upup[i]=0;

			}
			else if(i%4==1){
				if(periodic%4==0)side[i]=0;
				if(periodic%4==1)side[i]=-2;
				if(periodic%4==2)side[i]=0;
				if(periodic%4==3)side[i]=2;
				/*if(poz+side[i]>xx-1 || poz+side[i]<-xx+1){
				  upup[i]=qqq;
				  }*/
				//if(periodic%4==4)side[i]=0;
			}
			else if(i%4==2){
				if(periodic%4==0)upup[i]=0;
				if(periodic%4==1)upup[i]=-2;
				if(periodic%4==2)upup[i]=0;
				if(periodic%4==3)upup[i]=2;
				/*if(pox+upup[i]>xx-1 || pox+upup[i]<-xx+1){
				  upup[i]=ppp;
				  }*/
				//if(periodic%4==4)upup[i]=0;
			}		
			else if(i%4==3){
				if(periodic%4==0)side[i]=0;
				if(periodic%4==1)side[i]=2;
				if(periodic%4==2)side[i]=0;
				if(periodic%4==3)side[i]=-2;
				/*if(poz+side[i]>xx-1 || poz+side[i]<-xx+1){
				  upup[i]=qqq;
				  }*/
				//if(periodic%4==4)side[i]=0;
			}
		}
		periodic++;
		glutTimerFunc(300, update2, 0);
	}

	void update(int value){
		//printf("fallflag=%d\n",fallflag);
		if(fallflag==1){
			if(ydec>=BASE_HEIGHT+LEG_HEIGHT+2)exit(0);
			ydec=ydec+0.3;	
			//printf("ydec=%f\n",ydec);
		}
		if(jump==1){
			int i;
			for(i=0;i<staticb;i++){
				if(findcounter(pox,poz)==blockrnd[i]){
					poy=-LEG_HEIGHT+2;
				}

			}
			//printf("%d\n",jump);
			if(poy<6 && inc==0){
				//printf("jump poy up=%f\n",poy);
				poy=poy+1;
				if(poy>=6){
					inc=1;
				}
			}
			if(inc==1){
				if(poy>0){
					//printf("jump poy down=%f\n",poy);
					poy=poy-1;
					if(poy<=0){
						poy=0;
						inc=0;
						jump=0;
						jmpcnt=0;
					}
				}
			}
		}

		if(ht0<4 && incht0==0){
			ht0=ht0+0.2;
			if(ht0>=4){
				incht0=1;
			}
		}
		if(ht0==4)incht0=1;
		if(incht0==1){
			if(ht0>0){
				ht0=ht0-0.2;
				if(ht0<=0){
					incht0=0;
				}
			}
		}
		if(ht1<4 && incht1==0){
			ht1=ht1+0.2;
			if(ht1>=4){
				incht1=1;
			}
		}
		if(ht1==4)incht1=1;
		if(incht1==1){
			if(ht1>0){
				ht1=ht1-0.2;
				if(ht1<=0){
					incht1=0;
				}
			}
		}
		if(ht2<4 && incht2==0){
			ht2=ht2+0.2;
			if(ht2>=4){
				incht2=1;
			}
		}
		if(ht2==4)incht2=1;
		if(incht2==1){
			if(ht2>0){
				ht2=ht2-0.2;
				if(ht2<=0){
					incht2=0;
				}
			}
		}
		if(ht3<4 && incht3==0){
			ht3=ht3+0.2;
			if(ht3>=4){
				incht3=1;
			}
		}
		if(ht3==4)incht3=1;
		if(incht3==1){
			if(ht3>0){
				ht3=ht3-0.2;
				if(ht3<=0){
					incht3=0;
				}
			}
		}
		if(ht4<4 && incht4==0){
			ht4=ht4+0.2;
			if(ht4>=4){
				incht4=1;
			}
		}
		if(ht4==4)incht4=1;
		if(incht4==1){
			if(ht4>0){
				ht4=ht4-0.2;
				if(ht4<=0){
					incht4=0;
				}
			}
		}
		/*for(i=0;i<staticb;i++){
		  if(up[i] && incht0==0){
		  ht0=ht0+0.2;
		  if(ht0>=4){
		  incht0=1;
		  }
		  }
		  if(ht0==4)incht0=1;
		  if(incht0==1){
		  if(ht0>0){
		  ht0=ht0-0.2;
		  if(ht0<=0){
		  incht0=0;
		  }
		  }
		  }

		  }*/
		glutTimerFunc(160,update,1);
		glutPostRedisplay();
	}
	void processMouseActiveMotion(int button, int state, int x, int y){
		if(state == GLUT_DOWN){
			if(button == GLUT_LEFT_BUTTON){
				xi=x;
				yi=y;
				//Left Button code.
			}
			else if(button == GLUT_MIDDLE_BUTTON){
				//middle button code
			}
			else if(button == GLUT_RIGHT_BUTTON){
				//right button code
			}
		}
		if(state == GLUT_UP){
			if(button == GLUT_LEFT_BUTTON){
				xf=x;
				yf=y;
				if(chkhover==1 || drag==1){
					float ddx=xf-xi;
					float tanglex=-((ddx/40.0)*20.0)/180;
					printf("%f\n",tanglex);
					float tempx=camx;
					printf("%f %f\n",camx,camz);
					camx=camx*cos(tanglex)+camz*sin(tanglex);
					camz=-tempx*sin(tanglex)+camz*cos(tanglex);
					float ddy=yf-yi;
					float tangley=-((ddy/20.0)*20.0)/180;
					float tempy=camy;
					camy=camy*cos(tangley)-camz*sin(tangley);
					camz=tempy*sin(tangley)+camz*cos(tangley);

					inix=0;
					iniy=0;
					iniz=0;
				}
				//Left Button code.
			}
			else if(button == GLUT_MIDDLE_BUTTON){
				//middle button code
			}
			else if(button == GLUT_RIGHT_BUTTON){
				//right button code
			}
		}
		if (button==4)
		{
			{camx+=0.1*(camx-inix);camz+=0.1*(camz-iniz);camy+=0.1*(camy-iniy);}
		}

		if(button==3)
		{
			{camx-=0.1*(camx-inix);camz-=0.1*(camz-iniz);camy-=0.1*(camy-iniy);}
		}
	}
	void processMousePassiveMotion(int x,int y){
		if(chkhover==1 || onlyhover==1){
			if(flag41==0){
				flag41=1;
				prx=x;
				pry=y;
			}
			float delx,dely;
			delx=-(prx-x);
			dely=+(pry-y);
			inix+=delx/10;
			iniy+=dely/10;
			prx=x;
			pry=y;
			//printf("x=%d,y=%d,delx=%f,dely=%f,inix=%f,iniy=%f\n",x,y,delx,dely,inix,iniy);
			/*printf("%f %f\n",x/20.0,y/20.0);
			  inix=x/20.0;
			  iniy=y/20.0;*/
		}
	}
	void myinit() {
		GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
		GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glEnable(GL_DEPTH_TEST);        
		glEnable(GL_COLOR_MATERIAL);
		p=gluNewQuadric();
	}
	void init1(void){
		GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat mat_shininess[] = {50.0};
		GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat white_light[] = {0.3, 0.3, 0.3, 1.0};
		//GLfloat white_light[] = {0.8, 0.8, 0.8, 1.0};
		GLfloat lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		//	glEnable(GL_LIGHTING);
		//	glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		Image* image = loadBMP("w2.bmp");
		_textureId = loadTexture(image);
		delete image;
		glEnable(GL_DEPTH_TEST);
	}

	int main(int argc, char **argv)
	{
		int i,k=0,ii,j;
		srand(time(NULL));
		for(i=0;i<12;i++){
			rnd[i]=rand()%100;
			if(rnd[i]==0 || rnd[i]==99)i--;
		}
		while(1){
			if(k==mtiles){
				break;
			}
			ii=rand()%100+1;
			if(ii==0 || ii==99)continue;
			for(i=0;i<12;i++){
				if(ii==rnd[i]){
					break;
				}
			}
			if(i==12){
				brnd[k++]=ii;
			}
		}
		k=0;
		while(1){
			if(k==staticb)break;
			ii=rand()%100+1;
			if(ii==0 || ii==99)continue;
			for(i=0;i<12;i++){
				if(ii==rnd[i]){
					break;
				}
			}
			for(j=0;j<mtiles;j++){
				if(ii==brnd[j]){
					break;
				}
			}
			if(i==12 && j==mtiles){
				blockrnd[k++]=ii;
			}
		}
		for(i=0;i<staticb;i++){
			upup[i]=0;
			side[i]=0;
		}
		/*for(i=0;i<12;i++){
		  printf("%d ",rnd[i]);
		  }
		  printf("\n");
		  for(i=0;i<mtiles;i++){
		  printf("%d ",brnd[i]);
		  }
		  printf("\n");
		  for(i=0;i<staticb;i++){
		  printf("%d ",blockrnd[i]);
		  }
		  printf("\n");*/

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(500, 500);
		glutCreateWindow("robot");
		myinit();
		init1();
		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		//glutIdleFunc(idling);
		glutKeyboardFunc(keyboard);
		glutMouseFunc(processMouseActiveMotion);
		glutPassiveMotionFunc(processMousePassiveMotion);
		glutSpecialFunc(processSpecialKeys);
		glutTimerFunc(160, update, 0);
		glutTimerFunc(300, update2, 0);
		glutMainLoop();
		return 0;
	}

