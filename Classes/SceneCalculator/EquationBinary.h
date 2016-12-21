#pragma  once

#include "cocos2d.h"
#include "Equation.h"
#include "TextOperator.h"

class EquationBinary : public Equation
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(EquationBinary);

	//void enableTouch(bool touch);
	void onRemove();

	//void setEquationID(unsigned equationID);

	virtual std::string toString();
	static EquationBinary* createWithString(const std::string& eq_string);

private:

	TextHolder* _textHolderOperator;
	TextOperator* _textOperator;
	TextHolderWithLinking* _textHolderOperand_1;
	TextOperandWithLinking* _textOperand_1;
	TextHolderWithLinking* _textHolderOperand_2;
	TextOperandWithLinking* _textOperand_2;

	void _compute();
	void _setEquationOutOfDate();
	void updateHolderColor();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);



};


