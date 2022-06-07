#pragma once
#include <string>
#include <map>
class Stage
{
private:

	int LineCounter;
	int linecount;

	std::map < std::string, std::pair<VECTOR ,VECTOR>> filedate;
public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();

	bool MapLoder(std::string fileName);
protected:

};

