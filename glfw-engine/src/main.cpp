#include "Engine.h"
#include "Node/Axis.h"
#include "Node/Triangle.h"
#include "Node/Camera.h"
#include <math.h>

class MyEngine:public Engine{
public:
	Node*camera;
	void Init(){
		NodeNew(camera=new Camera());
		NodeNew(new Axis());
		NodeNew(new Triangle());
	}
	void Draw() {
		Stat&w=NodeState("WINDOW");
		float m=2*M_PI*float(w.time)/w.frq*0.1;
		camera->Move(5*sin(m),1,5*cos(m));
	}
};
int main(int argc, const char** argv){
	MyEngine engine;
	engine.NodeState("WINDOW",640,480);
	engine.Run();
	return 0;
}