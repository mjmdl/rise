#include "imgui_layer.hpp"
#include "logger.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace rise {

Imgui_Layer::Imgui_Layer(void *window_handle) : Layer("ImGUI"), window_handle(window_handle) {
	glfwGetWindowSize(reinterpret_cast<GLFWwindow *>(window_handle), reinterpret_cast<int *>(&width), reinterpret_cast<int *>(&height));
}

Imgui_Layer::~Imgui_Layer(void) {
}

void Imgui_Layer::attach(void) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO &io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow *>(window_handle), true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Imgui_Layer::detach(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Imgui_Layer::update(void) {
	float time = (float)glfwGetTime();
	ImGuiIO &io = ImGui::GetIO();
	io.DeltaTime = time > 0.0f ? (time - last_time) : (1.0f / 60.0f);
	last_time = time;
	io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Imgui_Layer::handle_event(Event &event) {
	Event_Dispatcher event_dispatcher(event);
	event_dispatcher.handle<Window_Resize_Event>([this](auto &resize_event) -> bool {
		width = resize_event.width;
		height = resize_event.height;
		return false;
	});
}

} // rise
