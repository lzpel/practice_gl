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
	Stat&w=NodeState("WINDOW");
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBufferData(GL_ARRAY_BUFFER, axis.size()*sizeof(GLfloat), &axis[0], GL_STATIC_DRAW);
	glCheckError();

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glCheckError();

	GLint position = glGetAttribLocation(w.shader, "pos");
	glCheckError();
	glEnableVertexAttribArray( position );
	glCheckError();
	glVertexAttribPointer( position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, 0 );
	glCheckError();

	glBindVertexArray( 0 );
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glCheckError();
	//glEnableVertexAttribA
	vbuf=buf;
	size=axis.size();
}
void Axis::Draw() {
	glCheckError();
	glBindVertexArray( vao );
	glDrawArrays(GL_LINES,0,size/6);
	glBindVertexArray( 0 );
	glCheckError();
}
void Axis::Terminate() {
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vbuf);
}