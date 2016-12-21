#pragma  once

#include "LayerUI.h"
#include "PanelInputOperand.h"
#include "PanelInputOperator.h"


class LayerUICal : public LayerUI
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LayerUICal);



private:





	PanelInputOperand* _panelInputOperand;
	PanelInputOperator* _panelInputOperator;


	void showPanelInputOperand(cocos2d::EventCustom* event);
	void showPanelInputOperator(cocos2d::EventCustom* event);


	//void menuQuitCallback(cocos2d::Ref* pSender);


	cocos2d::MenuItemImage* _itemShowLinkages;
	void menuShowLinkagesCallback(cocos2d::Ref* pSender);

/*

	//主菜单相关
	cocos2d::MenuItemToggle* _itemAddLink;
	void addLinkageCallback(cocos2d::Ref* pSender);
	cocos2d::Sprite* _buttonSave;
	cocos2d::Sprite* _buttonLoad;


	void endLinking(cocos2d::EventCustom* event);
*/

};
