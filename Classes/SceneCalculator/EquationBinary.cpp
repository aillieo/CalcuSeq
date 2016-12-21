#include "EquationBinary.h"
#include "TextHolder.h"
#include "TextHolderWithLinking.h"
#include "LinkingNodeOperand.h"
#include "PersistenceManager.h"




USING_NS_CC;



// on "init" you need to initialize your instance
bool EquationBinary::init()
{
     
    // 1. super init first
    if ( !Equation::init() )
    {
        return false;
    }

	
	_textHolderOperator = TextHolder::create();
	addChild(_textHolderOperator);
	_textHolderOperator->setPosition((Vec2)getContentSize()/2 + Vec2(-135,0));
	_textOperator = TextOperator::create();
	_textHolderOperator->initText(_textOperator);
	_textHolderOperator->holderType = TextHolderWithLinking::HolderType::OPERATOR_BINARY;
	

	_textHolderOperand_1 = TextHolderWithLinking::create();
	addChild(_textHolderOperand_1);
	_textHolderOperand_1->setPosition((Vec2)getContentSize()/2 + Vec2(-270,0));
	_textOperand_1 = TextOperandWithLinking::create();
	_textHolderOperand_1->initText(_textOperand_1);
	_textHolderOperand_1->holderType = TextHolderWithLinking::HolderType::OPERAND;
	LinkingNodeOperand* linkingNode_1 = LinkingNodeOperand::create();
	_textHolderOperand_1->initLinkingNode(linkingNode_1);


	_textHolderOperand_2 = TextHolderWithLinking::create();
	addChild(_textHolderOperand_2);
	_textHolderOperand_2->setPosition((Vec2)getContentSize()/2 + Vec2(0,0));
	_textOperand_2 = TextOperandWithLinking::create();
	_textHolderOperand_2->initText(_textOperand_2);
	_textHolderOperand_2->holderType = TextHolderWithLinking::HolderType::OPERAND;
	LinkingNodeOperand* linkingNode_2 = LinkingNodeOperand::create();
	_textHolderOperand_2->initLinkingNode(linkingNode_2);



	EquationBinary::_setEquationOutOfDate();
    
    return true;
}

