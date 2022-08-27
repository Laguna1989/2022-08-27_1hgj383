#include "state_game.hpp"
#include "math_helper.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_menu.hpp>
#include <tweens/tween_alpha.hpp>

void StateGame::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_player = std::make_shared<Player>();
    add(m_player);

    m_cannons = std::make_shared<jt::ObjectGroup<Cannon>>();
    add(m_cannons);

    auto cannon = std::make_shared<Cannon>();
    cannon->setShotCallback([this](auto const& p, auto const& v) { spawnLaser(p, v); });
    m_cannons->push_back(cannon);
    add(cannon);

    m_lasers = std::make_shared<jt::ObjectGroup<Laser>>();
    add(m_lasers);

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here
        if (getGame()->input().keyboard()->justPressed(jt::KeyCode::A)) {
            spawnLaser(jt::Vector2f { 300.0f, 0.0f }, jt::Vector2f { 0, 100.0f });
        }

        checkLaserPlayerCollision();
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchState(std::make_shared<StateMenu>());
}
std::string StateGame::getName() const { return "Game"; }

void StateGame::spawnLaser(jt::Vector2f const& pos, jt::Vector2f const& velocity)
{
    auto l = std::make_shared<Laser>(pos, velocity);
    add(l);
    m_lasers->push_back(l);
}

void StateGame::checkLaserPlayerCollision()
{

    for (auto const& laser : *m_lasers) {
        auto const l = laser.lock();

        auto const pp = m_player->m_shape->getPosition();

        for (auto const& lp : l->getCollisionPoints()) {
            auto const diff = lp - pp;
            if (jt::MathHelper::length(diff) < 16.0f) {
                l->kill();
            }
        }
    }
}
