
// DB-MiniProject3-Minhyeok_ChoiDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DB-MiniProject3-Minhyeok_Choi.h"
#include "DB-MiniProject3-Minhyeok_ChoiDlg.h"
#include "afxdialogex.h"

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <vector>
#include <string>

#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDBMiniProject3MinhyeokChoiDlg 대화 상자



CDBMiniProject3MinhyeokChoiDlg::CDBMiniProject3MinhyeokChoiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DBMINIPROJECT3MINHYEOK_CHOI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hEnv = NULL;
	hDbc = NULL;
}

void CDBMiniProject3MinhyeokChoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Field, m_editField);
	DDX_Control(pDX, IDC_INPUT, m_editInput);
}

	BEGIN_MESSAGE_MAP(CDBMiniProject3MinhyeokChoiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Check_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedCheckButton)
	ON_BN_CLICKED(SELECT_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedSELECTButton)
	ON_BN_CLICKED(INSERT_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedINSERTButton)
	ON_BN_CLICKED(DELETE_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedDELETEButton)
	ON_BN_CLICKED(UPDATE_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedUPDATEButton)
	ON_BN_CLICKED(Custom_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedCustomButton)

	ON_BN_CLICKED(Ok_Button, &CDBMiniProject3MinhyeokChoiDlg::OnBnClickedOkButton)
	END_MESSAGE_MAP()


// CDBMiniProject3MinhyeokChoiDlg 메시지 처리기

BOOL CDBMiniProject3MinhyeokChoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CFont* pFont = new CFont;
	pFont->CreatePointFont(100, _T("Consolas")); // 또는 "Courier New"
	m_editField.SetFont(pFont);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDBMiniProject3MinhyeokChoiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDBMiniProject3MinhyeokChoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDBMiniProject3MinhyeokChoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CDBMiniProject3MinhyeokChoiDlg::db_connect()
{
	SQLRETURN ret;

	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return false;
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) return false;

	ret = SQLConnect(hDbc,
		(SQLCHAR*)"DB01_Server", SQL_NTS,
		(SQLCHAR*)"KIM", SQL_NTS,
		(SQLCHAR*)"1234", SQL_NTS);

	return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}


void CDBMiniProject3MinhyeokChoiDlg::db_disconnect()
{
	if (hDbc) { SQLDisconnect(hDbc); SQLFreeHandle(SQL_HANDLE_DBC, hDbc); hDbc = NULL; }
	if (hEnv) { SQLFreeHandle(SQL_HANDLE_ENV, hEnv); hEnv = NULL; }
}


void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedCheckButton()
{
	SQLHSTMT hStmtTable = NULL, hStmtCol = NULL;
	SQLRETURN ret;
	CString result;

	struct TableInfo {
		std::string catalog;
		std::string schema;
		std::string name;
	};
	std::vector<TableInfo> tables;

	SQLCHAR catalog[256], schema[256], tableName[256], tableType[256];
	SQLCHAR columnName[256];
	SQLSMALLINT dataType;

	result += ">> 테이블 목록 및 컬럼 정보 <<\r\n\r\n";

	if (!db_connect()) {
		m_editField.SetWindowText("DB 연결 실패");
		return;
	}

	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmtTable);
	SQLTables(hStmtTable, NULL, 0, NULL, 0, NULL, 0, (SQLCHAR*)"TABLE", SQL_NTS);

	SQLBindCol(hStmtTable, 1, SQL_C_CHAR, catalog, sizeof(catalog), NULL);
	SQLBindCol(hStmtTable, 2, SQL_C_CHAR, schema, sizeof(schema), NULL);
	SQLBindCol(hStmtTable, 3, SQL_C_CHAR, tableName, sizeof(tableName), NULL);
	SQLBindCol(hStmtTable, 4, SQL_C_CHAR, tableType, sizeof(tableType), NULL);

	while (SQLFetch(hStmtTable) == SQL_SUCCESS) {
		if (strncmp((char*)tableName, "trace_", 6) == 0) continue;

		TableInfo t;
		t.catalog = (char*)catalog;
		t.schema = (char*)schema;
		t.name = (char*)tableName;
		tables.push_back(t);
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmtTable);

	for (const auto& t : tables) {
		result += "[Table: " + CString(t.name.c_str()) + "]\r\n";

		SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmtCol);
		ret = SQLColumns(hStmtCol,
			(SQLCHAR*)t.catalog.c_str(), SQL_NTS,
			(SQLCHAR*)t.schema.c_str(), SQL_NTS,
			(SQLCHAR*)t.name.c_str(), SQL_NTS,
			NULL, 0);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			SQLBindCol(hStmtCol, 4, SQL_C_CHAR, columnName, sizeof(columnName), NULL);
			SQLBindCol(hStmtCol, 5, SQL_C_SSHORT, &dataType, 0, NULL);

			bool hasColumn = false;
			while (SQLFetch(hStmtCol) == SQL_SUCCESS) {
				hasColumn = true;

				CString typeStr;
				switch (dataType) {
				case SQL_CHAR: typeStr = "CHAR"; break;
				case SQL_VARCHAR: typeStr = "VARCHAR"; break;
				case SQL_INTEGER: typeStr = "INT"; break;
				case SQL_BIGINT: typeStr = "BIGINT"; break;
				case SQL_SMALLINT: typeStr = "SMALLINT"; break;
				case SQL_FLOAT: typeStr = "FLOAT"; break;
				case SQL_DOUBLE: typeStr = "DOUBLE"; break;
				case SQL_BIT: typeStr = "BIT"; break;
				case SQL_TYPE_DATE: typeStr = "DATE"; break;
				default:
					typeStr.Format("TYPE %d", dataType); break;
				}

				result += "- " + CString((char*)columnName) + " (" + typeStr + ")\r\n";
			}

			if (!hasColumn)
				result += "- (컬럼 없음)\r\n";
		}
		else {
			SQLCHAR sqlState[6], message[256];
			SQLINTEGER nativeError;
			SQLSMALLINT msgLen;

			SQLGetDiagRec(SQL_HANDLE_STMT, hStmtCol, 1, sqlState, &nativeError, message, sizeof(message), &msgLen);

			result += "  [컬럼 정보를 가져오지 못했습니다] ";
			result += CString((char*)message);
			result += "\r\n";
		}

		result += "\r\n";
		SQLFreeHandle(SQL_HANDLE_STMT, hStmtCol);
	}

	m_editField.SetWindowText(result);

	db_disconnect();
}