void EquationBinary::_compute()
{


	bool hasResult = true;
	double result = 0.0;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (_finite(_textOperand_1->getValue()) == 0)
	{
		return;
	}
	if (_finite(_textOperand_2->getValue()) == 0)
	{
		return;
	}

	if (_isnan(_textOperand_1->getValue())!=0)
	{
		return;
	}
	if (_isnan(_textOperand_2->getValue())!=0)
	{
		return;
	}
#else

	if (isinf(_textOperand_1->getValue()) != 0)
	{
		return;
	}
	if (isinf(_textOperand_2->getValue()) != 0)
	{
		return;
	}

	if (isnan(_textOperand_1->getValue())!=0)
	{
		return;
	}
	if (isnan(_textOperand_2->getValue())!=0)
	{
		return;
	}

#endif





	switch (_textOperator->getOperator())
	{

		case UNDEFINED:
			hasResult = false;
			break;
		case BUTTON_D_PLUS:
			result = _textOperand_1->getValue()+_textOperand_2->getValue();
			break;
		case BUTTON_D_MINUS:
			result = _textOperand_1->getValue()-_textOperand_2->getValue();
			break;
		case BUTTON_D_MULTIPLY:
			result = _textOperand_1->getValue()*_textOperand_2->getValue();
			break;
		case BUTTON_D_DIVIDE:
			hasResult = (_textOperand_2->getValue()!=0);
			if (hasResult)
			{
				result = _textOperand_1->getValue()/_textOperand_2->getValue();
			}

			break;
		case BUTTON_D_POWER:
			if (((_textOperand_1->getValue()==0)&&(_textOperand_2->getValue()<=0)))
			{
				hasResult = false;
			}
			else if (((_textOperand_1->getValue()<0)&&( (long)_textOperand_2->getValue() != _textOperand_2->getValue() )))
			{
				hasResult = false;
			}
			
			if (hasResult)
			{
				result = pow(_textOperand_1->getValue(),_textOperand_2->getValue());
			}

			break;


		case BUTTON_D_EE:
			result = _textOperand_1->getValue() * pow(10,_textOperand_2->getValue());
			break;

		case BUTTON_D_HIGHER:
			result = (_textOperand_1->getValue()>_textOperand_2->getValue())?(_textOperand_1->getValue()):(_textOperand_2->getValue());
			break;
		case BUTTON_D_LOWER:
			result = (_textOperand_1->getValue()<_textOperand_2->getValue())?(_textOperand_1->getValue()):(_textOperand_2->getValue());
			break;
		case BUTTON_D_MOD:
			hasResult = (_textOperand_2->getValue()!=0);
			if (hasResult)
			{
				result = fmod(_textOperand_1->getValue(),_textOperand_2->getValue());
				//result = remainder(_textOperand_1->getValue(),_textOperand_2->getValue());
				if(fabs(result - _textOperand_2->getValue())< 1e-15)
				{
					result = 0;
				}
			}
			break;


		case BUTTON_D_GROWTH_RATE:
			result = _textOperand_1->getValue()*( 1 + _textOperand_2->getValue());
			break;
		case BUTTON_D_CHANGE_RATE:
			hasResult = (_textOperand_2->getValue()!=0);
			if (hasResult)
			{
				result = (_textOperand_1->getValue() - _textOperand_2->getValue())/_textOperand_2->getValue();
			}
			break;


		default:
			return;
	}




    
    
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

void EquationBinary::onRemove()
{
	Equation::onRemove();
	//_textHolderOperand_1->destroyLinkingNode();
	//_textHolderOperand_2->destroyLinkingNode();
}

/*
void EquationBinary::setEquationID( unsigned equationID )
{
	Equation::setEquationID(equationID);
	_textHolderOperand_1->passEquationID(equationID);
	_textHolderOperand_2->passEquationID(equationID);
	_textOperator->setEquationID(equationID);
}*/


bool EquationBinary::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
    
    //_touchManager.reset();
    
    
    bool bRet = false;
    
    Point p = _bg2->getParent()->convertToNodeSpace(touch->getLocation());
    
    if (_bg2->getBoundingBox().containsPoint(p))
    {

        bRet = true;
        _willLeadToDynamicSort  = true;
    }
    
    
    p = this->convertToNodeSpace(touch->getLocation());
    
    if (_textHolderOperand_1-> getBoundingBox().containsPoint(p))
    {
        _willLeadToDynamicSort = false;
    }
    else if (_textHolderOperand_2-> getBoundingBox().containsPoint(p))
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
        return Equation::onTouchBegan(touch, unused);
        
    }

    return bRet;
}


void EquationBinary::_setEquationOutOfDate()
{
	Equation::_setEquationOutOfDate();
	if (_textHolderOperator!= nullptr)
	{
		updateHolderColor();

	}
	

	

}

void EquationBinary::updateHolderColor()
{
	//Color3B c3b = _textHolderResult->getColor();
	//_textHolderOperator->setColor(c3b);
	//_textHolderOperand_1->setColor(c3b);
	//_textHolderOperand_2->setColor(c3b);
}

std::string EquationBinary::toString()
{
	std::string str = "";
	std::stringstream ss;  

	ss <<"b"<<",";

	ss << _textHolderOperand_1->toString()<<",";
	ss << _textHolderOperand_2->toString()<<",";
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

EquationBinary* EquationBinary::createWithString(const std::string& eq_string )
{
	EquationBinary* eq = EquationBinary::create();

	std::vector<std::string> strs = PersistenceManager::splitString(eq_string,",");

	if (strs.size() != 6)
	{
		return eq;
	}

	eq->_textHolderOperand_1->initWithString(strs[1]);
	eq->_textHolderOperand_2->initWithString(strs[2]);
	eq->_textHolderResult->initWithString(strs[3]);

	std::stringstream ss(strs[4]); 
	int oprtr;
	ss >> oprtr;  
	ss.clear();
	eq->_textOperator->setOperator((PanelButtonType)oprtr);

	std::stringstream ss2(strs[5]); 
	int computed;
	ss2 >> computed;  
	if(computed == 1)
	{
		eq->_compute();
	}
	ss2.clear();
	
	return eq;

}


