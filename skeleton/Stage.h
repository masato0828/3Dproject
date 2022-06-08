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
public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();

	bool MapLoder(std::string fileName);
protected:

};

