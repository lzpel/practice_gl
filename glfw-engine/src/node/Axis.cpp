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
	axis.reserve(6*(3+2*(SIZE*2+1)));
	for(int i=-SIZE;i<=SIZE;i++){
		axis.push_back(i);axis.push_back(0);axis.push_back(SIZE);
		axis.push_back(i);axis.push_back(0);axis.push_back(-SIZE);

		axis.push_back(SIZE);axis.push_back(0);axis.push_back(i);
		axis.push_back(-SIZE);axis.push_back(0);axis.push_back(i);
	}
	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(SIZE*2);axis.push_back(0);axis.push_back(0);

	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(0);axis.push_back(SIZE*2);axis.push_back(0);

	axis.push_back(0);axis.push_back(0);axis.push_back(0);
	axis.push_back(0);axis.push_back(0);axis.push_back(SIZE*2);
	GLuint buf;

	glGenBuffers(1,&buf);
	glBindBuffer(GL_ARRAY_BUFFER,buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBufferData(GL_ARRAY_BUFFER, axis.size()*sizeof(GLfloat), &axis[0], GL_STATIC_DRAW);

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0 );

	glBindVertexArray( 0 );
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//glEnableVertexAttribA
	vbuf=buf;
	size=axis.size();
}
void Axis::Draw() {
	glBindVertexArray( vao );
	glDrawArrays(GL_LINES,0,size/3);
	glBindVertexArray( 0 );
}
void Axis::Terminate() {
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vbuf);
}