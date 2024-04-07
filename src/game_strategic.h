#pragma once

#include "game_state.h"
#include "gamemode.h"
#include "mapview.h"
#include "ui_base.h"
#include "wave_function.h"

class ModeStrategicView : public GameMode
{
    enum class MapEventType
    {
        NO_EVENT,
        ENCOUNTER,
        SLEEP,
        GATHERING,
    };

    GameState _state;
    WaveMap _map;
    MapView _mapView;

    bool runBattle = false;
    bool _hotkeysShown = true;
    float _scrollTimer = 0.0f;
    float _eventTimer = 0.0f;
    float _eventSubtimer = 0.0f;
    MapEventType _eventType = MapEventType::NO_EVENT;
    UIContainer temporaryUI;
    std::unique_ptr<Window> activeWindow = nullptr;

    Label _lResources;
    Button _bOpenMenu;
    Button _bEndTurn;
    Window _menuPopup;

    void passTime( int amount );
    void executeEvent( float deltaTime );
    void processReward( const Reward & reward );

public:
    ModeStrategicView( GameState & state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;

    bool hasEventRunning() const;
};
