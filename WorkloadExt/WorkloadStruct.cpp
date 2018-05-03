// WorkloadStruct.cpp: implementation of the CWorkloadStruct class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorkloadStruct.h"

#include "..\shared\DateHelper.h"
#include "..\shared\graphicsMisc.h"
#include "..\shared\misc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

int WorkloadDEPENDENCY::STUB = 0;

WorkloadDEPENDENCY::WorkloadDEPENDENCY() 
	: 
	ptFrom(0), 
	ptTo(0), 
	dwFromID(0), 
	dwToID(0)
{
}

void WorkloadDEPENDENCY::SetFrom(const CPoint& pt, DWORD dwTaskID)
{
	dwFromID = dwTaskID;
	ptFrom = pt;
}

void WorkloadDEPENDENCY::SetTo(const CPoint& pt, DWORD dwTaskID)
{
	dwToID = dwTaskID;
	ptTo = pt;
}

DWORD WorkloadDEPENDENCY::GetFromID() const
{
	ASSERT(dwFromID);
	return dwFromID;
}

DWORD WorkloadDEPENDENCY::GetToID() const
{
	ASSERT(dwToID);
	return dwToID;
}

BOOL WorkloadDEPENDENCY::Matches(DWORD dwFrom, DWORD dwTo) const
{
	ASSERT(dwFromID && dwToID);
	return ((dwFromID == dwFrom) && (dwToID == dwTo));
}

BOOL WorkloadDEPENDENCY::Draw(CDC* pDC, const CRect& rClient, BOOL bDragging)
{
	if (!HitTest(rClient))
		return FALSE;
	
	// draw 3x3 box at ptTo
	if (!bDragging)
	{
		CRect rBox(ptTo.x - 1, ptTo.y - 1, ptTo.x + 2, ptTo.y + 2);
		pDC->FillSolidRect(rBox, 0);
	}
		
	CPoint pts[3];
	CalcDependencyPath(pts);
	
	int nOldROP2 = pDC->SetROP2(bDragging ? R2_NOT : R2_BLACK);
	pDC->Polyline(pts, 3);

	DrawDependencyArrow(pDC, pts[0]);
	pDC->SetROP2(nOldROP2);
	
	return TRUE;
}

#ifdef _DEBUG
void WorkloadDEPENDENCY::Trace() const
{
	TRACE(_T("WorkloadDEPENDENCY(from %d (pos = %d) to %d (pos = %d))\n"), dwFromID, ptFrom.x, dwToID, ptTo.x);
}
#endif

void WorkloadDEPENDENCY::DrawDependencyArrow(CDC* pDC, const CPoint& pt) const
{
	CPoint pts[3], ptArrow(pt);

	CalcDependencyArrow(ptArrow, pts);
	pDC->Polyline(pts, 3);
	
	// offset and draw again
	if (IsFromAboveTo())
		ptArrow.y++;
	else
		ptArrow.y--;
	
	CalcDependencyArrow(ptArrow, pts);
	pDC->Polyline(pts, 3);
}

BOOL WorkloadDEPENDENCY::HitTest(const CRect& rect) const
{
	CRect rThis;
	return (CalcBoundingRect(rThis) && CRect().IntersectRect(rect, rThis));
}

BOOL WorkloadDEPENDENCY::HitTest(const CPoint& point, int nTol) const
{
	CRect rThis;
	
	if (!CalcBoundingRect(rThis))
		return FALSE;

	// add tolerance
	rThis.InflateRect(nTol, nTol);

	if (!rThis.PtInRect(point))
		return FALSE;

	// check each line segment
	CPoint pts[3];
	CalcDependencyPath(pts);

	nTol = max(nTol, 1);
	
	for (int i = 0; i < 2; i++)
	{
		CRect rSeg;

		rSeg.left	= min(pts[i].x, pts[i+1].x) - nTol;
		rSeg.right	= max(pts[i].x, pts[i+1].x) + nTol;
		rSeg.top	= min(pts[i].y, pts[i+1].y) - nTol;
		rSeg.bottom = max(pts[i].y, pts[i+1].y) + nTol;

		if (rSeg.PtInRect(point))
			return TRUE;
	}

	// no hit
	return FALSE;
}

BOOL WorkloadDEPENDENCY::IsFromAboveTo() const
{
	return (ptFrom.y < ptTo.y);
}

