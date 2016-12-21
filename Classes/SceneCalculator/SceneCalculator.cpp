#include "SceneCalculator.h"
#include "VersionConfigCal.h"
#include "LayerPersistenceCal.h"

#include "PersistenceManager.h"




const float distance_between_equations = 180;


USING_NS_CC;

Scene* SceneCalculator::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneCalculator::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}




// on "init" you need to initialize your instance
bool SceneCalculator::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



	Sprite* bg = Sprite::create();
	addChild(bg);
	bg->setGlobalZOrder(-5);
	bg->setTexture("BLANK.png");
	//bg->setColor(Color3B(49,102,205));
	bg->setColor(Color3B(98,98,98));
	bg->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
	bg->setPosition(visibleSize/2);



	_hiddenLable = Label::createWithSystemFont("Wish you enjoy CalcuSeq","Arial",40);
	addChild(_hiddenLable);
	_hiddenLable->setPosition(Vec2(visibleSize/2)+ Vec2(0,450));
	_hiddenLable->setOpacity(0);



	_layerEquation = LayerEquation::create();
	addChild(_layerEquation);

	LayerUICal* _layerUICal = LayerUICal::create();
	addChild(_layerUICal,2);

	_layerHelpCal = LayerHelpCal::create();
	addChild(_layerHelpCal,3);

#if (CAL_VERSION_PRO == 1)

	LayerPersistenceCal* layerPersistenceCal = LayerPersistenceCal::create();
	addChild(layerPersistenceCal,5);
//#else
#endif



	auto displayHelpListener = EventListenerCustom ::create("DISPLAY_HELP_INFO",CC_CALLBACK_1(SceneCalculator::displayHelpInfo,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(displayHelpListener,this);

	auto saveSceneListener = EventListenerCustom ::create("SAVE_SCENE",CC_CALLBACK_1(SceneCalculator::saveScene,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(saveSceneListener,this);

	auto loadSceneListener = EventListenerCustom ::create("LOAD_SCENE",CC_CALLBACK_1(SceneCalculator::loadScene,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(loadSceneListener,this);


	auto hiddenLabelListener = EventListenerCustom ::create("ADJUST_HIDDEN_LABEL",CC_CALLBACK_1(SceneCalculator::adjustHiddenLable,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(hiddenLabelListener,this);
	


    return true;
}


SceneCalculator::SceneCalculator()
{
	LinkingManager::getInstance()->reset();

}

SceneCalculator::~SceneCalculator()
{
	LinkingManager::destroyInstance();

}

void SceneCalculator::displayHelpInfo( cocos2d::EventCustom* event )
{
	bool* display = (bool*)(event->getUserData());
	if (*display == _layerHelpCal->isVisible())
	{
		return;
	}
	
	_layerHelpCal->setVisible(*display);

}


void SceneCalculator::adjustHiddenLable( cocos2d::EventCustom* event )
{

	float* op = (float*)(event->getUserData());
	if ((*op >= 0)&&(*op <=255))
	{
		_hiddenLable->setOpacity(*op);
		//log("%f",*op);
	}



}



void SceneCalculator::saveScene(cocos2d::EventCustom* event)
{


	int* persistenceID = (int*)(event->getUserData());

	LinkingManager::getInstance()->resortNodeIDs();
	std::string str = _layerEquation->toString();


	log("save scene %d %s",&persistenceID,str.c_str());


	PersistenceManager::writeFile(str, *persistenceID);



}
void SceneCalculator::loadScene(cocos2d::EventCustom* event)
{

	int* persistenceID = (int*)(event->getUserData());

	std::string str = PersistenceManager::readFile( *persistenceID );

	if (str.empty())
	{
		str = "e~l";
	}
	

	log("load scene %d %s",&persistenceID,str.c_str());

	_layerEquation->removeFromParent();
	//_layerEquation = nullptr;
	LinkingManager::getInstance()->reset();
	_layerEquation = LayerEquation::createWithString(str);
	addChild(_layerEquation);





}

