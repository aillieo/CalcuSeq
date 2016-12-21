#include "PersistenceManager.h"

/*
#include "json/rapidjson.h"  
#include "json/writer.h"
#include "json/document.h"
#include "json/stringbuffer.h"
*/

USING_NS_CC;

using namespace std;




vector<string> PersistenceManager::splitString( const string& str , const std::string& sep )
{

	vector<string> strs;

	if (str.empty())
	{
		return strs;
	}


	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

		while (pos_begin != string::npos)
		{
			comma_pos = str.find(sep, pos_begin);
			if (comma_pos != string::npos)
			{
				tmp = str.substr(pos_begin, comma_pos - pos_begin);
				pos_begin = comma_pos + sep.length();
			}
			else
			{
				tmp = str.substr(pos_begin);
				pos_begin = comma_pos;
			}

			if (!tmp.empty())
			{
				strs.push_back(tmp);
				tmp.clear();
			}
		}
		return strs;
}



bool PersistenceManager::writeFile(const std::string& str, int id)
{

    std::string filename = FileUtils::getInstance()->getWritablePath();
	filename = filename + String::createWithFormat("sCal%2d.dat",id)->getCString();





    auto content = str.c_str();
    

    //向本地写入文件
    FILE *fp = fopen(filename.c_str(), "wb");
    if (fp)
    {
        fwrite(content, 1, strlen(content), fp);
        fclose(fp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("SAVE_SUCCESS");
		return true;
    }
    else
        log("Write failed");
		return false;

}



std::string PersistenceManager::readFile(int id)
{


    std::string filename = FileUtils::getInstance()->getWritablePath();
	filename = filename + String::createWithFormat("sCal%2d.dat",id)->getCString();

	

	//判断文件是否存在  
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		return "" ;
	}

    
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("LOAD_SUCCESS");
    
    return data;

}

    

    
    

