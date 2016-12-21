#include "PanelInputOperator.h"


USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelInputOperator::init()
{
     
    // 1. super init first
    if ( !PanelInput::init() )
    {
        return false;
    }
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    setTexture("BLANK.png");
    setTextureRect(Rect(0,0,720,270));

    initButtons();

    return true;
}

void PanelInputOperator::initButtons()
{

	//背景格子 
	for (int i = 0 ; i <= 24 ; i ++)
	{
		Sprite* pb = Sprite::create();
		pb->setTexture("BUTTON90_EMPTY.png");

		pb->setColor(Color3B(127,127,127));


		addChild(pb);
		pb->setPosition(45 + (i%8) * 90 , 45+ ((i-1)/8) * 90);
	}





	_buttonPad[0] = Node::create();
	addChild(_buttonPad[0]);
	_buttonPad[1] = Node::create();
	addChild(_buttonPad[1]);


	Point _base = Point(-45,-45);



/*	//按钮隐藏 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_G_CLOSE);
		addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,1);
	}
*/

	
	//单运算数的运算符 
	
	//倒数 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_RECIPROCAL);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,3);
	}
	//平方 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_SQUARE);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 3,3);
	}
	//开方 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_SQROOT);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,3);
	}
	//阶乘 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_FACTORIAL);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 6,3);
	}
	//to deg 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_TODEGREE);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 7,2);
	}
	//to rad 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_TORADIAN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 8,2);
	}



	//正弦 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_SIN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,2);
	}
	//余弦 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_COS);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,2);
	}
	//正切 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_TAN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 3,2);
	}
	//反正弦 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_ASIN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 4,2);
	}
	//反余弦 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_ACOS);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 5,2);
	}
	//反正切 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_ATAN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 6,2);
	}

	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_CUBE);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 4,3);
	}


	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_SINH);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_COSH);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_TANH);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 3,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_LN);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 4,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_LOG10);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 6,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_LOG2);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 5,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_ABS);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 7,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_ROUND);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 8,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_S_EXPONENT);
		_buttonPad[0]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 5,3);
	}

	



	//双运算数的运算符 
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_PLUS);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,3);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_MINUS);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,3);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_MULTIPLY);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 3,3);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_DIVIDE);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 4,3);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_POWER);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 5,3);
	}

	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_EE);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 6,3);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_HIGHER);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_LOWER);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,1);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_MOD);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 7,3);
	}

	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_GROWTH_RATE);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 1,2);
	}
	{
		PanelButton* pb = PanelButton::create();
		pb->setType(PanelButtonType::BUTTON_D_CHANGE_RATE);
		_buttonPad[1]->addChild(pb);
		_buttons.pushBack(pb);
		pb->setPosInPanel(_base , 2,2);
	}

}

void PanelInputOperator::setSymbolType( int symbolType )
{

	_buttonPad[symbolType-1]->setVisible(true);
	_buttonPad[2-symbolType]->setVisible(false);

}
