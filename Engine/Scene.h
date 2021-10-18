#pragma once
class CScene
{
public:
	enum OBJ_ID { OBJ_BG, OBJ_PLAYER, OBJ_JELLY, OBJ_END };

protected:
	CScene();
	virtual ~CScene();

public:
	CGameObject* Get_Player() { return m_listObject[OBJ_PLAYER].front(); }
	list<CGameObject*>	Get_ObjectList(size_t eID) { return m_listObject[eID]; }

	void Add_GameObject(OBJ_ID eID, CGameObject* pObject);

public:
	virtual void			Start_Scene(void);
	virtual int				Update_Scene(const float& fTimeDelta);
	virtual void			LateUpdate_Scene(const float& fTimeDelta);
	virtual void			Render_Scene(void);

protected:
	list<CGameObject*>		m_listObject[CScene::OBJ_END];
};

