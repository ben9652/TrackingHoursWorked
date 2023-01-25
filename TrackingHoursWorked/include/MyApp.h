#pragma once
#include "App.h"

class MyApp : public App
{
public:
	MyApp() = default;
	~MyApp() = default;

	virtual void StartUp() final;
	virtual void Update() final;

	char buf10[100];
	bool ventanaAbierta = true;
private:
	bool show_demo_window = true;
	bool show_another_window = false;
};