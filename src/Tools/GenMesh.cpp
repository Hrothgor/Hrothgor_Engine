/*
** EPITECH PROJECT, 2021
** indieStudio
** File description:
** GenMesh
*/

#include "GenMesh.hpp"

IS::GenMesh::GenMesh()
{
}

IS::GenMesh::~GenMesh()
{
}

Mesh IS::GenMesh::GenMeshSquare(float size)
{
    Mesh mesh = { 0 };

    float vertices[] = {
        -size, size, 0,
        -size, -size, 0,
        size, -size, 0,
        size, size, 0,
    };

    float texcoords[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };

    float normals[] = {
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
    };

    unsigned short indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.normals = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.normals, normals, 4*3*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(2*3*sizeof(unsigned short));
    memcpy(mesh.indices, indices, 2*3*sizeof(unsigned short));

    mesh.vertexCount = 4;
    mesh.triangleCount = 2;

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}