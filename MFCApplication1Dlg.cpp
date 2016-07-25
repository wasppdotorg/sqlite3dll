
void CMFCApplication1Dlg::OnBnClickedBnStart()
{
	// TODO: Add your control notification handler code here
	BOOL bFileExits = CFileFind().FindFile(_T("sqlite3.db"));
	if (bFileExits)
	{
		CFile::Remove(_T("sqlite3.db"));
	}

	CString strText;

	sqlite3* pSQLite3 = NULL;
	sqlite3_stmt* pSQLite3Stmt = NULL;

	LPCTSTR db = _T("sqlite3.db");
	int result = sqlite3_open16(db, &pSQLite3);
	if (result != SQLITE_OK)
	{
		//sqlite3_errcode(sqlite3_)
		MessageBox((LPCTSTR)sqlite3_errmsg(pSQLite3));
		return;
	}

	LPCTSTR query = _T("drop table test");
	result = sqlite3_prepare16(pSQLite3, query, -1, &pSQLite3Stmt, NULL);
	if (result == SQLITE_OK)
	{
		sqlite3_step(pSQLite3Stmt);
	}
	sqlite3_finalize(pSQLite3Stmt);

	query = _T("create table test(test1 INT, test2 BIGINT, test3 DOUBLE, test4 VARCHAR(10), test5 VARCHAR(50), test6 VARCHAR(255), test7 TEXT, test8 DATETIME)");
	result = sqlite3_prepare16(pSQLite3, query, -1, &pSQLite3Stmt, NULL);
	if (result == SQLITE_OK)
	{
		sqlite3_step(pSQLite3Stmt);
	}
	sqlite3_finalize(pSQLite3Stmt);

	query = _T("insert into test values(?, ?, ?, ?, ?, ?, ?, ?)");
	result = sqlite3_prepare16(pSQLite3, query, -1, &pSQLite3Stmt, NULL);
	if (result == SQLITE_OK)
	{
		int bind_index = 0;
		//{
		sqlite3_bind_int(pSQLite3Stmt, ++bind_index, 1);
		sqlite3_bind_int64(pSQLite3Stmt, ++bind_index, 2);
		sqlite3_bind_double(pSQLite3Stmt, ++bind_index, 3.1f);
		sqlite3_bind_text16(pSQLite3Stmt, ++bind_index, _T("4"), -1, NULL);
		sqlite3_bind_text16(pSQLite3Stmt, ++bind_index, _T("5"), -1, NULL);
		sqlite3_bind_text16(pSQLite3Stmt, ++bind_index, _T("6"), -1, NULL);
		sqlite3_bind_text16(pSQLite3Stmt, ++bind_index, _T("한글"), -1, NULL);
		sqlite3_bind_text16(pSQLite3Stmt, ++bind_index, _T("1970-01-01 00:00:00"), -1, NULL);
		//}

		sqlite3_step(pSQLite3Stmt);
	}
	sqlite3_finalize(pSQLite3Stmt);

	query = _T("select * from test");
	result = sqlite3_prepare16(pSQLite3, query, -1, &pSQLite3Stmt, NULL);
	if (result == SQLITE_OK)
	{
		int column_count = sqlite3_column_count(pSQLite3Stmt);

		while (sqlite3_step(pSQLite3Stmt) == SQLITE_ROW)
		{
			for (int i = 0; i < column_count; ++i)
			{
				MessageBox((LPCTSTR)sqlite3_column_name16(pSQLite3Stmt, i));

				if (sqlite3_column_type(pSQLite3Stmt, i) == SQLITE_INTEGER)
				{
					strText.Format(_T("%d"), sqlite3_column_int64(pSQLite3Stmt, i));
					MessageBox(strText);
				}
				else if (sqlite3_column_type(pSQLite3Stmt, i) == SQLITE_FLOAT)
				{
					strText.Format(_T("%f"), sqlite3_column_double(pSQLite3Stmt, i));
					MessageBox(strText);
				}
				else if (sqlite3_column_type(pSQLite3Stmt, i) == SQLITE3_TEXT)
				{
					MessageBox((LPCTSTR)sqlite3_column_text16(pSQLite3Stmt, i));
				}
			}
		}
	}
	sqlite3_finalize(pSQLite3Stmt);
	sqlite3_close(pSQLite3);

	MessageBox(_T("끝"));
}

