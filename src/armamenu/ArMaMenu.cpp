///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ArMaMenu.h"

///////////////////////////////////////////////////////////////////////////

ArMaMenu::ArMaMenu( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_toolBar1 = new wxToolBar( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_tool1 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool2 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_GO_HOME, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool3 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_FLOPPY, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_toolBar1->Realize(); 
	
	bSizer2->Add( m_toolBar1, 0, wxEXPAND, 5 );
	
	texto_superior = new wxStaticText( m_panel1, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	texto_superior->Wrap( -1 );
	bSizer2->Add( texto_superior, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listBox1 = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxNO_BORDER ); 
	m_listBox1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	bSizer3->Add( m_listBox1, 0, wxALL|wxEXPAND, 5 );
	
	m_bitmap1 = new wxStaticBitmap( m_panel1, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bitmap1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	texto_inferior = new wxStaticText( m_panel1, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	texto_inferior->Wrap( -1 );
	bSizer2->Add( texto_inferior, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_panel1->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( ArMaMenu::OnTecla ), NULL, this );
	this->Connect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ArMaMenu::OnOpen ) );
	texto_superior->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ArMaMenu::ClickDerecho ), NULL, this );
}

ArMaMenu::~ArMaMenu()
{
	// Disconnect Events
	m_panel1->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( ArMaMenu::OnTecla ), NULL, this );
	this->Disconnect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ArMaMenu::OnOpen ) );
	texto_superior->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ArMaMenu::ClickDerecho ), NULL, this );
	
}

listxml2sqlite::listxml2sqlite( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 540,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Archivo .xml (MAME -listxml)") ), wxVERTICAL );
	
	xml = new wxFilePickerCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	sbSizer1->Add( xml, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Base de Datos") ), wxVERTICAL );
	
	baseDeDatos = new wxFilePickerCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	sbSizer4->Add( baseDeDatos, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button4 = new wxButton( m_panel2, wxID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button4, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	m_button3 = new wxButton( m_panel2, wxID_OK, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button3, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer5->Add( bSizer6, 0, wxALIGN_RIGHT, 5 );
	
	
	m_panel2->SetSizer( bSizer5 );
	m_panel2->Layout();
	bSizer4->Add( m_panel2, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	this->Centre( wxBOTH );
}

listxml2sqlite::~listxml2sqlite()
{
}

Filtro::Filtro( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Filtro") ), wxHORIZONTAL );
	
	m_checkBox1 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("cloneof"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox1, 0, wxALL, 5 );
	
	m_checkBox2 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("romof"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox2, 0, wxALL, 5 );
	
	m_checkBox3 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("sampleof"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox3, 0, wxALL, 5 );
	
	m_checkBox4 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("runnable"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox4, 0, wxALL, 5 );
	
	m_checkBox5 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("isdevice"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox5, 0, wxALL, 5 );
	
	m_checkBox6 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("isbios"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_checkBox6, 0, wxALL, 5 );
	
	m_checkBox7 = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("ismechanical"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox7->SetValue(true); 
	sbSizer3->Add( m_checkBox7, 0, wxALL, 5 );
	
	
	bSizer8->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button6 = new wxButton( m_panel3, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button5 = new wxButton( m_panel3, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer8->Add( bSizer9, 0, wxALIGN_RIGHT, 5 );
	
	
	m_panel3->SetSizer( bSizer8 );
	m_panel3->Layout();
	bSizer8->Fit( m_panel3 );
	bSizer7->Add( m_panel3, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );
	
	this->Centre( wxBOTH );
}

Filtro::~Filtro()
{
}

Proxy::Proxy( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_panel10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 540,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel10, wxID_ANY, wxT("Proxy") ), wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText3 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Servidor"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer13->Add( m_staticText3, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl2 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_textCtrl2, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Puerto"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer14->Add( m_staticText4, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl3 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxT("3128"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl3->SetMaxLength( 5 ); 
	bSizer14->Add( m_textCtrl3, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer12->Add( bSizer14, 0, 0, 5 );
	
	
	sbSizer8->Add( bSizer12, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText5 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Usuario"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer16->Add( m_staticText5, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl4 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_textCtrl4, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer15->Add( bSizer16, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText7 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Clave"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer17->Add( m_staticText7, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl5 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer17->Add( m_textCtrl5, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer15->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	sbSizer8->Add( bSizer15, 0, wxEXPAND, 5 );
	
	
	bSizer11->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button6 = new wxButton( m_panel10, wxID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_button6, 0, wxALL, 5 );
	
	m_button5 = new wxButton( m_panel10, wxID_OK, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_button5, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer18, 1, wxALIGN_RIGHT, 5 );
	
	
	m_panel10->SetSizer( bSizer11 );
	m_panel10->Layout();
	bSizer10->Add( m_panel10, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );
	
	this->Centre( wxBOTH );
}

Proxy::~Proxy()
{
}

BaseMachines::BaseMachines( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_panel11 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 540,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel11, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	m_staticText8 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Base de Datos"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	sbSizer9->Add( m_staticText8, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_filePicker3 = new wxFilePickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	sbSizer9->Add( m_filePicker3, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button8 = new wxButton( sbSizer9->GetStaticBox(), wxID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_button8, 0, wxALL, 5 );
	
	m_button7 = new wxButton( sbSizer9->GetStaticBox(), wxID_OK, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_button7, 0, wxALL, 5 );
	
	
	sbSizer9->Add( bSizer21, 0, wxALIGN_RIGHT, 5 );
	
	
	bSizer20->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	
	m_panel11->SetSizer( bSizer20 );
	m_panel11->Layout();
	bSizer19->Add( m_panel11, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer19 );
	this->Layout();
	bSizer19->Fit( this );
	
	this->Centre( wxBOTH );
}

BaseMachines::~BaseMachines()
{
}

listxml2sqliteV2::listxml2sqliteV2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	m_panel6 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 480,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, wxT("Origen") ), wxVERTICAL );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_button9 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("mame.exe"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button9, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("or"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer28->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button10 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("listxml.xml"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button10, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizer6->Add( bSizer28, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Seleccionado:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer25->Add( m_staticText8, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer25->Add( m_staticText9, 0, wxALL, 5 );
	
	
	sbSizer6->Add( bSizer25, 0, wxEXPAND, 5 );
	
	
	bSizer29->Add( sbSizer6, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, wxT("Destino") ), wxVERTICAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Base de Datos:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer30->Add( m_staticText13, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_filePicker6 = new wxFilePickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxT("Base de datos a generar"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	bSizer30->Add( m_filePicker6, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	sbSizer9->Add( bSizer30, 1, wxEXPAND, 5 );
	
	
	bSizer29->Add( sbSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button11 = new wxButton( m_panel6, wxID_OK, wxT("Exportar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button11, 0, wxALL, 5 );
	
	m_button12 = new wxButton( m_panel6, wxID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button12, 0, wxALL, 5 );
	
	
	bSizer29->Add( bSizer32, 0, wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	
	m_gauge1 = new wxGauge( m_panel6, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge1->SetValue( 0 ); 
	bSizer33->Add( m_gauge1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer29->Add( bSizer33, 0, wxEXPAND, 5 );
	
	
	m_panel6->SetSizer( bSizer29 );
	m_panel6->Layout();
	bSizer22->Add( m_panel6, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer22 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

listxml2sqliteV2::~listxml2sqliteV2()
{
}
