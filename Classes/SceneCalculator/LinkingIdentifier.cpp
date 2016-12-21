#include "LinkingIdentifier.h"



USING_NS_CC;


// on "init" you need to initialize your instance
bool LinkingIdentifier::init()
{
     
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    

	 _inner_1 = Sprite::create("ResourcesCalculator/circle.png");
	 addChild(_inner_1);
	_inner_1->setPosition(0,0);



	 _inner_2 = Sprite::create("ResourcesCalculator/circle.png");
	 addChild(_inner_2);
	_inner_2->setPosition(0,0);


	hideIdentifier();



    return true;
}



void LinkingIdentifier::showAsTarget()
{



	_inner_1->setScale(2.0f);
	_inner_2->setScale(1.0f);
	_inner_1->setOpacity(1);
	_inner_2->setOpacity(127);
	
	_inner_1->setVisible(true);
	_inner_2->setVisible(true);


		 auto a1 = ScaleTo::create(0.999,0.01);
		 auto b1 = FadeTo::create(0.999,255);
		 auto a2 = ScaleTo::create(0.001,2);
		 auto b2 = FadeTo::create(0.001,1);

		 auto c1 = Spawn::create(a1,b1,NULL);
		 auto c2 = Spawn::create(a2,b2,NULL);

		 auto seq = Sequence::create(c1,c2,NULL);
		 auto repp = RepeatForever::create(seq);

		 _inner_1->runAction(repp);







		 auto d1 = ScaleTo::create(0.499,0.01);
		 auto e1 = FadeTo::create(0.499,255);
		 auto d2 = ScaleTo::create(0.001,2);
		 auto e2 = FadeTo::create(0.001,1);
		 auto d3 = ScaleTo::create(0.5,1);
		 auto e3 = FadeTo::create(0.5,127);

		 auto f1 = Spawn::create(d1,e1,NULL);
		 auto f2 = Spawn::create(d2,e2,NULL);
		 auto f3 = Spawn::create(d3,e3,NULL);

		 auto seq2 = Sequence::create(f1,f2,f3,NULL);
		 auto repp2 = RepeatForever::create(seq2);

		 _inner_2->runAction(repp2);




}


void LinkingIdentifier::showAsSource()
{
	_inner_1->setScale(0.01f);
	_inner_2->setScale(1.0f);

	_inner_1->setOpacity(255);
	_inner_2->setOpacity(127);

	_inner_1->setVisible(true);
	_inner_2->setVisible(true);


		 auto a1 = ScaleTo::create(0.999,2);
		 auto a2 = ScaleTo::create(0.001,0.01);

		 auto b1 = FadeTo::create(0.999,1);
		 auto b2 = FadeTo::create(0.001,255);

		 auto c1 = Spawn::create(a1,b1,NULL);
		 auto c2 = Spawn::create(a2,b2,NULL);


		 auto seq = Sequence::create(c1,c2,NULL);
		 auto repp = RepeatForever::create(seq);

		 _inner_1->runAction(repp);







		 auto d1 = ScaleTo::create(0.499,2);
		 auto d2 = ScaleTo::create(0.001,0.01);
		 auto d3 = ScaleTo::create(0.5,1.0);

		 auto e1 = FadeTo::create(0.499,1);
		 auto e2 = FadeTo::create(0.001,255);
		 auto e3 = FadeTo::create(0.5,127);

		 auto f1 = Spawn::create(d1,e1,NULL);
		 auto f2 = Spawn::create(d2,e2,NULL);
		 auto f3 = Spawn::create(d3,e3,NULL);

		 auto seq2 = Sequence::create(f1,f2,f3,NULL);
		 auto repp2 = RepeatForever::create(seq2);

		 _inner_2->runAction(repp2);

}



void LinkingIdentifier::hideIdentifier()
{
	
	_inner_1->stopAllActions();
	_inner_1->setVisible(false);

	_inner_2->stopAllActions();
	_inner_2->setVisible(false);



}








