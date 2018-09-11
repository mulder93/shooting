//
//  GameLayer.hpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include <memory>
#include "cocos2d.h"
#include "EventListenerHolder.hpp"

class CollisionDetector;
class Pistol;
class EnergyBar;
class Target;

class GameLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GameLayer);
    bool init() override;

    void update(float delta) override;
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onMouseMoved(cocos2d::EventMouse* event);

private:
    void startGame();
    void endGame();

    cocos2d::EventListener* createTouchListener();
    cocos2d::EventListener* createMouseListener();

    Pistol* createPistol() const;
    void resetTargets();
    void generateFastTarget(float);
    void addTarget(Target* target);

    void updateScoreLabel();
    void updateTimerLabel();
    void showResults();

    void rotatePistol(const cocos2d::Vec2& inputPosition);

    EventListenerHolder m_eventListenerHolder;
    std::shared_ptr<CollisionDetector> m_collisionDetector;

    cocos2d::Node* m_targetsHolder = nullptr;
    cocos2d::Label* m_scoreLabel = nullptr;
    cocos2d::Label* m_timerLabel = nullptr;
    cocos2d::Label* m_resultLabel = nullptr;

    Pistol* m_pistol = nullptr;
    EnergyBar* m_energyBar = nullptr;

    int m_score = 0;
    float m_timeLeft = 50.0f;
    bool m_playing = false;
};