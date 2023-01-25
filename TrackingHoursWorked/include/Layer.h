#pragma once

class Layer
{
public:
	virtual ~Layer() = default;

	bool showed = false;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	virtual void OnUIRender() {}
};