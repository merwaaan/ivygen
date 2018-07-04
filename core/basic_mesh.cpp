/**************************************************************************************
**
**  Copyright (C) 2006 Thomas Luft, University of Konstanz. All rights reserved.
**
**  This file is part of the Ivy Generator Tool.
**
**  This program is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the
**  Free Software Foundation; either version 2 of the License, or (at your
**  option) any later version.
**  This program is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
**  for more details.
**  You should have received a copy of the GNU General Public License along
**  with this program; if not, write to the Free Software Foundation,
**  Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
**
***************************************************************************************/

#include "basic_mesh.h"
#include <algorithm>

BasicMesh::BasicMesh()
{
    boundingSphereRadius = 1.0f;
    boundingSpherePos = Vector3d(0.0f, 0.0f, 0.0f);
}

BasicMesh::~BasicMesh()
{
}

void BasicMesh::reset()
{
    vertices.clear();
    normals.clear();
    texCoords.clear();
    triangles.clear();

    boundingSphereRadius = 1.0f;
    boundingSpherePos = Vector3d(0.0f, 0.0f, 0.0f);
}

void BasicMesh::prepareData()
{
    //update pointers of triangle
    for (std::vector<BasicTriangle>::iterator t = triangles.begin(); t != triangles.end(); ++t)
    {
        t->v0 = &vertices[t->v0id - 1];
        t->v1 = &vertices[t->v1id - 1];
        t->v2 = &vertices[t->v2id - 1];

        if (t->n0id != 0) t->n0 = &normals[t->n0id - 1];
        if (t->n1id != 0) t->n1 = &normals[t->n1id - 1];
        if (t->n2id != 0) t->n2 = &normals[t->n2id - 1];

        if (t->t0id != 0) t->t0 = &texCoords[t->t0id - 1];
        if (t->t1id != 0) t->t1 = &texCoords[t->t1id - 1];
        if (t->t2id != 0) t->t2 = &texCoords[t->t2id - 1];
    }

    //compute bounding sphere
    boundingSpherePos = Vector3d(0.0f, 0.0f, 0.0f);

    for (std::vector<BasicVertex>::iterator v = vertices.begin(); v != vertices.end(); ++v)
    {
        boundingSpherePos += v->pos;
    }

    boundingSpherePos /= (float)vertices.size();

    boundingSphereRadius = 0.0f;

    for (std::vector<BasicVertex>::iterator v = vertices.begin(); v != vertices.end(); ++v)
    {
        boundingSphereRadius = std::max<float>(boundingSphereRadius, Vector3d::getLength(v->pos - boundingSpherePos));
    }
}

void BasicMesh::calculateVertexNormals()
{
    normals.clear();

    normals.resize(vertices.size());

    for (std::vector<BasicTriangle>::iterator t = triangles.begin(); t != triangles.end(); ++t)
    {
        Vector3d tmp1(t->v0->pos - t->v1->pos);

        Vector3d tmp2(t->v1->pos - t->v2->pos);

        t->norm = Vector3d::crossProduct(tmp1, tmp2);

        t->norm.normalize();
    }

    for (std::vector<BasicTriangle>::iterator t = triangles.begin(); t != triangles.end(); ++t)
    {
        t->n0id = t->v0id;

        t->n0 = &normals[t->n0id - 1];

        t->n0->dir += t->norm;


        t->n1id = t->v1id;

        t->n1 = &normals[t->n1id - 1];

        t->n1->dir += t->norm;


        t->n2id = t->v2id;

        t->n2 = &normals[t->n2id - 1];

        t->n2->dir += t->norm;
    }

    for (std::vector<BasicNormal>::iterator n = normals.begin(); n != normals.end(); ++n)
    {
        n->dir.normalize();
    }
}

void BasicMesh::flipNormals()
{
    for (std::vector<BasicTriangle>::iterator t = triangles.begin(); t != triangles.end(); ++t)
    {
        t->norm *= -1.0f;
    }

    for (std::vector<BasicNormal>::iterator n = normals.begin(); n != normals.end(); ++n)
    {
        n->dir *= -1.0f;
    }
}
