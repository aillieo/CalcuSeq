#pragma  once

#include "cocos2d.h"
#include "Text.h"
#include "TouchManager.h"


class TextHolder : public cocos2d::Sprite
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(TextHolder);


	void enableInput(bool input);
	
    void initText(Text* text);

	enum HolderType
	{
		NOT_INPUT,
		OPERAND,
		OPERATOR_BINARY,
		OPERATOR_UNARY
	} holderType;

	Text* getText();

protected:

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	Text* _text;

	TouchManager _touchManager;

	bool _inputting;

	void checkPanelTypeToShow(bool show);

	void resetInputState(cocos2d::EventCustom* event);

};


