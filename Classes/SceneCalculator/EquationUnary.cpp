#include "EquationUnary.h"
#include "TextHolder.h"
#include "TextHolderWithLinking.h"
#include "LinkingNodeOperand.h"
#include <iomanip>
#include "PersistenceManager.h"



USING_NS_CC;



// on "init" you need to initialize your instance
bool EquationUnary::init()
{
	 
	// 1. super init first
	if ( !Equation::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_textHolderOperator = TextHolder::create();
	addChild(_textHolderOperator);
	_textHolderOperator->setPosition((Vec2)getContentSize()/2 + Vec2(-270,0));
	_textOperator = TextOperator::create();
	_textHolderOperator->initText(_textOperator);
	_textHolderOperator->holderType = TextHolderWithLinking::HolderType::OPERATOR_UNARY;


	_textHolderOperand = TextHolderWithLinking::create();
	addChild(_textHolderOperand);
	_textHolderOperand->setPosition((Vec2)getContentSize()/2 + Vec2(-135,0));
	_textOperand = TextOperandWithLinking::create();
	_textHolderOperand->initText(_textOperand);
	_textHolderOperand->holderType = TextHolderWithLinking::HolderType::OPERAND;
	LinkingNodeOperand* linkingNode = LinkingNodeOperand::create();
	_textHolderOperand->initLinkingNode(linkingNode);
/*

	auto preposeOperatorListener = EventListenerCustom ::create("PREPOSE_OPORATOR",CC_CALLBACK_1(EquationUnary::preposeOperator,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(preposeOperatorListener,this);
*/

	EquationUnary::_setEquationOutOfDate();

	return true;
}

void EquationUnary::_compute()
{

	bool hasResult = true;
	double result = 0.0;




#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (_finite(_textOperand->getValue()) == 0)
	{
		return;
	}

	if (_isnan(_textOperand->getValue())!=0)
	{
		return;
	}

#else

	if (isinf(_textOperand->getValue()) != 0)
	{
		return;
	}

	if (isnan(_textOperand->getValue())!=0)
	{
		return;
	}


#endif


	switch (_textOperator->getOperator())
	{

		case UNDEFINED:
			hasResult = false;
			break;
		case BUTTON_S_RECIPROCAL:
			hasResult = (_textOperand->getValue()!=0);
			if (hasResult)
			{
				result = 1.0/_textOperand->getValue();
			}
			break;
		case BUTTON_S_SQUARE:
			result = pow(_textOperand->getValue(),2.0);
			break;
		case BUTTON_S_SQROOT:
			hasResult = (_textOperand->getValue()>=0);
			if (hasResult)
			{
				result = sqrt(_textOperand->getValue());
			}
			break;
		case BUTTON_S_SIN:
			result = sin(_textOperand->getValue());
			break;
		case BUTTON_S_COS:
			result = cos(_textOperand->getValue());
			break;
		case BUTTON_S_TAN:
			hasResult = (fmod(_textOperand->getValue() - M_PI*0.5,M_PI) != 0);
			if (hasResult)
			{
				result = tan(_textOperand->getValue());
			}
			break;
		case BUTTON_S_ASIN:
			hasResult = (_textOperand->getValue()>= -1)&&(_textOperand->getValue()<= 1);
			if (hasResult)
			{
				result = asin(_textOperand->getValue());
			}

			break;
		case BUTTON_S_ACOS:
			hasResult = (_textOperand->getValue()>= -1)&&(_textOperand->getValue()<= 1);
			if (hasResult)
			{
				result = acos(_textOperand->getValue());
			}
			break;
		case BUTTON_S_ATAN:
			result = atan(_textOperand->getValue());
			break;
		case BUTTON_S_FACTORIAL:
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
			hasResult = (_textOperand->getValue()>= 0);
			if (hasResult)
			{
				if(_textOperand->getValue()== 0)
				{
					result = 1;
				}
				else
				{
					result = _textOperand->getValue() * tgamma(_textOperand->getValue()) ;
				}
			}
#endif
			break;
		case BUTTON_S_TORADIAN:
			result = _textOperand->getValue() * M_PI / 180.0;
			break;
		case BUTTON_S_TODEGREE:
			result = _textOperand->getValue() * 180.0 / M_PI;
			break;


		case BUTTON_S_EXPONENT:
			result = exp(_textOperand->getValue());
			break;
		case BUTTON_S_SINH:
			result = sinh(_textOperand->getValue());
			break;
		case BUTTON_S_COSH:
			result = cosh(_textOperand->getValue());
			break;
		case BUTTON_S_TANH:
			result = tanh(_textOperand->getValue());
			break;
		case BUTTON_S_LN:
			hasResult = (_textOperand->getValue()> 0);
			if (hasResult)
			{
				result = log(_textOperand->getValue());
			}
			break;
		case BUTTON_S_LOG10:
			hasResult = (_textOperand->getValue()> 0);
			if (hasResult)
			{
				result = log10(_textOperand->getValue());
			}
			break;
		case BUTTON_S_LOG2:

			hasResult = (_textOperand->getValue()> 0);
			if (hasResult)
			{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
				result = log2(_textOperand->getValue());
#else
				result = log(_textOperand->getValue())/log(2.0);
#endif
			}
			break;

		case BUTTON_S_CUBE:
			result = pow(_textOperand->getValue(),3);
			break;
		case BUTTON_S_ABS:
			result = fabs(_textOperand->getValue());
			break;
		case BUTTON_S_ROUND:
			result = (int)(_textOperand->getValue());
			break;


		default:
			return;
	}
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if (_finite(result) == 0)
    {
        return;
    }
    
    if (_isnan(result)!=0)
    {
        return;
    }
#else
    
    if (isinf(result) != 0)
    {
        return;
    }
    
    if (isnan(result)!=0)
    {
        return;
    }

#endif
    
*/
	

	if (hasResult)
	{
		Equation::_compute();
		if (_textHolderOperator!= nullptr)
		{
			updateHolderColor();

		}
		_textResult->setValue(result,true,false,true);
		////数值 -颜色  传递
	}
	
	
	


}

void EquationUnary::onRemove()
{
	Equation::onRemove();
	//_textHolderOperand->destroyLinkingNode();
}

/*
void EquationUnary::setEquationID( unsigned equationID )
{
	Equation::setEquationID(equationID);
	_textHolderOperand->passEquationID(equationID);
	_textOperator->setEquationID(equationID);
}*/


bool EquationUnary::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
    
    //_touchManager.reset();
    
    
    bool bRet = false;
    
    Point p = _bg2->getParent()->convertToNodeSpace(touch->getLocation());
    
    if (_bg2->getBoundingBox().containsPoint(p))
    {
        
        bRet = true;
        _willLeadToDynamicSort = true;
    }
    
    
    p = this->convertToNodeSpace(touch->getLocation());
    
    if (_textHolderOperand-> getBoundingBox().containsPoint(p))
    {
        _willLeadToDynamicSort = false;
    }
    else if (_textHolderResult-> getBoundingBox().containsPoint(p))
    {
        _willLeadToDynamicSort = false;
	}
	else if (_buttonCompute-> getBoundingBox().containsPoint(p))
	{
		_willLeadToDynamicSort = false;
	}
    
    
    if (bRet)
    {
        //_touchManager.containsTouchingPoint = true;
        //scheduleUpdate();
        return Equation::onTouchBegan(touch, unused);
    }
    
    return bRet;

}

