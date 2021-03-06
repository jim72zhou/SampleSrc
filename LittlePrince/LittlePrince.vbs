Option Explicit

'+++++++++ System Settings +++++++++++++++++++++++++++++++++++++++++++++++++++++
'DEBUG Flag
Const SYS_DEBUG		= True
'CSV输出格式，是否带引号
Const CSV_FMT1		= """"

'++++++++++ Script Start +++++++++++++++++++++++++++++++++++++++++++++++++++++++
'Main函数
Call Main()
'++++++++++ Script End +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

'@==============================================================================
''機能: メイン関数
'@==============================================================================
Sub Main()

	Dim objArgs, fileName, sheetName, csvFile
	If SYS_DEBUG Then
		fileName = "D:\Temp\Prince\2019暑假团.xlsx"
		sheetName = "物理数学化学"
		csvFile = "D:\Temp\Prince\Course_2019.csv"
	Else
		Set objArgs = WScript. Arguments
		If objArgs.Count <> 3 Then
			Call MsgBox("用法:" & vbNewLine & "LittlePrince.vbs excelFile dataSheet csvFile", vbOKOnly + vbInformation, "小王子加油站")
			Exit Sub
		End If
	
		fileName = objArgs(0)
		sheetName = objArgs(1)
		csvFile = objArgs(2)
	End If

	Dim arrData
	If Not ReadExcelFileData(fileName, sheetName, arrData) Then
		Exit Sub
	End If

	Dim charset : charset = "UTF-8"
	If WriteTextFile(csvFile, charset, arrData) Then
		Call MsgBox(csvFile & "生成成功！", vbOKOnly + vbInformation, "小王子加油站")
	Else
		Call MsgBox(csvFile & "保存失败！", vbOKOnly + vbInformation, "小王子加油站")
	End If

End Sub

'@==========================================================================
''機能:Excel文件读取
'@==========================================================================
Private Function ReadExcelFileData(ByVal excelFile, ByVal sheetName, ByRef arrData)

	ReadExcelFileData = False

	Dim oExcelKit : Set oExcelKit = New CExcelKit
	If Not oExcelKit.OpenFile(excelFile) Then
		Call MsgBox(excelFile & "打开失败！", vbOKOnly + vbInformation, "小王子加油站")
		Exit Function
	End If

	'课程信息的读取
	Dim oDicCourse : Set oDicCourse = CreateObject("Scripting.Dictionary")
	Call ReadCoureInfo(oExcelKit, oDicCourse)

	oExcelKit.SetActiveSheet(sheetName)
	Dim oSheet : Set oSheet = oExcelKit.GetActiveSheet

	'D列~Z列的学科信息的读取
	Dim iColSubjectFrom : iColSubjectFrom = 4
	Dim iColSubjectTo : iColSubjectTo = 26
	Dim oArrSubject : Set oArrSubject = New CArrayList
	Dim arrSubject
	For iCol = iColSubjectFrom To iColSubjectTo
		subject = oExcelKit.NullStrGuard(oSheet.Cells(1, iCol).Value)
		If Len(subject) > 0 Then
			oArrSubject.Add(subject)
		Else
			'空列也可以
			oArrSubject.Add(subject)
			'iColSubjectTo = iCol
			'Exit For
		End If
	Next
	arrSubject = oArrSubject.ToArray

	Dim oArrData : Set oArrData = New CArrayList
	'标题信息
	oArrData.Add("grade,subject,student,schedule,place")
	Dim grade, subject, student, courseInfo
	Dim courseKey, courseLine
	grade = "高三"

	Dim maxRow, iRow, iCol, iKeyCol
	maxRow = oSheet.UsedRange.Rows.Count
	'开始行设定
	iRow = 2
	'姓名列
	iKeyCol = 2
	Do While iRow <= maxRow
		'姓名
		student = oExcelKit.NullStrGuard(oSheet.Cells(iRow, iKeyCol).Value)

		'姓名连续三行空的话认为数据结束
		If Len(student) = 0 Then
			If iRow < maxRow Then
				If Len(oExcelKit.NullStrGuard(oSheet.Cells(iRow + 1, iKeyCol).Value)) = 0 Then
					If iRow + 1 < maxRow And Len(oExcelKit.NullStrGuard(oSheet.Cells(iRow + 2, iKeyCol).Value)) = 0 Then
						Exit Do
					End If
				End If
			Else
				Exit Do
			End If
		End If

		'E列~Z列的学科信息的读取
		For iCol = iColSubjectFrom To iColSubjectTo
			subject = oExcelKit.NullStrGuard(oSheet.Cells(iRow, iCol).Value)
			If Len(subject) > 0 Then
				subject = arrSubject(iCol - iColSubjectFrom)
				courseKey = CSV_FMT1 & grade & CSV_FMT1 & "," & CSV_FMT1 & subject & CSV_FMT1
				If oDicCourse.Exists(courseKey) Then
					courseInfo = oDicCourse.Item(courseKey)
					courseLine = courseKey & "," & CSV_FMT1 & student & CSV_FMT1 & "," & courseInfo
					oArrData.Add(courseLine)
				Else
					Call MsgBox(courseKey & "的课程信息没有！", vbOKOnly + vbInformation, "小王子加油站")
					Exit Function
				End If
			End If
		Next

		'次の行に移動
		iRow = iRow + 1
	Loop

	arrData = oArrData.ToArray

	'关闭Excel文件
	If Not oExcelKit.Close(False) Then
		Call MsgBox("Close Error!", vbOKOnly + vbInformation, "小王子加油站")
	End If

	Set oExcelKit = Nothing
	Set oSheet = Nothing
	Set oArrData = Nothing
	Set oDicCourse = Nothing

	ReadExcelFileData = True

End Function

'@==========================================================================
''機能:课程信息的读取
'@==========================================================================
Private Sub ReadCoureInfo(ByRef oExcelKit, ByRef oDicCourse)

	Dim sheetName : sheetName = "课程信息"
	oExcelKit.SetActiveSheet(sheetName)
	Dim oSheet : Set oSheet = oExcelKit.GetActiveSheet

	Dim maxRow, iRow
	Dim grade, subject, schedule, place, courseKey
	maxRow = oSheet.UsedRange.Rows.Count

	'开始行设定
	iRow = 3
	Do While iRow <= maxRow
		'年级
		grade = oExcelKit.NullStrGuard(oSheet.Cells(iRow, 1).Value)
		'年级空的话认为数据结束
		If Len(grade) = 0 Then
			Exit Do
		End If

		'学科
		subject = oExcelKit.NullStrGuard(oSheet.Cells(iRow, 2).Value)
		'上课时间
		schedule = oExcelKit.NullStrGuard(oSheet.Cells(iRow, 3).Value)
		'上课地点
		place = oExcelKit.NullStrGuard(oSheet.Cells(iRow, 4).Value)
		courseKey = CSV_FMT1 & grade & CSV_FMT1 & "," & CSV_FMT1 & subject & CSV_FMT1

		If oDicCourse.Exists(courseKey) Then
			Call MsgBox(courseKey & "的课程信息重复了，请确认！", vbOKOnly + vbInformation, "小王子加油站")
		Else
			Call oDicCourse.Add(courseKey, CSV_FMT1 & schedule & CSV_FMT1 & "," & CSV_FMT1 & place & CSV_FMT1)
		End If

		'次の行に移動
		iRow = iRow + 1
	Loop

	Set oSheet = Nothing

End Sub

'@==========================================================================
''機能: テキストファイルに書き込み
''@param fileName アスキーファイルパス名
''@param charset 文字コード("UTF-16"/"Shift_JIS"/"UTF-8")
''@param contents 出力文字列
''@return True(正常) / False(エラー)
'@==========================================================================
Function WriteTextFile(ByVal fileName, ByVal charset, ByRef contents)

	Dim oStream
	Dim txt

	'ストリームオブジェクトを生成
	Set oStream = CreateObject("ADODB.Stream")
	'ファイルタイプセット(1:バイナリデータ 2:テキストデータ)
	oStream.Type = 2
	'文字コードセット
	oStream.Charset = charset

	'エラー対応
	On Error Resume Next
	'オープン
	oStream.Open

	'ファイルに新規行として書き込む
	If IsArray(contents) Then
		For Each txt In contents
			oStream.WriteText txt, 1
		Next
	Else
		oStream.WriteText contents, 1
	End If

	'出力ファイル生成(上書き保存)
	oStream.SaveToFile fileName, 2
	oStream.Close
	Set oStream = Nothing

	'エラー発生時
	If(Err.Number <> 0) Then
		WriteTextFile = False
		Exit Function
	End If
	On Error Goto 0

	WriteTextFile = True

End Function

'@******************************************************************************
''Class: 擬似動的配列クラス
''System.Collections.ArrayListが.Net4.5でサポートしないので、CArrayListを作成しました
'@******************************************************************************
Class CArrayList

	Private m_arrayList

	Private Sub Class_Initialize()
		m_arrayList = Array()
	End Sub

	Private Sub Class_Terminate()
	End Sub

	Public Sub Add(arg)
		Dim max
		max = UBound(m_arrayList)
		ReDim Preserve m_arrayList(max+1)
		Select Case VarType(arg)
			Case vbObject
				Set m_arrayList(max+1) = arg
			Case Else
				m_arrayList(max+1) = arg
		End select
	End Sub

	Public Property Get Item(num)
		Select Case VarType(m_arrayList(num))
			Case vbObject
				Set Item = m_arrayList(num)
			Case Else
				Item = m_arrayList(num)
		End Select
	End Property

	Public Property Let Item(num, value)
		Select Case VarType(value)
			Case vbObject
				Set m_arrayList(num) = value
			Case Else
				m_arrayList(num) = value
		End Select
	End Property

	Public Function Contains(key)
		Contains = False
		Dim i
		For i=0 To UBound(m_arrayList)
			Select Case VarType(key)
				Case vbObject
					If m_arrayList(i) Is key Then
						Contains = True
						Exit For
					End If
				Case Else
					If m_arrayList(i) = key Then
						Contains = True
						Exit For
					End If
			End Select
		Next
	End Function

	''String型の場合のみソート
	Public Sub Sort()
		Call SortBubble(m_arrayList)
	End Sub

	''バブルソート
	Private Sub SortBubble(ByRef refArray)
		Dim i, j
		For i = 0 To UBound(refArray) - 1
			For j = i + 1 To UBound(refArray)
				If IsObject(refArray(j)) Or IsObject(refArray(i)) Then
					If refArray(j).CompareTo(refArray(i)) < 0 Then 
						Call Swap(refArray(i), refArray(j))
					End If 
				ElseIf IsArray(refArray(j)) Or IsArray(refArray(i)) Then
				Else
					If refArray(j) < refArray(i) Then
						Call swap(refArray(i), refArray(j))
					End If
				End If
			Next
		Next
	End Sub

	''配列要素交換用メソッド
	Private Sub Swap(ByRef x, ByRef y)
		Dim d
		If IsObject(x) Then
			Set d = x
		Else
			d = x
		End If
		If IsObject(y) Then
			Set x = y
		Else
			x = y
		End If
		If IsObject(d) Then
			Set y = d
		Else
			y = d
		End If
	End Sub

	Public Function Count()
		Count = UBound(m_arrayList)+1
	End Function

	Public Function List()
		List = m_arrayList
	End Function

	Public Function ToArray()
		ToArray = m_arrayList
	End Function

	Public Sub Clear()
		Erase m_arrayList
		ReDim m_arrayList(-1)
	End Sub

End Class

'@******************************************************************************
''Class: Excelデータ処理キットクラス
'@******************************************************************************
Class CExcelKit

	Private m_oApp				'Excel App
	Private m_oWorkBook			'Excel WorkBook
	Private m_bSaveClose		'クローズの時、ファイルを保存するか？

	Private Sub Class_Initialize()
		Set m_oApp = CreateObject("Excel.Application")
		If SYS_DEBUG Then
			m_oApp.Visible = True
		End If
		Set m_oWorkBook = Nothing
		m_bSaveClose = False
	End Sub

	Private Sub Class_Terminate()

		On Error Resume Next
		If Not Nothing Is m_oWorkBook Then
			Call m_oWorkBook.Close(m_bSaveClose)
			Set m_oWorkBook = Nothing
		End IF
		m_oApp.Quit
		Set m_oApp = Nothing
		On Error Goto 0

	End Sub

	'@==========================================================================
	''機能: 新規Excelファイルを作成
	''@param fileName Excelファイル名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function NewFile(ByVal fileName)

		On Error Resume Next
		Set m_oWorkBook = m_oApp.WorkBooks.Add
		m_oWorkBook.SaveAs(fileName)
		If Err.Number <> 0 Then
			'読み取りできない場合
			NewFile = False
			Exit Function
		End If
		On Error Goto 0

		NewFile = True

	End Function

	'@==========================================================================
	''機能: 新規ワークブックを作成
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function CreateWorkBook()

		On Error Resume Next
		Set m_oWorkBook = m_oApp.WorkBooks.Add
		If Err.Number <> 0 Then
			'作成できない場合
			CreateWorkBook = False
			Exit Function
		End If
		On Error Goto 0

		CreateWorkBook = True

	End Function

	'@==========================================================================
	''機能: Excelファイルをオープン
	''@param fileName Excelファイル名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function OpenFile(ByVal fileName)

		On Error Resume Next
		Set m_oWorkBook = m_oApp.WorkBooks.Open(fileName)
		If Err.Number <> 0 Then
			'読み取りできない場合
			OpenFile = False
			Exit Function
		End If
		On Error Goto 0

		OpenFile = True

	End Function

	'@==========================================================================
	''機能: Excelワークブックを取得
	''@return ワークブック
	'@==========================================================================
	Public Function GetWookBook()
		Set GetWookBook = m_oWorkBook
	End Function

	'@==========================================================================
	''機能: Excelアクティブシートを取得
	''@return アクティプシート
	'@==========================================================================
	Public Function GetSheets()
		Set GetSheets = m_oWorkBook.Worksheets
	End Function

	'@==========================================================================
	''機能: Excelアクティブシートを取得
	''@return アクティプシート
	'@==========================================================================
	Public Function GetActiveSheet()
		Set GetActiveSheet = m_oWorkBook.ActiveSheet
	End Function

	'@==========================================================================
	''機能: 指定シートをExcelアクティブシートに変更
	''@param sheetName シート名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function SetActiveSheet(ByVal sheetName)

		On Error Resume Next
		m_oWorkBook.Sheets(sheetName).Activate
		If Err.Number <> 0 Then
			SetActiveSheet = False
			Exit Function
		End If
		On Error Goto 0

		SetActiveSheet = True

	End Function

	'@==========================================================================
	''機能: Excelシートをコピー
	''@param fromSheet コピー元のシート名
	''@param toSheet コピー先のシート名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function CopySheetAs(ByVal fromSheet, ByVal toSheet)

		Dim oSheet

		CopySheetAs = True

		On Error Resume Next
		Set oSheet = m_oWorkBook.Worksheets(fromSheet)
		Call oSheet.Copy(Null, m_oWorkBook.Worksheets(m_oWorkBook.Worksheets.Count))
		Set oSheet = m_oWorkBook.Worksheets(m_oWorkBook.Worksheets.Count)
		oSheet.Name = toSheet
		If Err.Number <> 0 Then
			'エラー発生の場合
			CopySheetAs = False
		End If
		On Error Goto 0

		Set oSheet = Nothing

	End Function

	'@==========================================================================
	''機能: Excelファイルをクローズ
	''@param bSave 修正を保存するか?
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function Close(ByVal bSave)

		On Error Resume Next
		Call m_oWorkBook.Close(bSave)
		Set m_oWorkBook = Nothing
		If Err.Number <> 0 Then
			'エラーの場合
			Close = False
			Exit Function
		End If
		On Error Goto 0

		Close = True

	End Function

	'@==========================================================================
	''機能: Excelファイルを保存
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function Save()

		On Error Resume Next
		If Not m_oWorkBook.Save() Then
			Save = False
		End If
		On Error Goto 0

		Save = True

	End Function

	'@==========================================================================
	''機能: Excelファイルを指定ファイル名に保存
	''@param fileName ファイル名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function SaveAs(fileName)

		On Error Resume Next
		If Not m_oWorkBook.SaveAs(fileName) Then
			SaveAs = False
		End If
		On Error Goto 0

		SaveAs = True

	End Function

	'@==========================================================================
	''機能: Excelファイルを指定ファイル名に保存してファイルをオープン
	''@param fileName ファイル名
	''@return True(成功) / False(失敗)
	'@==========================================================================
	Public Function SaveAsAndOpen(fileName)

		SaveAsAndOpen = False

		'ファイルの保存
		On Error Resume Next
		If Not m_oWorkBook.SaveAs(fileName) Then
			Exit Function
		'正常終了した場合のみ、保存したファイルをオープン
		Else
			Call m_oWorkBook.Close(False)
			Set m_oWorkBook = Nothing
			Dim oExcelApp : Set oExcelApp = CreateObject("Excel.Application")
			oExcelApp.Visible = True
			Dim oWorkBook : Set oWorkBook = oExcelApp.WorkBooks.Open(fileName)
			If Err.Number <> 0 Then
				'エラー発生の場合
				Exit Function
			End If
		End If
		On Error Goto 0

		SaveAsAndOpen = True

	End Function

	'@==========================================================================
	''機能: Excelファイルに指定シートがあるかのチェック
	''@param sheetName シート名
	''@return True(ある) / False(ない)
	'@==========================================================================
	Public Function ExistsSheet(ByVal sheetName)

		'指定シートの存在チェック
		On Error Resume Next
		If m_oWorkBook.Sheets(sheetName) Is Nothing Then
			ExistsSheet = False
			Exit Function
		End If
		On Error GoTo 0

		ExistsSheet = True

	End Function

	'@==========================================================================
	''機能:セル値が"エラー型"の場合、空欄にして、取得値が最後に文字列にする
	''@param val セル値
	''@return 処理した文字列
	'@==========================================================================
	Public Function NullStrGuard(ByVal val)

		If m_oApp.WorksheetFunction.IsError(val) Then
			val = ""
		ElseIf IsEmpty(val) Then
			val = ""
		ElseIf IsNull(val) Then
			val = ""
		End If
		NullStrGuard = CStr(val)

	End Function

End Class

'EOF