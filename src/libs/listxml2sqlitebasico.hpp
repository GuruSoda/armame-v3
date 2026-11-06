#ifndef __LISTXML2SQLITEBASICO_HPP__
#define __LISTXML2SQLITEBASICO_HPP__

#include <string>

#include <GuruCompat.h>
#include <GuruSQLite.hpp>
#include <GuruDirectorio.hpp>

#include <modelodatosmame.hpp>
#include <parserxml.hpp>

class listxml2SQLiteBasico : public GuruMAME::GuruParserXML {
	uint64_t total = 1;
	string	nombre_bd;

	const char* ddl = "\
PRAGMA synchronous = off; \
PRAGMA foreign_keys = on; \
drop table if exists game; \
create table game ( \
	id_game 	integer primary key autoincrement, \
	name		text, \
	year		integer, \
	description	text, \
	manufacturer text, \
	sourcefile   text, \
	cloneof		text, \
	romof		text, \
	sampleof	text, \
	runnable	boolean, \
	isbios		boolean, \
	isdevice	boolean, \
	ismechanical	boolean \
);";

	GuruSQLite::bd base;
public:
	listxml2SQLiteBasico() {}
	virtual ~listxml2SQLiteBasico() {
		base.desconectar();
	}

	virtual void game(modelodatosmame::game& machine) {

		try {
			string consulta;
			consulta = "insert into game (id_game, name, year, description, manufacturer, sourcefile, cloneof, romof, sampleof, runnable, isbios, isdevice, ismechanical) values (" +
					GuruStringAlgo::int64astr(total) + ", " +
					GuruStringAlgo::comillas(machine.name) + ", " +
					GuruStringAlgo::int64astr(machine.year) + ", " +
					((machine.description.find('"') != std::string::npos) ? GuruStringAlgo::comilla_simple(machine.description) : GuruStringAlgo::comillas(machine.description)) + ", " +
					GuruStringAlgo::comillas(machine.manufacturer) + ", " +
					GuruStringAlgo::comillas(machine.sourcefile) + ", " +
					GuruStringAlgo::comillas(machine.cloneof) + ", " +
					GuruStringAlgo::comillas(machine.romof) + ", " +
					GuruStringAlgo::comillas(machine.sampleof) + ", " +
					GuruStringAlgo::int64astr(machine.runnable ? 1 : 0) + ", " +
					GuruStringAlgo::int64astr(machine.isbios ? 1 : 0) + ", " +
					GuruStringAlgo::int64astr(machine.isdevice ? 1 : 0) + ", " +
					GuruStringAlgo::int64astr(machine.ismechanical ? 1 : 0) + ")";

			base.exec(consulta);

			total++;
		} catch (GuruSQLite::GuruSQLiteException& e) {
			cout << e.what() << endl;
			finalizar();
		}
	}

	virtual void version(const GuruMAME::version& ver) {

		if (nombre_bd.empty()) {

			size_t inicio = ver.build.find('.');
			size_t fin = ver.build.find(' ');

			string str_version(ver.build.substr(inicio + 1, (fin - inicio) - 1));

			nombre_bd = "mame-" + str_version + ".sqlite";
		}

		if (GuruDirectorio::existe(nombre_bd)) GuruDirectorio::borrarArchivo(nombre_bd);

		base = GuruSQLite::conectar(nombre_bd, ddl);

		base.exec("BEGIN TRANSACTION");
	}

	void end() {
		base.exec("create index idx_name on game(name)");
		base.exec("create index idx_description on game(description)");
		base.exec("create index idx_manufacturer on game(manufacturer)");
		base.exec("create index idx_sourcefile on game(sourcefile)");
		base.exec("create index idx_cloneof on game(cloneof)");
		base.exec("create index idx_romof on game(romof)");
		base.exec("create index idx_sampleof on game(sampleof)");

		base.exec("END TRANSACTION");
	}

	uint64_t machines() { return total; }

	void nombre_base(const string& nombre) { nombre_bd = nombre; }
	string& nombre_base() { return nombre_bd; }
};

#endif
