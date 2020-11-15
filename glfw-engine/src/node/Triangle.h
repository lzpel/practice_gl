//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_TRIANGLE_H
#define GLPRACTICE_TRIANGLE_H

#include "Node.h"

class Triangle : public virtual Node{
public:
	void Init();
	void Draw();
	void Terminate();
};


#endif //GLPRACTICE_TRIANGLE_H
