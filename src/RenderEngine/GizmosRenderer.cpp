/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** GizmosRenderer
*/

#include "GizmosRenderer.hpp"
#include "../Ecs/GameObject.hpp"

hr::GizmosRenderer::GizmosRenderer()
{
}

hr::GizmosRenderer::~GizmosRenderer()
{
}


void hr::GizmosRenderer::Start()
{
}

void hr::GizmosRenderer::Draw()
{
    Start();
    for (GameObject *object : _objects)
        object->OnDrawGizmos();
    End();
}

void hr::GizmosRenderer::End()
{
    _objects.clear();
}

void hr::GizmosRenderer::RegisterObject(GameObject *object)
{
    _objects.push_back(object);
}