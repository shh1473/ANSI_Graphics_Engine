#include "common.h"

/* ImGui */
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

const float WindowWidth{ 800.0f };
const float WindowHeight{ 600.0f };

/* 프로그램 진입점 */
int main()
{
	/* GLFW 초기화, 창을 생성할 수 있는 상태 구축 */
	if (!glfwInit())
	{
		std::cout << "Failed: GLFW initialization" << std::endl;
		return -1;
	}
	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

	/* 창모드로 창을 생성하고 OpenGL context 생성 */
	GLFWwindow * window{ glfwCreateWindow(static_cast<unsigned>(WindowWidth), static_cast<unsigned>(WindowHeight), "Hello World", nullptr, nullptr) };
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed: Window creation" << std::endl;
		return -1;
	}
	GL_CHECK(glfwMakeContextCurrent(window));
	GL_CHECK(glfwSwapInterval(1));

	/* GLEW 초기화 */
	GLenum result{ glewInit() };
	if (result != GLEW_OK)
	{
		std::cout << "Failed: GLEW initialization - " << glewGetErrorString(result) << std::endl;
		return -1;
	}
	std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

	const unsigned char * version{ nullptr };
	GL_CHECK(version = glGetString(GL_VERSION));
	std::cout << "OpenGL Version: " << version << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while (!glfwWindowShouldClose(window))
	{
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GL_CHECK(glfwSwapBuffers(window));
		GL_CHECK(glfwPollEvents());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}
