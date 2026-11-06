#include <wx/wx.h>
#include <future>

#include <wx/app.h>

// generado por wxFormbuilder
#include "listxml2sqliteui.h"

#include <listxml2count.hpp>
#include <listxml2sqlitebasico.hpp>
#include <listxml2sqlitev2.hpp>

#include <GuruLog.hpp>

wxDEFINE_EVENT(LISTXML_UPDATE, wxCommandEvent);

class wxListxml2SQLiteV2: public listxml2SQLiteV2 {
	time_t			ultimo = 0, ahora = 0;
	wxWindow*		parent;
	uint64_t		_total_machines = 0;
	wxStatusBar*	barra_estado;
	wxGauge*		barra_porcentaje;
	wxCommandEvent	evento;
public:
	wxListxml2SQLiteV2(wxWindow* parent):parent(parent) {
		barra_porcentaje = (wxGauge*)parent->FindWindowById(wxID_BARRA_PORCENTAJE);
		evento.SetEventType(LISTXML_UPDATE);
	}
	virtual ~wxListxml2SQLiteV2() {}

	void game(modelodatosmame::game& machine) {

		ahora = ::time(NULL);

		if (ahora > ultimo + 1) {
			ultimo = ahora;

//			barra_estado->SetStatusText(wxString(wxT("Procesados ") + GuruStringAlgo::itos(listxml2SQLiteV2::machines())) + wxT(" Machines"));

			wxString str_estado;
			str_estado = wxString(wxT("Procesados ") + GuruStringAlgo::itos(listxml2SQLiteV2::machines())) + wxT(" Machines");

			// Como se ejecuta en el thread da error, las UI son orientada a eventos y no se puede hacer asi.
			//			((wxStatusBar*)parent->FindWindowById(wxID_BARRA_ESTADO))->SetStatusText(total);

			evento.SetString(str_estado);
			evento.SetExtraLong(1); // barra de estado

			wxPostEvent(parent, evento);
		}

		listxml2SQLiteV2::game(machine); // para que no aparezca la primera vez un 1 en la barra de estado.

		if (_total_machines) {
			evento.SetExtraLong(5); // rango de la barra de porcentaje
			evento.SetInt(total);

			wxPostEvent(parent, evento);
		}
	}

	void total_machines(uint64_t total) {
		_total_machines = total;

		evento.SetExtraLong(4); // tamaño de la barra de porcentaje
		evento.SetInt(total);

		wxPostEvent(parent, evento);
	}
};

class wxListxml2SQLiteBasico: public listxml2SQLiteBasico {
	time_t ultimo = 0, ahora = 0;
	wxWindow* parent;
	wxCommandEvent	evento;
public:
	wxListxml2SQLiteBasico(wxWindow* parent) :parent(parent) { evento.SetEventType(LISTXML_UPDATE); }
	virtual ~wxListxml2SQLiteBasico() {}

	void game(modelodatosmame::game& machine) {

		ahora = ::time(NULL);

		if (ahora > ultimo + 1) { // refresco cada 1 segundo
			ultimo = ahora;

//			((wxStatusBar*)parent->FindWindowById(wxID_BARRA_ESTADO))->SetStatusText(wxString(wxT("Procesados:") + GuruStringAlgo::itos(wxListxml2SQLiteBasico::machines())));

			wxString str_estado;
			str_estado = wxString(wxT("Procesados:") + GuruStringAlgo::itos(wxListxml2SQLiteBasico::machines()));

			evento.SetString(str_estado);
			evento.SetExtraLong(1); // barra de estado

			wxPostEvent(parent, evento);
		}

		listxml2SQLiteBasico::game(machine); // para que no aparezca la primera vez un 1 en la barra de estado.
	}
};

class wxListxml2Count : public listxml2count {
	time_t ultimo = 0, ahora = 0;
	wxWindow* parent;
public:
	wxListxml2Count(wxWindow* parent):parent(parent) {}
	virtual ~wxListxml2Count() {}

	void game(modelodatosmame::game& machine) {

		ahora = ::time(NULL);

		if (ahora > ultimo + 1) { // refresco cada 1 segundo
			ultimo = ahora;
			wxString total;

			total = wxT("Procesados: ") + GuruStringAlgo::itos(listxml2count::machines());

			// Como se ejecuta en el thread da error, las UI son orientada a eventos y no se puede hacer asi.
//			((wxStatusBar*)parent->FindWindowById(wxID_BARRA_ESTADO))->SetStatusText(total);

			wxCommandEvent evento(LISTXML_UPDATE);

			evento.SetString(total);
			evento.SetExtraLong(1); // barra de estado

			wxPostEvent(parent, evento);
		}

		listxml2count::game(machine); // para que no aparezca la primera vez un 1 en la barra de estado.
	}

