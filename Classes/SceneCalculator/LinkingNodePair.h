#pragma  once

#include "LinkingNode.h"


class LinkingNodePair : public cocos2d::Node
{
public:

	CREATE_FUNC(LinkingNodePair);

	LinkingNode* linkingNodeSource;
	LinkingNode* linkingNodeTarget;

private:


	LinkingNodePair();
	~LinkingNodePair();


};


