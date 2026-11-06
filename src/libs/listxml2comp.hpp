#ifndef __LISTXML2COMP_HPP__
#define __LISTXML2COMP_HPP__

#include <GuruCompat.h>

#include <modelodatosmame.hpp>
#include <parserxml.hpp>

/*
// Compara la salida -listxml contra una base de datos.
*/

class listxml2comp: public GuruMAME::GuruParserXML {
	uint64_t _machines = 0;
public:
	listxml2comp() {}
	virtual ~listxml2comp() {}

	void iniciar() {
		_machines = 0;
		GuruMAME::GuruParserXML::iniciar();
	}

	virtual void game(modelodatosmame::game& machine) {
		_machines++;
	}

	virtual void end() {
		int a = 0;
	}

	uint64_t machines() { return _machines; }
};

#endif
