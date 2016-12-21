#include "LayerHelpCal.h"
#include "VersionConfigCal.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerHelpCal::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	std::string str = "Press the button with \"+\" \nand move left or right\nto create an equation\n\nLong press operands and drag \nto make linkages\n\nTap top of the screen \nto hide/show linkages";
#if (CAL_VERSION_PRO == 1)
	
	str = str + "\n\nSwipe right from left edge of screen\nto show the save/load panel";

#endif


	Label* label = Label::create(str,"Arial",40);
	label->setAlignment(TextHAlignment::CENTER);
	addChild(label);
	label -> setPosition((Vec2)visibleSize/2 + Vec2(0, -30));


    return true;
}


