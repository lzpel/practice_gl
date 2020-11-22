//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_CAMERA_H
#define GLPRACTICE_CAMERA_H

#include "Node.h"
#include "Graphics.h"
class Camera :virtual public Node{
	vec3 up,lookat;
	mat4 pv;
	int shaderid;
	void Init();
	void Draw();
	void Terminate();
public:
	Camera();
};


#endif //GLPRACTICE_CAMERA_H
