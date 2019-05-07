//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "VirtualTrees.hpp"
//---------------------------------------------------------------------------
struct TreeNode
{
	int id;
	UnicodeString url;
	UnicodeString title;
	int visit_count;
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonLoad;
	TButton *ButtonSelect;
	TButton *ButtonDelete;
	TButton *ButtonDeleteAll;
	TButton *ButtonClose;
	TLabel *LabelStatus;
	TOpenDialog *OpenDialog1;
	TVirtualStringTree *VirtualStringTree1;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonLoadClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonDeleteAllClick(TObject *Sender);
	void __fastcall ButtonSelectClick(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
