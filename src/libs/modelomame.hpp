#ifndef __MODELOMAME_HPP__
#define __MODELOMAME_HPP__

#include <string>
#include <sstream>
#include <stdexcept>
#include <GuruCache.hpp>
#include <GuruSQLite.hpp>
#include <GuruSQLite_algo.hpp>
#include <GuruString_algo.hpp>
#include <GuruToken.hpp>

#include <modelodatosmame.hpp>

using namespace std;

#if !defined (MAMESQLITE_V1) && !defined (MAMESQLITE_V2)
#define MAMESQLITE_V1
#endif

#if defined MAMESQLITE_V1
	static const char* ddl = " \
PRAGMA synchronous=off;\
PRAGMA foreign_keys=on;\
drop table if exists manufacturer; \
create table manufacturer ( \
	id_manufacturer integer primary key autoincrement, \
	name			text not null \
); \
drop table if exists game; \
create table game ( \
	id_game 	integer primary key autoincrement, \
	name		text unique, \
	sourcefile	text, \
	year		integer, \
	description	text, \
	id_manufacturer INTEGER REFERENCES manufacturer (id_manufacturer) ON DELETE CASCADE, \
	cloneof		text, \
	romof		text \
); \
drop table if exists rom; \
create table rom ( \
	id_rom	integer primary key autoincrement, \
	name	text not null, \
	size	integer, \
	crc		text, \
	sha1	text, \
	merge	integer \
); \
drop table if exists rom_game; \
create table rom_game ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_rom		integer references rom (id_rom) on delete cascade \
); \
drop table if exists game_cloneof_romof; \
create table game_cloneof_romof ( \
	id_game integer not null, \
	cloneof text, \
	romof text \
)";
#endif

#if defined MAMESQLITE_V2
// sin la tabla rom_game y con una columna mas en rom que hace referencia al juego
	static const char* ddl = " \
PRAGMA synchronous=off;\
PRAGMA foreign_keys=on;\
create table text ( \
	id_text integer primary key autoincrement, \
	text	text not null \
); \
create table driver ( \
	id_driver	integer primary key autoincrement, \
	status		integer references text (id_text) on delete cascade, \
	emulation	integer references text (id_text) on delete cascade, \
	color 		integer references text (id_text) on delete cascade, \
	sound		integer references text (id_text) on delete cascade, \
    graphic		integer references text (id_text) on delete cascade, \
    cocktail 	integer references text (id_text) on delete cascade, \
    protection	integer references text (id_text) on delete cascade, \
    savestate 	integer references text (id_text) on delete cascade \
); \
create table manufacturer ( \
	id_manufacturer integer primary key autoincrement, \
	name			text not null \
); \
create table sourcefile ( \
	id_sourcefile	integer primary key autoincrement, \
	name			text not null \
); \
create table game ( \
	id_game 	integer primary key autoincrement, \
	name		text unique, \
	year		integer, \
	description	text, \
	manufacturer integer references manufacturer (id_manufacturer) on delete cascade, \
	sourcefile   integer references sourcefile (id_sourcefile) on delete cascade, \
	driver		integer references driver (id_driver) on delete cascade, \
	cloneof		text, \
	romof		text, \
	runnable	boolean \
); \
create table rom ( \
	id_rom	integer primary key autoincrement, \
	name	text not null, \
	size	integer, \
	crc		text, \
	sha1	text, \
	merge	integer, \
	id_game	integer references game (id_game) on delete cascade \
); \
create table game_cloneof_romof ( \
	id_game integer not null, \
	cloneof text, \
	romof text \
)";

// create index idx_manufacturer on manufacturer(name);
// create index idx_game on game (name);
// create index idx_sourcefile on sourcefile(name);

#endif

class modelomame {
	struct vo_rom {
		string		name;
		uint32_t	size;
		string		crc;
		string		sha1;

		bool operator < (const struct vo_rom& a) const {
			if (name < a.name) return true;
			return false;
		}
	};

public:
	modelomame():cacheManufacturer(1000),cacheGame(200),cacheRom(10000),cacheSourcefile(1000) {};
	virtual ~modelomame() {};

	void abrir(const string& archivo) { 
		try {
			bd = GuruSQLite::conectar(archivo, ddl);
		} catch(GuruSQLite::GuruSQLiteException& e) {
			cout << e.what() << endl;
		}
	};

	void cerrar() {
		bd.desconectar();
	};

