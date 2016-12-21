#pragma  once

#include "cocos2d.h"
#include "PanelButtonType.h"

class Text : public cocos2d::Node
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    //CREATE_FUNC(Text);


	virtual void enableInput(bool input);

	//cocos2d::EventListenerCustom* getInputListener();

	void setEquationID(unsigned equationID);

	std::string getTextString();

    void setTextColor(cocos2d::Color3B c3b);
    
protected:

	unsigned _equationID;

	cocos2d::Label* _labelText;

	std::string _text;

	


	cocos2d::EventListenerCustom* _listenerInput;

	void onEventInput(cocos2d::EventCustom* event);
	

	virtual void processInput(PanelButtonType panelButtonType) ;

	virtual void endInputting();
	

};


