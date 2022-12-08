#pragma once
#include <vector>
using namespace std;

enum class KeyCode
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
};

enum class KEY_STATE
{
	NONE,	
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_CODE_COUNT = static_cast<INT32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<INT32>(KEY_STATE::END),
};

class InputManager
{
private:
	InputManager();
	~InputManager();

public:
	SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

public:
	bool GetKey(KeyCode key) { return GetState(key) == KEY_STATE::PRESS; }
	bool GetKeyDown(KeyCode key) { return GetState(key) == KEY_STATE::DOWN; }
	bool GetKeyUp(KeyCode key) { return GetState(key) == KEY_STATE::UP; }

	const POINT& GetMousePos() { return m_mousePos; }

private:
	inline KEY_STATE GetState(KeyCode key) { return m_states[static_cast<UINT8>(key)]; }

private:
	HWND m_hwnd;
	vector<KEY_STATE> m_states;
	POINT m_mousePos = {};
};

