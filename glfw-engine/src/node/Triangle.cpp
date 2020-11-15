//
// Created by misum on 2020/11/15.
//

#include "Triangle.h"
#include "Graphics.h"
void Triangle::Init() {
}
void Triangle::Draw() {
	Stat& w=NodeState("WINDOW");
	glBegin(GL_TRIANGLES);
	glColor3f(0.5+0.5*sin(5*M_PI*w.time/w.frq), 0.5+0.5*sin(7*M_PI*w.time/w.frq), 0.5+0.5*sin(11*M_PI*w.time/w.frq));
	glVertex2f(sin(2*M_PI*w.time/w.frq), sqrt(3));
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
}
void Triangle::Terminate() {

}