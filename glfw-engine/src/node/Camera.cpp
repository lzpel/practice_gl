//
// Created by misum on 2020/11/15.
//
#include "Camera.h"
#include "Graphics.h"
Camera::Camera() {
	//最低限破綻なきように設定。メートルに準じる
	identity(pv);
	up[0] = up[1] = up[2] = lookat[0] = lookat[1] = lookat[2] = 0;
	up[1] = 1;
	Move(0, 1, 2);
	name = "camera";
}

void Camera::Init() {
	StateFloats("PV")=pv;
}

void Camera::Terminate() {}

void Camera::Draw() {
	mat4 v,p;
	modelview(v, lookat, pos, up);
	perspective(p, 45, float(StateInt("WIDTH")) / StateInt("HEIGHT"), 0.01f, 10000.0f);
	product(pv,p,v);
	vec3 sun_position = {3.0, 10.0, -5.0};
	vec3 sun_color = {1.0, 1.0, 1.0};
	glUniform3fv(1, 1, sun_position);
	glUniform3fv(2, 1, sun_color);
}