	void insertar_cloneof_romof(modelodatosmame::game& game) {

		stringstream ss;

		ss << "insert into game_cloneof_romof (id_game";

		if (!game.cloneof.empty()) ss << ", cloneof";
		
		if (!game.romof.empty()) ss << ", romof";
		
		ss << ") values (";

		ss << game.id;

		if (!game.cloneof.empty()) ss << ", " << GuruSQLite::comillas(game.cloneof);

		if (!game.romof.empty()) ss << ", " << GuruSQLite::comillas(game.romof);

		ss << ")";

		try {
			bd.exec(ss.str());
		} catch(GuruSQLite::GuruSQLiteException& e) {
			cout << "insertar_cloneof_romof:" << e.what() << "(" << ss.str() << ")" << endl;
		};

	};

	uint64_t id_game(const string& game_name) {
		uint64_t id=0;

		try {
			id = cacheGame(game_name);
		} catch (std::exception&) {
			try {
				id = GuruSQLite::resultado(bd.ejecutarEX("select id_game from game where name = \"" + game_name + "\""))->getUInt32(0, 0);
			
				if (id == 0) 
					throw runtime_error("Game sin ID");
				else
					cacheGame.insertar(game_name, id);

			} catch(GuruSQLite::GuruSQLiteException& e) {
				cout << "id_game: " << e.what() << endl;
			} catch (std::exception& e) {
				cout << "id_game: " << e.what() << endl;
			};
		}
		return id;
	}

	uint64_t insertar_driver(modelodatosmame::game& game) {
		return 0;

		stringstream ss;

		ss << "insert into driver (status, emulation, color, sound, graphic, cocktail, protection, savestate) values ("

		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.status) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.emulation) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.color) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.sound) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.graphic) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.cocktail) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.protection) << ", "
		<< GuruSQLiteAlgo::id(bd, cacheText, "text", "text", "id_text", game.driver.savestate) << ")";

		try {
			bd.exec(ss.str());
			game.driver.id = bd.int_sqlite3_last_insert_rowid();
		} catch(GuruSQLite::GuruSQLiteException& e) {
			cout << "insertar_driver:" << e.what() << "(" << ss.str() << ")" << endl;
			return 0;
		};

		return game.driver.id;
	}

	bool insertar_game(modelodatosmame::game& game) {

		if (game.isbios || game.isdevice) 
			return false;

		bd.exec("BEGIN TRANSACTION");

		stringstream ss;

		ss << "insert into game (name, year, description, manufacturer, sourcefile, driver";

		if (!game.cloneof.empty()) ss << ", cloneof";
		
		if (!game.romof.empty()) ss << ", romof";

		ss << ", runnable";
		
		ss << ") values (";

		ss << GuruSQLite::comillas(game.name) << "," 
		<< game.year << "," 
		<< GuruSQLite::comillas(game.description) << ","
		<< GuruSQLiteAlgo::id(bd, cacheManufacturer, "manufacturer", "name", "id_manufacturer", game.manufacturer)  << "," 
		<< GuruSQLiteAlgo::id(bd, cacheSourcefile, "sourcefile", "name", "id_sourcefile", game.sourcefile)  << "," 
		<< insertar_driver(game);

		if (!game.cloneof.empty()) ss << ", " << GuruSQLite::comillas(game.cloneof);

		if (!game.romof.empty()) ss << ", " << GuruSQLite::comillas(game.romof);

		ss << "," << (game.runnable) ? "1" : "0";

		ss << ")";

		try {
			bd.exec(ss.str());
			game.id = bd.int_sqlite3_last_insert_rowid();
//			cacheGame.insertar(game.name, game.id);

//			insertar_roms(game);

			insertar_roms_sin_id(game);

			if (!game.cloneof.empty() || !game.romof.empty()) insertar_cloneof_romof(game);

		} catch(GuruSQLite::GuruSQLiteException& e) {
			cout << "insertar_game:" << e.what() << "(" << ss.str() << ")" << endl;
		};

		bd.exec("END TRANSACTION");

		return true;
	};

	uint64_t id_rom(modelodatosmame::rom& rom) {
		uint64_t id=0;

		struct vo_rom a = {rom.name, rom.size, rom.crc, rom.sha1};

		try {
			id = cacheRom(a);
		} catch (GuruCacheException&) {
			try {
				id = GuruSQLite::resultado(bd.ejecutarEX("select id_rom from rom where name = " + GuruSQLite::comillas(rom.name) + " and size=" + GuruStringAlgo::int64astr(rom.size) + " and crc=" + GuruSQLite::comillas(rom.crc) + "and sha1=" + GuruSQLite::comillas(rom.sha1)))->getUInt32(0, 0);

				if (id != 0) cacheRom.insertar(a, id);
			} catch(GuruSQLite::GuruSQLiteException&) {};
		}

		return id;
	}

	bool insertar_roms(modelodatosmame::game& game) {

		string consulta;

		for (vector<modelodatosmame::rom>::iterator it=game.roms.begin();it!=game.roms.end();it++) {
			if (!it->merge.empty()) continue;

			uint64_t id = id_rom(*it);

			if (id == 0) {
				
				consulta = "insert into rom (name, size, crc, sha1) values (";
				consulta += GuruSQLite::comillas(it->name) + ",";
				consulta += GuruStringAlgo::itos(it->size) + ",";
				consulta += GuruSQLite::comillas(it->crc) + ",";
				consulta += GuruSQLite::comillas(it->sha1) + ")";

				try {
					bd.exec(consulta);
					it->id = bd.int_sqlite3_last_insert_rowid();

					struct vo_rom a = {it->name, it->size, it->crc, it->sha1};
					cacheRom.insertar(a, it->id);
					
					bd.exec("insert into rom_game (id_game, id_rom) values (" + GuruStringAlgo::itos(game.id) + "," + GuruStringAlgo::itos(it->id) + ")");
				} catch(GuruSQLite::GuruSQLiteException& e) {
					cout << "insertar_roms sin id:" << e.what() << "(" << consulta << ")" << endl;
				};
			} else {
				try {
					bd.exec("insert into rom_game (id_game, id_rom) values (" + GuruStringAlgo::itos(game.id) + "," + GuruStringAlgo::itos(id) + ")");
				} catch(GuruSQLite::GuruSQLiteException& e) {
					cout << "insertar_roms con id:" << e.what() << "(" << consulta << ")" << endl;
				};
			}
		}

		return true;
	};

