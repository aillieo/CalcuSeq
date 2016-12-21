#pragma  once

#include "cocos2d.h"


class LinkingIdentifier : public cocos2d::Node
{
public:

    virtual bool init();  


    CREATE_FUNC(LinkingIdentifier);


	void showAsTarget();
	void showAsSource();
	void hideIdentifier();

private:

	cocos2d::Sprite* _inner_1;
	cocos2d::Sprite* _inner_2;

};


