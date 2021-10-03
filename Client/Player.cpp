#include "stdafx.h"
#include "Player.h"

Player::Player(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

Player::~Player(void)
{
}

HRESULT Player::Add_Component(void)
{
	return S_OK;
}

void Player::Start_GameObject(void)
{
}

int Player::Update_GameObject(const float& fTimeDelta)
{
	return 0;
}

void Player::LateUpdate_GameObject(const float& fTimeDelta)
{
}

void Player::Render_GameObject(void)
{

}
