#pragma  once

#include "cocos2d.h"
#include "LinkingIdentifier.h"


class LinkingNode : public cocos2d::Node
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LinkingNode);


	void bindValue(double* value);

	void addTarget(LinkingNode* lnode);
	void setSource(LinkingNode* lnode);
	void removeTarget(LinkingNode* lnode);
	void removeSource();

	LinkingNode* getSource();
	LinkingNode* getRoot();

	//int getIndex();

	cocos2d::Vector<LinkingNode*> getAllTargetsInTree();

	virtual bool isLinkableAsTarget();


	void sendValueToTargets();

	void willBeSourceNode(bool willBe);

	void willBeTargetNode(bool willBe);

	double getValue();

	void setValue(double value);


	void setNodeID(unsigned nodeID);
	unsigned getNodeID();

    
   // void removeFromParent();
    void setParent(Node * parent);

private:

	unsigned _nodeID;


	double _value;


	LinkingIdentifier* _linkingIdentifier;



	void onRecevieValue(cocos2d::EventCustom* event);

	/*


	void startLinking(cocos2d::EventCustom* event);
	void endLinking(cocos2d::EventCustom* event);

	bool _linkabeAsTarget;



	HolderOperand* _holderOperand;

	bool _selected;

	void transferValue(cocos2d::EventCustom* event);
	void sendValue(LinkingNode* linkingNode);
*/

	LinkingNode* _sourceNode;
	cocos2d::Vector<LinkingNode*> _targetNodes;

	void onEnter();
	void onExit();



};


