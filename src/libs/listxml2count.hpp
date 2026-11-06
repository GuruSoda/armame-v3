#ifndef __LISTXML2COUNT_HPP__
#define __LISTXML2COUNT_HPP__

#include <GuruCompat.h>

#include <modelodatosmame.hpp>
#include <parserxml.hpp>

class listxml2count: public GuruMAME::GuruParserXML {
	uint64_t _machines = 0;
public:
	listxml2count() {}
	virtual ~listxml2count() {}

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
