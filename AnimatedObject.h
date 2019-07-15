#ifndef animatedobjectH
#define animatedobjectH

#include "Object.h"

class MAnimatedObject: public MObject
{
protected:
	stAnimation* Animation;
	unsigned char CurrentAnimation;
	unsigned int CurrentFrame;
public:
	MAnimatedObject();
	~MAnimatedObject();
	bool SetAnimation(stAnimation* inAnimation);
	bool SetCurrentAnimation(unsigned char inCurrentAnimation);
	bool SetCurrentFrame(unsigned int inCurrentFrame);
	bool SetRandomFrame();
	void IncAnimationFrame();
	unsigned char GetCurrentAnimation();
};

#endif
