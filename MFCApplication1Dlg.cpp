
void CMFCApplication1Dlg::OnBnClickedBnStop()
{
	// TODO: Add your control notification handler code here
	BOOL bFileExits = CFileFind().FindFile(_T("sqlite3.db"));
	if (bFileExits)
	{
		CFile::Remove(_T("sqlite3.db"));
	}

	CString strText;

	sqlite3* sqlite3_ = NULL;
	sqlite3_stmt* stmt_ = NULL;

	LPCTSTR db = _T("sqlite3.db");
	int result = sqlite3_open16(db, &sqlite3_);
	if (result != SQLITE_OK)
	{
		//sqlite3_errcode(sqlite3_)
		MessageBox((LPCTSTR)sqlite3_errmsg(sqlite3_));
		return;
	}

	LPCTSTR query = _T("drop table test");
	result = sqlite3_prepare16(sqlite3_, query, -1, &stmt_, NULL);
	if (result == SQLITE_OK)
	{
		sqlite3_step(stmt_);
	}
	sqlite3_finalize(stmt_);

	query = _T("create table test(test1 INT, test2 BIGINT, test3 DOUBLE, test4 VARCHAR(10), test5 VARCHAR(50), test6 VARCHAR(255), test7 TEXT, test8 DATETIME)");
	result = sqlite3_prepare16(sqlite3_, query, -1, &stmt_, NULL);
	if (result == SQLITE_OK)
	{
		sqlite3_step(stmt_);
	}
	sqlite3_finalize(stmt_);

	query = _T("insert into test values(?, ?, ?, ?, ?, ?, ?, ?)");
	result = sqlite3_prepare16(sqlite3_, query, -1, &stmt_, NULL);
	if (result == SQLITE_OK)
	{
		int bind_index = 0;
		//{
		sqlite3_bind_int(stmt_, ++bind_index, 1);
		sqlite3_bind_int64(stmt_, ++bind_index, 2);
		sqlite3_bind_double(stmt_, ++bind_index, 3.1f);
		sqlite3_bind_text16(stmt_, ++bind_index, _T("4"), -1, NULL);
		sqlite3_bind_text16(stmt_, ++bind_index, _T("5"), -1, NULL);
		sqlite3_bind_text16(stmt_, ++bind_index, _T("6"), -1, NULL);
		sqlite3_bind_text16(stmt_, ++bind_index, _T("한글"), -1, NULL);
		sqlite3_bind_text16(stmt_, ++bind_index, _T("1970-01-01 00:00:00"), -1, NULL);
		//}

		sqlite3_step(stmt_);
	}
	sqlite3_finalize(stmt_);

	query = _T("select * from test");
	result = sqlite3_prepare16(sqlite3_, query, -1, &stmt_, NULL);
	if (result == SQLITE_OK)
	{
		int column_count = sqlite3_column_count(stmt_);

		while (sqlite3_step(stmt_) == SQLITE_ROW)
		{
			for (int i = 0; i < column_count; ++i)
			{
				MessageBox((LPCTSTR)sqlite3_column_name16(stmt_, i));

				if (sqlite3_column_type(stmt_, i) == SQLITE_INTEGER)
				{
					strText.Format(_T("%d"), sqlite3_column_int64(stmt_, i));
					MessageBox(strText);
				}
				else if (sqlite3_column_type(stmt_, i) == SQLITE_FLOAT)
				{
					strText.Format(_T("%f"), sqlite3_column_double(stmt_, i));
					MessageBox(strText);
				}
				else if (sqlite3_column_type(stmt_, i) == SQLITE3_TEXT)
				{
					MessageBox((LPCTSTR)sqlite3_column_text16(stmt_, i));
				}
			}
		}
	}
	sqlite3_finalize(stmt_);
	sqlite3_close(sqlite3_);

	MessageBox(_T("끝"));
}

