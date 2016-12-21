#pragma  once

#include "cocos2d.h"
#include "LinkingNode.h"
#include "Linkage.h"

class LinkingManager : public cocos2d::Node
{
public:

	static LinkingManager* getInstance();

	static void destroyInstance();

	void reset();

	cocos2d::Vector<LinkingNode*> allLinkingNodes;

	cocos2d::Vector<Linkage*> allLinkages;


	void resortNodes();
	void resortNodeIDs();

private:


	LinkingManager();

	static LinkingManager*  _linkingManager;

};


