#include "TextOperator.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool TextOperator::init()
{
	 
	// 1. super init first
	if ( !Text::init() )
	{
		return false;
	}



	_symbolType = 2;

	_operator = PanelButtonType::UNDEFINED;

	return true;
}



void TextOperator::processInput(PanelButtonType panelButtonType)
{

	if (panelButtonType==BUTTON_G_CLOSE)
	{
		endInputting();
		return;
	}
	


	if((panelButtonType!=BUTTON_G_CLOSE)&&(panelButtonType!=_operator))
	{

        _eventDispatcher->dispatchCustomEvent("SET_EQUATION_OUT_OF_DATE",getParent()->getParent());

	}

	_operator = panelButtonType;
	updateText();


	//bool preposeOperator = false;


	switch (_operator)
	{

		case BUTTON_S_RECIPROCAL:
		case BUTTON_S_SQROOT:
		case BUTTON_S_SIN:
		case BUTTON_S_COS:
		case BUTTON_S_TAN:
		case BUTTON_S_ASIN:
		case BUTTON_S_ACOS:
		case BUTTON_S_ATAN:
		case BUTTON_S_EXPONENT:
		case BUTTON_S_SINH:
		case BUTTON_S_COSH:
		case BUTTON_S_TANH:
		case BUTTON_S_LN:
		case BUTTON_S_LOG10:
		case BUTTON_S_LOG2:
		case BUTTON_S_ABS:
		case BUTTON_S_ROUND:

			//preposeOperator = true;
			getParent()->setPositionX(getParent()->getParent()->getContentSize().width / 2 - 270);
			break;

		case BUTTON_S_SQUARE:
		case BUTTON_S_CUBE:
		case BUTTON_S_FACTORIAL:
		case BUTTON_S_TORADIAN:
		case BUTTON_S_TODEGREE:
			getParent()->setPositionX(getParent()->getParent()->getContentSize().width / 2 );
			break;
		default:
			break;
	}

	//_eventDispatcher->dispatchCustomEvent("PREPOSE_OPORATOR",&preposeOperator);


	endInputting();


}


void TextOperator::setSymbolType( int symbolType )
{
	_symbolType = symbolType;
}

PanelButtonType TextOperator::getOperator()
{
	return _operator;
}


void TextOperator::endInputting()
{
	int show = 0;
	_eventDispatcher->dispatchCustomEvent("SHOW_PANEL_INPUT_OPERATOR",&show);
	_eventDispatcher->dispatchCustomEvent("RESET_HOLDER");
	enableInput(false);
}



void TextOperator::updateText()
{
	switch (_operator)
	{

		case BUTTON_S_RECIPROCAL:
			_text = "1/";
			break;
		case BUTTON_S_SQUARE:
			_text = "^2";
			break;
		case BUTTON_S_SQROOT:
			_text = "sqrt";
			break;
		case BUTTON_S_SIN:
			_text = "sin";
			break;
		case BUTTON_S_COS:
			_text = "cos";
			break;
		case BUTTON_S_TAN:
			_text = "tan";
			break;
		case BUTTON_S_ASIN:
			_text = "asin";
			break;
		case BUTTON_S_ACOS:
			_text = "acos";
			break;
		case BUTTON_S_ATAN:
			_text = "atan";
			break;
		case BUTTON_S_FACTORIAL:
			_text = "!";
			break;
		case BUTTON_S_TORADIAN:
			_text = "->Rad";
			break;
		case BUTTON_S_TODEGREE:
			_text = "->Deg";
			break;
		case BUTTON_D_PLUS:
			_text = "+";
			break;
		case BUTTON_D_MINUS:
			_text = "-";
			break;
		case BUTTON_D_MULTIPLY:
			_text = "*";
			break;
		case BUTTON_D_DIVIDE:
			_text = "/";
			break;
		case BUTTON_D_POWER:
			_text = "^";
			break;

		case BUTTON_S_EXPONENT:
			_text = "exp";
			break;
		case BUTTON_S_SINH:
			_text = "sinh";
			break;
		case BUTTON_S_COSH:
			_text = "cosh";
			break;
		case BUTTON_S_TANH:
			_text = "tanh";
			break;
		case BUTTON_S_LN:
			_text = "ln";
			break;
		case BUTTON_S_LOG10:
			_text = "log10";
			break;
		case BUTTON_S_LOG2:
			_text = "log2";
			break;
		case BUTTON_S_CUBE:
			_text = "^3";
			break;
		case BUTTON_S_ABS:
			_text = "abs";
			break;
		case BUTTON_S_ROUND:
			_text = "int";
			break;


		case BUTTON_D_EE:
			_text = "EE";
			break;
		case BUTTON_D_HIGHER:
			_text = "?>";
			break;
		case BUTTON_D_LOWER:
			_text = "?<";
			break;
		case BUTTON_D_MOD:
			_text = "mod";
			break;

		case BUTTON_D_GROWTH_RATE:
			_text = "+%";
			break;
		case BUTTON_D_CHANGE_RATE:
			_text = "-=%";
			break;


		default:
			break;
	}

	_labelText->setString(_text) ;

}

void TextOperator::setOperator( PanelButtonType panelButtonType )
{
	//_operator = panelButtonType;
	processInput(panelButtonType);
}




