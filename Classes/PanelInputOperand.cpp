#include "PanelInputOperand.h"

#include "ModuleStorage.h"

#include "PanelButtonStore.h"
#include "PanelButtonRestore.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelInputOperand::init()
{
	 
	// 1. super init first
	if ( !PanelInput::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,720,360));

	initButtons();

	return true;
}

void PanelInputOperand::initButtons()
{


	//背景格子 
	for (int i = 0 ; i <= 20 ; i ++)
	{
		Sprite* pb = Sprite::create();
		pb->setTexture("BUTTON90_EMPTY.png");

		pb->setColor(Color3B(127,127,127));
	
		addChild(pb);
		pb->setPosition(45 + (i%5) * 90 , 45+ ((i-1)/5)* 90);
	}





	Point _base = Point(-45,-45);



	//按钮 1 到 9 
	for (int i = 1 ; i <= 9 ; i ++)
	{
		PanelButton* pb = PanelButton::create();
		pb->setType((PanelButtonType)i);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1+(i-1)%3 , 2+(i-1)/3);
	}



/*	//按钮隐藏 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_G_CLOSE);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,1);
	}
*/



	//按钮0 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_0);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 3,1);
	}

	//按钮00 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_00);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 4,1);
	}

	//按钮小数点 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_DECIMAL);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 2,1);
	}


	//退格 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_G_DELETE);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 4,4);
	}


	//清空 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_G_CLEAR);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 4,3);
	}


	//负号 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_NEGATIVE);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 4,2);
	}


	//百分号 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_PERCENT);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 5,1);
	}


	//输入 pi 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_PI);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 5,4);
	}


	//输入 e 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_E);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 5,3);
	}

	
	//输入 随机数 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_RANDOM);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base, 5,2);
	}



	//四个存储模块
	for (int i=0;i<4;i++)
	{
		ModuleStorage* ms = ModuleStorage::create();
		addChild(ms);
		
		PanelButtonStore* pbs = PanelButtonStore::create();
		_buttons.pushBack(pbs);
		PanelButtonRestore* pbr = PanelButtonRestore::create();
		_buttons.pushBack(pbr);
		ms->initComponents(pbs , pbr);
		ms->setStorageIndex(i);
		
		ms->setPosition(5*90+45,45+90*i);

	}


}
