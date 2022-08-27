#ifndef INC_1HGJ383_LASER_HPP
#define INC_1HGJ383_LASER_HPP

#include "sprite.hpp"
#include <game_object.hpp>
#include <shape.hpp>
#include <memory>

class Laser : public jt::GameObject {
public:
    Laser(jt::Vector2f const& pos, jt::Vector2f const& velocity);
    std::shared_ptr<jt::Shape> m_shape;

    std::vector<jt::Vector2f> getCollisionPoints() const;

private:
    jt::Vector2f m_velocity { 0.0f, 0.0f };
    jt::Vector2f m_initialPos { 0.0f, 0.0f };

    std::shared_ptr<jt::Sprite> m_glow;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // INC_1HGJ383_LASER_HPP
