#include "stdafx.h"
#include "AnimatedObject.h"

MAnimatedObject::MAnimatedObject():MObject()
{
}

MAnimatedObject::~MAnimatedObject()
{
}

bool MAnimatedObject::SetAnimation(stAnimation* inAnimation)
{
	if(!inAnimation) return false;
	Animation = inAnimation;
	
	return true;
}

bool MAnimatedObject::SetCurrentAnimation(unsigned char inCurrentAnimation)
{
	if(inCurrentAnimation >= sizeof(Animation))
	{
		LogFile<<"Animation: "<<inCurrentAnimation<<" not exist"<<endl;
		return false;
	}
	if(Animation[inCurrentAnimation].Count > 25)
	{
		LogFile<<"To many animation frames"<<endl;
		return false;
	}
	CurrentAnimation = inCurrentAnimation;
	if(CurrentAnimation != 1)
	{
		CurrentFrame = 0;
		SetTexId(Animation[CurrentAnimation].Texture[CurrentFrame].Id);
	}
	
	return true;
}

bool MAnimatedObject::SetCurrentFrame(unsigned int inCurrentFrame)
{
	if(inCurrentFrame >= Animation[CurrentAnimation].Count)
	{
		LogFile<<"Frame: "<<inCurrentFrame<<" not exist"<<endl;
		return false;
	}
	CurrentFrame = inCurrentFrame;
	
	return true;
}

bool MAnimatedObject::SetRandomFrame()
{
	CurrentFrame = rand() % Animation[CurrentAnimation].Count;
	return true;
}

void MAnimatedObject::IncAnimationFrame()
{
	switch(Animation[CurrentAnimation].Type)
	{
		case 1:
			CurrentFrame ++;
			if(CurrentFrame >= Animation[CurrentAnimation].Count) CurrentFrame = 0;
			SetTexId(Animation[CurrentAnimation].Texture[CurrentFrame].Id);
			break;
		case 2:
			if(CurrentFrame < Animation[CurrentAnimation].Count - 1)
			{
				CurrentFrame ++;
				SetTexId(Animation[CurrentAnimation].Texture[CurrentFrame].Id);
			}
			else
			{
				if(Animation[CurrentAnimation].Next != CurrentAnimation)
				{
					SetCurrentAnimation(Animation[CurrentAnimation].Next);
					SetCurrentFrame(0);
				}
			}
			break;
		default:
			break;
	}
	
}
unsigned char MAnimatedObject::GetCurrentAnimation()
{
	return CurrentAnimation;
}
