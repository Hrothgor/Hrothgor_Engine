/*
** EPITECH PROJECT, 2021
** 3D
** File description:
** DisplayManager
*/

#include "DisplayManager.hpp"

IS::DisplayManager::DisplayManager()
{
    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    InitWindow(WIDTH, HEIGHT, "Indie Studio Window");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
	ToggleFullscreen();
    // SetTargetFPS(120);
    InitAudioDevice();
    load();
}

IS::DisplayManager::~DisplayManager()
{
}

void IS::DisplayManager::load()
{
    GLOBAL::camera = new Camera;

    GLOBAL::_texturedModels["dragon"] = new TexturedModel("dragon");
    GLOBAL::_texturedModels["bomb"] = new TexturedModel("bomb");
    GLOBAL::_texturedModels["crate"] = new TexturedModel("crate");

    GLOBAL::_sounds["bombExplosion"] = new Sounds("bomb_explosion.ogg", false);
    GLOBAL::_sounds["bombFuse"] = new Sounds("bomb_fuse.ogg", false);
    GLOBAL::_sounds["background"] = new Sounds("background_music.ogg", true);

    GLOBAL::_particleTexturedModels["burn"] = new ParticleTexturedModel(GenMesh::GenMeshSquare(0.5), ASSETS_PATH"ressources/burn.png", 4);
    GLOBAL::_particleTexturedModels["smoke"] = new ParticleTexturedModel(GenMesh::GenMeshSquare(0.5), ASSETS_PATH"ressources/smoke.png", 8);
    GLOBAL::_particleTexturedModels["cosmic"] = new ParticleTexturedModel(GenMesh::GenMeshSquare(0.5), ASSETS_PATH"ressources/cosmic.png", 4);
    GLOBAL::_particleTexturedModels["fire"] = new ParticleTexturedModel(GenMesh::GenMeshSquare(0.5), ASSETS_PATH"ressources/fire.png", 8);

    GLOBAL::_particleSystem["star"] = new ParticleSystem(100, 6, 1, 3, 1, ASSETS_PATH"ressources/particleStar.png", &_3Drenderer);
    GLOBAL::_particleSystem["burn"] = new ParticleSystem(100, 10, 0, 3, 3, *GLOBAL::_particleTexturedModels["burn"], &_3Drenderer, IS::PARTICLE_EMISSION::DIRECTIONAL);
    GLOBAL::_particleSystem["smoke"] = new ParticleSystem(50, 2, 0, 6, 5, *GLOBAL::_particleTexturedModels["smoke"], &_3Drenderer);
    GLOBAL::_particleSystem["cosmic"] = new ParticleSystem(100, 1, 0, 3, 1, *GLOBAL::_particleTexturedModels["cosmic"], &_3Drenderer, IS::PARTICLE_EMISSION::CIRCLE);

    GLOBAL::_particleSystem["smokeFeet"] = new ParticleSystem(15, 2, 0, 3, 15, *GLOBAL::_particleTexturedModels["smoke"], &_3Drenderer, IS::PARTICLE_EMISSION::FLYING);
    GLOBAL::_particleSystem["fireBomb"] = new ParticleSystem(20, 2, 0, 2, 5, *GLOBAL::_particleTexturedModels["fire"], &_3Drenderer);
    GLOBAL::_particleSystem["explosionBomb"] = new ParticleSystem(1, 0, 0, 0.8, 12, *GLOBAL::_particleTexturedModels["cosmic"], &_3Drenderer, IS::PARTICLE_EMISSION::STATIC);
    GLOBAL::_particleSystem["shinyPowerUp"] = new ParticleSystem(10, 6, 1, 2, 1, ASSETS_PATH"ressources/particleStar.png", &_3Drenderer);

    GLOBAL::_entities.push_back(new Entity(*GLOBAL::_texturedModels["dragon"], { 120, 10, 60 }, { 0, 90, 0 }, 2));
}

void IS::DisplayManager::run()
{
    ///// 3D INIT /////
    _3Drenderer.addLight(LightValue({ 2000, 3000, 2000 }, WHITE));
    ///////////////////

    ///// 2D INIT /////
    // GLOBAL::_sounds["background"]->play();
    ///////////////////

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            //// UPDATE GAME ////
            GLOBAL::camera->update();
            ////////////
            for (auto &sound : GLOBAL::_sounds)
                UpdateMusicStream(sound.second->getMusic());
            for (int i = 0; i < GLOBAL::_entities.size(); i++)
                if (GLOBAL::_entities[i]->IsActive())
                    _3Drenderer.addEntity(0, GLOBAL::_entities[i]);
            //// 3D ////
            _3Drenderer.render(GLOBAL::_scene, GLOBAL::camera);
            ////////////
            //// 2D ////
            _2Drenderer.render(GLOBAL::_scene);
            /////////////

        }
        EndDrawing();
    }
    clean();
    CloseAudioDevice();
    CloseWindow();
}

void IS::DisplayManager::clean()
{
    for (auto &texturedModel : GLOBAL::_texturedModels)
        texturedModel.second->clean();
    for (auto &particleTexturedModel : GLOBAL::_particleTexturedModels)
        particleTexturedModel.second->clean();
    GLOBAL::_particleSystem.clear();
    GLOBAL::_entities.clear();
}