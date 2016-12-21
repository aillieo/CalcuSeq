#pragma  once

#include "cocos2d.h"
#include "Text.h"


class TextOperator : public Text
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


	// implement the "static create()" method manually
	CREATE_FUNC(TextOperator);

	void setSymbolType(int symbolType);

	void setOperator(PanelButtonType panelButtonType);

	PanelButtonType getOperator();

private:

	void processInput(PanelButtonType panelButtonType) override;



	int _symbolType;

	PanelButtonType _operator;

	void endInputting();

	void updateText();

};


