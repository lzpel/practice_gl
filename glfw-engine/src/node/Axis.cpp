//
// Created by misum on 2020/11/15.
//

#include "Axis.h"
#include "Graphics.h"
#include<vector>
Axis::Axis(){
	name="Axis";
}
void Axis::Init() {
	static const int SIZE=5;
	std::vector<GLfloat> axis;
	axis.reserve(12*(3+2*(SIZE*2+1)));
	for(int i=-SIZE;i<=SIZE;i++){
		axis.push_back(i);axis.push_back(0);axis.push_back(SIZE);
		axis.push_back(1);axis.push_back(1);axis.push_back(1);
		axis.push_back(i);axis.push_back(0);axis.push_back(-SIZE);
		axis.push_back(1);axis.push_back(1);axis.push_back(1);

		axis.push_back(SIZE);axis.push_back(0);axis.push_back(i);
		axis.push_back(1);axis.push_back(1);axis.push_back(1);
		axis.push_back(-SIZE);axis.push_back(0);axis.push_back(i);
		axis.push_back(1);axis.push_back(1);axis.push_back(1);
	}
	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(1);axis.push_back(0);axis.push_back(0);
	axis.push_back(SIZE*2);axis.push_back(0);axis.push_back(0);
	axis.push_back(1);axis.push_back(0);axis.push_back(0);

	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(0);axis.push_back(1);axis.push_back(0);
	axis.push_back(0);axis.push_back(SIZE*2);axis.push_back(0);
	axis.push_back(0);axis.push_back(1);axis.push_back(0);

	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(0);axis.push_back(0);axis.push_back(1);
	axis.push_back(0);axis.push_back(0);axis.push_back(SIZE*2);
	axis.push_back(0);axis.push_back(0);axis.push_back(1);
	GLuint buf;
	glGenBuffers(1,&buf);
	glBindBuffer(GL_ARRAY_BUFFER,buf);
	glBufferData(GL_ARRAY_BUFFER, axis.size()*sizeof(GLfloat), &axis[0], GL_STATIC_DRAW);
	vbuf=buf;
	size=axis.size();
}
void Axis::Draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*6, (char*)(sizeof(GLfloat)*0));
	glColorPointer(3,GL_FLOAT,sizeof(GL_FLOAT)*6,(char*)(sizeof(GL_FLOAT)*3));
	glDrawArrays(GL_LINES,0,size/6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
void Axis::Terminate() {
	glDeleteBuffers(1,&vbuf);
}