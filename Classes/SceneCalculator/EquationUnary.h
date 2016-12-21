#pragma  once

#include "cocos2d.h"
#include "Equation.h"
#include "TextOperator.h"

class EquationUnary : public Equation
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


	// implement the "static create()" method manually
	CREATE_FUNC(EquationUnary);

	//void enableTouch(bool touch);

	void onRemove();

	//void setEquationID(unsigned equationID);


	virtual std::string toString();
	static EquationUnary* createWithString(const std::string& eq_string);

private:


	//TextHolder* _textHolderOperator;
	//void preposeOperator(cocos2d::EventCustom* event);


	//TextHolder* _holderOperator;

	TextHolder* _textHolderOperator;
	TextOperator* _textOperator;
	TextHolderWithLinking* _textHolderOperand;
	TextOperandWithLinking* _textOperand;

	void _setEquationOutOfDate();
	void updateHolderColor();
	void _compute();
    
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);


};