	void end() {
		wxCommandEvent evento(LISTXML_UPDATE);

		evento.SetString(wxT("Finalizado, Procesados: ") + GuruStringAlgo::itos(listxml2count::machines()));
		evento.SetExtraLong(1); // barra de estado

		wxPostEvent(parent, evento);
	}
};

// clase listXML2SQLiteUI generada por wxFormbuilder
class ui: public listXML2SQLiteUI {
	wxString			origen;
	wxString			bdd;
	std::future<void>	contar_async;
	GuruMAME::GuruParserXML*	xml_a = NULL;
protected:
	void Onmame(wxFileDirPickerEvent& event) { ruta_seleccionada->SetLabel(event.GetPath()); origen = event.GetPath(); }
	void Onlistxml(wxFileDirPickerEvent& event) { ruta_seleccionada->SetLabel(event.GetPath()); origen = event.GetPath(); }
	void Onbdd(wxFileDirPickerEvent& event) { bdd = event.GetPath(); }

	void deshabilitar_todo() {
		sel_mame->Enable(false);
		sel_listxml->Enable(false);
		sel_basededatos->Enable(false);
		opciones_extraccion->Enable(false);
		botonGenerar->Enable(false);
	}

	void habilitar_todo() {
		sel_mame->Enable(true);
		sel_listxml->Enable(true);
		sel_basededatos->Enable(true);
		opciones_extraccion->Enable(true);
		botonGenerar->Enable(true);
	}

	void OnExportar(wxCommandEvent& event) {

		if (origen.empty()) {
			wxMessageBox(wxT("Por favor, seleccione un origen"), wxT("Problema"), wxICON_INFORMATION);
			return;
		}

		if (opciones_extraccion->GetSelection() == 0) {
			if (bdd.empty()) {
				wxMessageBox(wxT("Seleccione un destino"), wxT("Problema"), wxICON_INFORMATION);
				return;
			}

			deshabilitar_todo();
			botonSalir->SetLabelText(wxT("Cancelar"));
			estado->SetStatusText(wxT("Contando Machines..."));

			contar_async = std::async(std::launch::async, [&]() {
				uint64_t total_machines = 0;

				wxCommandEvent evento(LISTXML_UPDATE);

				{
					xml_a = new wxListxml2Count(this);

					xml_a->xml(origen.ToStdString());

					xml_a->iniciar();

					total_machines = static_cast<wxListxml2Count*>(xml_a)->machines();

					delete xml_a;
				}

				evento.SetString(wxT("Procesando Machines"));
				evento.SetExtraLong(1); // barra de estado
				wxPostEvent(this, evento);

				xml_a = new wxListxml2SQLiteV2(this);

				xml_a->xml(origen.ToStdString());
				(static_cast<wxListxml2SQLiteV2*>(xml_a))->nombre_base(bdd.ToStdString());

				(static_cast<wxListxml2SQLiteV2*>(xml_a))->total_machines(total_machines);

				xml_a->iniciar();

				evento.SetString(wxT("Escribiendo Machines en ") + bdd);
				evento.SetExtraLong(1); // barra de estado
				wxPostEvent(this, evento);

				(static_cast<wxListxml2SQLiteV2*>(xml_a))->importar_a_base_v2();

				delete xml_a;

				evento.SetString(wxT("Datos exportados correctamente"));
				evento.SetExtraLong(2); // pop-up
				wxPostEvent(this, evento);

				evento.SetExtraLong(3); // habilitar todo
				wxPostEvent(this, evento);
			});

		} else if (opciones_extraccion->GetSelection() == 1) {
			if (bdd.empty()) {
				wxMessageBox(wxT("Seleccione un destino"), wxT("Problema"), wxICON_INFORMATION);
				return;
			}

			deshabilitar_todo();
			botonSalir->SetLabelText(wxT("Cancelar"));
			estado->SetStatusText(wxT("Generando"));

			contar_async = std::async(std::launch::async, [&]() {
				xml_a = new wxListxml2SQLiteBasico(this);

				xml_a->xml(origen.ToStdString());
				(static_cast<wxListxml2SQLiteBasico*>(xml_a))->nombre_base(bdd.ToStdString());

				xml_a->iniciar();

				delete xml_a;

				wxCommandEvent evento(LISTXML_UPDATE);
				evento.SetString(wxT("Datos exportados correctamente"));
				evento.SetExtraLong(2); // pop-up
				wxPostEvent(this, evento);

				evento.SetExtraLong(3); // habilitar todo
				wxPostEvent(this, evento);
			});

		} else if (opciones_extraccion->GetSelection() == 2) {
			GURULOG_TRACE("deshabilitar_todo...");
			deshabilitar_todo();
			GURULOG_TRACE("botonSalir...");
			botonSalir->SetLabelText(wxT("Cancelar"));
			GURULOG_TRACE("estado...");
			estado->SetStatusText(wxT("Contando Machines..."));

			contar_async = std::async(std::launch::async, [&]() {
				xml_a = new wxListxml2Count(this);

				xml_a->xml(origen.ToStdString());

				xml_a->iniciar();

				GURULOG_TRACE("Terminado de contar, " +  GuruStringAlgo::itos((static_cast<wxListxml2Count*>(xml_a))->machines()) + " encontrados...");

				wxCommandEvent evento(LISTXML_UPDATE);

				evento.SetString("Terminado de contar, " + GuruStringAlgo::itos((static_cast<wxListxml2Count*>(xml_a))->machines()) + " encontrados...");
				evento.SetExtraLong(2); // pop-up

	//			wxPostEvent(this, evento);
				// or
				this->AddPendingEvent(evento);

				delete xml_a;

				evento.SetExtraLong(3); // habilitar todo
				wxPostEvent(this, evento);
			});
		} 
	}

