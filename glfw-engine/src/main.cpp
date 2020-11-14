#include "Engine.h"
#include "Node/Axis.h"

int main(int argc, const char** argv){
	Engine engine;
	engine.NodeState("WINDOW",640,480);
	engine.WindowTitle="Hello World";
	engine.Run();
	return 0;
}