void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedSELECTButton()
{
	m_menu = 0;
	m_selectStep = 0;
	m_selectedOption = 0;
	m_editField.SetWindowText(
		_T("조회할 항목을 선택하세요:\r\n")
		"1. 주민번호로 예약 조회\r\n"
		"2. 날짜로 예약 조회\r\n"
		"3. 사업자로 서비스 조회\r\n"
		"4. 서비스가 제공하는 타임 슬롯 조회\r\n"
		"5. 사업자의 예약 받은 내역 조회\r\n"
		"6. 내 정보 조회\r\n"
		"선택 번호를 입력한 뒤 [확인]을 눌러주세요.");
	m_editInput.SetWindowText(_T(""));
}

void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedINSERTButton()
{
	m_menu = 1;
	m_selectStep = 0;
	m_selectedOption = 0;
	m_editField.SetWindowText(
		_T("수행할 항목을 선택하세요:\r\n")
		"1. 고객의 새로운 예약 등록\r\n"
		"2. 사업체의 새로운 서비스 등록\r\n"
		"3. 새로운 고객 정보 등록\r\n"
		"4. 서비스의 제공 타임 슬롯 추가\r\n\r\n"
		"선택 번호를 입력한 뒤 [확인]을 눌러주세요.");
	m_editInput.SetWindowText(_T(""));
}

void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedDELETEButton(){
	m_menu = 2;
	m_selectStep = 0;
	m_selectedOption = 0;
	m_editField.SetWindowText(
		_T("수행할 항목을 선택하세요:\r\n")
		"1. 고객 주민번호를 기반으로 예약 삭제\r\n"
		"2. Provider가 제공하는 서비스 삭제\r\n\r\n"
		"선택 번호를 입력한 뒤 [확인]을 눌러주세요.");
	m_editInput.SetWindowText(_T(""));
}

void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedUPDATEButton(){
	m_menu = 3;
	m_selectStep = 0;
	m_selectedOption = 0;
	m_editField.SetWindowText(
		_T("수행할 항목을 선택하세요:\r\n")
		"1. Provider가 제공하는 서비스의 가격 수정\r\n"
		"2. Service가 제공하는 TimeSlot의 시간 수정\r\n"
		"3. Client 예약 인원 수정\r\n\r\n"
		"선택 번호를 입력한 뒤 [확인]을 눌러주세요.");
	m_editInput.SetWindowText(_T(""));
}

void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedCustomButton() {
	m_menu = 4;
	m_selectStep = 0;
	m_selectedOption = 0;
	m_editField.SetWindowText(_T("원하는 SQL문을 직접 작성해 주세요.\r\n"));
	m_editInput.SetWindowText(_T(""));
}

