#include "cannon.hpp"
#include "math_helper.hpp"
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

    m_shape->setColor(GP::getPalette().getColor(3));

    m_rand1 = jt::Random::getFloat(0.8f, 1.2f);
    m_rand2 = jt::Random::getFloat(0.1f, 5.0f);
}

void Cannon::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);
    m_shotTimer -= elapsed;

    auto pos = m_shape->getPosition();

    auto moveDir = jt::MathHelper::rotateBy(m_shotVelocity, 90.0f);
    auto offset = sin(getAge() * 1.5f * m_rand1 + m_rand2) * 0.17f * moveDir * elapsed;

    float const shotPreFlickerTimer = 1.0f;
    if (m_shotTimer <= shotPreFlickerTimer && m_shotTimer + elapsed >= shotPreFlickerTimer) {
        m_shape->flicker(shotPreFlickerTimer);
    }
    if (m_shotTimer <= shotPreFlickerTimer) {
        offset = jt::Vector2f { 0.0f, 0.0f };
    }

    auto newPos = pos + offset;
    float const margin { 10.0f };

    if (newPos.x < margin) {
        newPos.x = margin;
    } else if (newPos.x >= GP::GetScreenSize().x - margin) {
        newPos.x = GP::GetScreenSize().x - margin;
    }
    if (newPos.y < margin) {
        newPos.y = margin;
    } else if (newPos.y >= GP::GetScreenSize().y - margin) {
        newPos.y = GP::GetScreenSize().y - margin;
    }
    m_shape->setPosition(newPos);

    if (m_shotTimer <= 0.0f) {
        m_shotTimer = GP::CannonFireTimer() + jt::Random::getFloat(-1.0f, 1.0f);
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
