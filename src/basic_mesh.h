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


#ifndef BASICMESH_H
#define BASICMESH_H

#include "vector3d.h"
#include "vector2d.h"
#include <vector>
#include <string>

#include "core_global.h"


/** a simple vertex */
class CORESHARED_EXPORT BasicVertex
{
public:

	Vector3d pos;
};


/** a simple normal vector */
class CORESHARED_EXPORT BasicNormal
{
public:

	Vector3d dir;
};


/** a simple uv texture coordinate */
class CORESHARED_EXPORT BasicTexCoord
{
public:

	Vector2d pos;
};


/** a simple material containing only a single texture */
class CORESHARED_EXPORT BasicMaterial
{
public:

	BasicMaterial() : id(0), texObj(0) {}

	unsigned int id;

	std::string name;

	std::string texFile;

	unsigned int texObj;
};


/** a simple triangle containing vertices, normals, texCoords, and a material */
class CORESHARED_EXPORT BasicTriangle
{
public:

    BasicTriangle() : v0(NULL), v0id(0), v1(NULL), v1id(0), v2(NULL), v2id(0),
                        n0(NULL), n0id(0), n1(NULL), n1id(0), n2(NULL), n2id(0),
                        t0(NULL), t0id(0), t1(NULL), t1id(0), t2(NULL), t2id(0),
                        mat(NULL), matid(0) {}

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

	BasicMaterial* mat;
    unsigned int matid;

	Vector3d norm;
};


/** a simple triangle mesh */
class CORESHARED_EXPORT BasicMesh
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

	/** loads the textures for all materials, only png */
	bool loadTextures();

	/** creates a single display list if no materials are used, or a number of display lists for each material one */
	void createDisplayList(bool smooth = false);


public:

	std::vector<BasicVertex> vertices;

	std::vector<BasicNormal> normals;

	std::vector<BasicTexCoord> texCoords;

	std::vector<BasicMaterial> materials;

	std::vector<BasicTriangle> triangles;

	Vector3d boundingSpherePos;

	float boundingSphereRadius;

    std::string file;

	std::string path;

	unsigned int displayListObj;
};


#endif