void CDBMiniProject3MinhyeokChoiDlg::OnBnClickedOkButton() {
	CString input;
	m_editInput.GetWindowText(input);
	input.Trim();

	if (input.IsEmpty()) {
		m_editField.SetWindowText(_T("입력이 비어 있습니다."));
		return;
	}

	char query[512] = { 0 };
	SQLHSTMT hStmt = NULL;
	SQLRETURN ret;
	CString result;


	switch (m_menu)
	{
	case 0: //m_menu == 0 일때는 SELECT
		if (m_selectStep == 0) {
			m_selectedOption = _ttoi(input);
			CT2A ascii(input);

			if (!db_connect()) {
				m_editField.SetWindowText(_T("DB 연결 실패"));
				return;
			}
			
			if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
				switch (m_selectedOption)
				{
				case 1:
					m_editField.SetWindowText(_T("주민번호를 입력하세요:"));
					m_selectStep = 1;
					break;
				case 2:
					m_editField.SetWindowText(_T("날짜를 입력하세요 (YYYY-MM-DD):"));
					m_selectStep = 1;
					break;
				case 3:
					SELECT_AllProvider(hStmt, ret, (const char*)ascii, query, result);
					result += _T("사업자 ID를 입력하세요:");
					m_editField.SetWindowText(result);
					m_selectStep = 1;
					break;
				case 4:
					SELECT_AllService(hStmt, ret, (const char*)ascii, query, result);
					result += _T("서비스 ID를 입력하세요:");
					m_editField.SetWindowText(result);
					m_selectStep = 1;
					break;
				case 5:
					SELECT_AllProvider(hStmt, ret, (const char*)ascii, query, result);
					result += _T("사업자 ID를 입력하세요:");
					m_editField.SetWindowText(result);
					m_selectStep = 1;
					break;
				case 6:
					m_editField.SetWindowText(_T("주민번호를 입력하세요:"));
					m_selectStep = 1;
					break;
				default:
					m_editField.SetWindowText(_T("유효한 번호를 입력하세요 (1~6)"));
					break;
				}
			}

			
			
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			db_disconnect();
			m_editInput.SetWindowText(_T(""));
			return;
		}
		else if (m_selectStep == 1) {

			if (!db_connect()) {
				m_editField.SetWindowText(_T("DB 연결 실패"));
				return;
			}

			CT2A ascii(input);


			if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

				switch (m_selectedOption) {
				case 1:
					SELECT_ReservationByRes(hStmt, ret, (const char*)ascii, query, result);
					break;
				case 2:
					SELECT_ReservationByDate(hStmt, ret, (const char*)ascii, query, result);
					break;
				case 3:
					SELECT_ServiceByPro(hStmt, ret, (const char*)ascii, query, result);
					break;
				case 4:
					SELECT_TimeSlotByS_id(hStmt, ret, (const char*)ascii, query, result);
					break;
				case 5:
					SELECT_ReservationByPro(hStmt, ret, (const char*)ascii, query, result);
					break;
				case 6:
					SELECT_ClientByRes(hStmt, ret, (const char*)ascii, query, result);
					break;
				}



				m_editField.SetWindowText(result);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_editInput.SetWindowText(_T(""));
			}
		}
		break;

	case 1: //INSERT
		if (m_selectStep == 0) {
			CT2A ascii(input);
			m_selectedOption = _ttoi(input);

			// step 1. 메뉴 번호 선택
			switch (m_selectedOption)
			{
			case 1:
				m_editField.SetWindowText(_T("주민번호, 서비스 ID, 시간대 ID, 예약 인원, 예약 날짜(YYYY-MM-DD)를 입력하세요(공백 없이 컴마로 구분하여 입력할 것) :"));
				m_selectStep = 1;
				break;
			case 2:
				m_editField.SetWindowText(_T("사업자 ID, 서비스명, 서비스에 대한 간단한 설명, 가격, 서비스 유형을 입력하세요(공백 없이 컴마로 구분하여 입력할 것) :"));
				m_selectStep = 1;
				break;
			case 3:
				m_editField.SetWindowText(_T("주민번호, 이름, 이메일, 전화번호, 나이를 입력하세요(공백 없이 컴마로 구분하여 입력할 것) :"));
				m_selectStep = 1;
				break;
			case 4:
				db_connect();
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
				SELECT_AllService(hStmt, ret, (const char*)ascii, query, result);
				result += _T("타임 슬롯 추가를 원하는 서비스 ID를 입력하세요 :");
				m_editField.SetWindowText(result);
				m_selectStep = 1;

				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();


				break;
			default:
				m_editField.SetWindowText(_T("유효한 번호를 입력하세요 (1~4)"));
				break;
			}




			m_editInput.SetWindowText(_T(""));
			return;
		}
		else if (m_selectStep == 1) {
			CStringArray tokens;
			CString token;
			switch (m_selectedOption)
			{
			case 1: {
				int cur = 0;
				while (AfxExtractSubString(token, input, cur, ',')) {
					tokens.Add(token);
					cur++;
				}

				if (tokens.GetSize() != 5) {
					m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
					m_selectStep = 0;
					return;
				}


				if (!db_connect()) {
					m_editField.SetWindowText(_T("DB 연결 실패"));
					return;
				}

				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


				sprintf_s(query, "INSERT INTO Reservation (client_id) VALUES ('%s');", tokens[0]);

				ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
				if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
					m_editField.SetWindowText(_T("Reservation 등록 실패"));
					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					db_disconnect();
					m_selectStep = 0;
					return;
				}

				SQLCloseCursor(hStmt);

				SQLExecDirect(hStmt, (SQLCHAR*)"SELECT MAX(reservation_id) FROM Reservation", SQL_NTS);

				SQLINTEGER reservation_id;
				SQLLEN ind;

				SQLBindCol(hStmt, 1, SQL_C_SLONG, &reservation_id, 0, &ind);

				if (SQLFetch(hStmt) != SQL_SUCCESS) {
					m_editField.SetWindowText(_T("Reservation ID 조회 실패"));

					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					db_disconnect();
					return;
				}
				SQLCloseCursor(hStmt);

				// MakesReservation INSERT
				sprintf_s(query, "INSERT INTO MakesReservation (reservation_id, service_id, timeslot_id, num_guest, reservation_date) VALUES (%d, '%s', '%s', '%s', '%s')", reservation_id, tokens[1], tokens[2], tokens[3], tokens[4]);

				ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

				if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
					m_editField.SetWindowText(_T("MakesReservation 등록 실패."));
				}
				else {
					result.Format(_T("예약이 성공적으로 등록되었습니다.\r\n등록된 reservation_id : %d"), ind);
					m_editField.SetWindowText(result);
				}

				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 0;
				m_editInput.SetWindowText(_T(""));

				break;
			}
			case 2: {
				int cur = 0;
				while (AfxExtractSubString(token, input, cur, ',')) {
					tokens.Add(token);
					cur++;
				}

				if (tokens.GetSize() != 5) {
					m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
					m_selectStep = 0;
					return;
				}

				if (!db_connect()) {
					m_editField.SetWindowText(_T("DB 연결 실패"));
					m_selectStep = 0;
					return;
				}

				hStmt = NULL;
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


				sprintf_s(query, "INSERT INTO Service (provider_id, service_name, description, price, service_type) VALUES ('%s', '%s', '%s', %s, '%s')", tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
				ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

				if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
					CString errorMessage;
					errorMessage = _T("Service 등록 실패\n쿼리:\n");
					m_editField.SetWindowText(errorMessage + " " + query);
				}
				else {
					SQLCloseCursor(hStmt);
					SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
					SQLExecDirect(hStmt, (SQLCHAR*)"SELECT MAX(service_id) FROM Service", SQL_NTS);

					SQLINTEGER service_id;
					SQLLEN ind;

					SQLBindCol(hStmt, 1, SQL_C_SLONG, &service_id, 0, &ind);

					if (SQLFetch(hStmt) == SQL_SUCCESS) {
						CString msg;
						msg.Format(_T("서비스가 성공적으로 등록되었습니다.\n생성된 service_id: %d"), service_id);
						m_editField.SetWindowText(msg);
					}
					else {
						m_editField.SetWindowText(_T("서비스 등록 성공 (service_id 조회 실패)"));
					}

					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				}

				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 0;
				m_editInput.SetWindowText(_T(""));
				break;
			}
			case 3: {
				int cur = 0;
				while (AfxExtractSubString(token, input, cur, ',')) {
					tokens.Add(token);
					cur++;
				}

				if (tokens.GetSize() != 5) {
					m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
					m_selectStep = 0;
					return;
				}

				if (!db_connect()) {
					m_editField.SetWindowText(_T("DB 연결 실패"));
					m_selectStep = 0;
					return;
				}

				hStmt = NULL;
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


				sprintf_s(query, "INSERT INTO Client (resident_number, name, email, phone_number, age) VALUES ('%s', '%s', '%s', '%s', '%s')", tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
				ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

				if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
					CString errorMessage;
					errorMessage = _T("Client 등록 실패\n쿼리:\n");
					m_editField.SetWindowText(errorMessage + " " + query);
				}
				else {
					SQLCloseCursor(hStmt);
					SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
					SQLExecDirect(hStmt, (SQLCHAR*)"SELECT MAX(service_id) FROM Client", SQL_NTS);

					SQLINTEGER client_id;
					SQLLEN ind;

					SQLBindCol(hStmt, 1, SQL_C_SLONG, &client_id, 0, &ind);

					if (SQLFetch(hStmt) == SQL_SUCCESS) {
						CString msg;
						msg.Format(_T("고객이 성공적으로 등록되었습니다.\n생성된 client_id : %d"), client_id);
						m_editField.SetWindowText(msg);
					}
					else {
						m_editField.SetWindowText(_T("서비스 등록 성공 (client_id 조회 실패)"));
					}

					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				}

				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 0;
				m_editInput.SetWindowText(_T(""));
				break;
			}

				break;
			case 4:

				break;
			default:
				break;
			}


		}
		break;

	case 2: //DELETE
		if (m_selectStep == 0) {
			// step 1. 메뉴 번호 선택
			m_selectedOption = _ttoi(input);
			if (m_selectedOption == 1) {
				m_editField.SetWindowText(_T("예약자의 주민번호를 입력하세요 : "));
				m_selectStep++;
			}
			else if (m_selectedOption == 2) {
				m_editField.SetWindowText(_T("서비스를 삭제할 Provider_id를 입력하세요 :"));
				m_selectStep++;
			}
			else
			{
				m_editField.SetWindowText(_T("유효한 번호를 입력하세요 (1~2)"));
			}
			m_editInput.SetWindowText(_T(""));
			return;
		}
		else if (m_selectStep == 1) {
			m_editInput.GetWindowText(input);
			input.Trim();
			CT2A ascii(input);


			if (db_connect()) {
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

				if (m_selectedOption == 1) {
					SELECT_ReservationByRes(hStmt, ret, (const char*)ascii, query, result);
					result += _T("\n삭제할 예약의 id를 입력하세요\r\n");
				}
				else if (m_selectedOption == 2) {
					SELECT_ServiceByPro(hStmt, ret, (const char*)ascii, query, result);
					result += _T("\n삭제할 서비스의 id를 입력하세요\r\n");
				}

				m_editField.SetWindowText(result);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 2;
				m_editInput.SetWindowText(_T(""));
			}
			else {
				m_editInput.SetWindowText(_T("DB 연결 실패"));
			}

		}
		else if (m_selectStep == 2) {
			m_editInput.GetWindowText(input);
			input.Trim();
			CT2A ascii(input);

			if (db_connect()) {
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

				if (m_selectedOption == 1) {

					sprintf_s(query, "DELETE FROM Reservation WHERE reservation_id = %s;", (const char*)ascii);

					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						result = _T((const char*)ascii);
						result += _T("번 예약이 삭제 완료되었습니다.\r\n");
					}
				}
				else if (m_selectedOption == 2) {
					sprintf_s(query, "DELETE FROM Service WHERE service_id = %s", (const char*)ascii);

					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						result = _T((const char*)ascii);
						result += _T("번 서비스가 삭제 완료되었습니다.\r\n");
					}
				}
				m_editField.SetWindowText(result);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 2;
				m_editInput.SetWindowText(_T(""));
			}
			else {
				result = _T("DB연결 오류\r\n");
			}
		}
		break;

	case 3: //UPDATE
		if (m_selectStep == 0) {
			m_selectedOption = _ttoi(input);
			CT2A ascii(input);
			if (m_selectedOption == 1) {
				if (db_connect()) {

					if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

						SELECT_AllProvider(hStmt, ret, (const char*)ascii, query, result);

						SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
						db_disconnect();
					}
					else {
						m_editField.SetWindowText(_T("Statement 할당 실패"));
					}
				}
				else {
					m_editField.SetWindowText(_T("DB 연결 실패"));
				}
				result += _T("\r\nservice를 수정할 Provider_id를 입력하세요 : ");
				m_editField.SetWindowText(result);
			}
			else if (m_selectedOption == 2) {

				if (db_connect()) {

					SQLCHAR service_name[100], description[255], service_type[50];
					SQLINTEGER service_id, price, provider_id;
					SQLLEN cb1, cb2, cb3, cb4, cb5, cb6;

					if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

						sprintf_s(query, "SELECT * FROM Service");
						ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

						if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
							SQLBindCol(hStmt, 1, SQL_C_LONG, &service_id, 0, &cb1);
							SQLBindCol(hStmt, 2, SQL_C_CHAR, service_name, sizeof(service_name), &cb2);
							SQLBindCol(hStmt, 3, SQL_C_CHAR, description, sizeof(description), &cb3);
							SQLBindCol(hStmt, 4, SQL_C_LONG, &price, 0, &cb4);
							SQLBindCol(hStmt, 5, SQL_C_CHAR, service_type, sizeof(service_type), &cb5);
							SQLBindCol(hStmt, 6, SQL_C_LONG, &provider_id, 0, &cb6);

							result = _T("서비스 정보:\r\n");
							result += _T("--------------------------------------------------------------\r\n");
							while (SQLFetch(hStmt) == SQL_SUCCESS) {
								result += _T("Service ID        : ");
								result.AppendFormat(_T("%d\r\n"), service_id);

								result += _T("Service Name      : ");
								result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

								result += _T("Description       : ");
								result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)description);

								result += _T("Service Type      : ");
								result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_type);

								result += _T("Price             : ");
								result.AppendFormat(_T("%d\r\n"), cb4 == SQL_NULL_DATA ? 0 : price);

								result += _T("Provider ID       : ");
								result.AppendFormat(_T("%d\r\n"), cb6 == SQL_NULL_DATA ? 0 : provider_id);
								result += _T("--------------------------------------------------------------\r\n");
							}

						}
						else {
							result = _T("쿼리 실행 실패");
						}

						SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
						db_disconnect();
					}
					else {
						m_editField.SetWindowText(_T("Statement 할당 실패"));
					}
				}
				else {
					m_editField.SetWindowText(_T("DB 연결 실패"));
				}


				result += _T("\r\nTimeSlot을 수정할 service_id를 입력하세요 : ");
				m_editField.SetWindowText(result);
			}
			else if (m_selectedOption == 3) {
				m_editField.SetWindowText(_T("예약 정보를 변경할 예약자의 주민번호를 입력하세요 :"));
			}
			else
			{
				m_editField.SetWindowText(_T("유효한 번호를 입력하세요 (1~3)"));
			}
			m_editInput.SetWindowText(_T(""));
			m_selectStep = 1;
			return;
		}
		else if (m_selectStep == 1) {
			m_editInput.GetWindowText(input);
			input.Trim();
			CT2A ascii(input);

			if (db_connect()) {
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


				if (m_selectedOption == 1) {
					SELECT_ServiceByPro(hStmt, ret, (const char*)ascii, query, result);
					result += _T("\r\n가격을 수정할 서비스의 ID와 새로운 가격을 입력하세요 (컴마로 공백없이 구분):\r\n");
				}

				else if (m_selectedOption == 2) {
					sprintf_s(query, "SELECT T.timeslot_id, T.start_time, T.end_time, T.is_available, T.capacity, T.service_id FROM TimeSlot T WHERE T.service_id = %s",
						(const char*)ascii);

					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						SQLINTEGER timeslot_id, capacity, service_id;
						SQLCHAR start_time[50], end_time[50], is_available[10];
						SQLLEN cb1, cb2, cb3, cb4, cb5, cb6;

						SQLBindCol(hStmt, 1, SQL_C_LONG, &timeslot_id, 0, &cb1);
						SQLBindCol(hStmt, 2, SQL_C_CHAR, start_time, sizeof(start_time), &cb2);
						SQLBindCol(hStmt, 3, SQL_C_CHAR, end_time, sizeof(end_time), &cb3);
						SQLBindCol(hStmt, 4, SQL_C_CHAR, is_available, sizeof(is_available), &cb4);
						SQLBindCol(hStmt, 5, SQL_C_LONG, &capacity, 0, &cb5);
						SQLBindCol(hStmt, 6, SQL_C_LONG, &service_id, 0, &cb6);

						result = _T("TimeSlot Information:\r\n");
						result += _T("-------------------------------\r\n");

						while (SQLFetch(hStmt) == SQL_SUCCESS) {

							result += _T("TimeSlot ID        : ");
							result.AppendFormat(_T("%d\r\n"), cb1 == SQL_NULL_DATA ? 0 : timeslot_id);

							result += _T("Service ID         : ");
							result.AppendFormat(_T("%d\r\n"), cb6 == SQL_NULL_DATA ? 0 : service_id);

							result += _T("Start Time         : ");
							result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)start_time);

							result += _T("End Time           : ");
							result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)end_time);

							result += _T("Capacity           : ");
							result.AppendFormat(_T("%d\r\n"), cb5 == SQL_NULL_DATA ? 0 : capacity);

							result += _T("Is Available       : ");
							result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)is_available);
							result += _T("-------------------------------\r\n");

						}


						result += _T("\r\n시작/종료 시간을 수정할 timeslot_id와 새로운 시작/종료 시간을 입력하세요(컴마로 공백없이 구분, 시간은 00:00:00 형식):\r\n");
					}
					else {
						result = _T("쿼리 실행 실패\n");
					}
				}

				else if (m_selectedOption == 3) {
					SELECT_ReservationByRes(hStmt, ret, (const char*)ascii, query, result);
					result += _T("\r\n인원을 수정할 예약의 id와 인원 수를 입력하세요.(컴마로 공백 없이)\r\n");
				}

				m_editField.SetWindowText(result);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 2;
				m_editInput.SetWindowText(_T(""));
			}
		}
		else if (m_selectStep == 2) {
			m_editInput.GetWindowText(input);
			input.Trim();
			CT2A ascii(input);

			CStringArray tokens;
			CString token;

			if (db_connect()) {
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


				if (m_selectedOption == 1) {
					int cur = 0;
					while (AfxExtractSubString(token, input, cur, ',')) {
						tokens.Add(token);
						cur++;
					}

					if (tokens.GetSize() != 2) {
						m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
						m_selectStep = 0;
						return;
					}

					sprintf_s(query, "UPDATE Service SET price = %s WHERE service_id = %s;", tokens[1], tokens[0]);
					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						result += _T("가격이 수정되었습니다.\r\n");
					}
					else {
						result += _T("수정 실패\r\n");

					}
				}

				else if (m_selectedOption == 2) {
					int cur = 0;
					while (AfxExtractSubString(token, input, cur, ',')) {
						tokens.Add(token);
						cur++;
					}

					if (tokens.GetSize() != 3) {
						m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
						return;
					}
					sprintf_s(query, "UPDATE TimeSlot SET start_time = '%s', end_time = '%s' WHERE timeslot_id = %s;", tokens[1], tokens[2], tokens[0]);
					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						result += _T("시작/종료 시간이 수정되었습니다.\r\n");
					}
					else {
						result += _T("수정 실패\r\n");

					}
				}
				else if (m_selectedOption == 3) {

					int cur = 0;
					while (AfxExtractSubString(token, input, cur, ',')) {
						tokens.Add(token);
						cur++;
					}

					if (tokens.GetSize() != 2) {
						m_editField.SetWindowText(_T("입력 형식이 올바르지 않습니다. 다시 시도하세요."));
						return;
					}


					sprintf_s(query, "UPDATE MakesReservation SET num_guest = %s WHERE reservation_id = %s;", tokens[1], tokens[0]);
					ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
						result += _T("예약 인원이 수정되었습니다.\r\n");
					}
					else {
						result += _T("수정 실패\r\n");

					}
				}

				m_editField.SetWindowText(result);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				db_disconnect();
				m_selectStep = 2;
				m_editInput.SetWindowText(_T(""));
			}
		}
		break;

	case 4: //CUSTOM
		if (m_selectStep == 0) {
			CT2A ascii(input);

			if (db_connect()) {
				SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
				sprintf_s(query, "%s", (const char*)ascii);

				ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
				if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
					result += _T("Query가 정상적으로 수행되었습니다.\r\n\r\n");
					SQLCloseCursor(hStmt);
					PrintAffectedTableData(input, result);
				}
				else {
					SQLCHAR sqlState[6], message[256];
					SQLINTEGER nativeError;
					SQLSMALLINT msgLen;

					SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &msgLen);

					result += _T("쿼리 수행 실패\n");
					result += _T("SQLSTATE: ") + CString((char*)sqlState) + _T("\n");
					result += _T("오류 메시지: ") + CString((char*)message) + _T("\n");

				}
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				m_editField.SetWindowText(result);
				m_editInput.SetWindowText(_T(""));
			}
			else {
				m_editField.SetWindowText(_T("DB 연결 실패."));
			}
		}
		break;
	default:
		break;
	}
}

