#pragma once

#include "PanelButton.h"


class PanelButtonStore : public PanelButton
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


	// implement the "static create()" method manually
	CREATE_FUNC(PanelButtonStore);

	void setStorageIndex(int index);

protected:

	int _storageIndex;


	virtual void onPressed();



};


