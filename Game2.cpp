#include "stdafx.h"
#include "Game2.h"

MGame2::MGame2():MWindow() //IMPORTANT
{
	Pause = true;
    Key = new bool [256];
    memset(Key, 0, 256);
}

MGame2::~MGame2()
{
}

bool MGame2::Initialize()
{	
    LogFile<<"Initialize Game2"<<endl;
    
    if(!WindowInitialized)
    {
    	LogFile<<"Window was not initialized"<<endl;
    	return 0;
	}
	
	//randomize
    LogFile<<"Randomize rand by time"<<endl; 
    srand(time(NULL));
    
    //read config
    int WindowSize[2];
    int ObjectSize[2];
    float TextureScale[2];
    string FileName;
    bool LinearMode;
    unsigned int txParams[2];
    string FileString;
    
    ifstream ConfigFile("config.txt");
    getline(ConfigFile, FileString);
    FileName = FileString;
    getline(ConfigFile, FileString);
    WindowSize[0] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    WindowSize[1] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    ObjectSize[0] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    ObjectSize[1] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    TextureScale[0] = (float)atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    TextureScale[1] = (float)atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    if(FileString == "true") LinearMode = true;
    else LinearMode = false;
    getline(ConfigFile, FileString);
    txParams[0] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    txParams[1] = atoi(FileString.c_str());
    getline(ConfigFile, FileString);
    
    //textures and animation
    LogFile<<"Texture loading"<<endl;
    Animation = new stAnimation [1];
    TextureLoader = new MTextureLoader;
    TextureLoader->LinearMode = LinearMode;
    Animation->Texture = TextureLoader->LoadTexture(FileName.c_str(), txParams[0], txParams[1], 0, Animation->Count);
    if(!Animation->Texture) return false;
    Animation->SetParameters(1, 0);
    
    AnimatedObject = new MAnimatedObject;
    AnimatedObject->CreateByPoints(0, 0, ObjectSize[0], ObjectSize[1]);
    if(!AnimatedObject->SetAnimation(Animation)) return false;
    if(!AnimatedObject->SetCurrentAnimation(0)) return false;
	SetWindowPos(m_hWnd, NULL, 200, 200, WindowSize[0], WindowSize[1], SWP_SHOWWINDOW);

    //viewbox
    ViewBox.Enabled = true;
    ViewBox.SetSize((float)WindowWidth, (float)WindowHeight);
   
    //VERY IMPORTANT! (Do not use game resources before textures loads)
    //start capture buttons. scene always drawing
    Pause = false;
    LogFile<<"Pause is "<<Pause<<endl;
    
    return true;
}

void MGame2::Start()
{
    Pause = false;
}

void MGame2::Stop()
{
    Pause = true;
}

void MGame2::OnDraw()
{
	AnimatedObject->Draw();
}

void MGame2::OnKeyDown(WPARAM wParam)
{
	Key[wParam] = 1;
}

void MGame2::OnKeyUp(WPARAM wParam)
{
	Key[wParam] = 0;
}

void MGame2::OnClose()
{
	Stop();
	LogFile<<"Free game resources"<<endl;
	if(Key) delete [] Key;
	if(AnimatedObject) delete AnimatedObject;
	TextureLoader->DeleteTexture(Animation->Texture, Animation->Count);
	TextureLoader->Close();
    if(TextureLoader) delete TextureLoader;
    if(Animation) delete [] Animation;
}

void MGame2::OnMainTimer()
{
	//start-stop game
	if(Key[VK_RETURN])
	{
		Pause = !Pause;
		LogFile<<"Pause = "<<Pause<<endl;
		Key[VK_RETURN] = 0;
	}
}

void MGame2::OnFrameTimer()
{
	AnimatedObject->IncAnimationFrame();
}

void MGame2::OnSize()
{
	ViewBox.SetSize((float)WindowWidth, (float)WindowHeight);
}
