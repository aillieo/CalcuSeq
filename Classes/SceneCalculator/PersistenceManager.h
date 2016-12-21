#pragma  once

#include "cocos2d.h"

class PersistenceManager : public cocos2d::Node
{
public:



	static std::vector<std::string> splitString(const std::string& str , const std::string& sep);

    
    static bool writeFile(const std::string& str, int id);
    static std::string readFile(int id);

private:



};


