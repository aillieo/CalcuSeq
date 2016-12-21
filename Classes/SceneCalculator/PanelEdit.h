#pragma  once

#include "cocos2d.h"


class PanelEdit : public cocos2d::Node
{
public:

    virtual bool init();  


    CREATE_FUNC(PanelEdit);

	
	//void setAsTop(bool top);
	//void setAsBottom(bool bottom);

	void showItems();
	void hideItems();
	void reverseItems();


private:


	bool _isTop;
	bool _isBottom;


	cocos2d::MenuItemImage* _itemRemove; 
	//cocos2d::MenuItemImage* _itemMoveUp;
	//cocos2d::MenuItemImage* _itemMoveDown;


	void itemRemoveCallback(cocos2d::Ref* pSender);
	//void itemMoveUpCallback(cocos2d::Ref* pSender);
	//void itemMoveDownCallback(cocos2d::Ref* pSender);

};


