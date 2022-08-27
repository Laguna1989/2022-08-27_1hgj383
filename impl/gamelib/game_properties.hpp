﻿#ifndef GAME_GAMEPROPERTIES_HPP
#define GAME_GAMEPROPERTIES_HPP

#include <color/color.hpp>
#include <color/palette.hpp>
#include <vector.hpp>
#include <string>

class GP {
public:
    GP() = delete;

    static std::string GameName() { return "Lasergrid"; }
    static std::string AuthorName() { return "Laguna_999"; }
    static std::string JamName() { return "1hgj383"; }
    static std::string JamDate() { return "2022-08-27"; }

    static jt::Vector2f GetWindowSize() { return jt::Vector2f { 1200, 800 }; }
    static float GetZoom() { return 2.0f; }
    static jt::Vector2f GetScreenSize() { return GetWindowSize() * (1.0f / GetZoom()); }

    static jt::Color PaletteBackground() { return GP::getPalette().getColor(0); }
    static jt::Color PaletteFontFront() { return GP::getPalette().getColor(6); }
    static jt::Color PaletteFontShadow() { return GP::getPalette().getColor(2); }
    static jt::Color PaletteFontCredits() { return GP::getPalette().getColor(5); }

    static jt::Palette getPalette();

    static int PhysicVelocityIterations();
    static int PhysicPositionIterations();
    static jt::Vector2f PlayerSize();
    static float const ShotVelocity() { return 175.0f; };
    static float CannonFireTimer();
    static float CannonSpawnInterval();
};

#endif
