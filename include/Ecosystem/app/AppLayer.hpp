#pragma once

#include <Akila/core/Core.hpp>
#include <Akila/entities/Transform.hpp>

#include <iostream>
#include <Ecosystem/utils/Random.hpp>
#include <Ecosystem/simulation/Terrain.hpp>

#include <Ecosystem/app/MouseCamera.hpp>

class AppLayer: public Akila::Layer {
private:
	Terrain terrain;
	bool play;
	std::shared_ptr<MouseCamera> camera;

public:
	AppLayer();
	void update() override;
	void draw() override;
	void drawImGui() override;
};
