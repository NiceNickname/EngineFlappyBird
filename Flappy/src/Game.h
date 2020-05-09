#pragma once
#include <Engine.h>
#include "EntryPoint.h"
#include "GameObjects/Level.h"
#include <memory>



class Game : public Engine::App
{
private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::shared_ptr<Level> m_Level;
};