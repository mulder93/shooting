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

    void update(float delta) override;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;

private:
    void startGame();
    void endGame();

    Pistol* createPistol();
    void initTargets();

    void updateScoreLabel();
    void updateTimerLabel();

    std::shared_ptr<CollisionDetector> m_collisionDetector;
    Pistol* m_pistol = nullptr;
    cocos2d::Node* m_targetsHolder = nullptr;

    cocos2d::Label* m_scoreLabel = nullptr;
    cocos2d::Label* m_timerLabel = nullptr;

    int m_score = 0;
    float m_timeLeft = 50.0f;
};
