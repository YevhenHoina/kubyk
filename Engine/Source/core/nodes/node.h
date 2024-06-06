#pragma once
#include <string>

class node
{
public:
	//order for nodes to work
	int order = 0;

	bool isOpen = true;
	std::string title = "Node";

	float nodeSizeX = 200.0f;
	float nodeSizeY = 130.5f;

	float nodePosX = 550.0f;
	float nodePosY = 250.0f;

	node(float x, float y) : nodePosX(x), nodePosY(y) {};
	bool isMovable = true;

	
	virtual void nodeAction() {};
};

