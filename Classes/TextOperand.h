#pragma  once

#include "cocos2d.h"
#include "Text.h"

class TextOperand : public Text
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(TextOperand);

	double getValue();
	virtual void setValue(double value, bool bUpdateText);

protected:

	double _value;

	void updateText();
	void updateTextFromValue();
	void updateValue();

	bool _isAppending;

	void processInput(PanelButtonType panelButtonType) override;



	int hasDecimal();
	int getDigitalLength();


	void endInputting();



	cocos2d::EventListenerCustom* _listenerStoreValue;
	cocos2d::EventListenerCustom* _listenerRestoreValue;

	void enableInput(bool input);

	void storeValue(cocos2d::EventCustom* event );
	void restoreValue(cocos2d::EventCustom* event );

	
private:


	std::string& stringReplace(std::string& str,const std::string& old_value,const std::string& new_value);


};


