#pragma once

#include "cocos2d.h"
#include "PanelButtonRestore.h"
#include "TextOperand.h"



class ModuleStorage : public cocos2d::Node
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  


	// implement the "static create()" method manually
	CREATE_FUNC(ModuleStorage);


	void initComponents(PanelButtonStore* panelButtonStore , PanelButtonRestore* panelButtonRestore);

	void setStorageIndex(int index );

private:

	int _storageIndex;

	PanelButtonStore* _panelButtonStore;
	PanelButtonRestore* _panelButtonRestore;
	TextOperand* _textOperand;


	void updateStoreValue(cocos2d::EventCustom* event);

	void _updateStoreValue();

};


