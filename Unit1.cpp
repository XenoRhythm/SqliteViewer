//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "sqlite3.h"
#include <string>
#include "Unit1.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
sqlite3* Database;
String filePath;
bool ExecQueryNoResult(const char *sql);
bool ExecQueryWithResult(const char *sql, TForm1 *Form1);
void CloseApp(TForm1 *Form1);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->VirtualStringTree1->NodeDataSize = sizeof(TreeNode);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonCloseClick(TObject *Sender)
{
	CloseApp(this);
}
//---------------------------------------------------------------------------
void CloseApp(TForm1 *Form1)
{
	Form1->VirtualStringTree1->Clear();
	sqlite3_close(Database);
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	CloseApp(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonLoadClick(TObject *Sender)
{
	if(filePath!="")
	{
		VirtualStringTree1->Clear();
		sqlite3_close(Database);
		VirtualStringTree1->Visible = False;
		ButtonSelect->Enabled = False;
		ButtonDelete->Enabled = False;
		ButtonDeleteAll->Enabled = False;
		LabelStatus->Caption = "Смена базы данных. Закрытие старой.";
	}

	if (OpenDialog1->Execute())
	{
		filePath = OpenDialog1->FileName;
		const wchar_t* filePathChar = filePath.c_str();
		if(sqlite3_open16(filePathChar,&Database) == 0)
		{
			LabelStatus->Caption = "База данных загружена";
			ButtonSelect->Enabled = True;
			ButtonDelete->Enabled = True;
			ButtonDeleteAll->Enabled = True;
			VirtualStringTree1->Visible = True;
		}
		else
		{
			LabelStatus->Caption = "Ошибка подключения базы данных";
		}
	}
}
//---------------------------------------------------------------------------
bool ExecQueryNoResult(const char *sql)
{
	sqlite3_stmt *pStatement;
	int result = sqlite3_prepare_v2(Database,sql,-1,&pStatement,NULL);
	if(result != SQLITE_OK)
	{
		return false;
	}
    result = sqlite3_step(pStatement);
	if(result != SQLITE_DONE)
	{
		return false;
	}
	sqlite3_finalize(pStatement);
	return true;
}
//---------------------------------------------------------------------------
bool ExecQueryWithResult(const char *sql, TForm1 *Form1)
{
	sqlite3_stmt *pStatement;
	int result = sqlite3_prepare_v2(Database,sql,-1,&pStatement,NULL);
	if(result != SQLITE_OK)
	{
		return false;
	}

	Form1->VirtualStringTree1->Clear();

	while(true)
	{

		result = sqlite3_step(pStatement);

		if(result == SQLITE_ROW)
		{
			PVirtualNode entryNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode);
			TreeNode *nodeData = (TreeNode*)Form1->VirtualStringTree1->GetNodeData(entryNode);

			nodeData->id = sqlite3_column_int(pStatement, 0 /*номер столбца*/);
			nodeData->url = (wchar_t*)sqlite3_column_text16(pStatement, 1);
			nodeData->title = (wchar_t*)sqlite3_column_text16(pStatement, 2);
			nodeData->visit_count = sqlite3_column_int(pStatement, 3);
		}
		else
		{
			return false;
		}
	}

	sqlite3_finalize(pStatement);
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDeleteClick(TObject *Sender)
{
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	if(!selectedNode)
	{
		LabelStatus->Caption = "Ошибка получения выделенной строки";
		return;
	}
	unsigned int selectedNodeIndex = selectedNode->Index;
	TreeNode *nodeData = (TreeNode*)VirtualStringTree1->GetNodeData(selectedNode);

	string id = to_string(nodeData->id);
	string sql_s = "delete from urls where id=="+id+" ;";
	const char *sql =sql_s.c_str();

	if(!ExecQueryNoResult(sql))
	{
		LabelStatus->Caption = "Произошла ошибка выполнения запроса удаления";
	}
	else
	{
		VirtualStringTree1->DeleteNode(selectedNode);
		LabelStatus->Caption = "Запись была удалена";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDeleteAllClick(TObject *Sender)
{
	const char *sql = "delete from urls ;";
	if(!ExecQueryNoResult(sql))
	{
		LabelStatus->Caption = "Произошла ошибка выполнения запроса удаления";
	}
	else
	{
		VirtualStringTree1->Clear();
		LabelStatus->Caption = "Все данные были удалены";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSelectClick(TObject *Sender)
{
	const char *sql = "select id, url, title, visit_count from urls ;";
	if(!ExecQueryWithResult(sql, this))
	{
		LabelStatus->Caption = "Произошла ошибка выполнения запроса получения строк";
	}
	else
	{
		LabelStatus->Caption = "Данные получены";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
    if(!Node)	return;
	TreeNode *nodeData = (TreeNode*)Sender->GetNodeData(Node);
	switch(Column)
	{
		case 0: CellText = nodeData->id; break;
		case 1: CellText = nodeData->url; break;
		case 2: CellText = nodeData->title; break;
		case 3: CellText = nodeData->visit_count; break;
	}
}
//---------------------------------------------------------------------------
