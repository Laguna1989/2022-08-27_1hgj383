#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "cannon.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <laser.hpp>
#include <object_group.hpp>
#include <player.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Vignette> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<Player> m_player;

    std::shared_ptr<jt::ObjectGroup<Laser>> m_lasers;
    std::shared_ptr<jt::ObjectGroup<Cannon>> m_cannons;

    bool m_running { true };
    bool m_hasEnded { false };

    int m_scoreP1 { 0 };
    int m_scoreP2 { 0 };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void endGame();
    void spawnLaser(jt::Vector2f const& pos, jt::Vector2f const& velocity);
    void checkLaserPlayerCollision();
};

#endif
