#include "Engine.h"
#include "Node/Axis.h"
#include "Node/Triangle.h"
#include "Node/Camera.h"
#include "Node/Model.h"
#include <math.h>

//TODO 3.3 core profile に置き換えてバイナリサイズを下げる

class MyEngine:public Engine{
public:
	Node*camera;
	void Init(){
		NodeNew(camera=new Camera());
		NodeNew(new Axis());
		//NodeNew(new Triangle());
		NodeNew(new Model(StateCstr("FILE")));
	}
	void Draw() {
		float m=0.1*M_PI*StateDouble("TIME");
		camera->Move(100*sin(m),-100,100*cos(m));
	}
};
int main(int argc, const char** argv){
	MyEngine engine;
	engine.StateInt("WIDTH")=640;
	engine.StateInt("HEIGHT")=480;
	engine.StateCstr("FILE")=argc>1?argv[1]:"scene.gltf";
	engine.Run();
	return 0;
}