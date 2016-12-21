#include "PanelButton.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelButton::init()
{
	 
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("BUTTON90.png");
	setColor(Color3B(127,127,127));
	


	_label = Label::create("NA","font/Simplifica.ttf",60);
	addChild(_label);
	_label->setPosition(getContentSize()/2);

	_sideLabel = Label::create("NA","font/Simplifica.ttf",20);
	addChild(_sideLabel);
	_sideLabel->setPosition(getContentSize()/2);
	_sideLabel->setVisible(false);

	_icon = Sprite::create();
	addChild(_icon);
	_icon->setPosition(getContentSize()/2);
	_icon->setVisible(false);

	//_caption = "NA";
	setType(_panelButtonType);

	return true;
}



void PanelButton::setType(PanelButtonType panelButtonType )
{

	initCaption(panelButtonType);

	

/*
	if (_caption.length()>4)
	{
		_label->setScale(0.5f);
	}
	else if (_caption.length()>3)
	{
		_label->setScale(0.6f);
	}
	else if(_caption.length()>2)
	{
		_label->setScale(0.75f);
	}
	else 
	{
		_label->setScale(0.9f);
	}

	
*/

	switch (_panelButtonType)
	{


	case BUTTON_G_DELETE:
		_label->setVisible(false);
		_icon->setTexture("buttons/button_delete.png");
		_icon->setVisible(true);
		break;





/*		
		case BUTTON_NEGATIVE:
			_caption = "-";
			break;
		case BUTTON_PERCENT:
			_caption = "%";
			break;
		case BUTTON_PI:
			_caption = "pi";
			break;
		case BUTTON_RANDOM:
			_caption = "rdm";
			break;
		case BUTTON_E:
			_caption = "e";
			break;

		case BUTTON_G_CLOSE:
			_caption = "X";
			break;

		case BUTTON_G_CLEAR:
			_caption = "C";
			break;








	


		case BUTTON_D_PLUS:
		case BUTTON_D_MINUS:
		case BUTTON_D_MULTIPLY:
		case BUTTON_D_POWER:
			_label->setScale(1.0f);
			break;

			*/

		case BUTTON_S_RECIPROCAL:
		case BUTTON_S_SQUARE:
		case BUTTON_S_SQROOT:
		case BUTTON_S_SIN:
		case BUTTON_S_COS:
		case BUTTON_S_TAN:
		case BUTTON_S_ASIN:
		case BUTTON_S_ACOS:
		case BUTTON_S_ATAN:
		case BUTTON_S_FACTORIAL:
		case BUTTON_S_TORADIAN:
		case BUTTON_S_TODEGREE:
		case BUTTON_S_EXPONENT:
		case BUTTON_S_SINH:
		case BUTTON_S_COSH:
		case BUTTON_S_TANH:
		case BUTTON_S_LN:
		case BUTTON_S_LOG10:
		case BUTTON_S_LOG2:
		case BUTTON_S_CUBE:
		case BUTTON_S_ABS:
		case BUTTON_S_ROUND:
			_label->setScale(0.85f);
			break;


		case BUTTON_D_DIVIDE:
		case BUTTON_D_EE:
		case BUTTON_D_HIGHER:
		case BUTTON_D_LOWER:
		case BUTTON_D_MOD:
		case BUTTON_D_GROWTH_RATE:
		case BUTTON_D_CHANGE_RATE:
			_label->setScale(0.85f);
			break;





		default:
			break;
	}






}

void PanelButton::setPosInPanel( Point base ,  int x , int y )
{
	setPosition(base + Vec2(90 * x , 90 * y));
}

void PanelButton::onPressed()
{
	
	_eventDispatcher->dispatchCustomEvent("INPUT",&_panelButtonType);

}


TouchManager& PanelButton::getTouchManager()
{
	return _touchManager;
}


PanelButtonType PanelButton::getType()
{
	return _panelButtonType;
}



std::string PanelButton::getCaption()
{
	return _caption;
}

