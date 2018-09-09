//
//  GameLayer.hpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include <memory>
#include "cocos2d.h"

class CollisionDetector;
class Pistol;

class GameLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GameLayer);
    bool init() override;
    ~GameLayer();

    void update(float delta) override;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onMouseMoved(cocos2d::EventMouse* event);

private:
    void startGame();
    void endGame();

    Pistol* createPistol();
    void resetTargets();

    void updateScoreLabel();
    void updateTimerLabel();
    void showResults();

    void onInputMoved(const cocos2d::Vec2& location, const cocos2d::Vec2& previousLocation);

    cocos2d::EventListenerTouchOneByOne* m_touchListener = nullptr;
    cocos2d::EventListenerMouse* m_mouseListener = nullptr;

    std::shared_ptr<CollisionDetector> m_collisionDetector;
    Pistol* m_pistol = nullptr;
    cocos2d::Node* m_targetsHolder = nullptr;

    cocos2d::Label* m_scoreLabel = nullptr;
    cocos2d::Label* m_timerLabel = nullptr;
    cocos2d::Label* m_resultLabel = nullptr;
    cocos2d::ProgressTimer* m_energyBar = nullptr;

    int m_score = 0;
    float m_timeLeft = 50.0f;
    bool m_playing = false;
    cocos2d::Vec2 m_mousePreviousPosition{0.0f, 0.0f};
};
