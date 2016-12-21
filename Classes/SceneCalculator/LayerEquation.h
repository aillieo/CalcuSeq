#pragma  once

#include "LayerScroll.h"
#include "EquationBuilder.h"
#include "Equation.h"

#include "TouchManager.h"
#include "LayerLinkage.h"


class LayerEquation : public LayerScroll
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LayerEquation);


	virtual std::string toString();
	static LayerEquation* createWithString(const std::string& str);

private:


	void _update(float delta);


	LayerLinkage* _layerLinkage;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);

	void sendOpacityOfHiddenLabel();


	void updateLimitUpper();



	EquationBuilder* _equationBuilder;


	cocos2d::Vector<Equation*> _equations;
	std::vector<unsigned> _equationIDs;


	void addEquation(cocos2d::EventCustom* event);
	void _addEquation(Equation* eq);
	void removeEquation(cocos2d::EventCustom* event);
	//void equationMoveUp(cocos2d::EventCustom* event);
	//void equationMoveDown(cocos2d::EventCustom* event);

    
    cocos2d::Color3B getRandomColor();
    int _lastColor;
    

	void swapPos(Equation* eq1 , Equation* eq2);

	void resortEquations();


    Equation* _eqInDynamicSorting;
    float _eqInDynamicSorting_Y;
    void dynamicSort(cocos2d::EventCustom* event);
    void update(float delta);

	bool _locked;
	void scrollLock(cocos2d::EventCustom* event);

};


