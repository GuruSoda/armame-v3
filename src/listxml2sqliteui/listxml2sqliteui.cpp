///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "listxml2sqliteui.h"

///////////////////////////////////////////////////////////////////////////

listXML2SQLiteUI::listXML2SQLiteUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	estado = this->CreateStatusBar( 2, 0, wxID_BARRA_ESTADO );
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 480,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* SizerOrigen;
	SizerOrigen = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Origen") ), wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( SizerOrigen->GetStaticBox(), wxID_ANY, wxT("mame.exe:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer8->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	sel_mame = new wxFilePickerCtrl( SizerOrigen->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.exe"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_SMALL );
	bSizer8->Add( sel_mame, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer5->Add( bSizer8, 1, wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( SizerOrigen->GetStaticBox(), wxID_ANY, wxT("or"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( SizerOrigen->GetStaticBox(), wxID_ANY, wxT("listxml.xml:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer9->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	sel_listxml = new wxFilePickerCtrl( SizerOrigen->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.xml"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_SMALL );
	bSizer9->Add( sel_listxml, 1, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer5->Add( bSizer9, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( SizerOrigen->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer5->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	
	SizerOrigen->Add( bSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( SizerOrigen->GetStaticBox(), wxID_ANY, wxT("Seleccionado:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer6->Add( m_staticText2, 0, wxALL, 5 );
	
	ruta_seleccionada = new wxStaticText( SizerOrigen->GetStaticBox(), wxID_ANY, wxT("."), wxDefaultPosition, wxDefaultSize, 0 );
	ruta_seleccionada->Wrap( -1 );
	bSizer6->Add( ruta_seleccionada, 0, wxALL, 5 );
	
	
	SizerOrigen->Add( bSizer6, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( SizerOrigen, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* SizerDestino;
	SizerDestino = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Destino") ), wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( SizerDestino->GetStaticBox(), wxID_ANY, wxT("Base de Datos"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer7->Add( m_staticText4, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	sel_basededatos = new wxFilePickerCtrl( SizerDestino->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	bSizer7->Add( sel_basededatos, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	SizerDestino->Add( bSizer7, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( SizerDestino, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* SizerOpciones;
	SizerOpciones = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Opciones") ), wxHORIZONTAL );
	
	wxString opciones_extraccionChoices[] = { wxT("Completo"), wxT("Basico"), wxT("Solo Contar") };
	int opciones_extraccionNChoices = sizeof( opciones_extraccionChoices ) / sizeof( wxString );
	opciones_extraccion = new wxRadioBox( SizerOpciones->GetStaticBox(), wxID_ANY, wxT("Exportar"), wxDefaultPosition, wxDefaultSize, opciones_extraccionNChoices, opciones_extraccionChoices, 3, wxRA_SPECIFY_COLS );
	opciones_extraccion->SetSelection( 2 );
	SizerOpciones->Add( opciones_extraccion, 0, 0, 5 );
	
	
	bSizer2->Add( SizerOpciones, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* SizerGenerar;
	SizerGenerar = new wxBoxSizer( wxHORIZONTAL );
	
	porcentajeHecho = new wxGauge( m_panel1, wxID_BARRA_PORCENTAJE, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	porcentajeHecho->SetValue( 0 ); 
	SizerGenerar->Add( porcentajeHecho, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	botonGenerar = new wxButton( m_panel1, wxID_ANY, wxT("Generar"), wxDefaultPosition, wxDefaultSize, 0 );
	SizerGenerar->Add( botonGenerar, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	botonSalir = new wxButton( m_panel1, wxID_EXIT, wxT("Salir"), wxDefaultPosition, wxDefaultSize, 0 );
	SizerGenerar->Add( botonSalir, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer2->Add( SizerGenerar, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	sel_mame->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onmame ), NULL, this );
	sel_listxml->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onlistxml ), NULL, this );
	sel_basededatos->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onbdd ), NULL, this );
	botonGenerar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( listXML2SQLiteUI::OnExportar ), NULL, this );
	botonSalir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( listXML2SQLiteUI::OnSalir ), NULL, this );
}

listXML2SQLiteUI::~listXML2SQLiteUI()
{
	// Disconnect Events
	sel_mame->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onmame ), NULL, this );
	sel_listxml->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onlistxml ), NULL, this );
	sel_basededatos->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( listXML2SQLiteUI::Onbdd ), NULL, this );
	botonGenerar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( listXML2SQLiteUI::OnExportar ), NULL, this );
	botonSalir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( listXML2SQLiteUI::OnSalir ), NULL, this );
}
