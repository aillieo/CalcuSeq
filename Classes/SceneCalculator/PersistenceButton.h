#pragma  once

#include "cocos2d.h"

class PersistenceButton : public cocos2d::Sprite
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(PersistenceButton);


	void setPersistenceID(int pID);

private:

	//关于触摸事件
	cocos2d::EventListenerTouchOneByOne* _touchListener;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	cocos2d::Sprite* _save;
	cocos2d::Sprite* _load;
	cocos2d::Sprite* _ext;

	int _persistenceID;


};


