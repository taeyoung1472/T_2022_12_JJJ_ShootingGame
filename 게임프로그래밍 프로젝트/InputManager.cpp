#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Init(HWND hWnd)
{
	m_hwnd = hWnd;
	m_states.resize(KEY_CODE_COUNT, KEY_STATE::NONE);
}

void InputManager::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (m_hwnd != hwnd)
	{
		for (UINT32 key = 0; key < KEY_CODE_COUNT; ++key)
			m_states[key] = KEY_STATE::NONE;
		return;
	}

	BYTE asciiKeys[KEY_CODE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (UINT32 key = 0; key < KEY_CODE_COUNT; ++key)
	{
		// Ű�� ���� ������ true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = m_states[key];

			// ���� �����ӿ� Ű�� ���� �������� üũ
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = m_states[key];

			// ���� �����ӿ� Ű�� ���� �������� üũ
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&m_mousePos);
	::ScreenToClient(m_hwnd, &m_mousePos);
}
