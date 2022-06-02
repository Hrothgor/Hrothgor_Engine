/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** GizmosRenderer
*/

#include "GizmosRenderer.hpp"
#include "Ecs/GameObject.hpp"

namespace hr {
    GizmosRenderer::GizmosRenderer()
    {
    }

    GizmosRenderer::~GizmosRenderer()
    {
    }

    void GizmosRenderer::Start()
    {
    }

    void GizmosRenderer::BeginFrame()
    {
    }

    void GizmosRenderer::Draw()
    {
        BeginFrame();
        for (GameObject *object : _objects)
            object->OnDrawGizmos();
        EndFrame();
    }

    void GizmosRenderer::EndFrame()
    {
        _objects.clear();
    }

    void GizmosRenderer::RegisterObject(GameObject *object)
    {
        _objects.push_back(object);
    }

    void GizmosRenderer::End()
    {
    }
}