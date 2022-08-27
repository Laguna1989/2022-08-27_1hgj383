#include "game_properties.hpp"

jt::Palette GP::getPalette()
{
    static auto const p = jt::Palette::parseGPL(R"(GIMP Palette
#Palette Name: moondrom
#Description: inspired by andylittle's palette https://www.deviantart.com/andylittle
#Colors: 8
42	36	43	2a242b
70	64	64	464040
119	91	91	775b5b
204	112	72	cc7048
215	181	80	d7b550
104	168	171	68a8ab
144	213	156	90d59c
255	255	178	ffffb2
)");
    return p;
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 16.0f, 16.0f }; }
float GP::CannonFireTimer() { return 3.0f; }
float GP::CannonSpawnInterval() { return 4.1f; }
