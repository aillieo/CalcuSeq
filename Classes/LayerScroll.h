#pragma  once

#include "cocos2d.h"



class LayerScroll : public cocos2d::Layer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LayerScroll);


protected:

	void scrollTo(float posY);


	virtual void updateLimitUpper();

	float _limitBottom;
	float _limitUpper;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);


	virtual void _update(float delta);

private:
	
	float _velocityY;
	float _resistanceY;
	float _elasticY;



	void performFriction();

	void performElasticOnMoving();
	void performElasticOnReleased();

	bool _scrollUpdating;

};


