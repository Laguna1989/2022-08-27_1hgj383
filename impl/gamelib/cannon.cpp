#include "cannon.hpp"
#include <random/random.hpp>

void Cannon::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(jt::Vector2f { 12.0f, 12.0f }, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);

    auto const r = jt::Random::getInt(0, 3);
    //    if (r == 0) { }
    m_shotVelocity = jt::Vector2f { 0, 100 };
    m_shape->setPosition(jt::Vector2f { 300, 0.0f });
}

void Cannon::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);
    m_shotTimer -= elapsed;
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
