//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_AXIS_H
#define GLPRACTICE_AXIS_H

#include "Node.h"

class Axis :virtual public Node{
	unsigned vbuf,vao,size;
public:
	Axis();
	void Init();
	void Draw();
	void Terminate();
};


#endif //GLPRACTICE_AXIS_H
