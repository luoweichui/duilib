#ifndef _UICheckBoxEx_
#define _UICheckBoxEx_

#pragma once

namespace DuiLib
{
	class UILIB_API CCheckBoxExUI :public CButtonUI
	{
		DECLARE_DUICONTROL(CCheckBoxExUI)
	public:
		CCheckBoxExUI();
		~CCheckBoxExUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);

		bool Activate();
		void SetEnabled(bool bEnable = true);

		LPCTSTR GetSelectedImage();
		void SetSelectedImage(LPCTSTR pStrImage);

		LPCTSTR GetSelectedHotImage();
		void SetSelectedHotImage(LPCTSTR pStrImage);

		LPCTSTR GetSelectedPushedImage();
		void SetSelectedPushedImage(LPCTSTR pStrImage);

		void SetSelectedTextColor(DWORD dwTextColor);
		DWORD GetSelectedTextColor();

		void SetSelectedBkColor(DWORD dwBkColor);
		DWORD GetSelectBkColor();

		LPCTSTR GetForeImage();
		void SetForeImage(LPCTSTR pStrImage);

		LPCTSTR GetSelectedForedImage();
		void SetSelectedForedImage(LPCTSTR pStrImage);

		LPCTSTR GetGroup() const;
		void SetGroup(LPCTSTR pStrGroupName = NULL);
		virtual bool IsSelected() const;
		virtual void Selected(bool bSelected);
		void SetFather(LPCTSTR pstrValue);
		bool GetFather();

		SIZE EstimateSize(SIZE szAvailable);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);
	protected:
		bool			m_bSelected;
		bool			m_bfather;
		CDuiString		m_sGroupName;

		DWORD			m_dwSelectedBkColor;
		DWORD			m_dwSelectedTextColor;

		CDuiString		m_sSelectedImage;
		CDuiString		m_sSelectedHotImage;
		CDuiString		m_sSelectedPushedImage;
		CDuiString		m_sForeImage;
		CDuiString		m_sSelectedForeImage;
	};

}

#endif // UICheckBoxEx