#include "stdafx.h"
#include "UICheckBoxEx.h"

namespace DuiLib
{
	IMPLEMENT_DUICONTROL(CCheckBoxExUI)
	CCheckBoxExUI::CCheckBoxExUI() :m_bSelected(false), m_dwSelectedTextColor(0), m_dwSelectedBkColor(0), m_bfather(false)
	{
	}

	CCheckBoxExUI::~CCheckBoxExUI()
	{
		if (!m_sGroupName.IsEmpty() && m_pManager) m_pManager->RemoveOptionGroup(m_sGroupName, this);
	}

	LPCTSTR CCheckBoxExUI::GetClass() const
	{
		return _T("CCheckBoxExUI");
	}


	LPVOID CCheckBoxExUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcsicmp(pstrName, DUI_CTR_CHECKBOXEX) == 0) return static_cast<CCheckBoxExUI*>(this);
		return CButtonUI::GetInterface(pstrName);
	}

	void CCheckBoxExUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit)
	{
		CControlUI::SetManager(pManager, pParent, bInit);
		if (bInit && !m_sGroupName.IsEmpty()) {
			if (m_pManager) m_pManager->AddOptionGroup(m_sGroupName, this);
		}
	}

	LPCTSTR CCheckBoxExUI::GetGroup() const
	{
		return m_sGroupName;
	}

	void CCheckBoxExUI::SetGroup(LPCTSTR pStrGroupName)
	{
		if (pStrGroupName == NULL) {
			if (m_sGroupName.IsEmpty()) return;
			m_sGroupName.Empty();
		}
		else {
			if (m_sGroupName == pStrGroupName) return;
			if (!m_sGroupName.IsEmpty() && m_pManager) m_pManager->RemoveOptionGroup(m_sGroupName, this);
			m_sGroupName = pStrGroupName;
		}

		if (!m_sGroupName.IsEmpty()) {
			if (m_pManager) m_pManager->AddOptionGroup(m_sGroupName, this);
		}
		else {
			if (m_pManager) m_pManager->RemoveOptionGroup(m_sGroupName, this);
		}
	}

	bool CCheckBoxExUI::IsSelected() const
	{
		return m_bSelected;
	}

	void CCheckBoxExUI::Selected(bool bSelected)
	{
		m_bSelected = bSelected;
		if (m_bSelected) m_uButtonState |= UISTATE_SELECTED;
		else m_uButtonState &= ~UISTATE_SELECTED;

		if (m_pManager != NULL) {
			if (!m_sGroupName.IsEmpty()) {
					CStdPtrArray* aOptionGroup = m_pManager->GetOptionGroup(m_sGroupName);
					if (m_bfather)
					{
						for (int i = 0; i < aOptionGroup->GetSize(); i++)
						{
							CCheckBoxExUI* pControl = static_cast<CCheckBoxExUI*>(aOptionGroup->GetAt(i));
							if (pControl != this)
							{
								pControl->Selected(bSelected);
							}
						}
					}
					m_pManager->SendNotify(this, DUI_MSGTYPE_SELECTCHANGED);
			}
			else {
				m_pManager->SendNotify(this, DUI_MSGTYPE_SELECTCHANGED);
			}
		}

		Invalidate();
	}

	bool CCheckBoxExUI::Activate()
	{
		if (!CButtonUI::Activate()) return false;
		Selected(!m_bSelected);
		return true;
	}

	void CCheckBoxExUI::SetEnabled(bool bEnable)
	{
		CControlUI::SetEnabled(bEnable);
		if (!IsEnabled()) {
			if (m_bSelected) m_uButtonState = UISTATE_SELECTED;
			else m_uButtonState = 0;
		}
	}

	LPCTSTR CCheckBoxExUI::GetSelectedImage()
	{
		return m_sSelectedImage;
	}

	void CCheckBoxExUI::SetSelectedImage(LPCTSTR pStrImage)
	{
		m_sSelectedImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CCheckBoxExUI::GetSelectedHotImage()
	{
		return m_sSelectedHotImage;
	}

	void CCheckBoxExUI::SetSelectedHotImage(LPCTSTR pStrImage)
	{
		m_sSelectedHotImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CCheckBoxExUI::GetSelectedPushedImage()
	{
		return m_sSelectedPushedImage;
	}

	void CCheckBoxExUI::SetSelectedPushedImage(LPCTSTR pStrImage)
	{
		m_sSelectedPushedImage = pStrImage;
		Invalidate();
	}

	void CCheckBoxExUI::SetSelectedTextColor(DWORD dwTextColor)
	{
		m_dwSelectedTextColor = dwTextColor;
	}

	DWORD CCheckBoxExUI::GetSelectedTextColor()
	{
		if (m_dwSelectedTextColor == 0) m_dwSelectedTextColor = m_pManager->GetDefaultFontColor();
		return m_dwSelectedTextColor;
	}

	void CCheckBoxExUI::SetSelectedBkColor(DWORD dwBkColor)
	{
		m_dwSelectedBkColor = dwBkColor;
	}

	DWORD CCheckBoxExUI::GetSelectBkColor()
	{
		return m_dwSelectedBkColor;
	}

	LPCTSTR CCheckBoxExUI::GetForeImage()
	{
		return m_sForeImage;
	}

	void CCheckBoxExUI::SetForeImage(LPCTSTR pStrImage)
	{
		m_sForeImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CCheckBoxExUI::GetSelectedForedImage()
	{
		return m_sSelectedForeImage;
	}

	void CCheckBoxExUI::SetSelectedForedImage(LPCTSTR pStrImage)
	{
		m_sSelectedForeImage = pStrImage;
		Invalidate();
	}

	SIZE CCheckBoxExUI::EstimateSize(SIZE szAvailable)
	{
		if (m_cxyFixed.cy == 0) return CDuiSize(m_cxyFixed.cx, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 8);
		return CControlUI::EstimateSize(szAvailable);
	}

	void CCheckBoxExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcsicmp(pstrName, _T("group")) == 0) SetGroup(pstrValue);
		else if (_tcsicmp(pstrName, _T("selected")) == 0) Selected(_tcsicmp(pstrValue, _T("true")) == 0);
		else if (_tcsicmp(pstrName, _T("selectedimage")) == 0) SetSelectedImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("selectedhotimage")) == 0) SetSelectedHotImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("selectedpushedimage")) == 0) SetSelectedPushedImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("foreimage")) == 0) SetForeImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("selectedforeimage")) == 0) SetSelectedForedImage(pstrValue);
		else if (_tcsicmp(pstrName, _T("selectedbkcolor")) == 0) {
			if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelectedBkColor(clrColor);
		}
		else if (_tcsicmp(pstrName, _T("selectedtextcolor")) == 0) {
			if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetSelectedTextColor(clrColor);
		}
		else if (_tcsicmp(pstrName, _T("father")) == 0) SetFather(pstrValue);
		else CButtonUI::SetAttribute(pstrName, pstrValue);
	}

	void CCheckBoxExUI::SetFather(LPCTSTR pstrValue)
	{
		if (wcscmp(pstrValue, _T("true")) == 0)
			m_bfather = true;
		else
			m_bfather = false;
	}

	bool CCheckBoxExUI::GetFather()
	{
		return m_bfather;
	}

	void CCheckBoxExUI::PaintStatusImage(HDC hDC)
	{

		if ((m_uButtonState & UISTATE_PUSHED) != 0 && IsSelected() && !m_sSelectedPushedImage.IsEmpty()) {
			if (!DrawImage(hDC, (LPCTSTR)m_sSelectedPushedImage))
				m_sSelectedPushedImage.Empty();
			else goto Label_ForeImage;
		}
		else if ((m_uButtonState & UISTATE_HOT) != 0 && IsSelected() && !m_sSelectedHotImage.IsEmpty()) {
			if (!DrawImage(hDC, (LPCTSTR)m_sSelectedHotImage))
				m_sSelectedHotImage.Empty();
			else goto Label_ForeImage;
		}
		else if ((m_uButtonState & UISTATE_SELECTED) != 0) {
			if (!m_sSelectedImage.IsEmpty()) {
				if (!DrawImage(hDC, (LPCTSTR)m_sSelectedImage)) m_sSelectedImage.Empty();
				else goto Label_ForeImage;
			}
			else if (m_dwSelectedBkColor != 0) {
				CRenderEngine::DrawColor(hDC, m_rcPaint, GetAdjustColor(m_dwSelectedBkColor));
				return;
			}
		}

		CButtonUI::PaintStatusImage(hDC);

	Label_ForeImage:
		if (IsSelected() && !m_sSelectedForeImage.IsEmpty())
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sSelectedForeImage)) m_sSelectedForeImage.Empty();
		}
		else if (!m_sForeImage.IsEmpty())
		{
			if (!DrawImage(hDC, (LPCTSTR)m_sForeImage)) m_sForeImage.Empty();
		}

	}

	void CCheckBoxExUI::PaintText(HDC hDC)
	{
		if ((m_uButtonState & UISTATE_SELECTED) != 0)
		{
			DWORD oldTextColor = m_dwTextColor;
			if (m_dwSelectedTextColor != 0) m_dwTextColor = m_dwSelectedTextColor;

			if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
			if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

			CDuiString sText = GetText();
			if (sText.IsEmpty()) return;
			int nLinks = 0;
			RECT rc = m_rcItem;
			rc.left += m_rcTextPadding.left;
			rc.right -= m_rcTextPadding.right;
			rc.top += m_rcTextPadding.top;
			rc.bottom -= m_rcTextPadding.bottom;

			if (m_bShowHtml)
				CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, sText, IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor, \
				NULL, NULL, nLinks, m_uTextStyle);
			else
				CRenderEngine::DrawText(hDC, m_pManager, rc, sText, IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor, \
				m_iFont, m_uTextStyle);

			m_dwTextColor = oldTextColor;
		}
		else
			CButtonUI::PaintText(hDC);
	}
}