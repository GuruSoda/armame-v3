#include <wx/wx.h>
#include "armamewsclui.h"

#include <Windows.h>

#include <GuruHttp/GuruhttpClienteREST.hpp>

class MameGui : public ArMameWSCLUI
{
protected:
	void OnBuscarSelect(wxCommandEvent& event) { cargarResultado(); }
	void OnBuscarEnter(wxCommandEvent& event) { cargarResultado(); }
	void OnBuscarClick(wxCommandEvent& event) { cargarResultado(); }
	void OnSalirClick(wxCommandEvent& event) { Destroy(); }

	void cargarResultado() {

		try {

			m_lista_resultado->Clear();

			wxString busqueda = m_busqueda->GetValue();

			if (busqueda.empty()) return;

			wxString url;

			url = "http://www.planetaguru.com.ar/armamews/games?game=" + busqueda;

			GuruHttpCliente::opciones_get opt;

	//		opt.proxy_server("http://frossi:Soda0009@10.1.1.86:3128");
			GuruHttpCliente::rest::response res = GuruHttpCliente::rest::get(url.ToStdString(), opt);

			if (res.status_code() == 200) {
				uint32_t t = 1;
				wxArrayString descripciones;

				for (Json::ValueIterator it = res.json().begin(); it != res.json().end(); ++it, t++) {
					descripciones.push_back(wxString((*it)["Description"].asString()));
					// std::cout << "Name:" << (*it)["Name"].asString() << std::endl;
					// std::cout << "Description:" << (*it)["Description"].asString() << std::endl;
				}

				m_lista_resultado->InsertItems(descripciones, 0);
			} else {
				wxMessageBox("Sin resultados");
				return;
			}

			res.clear();
		} catch (GuruHttpCliente::GuruHttpException& e) {
			wxMessageBox(e.what());

		}
	}
public:
	MameGui(wxWindow* parent):ArMameWSCLUI(parent) {
		m_panel1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Consolas")));
	}
};

class wxWidgetsApp : public wxApp
{
public:
    wxWidgetsApp() {};
    virtual ~wxWidgetsApp() {};
    virtual bool OnInit();
};

DECLARE_APP(wxWidgetsApp)

IMPLEMENT_APP(wxWidgetsApp)

bool wxWidgetsApp::OnInit()
{
	MameGui* dialog = new MameGui( (wxWindow*)NULL );
    dialog->Show();
    SetTopWindow( dialog );
    return true;
}
