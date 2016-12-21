#pragma  once

#include "cocos2d.h"
#include "TouchManager.h"



class LayerPersistenceCal : public cocos2d::Layer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LayerPersistenceCal);



private:


	bool _shown;
	bool _updating;

	//cocos2d::EventListenerTouchOneByOne* _touchListener;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	cocos2d::Label* _label;

	cocos2d::Sprite* _bg;

	void update(float delta);

	void onSaveSucceed(cocos2d::EventCustom* event);
	void onLoadSucceed(cocos2d::EventCustom* event);

};
