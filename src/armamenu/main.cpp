#include <wx/wx.h>

#include "ArMaMenu.h" // Modificar por el .h generado por wxFormbuilder

// Modificar UI_MainFrame por el nombre de la clase generada por wxFormbuilder dentro de .h
class ui : public ArMaMenu {
protected:
	void OnSalirClick(wxCommandEvent& event) { OutputDebugString(_T("Salir!"));}

	void OnTecla(wxKeyEvent& event) { 
		int a = 0;
	}

	virtual void OnOpen(wxCommandEvent& event) { 
		BaseMachines dlg(NULL);

		if (dlg.ShowModal() == wxID_OK) {

		}
	}

	void ClickDerecho(wxMouseEvent& event) { 
		int a = 0;
//		listxml2sqlite dlg(NULL);
		listxml2sqliteV2 dlg(NULL);
//		Proxy dlg(NULL);
//		BaseMachines dlg(NULL);

		if(dlg.ShowModal() == wxID_OK) {
		}
	}

public:
	ui(wxWindow* parent):ArMaMenu(parent) {}
};

class wxWidgetsApp : public wxApp {
public:
	wxWidgetsApp() {};
	virtual ~wxWidgetsApp() {};

	virtual bool OnInit() {
		ui* dialog = new ui( (wxWindow*)NULL );
		dialog->Show();
		SetTopWindow( dialog );

		return true;
	}
};

DECLARE_APP(wxWidgetsApp)

IMPLEMENT_APP(wxWidgetsApp)
