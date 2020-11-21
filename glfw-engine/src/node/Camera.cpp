//
// Created by misum on 2020/11/15.
//
#include "Camera.h"
#include "Graphics.h"

glm::mat4 genView(glm::vec3 pos, glm::vec3 lookat) {
	// Camera matrix
	glm::mat4 view = glm::lookAt(pos, lookat, glm::vec3(0, 1, 0));
	return view;
}

glm::mat4 genMVP(glm::mat4 view_mat, glm::mat4 model_mat, float fov, int w, int h) {
	glm::mat4 Projection = glm::perspective(glm::radians(fov), (float) w / (float) h, 0.01f, 10000.0f);
	// Or, for an ortho camera :
	// glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
	// // In world coordinates
	glm::mat4 mvp = Projection * view_mat * model_mat;
	return mvp;
}

Camera::Camera() {
	//最低限破綻なきように設定。
	//メートルに準じる
	up[0] = up[1] = up[2] = lookat[0] = lookat[1] = lookat[2] = 0;
	up[1] = 1;
	Move(0, 1, 2);
	name = "camera";
}

void Camera::Init() {}

void Camera::Terminate() {}

void Camera::Draw() {
	Stat &window = NodeState("WINDOW");
	vec3 up = {0, 1, 0};
	mat4 view_mat;
	modelview(view_mat, lookat, pos, up);
	vec3 sun_position = {3.0, 10.0, -5.0};
	vec3 sun_color = {1.0, 1.0, 1.0};
	mat4 p, mvp;
	perspective(p, 45, float(window.x) / window.y, 0.01f, 10000.0f);
	product(mvp, view_mat,p);
	//transpose(mvp);
	glUniformMatrix4fv(glGetUniformLocation(window.shader, "mvp"), 1, GL_FALSE, mvp);
	glUniform3fv(glGetUniformLocation(window.shader, "lp"), 1, &sun_position[0]);
	glUniform3fv(glGetUniformLocation(window.shader, "lc"), 1, &sun_color[0]);
}