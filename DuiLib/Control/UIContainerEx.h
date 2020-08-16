#ifndef _UIContainerEx_
#define _UIContainerEx_

#pragma once
namespace DuiLib
{
	class UILIB_API CContainerExUI :public CContainerUI
	{
		DECLARE_DUICONTROL(CContainerExUI)
	public:
		CContainerExUI();
		~CContainerExUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	private:
		CDuiString m_sHotImage;
		CDuiString m_sPushedImage;
		CDuiString m_sFocusedImage;
		CDuiString m_sNormalImage;
		CDuiString m_sCursorHand;
		CGifAnimUI *pGif;
		bool b_hotgif;
		bool b_normalgif;
	public:
		void SetHotImage(LPCTSTR pStrImage);
		void SetPushedImage(LPCTSTR pStrImage);
		void SetFocusedImage(LPCTSTR pStrImage);
		void SetNormalImage(LPCTSTR pStrImage);
		void SetHotGifName(LPCTSTR pStrImage);
		void SetCursorHand(LPCTSTR pStrImage);
		void SetNormalGifName(LPCTSTR pStrImage);
	public:
		void PaintStatusImage(HDC hDC);
		void DoEvent(TEventUI& event);
		bool Activate();
	protected:
		UINT m_uButtonState;
	};

}

#endif // _UIContainerEx_