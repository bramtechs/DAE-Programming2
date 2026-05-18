#pragma once
#include "BaseGame.h"
#include "Camera.h"

#include <SDL2/SDL_ttf.h>

constexpr float g_ScreenWidth{1280.f};
constexpr float g_ScreenHeight{720.f};
constexpr float g_TileSize{32.f};
constexpr float g_TileCols{1280.f / 32.f};
constexpr float g_TileRows{720.f / 32.f};

class PlayerGUI;
class TextManager;
class DialogManager;
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

    Level* SwitchLevel(Level *pLevel);

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

  private:
    static Vector2f m_LastMousePos;

    Camera m_Camera;
    DialogManager *m_pDialogManager{};
    TextManager *m_pTextManager{};
    Level *m_pActiveLevel{};
    Level *m_pNextLevel{};
    Player *m_pPlayer{};
    PlayerGUI *m_pPlayerGUI{};
    Editor *m_pEditor{};

    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;
};
