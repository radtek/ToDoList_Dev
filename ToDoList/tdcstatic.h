#if !defined(AFX_TDCSTATIC_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_)
#define AFX_TDCSTATIC_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// tdcstatic.h : header file
//

#include "resource.h"
#include "tdcstruct.h"

#include "..\shared\wclassdefines.h"
#include "..\shared\rcctrlparser.h"

/////////////////////////////////////////////////////////////////////////////////////

struct SHORTCUT
{
	DWORD dwShortcut;
	UINT nIDShortcut;
};

static const SHORTCUT MISC_SHORTCUTS[] = 
{
// 	{ MAKELONG('B', HOTKEYF_ALT | HOTKEYF_EXT), IDS_SETFOCUS2TASKLIST },
// 
// 	{ 0, 0 },	

	{ MAKELONG(VK_UP, HOTKEYF_SHIFT | HOTKEYF_EXT), IDS_TASKLISTEXTENDEDSELECTION },
	{ MAKELONG(VK_DOWN, HOTKEYF_SHIFT | HOTKEYF_EXT), IDS_TASKLISTEXTENDEDSELECTION },
	{ MAKELONG(VK_PRIOR, HOTKEYF_SHIFT | HOTKEYF_EXT), IDS_TASKLISTEXTENDEDSELECTION },
	{ MAKELONG(VK_NEXT, HOTKEYF_SHIFT | HOTKEYF_EXT), IDS_TASKLISTEXTENDEDSELECTION },
};
static const int NUM_MISCSHORTCUTS = sizeof(MISC_SHORTCUTS) / sizeof(SHORTCUT);

/////////////////////////////////////////////////////////////////////////////////////

