#pragma  once


#include "TextOperand.h"

class TextOperandWithLinking : public TextOperand
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(TextOperandWithLinking);


	void setValue(double value, bool bUpdateText);
	void setValue(double value, bool bUpdateText, bool bSetOutOfDate, bool bTransfer);

	//void setValueByLinkage(double value, bool bUpdateText);



private:



	void onRecevieValue(cocos2d::EventCustom* event);

};


