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
    std::shared_ptr<CollisionDetector> m_collisionDetector;
    Pistol* m_pistol = nullptr;
    int m_score = 0;
};