#if defined MAMESQLITE_V1
	bool insertar_roms_sin_id(modelodatosmame::game& game) {

		stringstream ss;

		for (vector<modelodatosmame::rom>::iterator it=game.roms.begin();it!=game.roms.end();it++) {
			if (!it->merge.empty()) continue;

			ss.str("");
			ss << "insert into rom (name, size, crc, sha1) values " << "(" 
				<< GuruSQLite::comillas(it->name) << "," 
				<< it->size << "," 
				<< GuruSQLite::comillas(it->crc) << "," 
				<< GuruSQLite::comillas(it->sha1) << ")";

			try {
				bd.exec(ss.str());
				it->id = bd.int_sqlite3_last_insert_rowid();

				ss.str("");
				ss << "insert into rom_game (id_game, id_rom) values (" << game.id << "," << it->id << ")";
				bd.exec(ss.str());
			} catch(GuruSQLite::GuruSQLiteException& e) {
					cout << "insertar_roms sin id:" << e.what() << "(" << ss.str() << ")" << endl;
			};
		}

		return true;
	};
#endif

#if defined MAMESQLITE_V2
	bool insertar_roms_sin_id(modelodatosmame::game& game) {

		string consulta;

		for (vector<modelodatosmame::rom>::iterator it=game.roms.begin();it!=game.roms.end();it++) {
			if (!it->merge.empty()) continue;

			consulta = "insert into rom (name, size, crc, sha1, id_game) values (";
			consulta += GuruSQLite::comillas(it->name) + ",";
			consulta += GuruStringAlgo::itos(it->size) + ",";
			consulta += GuruSQLite::comillas(it->crc) + ",";
			consulta += GuruSQLite::comillas(it->sha1) + "," + GuruStringAlgo::itos(game.id) + ")";

			try {
				bd.exec(consulta);
				it->id = bd.int_sqlite3_last_insert_rowid();
			} catch(GuruSQLite::GuruSQLiteException& e) {
					cout << "insertar_roms sin id:" << e.what() << "(" << consulta << ")" << endl;
			};
		}

		return true;
	};
#endif

protected:
	GuruCacheLRU<string, uint64_t>			cacheManufacturer;
	GuruCacheLRU<string, uint64_t>			cacheSourcefile;
	GuruCacheLRU<string, uint64_t>			cacheText;
	GuruCacheLRU<string, uint64_t>			cacheGame;
	GuruCacheLRU<struct vo_rom, uint64_t>	cacheRom;
	GuruSQLite::bd							bd;
};

#endif