void WorkloadDEPENDENCY::CalcDependencyPath(CPoint pts[3]) const
{
	CPoint ptTemp(ptFrom);

	// first point
	if (IsFromAboveTo())
		ptTemp.y -= (2 - STUB);
	else
		ptTemp.y += (1 - STUB);

	pts[0] = ptTemp;

	// mid point
	ptTemp.y = ptTo.y;
	pts[1] = ptTemp;

	// last point
	pts[2] = ptTo;
}

void WorkloadDEPENDENCY::CalcDependencyArrow(const CPoint& pt, CPoint pts[3]) const
{
	pts[0] = pts[1] = pts[2] = pt;

	const int ARROW = (STUB / 2);
	
	if (IsFromAboveTo())
	{
		pts[0].Offset(-ARROW, ARROW);
		pts[2].Offset(ARROW+1, ARROW+1);
	}
	else
	{
		pts[0].Offset(-ARROW, -ARROW);
		pts[2].Offset(ARROW+1, -(ARROW+1));
	}
}

BOOL WorkloadDEPENDENCY::CalcBoundingRect(CRect& rect) const
{
	if (ptFrom == ptTo)
		return FALSE;
	
	// allow for stub overhang
	rect.left	= min(ptFrom.x, ptTo.x) - STUB;
	rect.right	= max(ptFrom.x, ptTo.x) + STUB;
	rect.top	= min(ptFrom.y, ptTo.y);
	rect.bottom = max(ptFrom.y, ptTo.y);
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

WorkloadITEM::WorkloadITEM() 
	: 
	color(CLR_NONE), 
	bParent(FALSE), 
	dwTaskID(0), 
	dwRefID(0), 
	dwOrgRefID(0), 
	bGoodAsDone(FALSE),
	nPosition(-1),
	bLocked(FALSE),
	bSomeSubtaskDone(FALSE)
{
}

WorkloadITEM::WorkloadITEM(const WorkloadITEM& gi)
{
	*this = gi;
}

WorkloadITEM& WorkloadITEM::operator=(const WorkloadITEM& gi)
{
	sTitle = gi.sTitle;
	dtStart = gi.dtStart;
	dtMinStart = gi.dtMinStart;
	dtDue = gi.dtDue;
	dtMaxDue = gi.dtMaxDue;
	dtDone = gi.dtDone;
	color = gi.color;
	sAllocTo = gi.sAllocTo;
	bParent = gi.bParent;
	dwTaskID = gi.dwTaskID;
	dwRefID = gi.dwRefID;
	nPercent = gi.nPercent;
	bGoodAsDone = gi.bGoodAsDone;
	nPosition = gi.nPosition;
	bLocked = gi.bLocked;
	bHasIcon = gi.bHasIcon;
	bSomeSubtaskDone = gi.bSomeSubtaskDone;
	
	aTags.Copy(gi.aTags);
	aDependIDs.Copy(gi.aDependIDs);
	
	return (*this);
}

BOOL WorkloadITEM::operator==(const WorkloadITEM& gi)
{
	return ((sTitle == gi.sTitle) &&
			(dtStart == gi.dtStart) &&
			(dtMinStart == gi.dtMinStart) &&
			(dtDue == gi.dtDue) &&
			(dtMaxDue == gi.dtMaxDue) &&
			(dtDone == gi.dtDone) &&
			(color == gi.color) &&
			(sAllocTo == gi.sAllocTo) &&
			(bParent == gi.bParent) &&
			(dwTaskID == gi.dwTaskID) &&
			(dwRefID == gi.dwRefID) &&
			(nPercent == gi.nPercent) &&	
			(nPosition == gi.nPosition) &&
			(bGoodAsDone == gi.bGoodAsDone) &&
			(bLocked == gi.bLocked) &&
			(bHasIcon == gi.bHasIcon) &&
			(bSomeSubtaskDone == gi.bSomeSubtaskDone) &&
			Misc::MatchAll(aTags, gi.aTags) &&
			Misc::MatchAll(aDependIDs, gi.aDependIDs));
}

WorkloadITEM::~WorkloadITEM()
{
	
}

void WorkloadITEM::MinMaxDates(const WorkloadITEM& giOther)
{
	if (giOther.bParent)
	{
		CDateHelper::Max(dtMaxDue, giOther.dtMaxDue);
		CDateHelper::Min(dtMinStart, giOther.dtMinStart);
	}
	else // leaf task
	{
		CDateHelper::Max(dtMaxDue, giOther.dtDue);
		CDateHelper::Max(dtMaxDue, giOther.dtDone);
		CDateHelper::Min(dtMinStart, giOther.dtStart);
	}
}

BOOL WorkloadITEM::IsDone(BOOL bIncGoodAs) const
{
	if (CDateHelper::IsDateSet(dtDone))
		return TRUE;

	// else
	return (bIncGoodAs && bGoodAsDone);
}

BOOL CWorkloadItemMap::ItemIsLocked(DWORD dwTaskID) const
{
	const WorkloadITEM* pGI = GetItem(dwTaskID);
	
	return (pGI && pGI->bLocked);
}

BOOL CWorkloadItemMap::ItemHasDependecies(DWORD dwTaskID) const
{
	const WorkloadITEM* pGI = GetItem(dwTaskID);
	
	return (pGI && pGI->aDependIDs.GetSize());
}

BOOL WorkloadITEM::HasStart() const
{
	return CDateHelper::IsDateSet(dtStart);
}

BOOL WorkloadITEM::HasDue() const
{
	return CDateHelper::IsDateSet(dtDue);
}

COLORREF WorkloadITEM::GetTextColor(BOOL bSelected, BOOL bColorIsBkgnd) const
{
	if (HasColor())
	{
		if (bColorIsBkgnd && !bSelected && !IsDone(TRUE))
			return GraphicsMisc::GetBestTextColor(color);
		else
			return color;
	}
	
	// else
	return GetSysColor(COLOR_WINDOWTEXT);
}

COLORREF WorkloadITEM::GetTextBkColor(BOOL bSelected, BOOL bColorIsBkgnd) const
{
	if (!bSelected && HasColor())
	{
		if (bColorIsBkgnd && !IsDone(TRUE))
			return color;
	}
	
	// else
	return CLR_NONE;
}

COLORREF WorkloadITEM::GetFillColor() const
{
	if (IsDone(TRUE))
	{
		if (!Misc::IsHighContrastActive())
			return GraphicsMisc::Lighter(color, 0.8);
	}
	else if (HasColor())
	{
		return color;
	}
	
	// else
	return CLR_NONE;
}

COLORREF WorkloadITEM::GetBorderColor() const
{
	if (IsDone(TRUE))
	{
		if (!Misc::IsHighContrastActive())
			return color;
	}
	else if (HasColor())
	{
		return GraphicsMisc::Darker(color, 0.4);
	}
	
	// else
	return CLR_NONE;
}

BOOL WorkloadITEM::HasColor() const
{
	return ((color != CLR_NONE) && (color != GetSysColor(COLOR_WINDOWTEXT)));
}

//////////////////////////////////////////////////////////////////////

CWorkloadItemMap::~CWorkloadItemMap()
{
	RemoveAll();
}

void CWorkloadItemMap::RemoveAll()
{
	DWORD dwTaskID = 0;
	WorkloadITEM* pGI = NULL;
	
	POSITION pos = GetStartPosition();
	
	while (pos)
	{
		GetNextAssoc(pos, dwTaskID, pGI);
		ASSERT(pGI);
		
		delete pGI;
	}
	
	CMap<DWORD, DWORD, WorkloadITEM*, WorkloadITEM*&>::RemoveAll();
}

BOOL CWorkloadItemMap::RemoveKey(DWORD dwKey)
{
	WorkloadITEM* pGI = NULL;
	
	if (Lookup(dwKey, pGI))
	{
		delete pGI;
		return CMap<DWORD, DWORD, WorkloadITEM*, WorkloadITEM*&>::RemoveKey(dwKey);
	}
	
	// else
	return FALSE;
}

BOOL CWorkloadItemMap::HasItem(DWORD dwKey) const
{
	if (dwKey == 0)
		return FALSE;

	return (GetItem(dwKey) != NULL);
}

WorkloadITEM* CWorkloadItemMap::GetItem(DWORD dwKey) const
{
	if (dwKey == 0)
		return NULL;

	WorkloadITEM* pGI = NULL;
	
	if (Lookup(dwKey, pGI))
		ASSERT(pGI);
	
	return pGI;
}

BOOL CWorkloadItemMap::RestoreItem(const WorkloadITEM& giPrev)
{
	WorkloadITEM* pGI = NULL;

	if (Lookup(giPrev.dwTaskID, pGI) && pGI)
	{
		*pGI = giPrev;
		return TRUE;
	}

	ASSERT(0);
	return FALSE;
}

BOOL CWorkloadItemMap::IsItemDependentOn(const WorkloadITEM* pGI, DWORD dwOtherID) const
{
	if (!pGI)
	{
		ASSERT(0);
		return FALSE;
	}

	int nDepend = pGI->aDependIDs.GetSize();

	while (nDepend--)
	{
		DWORD dwDependID = pGI->aDependIDs[nDepend];
		ASSERT(dwDependID);

		if (dwDependID == dwOtherID)
			return TRUE;

		// else check dependents of dwDependID
		if (IsItemDependentOn(GetItem(dwDependID), dwOtherID)) // RECURSIVE
			return TRUE;
	}
	
	// all else
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

WorkloadDATERANGE::WorkloadDATERANGE()
{
	Clear();
}

void WorkloadDATERANGE::Clear()
{
	CDateHelper::ClearDate(dtStart);
	CDateHelper::ClearDate(dtEnd);
}

void WorkloadDATERANGE::MinMax(const WorkloadITEM& gi)
{
	MinMax(gi.dtStart);
	MinMax(gi.dtDue);
	MinMax(gi.dtDone);
}

void WorkloadDATERANGE::MinMax(const COleDateTime& date)
{
	CDateHelper::Min(dtStart, date);
	CDateHelper::Max(dtEnd, date);
}

COleDateTime WorkloadDATERANGE::GetStart(GTLC_MONTH_DISPLAY nDisplay, BOOL bZeroBasedDecades) const
{
	COleDateTime dtTemp = COleDateTime::GetCurrentTime();

	if (CDateHelper::IsDateSet(dtStart))
		dtTemp = dtStart;

	switch (nDisplay)
	{
	case GTLC_DISPLAY_QUARTERCENTURIES:
		return CDateHelper::GetStartOfQuarterCentury(dtTemp, bZeroBasedDecades);

	case GTLC_DISPLAY_DECADES:
		return CDateHelper::GetStartOfDecade(dtTemp, bZeroBasedDecades);

	case GTLC_DISPLAY_YEARS:
		return CDateHelper::GetStartOfYear(dtTemp);

	case GTLC_DISPLAY_QUARTERS_SHORT:
	case GTLC_DISPLAY_QUARTERS_MID:
	case GTLC_DISPLAY_QUARTERS_LONG:
		return CDateHelper::GetStartOfQuarter(dtTemp);

	case GTLC_DISPLAY_MONTHS_SHORT:
	case GTLC_DISPLAY_MONTHS_MID:
	case GTLC_DISPLAY_MONTHS_LONG:
	case GTLC_DISPLAY_WEEKS_SHORT:
	case GTLC_DISPLAY_WEEKS_MID:
	case GTLC_DISPLAY_WEEKS_LONG:
	case GTLC_DISPLAY_DAYS_SHORT:
	case GTLC_DISPLAY_DAYS_MID:
	case GTLC_DISPLAY_DAYS_LONG:
	case GTLC_DISPLAY_HOURS:
		return CDateHelper::GetStartOfMonth(dtTemp);
	}

	ASSERT(0);
	return dtTemp;
}

COleDateTime WorkloadDATERANGE::GetEnd(GTLC_MONTH_DISPLAY nDisplay, BOOL bZeroBasedDecades) const
{
	COleDateTime dtTemp = COleDateTime::GetCurrentTime();

	if (CDateHelper::IsDateSet(dtEnd))
		dtTemp = dtEnd;

	switch (nDisplay)
	{
	case GTLC_DISPLAY_QUARTERCENTURIES:
		return CDateHelper::GetEndOfQuarterCentury(dtTemp, bZeroBasedDecades);

	case GTLC_DISPLAY_DECADES:
		return CDateHelper::GetEndOfDecade(dtTemp, bZeroBasedDecades);

	case GTLC_DISPLAY_YEARS:
		return CDateHelper::GetEndOfYear(dtTemp);

	case GTLC_DISPLAY_QUARTERS_SHORT:
	case GTLC_DISPLAY_QUARTERS_MID:
	case GTLC_DISPLAY_QUARTERS_LONG:
		return CDateHelper::GetEndOfQuarter(dtTemp);

	case GTLC_DISPLAY_MONTHS_SHORT:
	case GTLC_DISPLAY_MONTHS_MID:
	case GTLC_DISPLAY_MONTHS_LONG:
	case GTLC_DISPLAY_WEEKS_SHORT:
	case GTLC_DISPLAY_WEEKS_MID:
	case GTLC_DISPLAY_WEEKS_LONG:
	case GTLC_DISPLAY_DAYS_SHORT:
	case GTLC_DISPLAY_DAYS_MID:
	case GTLC_DISPLAY_DAYS_LONG:
	case GTLC_DISPLAY_HOURS:
		return CDateHelper::GetEndOfMonth(dtTemp);
	}

	ASSERT(0);
	return dtTemp;
}

int WorkloadDATERANGE::Compare(const COleDateTime& date) const
{
	ASSERT(CDateHelper::IsDateSet(date) && IsValid());

	if (date < dtStart)
		return -1;

	if (date > dtEnd)
		return 1;

	// else
	return 0; // contains
}

BOOL WorkloadDATERANGE::IsValid() const
{
	return (CDateHelper::IsDateSet(dtStart) && CDateHelper::IsDateSet(dtEnd) &&
			(dtStart <= dtEnd));
}

BOOL WorkloadDATERANGE::IsEmpty() const
{
	ASSERT(IsValid());

	return (dtEnd == dtStart);
}

BOOL WorkloadDATERANGE::Contains(const WorkloadITEM& gi)
{
	return ((Compare(gi.dtStart) == 0) && (Compare(gi.dtDue) == 0));
}

//////////////////////////////////////////////////////////////////////

WorkloadSORTCOLUMN::WorkloadSORTCOLUMN() : nBy(GTLCC_NONE), bAscending(-1)
{

}

BOOL WorkloadSORTCOLUMN::Matches(GTLC_COLUMN nSortBy, BOOL bSortAscending) const
{
	return ((nBy == nSortBy) && (bAscending == bSortAscending));
}

BOOL WorkloadSORTCOLUMN::operator==(const WorkloadSORTCOLUMN& col) const
{
	return Matches(col.nBy, col.bAscending);
}

BOOL WorkloadSORTCOLUMN::Sort(GTLC_COLUMN nSortBy, BOOL bAllowToggle, BOOL bSortAscending)
{
	if (!bAllowToggle && Matches(nSortBy, bSortAscending))
		return FALSE;

	GTLC_COLUMN nOldSort = nBy;
	nBy = nSortBy;

	if (nSortBy != GTLCC_NONE)
	{
		// if it's the first time or we are changing columns 
		// we always reset the direction
		if ((bAscending == -1) || (nSortBy != nOldSort))
		{
			if (bSortAscending != -1)
			{
				bAscending = bSortAscending;
			}
			else
			{
				bAscending = 1;
			}
		}
		else if (bAllowToggle)
		{
			ASSERT(bAscending != -1);
			bAscending = !bAscending;
		}
	}
	else
	{
		// Always ascending for 'unsorted' to match app
		bAscending = 1;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

WorkloadSORTCOLUMNS::WorkloadSORTCOLUMNS()
{

}

BOOL WorkloadSORTCOLUMNS::Sort(const WorkloadSORTCOLUMNS& sort)
{
	if (*this == sort)
		return FALSE;

	for (int nCol = 0; nCol < 3; nCol++)
		cols[nCol] = sort.cols[nCol];

	return TRUE;
}

BOOL WorkloadSORTCOLUMNS::operator==(const WorkloadSORTCOLUMNS& sort) const
{
	for (int nCol = 0; nCol < 3; nCol++)
	{
		if (!(cols[nCol] == sort.cols[nCol]))
			return FALSE;
	}

	// else
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

WorkloadSORT::WorkloadSORT() : bMultiSort(FALSE)
{

}

BOOL WorkloadSORT::IsSorting() const
{
	if (!bMultiSort)
		return (single.nBy != GTLCC_NONE);

	// else
	return (multi.cols[0].nBy != GTLCC_NONE);
}

BOOL WorkloadSORT::IsSortingBy(GTLC_COLUMN nColID) const
{
	if (!bMultiSort)
		return IsSingleSortingBy(nColID);

	return IsMultiSortingBy(nColID);
}

BOOL WorkloadSORT::IsSingleSortingBy(GTLC_COLUMN nColID) const
{
	return (!bMultiSort && (single.nBy == nColID));
}

BOOL WorkloadSORT::IsMultiSortingBy(GTLC_COLUMN nColID) const
{
	if (bMultiSort)
	{
		for (int nCol = 0; nCol < 3; nCol++)
		{
			if (multi.cols[nCol].nBy == nColID)
				return TRUE;
		}
	}

	return FALSE;
}

BOOL WorkloadSORT::Sort(GTLC_COLUMN nBy, BOOL bAllowToggle, BOOL bAscending)
{
	if (bMultiSort)
	{
		bMultiSort = FALSE;
		return single.Sort(nBy, FALSE, bAscending);
	}

	return single.Sort(nBy, bAllowToggle, bAscending);
}

BOOL WorkloadSORT::Sort(const WorkloadSORTCOLUMNS& sort)
{
	bMultiSort = TRUE;
	return multi.Sort(sort);
}

/////////////////////////////////////////////////////////////////////////////
