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

#pragma once

#include "vector3d.h"
#include "vector2d.h"
#include <vector>

namespace IvyGen
{
    /** a simple vertex */
    class BasicVertex
    {
    public:

        Vector3d pos;
    };

    /** a simple normal vector */
    class BasicNormal
    {
    public:

        Vector3d dir;
    };

    /** a simple uv texture coordinate */
    class BasicTexCoord
    {
    public:

        Vector2d pos;
    };

    /** a simple triangle containing vertices, normals, texCoords, and a material */
    class BasicTriangle
    {
    public:

        BasicTriangle() : v0(nullptr), v0id(0), v1(nullptr), v1id(0), v2(nullptr), v2id(0),
            n0(nullptr), n0id(0), n1(nullptr), n1id(0), n2(nullptr), n2id(0),
            t0(nullptr), t0id(0), t1(nullptr), t1id(0), t2(nullptr), t2id(0)

        BasicVertex* v0;
        unsigned int v0id;

        BasicVertex* v1;
        unsigned int v1id;

        BasicVertex* v2;
        unsigned int v2id;

        BasicNormal* n0;
        unsigned int n0id;

        BasicNormal* n1;
        unsigned int n1id;

        BasicNormal* n2;
        unsigned int n2id;

        BasicTexCoord* t0;
        unsigned int t0id;

        BasicTexCoord* t1;
        unsigned int t1id;

        BasicTexCoord* t2;
        unsigned int t2id;

        Vector3d norm;
    };

    /** a simple triangle mesh */
    class BasicMesh
    {
    public:

        BasicMesh();
        ~BasicMesh();

        void reset();

        /** setup the triangles pointer to their vertices, normals, texCoords, and materials; computes the bounding sphere */
        void prepareData();

        /** computes the vertex normals */
        void calculateVertexNormals();

        /** flips the vertex normals */
        void flipNormals();

    public:

        std::vector<BasicVertex> vertices;
        std::vector<BasicNormal> normals;
        std::vector<BasicTexCoord> texCoords;
        std::vector<BasicTriangle> triangles;

        Vector3d boundingSpherePos;
        float boundingSphereRadius;
    };
}
