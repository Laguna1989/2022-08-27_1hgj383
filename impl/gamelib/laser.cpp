#include "laser.hpp"
#include <game_properties.hpp>

Laser::Laser(jt::Vector2f const& pos, jt::Vector2f const& velocity)
{
    m_initialPos = pos;
    m_velocity = velocity;
}

void Laser::doCreate()
{
    m_glow = std::make_shared<jt::Sprite>("#g#32#150", textureManager());

    m_glow->setColor(GP::getPalette().getColor(7));
    m_shape = std::make_shared<jt::Shape>();
    if (m_velocity.x == 0) {
        m_shape->makeRect(jt::Vector2f { 2, 16 }, textureManager());

        m_glow->setScale(jt::Vector2f { 0.3f, 1.0f });

#if JT_ENABLE_WEB
        m_glow->setOrigin(jt::OriginMode::CENTER);
        m_glow->setOffset(jt::Vector2f { 13, 1 });
#else
        m_glow->setOrigin(jt::OriginMode::CENTER);

#endif

    } else {
        m_shape->makeRect(jt::Vector2f { 16, 2 }, textureManager());
        m_glow->setScale(jt::Vector2f { 1.0f, 0.3f });
#if JT_ENABLE_WEB
        m_glow->setOrigin(jt::OriginMode::CENTER);
        m_glow->setOffset(jt::Vector2f { 1, 13 });
#else
        m_glow->setOrigin(jt::OriginMode::CENTER);

#endif
    }
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_shape->setPosition(m_initialPos);
    m_shape->setColor(GP::getPalette().getColor(7));
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

    m_glow->setPosition(pos);
    m_glow->update(elapsed);
}

void Laser::doDraw() const
{
    m_shape->draw(renderTarget());
    m_glow->draw(renderTarget());
}

std::vector<jt::Vector2f> Laser::getCollisionPoints() const
{
    std::vector<jt::Vector2f> points;

    if (m_velocity.x == 0) {
        points.push_back(m_shape->getPosition() + jt::Vector2f { 0, -8.0f });
        points.push_back(m_shape->getPosition() + jt::Vector2f { 0, 0.0f });
        points.push_back(m_shape->getPosition() + jt::Vector2f { 0, 8.0f });
    } else {
        points.push_back(m_shape->getPosition() + jt::Vector2f { -8.0f, 0.0f });
        points.push_back(m_shape->getPosition() + jt::Vector2f { 0.0f, 0.0f });
        points.push_back(m_shape->getPosition() + jt::Vector2f { 8.0f, 0.0f });
    }

    return points;
}
