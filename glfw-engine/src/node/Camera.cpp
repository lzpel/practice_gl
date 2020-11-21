//
// Created by misum on 2020/11/15.
//
#include "Camera.h"
#include "Graphics.h"
#include <glm/gtc/matrix_transform.hpp>
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
	float fov=45,*pmvp;
	//glm

	glm::mat4 gview_mat = glm::lookAt(glm::vec3(pos[0], pos[1], pos[2]), glm::vec3(lookat[0], lookat[1], lookat[2]), glm::vec3(up[0], up[1], up[0]));
	mat4 &tmp=(mat4&)gview_mat[0][0];
	glm::mat4 gProjection = glm::perspective(glm::radians(fov), (float) window.x / (float)  window.y, 0.01f, 10000.0f);
	glm::mat4 gmvp = gProjection * gview_mat;
	pmvp=&gmvp[0][0];

	mat4 view_mat;
	modelview(view_mat, lookat, pos, up);
	mat4 p, mvp;
	perspective(p, 45, float(window.x) / window.y, 0.01f, 10000.0f);
	product(mvp,view_mat,p);
	//transpose(mvp);

	vec3 sun_position = {3.0, 10.0, -5.0};
	vec3 sun_color = {1.0, 1.0, 1.0};
	glUniformMatrix4fv(glGetUniformLocation(window.shader, "mvp"), 1, GL_FALSE, pmvp);
	glUniform3fv(glGetUniformLocation(window.shader, "lp"), 1, &sun_position[0]);
	glUniform3fv(glGetUniformLocation(window.shader, "lc"), 1, &sun_color[0]);
}