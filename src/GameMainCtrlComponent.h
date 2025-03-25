#pragma once
#include "Component.h"
#include "ofMain.h"
#include "FontRendererComponent.h"

class GameState;

class GameMainCtrlComponent :
    public Component
{
    // このコンポーネントの private にアクセスできるようにする
    friend class GameStateGameOver;
    friend class GameStateTitle;
    friend class GameStateMain;
    friend class GameStateMainRPG;
    friend class GameStateGameCLEAR;

private:
  
public:
    GameMainCtrlComponent(GameActor* _gActor);
    virtual ~GameMainCtrlComponent();
    void gameStateStart();
    void update();

    GameState* gameState_;      // 現在のステート
    static GameStateTitle gameStateTitle_;
    static GameStateMain  gameStateMain_;
    static GameStateGameOver gameStateGameOver_;
    static GameStateMainRPG gameStateMainRPG_;
    static GameStateGameCLEAR gameStateGameClear_;

    bool isGameover_;
    int battlecountr_;
    int ScenemoveCnt_;
    int playerScore_;
    int playerLife_;
    int bombcnt_;
};

