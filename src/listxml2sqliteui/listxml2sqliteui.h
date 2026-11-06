///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __LISTXML2SQLITEUI_H__
#define __LISTXML2SQLITEUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/gauge.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_BARRA_ESTADO 1000
#define wxID_BARRA_PORCENTAJE 1001

///////////////////////////////////////////////////////////////////////////////
/// Class listXML2SQLiteUI
///////////////////////////////////////////////////////////////////////////////
class listXML2SQLiteUI : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* estado;
		wxBoxSizer* bSizer1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText5;
		wxFilePickerCtrl* sel_mame;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText6;
		wxFilePickerCtrl* sel_listxml;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText2;
		wxStaticText* ruta_seleccionada;
		wxStaticText* m_staticText4;
		wxFilePickerCtrl* sel_basededatos;
		wxRadioBox* opciones_extraccion;
		wxGauge* porcentajeHecho;
		wxButton* botonGenerar;
		wxButton* botonSalir;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Onmame( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void Onlistxml( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void Onbdd( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnExportar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSalir( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		listXML2SQLiteUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("listxml 2 SQLite"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~listXML2SQLiteUI();
	
};

#endif //__LISTXML2SQLITEUI_H__
