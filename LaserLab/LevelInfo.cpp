#include "LevelInfo.h"
#include <string>
#include <iostream>	
#include <fstream>
#include "LevelManager.h"
#include "GameScreen.h"

LevelInfo::LevelInfo(const char* fileName)
{
	std::string * info = loadTXT(fileName);
	label_ = atoi(info[0].c_str());
	isLocked_ = (info[1] != "0");
	bestScore_ = atoi(info[2].c_str());
	threshold_1_ = atoi(info[3].c_str());
	threshold_2_ = atoi(info[4].c_str());
	initialScore_ = atoi(info[5].c_str());
}

int LevelInfo::getLabel()
{
	return label_;
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


int LevelInfo::getInitialScore()
{
	return initialScore_;
}



void LevelInfo::saveToFile()
{
	std::string levelName = "";
	if(load_mode == 0)
	{
		levelName = "Level/level_";
		char numStr[10] = {};
		itoa(label_, numStr, 10);
		std::string num = std::string(numStr);
		levelName += num;
	}
	else
	{
		levelName = "UserLevel/" + user_curr_level;
	}
	levelName += "_info.txt";
	const char * fileName = levelName.c_str();
	std::ofstream saveFile;
	saveFile.open(fileName);
	saveFile << label_ << "\n";
	saveFile << (int)(isLocked_) << "\n";
	saveFile << bestScore_ << "\n";
	saveFile << threshold_1_ << "\n";
	saveFile << threshold_2_ << "\n";
	saveFile << initialScore_;
	saveFile.close();
}


