//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_CAMERA_H
#define GLPRACTICE_CAMERA_H

#include "Node.h"

class Camera :virtual public Node{
	float up[3];
	float lookat[3];
	int shaderid,shadermvpid;
	void Init();
	void Draw();
	void Terminate();
public:
	Camera();
};


#endif //GLPRACTICE_CAMERA_H
