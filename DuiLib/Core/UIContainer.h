#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class IContainerUI
{
public:
    virtual CControlUI* GetItemAt(int iIndex) const = 0;
    virtual int GetItemIndex(CControlUI* pControl) const  = 0;
    virtual bool SetItemIndex(CControlUI* pControl, int iNewIndex) = 0;
    virtual bool SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex) = 0;
    virtual int GetCount() const = 0;
    virtual bool Add(CControlUI* pControl) = 0;
    virtual bool AddAt(CControlUI* pControl, int iIndex)  = 0;
    virtual bool Remove(CControlUI* pControl, bool bDoNotDestroy=false) = 0;
    virtual bool RemoveAt(int iIndex, bool bDoNotDestroy=false)  = 0;
    virtual void RemoveAll() = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
class CScrollBarUI;

class DUILIB_API CContainerUI : public CControlUI, public IContainerUI
{
public:
    CContainerUI();
    virtual ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);   //  重写 基类 CControlUI 的这个可函数  可以获取本控件的实例

    CControlUI* GetItemAt(int iIndex) const;
    int GetItemIndex(CControlUI* pControl) const;
    bool SetItemIndex(CControlUI* pControl, int iNewIndex);
    bool SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
    int GetCount() const;
    bool Add(CControlUI* pControl);                             // 添加并注册一个控件
    bool AddAt(CControlUI* pControl, int iIndex);
    bool Remove(CControlUI* pControl, bool bDoNotDestroy=false);
    bool RemoveAt(int iIndex, bool bDoNotDestroy=false);
    void RemoveAll();

    void DoEvent(TEventUI& event);
    void SetVisible(bool bVisible = true);
    void SetInternVisible(bool bVisible = true);
    void SetMouseEnabled(bool bEnable = true);

    virtual RECT GetInset() const;
    virtual void SetInset(RECT rcInset); // 设置内边距，相当于设置客户区
    virtual int GetChildPadding() const;
    virtual void SetChildPadding(int iPadding);
	virtual UINT GetChildAlign() const;
	virtual void SetChildAlign(UINT iAlign);
	virtual UINT GetChildVAlign() const;
	virtual void SetChildVAlign(UINT iVAlign);
    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy(bool bAuto);
    virtual bool IsDelayedDestroy() const;
    virtual void SetDelayedDestroy(bool bDelayed);
    virtual bool IsMouseChildEnabled() const;
    virtual void SetMouseChildEnabled(bool bEnable = true);

    virtual int FindSelectable(int iIndex, bool bForward = true) const;

	RECT GetClientPos() const;
	void SetPos(RECT rc, bool bNeedInvalidate = true);
	void Move(SIZE szOffset, bool bNeedInvalidate = true);
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
    CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	bool SetSubControlText(LPCTSTR pstrSubControlName,LPCTSTR pstrText);
	bool SetSubControlFixedHeight(LPCTSTR pstrSubControlName,int cy);
	bool SetSubControlFixedWdith(LPCTSTR pstrSubControlName,int cx);
	bool SetSubControlUserData(LPCTSTR pstrSubControlName,LPCTSTR pstrText);

	CDuiString GetSubControlText(LPCTSTR pstrSubControlName);
	int GetSubControlFixedHeight(LPCTSTR pstrSubControlName);
	int GetSubControlFixedWdith(LPCTSTR pstrSubControlName);
	const CDuiString GetSubControlUserData(LPCTSTR pstrSubControlName);
	CControlUI* FindSubControl(LPCTSTR pstrSubControlName);

    virtual SIZE GetScrollPos() const;
    virtual SIZE GetScrollRange() const;
    virtual void SetScrollPos(SIZE szPos);
    virtual void LineUp();
    virtual void LineDown();
    virtual void PageUp();
    virtual void PageDown();
    virtual void HomeUp();
    virtual void EndDown();
    virtual void LineLeft();
    virtual void LineRight();
    virtual void PageLeft();
    virtual void PageRight();
    virtual void HomeLeft();
    virtual void EndRight();
    virtual void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
    virtual CScrollBarUI* GetVerticalScrollBar() const;
    virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
    virtual void SetFloatPos(int iIndex);
    virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);

protected:
    CDuiPtrArray m_items;   //  本容器内包含的控件实例列表
    RECT m_rcInset;
    int m_iChildPadding;
	UINT m_iChildAlign;
	UINT m_iChildVAlign;
    bool m_bAutoDestroy;
    bool m_bDelayedDestroy;
    bool m_bMouseChildEnabled;
    bool m_bScrollProcess; // 防止SetPos循环调用

    CScrollBarUI* m_pVerticalScrollBar;
    CScrollBarUI* m_pHorizontalScrollBar;
};

} // namespace DuiLib

#endif // __UICONTAINER_H__
