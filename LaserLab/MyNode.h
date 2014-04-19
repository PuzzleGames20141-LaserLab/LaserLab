#ifndef MYNODE_H
#define MYNODE_H

class MyNode
{
public:
	MyNode();
	char label; // indicate what kind of equipment it is. ' ' for empty
	int mirrorDir; // if it's mirror, the direction of the mirror
	int splitterDir; // if it's splitter, the direction
	int rowIdx; // row #
	int colIdx; // column #
	int left; // level depth on left direction
	int up; // level depth on left direction
	int down; // level depth on left direction
	int right; //level depth on left direction
	int currDirection; // current direction of the node
};


#endif