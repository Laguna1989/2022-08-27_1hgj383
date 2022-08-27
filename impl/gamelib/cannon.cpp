#include "cannon.hpp"
#include <game_properties.hpp>
#include <random/random.hpp>

void Cannon::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(jt::Vector2f { 12.0f, 12.0f }, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);

    auto const r = jt::Random::getInt(0, 3);

    float const margin = 10.0f;
    float const shotVelocity = GP::ShotVelocity();
    if (r == 0) {
        // top
        m_shotVelocity = jt::Vector2f { 0.0f, shotVelocity };
        m_shape->setPosition(
            jt::Vector2f { jt::Random::getFloat(margin, GP::GetScreenSize().x - margin), 6.0f });
    } else if (r == 1) {
        // bot
        m_shotVelocity = jt::Vector2f { 0.0f, -shotVelocity };
        m_shape->setPosition(
            jt::Vector2f { jt::Random::getFloat(margin, GP::GetScreenSize().x - margin),
                GP::GetScreenSize().y - 6.0f });
    } else if (r == 2) {
        // left
        m_shotVelocity = jt::Vector2f { shotVelocity, 0.0f };
        m_shape->setPosition(
            jt::Vector2f { 6.0f, jt::Random::getFloat(margin, GP::GetScreenSize().y - margin) });
    } else if (r == 3) {
        // left
        m_shotVelocity = jt::Vector2f { -shotVelocity, 0.0f };
        m_shape->setPosition(jt::Vector2f { GP::GetScreenSize().x - 6.0f,
            jt::Random::getFloat(margin, GP::GetScreenSize().y - margin) });
    }
}

void Cannon::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);
    m_shotTimer -= elapsed;

    float const shotPreFlickerTimer = 1.0f;
    if (m_shotTimer <= shotPreFlickerTimer && m_shotTimer + elapsed >= shotPreFlickerTimer) {
        m_shape->flicker(shotPreFlickerTimer);
    }

    if (m_shotTimer <= 0.0f) {
        m_shotTimer = 5.0f;
        if (m_shotCallback) {
            m_shotCallback(m_shape->getPosition(), m_shotVelocity);
        }
    }
}
void Cannon::doDraw() const { m_shape->draw(renderTarget()); }

void Cannon::setShotCallback(std::function<void(jt::Vector2f const&, jt::Vector2f const&)> cb)
{
    m_shotCallback = cb;
}
