//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_MODEL_H
#define GLPRACTICE_MODEL_H

#include "Node.h"
#include "tiny_gltf.h"

class Model : public virtual Node{
	tinygltf::Model model;
	int vao,shader;
public:
	Model(const char*filename);
	virtual ~Model();
	void Init();
	void Draw();
	void Terminate();
};

#endif //GLPRACTICE_MODEL_H