void CDBMiniProject3MinhyeokChoiDlg::PrintAffectedTableData(const CString& inputSQL, CString& result)
{
	CString upper = inputSQL;
	upper.MakeUpper();

	CString tableName;
	if (upper.Find(_T("FROM ")) != -1) {
		int pos = upper.Find(_T("FROM ")) + 5;
		tableName = inputSQL.Mid(pos).SpanExcluding(_T(" ;\r\n"));
	}
	else if (upper.Find(_T("INTO ")) != -1) {
		int pos = upper.Find(_T("INTO ")) + 5;
		tableName = inputSQL.Mid(pos).SpanExcluding(_T(" ;\r\n"));
	}
	else if (upper.Find(_T("UPDATE ")) != -1) {
		int pos = upper.Find(_T("UPDATE ")) + 7;
		tableName = inputSQL.Mid(pos).SpanExcluding(_T(" ;\r\n"));
	}
	else if (upper.Find(_T("DELETE FROM ")) != -1) {
		int pos = upper.Find(_T("DELETE FROM ")) + 12;
		tableName = inputSQL.Mid(pos).SpanExcluding(_T(" ;\r\n"));
	}

	if (tableName.IsEmpty()) {
		result += _T("테이블명을 추출할 수 없습니다.\r\n");
		return;
	}


	CString selectQuery = _T("SELECT * FROM ") + tableName + _T(";");
	SQLHSTMT hStmt = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

	CT2A ascii(selectQuery);
	SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)(const char*)ascii, SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLSMALLINT colCount = 0;
		SQLNumResultCols(hStmt, &colCount);

		std::vector<CString> colNames;
		for (int i = 1; i <= colCount; ++i) {
			SQLCHAR colName[256];
			SQLSMALLINT nameLen, dataType, decimalDigits, nullable;
			SQLULEN colSize;

			SQLDescribeCol(hStmt, i, colName, sizeof(colName), &nameLen, &dataType, &colSize, &decimalDigits, &nullable);
			colNames.push_back(CString((char*)colName));
		}

		result += _T("[") + tableName + _T("] 테이블의 전체 데이터:\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			result += _T("--------------------------------------------------------------\r\n");

			for (int i = 1; i <= colCount; ++i) {
				char buf[256] = { 0 };
				SQLLEN indicator;
				SQLGetData(hStmt, i, SQL_C_CHAR, buf, sizeof(buf), &indicator);

				CString colLabel = colNames[i - 1];
				colLabel.AppendFormat(_T("%*s"), 20 - colLabel.GetLength(), _T(""));
				result += colLabel + _T(": ") + CString(buf) + _T("\r\n");
			}
		}
	}
	else {
		SQLCHAR sqlState[6], message[256];
		SQLINTEGER nativeError;
		SQLSMALLINT msgLen;

		SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &msgLen);

		result += _T("데이터 조회 실패\n");
		result += _T("SQLSTATE: ") + CString((char*)sqlState) + _T("\n");
		result += _T("오류 메시지: ") + CString((char*)message) + _T("\n");
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}




