#pragma once

#include <S3DGEngine.h>

void LoadResources();

void CreateRenderables();

s3dge::Mesh*const CreateArrowMesh();

s3dge::Mesh*const CreateRoomMesh(s3dge::Texture2D*const texture);

s3dge::Mesh*const CreateTexturedCubeUnitSize(s3dge::Texture2D*const texture);