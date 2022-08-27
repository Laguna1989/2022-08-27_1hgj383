#include "player.hpp"
#include <game_interface.hpp>
#include <game_properties.hpp>

void Player::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeCircle(16, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_shape->setPosition(0.5f * GP::GetScreenSize());
    m_shape->setColor(GP::getPalette().getColor(6));
}
void Player::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);

    auto& input = getGame()->input();
    jt::Vector2f dir { 0.0f, 0.0f };
    if (input.keyboard()->pressed(jt::KeyCode::A) || input.keyboard()->pressed(jt::KeyCode::Left)) {
        dir += jt::Vector2f { -1.0f, 0.0f };
    }
    if (input.keyboard()->pressed(jt::KeyCode::D)
        || input.keyboard()->pressed(jt::KeyCode::Right)) {
        dir += jt::Vector2f { 1.0f, 0.0f };
    }
    if (input.keyboard()->pressed(jt::KeyCode::W) || input.keyboard()->pressed(jt::KeyCode::Up)) {
        dir += jt::Vector2f { 0.0f, -1.0f };
    }
    if (input.keyboard()->pressed(jt::KeyCode::S) || input.keyboard()->pressed(jt::KeyCode::Down)) {
        dir += jt::Vector2f { 0.0f, 1.0f };
    }

    auto pos = m_shape->getPosition();
    float velocity = 150.0f;
    pos += velocity * elapsed * dir;

    float const margin { 10.0f };

    if (pos.x < margin) {
        pos.x = margin;
    } else if (pos.x >= GP::GetScreenSize().x - margin) {
        pos.x = GP::GetScreenSize().x - margin;
    }
    if (pos.y < margin) {
        pos.y = margin;
    } else if (pos.y >= GP::GetScreenSize().y - margin) {
        pos.y = GP::GetScreenSize().y - margin;
    }

    m_shape->setPosition(pos);

    m_hurtTimer -= elapsed;
}

void Player::doDraw() const { m_shape->draw(renderTarget()); }
bool Player::canBeHurt() const { return m_hurtTimer <= 0; }
void Player::hurt()
{
    m_hurtTimer = 0.75f;
    m_shape->flash(0.5f, GP::getPalette().getColor(3));
    m_shape->flicker(0.5f);
}
