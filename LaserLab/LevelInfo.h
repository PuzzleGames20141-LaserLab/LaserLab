#ifndef LEVELINFO_H
#define LEVELINFO_H


class LevelInfo
{
private:
	int label_;
	bool isLocked_;
	int bestScore_;
	int threshold_1_;
	int threshold_2_;
public:
	LevelInfo(const char* fileName);
	int getLabel();
	void lock();
	void unlock();
	bool isLocked();
	void setScore(int currentScore);
	int getStarNum();
	void setThreshold(int t1, int t2);
};

#endif