void CDBMiniProject3MinhyeokChoiDlg::SELECT_ReservationByRes(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	sprintf_s(query, 512,
		"SELECT R.client_id, M.reservation_date, R.reservation_id, C.name, S.service_name, "
		"T.start_time, T.end_time, M.num_guest, R.status "
		"FROM Reservation R, TimeSlot T, Service S, MakesReservation M, Client C "
		"WHERE R.client_id = %s AND R.reservation_id = M.reservation_id AND "
		"M.service_id = S.service_id AND M.timeslot_id = T.timeslot_id AND C.resident_number = R.client_id;",
		inputAscii);

	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		SQLCHAR sqlState[6] = { 0 };
		SQLCHAR message[SQL_MAX_MESSAGE_LENGTH] = { 0 };
		SQLINTEGER nativeError = 0;
		SQLSMALLINT messageLength = 0;

		if (SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &messageLength) == SQL_SUCCESS) {
			result.Format(_T("서비스 수행 실패\nSQLState: %S\nError: %d\nMessage: %S"),
				sqlState, nativeError, message);
		}
		else {
			result = _T("서비스 수행 실패 (상세 오류 정보 없음)");
			result += _T(query);
		}
		return;
	}

	SQLCHAR client_id[20], reservation_date[20], reservation_id[20], client_name[100];
	SQLCHAR service_name[100], start_time[50], end_time[50], num_guest[10], status[20];
	SQLLEN cb1, cb2, cb3, cb4, cb5, cb6, cb7, cb8, cb9;
	SQLBindCol(hStmt, 1, SQL_C_CHAR, client_id, sizeof(client_id), &cb1);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, reservation_date, sizeof(reservation_date), &cb2);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, reservation_id, sizeof(reservation_id), &cb3);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, client_name, sizeof(client_name), &cb4);
	SQLBindCol(hStmt, 5, SQL_C_CHAR, service_name, sizeof(service_name), &cb5);
	SQLBindCol(hStmt, 6, SQL_C_CHAR, start_time, sizeof(start_time), &cb6);
	SQLBindCol(hStmt, 7, SQL_C_CHAR, end_time, sizeof(end_time), &cb7);
	SQLBindCol(hStmt, 8, SQL_C_CHAR, num_guest, sizeof(num_guest), &cb8);
	SQLBindCol(hStmt, 9, SQL_C_CHAR, status, sizeof(status), &cb9);

	result = _T("예약 목록:\r\n");
	result += _T("-------------------------------\r\n");

	while (SQLFetch(hStmt) == SQL_SUCCESS) {

		result += _T("Reservation Date  : ");
		result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_date);

		result += _T("Reservation ID    : ");
		result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_id);

		result += _T("Client ID         : ");
		result.AppendFormat(_T("%s\r\n"), cb1 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)client_id);

		result += _T("Client Name       : ");
		result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)client_name);

		result += _T("Service Name      : ");
		result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

		result += _T("Start Time        : ");
		result.AppendFormat(_T("%s\r\n"), cb6 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)start_time);

		result += _T("End Time          : ");
		result.AppendFormat(_T("%s\r\n"), cb7 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)end_time);

		result += _T("Number of Guests  : ");
		result.AppendFormat(_T("%s\r\n"), cb8 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)num_guest);

		result += _T("Status            : ");
		result.AppendFormat(_T("%s\r\n"), cb9 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)status);
		result += _T("-------------------------------\r\n");

	}
}




