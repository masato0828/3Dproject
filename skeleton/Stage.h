#pragma once
#include <string>
#include <unordered_map>
#include <list>
class Stage
{
private:

	int LineCounter;
	int linecount;

	std::unordered_multimap < std::string, std::pair<VECTOR ,VECTOR>> filedate;

	std::list<int> modeldata;

	// キー値の格納（仮）
	std::unordered_map<std::string, int> keymap;

	double angle;


	int testmHndle;
	VECTOR angle_;

public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();

	bool MapLoder(std::string fileName);

	VECTOR DegRadVGet(double x, double y, double z );
protected:

};

