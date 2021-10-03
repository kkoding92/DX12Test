#pragma once

class Player : public CGameObject
{
public:
	Player(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Player(void);

private:
	HRESULT			Add_Component(void);

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;
};

