#include "Game.h"
#include "pch.h"
#include <ctime>

void StartHeapControl();
void DumpMemoryLeaks();

#if WIN32
int SDL_main(int argv, char **args)
#else
int main(int argv, char **args)
#endif
{
    srand(static_cast<unsigned int>(time(nullptr)));

    StartHeapControl();

    Game *pGame{
        new Game{Window{"Prog2 Project \"Cave Story Plus\" - Deraeve, Bram - 1DAE25", g_ScreenWidth, g_ScreenHeight}}};
    pGame->Run();
    delete pGame;

    DumpMemoryLeaks();
    return 0;
}

void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
    // Notify user if heap is corrupt
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    // Report detected leaks when the program exits
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Set a breakpoint on the specified object allocation order number
    //_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtDumpMemoryLeaks();
#endif
}
