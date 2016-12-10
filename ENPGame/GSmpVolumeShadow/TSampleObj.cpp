#include "TSampleObj.h"

bool TSampleObj::PreDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand)
{
	pUnit->m_pModel->PreRender(pContext);
	return true;
}
bool TSampleObj::PostDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand)
{
	Draw(pContext, pUnit, bCommand);
	return true;
}

TSampleObj::TSampleObj()
{
}


TSampleObj::~TSampleObj()
{
}