void PanelButton::initCaption(PanelButtonType panelButtonType)
{
	_panelButtonType = panelButtonType;
	
	switch (_panelButtonType)
	{
	case UNDEFINED:
		_caption = "";
	case BUTTON_00:
		_caption = "00";
		break;
	case BUTTON_0:
		_caption = "0";
		break;
	case BUTTON_1:
		_caption = "1";
		break;
	case BUTTON_2:
		_caption = "2";
		break;
	case BUTTON_3:
		_caption = "3";
		break;
	case BUTTON_4:
		_caption = "4";
		break;
	case BUTTON_5:
		_caption = "5";
		break;
	case BUTTON_6:
		_caption = "6";
		break;
	case BUTTON_7:
		_caption = "7";
		break;
	case BUTTON_8:
		_caption = "8";
		break;
	case BUTTON_9:
		_caption = "9";
		break;
	case BUTTON_DECIMAL:
		_caption = ".";
		break;
	case BUTTON_NEGATIVE:
		_caption = "+/-";
		break;
	case BUTTON_PERCENT:
		_caption = "%";
		break;
	case BUTTON_PI:
		_caption = "pi";
		break;
	case BUTTON_RANDOM:
		_caption = "rand";
		break;
	case BUTTON_E:
		_caption = "e";
		break;
	case BUTTON_G_CLOSE:
		_caption = "X";
		break;
	case BUTTON_G_DELETE:
		_caption = "<<";
		break;
	case BUTTON_G_CLEAR:
		_caption = "C";
		break;
	case BUTTON_S_RECIPROCAL:
		_caption = "1/x";
		break;
	case BUTTON_S_SQUARE:
		_caption = "^2";
		break;
	case BUTTON_S_SQROOT:
		_caption = "sqrt";
		break;
	case BUTTON_S_SIN:
		_caption = "sin";
		break;
	case BUTTON_S_COS:
		_caption = "cos";
		break;
	case BUTTON_S_TAN:
		_caption = "tan";
		break;
	case BUTTON_S_ASIN:
		_caption = "asin";
		break;
	case BUTTON_S_ACOS:
		_caption = "acos";
		break;
	case BUTTON_S_ATAN:
		_caption = "atan";
		break;
	case BUTTON_S_FACTORIAL:
		_caption = "x!";
		break;
	case BUTTON_S_TORADIAN:
		_caption = "->Rad";
		break;
	case BUTTON_S_TODEGREE:
		_caption = "->Deg";
		break;
	case BUTTON_D_PLUS:
		_caption = "+";
		break;
	case BUTTON_D_MINUS:
		_caption = "-";
		break;
	case BUTTON_D_MULTIPLY:
		_caption = "*";
		break;
	case BUTTON_D_DIVIDE:
		_caption = "/";
		break;
	case BUTTON_D_POWER:
		_caption = "^";
		break;
	case BUTTON_S_EXPONENT:
		_caption = "exp";
		break;
	case BUTTON_S_SINH:
		_caption = "sinh";
		break;
	case BUTTON_S_COSH:
		_caption = "cosh";
		break;
	case BUTTON_S_TANH:
		_caption = "tanh";
		break;
	case BUTTON_S_LN:
		_caption = "ln";
		break;
	case BUTTON_S_LOG10:
		_caption = "log10";
		break;
	case BUTTON_S_LOG2:
		_caption = "log2";
		break;
	case BUTTON_S_CUBE:
		_caption = "^3";
		break;
	case BUTTON_S_ABS:
		_caption = "abs";
		break;
	case BUTTON_S_ROUND:
		_caption = "int";
		break;
	case BUTTON_D_EE:
		_caption = "EE";
		break;
	case BUTTON_D_HIGHER:
		_caption = "?>";
		break;
	case BUTTON_D_LOWER:
		_caption = "?<";
		break;
	case BUTTON_D_MOD:
		_caption = "mod";
		break;
	case BUTTON_D_GROWTH_RATE:
		_caption = "+%";
		break;
	case BUTTON_D_CHANGE_RATE:
		_caption = "-=%";
		break;

	default:
		break;
	}

	_label->setString(_caption);

}