// note: do not use 'c' as a shortcut letter
static const TDCCONTROL TDCCONTROLS[] = 
{
	{ WC_STATIC,	IDS_TDC_FIELD_PROJECT, SS_CENTERIMAGE, 0, 0,2,40,16, IDC_PROJECTLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | WS_TABSTOP, 0, 42,0,142,13, IDC_PROJECTNAME },
	{ WC_STATIC,	IDS_TDC_FIELD_PRIORITY, SS_CENTERIMAGE, 0, 119,131,22,8, IDC_PRIORITYLABEL },
	{ WC_COMBOBOX,	0, CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,128,65,300, IDC_PRIORITY },
	{ WC_STATIC,	IDS_TDC_FIELD_RISK, SS_CENTERIMAGE, 0, 119,131,22,8, IDC_RISKLABEL },
	{ WC_COMBOBOX,	0, CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,128,65,300, IDC_RISK },
	{ WC_STATIC,	IDS_TDC_FIELD_PERCENT, SS_CENTERIMAGE, 0, 119,148,37,8, IDC_PERCENTLABEL },
	{ WC_EDIT,		0, WS_TABSTOP, 0, 159,146,65,13, IDC_PERCENT },
	{ WC_SPIN,		0, UDS_SETBUDDYINT | UDS_ARROWKEYS, 0, 97,180,13,14, IDC_PERCENTSPIN },
	{ WC_STATIC,	IDS_TDC_FIELD_TIMEEST, SS_CENTERIMAGE, 0, 1,148,40,8, IDC_TIMEESTLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | WS_TABSTOP, 0, 45,146,65,13, IDC_TIMEEST },
	{ WC_STATIC,	IDS_TDC_FIELD_TIMESPENT, SS_CENTERIMAGE, 0, 1,148,40,8, IDC_TIMESPENTLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | WS_TABSTOP, 0, 45,146,65,13, IDC_TIMESPENT },
	{ WC_STATIC,	IDS_TDC_FIELD_STARTDATE, SS_CENTERIMAGE, 0, 1,166,33,8, IDC_STARTLABEL },
	{ WC_DATETIMEPICK, 0, DTS_RIGHTALIGN | DTS_SHOWNONE | WS_TABSTOP, 0, 45,164,65,13, IDC_STARTDATE },
	{ WC_STATIC,	IDS_TDC_FIELD_STARTTIME, SS_CENTERIMAGE, 0, 119,166,32,8, IDC_STARTTIMELABEL },
	{ WC_COMBOBOX, 0, CBS_UPPERCASE | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,164,65,13, IDC_STARTTIME },
	{ WC_STATIC,	IDS_TDC_FIELD_DUEDATE, SS_CENTERIMAGE, 0, 119,166,32,8, IDC_DUELABEL },
	{ WC_DATETIMEPICK, 0, DTS_RIGHTALIGN | DTS_SHOWNONE | WS_TABSTOP, 0, 159,164,65,13, IDC_DUEDATE },
	{ WC_STATIC,	IDS_TDC_FIELD_DUETIME, SS_CENTERIMAGE, 0, 119,166,32,8, IDC_DUETIMELABEL },
	{ WC_COMBOBOX, 0, CBS_UPPERCASE | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,164,65,13, IDC_DUETIME },
	{ WC_STATIC,	IDS_TDC_FIELD_DONEDATE, SS_CENTERIMAGE, 0, 1,184,34,8, IDC_DONELABEL },
	{ WC_DATETIMEPICK, 0, DTS_RIGHTALIGN | DTS_SHOWNONE | WS_TABSTOP, 0, 45,182,65,13, IDC_DONEDATE },
	{ WC_STATIC,	IDS_TDC_FIELD_DONETIME, SS_CENTERIMAGE, 0, 119,166,32,8, IDC_DONETIMELABEL },
	{ WC_COMBOBOX, 0, CBS_UPPERCASE | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,164,65,13, IDC_DONETIME },
	{ WC_STATIC,	IDS_TDC_FIELD_RECURRENCE, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_RECURRENCELABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | ES_LEFT | WS_TABSTOP, 0, 159,182,65,13, IDC_RECURRENCE },
	{ WC_STATIC,	IDS_TDC_FIELD_COLOUR, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_COLOURLABEL },
	{ WC_BUTTON,	0, WS_TABSTOP, 0, 1,131,38,8, IDC_COLOUR },
	{ WC_STATIC,	IDS_TDC_FIELD_ALLOCTO, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_ALLOCTOLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_ALLOCTO },
	{ WC_STATIC,	IDS_TDC_FIELD_ALLOCBY, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_ALLOCBYLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_ALLOCBY },
	{ WC_STATIC,	IDS_TDC_FIELD_STATUS, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_STATUSLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_STATUS },
	{ WC_STATIC,	IDS_TDC_FIELD_CATEGORY, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_CATEGORYLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_CATEGORY },
	{ WC_STATIC,	IDS_TDC_FIELD_TAGS, SS_CENTERIMAGE, 0, 1,131,38,8, IDC_TAGSLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_TAGS },
	{ WC_STATIC,	IDS_TDC_FIELD_EXTID, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_EXTERNALIDLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | ES_LEFT | WS_TABSTOP, 0, 159,182,65,13, IDC_EXTERNALID },
	{ WC_STATIC,	IDS_TDC_FIELD_COST, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_COSTLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | ES_LEFT | WS_TABSTOP, 0, 159,182,65,13, IDC_COST },
	{ WC_STATIC,	IDS_TDC_FIELD_DEPENDENCY, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_DEPENDSLABEL },
	{ WC_EDIT,		0, ES_AUTOHSCROLL | ES_LEFT | WS_TABSTOP, 0, 159,182,65,13, IDC_DEPENDS },
	{ WC_STATIC,	IDS_TDC_FIELD_VERSION, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_VERSIONLABEL },
	{ WC_COMBOBOX,	0, CBS_SORT | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 45,128,65,200, IDC_VERSION },
	{ WC_STATIC,	IDS_TDC_FIELD_FILEREF, SS_CENTERIMAGE, 0, 119,184,37,8, IDC_FILEPATHLABEL },
	{ WC_COMBOBOX,	0, CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | WS_TABSTOP | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS, 0, 159,182,65,13, IDC_FILEPATH },
};
static const int NUM_TDCCTRLS = sizeof(TDCCONTROLS) / sizeof(TDCCONTROL);

/////////////////////////////////////////////////////////////////////////////////////

static const TDCCONTROL FTDCCONTROLS[] = 
{
	{ WC_TABCONTROL,0, TCS_BOTTOM | TCS_FOCUSNEVER | TCS_HOTTRACK | TCS_TABS | TCS_SINGLELINE | TCS_RIGHTJUSTIFY | TCS_TOOLTIPS | WS_TABSTOP | WS_CLIPCHILDREN, 0, 28,1,142,13, IDC_FTC_TABCTRL },
};
static const int NUM_FTDCCTRLS = sizeof(FTDCCONTROLS) / sizeof(TDCCONTROL);

/////////////////////////////////////////////////////////////////////////////////////

