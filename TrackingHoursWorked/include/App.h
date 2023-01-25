#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>
#include <memory>
#include <Layer.h>
#include <Windows.h>

class App
{
public:
	virtual ~App();

	void Run();
	void SetFlagToClose();
	void Close();
	void Shutdown();

	static App& Get();

	template<typename T>
	void PushLayer()
	{
		static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
		m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
	}

	void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

	void PopLayer() { m_LayerStack.at(m_LayerStack.size() - 1)->OnDetach(); m_LayerStack.pop_back(); }

	friend App* CreateApplication(int argc, char** argv);

	void ModifyWindowSize(int _x, int _y);
	void CenterWindow();

private:
	App();
	std::vector<std::shared_ptr<Layer>> m_LayerStack;

protected:
	HWND windowHandle;
	static App* singleton;
	GLFWwindow* window;
	ImVec4 clear_color;
};