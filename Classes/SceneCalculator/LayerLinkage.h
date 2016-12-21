#pragma  once

#include "cocos2d.h"
#include "LinkingNodePair.h"
#include "LinkingManager.h"


class LayerLinkage : public cocos2d::Layer
{
public:

    virtual bool init();  

    CREATE_FUNC(LayerLinkage);

	bool initLinkagesWithString(const std::string& str);

private:

	LinkingManager* _linkingManager;

	void createLinkage(cocos2d::EventCustom* event);
	void _createLinkage(LinkingNodePair* linkingNodePair);

	void updateLinkagePosition(cocos2d::EventCustom* event);
   	void autoUpdateLinkagePosition(cocos2d::EventCustom* event);

	bool validateLinkage(LinkingNodePair* linkingNodePair);

	void removeLinkageByTarget(cocos2d::EventCustom* event);

	float _updating;

	void update(float delta);

	void setLinkagesVisible(cocos2d::EventCustom* event);
	
	void showLinkages(bool show);
	bool _linkagesShown;

	bool _autoUpdateLkgPos;

};


