#pragma  once

#include "cocos2d.h"
//#include "LayerLinkage.h"
#include "LayerEquation.h"
#include "LayerUICal.h"
#include "LayerHelpCal.h"


class SceneCalculator : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(SceneCalculator);



private:

	SceneCalculator();
	~SceneCalculator();


	cocos2d::Label* _hiddenLable;
	void adjustHiddenLable(cocos2d::EventCustom* event);

	//LayerLinkage* _layerLinkage;
	LayerEquation* _layerEquation;

	LayerHelpCal* _layerHelpCal;


	void displayHelpInfo(cocos2d::EventCustom* event);

	void saveScene(cocos2d::EventCustom* event);
	void loadScene(cocos2d::EventCustom* event);

};


