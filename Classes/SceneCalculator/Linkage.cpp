#include "Linkage.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool Linkage::init()
{
     
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
 
	setCascadeOpacityEnabled(true);



    
    return true;
}

void Linkage::setNodes(LinkingNode* nodeSource, LinkingNode* nodeTarget)
{
	_nodeSource = nodeSource;
	_nodeTarget = nodeTarget;


	_nodeSource->addTarget(_nodeTarget);
	_nodeTarget->setSource(_nodeSource);



	drawLinkage();

}

void Linkage::drawLinkage()
{

	_pathLine = Sprite::create("ResourcesCalculator/path.png");
	addChild(_pathLine,2);
	_pathLine->setAnchorPoint(Point(0.5,0));
	_pathLine->getTexture()->setAntiAliasTexParameters();


	_pathLine_shadow = Sprite::create("ResourcesCalculator/path.png");
	addChild(_pathLine_shadow);
	_pathLine_shadow->setAnchorPoint(Point(0.5,0));
	_pathLine_shadow->setColor(Color3B(Color4F(0,0,0,0.75)));
	_pathLine_shadow->getTexture()->setAntiAliasTexParameters();

	_head = Sprite::create("ResourcesCalculator/head.png");
	addChild(_head,2);
	//_head->setScale(0.5,0.8);
	_head->setAnchorPoint(Point(0.5,1));

	
	_head_shadow = Sprite::create("ResourcesCalculator/head.png");
	addChild(_head_shadow);
	//_head_shadow->setScale(_head->getScaleX(),_head->getScaleY());
	_head_shadow->setAnchorPoint(_head->getAnchorPoint());
	_head_shadow->setColor(Color3B(Color4F(0,0,0,0.75)));

	updatePosition();
}


Linkage::~Linkage()
{
	
	_nodeSource = nullptr;
	_nodeTarget = nullptr;
}







bool Linkage::hasTarget( LinkingNode* target )
{
	return target == _nodeTarget;
}



void Linkage::updatePosition()
{
	//_pathLine->clear();
	//_pathLine_shadow->clear();

	if ((_nodeSource == nullptr)||(_nodeTarget == nullptr))
	{
		return;
	}
	

	Point ps = getParent()->convertToNodeSpace( _nodeSource->getParent()->convertToWorldSpace(_nodeSource->getPosition()) );
	Point pt = getParent()->convertToNodeSpace( _nodeTarget->getParent()->convertToWorldSpace(_nodeTarget->getPosition()) );

	bool b = pt.y > ps.y;
	pt.y += 30* (b?-1:1);
	ps.y += 30* (b?1:-1);

	Vec2 shadowOffset = Vec2(3,-3);

	float f_length = ps.getDistance(pt);
	Vec2 v_normalized = ccpNormalize(ccp(pt.x - ps.x,	pt.y - ps.y));
	//Point p_pathEnd = ps + v_normalized*(f_length - 30);

	
	_pathLine->setScaleY((f_length - 48)/4.0);
	_pathLine_shadow->setScaleY(_pathLine->getScaleY());
	//_pathLine->drawSegment(ps,p_pathEnd,2,Color4F(1,1,1,1));
	//_pathLine_shadow->drawSegment(ps+shadowOffset,p_pathEnd+shadowOffset,2,Color4F(0,0,0,0.75));


	_head->setPosition(pt);
	_head->setRotation(CC_RADIANS_TO_DEGREES(atan2(v_normalized.y, - v_normalized.x)) - 90);

	_head_shadow->setPosition(pt+shadowOffset);
	_head_shadow->setRotation(_head->getRotation());


	_pathLine->setRotation(_head->getRotation());
	_pathLine->setPosition(ps);
	_pathLine_shadow->setRotation(_head->getRotation());
	_pathLine_shadow->setPosition(ps + shadowOffset);

}

LinkingNodePair* Linkage::getLinkingNodePair()
{
	LinkingNodePair* lnp = LinkingNodePair::create();
	lnp->linkingNodeSource = _nodeSource;
	lnp->linkingNodeTarget = _nodeTarget;
	return lnp;

}
