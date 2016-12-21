#pragma  once

#include "cocos2d.h"
#include "TextHolderWithLinking.h"
#include "TouchManager.h"
#include "TextOperandWithLinking.h"
#include "PanelEdit.h"
#include "ButtonCompute.h"


class Equation : public cocos2d::Sprite
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(Equation);

	unsigned getEquationID();
	virtual void setEquationID(unsigned equationID);

	//virtual void enableTouch(bool touch);

	virtual void onRemove();

	void setPosInLayer(cocos2d::Point pos);
	void updatePosition();
	//void setPosInSeq(bool isTop, bool isBottom);


	virtual std::string toString();
	static Equation* createWithString(const std::string& eq_string);

    
    void setEquationColor(cocos2d::Color3B c3b);

protected:

	ButtonCompute* _buttonCompute;

	cocos2d::Sprite* _bg1;
	cocos2d::Sprite* _bg2;

	bool _computed;

	cocos2d::Point _posInLayer;

	TextHolderWithLinking* _textHolderResult;
	TextOperandWithLinking* _textResult;

	//virtual void compute(cocos2d::Ref* pSender);
	virtual void compute(cocos2d::EventCustom* event);
	virtual void _compute();
    

    cocos2d::EventListenerTouchOneByOne* _touchListener;
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);
    
	TouchManager _touchManager;
    
    bool _willLeadToDynamicSort;

	virtual void _setEquationOutOfDate();
	virtual void updateHolderColor();

private:
    
    int _equationID;

    
	void setEquationOutOfDate(cocos2d::EventCustom* event);


    
    void onLongPressed();
    
    void update(float delta);
    
	//cocos2d::MenuItem* _itemRemove;
	//cocos2d::MenuItem* _itemMoveUp;
	//cocos2d::MenuItem* _itemMoveDown;
    

	void onExit();
	


	PanelEdit* _panelEdit;
    bool _moveWithPanelEdit;


    bool _inDynamicSorting;


};


