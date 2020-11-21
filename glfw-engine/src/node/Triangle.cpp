//
// Created by misum on 2020/11/15.
//

#include "Triangle.h"
#include "Graphics.h"
#include <math.h>
void Triangle::Init() {
}
void Triangle::Draw() {
	Stat& w=NodeState("WINDOW");
	GLfloat m[18]={0};
	m[0]=sin(2*M_PI*w.time/w.frq);
	m[1]=sqrt(3);
	m[3]=0.5+0.5*sin(5*M_PI*w.time/w.frq);
	m[4]=0.5+0.5*sin(7*M_PI*w.time/w.frq);
	m[5]=0.5+0.5*sin(11*M_PI*w.time/w.frq);
	m[06]=+1;
	m[12]=-1;
	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*6, &m[0]);
	glColorPointer(3,GL_FLOAT,sizeof(GLfloat)*6, &m[3]);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	 */
}
void Triangle::Terminate() {

}