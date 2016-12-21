#include "LinkingManager.h"

USING_NS_CC;

LinkingManager* LinkingManager::_linkingManager = nullptr;


LinkingManager::LinkingManager()
{
	reset();
}



LinkingManager* LinkingManager::getInstance()
{
	if(_linkingManager == nullptr)
	{
		_linkingManager = new LinkingManager();
	}

	return _linkingManager;

}

void LinkingManager::destroyInstance()
{
	//reset();
	CC_SAFE_RELEASE_NULL(_linkingManager);
}

void LinkingManager::reset()
{
	allLinkingNodes.clear();
	allLinkages.clear();

}

void LinkingManager::resortNodes()
{

	std::sort(allLinkingNodes.begin(),allLinkingNodes.end(),[](LinkingNode* ln1 ,LinkingNode* ln2 ){return ln1->getNodeID()<ln2->getNodeID();});
	
}

void LinkingManager::resortNodeIDs()
{
	for (LinkingNode* ln : allLinkingNodes)
	{
		ln->setNodeID(allLinkingNodes.getIndex(ln));
	}
}



