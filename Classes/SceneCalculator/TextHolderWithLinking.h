#pragma  once

#include "TextHolder.h"
#include "LinkingNode.h"
#include "LinkingManager.h"


class TextHolderWithLinking : public TextHolder
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(TextHolderWithLinking);



	LinkingNode* getLinkingNode();

	void initLinkingNode(LinkingNode* linkingNode);

	//void destroyLinkingNode();

	//void passEquationID(unsigned equationID);

	bool initWithString(const std::string& str);
	std::string toString();


private:


	void buildLinkage(LinkingNode* source , LinkingNode* target);

	//cocos2d::EventListenerTouchOneByOne* _touchListener;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	void onLongPressed();

	bool _searchingForTarget;
	LinkingNode* _potentialTarget;


	LinkingManager* _linkingManager;

	LinkingNode* _linkingNode;

	void update(float delta);

};


