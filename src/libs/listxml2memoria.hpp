#ifndef __LISTXML2MEMORIA_HPP__
#define __LISTXML2MEMORIA_HPP__

#include <list>
#include <map>

#include <GuruCompat.h>

#include <modelodatosmame.hpp>
#include <parserxml.hpp>

class XMLaMemoria: public GuruMAME::GuruParserXML {
	std::list<modelodatosmame::game>		listxml;
	set<modelodatosmame::rom>				roms;

	std::map<uint64_t, vector<uint64_t> >	game_rom; // id game -> id's roms

	std::set<std::string>	manufacturer;
	uint64_t total = 1;
public:
	XMLaMemoria() {}
	virtual ~XMLaMemoria() {}

	void game(modelodatosmame::game& machine) {

		listxml.push_back(machine);
//		cout << nuevo.name << endl;
//		cout << "\r" << progreso();

		total++;
	}
};

#endif
