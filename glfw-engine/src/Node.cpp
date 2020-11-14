//
// Created by misum on 2020/11/15.
//

#include "Node.h"

Node::Node(bool isStateMachine){
	parent=0;
	status=0;
	if(isStateMachine){
		status=new std::map<std::string,Node::Stat>();
	}
}
Node::~Node(){
	if(status)delete status;
}

void Node::NodeNew(Node *newchild) {
	newchild->parent=this;
	newchild->Init();
	children.push_back(newchild);
}

void Node::NodeTerminate() {
	for(auto itr = children.begin(); itr != children.end(); ++itr) {
		//delete this;はメモリが非安全なので避ける
		//TerminateやDestructorで兄弟を増やしたり減らしたりするとエラーになりそう。
		(*itr)->NodeTerminate();
		delete (*itr);
	}
	children.clear();
	Terminate();
}

void Node::NodeDraw() {
	Draw();
	for(auto itr = children.begin(); itr != children.end(); ++itr) {
		(*itr)->NodeDraw();
	}
}

Node::Stat& Node::NodeState(const char *key) {
	Node*statemachine=this;
	while(!statemachine->status)statemachine=statemachine->parent;
	return (*statemachine->status)[key];
}

void Node::NodeState(const char *key,int x,int y,int z) {
	Stat&s=NodeState(key);
	s.x=x;s.y=y;s.z=z;
}

void Node::Move(float x, float y, float z) {
	pos[0]=x;
	pos[1]=y;
	pos[2]=z;
}