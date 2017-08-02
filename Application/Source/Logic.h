#pragma once

#include <S3DGEngine.h>

s3dge::Mesh* CreateArrowMesh();

s3dge::Mesh* CreateRoomMesh(s3dge::Texture2D* texture, const float textureNum);

s3dge::Mesh* CreateTexturedCubeUnitSize(s3dge::Texture2D* texture, const float textureNum);