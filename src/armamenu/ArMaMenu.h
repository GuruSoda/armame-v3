///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ARMAMENU_H__
#define __ARMAMENU_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/filepicker.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/gauge.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ArMaMenu
///////////////////////////////////////////////////////////////////////////////
class ArMaMenu : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_tool1; 
		wxToolBarToolBase* m_tool2; 
		wxToolBarToolBase* m_tool3; 
		wxStaticText* texto_superior;
		wxListBox* m_listBox1;
		wxStaticBitmap* m_bitmap1;
		wxStaticText* texto_inferior;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTecla( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClickDerecho( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		ArMaMenu( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ArMaMenu"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~ArMaMenu();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class listxml2sqlite
///////////////////////////////////////////////////////////////////////////////
class listxml2sqlite : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel2;
		wxFilePickerCtrl* xml;
		wxFilePickerCtrl* baseDeDatos;
		wxButton* m_button4;
		wxButton* m_button3;
	
	public:
		
		listxml2sqlite( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~listxml2sqlite();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Filtro
///////////////////////////////////////////////////////////////////////////////
class Filtro : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel3;
		wxCheckBox* m_checkBox1;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxCheckBox* m_checkBox4;
		wxCheckBox* m_checkBox5;
		wxCheckBox* m_checkBox6;
		wxCheckBox* m_checkBox7;
		wxButton* m_button6;
		wxButton* m_button5;
	
	public:
		
		Filtro( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~Filtro();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Proxy
///////////////////////////////////////////////////////////////////////////////
class Proxy : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel10;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrl2;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl3;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textCtrl5;
		wxButton* m_button6;
		wxButton* m_button5;
	
	public:
		
		Proxy( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~Proxy();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseMachines
///////////////////////////////////////////////////////////////////////////////
class BaseMachines : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel11;
		wxStaticText* m_staticText8;
		wxFilePickerCtrl* m_filePicker3;
		wxButton* m_button8;
		wxButton* m_button7;
	
	public:
		
		BaseMachines( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~BaseMachines();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class listxml2sqliteV2
///////////////////////////////////////////////////////////////////////////////
class listxml2sqliteV2 : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel6;
		wxButton* m_button9;
		wxStaticText* m_staticText12;
		wxButton* m_button10;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText13;
		wxFilePickerCtrl* m_filePicker6;
		wxButton* m_button11;
		wxButton* m_button12;
		wxGauge* m_gauge1;
	
	public:
		
		listxml2sqliteV2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 480,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~listxml2sqliteV2();
	
};

#endif //__ARMAMENU_H__
