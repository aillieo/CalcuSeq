#pragma  once

#include "cocos2d.h"
#include "LinkingNode.h"
#include "LinkingNodePair.h"

class Linkage : public cocos2d::Node
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(Linkage);


	void setNodes(LinkingNode* nodeSource, LinkingNode* nodeTarget);
	

	bool hasTarget(LinkingNode* target);

	LinkingNodePair* getLinkingNodePair();

	void updatePosition();

private:


	cocos2d::Sprite* _pathLine;

	cocos2d::Sprite* _pathLine_shadow;
	
	cocos2d::Sprite* _head;

	cocos2d::Sprite* _head_shadow;


	LinkingNode* _nodeSource;
	LinkingNode* _nodeTarget;

	void drawLinkage();



	~Linkage();

};


