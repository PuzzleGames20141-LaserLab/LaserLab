#ifndef MYNODE_H
#define MYNODE_H

class MyNode
{
public:
	MyNode();
	MyNode *parent;
	int rowIdx;
	int colIdx;
	int left;
	int up;
	int down;
	int right;
	int currDirection;
	int hit;
};


#endif