static const TDCCOLUMN COLUMNS[] = 
{
	{ TDCC_POSITION,		IDS_TDC_COLUMN_POS,			IDS_TDLBC_POS,			DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_ID,				IDS_TDC_COLUMN_ID,			IDS_TDLBC_ID,			DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },								
	{ TDCC_PARENTID,		IDS_TDC_COLUMN_PARENTID,	IDS_TDLBC_PARENTID,		DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },								
	{ TDCC_PRIORITY,		0,							IDS_TDLBC_PRIORITY,		DT_CENTER,	FALSE,	TDCCI_PRIORITY,		TDCCI_NONE },
	{ TDCC_LOCK,			0,							IDS_TDLBC_LOCK,			DT_CENTER,	FALSE,	TDCCI_LOCK,			TDCCI_LOCKCALC },
	{ TDCC_RISK,			0,							IDS_TDLBC_RISK,			DT_CENTER,	TRUE,	TDCCI_RISK,			TDCCI_NONE },
	{ TDCC_TRACKTIME,		0,							IDS_TDLBC_TRACKTIME,	DT_CENTER,	TRUE,	TDCCI_TRACKTIME,	TDCCI_NONE },
	{ TDCC_REMAINING,		0,							IDS_TDLBC_REMAINING,	DT_RIGHT,	TRUE,	TDCCI_REMAINING,	TDCCI_NONE },
	{ TDCC_DEPENDENCY,		0,							IDS_TDLBC_DEPENDS,		DT_CENTER,	TRUE,	TDCCI_DEPENDENCY,	TDCCI_NONE },
	{ TDCC_FILEREF,			0,							IDS_TDLBC_FILEREF,		DT_CENTER,	TRUE,	TDCCI_FILEREF,		TDCCI_NONE },
	{ TDCC_FLAG,			0,							IDS_TDLBC_FLAG,			DT_CENTER,	FALSE,	TDCCI_FLAG,			TDCCI_FLAGCALC },
	{ TDCC_REMINDER,		0,							IDS_TDLBC_REMINDER,		DT_CENTER,	FALSE,	TDCCI_REMINDER,		TDCCI_REMINDERDATEUNSET },
	{ TDCC_ICON,			0,							IDS_TDLBC_ICON,			DT_CENTER,	FALSE,	TDCCI_ICON,			TDCCI_NONE },
	{ TDCC_DONE,			0,							IDS_TDLBC_DONE,			DT_CENTER,	FALSE,	TDCCI_DONE,			TDCCI_NONE },
	{ TDCC_PERCENT,			IDS_TDC_COLUMN_PERCENT,		IDS_TDLBC_PERCENT,		DT_CENTER,	FALSE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_TIMEEST,			IDS_TDC_COLUMN_TIMEEST,		IDS_TDLBC_TIMEEST,		DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_TIMESPENT,		IDS_TDC_COLUMN_TIMESPENT,	IDS_TDLBC_TIMESPENT,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_CREATIONDATE,	IDS_TDC_COLUMN_CREATEDATE,	IDS_TDLBC_CREATEDATE,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_CREATEDBY,		IDS_TDC_COLUMN_CREATEDBY,	IDS_TDLBC_CREATEDBY,	DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_LASTMODDATE,		IDS_TDC_COLUMN_LASTMODDATE,	IDS_TDLBC_LASTMODDATE,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_LASTMODBY,		IDS_TDC_COLUMN_LASTMODBY,	IDS_TDLBC_LASTMODBY,	DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_RECENTEDIT,		IDS_TDC_COLUMN_RECENTEDIT,	IDS_TDLBC_RECENTEDIT,	DT_CENTER,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_STARTDATE,		IDS_TDC_COLUMN_STARTDATE,	IDS_TDLBC_STARTDATE,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_DUEDATE,			IDS_TDC_COLUMN_DUEDATE,		IDS_TDLBC_DUEDATE,		DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_DONEDATE,		IDS_TDC_COLUMN_DONEDATE,	IDS_TDLBC_DONEDATE,		DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_RECURRENCE,		IDS_TDC_COLUMN_RECURRENCE,	IDS_TDLBC_RECURRENCE,	DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_ALLOCTO,			IDS_TDC_COLUMN_ALLOCTO,		IDS_TDLBC_ALLOCTO,		DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_ALLOCBY,			IDS_TDC_COLUMN_ALLOCBY,		IDS_TDLBC_ALLOCBY,		DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_STATUS,			IDS_TDC_COLUMN_STATUS,		IDS_TDLBC_STATUS,		DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_CATEGORY,		IDS_TDC_COLUMN_CATEGORY,	IDS_TDLBC_CATEGORY,		DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_TAGS,			IDS_TDC_COLUMN_TAGS,		IDS_TDLBC_TAGS,			DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_EXTERNALID,		IDS_TDC_COLUMN_EXTID,		IDS_TDLBC_EXTERNALID,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_COST,			IDS_TDC_COLUMN_COST,		IDS_TDLBC_COST,			DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_VERSION,			IDS_TDC_COLUMN_VERSION,		IDS_TDLBC_VERSION,		DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_PATH,			IDS_TDC_COLUMN_PATH,		IDS_TDLBC_PATH,			DT_LEFT,	FALSE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_SUBTASKDONE,		IDS_TDC_COLUMN_SUBTASKDONE,	IDS_TDLBC_SUBTASKDONE,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	{ TDCC_COMMENTSSIZE,	IDS_TDC_COLUMN_COMMENTSSIZE,IDS_TDLBC_COMMENTSSIZE,	DT_RIGHT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
	
	// special client column
	{ TDCC_CLIENT,			IDS_TDC_COLUMN_TASK,		IDS_TDLBC_NAME,			DT_LEFT,	TRUE,	TDCCI_NONE,			TDCCI_NONE },
};
static const int NUM_COLUMNS = sizeof(COLUMNS) / sizeof(TDCCOLUMN);

static CString GetColumnName(TDC_COLUMN nColID)
{
	int nCol = NUM_COLUMNS;

	while (nCol--)
	{
		if (COLUMNS[nCol].nColID == nColID)
			return CEnString(COLUMNS[nCol].nIDLongName);
	}

	ASSERT(0);
	return _T("");
}

/////////////////////////////////////////////////////////////////////////////////////

static const CTRLITEM CTRLITEMS[] = 
{
	{ IDC_PRIORITY,		IDC_PRIORITYLABEL,	TDCA_PRIORITY },
	{ IDC_RISK,			IDC_RISKLABEL,		TDCA_RISK },
	{ IDC_PERCENT,		IDC_PERCENTLABEL,	TDCA_PERCENT },
	{ IDC_TIMEEST,		IDC_TIMEESTLABEL,	TDCA_TIMEEST },
	{ IDC_TIMESPENT,	IDC_TIMESPENTLABEL,	TDCA_TIMESPENT },
	{ IDC_STARTDATE,	IDC_STARTLABEL,		TDCA_STARTDATE },
	{ IDC_STARTTIME,	IDC_STARTTIMELABEL,	TDCA_STARTTIME },
	{ IDC_DUEDATE,		IDC_DUELABEL,		TDCA_DUEDATE },
	{ IDC_DUETIME,		IDC_DUETIMELABEL,	TDCA_DUETIME },
	{ IDC_DONEDATE,		IDC_DONELABEL,		TDCA_DONEDATE },
	{ IDC_DONETIME,		IDC_DONETIMELABEL,	TDCA_DONETIME },
	{ IDC_RECURRENCE,	IDC_RECURRENCELABEL,TDCA_RECURRENCE },
	{ IDC_COLOUR,		IDC_COLOURLABEL,	TDCA_COLOR },
	{ IDC_ALLOCTO,		IDC_ALLOCTOLABEL,	TDCA_ALLOCTO },
	{ IDC_ALLOCBY,		IDC_ALLOCBYLABEL,	TDCA_ALLOCBY },
	{ IDC_STATUS,		IDC_STATUSLABEL,	TDCA_STATUS },
	{ IDC_CATEGORY,		IDC_CATEGORYLABEL,	TDCA_CATEGORY },
	{ IDC_TAGS,			IDC_TAGSLABEL,		TDCA_TAGS },
	{ IDC_EXTERNALID,	IDC_EXTERNALIDLABEL,TDCA_EXTERNALID },
	{ IDC_COST,			IDC_COSTLABEL,		TDCA_COST },
	{ IDC_DEPENDS,		IDC_DEPENDSLABEL,	TDCA_DEPENDENCY },
	{ IDC_VERSION,		IDC_VERSIONLABEL,	TDCA_VERSION },
	{ IDC_FILEPATH,		IDC_FILEPATHLABEL,	TDCA_FILEREF },
};
static const int NUM_CTRLITEMS = sizeof(CTRLITEMS) / sizeof(CTRLITEM);

/////////////////////////////////////////////////////////////////////////////////////

static const UINT FILTER_OPTIONS[][2] = 
{ 
	{ IDS_FILTER_ANYCATS,		FO_ANYCATEGORY },
	{ IDS_FILTER_ANYPEOPLE,		FO_ANYALLOCTO },
	{ IDS_FILTER_ANYTAGS,		FO_ANYTAG },
	{ IDS_FILTER_HIDEPARENTS,	FO_HIDEPARENTS },
	{ IDS_FILTER_HIDEOVERDUE,	FO_HIDEOVERDUE },
	{ IDS_FILTER_HIDEDONE,		FO_HIDEDONE },
	{ IDS_FILTER_HIDECOLLAPSED,	FO_HIDECOLLAPSED },
	{ IDS_FILTER_SHOWALLSUB,	FO_SHOWALLSUB },
};
static const int NUM_FILTEROPT = sizeof(FILTER_OPTIONS) / (2 * sizeof(UINT));

/////////////////////////////////////////////////////////////////////////////////////

static const UINT SHOW_FILTERS[][2] = 
{ 
	{ IDS_FILTER_ALL,			FS_ALL },
	{ IDS_FILTER_NOTDONE,		FS_NOTDONE },
	{ IDS_FILTER_DONE,			FS_DONE }, 
	{ IDS_FILTER_FLAGGED,		FS_FLAGGED },
	{ IDS_FILTER_SELECTED,		FS_SELECTED },
	{ IDS_FILTER_RECENTMOD,		FS_RECENTMOD },
	{ IDS_FILTER_LOCKED,		FS_LOCKED }
};
static const int NUM_SHOWFILTER = sizeof(SHOW_FILTERS) / (2 * sizeof(UINT));

/////////////////////////////////////////////////////////////////////////////////////

static const UINT DATE_FILTERS[][2] = 
{ 
	{ IDS_FILTER_ANYDATE,		FD_ANY },
	{ IDS_FILTER_NODATE,		FD_NONE },
	{ IDS_FILTER_USERDATE,		FD_USER },
	{ IDS_FILTER_NOW,			FD_NOW },
	{ IDS_FILTER_TODAY,			FD_TODAY },
	{ IDS_FILTER_TOMORROW,		FD_TOMORROW },
	{ IDS_FILTER_ENDTHISWEEK,	FD_ENDTHISWEEK }, 
	{ IDS_FILTER_ENDNEXTWEEK,	FD_ENDNEXTWEEK }, 
	{ IDS_FILTER_ENDTHISMONTH,	FD_ENDTHISMONTH },
	{ IDS_FILTER_ENDNEXTMONTH,	FD_ENDNEXTMONTH },
	{ IDS_FILTER_ENDTHISYEAR,	FD_ENDTHISYEAR },
	{ IDS_FILTER_ENDNEXTYEAR,	FD_ENDNEXTYEAR },
	{ IDS_FILTER_NEXTSEVENDAYS,	FD_NEXTNDAYS },
	{ IDS_FILTER_YESTERDAY,		FD_YESTERDAY },
};
static const int NUM_DATEFILTER = sizeof(DATE_FILTERS) / (2 * sizeof(UINT));

/////////////////////////////////////////////////////////////////////////////////////

static const TDCATTRIBUTE ATTRIBUTES[] = 
{
	{ TDCA_NONE,				0 },
	{ TDCA_TASKNAME,			IDS_TDLBC_TITLE },
	{ TDCA_DONEDATE,			IDS_TDLBC_DONEDATE },
	{ TDCA_DUEDATE,				IDS_TDLBC_DUEDATE },
	{ TDCA_STARTDATE,			IDS_TDLBC_STARTDATE },
	{ TDCA_PRIORITY,			IDS_TDLBC_PRIORITY },
	{ TDCA_COLOR,				IDS_TDLBC_COLOR },
	{ TDCA_ALLOCTO,				IDS_TDLBC_ALLOCTO },
	{ TDCA_ALLOCBY,				IDS_TDLBC_ALLOCBY },
	{ TDCA_STATUS,				IDS_TDLBC_STATUS },
	{ TDCA_CATEGORY,			IDS_TDLBC_CATEGORY },
	{ TDCA_TAGS,				IDS_TDLBC_TAGS },
	{ TDCA_PERCENT,				IDS_TDLBC_PERCENT },
	{ TDCA_TIMEEST,				IDS_TDLBC_TIMEEST },
	{ TDCA_TIMESPENT,			IDS_TDLBC_TIMESPENT },
	{ TDCA_FILEREF,				IDS_TDLBC_FILEREF },
	{ TDCA_PROJECTNAME,			IDS_TDLBC_PROJECTNAME },
	{ TDCA_FLAG,				IDS_TDLBC_FLAG },
	{ TDCA_LOCK,				IDS_TDLBC_LOCK },
	{ TDCA_CREATIONDATE,		IDS_TDLBC_CREATEDATE },
	{ TDCA_CREATEDBY,			IDS_TDLBC_CREATEDBY },
	{ TDCA_RISK,				IDS_TDLBC_RISK },
	{ TDCA_EXTERNALID,			IDS_TDLBC_EXTERNALID },
	{ TDCA_COST,				IDS_TDLBC_COST },
	{ TDCA_DEPENDENCY,			IDS_TDLBC_DEPENDS },
	{ TDCA_RECURRENCE,			IDS_TDLBC_RECURRENCE },
	{ TDCA_VERSION,				IDS_TDLBC_VERSION  },
	{ TDCA_POSITION,			IDS_TDLBC_POS },
	{ TDCA_PATH,				IDS_TDC_COLUMN_PATH }, // special case
	{ TDCA_ID,					IDS_TDLBC_ID },
	{ TDCA_PARENTID,			IDS_TDLBC_PARENTID },
	{ TDCA_LASTMODDATE,			IDS_TDLBC_LASTMODDATE },
	{ TDCA_LASTMODBY,			IDS_TDLBC_LASTMODBY },
	{ TDCA_COMMENTS,			IDS_TDLBC_COMMENTS },
	{ TDCA_TASKNAMEORCOMMENTS,	IDS_TDLBC_TITLEORCOMMENTS },
	{ TDCA_ANYTEXTATTRIBUTE,	IDS_TDLBC_ANYTEXTATTRIB },
	{ TDCA_SUBTASKDONE,			IDS_TDLBC_SUBTASKDONE },
	{ TDCA_ICON,				IDS_TDLBC_ICON },
	{ TDCA_COMMENTSSIZE,		IDS_TDLBC_COMMENTSSIZE },
};
static const int ATTRIB_COUNT = sizeof(ATTRIBUTES) / sizeof(TDCATTRIBUTE);

static CString GetAttributeName(TDC_ATTRIBUTE nAttrib)
{
	int nAtt = ATTRIB_COUNT;

	while (nAtt--)
	{
		if (ATTRIBUTES[nAtt].attrib == nAttrib)
			return CEnString(ATTRIBUTES[nAtt].nAttribResID);
	}

	ASSERT(0);
	return _T("");
}

/////////////////////////////////////////////////////////////////////////////////////

static const TDCOPERATOR OPERATORS[] =
{
	{ FOP_NONE,				0 },
	{ FOP_EQUALS,			IDS_FP_EQUALS },
	{ FOP_NOT_EQUALS,		IDS_FP_NOT_EQUALS },
	{ FOP_INCLUDES,			IDS_FP_INCLUDES },
	{ FOP_NOT_INCLUDES,		IDS_FP_NOT_INCLUDES },
	{ FOP_ON_OR_BEFORE,		IDS_FP_ON_OR_BEFORE },
	{ FOP_BEFORE,			IDS_FP_BEFORE },
	{ FOP_ON_OR_AFTER,		IDS_FP_ON_OR_AFTER },
	{ FOP_AFTER,			IDS_FP_AFTER },
	{ FOP_GREATER_OR_EQUAL, IDS_FP_GREATER_OR_EQUAL },
	{ FOP_GREATER,			IDS_FP_GREATER },
	{ FOP_LESS_OR_EQUAL,	IDS_FP_LESS_OR_EQUAL },
	{ FOP_LESS,				IDS_FP_LESS },
	{ FOP_SET,				IDS_FP_SET },
	{ FOP_NOT_SET,			IDS_FP_NOT_SET }
};
static const int OP_COUNT = sizeof(OPERATORS) / sizeof(TDCOPERATOR);

/////////////////////////////////////////////////////////////////////////////////////


#endif // AFX_TDCSTATIC_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_