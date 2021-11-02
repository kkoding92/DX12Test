#pragma once

class CJelly;
class CKingJelly;
class CMainScene : public CScene
{
public:
	CMainScene();
	virtual ~CMainScene();

private:
	void			Create_GameObject();
	void			Check_Collision();

public:
	void			Start_Scene(void) override;
	int				Update_Scene(const float& fTimeDelta) override;
	void			LateUpdate_Scene(const float& fTimeDelta) override;
	void			Render_Scene(void) override;

private:
	int				m_iJellyCount = 0;
	CJelly*			m_pBaseJelly;
	CKingJelly*		m_pBaseKingJelly;
};

