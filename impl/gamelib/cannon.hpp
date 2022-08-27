#ifndef INC_1HGJ383_CANNON_HPP
#define INC_1HGJ383_CANNON_HPP

#include <game_object.hpp>
#include <shape.hpp>
#include <functional>
#include <memory>

class Cannon : public jt::GameObject {
public:
    std::shared_ptr<jt::Shape> m_shape;

    void setShotCallback(std::function<void(jt::Vector2f const&, jt::Vector2f const&)> cb);

private:
    jt::Vector2f m_shotVelocity { 0.0f, 0.0f };

    std::function<void(jt::Vector2f const&, jt::Vector2f const&)> m_shotCallback { nullptr };

    float m_shotTimer { 3.0f };

    float m_rand1 { 1.0f };
    float m_rand2 { 0.0f };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // INC_1HGJ383_CANNON_HPP
