<<<<<<< HEAD
// 这是OpenGl中的照相机类
=======
﻿// ?????
>>>>>>> 249c843b8f9b104efaca069f35968b25808e02a2
#include "Camera.h"

Camera::Camera() { updateCamera(); };
Camera::~Camera() {};


mat4 Camera::lookAt(const vec4& eye, const vec4& at, const vec4& up)
{
	// @TODO: Task1:请按照实验课内容补全相机观察矩阵的计算
	mat4 c;
	return c;
}

mat4 Camera::ortho(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// @TODO: Task2:请按照实验课内容补全正交投影矩阵的计算
	mat4 c;
	return c;
}

mat4 Camera::perspective(const GLfloat fovy, const GLfloat aspect,
	const GLfloat zNear, const GLfloat zFar)
{
	// @TODO: Task3:请按照实验课内容补全透视投影矩阵的计算
	mat4 c;
	return c;
}

mat4 Camera::frustum(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// 任意视锥体矩阵
	mat4 c;
	c[0][0] = 2.0 * zNear / (right - left);
	c[0][2] = (right + left) / (right - left);
	c[1][1] = 2.0 * zNear / (top - bottom);
	c[1][2] = (top + bottom) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;
	return c;
}


void Camera::updateCamera()
{
	// @TODO: Task1 设置相机位置和方向
	float eyex = 0;			// 根据rotateAngle和upAngle设置x
	float eyey = 0;			// 根据upAngle设置y
	float eyez = radius;	// 根据rotateAngle和upAngle设置z

	eye = vec4(eyex, eyey, eyez, 1.0);
	at = vec4(0.0, 0.0, 0.0, 1.0);
	up = vec4(0.0, 1.0, 0.0, 0.0);

}

void Camera::keyboard(unsigned char key, int x, int y)
{

	// 键盘事件处理
	switch (key)
	{
		// 通过按键改变相机和投影的参数
	case 'x':
		rotateAngle += 5.0;
		break;
	case 'X':
		rotateAngle -= 5.0;
		break;

	case 'y':
		upAngle += 5.0;
		if (upAngle > 180)
			upAngle = 180;
		break;
	case 'Y':
		upAngle -= 5.0;
		if (upAngle < -180)
			upAngle = -180;
		break;

	case 'r':
		radius += 0.1;
		break;
	case 'R':
		radius -= 0.1;
		break;

	case 'f':
		fov += 5.0;
		break;
	case 'F':
		fov -= 5.0;
		break;

	case 'a':
		aspect += 0.1;
		break;
	case 'A':
		aspect -= 0.1;
		break;

	case 's':
		scale += 0.1;
		break;
	case 'S':
		scale -= 0.1;
		break;

		// 空格键初始化所有参数
	case ' ':
		radius = 4.0;
		rotateAngle = 0.0;
		upAngle = 0.0;
		fov = 45.0;
		aspect = 1.0;
		scale = 1.5;
		break;
	}
}
