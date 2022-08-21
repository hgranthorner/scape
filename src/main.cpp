#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>


void error_callback(int error_code, const char* description) {
	std::cerr << "OpenGL Error [" << error_code << "]: " << description << std::endl;
}

int main() {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Failed to init OpenGL" << std::endl;
		return 1;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	auto window = glfwCreateWindow(1280, 720, "Scape", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create window!" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);
	auto version = gladLoadGL(glfwGetProcAddress);
	std::cout << "OpenGL version: " << version << std::endl;

	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	std::chrono::time_point<std::chrono::system_clock> start, end;
	float elapsed = 0;
	while (!glfwWindowShouldClose(window)) {
		start = std::chrono::system_clock::now();

		glfwPollEvents();

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("Controls");
			ImGui::Text("FPS: %3f", elapsed);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);

		end = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = end - start;
		elapsed = elapsed_seconds.count() * 1000;
	}
}