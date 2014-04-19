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


bool GameScreen::autoSolver(sf::RenderWindow& window)
{
	// 2-Dimension vector to save all the current equipments on the grid
	std::vector<std::vector<MyNode>> nodeGrid;
	// vector initialization
	for(int i = 0; i != 12; i++)
	{
		std::vector<MyNode> rowNode;
		for(int j = 0; j != 15; j++)
		{	
			MyNode curr;
			curr.rowIdx = i;
			curr.colIdx = j;
			rowNode.push_back(curr);
		}
		nodeGrid.push_back(rowNode);
	}
	// visited map for BFS
	bool visited[12][15] = {false};
	// Queue for BFS
	std::queue<MyNode> myQueue;
	// target position
	int end_row;
	int end_col;
	// initial direction of the light(laserSource)
	int initialDir;

	// add all the equipments on grid to the 2-D vector, each node actually records the level depth of one block in 4 directions separately.
	std::map<int, std::shared_ptr<Equipment>> :: iterator it = GameScreen::tool_manager.equipments_on_grid_.begin();
	for(; it != GameScreen::tool_manager.equipments_on_grid_.end(); it++)
	{
		int row = (*it).first/GRID_WIDTH;
		int col = (*it).first%GRID_WIDTH;
		switch((*it).second->label)
		{
			case LASER_SOURCE_U_RED: 
			{
				nodeGrid[row][col].label = LASER_SOURCE_U_RED;
				int dir = (int)((360 - (*it).second->getRotation()) / 90) % 4;
				// switch the direction of laserSource
				switch(dir)
				{
					case 0:
					{
						nodeGrid[row][col].right = -1; // if right, the node represent the laserSource has a -1 depth on right direction
						nodeGrid[row][col].currDirection = 0; // currDirection set to right
						break;
					}
					case 1:
					{
						nodeGrid[row][col].up = -1;
						nodeGrid[row][col].currDirection = 1;	
						break;
					}
					case 2:
					{
						nodeGrid[row][col].left = -1;
						nodeGrid[row][col].currDirection = 2;	
						break;
					}
					case 3:
					{
						nodeGrid[row][col].down = -1;
						nodeGrid[row][col].currDirection = 3;	
						break;
					}
				}
				// laserSource is the root node of depth -1. push it into queue
				myQueue.push(nodeGrid[row][col]);
				break;
			}
			// if there is mirror already on grid, save the direction.
			case MIRROR:
			{
				nodeGrid[row][col].label = MIRROR;
				nodeGrid[row][col].mirrorDir = (int)(((*it).second ->getRotation())/90);
			}
			default:
			{
				nodeGrid[row][col].label = (*it).second->label;
				break;
			}
		}
	}

// start of the BFS
loop: while(!myQueue.empty())
	{
		//dequeu
		MyNode curr = myQueue.front();
		myQueue.pop();
		visited[curr.rowIdx][curr.colIdx] = true;
		// if the dequeud node is the laserSource, the following "if block" only excute once
		if(curr.label == LASER_SOURCE_U_RED)
		{
			int currDir = curr.currDirection; // current direction of the light(node)
			int row = curr.rowIdx; // current row # of the node
			int col = curr.colIdx; // current col # of the node
			// switch the direction of laserSource and move 1 step accordingly
			switch(currDir)
			{
			case 0: col++; break;
			case 1: row--; break;
			case 2: col--; break;
			case 3: row++; break;
			default: break;
			}
			// while loop when the light has not go out of the boundary and also has not terminated by wall or mirror.
			while(row >= 0 && row <= 11 && col >= 0 && col <= 14)
			{
				// find the target with exsiting equipments
				if(nodeGrid[row][col].label == DOOR_U_RED)
				{
					return true;
				}
				// the light occurs mirror
				else if(nodeGrid[row][col].label == MIRROR)
				{
					// turn the light according to the direction of the mirror, or break out if the mirror block the light
					switch(nodeGrid[row][col].mirrorDir)
					{
						case 0:
						{
							if(currDir == 0)
							{
								currDir = 3;
								row++;
								continue;
							}
							else if(currDir == 1)
							{
								currDir = 2;
								col--;
								continue;
							}
							else
							{
								goto loop; // break out, terminate searching from LaserSource
							}
							break;
						}
						case 1:
						{
							if(currDir == 0)
							{
								currDir = 1;
								row--;
								continue;
							}
							else if(currDir == 3)
							{
								currDir = 2;
								col--;
								continue;
							}
							else
							{
								goto loop; // break out, terminate searching from LaserSource
							}
							break;
						}
						case 2:
						{
							if(currDir == 3)
							{
								currDir = 0;
								col++;
								continue;
							}
							else if(currDir == 2)
							{
								currDir = 1;
								row--;
								continue;
							}
							else
							{
								goto loop; // break out, terminate searching from LaserSource
							}
							break;
						}
						case 3:
						{
							if(currDir == 1)
							{
								currDir = 0;
								col++;
								continue;
							}
							else if(currDir == 2)
							{
								currDir = 3;
								row++;
								continue;
							}
							else
							{
								goto loop; // break out, terminate searching from LaserSource
							}
							break;
						}
					}
				}
				else if(nodeGrid[row][col].label != ' ')
				{
					goto loop; // break out, terminate searching from LaserSource
				}
				else // the current block is empty
				{
					nodeGrid[row][col].currDirection = currDir; // assign direction to current node
					// assign level depth to the corresponding direction of current node
					switch(currDir)
					{
					case 0: nodeGrid[row][col].right = 0; break;
					case 1: nodeGrid[row][col].up = 0; break;
					case 2: nodeGrid[row][col].left = 0; break;
					case 3: nodeGrid[row][col].down = 0; break;
					default: break;
					}
					// if the node is still in bound and not visited, push into queue
					if(row >= 0 && row <= 11 && col >= 0 && col <= 14 && !visited[row][col])
					{
						myQueue.push(nodeGrid[row][col]);
					}
					// move one step accordingly
					switch(currDir)
					{
						case 0: col++; break;
						case 1: row--; break;
						case 2: col--; break;
						case 3: row++; break;
						default: break;
					}
				}
			}
		}
		// if the dequeued node is not LaserSource, the following code always be excuted except for the first time which the node must be a laserSource 
		else
		{
			// for each node there are 2 possibilities to be reflected to.
			// search both directions
			int currTurn; // current level depth(number of extra mirrors needed)
			int currDir = curr.currDirection;
			int currDir_first; // direction of first explore
			int currDir_second; // direction fo second explore
			// start point of first explore
			int row_first = curr.rowIdx;
			int col_first = curr.colIdx;
			// start point of second explore
			int row_second = curr.rowIdx;
			int col_second = curr.colIdx;

			// initialize the 2 directions to be explored
			switch(currDir)
			{
			case 0:
				{
					row_first--;
					row_second++;
					currDir_first = 1;
					currDir_second = 3;
					currTurn = curr.right; // assign previous level depth to the current depth
					break;
				}
			case 1:
				{
					col_first--;
					col_second++;
					currDir_first = 2;
					currDir_second = 0;
					currTurn = curr.up;
					break;
				}
			
			case 2:
				{
					row_first--;
					row_second++;
					currDir_first = 1;
					currDir_second = 3;
					currTurn = curr.left;
					break;
				}
			case 3:
				{
					col_first--;
					col_second++;
					currDir_first = 2;
					currDir_second = 0;
					currTurn = curr.down;
					break;
				}
			default:break;
			}

			// if previous level depth + 1 exceed the balance, return false
			if(currTurn+1 > currentScore/10)
				return false;
			
			// first explore, almost the same with the loop dealing with laserSource
			while(row_first>=0 && row_first<=11 && col_first>=0 && col_first<=14)
			{
				if(nodeGrid[row_first][col_first].label == DOOR_U_RED)
					return true;
				
				else if(nodeGrid[row_first][col_first].label == MIRROR)
				{
					switch(nodeGrid[row_first][col_first].mirrorDir)
					{
						case 0:
						{
							if(currDir_first == 0)
							{
								currDir_first = 3;
								row_first++;
								continue;
							}
							else if(currDir_first == 1)
							{
								currDir_first = 2;
								col_first--;
								continue;
							}
							else
							{
								goto secondloop;
							}
							break;
						}

						case 1:
						{
							if(currDir_first == 0)
							{
								currDir_first = 1;
								row_first--;
								continue;
							}
							else if(currDir_first == 3)
							{
								currDir_first = 2;
								col_first--;
								continue;
							}
							else
							{
								goto secondloop;
							}
							break;
						}

						case 2:
						{
							if(currDir_first == 3)
							{
								currDir_first = 0;
								col_first++;
								continue;
							}
							else if(currDir_first == 2)
							{
								currDir_first = 1;
								row_first--;
								continue;
							}
							else
							{
								goto secondloop;
							}
							break;
						}

						case 3:
						{
							if(currDir_first == 1)
							{
								currDir_first = 0;
								col_first++;
								continue;
							}
							else if(currDir_first == 2)
							{
								currDir_first = 3;
								row_first++;
								continue;
							}
							else
							{
								goto secondloop;
							}
							break;
						}
					}
				}	
				else if(nodeGrid[row_first][col_first].label != ' ')
					goto secondloop;

				else
				{
					nodeGrid[row_first][col_first].currDirection = currDir_first;
					switch(currDir_first)
					{
					case 0: nodeGrid[row_first][col_first].right = currTurn+1; break;
					case 1: nodeGrid[row_first][col_first].up = currTurn+1; break;
					case 2: nodeGrid[row_first][col_first].left = currTurn+1; break;
					case 3: nodeGrid[row_first][col_first].down = currTurn+1; break;
					default: break;
					}
					if(row_first >= 0 && row_first <= 11 && col_first >= 0 && col_first <= 14 && !visited[row_first][col_first])
					{
						myQueue.push(nodeGrid[row_first][col_first]);
					}
					switch(currDir_first)
					{
						case 0: col_first++; break;
						case 1: row_first--; break;
						case 2: col_first--; break;
						case 3: row_first++; break;
						default: break;
					}
				}
			}

			// second explore, almost the same with the first explore
secondloop : while(row_second>=0 && row_second<=11 && col_second>=0 && col_second<=14)
			{
				if(nodeGrid[row_second][col_second].label == DOOR_U_RED)
					return true;
				
				else if(nodeGrid[row_second][col_second].label == MIRROR)
				{
					switch(nodeGrid[row_second][col_second].mirrorDir)
					{
						case 0:
						{
							if(currDir_second == 0)
							{
								currDir_second = 3;
								row_second++;
								continue;
							}
							else if(currDir_second == 1)
							{
								currDir_second = 2;
								col_second--;
								continue;
							}
							else
							{
								goto loop;
							}
							break;
						}

						case 1:
						{
							if(currDir_second == 0)
							{
								currDir_second = 1;
								row_second--;
								continue;
							}
							else if(currDir_second == 3)
							{
								currDir_second = 2;
								col_second--;
								continue;
							}
							else
							{
								goto loop;
							}
							break;
						}

						case 2:
						{
							if(currDir_second == 3)
							{
								currDir_second = 0;
								col_second++;
								continue;
							}
							else if(currDir_second == 2)
							{
								currDir_second = 1;
								row_second--;
								continue;
							}
							else
							{
								goto loop;
							}
							break;
						}

						case 3:
						{
							if(currDir_second == 1)
							{
								currDir_second = 0;
								col_second++;
								continue;
							}
							else if(currDir_second == 2)
							{
								currDir_second = 3;
								row_second++;
								continue;
							}
							else
							{
								goto loop;
							}
							break;
						}
					}

			
				}	
				else if(nodeGrid[row_second][col_second].label != ' ')
					goto loop;

				else
				{
					nodeGrid[row_second][col_second].currDirection = currDir_second;
					switch(currDir_second)
					{
					case 0: nodeGrid[row_second][col_second].right = currTurn+1; break;
					case 1: nodeGrid[row_second][col_second].up = currTurn+1; break;
					case 2: nodeGrid[row_second][col_second].left = currTurn+1; break;
					case 3: nodeGrid[row_second][col_second].down = currTurn+1; break;
					default: break;
					}
					if(row_second >= 0 && row_second <= 11 && col_second >= 0 && col_second <= 14 && !visited[row_second][col_second])
					{
						myQueue.push(nodeGrid[row_second][col_second]);
					}
					switch(currDir_second)
					{
						case 0: col_second++; break;
						case 1: row_second--; break;
						case 2: col_second--; break;
						case 3: row_second++; break;
						default: break;
					}
				}
			}
		}
	}
	// haven't found the target after we explored every block on the grid, return false.
	return false;
}