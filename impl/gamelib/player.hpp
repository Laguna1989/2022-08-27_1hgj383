#ifndef INC_1HGJ383_PLAYER_HPP
#define INC_1HGJ383_PLAYER_HPP

#include <game_object.hpp>
#include <shape.hpp>
#include <memory>

class Player : public jt::GameObject {
public:
    std::shared_ptr<jt::Shape> m_shape;

    bool canBeHurt() const;

    void hurt();

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    float m_hurtTimer { 0.0f };
};

#endif // INC_1HGJ383_PLAYER_HPP