void CDBMiniProject3MinhyeokChoiDlg::SELECT_ReservationByDate(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	sprintf_s(query, 512,
		"SELECT M.reservation_date, M.reservation_id, S.service_name, T.start_time, T.end_time, M.num_guest, R.status "
		"FROM Reservation R, MakesReservation M, Service S, TimeSlot T "
		"WHERE M.reservation_date = '%s' AND M.reservation_id = R.reservation_id AND "
		"M.service_id = S.service_id AND M.timeslot_id = T.timeslot_id;",
		inputAscii);

	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		result = _T("쿼리 수행 실패\n");
		return;
	}

	SQLCHAR reservation_date[20], reservation_id[20], service_name[100];
	SQLCHAR start_time[50], end_time[50], num_guest[10], status[20];
	SQLLEN cb1, cb2, cb3, cb4, cb5, cb6, cb7;
	SQLBindCol(hStmt, 1, SQL_C_CHAR, reservation_date, sizeof(reservation_date), &cb1);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, reservation_id, sizeof(reservation_id), &cb2);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, service_name, sizeof(service_name), &cb3);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, start_time, sizeof(start_time), &cb4);
	SQLBindCol(hStmt, 5, SQL_C_CHAR, end_time, sizeof(end_time), &cb5);
	SQLBindCol(hStmt, 6, SQL_C_CHAR, num_guest, sizeof(num_guest), &cb6);
	SQLBindCol(hStmt, 7, SQL_C_CHAR, status, sizeof(status), &cb7);

	result = _T("날짜별 예약 조회:\r\n");
	result += _T("-------------------------------\r\n");
	while (SQLFetch(hStmt) == SQL_SUCCESS) {
		result += _T("Reservation Date  : ");
		result.AppendFormat(_T("%s\r\n"), cb1 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_date);

		result += _T("Reservation ID    : ");
		result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_id);

		result += _T("Service Name      : ");
		result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

		result += _T("Start Time        : ");
		result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)start_time);

		result += _T("End Time          : ");
		result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)end_time);

		result += _T("Number of Guests  : ");
		result.AppendFormat(_T("%s\r\n"), cb6 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)num_guest);

		result += _T("Status            : ");
		result.AppendFormat(_T("%s\r\n"), cb7 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)status);
		result += _T("-------------------------------\r\n");
	}

}