void EquationUnary::_setEquationOutOfDate()
{

	Equation::_setEquationOutOfDate();
	if (_textHolderOperator!= nullptr)
	{
		updateHolderColor();
	}

}


void EquationUnary::updateHolderColor()
{
	//Color3B c3b = _textHolderResult->getColor();
	//_textHolderOperator->setColor(c3b);
	//_textHolderOperand->setColor(c3b);
}

std::string EquationUnary::toString()
{
	std::string str = "";
	std::stringstream ss;  

	ss <<"u"<<",";

	ss << _textHolderOperand->toString()<<",";
	ss << _textHolderResult->toString()<<",";

	//ss <<std::setprecision(16);
	ss << (int)(_textOperator->getOperator())<<",";

	if(_computed)
	{
		ss << 1;
	}
	else
	{
		ss << 0;
	}
	

	ss >> str; 
	ss.clear();
	return str;
}

EquationUnary* EquationUnary::createWithString( const std::string& eq_string )
{

	EquationUnary* eq = EquationUnary::create();

	std::vector<std::string> strs = PersistenceManager::splitString(eq_string,",");

	if (strs.size() != 5)
	{
		return eq;
	}

	eq->_textHolderOperand->initWithString(strs[1]);
	eq->_textHolderResult->initWithString(strs[2]);

	std::stringstream ss(strs[3]); 
	int oprtr;
	ss >> oprtr;  

	eq->_textOperator->setOperator((PanelButtonType)oprtr);


	ss.clear();


	std::stringstream ss2(strs[4]); 
	int computed;
	ss2 >> computed;  
	if(computed == 1)
	{
		eq->_compute();
	}
	ss2.clear();




	return eq;


}


