///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ARMAMEWSCLUI_H__
#define __ARMAMEWSCLUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ArMameWSCLUI
///////////////////////////////////////////////////////////////////////////////
class ArMameWSCLUI : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxComboBox* m_busqueda;
		wxButton* m_button_buscar;
		wxStaticText* m_staticText2;
		wxListBox* m_lista_resultado;
		wxButton* m_button_salir;
		wxNotebook* m_notebook1;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBuscarSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBuscarEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBuscarClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSalirClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ArMameWSCLUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ArMame3 Web Service Client"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~ArMameWSCLUI();
	
};

#endif //__ARMAMEWSCLUI_H__
