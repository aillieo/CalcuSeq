#include "TextOperand.h"
#include <iomanip>

USING_NS_CC;

const int maxDecimal = 7;
const int maxLength = 9;



// on "init" you need to initialize your instance
bool TextOperand::init()
{
     
    // 1. super init first
    if ( !Text::init() )
    {
        return false;
    }
    

	_isAppending = false;
	_value = 0;
	_text = "0";
	updateText();


	_listenerStoreValue = EventListenerCustom ::create("STORE_VALUE",CC_CALLBACK_1(TextOperand::storeValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerStoreValue,this);

	_listenerRestoreValue = EventListenerCustom ::create("RESTORE_VALUE",CC_CALLBACK_1(TextOperand::restoreValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerRestoreValue,this);

	enableInput(false);

    
    return true;
}


void TextOperand::processInput(PanelButtonType panelButtonType)
{

	switch (panelButtonType)
	{
	case BUTTON_G_CLOSE:
		_isAppending = false;
		endInputting();
		return;

	case BUTTON_PI:
		setValue(M_PI,true);
		updateTextFromValue();
		_isAppending = false;
		endInputting();
		return;

	case BUTTON_E:
		setValue(M_E,true);
		updateTextFromValue();
		_isAppending = false;
		endInputting();
		return;

	case BUTTON_RANDOM:
		setValue(CCRANDOM_0_1(),true);
		updateTextFromValue();
		_isAppending = false;
		endInputting();
		return;


	case BUTTON_G_CLEAR:
		setValue(0,true);
		_text = "0";
		_isAppending = true;
		break;

	case BUTTON_0:
	case BUTTON_00:
            if (!_isAppending)
            {
                setValue(0,true);
                _isAppending = true;
            }
		if (getDigitalLength()>= maxLength )
		{
			return;
		}
		if (getDigitalLength()>= maxLength - ((panelButtonType==BUTTON_0)?0:1) )
		{
			return;
		}

		_text = _text + ((panelButtonType==BUTTON_0)?"0":"00");

		if ((hasDecimal()< 0))
		{
			updateValue();
		}

		break;


	case BUTTON_1:
	case BUTTON_2:
	case BUTTON_3:
	case BUTTON_4:
	case BUTTON_5:
	case BUTTON_6:
	case BUTTON_7:
	case BUTTON_8:
	case BUTTON_9:
		if (!_isAppending)
		{
			setValue(0,true);
			_isAppending = true;
		}
		//if ((_text.length()>= maxLength )||(hasDecimal()>= maxDecimal))
		if (getDigitalLength()>= maxLength )
		{
			return;
		}
		_text = _text + String::createWithFormat("%d",(int)panelButtonType)->getCString();
		updateText();
		updateValue();
		return;


	case BUTTON_DECIMAL:
		if (!_isAppending)
		{
			_value = 0;
			_text = "0.";
			updateText();
			_isAppending = true;
		}
		if (hasDecimal()==-1)
		{
			_text = _text + ".";
			_labelText->setString(_text) ;
		}
		return;

	case BUTTON_PERCENT:
		setValue( _value * 0.01,true);
		_isAppending = false;
		break;

	case BUTTON_G_DELETE:
		if (!_isAppending)
		{
			setValue(0,true);
			_isAppending = true;
			break;
		}
		if (_text.back() == '.')
		{
			_text = _text.substr(0,_text.length()-1);
			updateText();
			return;
		}
		else
		{
			if (_text.length() > 1)
			{
				_text = _text.substr(0,_text.length()-1);
			}
			else
			{
				_text = "0";
			}
			updateText();
			updateValue();
			return;
		}


	case BUTTON_NEGATIVE:
 		if (!_isAppending)
 		{
 			_value = 0;
 			_text = "0";
			updateText();
 			_isAppending = true;
 		}
		if (_text.front() == '-')
		{
			_text = _text.substr(1,_text.length());
		}
		else
		{
			_text = "-" + _text;
		}
		setValue(_value * (-1),false);
            updateText();
		return;


	default:
		break;
	}



	updateText();




}




int TextOperand::hasDecimal()
{

	size_t found = _text.find_first_of(".");
		
	if (found == std::string::npos)
	{
		return -1;
	}
	else
	{
		return _text.length()- found;
	}


}




double TextOperand::getValue()
{
	return _value;
}

void TextOperand::updateText()
{

	while (_text.front()=='0'&&_text.length()>1)
	{
		_text = _text.substr(1,_text.length());
	}

	while (_text.front()=='-'&&_text.length()>2 && _text[1]=='0')
	{
		_text = "-" + _text.substr(2,_text.length());
	}


	if (_text.front()== '.')
	{
		_text= "0"+_text;
	}
    else if(_text.front()=='-'&&_text.length()>=2 && _text[1]=='.')
    {
        _text = "-0" + _text.substr(1,_text.length());
    }

	if (_text == "-")
	{
		_text = "-0";
	}
	



	_labelText->setString(_text) ;




	if (_text.length()>=9)
	{
		_labelText->setScale(0.7);

	}
	else if (_text.length()>=8)
	{
		_labelText->setScale(0.75);

	}
	else if (_text.length()>=7)
	{
		_labelText->setScale(0.9);

	}
	else
	{
		_labelText->setScale(1);
	}




}

void TextOperand::setValue(double value, bool bUpdateText)
{
	_value = value;

	if (fabs(_value)<1e-11)
	{
		_value = 0;
	}


	if (bUpdateText)
	{
		updateTextFromValue();
	}
	

}

void TextOperand::endInputting()
{

	bool show = false;
	_eventDispatcher->dispatchCustomEvent("SHOW_PANEL_INPUT_OPERAND",&show);
	_eventDispatcher->dispatchCustomEvent("RESET_HOLDER");

	enableInput(false);
	//_isAppending = false;

}

void TextOperand::updateValue()
{

	//_labelText->setString(_text);
	std::stringstream ss(_text);  
	ss >> _value;  
	ss.clear();
	setValue(_value,false);

}


void TextOperand::storeValue(cocos2d::EventCustom* event )
{
	int* storageIndex = (int*)(event->getUserData());
	std::string key = "store_value_";
	key = key + String::createWithFormat("%d",* storageIndex)->_string;
	UserDefault::getInstance()->setDoubleForKey(key.c_str() , _value);

}
void TextOperand::restoreValue(cocos2d::EventCustom* event )
{
	int* storageIndex = (int*)(event->getUserData());
	std::string key = "store_value_";
	key = key + String::createWithFormat("%d",* storageIndex)->_string;
	double d = UserDefault::getInstance()->getDoubleForKey(key.c_str(),0);
	setValue(d,true);

}

void TextOperand::enableInput( bool input )
{
	Text::enableInput(input);
	_listenerRestoreValue->setEnabled(input);
	_listenerStoreValue->setEnabled(input);

}

void TextOperand::updateTextFromValue()
{

	std::stringstream ss;  
	ss <<std::setprecision(maxLength)<< _value;
	//ss <<std::setprecision(16)<<std::setw(maxLength)<<_value;
	ss >> _text; 
	ss.clear();



	if (_text.length()>maxLength+2)
	{
		_text = String::createWithFormat("%6E",_value)->_string;
	}
	_text = stringReplace(_text,"e","E");
	_text = stringReplace(_text,"E+0","E+");
	_text = stringReplace(_text,"E+","E");
	_text = stringReplace(_text,"E-0","E-");


	updateText();



}

int TextOperand::getDigitalLength()
{
	int ret = _text.length();
	if (hasDecimal()!= -1)
	{
		ret -= 1;
	}
	if (_text.front() == '-')
	{
		ret -= 1;
	}
	return ret;
	
	
}

std::string& TextOperand::stringReplace(std::string&   str,const   std::string&   old_value,const   std::string&   new_value)
{     
	while(true)   {     
		std::string::size_type   pos(0);     
		if(   (pos=str.find(old_value))!=std::string::npos   )     
			str.replace(pos,old_value.length(),new_value);     
		else   break;     
	}     
	return   str;  
}  




