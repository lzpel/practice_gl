//
// Created by misum on 2020/11/15.
//

#include "Node.h"
#include "string.h"

Node::Node(bool isStateMachine) {
	parent = 0;
	status = 0;
	name = 0;
	if (isStateMachine) {
		status = new std::map<std::string, Node::Stat>();
	}
}

Node::~Node() {
	if (status)delete status;
}

void Node::NodeNew(Node *newchild) {
	newchild->parent = this;
	newchild->Init();
	children.push_back(newchild);
}

void Node::NodeTerminate() {
	for (auto itr = children.begin(); itr != children.end(); ++itr) {
		(*itr)->NodeTerminate();
		delete (*itr);
	}
	children.clear();
	Terminate();
}

void Node::NodeDraw() {
	Draw();
	for (auto itr = children.begin(); itr != children.end(); ++itr) {
		(*itr)->NodeDraw();
	}
}

Node *Node::NodeFind(const char *key) {
	for (auto itr = children.begin(); itr != children.end(); ++itr) {
		if (strcmp((*itr)->name, key) == 0)return *itr;
	}
	return 0;
}

Node::Stat &Node::NodeState(const char *key, bool apex) {
	Node *p = this;
	if (apex) {
		while (p->parent)p = p->parent;
	} else {
		while (!p->status)p = p->parent;
	}
	return (*p->status)[key];
}

void Node::NodeState(const char* key,int x,int y){
	Stat&s=NodeState(key);
	s.x=x;
	s.y=y;
}
void Node::Move(float x, float y, float z) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}