	void OnClose(wxCloseEvent&) {
		cout << "OnClose!" << endl;
		Destroy();
	}

	void OnSalir(wxCommandEvent& event) {
		cout << "Boton Salir!" << endl;
		this->Destroy();

		if (!contar_async.valid()) wxWindow::Close();

		else if (contar_async.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout) {
			if (wxMessageBox(wxT("Cancelar?"), wxT("listXML2SQLite"), wxYES_NO | wxICON_EXCLAMATION) == wxYES) {
				if (opciones_extraccion->GetSelection() == 0) {
					xml_a->finalizar();
				} else if (opciones_extraccion->GetSelection() == 1) {
					xml_a->finalizar();
				} else if (opciones_extraccion->GetSelection() == 2) 
					xml_a->finalizar();
			}
		} else 
			this->Close(true);
	}

	void finTarea(wxCommandEvent& evento) {
		wxMessageBox(evento.GetString(), wxT("Finalizado"), wxICON_INFORMATION);
	}

	void actualizar(wxCommandEvent& evento) {

		if (evento.GetExtraLong() == 1) { // barra de estado
			estado->SetStatusText(evento.GetString());
		} else if (evento.GetExtraLong() == 2) { // pop-up
			wxMessageBox(evento.GetString(), wxT("listXML2SQLite"), wxICON_INFORMATION);
		} else if (evento.GetExtraLong() == 3) { // habilitar todo
			habilitar_todo();
			botonSalir->SetLabelText(wxT("Salir"));
		} else if (evento.GetExtraLong() == 4) { // tamaño de la barra de porcentaje
			porcentajeHecho->SetRange(evento.GetInt());
		} else if (evento.GetExtraLong() == 5) { // valor de la barra de porcentaje
			porcentajeHecho->SetValue(evento.GetInt());
		}
	}

public:
	ui(wxWindow* parent):listXML2SQLiteUI(parent) {
		Bind(LISTXML_UPDATE, &ui::actualizar, this);
	}

	virtual ~ui() {
		Unbind(LISTXML_UPDATE, &ui::actualizar, this);
		cout << "Destruyendo!" << endl;
	}

	wxStatusBar* BarraEstado() { return estado;	}
};

class wxWidgetsApp: public wxApp {
	ui* dialog;
public:
	wxWidgetsApp() {};
	virtual ~wxWidgetsApp() {
		cout << "Destruyendo App" << endl;
	};

	virtual bool OnInit() {
		if (!wxApp::OnInit()) return false;

//		GuruLog::init(GuruLog::level_trace, cout);
		
		dialog = new ui( (wxWindow*)NULL );

		dialog->Show(true);
		SetTopWindow( dialog );

		return true;
	}

	virtual int OnExit() {
		cout << "Chau!" << endl;

		this->wxApp::OnExit();

		return 0;
	}

	virtual void OnUnhandledException() {
		cout << "Quilombo!" << endl;
	}
};

DECLARE_APP(wxWidgetsApp)

IMPLEMENT_APP(wxWidgetsApp)

