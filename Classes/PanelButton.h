#pragma once

#include "cocos2d.h"
#include "TouchManager.h"
#include "PanelButtonType.h"


class PanelButton : public cocos2d::Sprite
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


	// implement the "static create()" method manually
	CREATE_FUNC(PanelButton);

	void setType(PanelButtonType panelButtonType);

	PanelButtonType getType();

	void setPosInPanel(cocos2d::Point base , int x , int y);

	TouchManager& getTouchManager();

	virtual void onPressed();

	std::string getCaption();



protected:

	//关于触摸事件
	TouchManager _touchManager;

	std::string _caption;

	cocos2d::Label* _label;
	cocos2d::Label* _sideLabel;
	cocos2d::Sprite* _icon;

	PanelButtonType _panelButtonType;

	void initCaption(PanelButtonType panelButtonType);

};


