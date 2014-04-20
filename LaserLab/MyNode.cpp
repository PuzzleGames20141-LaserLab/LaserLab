#include "MyNode.h"
#include "iostream"

MyNode::MyNode()
{
	rowIdx = -1;
	colIdx = -1;
	up = -2;
	down = -2;
	left = -2;
	right = -2;
	currDirection = -1;
	parent = NULL;
	hit = 0;
}