#pragma once

#include <Akila/core/Core.hpp>
#include <Akila/entities/Transform.hpp>

#include <iostream>
#include <Ecosystem/utils/Random.hpp>
#include <Ecosystem/simulation/Simulation.hpp>

#include <Ecosystem/app/MouseCamera.hpp>

class AppLayer: public Akila::Layer {
private:
	int uiTerrainSize;
	Simulation simulation;
	std::shared_ptr<MouseCamera> camera;

public:
	AppLayer();
	void setCamaraToMapCenter();
	void update() override;
	void draw() override;
	void drawImGui() override;
};
