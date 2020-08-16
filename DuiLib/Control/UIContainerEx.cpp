#include "stdafx.h"
#include "UIContainerEx.h"
#include <atlconv.h>
namespace DuiLib
{
	IMPLEMENT_DUICONTROL(CContainerExUI)
		CContainerExUI::CContainerExUI() : m_uButtonState(0)
	{
			pGif = NULL;
			b_hotgif = false;
			b_normalgif = false;
	}

	CContainerExUI::~CContainerExUI()
	{
	}

	LPCTSTR CContainerExUI::GetClass() const
	{
		return _T("CContainerExUI");
	}

	LPVOID CContainerExUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcsicmp(pstrName, DUI_CTR_CONTAINEREX) == 0) return static_cast<CContainerExUI*>(this);
		return CContainerUI::GetInterface(pstrName);
	}

	void CContainerExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcsicmp(pstrName, _T("hotimage")) == 0) SetHotImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("pushedimage")) == 0) SetPushedImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("focusedimage")) == 0) SetFocusedImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("normalimage")) == 0) SetNormalImage(pstrValue); 
		else if (_tcsicmp(pstrName, _T("hotgifname")) == 0) SetHotGifName(pstrValue);
		else if (_tcsicmp(pstrName, _T("normalgifname")) == 0) SetNormalGifName(pstrValue);
		else if (_tcsicmp(pstrName, _T("cursor")) == 0) SetCursorHand(pstrValue);
		else
		{
			CContainerUI::SetAttribute(pstrName, pstrValue);
		}
		return;
	}

	void CContainerExUI::SetHotImage(LPCTSTR pStrImage)
	{
		m_sHotImage = pStrImage;
		Invalidate();
	}

	void CContainerExUI::SetPushedImage(LPCTSTR pStrImage)
	{
		m_sPushedImage = pStrImage;
		Invalidate();
	}

	void CContainerExUI::SetFocusedImage(LPCTSTR pStrImage)
	{
		m_sFocusedImage = pStrImage;
		Invalidate();
	}

	void CContainerExUI::SetNormalImage(LPCTSTR pStrImage)
	{
		m_sNormalImage = pStrImage;
		Invalidate();
	}

	void CContainerExUI::SetHotGifName(LPCTSTR pStrImage)
	{
		pGif = static_cast<CGifAnimUI*>(this->FindSubControl(pStrImage));
		b_hotgif = true;
		Invalidate();
	}

	void CContainerExUI::SetNormalGifName(LPCTSTR pStrImage)
	{
		pGif = static_cast<CGifAnimUI*>(this->FindSubControl(pStrImage));
		b_normalgif = true;
		Invalidate();
	}

	void CContainerExUI::SetCursorHand(LPCTSTR pStrImage)
	{
		m_sCursorHand = pStrImage;
		Invalidate();
	}

	void CContainerExUI::DoEvent(TEventUI& event)
	{
		if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND) {
			if (m_pParent != NULL) m_pParent->DoEvent(event);
			else CControlUI::DoEvent(event);
			return;
		}
		
		if (event.Type == UIEVENT_SETFOCUS)
		{
			Invalidate();
		}
		if (event.Type == UIEVENT_KILLFOCUS)
		{
			Invalidate();
		}
		if (event.Type == UIEVENT_KEYDOWN)
		{
			if (IsKeyboardEnabled()) {
				if (event.chKey == VK_SPACE || event.chKey == VK_RETURN) {
					Activate();
					return;
				}
			}
		}
		if (event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK)
		{
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
				Invalidate();
			}
			return;
		}
		if (event.Type == UIEVENT_MOUSEMOVE)
		{
			if (m_sCursorHand.Compare(_T("hand")) == 0)
			{
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
			}
			if ((m_uButtonState & UISTATE_CAPTURED) != 0) {
				if (::PtInRect(&m_rcItem, event.ptMouse)) m_uButtonState |= UISTATE_PUSHED;
				else m_uButtonState &= ~UISTATE_PUSHED;
				Invalidate();
			}
			return;
		}
		if (event.Type == UIEVENT_BUTTONUP)
		{
			if ((m_uButtonState & UISTATE_CAPTURED) != 0) {
				if (::PtInRect(&m_rcItem, event.ptMouse)) Activate();
				m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
				Invalidate();
			}
			return;
		}
		if (event.Type == UIEVENT_CONTEXTMENU)
		{
			if (IsContextMenuUsed()) {
				m_pManager->SendNotify(this, DUI_MSGTYPE_MENU, event.wParam, event.lParam);
			}
			return;
		}
		if (event.Type == UIEVENT_MOUSEENTER)
		{
			if (IsEnabled()) {
				m_uButtonState |= UISTATE_HOT;
				Invalidate();
			}
		}
		if (event.Type == UIEVENT_MOUSELEAVE)
		{
			if (IsEnabled()) {
				m_uButtonState &= ~UISTATE_HOT;
				Invalidate();
			}
		}
		CContainerUI::DoEvent(event);
	}

	void CContainerExUI::PaintStatusImage(HDC hDC)
	{
		if (IsFocused()) 
			m_uButtonState |= UISTATE_FOCUSED;
		else 
			m_uButtonState &= ~UISTATE_FOCUSED;
		if (!IsEnabled()) 
			m_uButtonState |= UISTATE_DISABLED;
		else 
			m_uButtonState &= ~UISTATE_DISABLED;

		if ((m_uButtonState & UISTATE_PUSHED) != 0) {
			if (!m_sPushedImage.IsEmpty()) {
				if (!DrawImage(hDC, (LPCTSTR)m_sPushedImage)){
					m_sPushedImage.Empty();
				}
				else goto Label_ForeImage;
			}
		}
		else if ((m_uButtonState & UISTATE_HOT) != 0) {
			if (pGif != NULL && b_hotgif)
			{
				pGif->SetVisible(true);
			}
			if (pGif != NULL && b_normalgif)
			{
				pGif->SetVisible(false);
			}
			if (!m_sHotImage.IsEmpty()) {
				if (!DrawImage(hDC, (LPCTSTR)m_sHotImage)){
					m_sHotImage.Empty();
				}
				else goto Label_ForeImage;
			}
		}
		else if ((m_uButtonState & UISTATE_HOT) == 0)
		{
			if (pGif != NULL && b_hotgif)
			{
				pGif->SetVisible(false);
			}
			if (pGif != NULL && b_normalgif)
			{
				pGif->SetVisible(true);
			}
		}
		else if ((m_uButtonState & UISTATE_FOCUSED) != 0) {
			if (!m_sFocusedImage.IsEmpty()) {
				if (!DrawImage(hDC, (LPCTSTR)m_sFocusedImage)) m_sFocusedImage.Empty();
				else goto Label_ForeImage;
			}
		}

		if (!m_sNormalImage.IsEmpty()) {
			if (!DrawImage(hDC, (LPCTSTR)m_sNormalImage)) m_sNormalImage.Empty();
			else goto Label_ForeImage;
		}

		if (!m_sForeImage.IsEmpty())
			goto Label_ForeImage;

		return;

	Label_ForeImage:
		if (!m_sForeImage.IsEmpty()) {
			if (!DrawImage(hDC, (LPCTSTR)m_sForeImage)) m_sForeImage.Empty();
		}
	}

	bool CContainerExUI::Activate()
	{
		if (!CControlUI::Activate()) return false;
		if (m_pManager != NULL)
		{
			m_pManager->SendNotify(this, DUI_MSGTYPE_CLICK);
		}
		return true;
	}
}