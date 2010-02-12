#include "ExampleApplication.h"

class TutorialApplication : public ExampleApplication
{
protected:
public:
    TutorialApplication()
    {
    }

    ~TutorialApplication() 
    {
    }
protected:
    void createScene(void)
    {
    }
};

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    // Create application object
    TutorialApplication app;
    try {
        app.go();
    } catch( Exception& e ) {
        MessageBox( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
    return 0;
}