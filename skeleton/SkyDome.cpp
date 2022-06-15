#include "SkyDome.h"

void SkyDome::Init(void)
{
	model = MV1LoadModel("model/Skydome/SkyDome.mv1");
}

void SkyDome::Update(void)
{
}

void SkyDome::Draw(void)
{
	MV1DeleteModel(model);
}

void SkyDome::Release(void)
{
}

void SkyDome::ChangeState(STATE state)
{
}