void CDBMiniProject3MinhyeokChoiDlg::SELECT_ServiceByPro(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	sprintf_s(query, 512,
		"SELECT P.provider_id, S.service_id, S.service_name, S.price "
		"FROM Provider P, Service S "
		"WHERE P.provider_id = %s AND P.provider_id = S.provider_id;",
		inputAscii);

	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLINTEGER provider_id, service_id;
		SQLCHAR service_name[100], price[20];
		SQLLEN cb1, cb2, cb3, cb4;

		SQLBindCol(hStmt, 1, SQL_C_LONG, &provider_id, 0, &cb1);
		SQLBindCol(hStmt, 2, SQL_C_LONG, &service_id, 0, &cb2);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, service_name, sizeof(service_name), &cb3);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, price, sizeof(price), &cb4);

		result = _T("제공 서비스 목록:\r\n");
		result += _T("-------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {

			result += _T("Provider ID      : ");
			result.AppendFormat(_T("%d\r\n"), cb1 == SQL_NULL_DATA ? 0 : provider_id);

			result += _T("Service ID       : ");
			result.AppendFormat(_T("%d\r\n"), cb2 == SQL_NULL_DATA ? 0 : service_id);

			result += _T("Service Name     : ");
			result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

			result += _T("Price            : ");
			result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)price);
			result += _T("-------------------------------\r\n");
		}

	}
	else {
		result = _T("쿼리 실행 실패\n");
	}
}


void CDBMiniProject3MinhyeokChoiDlg::SELECT_TimeSlotByS_id(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	sprintf_s(query, 512,
		"SELECT T.service_id, S.service_name, T.timeslot_id, T.start_time, T.end_time, T.is_available, T.capacity "
		"FROM TimeSlot T, Service S "
		"WHERE T.service_id = %s AND T.service_id = S.service_id;",
		inputAscii);


	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLINTEGER service_id, timeslot_id, is_available, capacity;
		SQLCHAR service_name[100], start_time[50], end_time[50];
		SQLLEN cb1, cb2, cb3, cb4, cb5, cb6, cb7;

		SQLBindCol(hStmt, 1, SQL_C_LONG, &service_id, 0, &cb1);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, service_name, sizeof(service_name), &cb2);
		SQLBindCol(hStmt, 3, SQL_C_LONG, &timeslot_id, 0, &cb3);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, start_time, sizeof(start_time), &cb4);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, end_time, sizeof(end_time), &cb5);
		SQLBindCol(hStmt, 6, SQL_C_LONG, &is_available, 0, &cb6);
		SQLBindCol(hStmt, 7, SQL_C_LONG, &capacity, 0, &cb7);

		result = _T("해당 서비스의 타임 슬롯 목록:\r\n");
		result += _T("-------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			result += _T("Service ID       : ");
			result.AppendFormat(_T("%d\r\n"), cb1 == SQL_NULL_DATA ? 0 : service_id);

			result += _T("Service Name     : ");
			result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

			result += _T("Timeslot ID      : ");
			result.AppendFormat(_T("%d\r\n"), cb3 == SQL_NULL_DATA ? 0 : timeslot_id);

			result += _T("Start Time       : ");
			result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)start_time);

			result += _T("End Time         : ");
			result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)end_time);

			result += _T("Is Available     : ");
			result.AppendFormat(_T("%s\r\n"), cb6 == SQL_NULL_DATA ? _T("No") : (is_available ? _T("Yes") : _T("No")));

			result += _T("Capacity         : ");
			result.AppendFormat(_T("%d\r\n"), cb7 == SQL_NULL_DATA ? 0 : capacity);

			result += _T("-------------------------------\r\n");
		}



	}
	else {
		result = _T("쿼리 실행 실패\n");
	}

}



