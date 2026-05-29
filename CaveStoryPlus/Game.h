#pragma once
#include "BaseGame.h"
#include "MusicManager.h"
#include "Camera.h"

#include <SDL2/SDL_ttf.h>

extern const float g_ScreenWidth;
extern const float g_ScreenHeight;
extern const float g_TileSize;
extern const float g_TileCols;
extern const float g_TileRows;

class PlayerGUI;
class TextManager;
class DialogManager;
class SoundManager;
class Player;
class Level;
class Texture;
class Editor;

class Game final : public BaseGame
{
  public:
    explicit Game(const Window &window);
    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;
    Game(Game &&other) = delete;
    Game &operator=(Game &&other) = delete;
    // http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
    ~Game();

    void Update(float elapsedSec) override;
    void Draw() const override;

    // Event handling
    void ProcessKeyDownEvent(const SDL_KeyboardEvent &e) override;
    void ProcessKeyUpEvent(const SDL_KeyboardEvent &e) override;
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent &e) override;
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent &e) override;
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent &e) override;

    void Restart();
    void SwitchLevel(Level *pLevel);

    static inline Vector2f GetMousePosition()
    {
        return m_LastMousePos;
    }

    DialogManager *GetDialogManager() const
    {
        return m_pDialogManager;
    }

    TextManager *GetTextManager() const
    {
        return m_pTextManager;
    }

    Level *GetActiveLevel() const
    {
        return m_pActiveLevel;
    }

    Player *GetPlayer() const
    {
        return m_pPlayer;
    }

    MusicManager &GetMusicManager()
    {
        return m_MusicManager;
    }

    SoundManager *GetSoundManager() const
    {
        return m_pSoundManager;
    }

  private:
    static Vector2f m_LastMousePos;

    Camera m_Camera;
    DialogManager *m_pDialogManager{};
    TextManager *m_pTextManager{};
    Level *m_pActiveLevel{};
    Level *m_pNextLevel{};
    Player *m_pPlayer{};
    Editor *m_pEditor{};
    SoundManager *m_pSoundManager{};
    MusicManager m_MusicManager{};

    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;
};
