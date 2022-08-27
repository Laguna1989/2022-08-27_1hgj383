#include "laser.hpp"
#include <game_properties.hpp>

Laser::Laser(jt::Vector2f const& pos, jt::Vector2f const& velocity)
{
    m_initialPos = pos;
    m_velocity = velocity;
}

void Laser::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(jt::Vector2f { 2, 16 }, textureManager());
    m_shape->setPosition(m_initialPos);
}
void Laser::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);

    auto pos = m_shape->getPosition();
    pos += elapsed * m_velocity;
    m_shape->setPosition(pos);

    if (pos.x < -32.0f || pos.x >= GP::GetScreenSize().x + 32.0f) {
        kill();
    }

    if (pos.y < -32.0f || pos.y >= GP::GetScreenSize().y + 32.0f) {
        kill();
    }
}
void Laser::doDraw() const { m_shape->draw(renderTarget()); }