void CDBMiniProject3MinhyeokChoiDlg::SELECT_ReservationByPro(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	sprintf_s(query, 512,
		"SELECT R.client_id, M.service_id, M.reservation_id, M.timeslot_id, M.reservation_date, R.status "
		"FROM Service S, MakesReservation M, Reservation R "
		"WHERE S.provider_id = %s AND M.service_id = S.service_id AND M.reservation_id = R.reservation_id",
		inputAscii);

	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLCHAR client_id[100], reservation_id[100], reservation_date[100], status[100];
		SQLINTEGER service_id, timeslot_id;
		SQLLEN cb1, cb2, cb3, cb4, cb5, cb6;

		SQLBindCol(hStmt, 1, SQL_C_CHAR, client_id, sizeof(client_id), &cb1);
		SQLBindCol(hStmt, 2, SQL_C_LONG, &service_id, 0, &cb2);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, reservation_id, sizeof(reservation_id), &cb3);
		SQLBindCol(hStmt, 4, SQL_C_LONG, &timeslot_id, 0, &cb4);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, reservation_date, sizeof(reservation_date), &cb5);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, status, sizeof(status), &cb6);

		result.Format(_T("[Provider ID = %S] 예약 목록 :\r\n"), inputAscii);
		result += _T("-------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {

			result += _T("Client ID         : ");
			result.AppendFormat(_T("%s\r\n"), cb1 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)client_id);

			result += _T("Service ID        : ");
			result.AppendFormat(_T("%d\r\n"), cb2 == SQL_NULL_DATA ? 0 : service_id);

			result += _T("Reservation ID    : ");
			result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_id);

			result += _T("Timeslot ID       : ");
			result.AppendFormat(_T("%d\r\n"), cb4 == SQL_NULL_DATA ? 0 : timeslot_id);

			result += _T("Reservation Date  : ");
			result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)reservation_date);

			result += _T("Status            : ");
			result.AppendFormat(_T("%s\r\n"), cb6 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)status);
			result += _T("-------------------------------\r\n");
		}
	}
	else {
		result = _T("쿼리 실행 실패\n");
	}

}


void CDBMiniProject3MinhyeokChoiDlg::SELECT_AllProvider(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	SQLCHAR exponent[100], email[100], phone[20], business_type[50], business_name[100];
	SQLINTEGER provider_id;
	SQLLEN cb1, cb2, cb3, cb4, cb5, cb6;

	sprintf_s(query, 512, "SELECT * FROM Provider");
	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

		SQLBindCol(hStmt, 1, SQL_C_LONG, &provider_id, 0, &cb1);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, exponent, sizeof(exponent), &cb2);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, email, sizeof(email), &cb3);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, phone, sizeof(phone), &cb4);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, business_type, sizeof(business_type), &cb5);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, business_name, sizeof(business_name), &cb6);

		result = _T("사업자 정보:\r\n");
		result += _T("--------------------------------------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			result += _T("Provider ID       : ");
			result.AppendFormat(_T("%d\r\n"), provider_id);

			result += _T("Business Name     : ");
			result.AppendFormat(_T("%s\r\n"), cb6 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)business_name);

			result += _T("Business Type     : ");
			result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)business_type);

			result += _T("Representative    : ");
			result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)exponent);

			result += _T("Email             : ");
			result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)email);

			result += _T("Phone             : ");
			result.AppendFormat(_T("%s\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)phone);
			result += _T("--------------------------------------------------------------\r\n");
		}

	}
	else {
		result = _T("쿼리 실행 실패");
	}
}


void CDBMiniProject3MinhyeokChoiDlg::SELECT_AllService(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	SQLCHAR service_name[50], description[50], service_type[50];
	SQLINTEGER service_id, price;
	SQLLEN cb1, cb2, cb3, cb4, cb5;

	sprintf_s(query, 512, "SELECT * FROM Service;");
	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

		SQLBindCol(hStmt, 1, SQL_C_LONG, &service_id, 0, &cb1);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, service_name, sizeof(service_name), &cb2);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, description, sizeof(description), &cb3);
		SQLBindCol(hStmt, 4, SQL_C_LONG, &price, 0, &cb4);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, service_type, sizeof(service_type), &cb5);

		result = _T("서비스 정보:\r\n");
		result += _T("--------------------------------------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			result += _T("Service ID        : ");
			result.AppendFormat(_T("%d\r\n"), service_id);

			result += _T("Service Name      : ");
			result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_name);

			result += _T("description       : ");
			result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)description);

			result += _T("Service Type      : ");
			result.AppendFormat(_T("%s\r\n"), cb5 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)service_type);

			result += _T("price             : ");
			result.AppendFormat(_T("%d\r\n"), cb4 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)price);
			result += _T("--------------------------------------------------------------\r\n");
		}

	}
	else {
		result = _T("쿼리 실행 실패\r\n");
		result += _T(query);
	}
}

void CDBMiniProject3MinhyeokChoiDlg::SELECT_ClientByRes(
	SQLHSTMT hStmt,
	SQLRETURN& ret,
	const char* inputAscii,
	char* query,
	CString& result)
{
	SQLCHAR name[100], email[100], phone[20];
	SQLINTEGER age;
	SQLLEN cb1, cb2, cb3, cb4;

	sprintf_s(query, 512,
		"SELECT C.name, C.email, C.phone_number, C.age FROM Client C WHERE resident_number = %s;",
		inputAscii);

	ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
	
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

		SQLBindCol(hStmt, 1, SQL_C_CHAR, name, sizeof(name), &cb1);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, email, sizeof(email), &cb2);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, phone, sizeof(phone), &cb3);
		SQLBindCol(hStmt, 4, SQL_C_LONG, &age, 0, &cb4);

		CString providerIdStr(inputAscii);
		result.Format(_T("[Provider ID = %s] 개인 정보 :\r\n"), providerIdStr);
		result += _T("--------------------------------------------------------------\r\n");

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			result += _T("Name              : ");
			result.AppendFormat(_T("%s\r\n"), cb1 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)name);

			result += _T("Email             : ");
			result.AppendFormat(_T("%s\r\n"), cb2 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)email);

			result += _T("Phone             : ");
			result.AppendFormat(_T("%s\r\n"), cb3 == SQL_NULL_DATA ? _T("(null)") : (TCHAR*)phone);

			result += _T("Age               : ");
			result.AppendFormat(_T("%d\r\n"), cb4 == SQL_NULL_DATA ? 0 : age);

			result += _T("--------------------------------------------------------------\r\n");
		}

	}
	else {
		result = _T("쿼리 실행 실패");
	}
	
}
