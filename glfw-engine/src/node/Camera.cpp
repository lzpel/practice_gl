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

Camera::Camera(){
	//最低限破綻なきように設定。
	//メートルに準じる
	up[0]=up[1]=up[2]=lookat[0]=lookat[1]=lookat[2]=0;up[1]=1;
	Move(0,1,2);
	name="camera";
}

void Camera::Init() {}

void Camera::Terminate() {}

void Camera::Draw() {
	Stat& window=NodeState("WINDOW");
	// grab uniforms to modify
	//GLuint MVP_u = glGetUniformLocation(shader.pid, "MVP");
	//GLuint sun_position_u = glGetUniformLocation(shader.pid, "sun_position");
	//GLuint sun_color_u = glGetUniformLocation(shader.pid, "sun_color");

	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 model_rot = glm::mat4(1.0f);
	glm::vec3 model_pos = glm::vec3(lookat[0], lookat[1], lookat[2]);

	// generate a camera view, based on eye-position and lookAt world-position
	glm::mat4 view_mat = genView(glm::vec3(pos[0], pos[1], pos[2]), model_pos);

	glm::vec3 sun_position = glm::vec3(3.0, 10.0, -5.0);
	glm::vec3 sun_color = glm::vec3(1.0);

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), model_pos);  // reposition model
	model_rot = glm::rotate(model_rot, glm::radians(0.08f), glm::vec3(0, 1, 0));  // rotate model on y axis
	model_mat = trans * model_rot;

	// build a model-view-projection
	glm::mat4 mvp = genMVP(view_mat, model_mat, 45.0f, window.x, window.y);
	glCheckError();
	glUniformMatrix4fv(glGetUniformLocation(window.shader, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	glUniform3fv(glGetUniformLocation(window.shader, "lp"), 1, &sun_position[0]);
	glUniform3fv(glGetUniformLocation(window.shader, "lc"), 1, &sun_color[0]);
	glCheckError();
}