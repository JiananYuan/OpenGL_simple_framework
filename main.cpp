// dev
#include "Angel.h"
#include <string>

// #pragma comment(lib, "glew32.lib")

const int NUM_POINTS = 3;

void init()
{
	// 定义三角形的三个点
	vec2 vertices[3] = {
		vec2(-0.75, -0.75), vec2(0.0, 0.75), vec2(0.75, -0.75)
	};

	// 创建顶点数组对象
	GLuint vao;
	#ifdef __APPLE__	// for MacOS
		glGenVertexArraysAPPLE(1, &vao);	// 分配1个顶点数组对象
		glBindVertexArrayAPPLE(vao);		// 绑定顶点数组对象
	#else				// for Windows
		glGenVertexArrays(1, &vao);		// 分配1个顶点数组对象
		glBindVertexArray(vao);			// 绑定顶点数组对象
	#endif

	// 创建顶点缓存对象
	GLuint buffer;
	// 分配1个顶点缓存对象
	glGenBuffers(1, &buffer);
	// 绑定顶点缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// 分配数据所需的存储空间，将数据拷贝到OpenGL服务端内存
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 读取着色器并使用
	std::string vshader, fshader;
	#ifdef __APPLE__	// for MacOS
		vshader = "shaders/vshader_mac.glsl";
		fshader = "shaders/fshader_mac.glsl";
	#else				// for Windows
		vshader = "shaders/vshader_win.glsl";
		fshader = "shaders/fshader_win.glsl";
	#endif
	GLuint program = InitShader(vshader.c_str(), fshader.c_str());
	glUseProgram(program);

	// 从顶点着色器中初始化顶点的位置
	GLuint location = glGetAttribLocation(program, "vPosition");
	// 启用顶点属性数组
	glEnableVertexAttribArray(location);
	// 关联到顶点属性数组 (index, size, type, normalized, stride, *pointer)
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// 白色背景
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(void)
{
	// 清理窗口
	glClear(GL_COLOR_BUFFER_BIT);
	// 绘制所有点
	glDrawArrays(GL_TRIANGLES, 0, NUM_POINTS);
	glFlush();
}

int main(int argc, char **argv)
{
	// 初始化GLUT库，必须是应用程序调用的第一个GLUT函数
	glutInit(&argc, argv);

	// 配置窗口的显示特性
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Red Triangle");

	// for Windows
	#ifdef WIN32
		// 检测是否使用了freeglut，并检测是否使用到了OpenGL 3.3
		glutInitContextVersion(3, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);
		// 保证GLEW使用更多的现代技术管理OpenGL，防止core profile出现崩溃
		glewExperimental = GL_TRUE;
		glewInit();
	#endif

	init();
	// 指定当前窗口进行重绘时要调用的函数
	glutDisplayFunc(display);

	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Supported GLSL version is: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// 负责一直处理窗口和操作系统的用户输入等操作
	glutMainLoop();

	return 0;
}
