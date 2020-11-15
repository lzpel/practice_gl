#include "Engine.h"
#include "Node/Axis.h"
#include "Node/Triangle.h"
#include "Node/Camera.h"
#include "Node/Model.h"
#include <math.h>

class MyEngine:public Engine{
public:
	Node*camera;
	void Init(){
		NodeNew(camera=new Camera());
		NodeNew(new Axis());
		NodeNew(new Triangle());
		NodeNew(new Model("C:/Users/misum/Downloads/mew_pokemon/scene.gltf"));
	}
	void Draw() {
		Stat&w=NodeState("WINDOW");
		float m=2*M_PI*float(w.time)/w.frq*0.1;
		camera->Move(100*sin(m),-100,100*cos(m));
	}
};
int main(int argc, const char** argv){
	MyEngine engine;
	engine.NodeState("WINDOW",640,480);
	engine.Run();
	return 0;
}