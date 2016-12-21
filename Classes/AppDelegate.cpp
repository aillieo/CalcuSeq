#include "AppDelegate.h"
#include "SceneMenu.h"
#include "SceneCalculator/SceneCalculator.h"

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("ColorDefence");
		director->setOpenGLView(glview);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//以红米手机的显示分辨率为设计目标1280x720
	glview->setFrameSize(720,1280);
	glview->setFrameZoomFactor(0.5);

#endif


	glview->setDesignResolutionSize(720,1280, ResolutionPolicy::SHOW_ALL);

	//图像资源路径
	//获取当前设备屏幕尺寸
	Size frameSize = glview->getFrameSize();
	std::vector<std::string> searchPath;
	//如果屏幕尺寸宽>smallResource素材尺寸宽
	//if (frameSize.width > 1080 )
	if (frameSize.width > 108000 )
	{
		//使用大尺寸的素材
		searchPath.push_back("xxxhdpi/");
		director->setContentScaleFactor(2.0);
	}
	else
	{
		//使用小尺寸的素材
		searchPath.push_back("xhdpi/");
		director->setContentScaleFactor(1.0);
	}

	// 设置素材路径目录
	FileUtils::getInstance()->setSearchPaths(searchPath);


	//在windows下运行时按0.5比例显示 以预览整个界面


	// turn on display FPS
	//director->setDisplayStats(true);
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	//auto scene = SceneMenu::createScene();
	auto scene = SceneCalculator::createScene();
    
    //读写路径
    log(" %s" , FileUtils::getInstance()->getWritablePath().c_str());
    
	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
