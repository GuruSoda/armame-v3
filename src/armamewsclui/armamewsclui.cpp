///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "armamewsclui.h"

///////////////////////////////////////////////////////////////////////////

ArMameWSCLUI::ArMameWSCLUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Busqueda"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_busqueda = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER ); 
	bSizer3->Add( m_busqueda, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button_buscar = new wxButton( m_panel1, wxID_ANY, wxT("Buscar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_buscar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, wxT("Resultado:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer4->Add( m_staticText2, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_lista_resultado = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer4->Add( m_lista_resultado, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_button_salir = new wxButton( m_panel1, wxID_ANY, wxT("Salir"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button_salir, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizer2->Add( bSizer5, 0, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer9->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer6->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer6->Add( bSizer10, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer6 );
	m_panel1->Layout();
	bSizer6->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_busqueda->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ArMameWSCLUI::OnBuscarSelect ), NULL, this );
	m_busqueda->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ArMameWSCLUI::OnBuscarEnter ), NULL, this );
	m_button_buscar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ArMameWSCLUI::OnBuscarClick ), NULL, this );
	m_button_salir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ArMameWSCLUI::OnSalirClick ), NULL, this );
}

ArMameWSCLUI::~ArMameWSCLUI()
{
	// Disconnect Events
	m_busqueda->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ArMameWSCLUI::OnBuscarSelect ), NULL, this );
	m_busqueda->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ArMameWSCLUI::OnBuscarEnter ), NULL, this );
	m_button_buscar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ArMameWSCLUI::OnBuscarClick ), NULL, this );
	m_button_salir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ArMameWSCLUI::OnSalirClick ), NULL, this );
	
}
