#pragma  once

#include "cocos2d.h"

class EquationBuilder : public cocos2d::Sprite
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(EquationBuilder);

	void setPosInLayer(cocos2d::Point posInLayer);

	void updatePosition();

private:

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	cocos2d::Sprite* _left;
	cocos2d::Sprite* _right;

	cocos2d::Point _posInLayer;



};


