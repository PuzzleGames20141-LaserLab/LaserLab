#include "LevelInfo.h"
#include "Grid.h"
#include <string>
#include <iostream>	

LevelInfo::LevelInfo(const char* fileName)
{
	std::string * info = loadTXT(fileName);
	label_ = atoi(info[0].c_str());
	isLocked_ = (info[1] != "0");
	bestScore_ = atoi(info[2].c_str());
	threshold_1_ = atoi(info[3].c_str());
	threshold_2_ = atoi(info[4].c_str());
}

void LevelInfo::lock()
{
	isLocked_ = true;
}

void LevelInfo::unlock()
{
	isLocked_ = false;
}

void LevelInfo::setScore(int currentScore)
{
	bestScore_ = bestScore_ < currentScore ? currentScore : bestScore_;
}

int LevelInfo::getStarNum()
{
	if(isLocked_) return -1;
	if(bestScore_ == 0) return 0;
	else if(bestScore_ < threshold_1_) return 1;
	else if(bestScore_ < threshold_2_) return 2;
	else return 3;
}
	
void LevelInfo::setThreshold(int t1, int t2)
{
	threshold_1_ = t1;
	threshold_2_ = t2;
}

