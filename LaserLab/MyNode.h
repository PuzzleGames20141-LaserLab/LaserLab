#ifndef MYNODE_H
#define MYNODE_H

class MyNode
{
public:
	MyNode();
	char label;
	int mirrorDir;
	int rowIdx;
	int colIdx;
	int left;
	int up;
	int down;
	int right;
	int currDirection;
};


#endif