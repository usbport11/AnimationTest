#ifndef game2H
#define game2H

#include "Window.h"
#include "AnimatedObject.h"
#include "TextureLoader.h"

class MGame2: public MWindow
{
private:
	//statuses
	bool Pause;
	
	bool* Key;
	
	//clases
	MTextureLoader* TextureLoader;
	stAnimation* Animation;
    MAnimatedObject* AnimatedObject;
	
	//viewbox
	stViewBox ViewBox;
	
	//overload virtual functions
	void OnDraw();
	void OnKeyUp(WPARAM wParam);
	void OnKeyDown(WPARAM wParam);
	void OnMainTimer();
	void OnFrameTimer();
	void OnSize();
	
	//local
	void Start();
	void Stop();
	
public:
	MGame2();
	~MGame2();
	bool Initialize();
	bool LoadConfig();
	void OnClose();
};

#endif
