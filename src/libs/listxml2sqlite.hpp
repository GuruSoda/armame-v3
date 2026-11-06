#ifndef __LISTXML2SQLITE_HPP__
#define __LISTXML2SQLITE_HPP__

#include <string>

#include <GuruSQLite.hpp>

#include <modelomame.hpp>
#include <modelodatosmame.hpp>
#include <parserxml.hpp>

class XMLaSQLite: public GuruMAME::GuruParserXML {
public:
	XMLaSQLite() {}
	virtual ~XMLaSQLite() {}

	void sqlite(const string& base) { 
		if (GuruDirectorio::existe(base)) GuruDirectorio::borrarArchivo(base);
		mame.abrir(base); 
	}

	void game(modelodatosmame::game& nuevo) {

		if (!nuevo.isbios && !nuevo.isdevice) {
			if (mame.insertar_game(nuevo)) {
		//		cout << nuevo.name << endl;
		//		cout << "\r" << progreso();
			}
		}
	}

	void version(const GuruMAME::version& ver) {
//		cout << "Procesando: " << ver.build << endl;
	};

private:
	modelomame		mame;
};

#endif
