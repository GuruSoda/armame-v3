#ifndef __LISTXML2SQLITEV2_HPP__
#define __LISTXML2SQLITEV2_HPP__

#include <string>
#include <set>
#include <map>
#include <future>

#include <GuruCompat.h>
#include <GuruSQLite.hpp>
#include <GuruID.hpp>
#include <GuruDirectorio.hpp>

#include <modelodatosmame.hpp>
#include <parserxml.hpp>

static const char* listxml2sqlitev2_ddl = " \
PRAGMA synchronous=off;\
PRAGMA foreign_keys=on;\
drop table if exists version; \
create table version ( \
	id_version	integer primary key autoincrement, \
	build		text not null, \
	debug		text not null, \
	mameconfig	text not null \
); \
drop table if exists text; \
create table text ( \
	id_text integer primary key autoincrement, \
	text	text not null \
); \
drop table if exists manufacturer; \
create table manufacturer ( \
	id_manufacturer integer primary key autoincrement, \
	name			text not null \
); \
drop table if exists sourcefile; \
create table sourcefile ( \
	id_sourcefile	integer primary key autoincrement, \
	name			text not null \
); \
drop table if exists game; \
create table game ( \
	id_game 	integer primary key autoincrement, \
	name		text, \
	year		integer, \
	description	text, \
	manufacturer integer references manufacturer (id_manufacturer) on delete cascade, \
	sourcefile   integer references sourcefile (id_sourcefile) on delete cascade, \
	cloneof		text, \
	romof		text, \
	sampleof	text, \
	runnable	boolean, \
	isbios		boolean, \
	isdevice	boolean, \
	ismechanical	boolean \
); \
drop table if exists driver; \
create table driver ( \
	id_game		integer references game (id_game) on delete cascade, \
	status		integer references text (id_text) on delete cascade, \
	emulation	integer references text (id_text) on delete cascade, \
	color 		integer references text (id_text) on delete cascade, \
	sound		integer references text (id_text) on delete cascade, \
    graphic		integer references text (id_text) on delete cascade, \
    cocktail 	integer references text (id_text) on delete cascade, \
    protection	integer references text (id_text) on delete cascade, \
    savestate 	integer references text (id_text) on delete cascade, \
	palettesize integer references text (id_text) on delete cascade \
); \
drop table if exists biosset; \
create table biosset ( \
	id_biosset	integer primary key autoincrement, \
	name		text not null, \
	description	text not null, \
	_default	text not null \
); \
drop table if exists rom; \
create table rom ( \
	id_rom	integer primary key autoincrement, \
	name	text not null, \
	bios	text, \
	size	integer, \
	crc		text, \
	sha1	text, \
	merge	integer, \
	region  integer references text (id_text) on delete cascade, \
	offset	text, \
	status	integer references text (id_text) on delete cascade, \
	optional text \
); \
drop table if exists disk; \
create table disk ( \
	id_disk integer primary key autoincrement, \
	name	text not null, \
	sha1	text, \
	merge	text, \
	region	text, \
	_index	text, \
	writable text, \
	status	text, \
	optional text \
); \
drop table if exists chip; \
create table chip ( \
	id_chip integer primary key autoincrement, \
	name	text not null, \
	tag		text, \
	type	text, \
	clock	text \
); \
drop table if exists dipswitch; \
create table dipswitch ( \
	id_dipswitch integer primary key autoincrement, \
	name	text, \
	tag		text, \
	mask	text \
); \
drop table if exists dipvalue; \
create table dipvalue ( \
	id_dipvalue integer primary key autoincrement, \
	name	text, \
	value	text, \
	_default	text \
); \
drop table if exists configuration; \
create table configuration ( \
	id_configuration integer primary key autoincrement, \
	name	text, \
	tag		text, \
	mask	text \
); \
drop table if exists confsetting; \
create table confsetting ( \
	id_confsetting integer primary key autoincrement, \
	name	text, \
	value	text, \
	_default	text \
); \
drop table if exists slot; \
create table slot ( \
	id_slot integer primary key autoincrement, \
	name	text \
); \
drop table if exists slotoption; \
create table slotoption ( \
	id_slotoption integer primary key autoincrement, \
	name	text, \
	devname	text, \
	_default	text \
); \
drop table if exists input; \
create table input ( \
	id_input integer primary key autoincrement, \
	service text, \
	tilt text, \
	players text, \
	coins text \
); \
drop table if exists control; \
create table control ( \
	id_control integer primary key autoincrement, \
	type text, \
	player text, \
	buttons text, \
	reqbuttons text, \
	minimum text, \
	maximum text, \
	sensitivity text, \
	keydelta text, \
	reverse text, \
	ways text, \
	ways2 text, \
	ways3 text \
); \
drop table if exists device; \
create table device ( \
	id_device integer primary key autoincrement, \
	type	text, \
	tag		text, \
	fixed_image	text, \
	mandatory	text, \
	interface	text \
); \
drop table if exists instance; \
create table instance ( \
	id_instance integer primary key autoincrement, \
	name	text, \
	briefname	text \
); \
drop table if exists extension; \
create table extension ( \
	id_extension integer primary key autoincrement, \
	name	text \
); \
drop table if exists port; \
create table port ( \
	id_port integer primary key autoincrement, \
	tag	text \
); \
drop table if exists analog; \
create table analog ( \
	id_analog integer primary key autoincrement, \
	mask	text \
); \
drop table if exists display; \
create table display ( \
	id_game		integer primary key autoincrement, \
	tag			text, \
	type		text, \
	rotate		integer, \
	flipx		text, \
	width		integer, \
	height		integer, \
	refresh		text, \
	pixclock	text, \
	htotal		integer, \
	hbend		integer, \
	hbstart		integer, \
	vtotal		integer, \
	vbend		integer, \
	vbstart		integer \
); \
drop table if exists softwarelist; \
create table softwarelist ( \
	id_softwarelist integer primary key autoincrement, \
	name	text, \
	status	text, \
	filter	text \
); \
drop table if exists adjuster; \
create table adjuster ( \
	id_adjuster integer primary key autoincrement, \
	name	text, \
	_default	text \
); \
drop table if exists sound; \
create table sound ( \
	id_sound integer primary key autoincrement, \
	channels integer \
); \
drop table if exists device_ref; \
create table device_ref ( \
	id_game		integer references game (id_game) on delete cascade, \
	name		integer references text (id_text) on delete cascade \
); \
drop table if exists sample; \
create table sample ( \
	id_game		integer references game (id_game) on delete cascade, \
	name		integer references text (id_text) on delete cascade \
); \
drop table if exists ramoption; \
create table ramoption ( \
	id_ramoption integer primary key autoincrement, \
	_default	integer \
); \
drop table if exists game_biosset; \
create table game_biosset ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_biosset	integer references biosset (id_biosset) on delete cascade \
); \
drop table if exists game_adjuster; \
create table game_adjuster ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_adjuster	integer references adjuster (id_adjuster) on delete cascade \
); \
drop table if exists game_sound; \
create table game_sound ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_sound	integer references sound (id_sound) on delete cascade \
); \
drop table if exists game_softwarelist; \
create table game_softwarelist ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_softwarelist	integer references softwarelist (id_softwarelist) on delete cascade \
); \
drop table if exists game_rom; \
create table game_rom ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_rom		integer references rom (id_rom) on delete cascade \
); \
drop table if exists game_chip; \
create table game_chip ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_chip		integer references chip (id_chip) on delete cascade \
); \
drop table if exists game_device; \
create table game_device ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_device	integer references device (id_device) on delete cascade \
); \
drop table if exists device_instance; \
create table device_instance ( \
	id_device	integer references device (id_device) on delete cascade, \
	id_instance	integer references instance (id_instance) on delete cascade \
); \
drop table if exists device_extension; \
create table device_extension ( \
	id_device	integer references device (id_device) on delete cascade, \
	id_extension	integer references extension (id_extension) on delete cascade \
); \
drop table if exists game_dipswitch; \
create table game_dipswitch ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_dipswitch		integer references dipswitch (id_dipswitch) on delete cascade \
); \
drop table if exists dipswitch_dipvalue; \
create table dipswitch_dipvalue ( \
	id_dipswitch	integer references dipswitch (id_dipswitch) on delete cascade, \
	id_dipvalue		integer references dipvalue (id_dipvalue) on delete cascade \
); \
drop table if exists game_configuration; \
create table game_configuration ( \
	id_game			integer references game (id_game) on delete cascade, \
	id_configuration	integer references configuration (id_configuration) on delete cascade \
); \
drop table if exists configuration_confsetting; \
create table configuration_confsetting ( \
	id_configuration	integer references configuration (id_configuration) on delete cascade, \
	id_confsetting		integer references confsetting (id_confsetting) on delete cascade \
); \
drop table if exists game_slot; \
create table game_slot ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_slot		integer references slot (id_slot) on delete cascade \
); \
drop table if exists slot_slotoption; \
create table slot_slotoption ( \
	id_slot			integer references slot (id_slot) on delete cascade, \
	id_slotoption	integer references slotoption (id_slotoption) on delete cascade \
); \
drop table if exists game_port; \
create table game_port ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_port		integer references port (id_port) on delete cascade \
); \
drop table if exists port_analog; \
create table port_analog ( \
	id_port			integer references port (id_port) on delete cascade, \
	id_analog		integer references analog (id_analog) on delete cascade \
); \
drop table if exists game_ramoption; \
create table game_ramoption ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_ramoption	integer references ramoption (id_ramoption) on delete cascade \
); \
drop table if exists game_input; \
create table game_input ( \
	id_game			integer references game (id_game) on delete cascade, \
	id_input		integer references input (id_input) on delete cascade \
); \
drop table if exists input_control; \
create table input_control ( \
	id_input		integer references input (id_input) on delete cascade, \
	id_control		integer references control (id_control) on delete cascade \
); \
drop table if exists game_disk; \
create table game_disk ( \
	id_game		integer references game (id_game) on delete cascade, \
	id_disk		integer references disk (id_disk) on delete cascade \
);";

class listxml2SQLiteV2: public GuruMAME::GuruParserXML {
protected:
	string nombre_bd;

	set<modelodatosmame::rom>			roms;					// todas las roms existentes en el mame
	set<modelodatosmame::disk>			disks;					// todos los discos existentes en el mame
	set<modelodatosmame::chip>			chips;					// todos los chips existentes en el mame
	set<modelodatosmame::biosset>		biossets;				// todos los biossets existentes en el mame
	set<modelodatosmame::dipvalue>		dipvalues;				// todos los dipvalues existentes en el mame
	set<modelodatosmame::dipswitch>		dipswitchs;				// todos los dipvalues existentes en el mame
	set<modelodatosmame::softwarelist>	softwarelists;			// todos los softwarelist existentes en el mame
	set<modelodatosmame::adjuster>		adjusters;				// todos los adjuster existentes en el mame
	set<modelodatosmame::configuration>	configurations;			// todos los configuration existentes en el mame
	set<modelodatosmame::confsetting>	confsettings;			// todos los confsettings existentes en el mame
	set<modelodatosmame::slot>			slots;					// todos los slot existentes en el mame
	set<modelodatosmame::slotoption>	slotoptions;			// todos los slotoptions existentes en el mame
	set<modelodatosmame::port>			ports;					// todos los ports existentes en el mame
	set<modelodatosmame::analog>		analogs;				// todos los analogs existentes en el mame
	set<modelodatosmame::device>		devices;				// todos los devices existentes en el mame
	set<modelodatosmame::instance>		instances;				// todos los instances existentes en el mame
	set<modelodatosmame::extension>		extensions;				// todos los extensions existentes en el mame
	set<modelodatosmame::input>			inputs;					// todos los inputs existentes en el mame
	set<modelodatosmame::control>		controls;				// todos los controls existentes en el mame
	set<modelodatosmame::ramoption>		ramoptions;				// todos los ramoptions existentes en el mame
	set<modelodatosmame::sound>			sounds;					// todos los sounds existentes en el mame

	// uno a muchos
	std::map<uint64_t, vector<uint64_t> >	game_rom;				// id game -> id's roms | une la table game con rom
	std::map<uint64_t, vector<uint64_t> >	game_disk;				// id game -> id disk | une la tabla game con la tabla disk
	std::map<uint64_t, vector<uint64_t> >	game_chip;				// id game -> id chip | une la tabla game con la tabla chip
	std::map<uint64_t, vector<uint64_t> >	game_biosset;			// id game -> id biosset | une la tabla game con la tabla biosset
	std::map<uint64_t, vector<uint64_t> >	game_dipswitch;			// id game -> id dipswitch | une la tabla game con la tabla dipswitch
	std::map<uint64_t, vector<uint64_t> >	dipswitch_dipvalue;		// id dipswitch -> id dipvalue | une la tabla dipswitch con la tabla dipvalue
	std::map<uint64_t, vector<uint64_t> >	game_adjuster;			// id game -> id adjuster | une la tabla game con la tabla adjuster
	std::map<uint64_t, vector<uint64_t> >	game_softwarelist;		// id game -> id adjuster | une la tabla game con la tabla adjuster
	std::map<uint64_t, vector<uint64_t> >	game_configuration;		// id game -> id configuration | une la tabla game con la tabla configuration
	std::map<uint64_t, vector<uint64_t> >	configuration_confsetting;	// id configuration -> id confsetting | une la tabla configuration con la tabla confsetting
	std::map<uint64_t, vector<uint64_t> >	game_slot;				// id game -> id slot | une la tabla game con la tabla slot
	std::map<uint64_t, vector<uint64_t> >	slot_slotoption;		// id configuration -> id slotoption | une la tabla slot con la tabla slotoption
	std::map<uint64_t, vector<uint64_t> >	game_port;				// id game -> id port | une la tabla game con la tabla port
	std::map<uint64_t, vector<uint64_t> >	port_analog;			// id port -> id analog | une la tabla port con la tabla analog
	std::map<uint64_t, vector<uint64_t> >	game_device;			// id game -> id device | une la tabla game con la tabla device
	std::map<uint64_t, vector<uint64_t> >	device_instance;		// id device -> id instance | une la tabla device con la tabla instance
	std::map<uint64_t, vector<uint64_t> >	device_extension;		// id device -> id extension | une la tabla device con la tabla extension
	std::map<uint64_t, vector<uint64_t> >	game_input;				// id game -> id input | une la tabla game con la tabla input
	std::map<uint64_t, vector<uint64_t> >	input_control;			// id input -> id control | une la tabla input con la tabla control
	std::map<uint64_t, vector<uint64_t> >	game_ramoption;			// id game -> id ramoption | une la tabla game con la tabla ramoption
	std::map<uint64_t, vector<uint64_t> >	game_sound;			// id game -> id ramoption | une la tabla game con la tabla ramoption

	// uno a uno
	std::map<uint64_t, uint64_t>			game_manufacturer;		// id game -> id manufacturer
	std::map<uint64_t, uint64_t>			game_sourcefile;		// id game -> id sourcefile
	std::map<uint64_t, uint64_t>			rom_region;				// id rom -> id text (nombre de la region)
	std::map<uint64_t, uint64_t>			rom_status;				// id rom -> id text (nombre del status)

// para generar id's
	GuruID_threadsafe<std::string>						table_manufacturer;
	GuruID_threadsafe<std::string>						table_sourcefile;
	GuruID_threadsafe<std::string>						table_text;

	uint64_t total = 0; // total de maquinas

	typedef struct {
		uint64_t id_game;

		int status = 0;
		int emulation = 0;
		int color = 0;
		int sound = 0;
		int graphic = 0;
		int cocktail = 0;
		int protection = 0;
		int savestate = 0;
		int palettesize = 0;
	} reg_driver;

	typedef struct {
		uint64_t id_device_ref;

		int name = 0;
	}reg_device_ref;

	typedef struct {
		uint64_t id_sample;

		int name = 0;
	}reg_sample;

	std::list<modelodatosmame::game>		table_game;
	std::list<reg_driver>					table_driver;
	std::list<modelodatosmame::display>		table_display;
	std::list<reg_device_ref>				table_device_ref;
	std::list<reg_sample>					table_sample;

	modelodatosmame::version version_mame;
public:
	listxml2SQLiteV2() {}
	virtual ~listxml2SQLiteV2() {}

	void game(modelodatosmame::game& machine) {

		std::function<void()> insert_roms = [&] () {
			vector<uint64_t> id_rom;
			for (vector<modelodatosmame::rom>::iterator it = machine.roms.begin(), itend = machine.roms.end(); it != itend; ++it) {
				rom_region.insert(make_pair(it->id, table_text.id(it->region)));
				it->region.clear();

				rom_status.insert(make_pair(it->id, table_text.id(it->status)));
				it->status.clear();

				id_rom.push_back(roms.insert(*it).first->id);
			}

			game_rom.insert(make_pair(machine.id, id_rom));
		};

		std::future<void> rom_async(std::async(insert_roms));
		rom_async.get();

		{
			reg_driver d;

			d.id_game = machine.id;
			d.status = table_text.id(machine.driver.status);
			d.emulation = table_text.id(machine.driver.emulation);
			d.color = table_text.id(machine.driver.color);
			d.sound = table_text.id(machine.driver.sound);
			d.graphic = table_text.id(machine.driver.graphic);
			d.cocktail = table_text.id(machine.driver.cocktail);
			d.protection = table_text.id(machine.driver.protection);
			d.savestate = table_text.id(machine.driver.savestate);
			d.palettesize = table_text.id(machine.driver.palettesize);

			table_driver.push_back(d);
		}

		game_manufacturer.insert(make_pair(machine.id, table_manufacturer.id(machine.manufacturer)));
		machine.manufacturer.clear();

		game_sourcefile.insert(make_pair(machine.id, table_sourcefile.id(machine.sourcefile)));
		machine.sourcefile.clear();

		std::future<void> disk_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_disk;
			for (vector<modelodatosmame::disk>::iterator it = machine.disks.begin(), itend = machine.disks.end(); it != itend; ++it)
				id_disk.push_back(disks.insert(*it).first->id);

			game_disk.insert(make_pair(machine.id, id_disk));
		}));

		std::future<void> biosset_async(std::async(std::launch::async, [&] () {
			vector<uint64_t> id_biosset;
			for (vector<modelodatosmame::biosset>::iterator it = machine.biossets.begin(), itend = machine.biossets.end(); it != itend; ++it)
				id_biosset.push_back(biossets.insert(*it).first->id);

			game_biosset.insert(make_pair(machine.id, id_biosset));
		} ));

		std::future<void> adjuster_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_adjuster;
			for (vector<modelodatosmame::adjuster>::iterator it = machine.adjusters.begin(), itend = machine.adjusters.end(); it != itend; ++it)
				id_adjuster.push_back(adjusters.insert(*it).first->id);

			game_adjuster.insert(make_pair(machine.id, id_adjuster));
		}));

		std::future<void> softwarelist_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_softwarelist;
			for (vector<modelodatosmame::softwarelist>::iterator it = machine.softwarelists.begin(), itend = machine.softwarelists.end(); it != itend; ++it)
				id_softwarelist.push_back(softwarelists.insert(*it).first->id);

			game_softwarelist.insert(make_pair(machine.id, id_softwarelist));
		}));

		std::future<void> chip_async(std::async(std::launch::async, [&] () {
			vector<uint64_t> id_chip;
			for (vector<modelodatosmame::chip>::iterator it = machine.chips.begin(), itend = machine.chips.end(); it != itend; ++it)
				id_chip.push_back(chips.insert(*it).first->id);

			game_chip.insert(make_pair(machine.id, id_chip));
		}));

		machine.display.id = machine.id;
		table_display.push_back(machine.display);

		std::future<void> device_ref_async(std::async(std::launch::async, [&]() {
			reg_device_ref dr;
			dr.id_device_ref = machine.id;
			for (vector<modelodatosmame::device_ref>::iterator it = machine.device_refs.begin(), itend = machine.device_refs.end(); it != itend; ++it) {
				dr.name = table_text.id(it->name);
				table_device_ref.push_back(dr);
			}
		}));

		std::future<void> sample_async(std::async(std::launch::async, [&]() {
			reg_sample s;
			s.id_sample = machine.id;
			for (vector<modelodatosmame::sample>::iterator it = machine.samples.begin(), itend = machine.samples.end(); it != itend; ++it) {
				s.name = table_text.id(it->name);
				table_sample.push_back(s);
			}
		}));

		std::future<void> dipswitch_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_dipswitch;
			for (vector<modelodatosmame::dipswitch>::iterator it = machine.dipswitchs.begin(), itend = machine.dipswitchs.end(); it != itend; ++it) {

				modelodatosmame::dipswitch dip;

				dip.id = it->id;
				dip.name = it->name;
				dip.tag = it->tag;
				dip.mask = it->mask;

				auto a = dipswitchs.insert(dip).first->id;
				id_dipswitch.push_back(a);

				vector<uint64_t> id_dipvalue;
				for (vector<modelodatosmame::dipvalue>::iterator it2 = it->dipvalues.begin(), it2end = it->dipvalues.end(); it2 != it2end; ++it2) {
					id_dipvalue.push_back(dipvalues.insert(*it2).first->id);
				}
				dipswitch_dipvalue.insert(make_pair(a, id_dipvalue));
			}

			game_dipswitch.insert(make_pair(machine.id, id_dipswitch));
		}));

		std::future<void> configuration_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_configuration;
			for (vector<modelodatosmame::configuration>::iterator it = machine.configurations.begin(), itend = machine.configurations.end(); it != itend; ++it) {

				modelodatosmame::configuration conf;

				conf.id = it->id;
				conf.name = it->name;
				conf.tag = it->tag;
				conf.mask = it->mask;

				auto a = configurations.insert(conf).first->id;
				id_configuration.push_back(a);

				vector<uint64_t> id_confsetting;
				for (vector<modelodatosmame::confsetting>::iterator it2 = it->confsettings.begin(), it2end = it->confsettings.end(); it2 != it2end; ++it2) {
					id_confsetting.push_back(confsettings.insert(*it2).first->id);
				}
				configuration_confsetting.insert(make_pair(a, id_confsetting));
			}

			game_configuration.insert(make_pair(machine.id, id_configuration));
		}));

		std::future<void> slot_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_slot;
			for (vector<modelodatosmame::slot>::iterator it = machine.slots.begin(), itend = machine.slots.end(); it != itend; ++it) {

				modelodatosmame::slot conf;

				conf.id = it->id;
				conf.name = it->name;

				auto a = slots.insert(conf).first->id;
				id_slot.push_back(a);

				vector<uint64_t> id_slotoption;
				for (vector<modelodatosmame::slotoption>::iterator it2 = it->slotoptions.begin(), it2end = it->slotoptions.end(); it2 != it2end; ++it2) {
					id_slotoption.push_back(slotoptions.insert(*it2).first->id);
				}
				slot_slotoption.insert(make_pair(a, id_slotoption));
			}

			game_slot.insert(make_pair(machine.id, id_slot));
		}));

		std::future<void> port_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_port;
			for (vector<modelodatosmame::port>::iterator it = machine.ports.begin(), itend = machine.ports.end(); it != itend; ++it) {

				modelodatosmame::port conf;

				conf.id = it->id;
				conf.tag = it->tag;

				auto a = ports.insert(conf).first->id;
				id_port.push_back(a);

				vector<uint64_t> id_analog;
				for (vector<modelodatosmame::analog>::iterator it2 = it->analogs.begin(), it2end = it->analogs.end(); it2 != it2end; ++it2) {
					id_analog.push_back(analogs.insert(*it2).first->id);
				}
				port_analog.insert(make_pair(a, id_analog));
			}

			game_port.insert(make_pair(machine.id, id_port));
		}));

		std::future<void> device_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_device;
			for (vector<modelodatosmame::device>::iterator it = machine.devices.begin(), itend = machine.devices.end(); it != itend; ++it) {

				modelodatosmame::device conf;

				conf.id = it->id;
				conf.type = it->tag;
				conf.tag = it->tag;
				conf.fixed_image = it->fixed_image;
				conf.mandatory = it->mandatory;
				conf._interface = it->_interface;

				auto a = devices.insert(conf).first->id;
				id_device.push_back(a);

				vector<uint64_t> id_instance;
				for (vector<modelodatosmame::instance>::iterator it2 = it->instances.begin(), it2end = it->instances.end(); it2 != it2end; ++it2) {
					id_instance.push_back(instances.insert(*it2).first->id);
				}
				device_instance.insert(make_pair(a, id_instance));

				vector<uint64_t> id_extension;
				for (vector<modelodatosmame::extension>::iterator it2 = it->extensions.begin(), it2end = it->extensions.end(); it2 != it2end; ++it2) {
					id_extension.push_back(extensions.insert(*it2).first->id);
				}
				device_extension.insert(make_pair(a, id_extension));
			}

			game_device.insert(make_pair(machine.id, id_device));
		}));

		std::future<void> input_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_input;
			for (vector<modelodatosmame::input>::iterator it = machine.inputs.begin(), itend = machine.inputs.end(); it != itend; ++it) {

				modelodatosmame::input conf;

				conf.id = it->id;
				conf.service = it->service;
				conf.tilt = it->tilt;
				conf.players = it->players;
				conf.coins = it->coins;

				auto a = inputs.insert(conf).first->id;
				id_input.push_back(a);

				vector<uint64_t> id_control;
				for (vector<modelodatosmame::control>::iterator it2 = it->controls.begin(), it2end = it->controls.end(); it2 != it2end; ++it2) {
					id_control.push_back(controls.insert(*it2).first->id);
				}
				input_control.insert(make_pair(a, id_control));
			}

			game_input.insert(make_pair(machine.id, id_input));
		}));

		std::future<void> ramoption_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_ramoption;
			for (vector<modelodatosmame::ramoption>::iterator it = machine.ramoptions.begin(), itend = machine.ramoptions.end(); it != itend; ++it) {
				id_ramoption.push_back(ramoptions.insert(*it).first->id);
			}

			game_ramoption.insert(make_pair(machine.id, id_ramoption));
		}));

		std::future<void> sound_async(std::async(std::launch::async, [&]() {
			vector<uint64_t> id_sound;
			for (vector<modelodatosmame::sound>::iterator it = machine.sounds.begin(), itend = machine.sounds.end(); it != itend; ++it) {
				id_sound.push_back(sounds.insert(*it).first->id);
			}

			game_sound.insert(make_pair(machine.id, id_sound));
		}));

		disk_async.get();
		biosset_async.get();
		adjuster_async.get();
		chip_async.get();
		device_ref_async.get();
		sample_async.get();
		dipswitch_async.get();
		configuration_async.get();
		slot_async.get();
		port_async.get();
		device_async.get();
		input_async.get();
		ramoption_async.get();
		sound_async.get();

		machine.disks.clear();
		machine.roms.clear();
		machine.driver.clear();
		machine.display.clear();
		machine.chips.clear();
		machine.device_refs.clear();
		machine.biossets.clear();
		machine.dipswitchs.clear();
		machine.samples.clear();
		machine.inputs.clear();
		machine.softwarelists.clear();
		machine.configurations.clear();
		machine.adjusters.clear();
		machine.slots.clear();
		machine.devices.clear();
		machine.ports.clear();

		table_game.push_back(machine);

		//			cout << nuevo.name << endl;
// 		cout << "\r" << progreso();

		total++;
	}

	void version(const GuruMAME::version& ver) {
		this->version_mame.build = ver.build;
		this->version_mame.debug = ver.debug;
		this->version_mame.mameconfig = ver.mameconfig;
	};

	void importar_a_base_v2() {
		uint32_t total = 0;

		GuruSQLite::bd base;

		try {
			std::string consulta;

			if (nombre_bd.empty()) nombre_bd = "mame.sqlite";

			cout << "Creando base..." << endl;
			base = GuruSQLite::conectar(nombre_bd, listxml2sqlitev2_ddl, GuruSQLite::bd::modo::crear | GuruSQLite::bd::modo::lecturaEscritura);

			cout << "Comenzando transaccion..." << endl;
			base.exec("BEGIN TRANSACTION");

			cout << "Insertando version..." << endl;
			consulta = "insert into version (build, debug, mameconfig) values (" + GuruStringAlgo::comillas(version_mame.build) + ", " + GuruStringAlgo::comillas(version_mame.debug) + ", " + GuruStringAlgo::comillas(version_mame.mameconfig) + ")";
			base.exec(consulta);

			cout << "Insertando text [" << table_text.reverse_src().size() << "]... "; total = 0;
			for (map<unsigned long, typename map<std::string, unsigned long>::iterator>::iterator it = table_text.reverse_src().begin(), itend = table_text.reverse_src().end(); it != itend; ++it) {
				consulta = "insert into text (id_text, text) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::comillas(it->second->first) + ")";
				base.exec(consulta);
				total++;
			}
			cout << total << endl;

			cout << "Insertando manufacturer (" << table_manufacturer.reverse_src().size() << ")... "; total = 0;
			for (map<unsigned long, typename map<std::string, unsigned long>::iterator>::iterator it = table_manufacturer.reverse_src().begin(), itend = table_manufacturer.reverse_src().end(); it != itend; ++it) {
				consulta = "insert into manufacturer (id_manufacturer, name) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::comillas(it->second->first) + ")";
				base.exec(consulta);
				total++;
			}
			cout << total << endl;

			cout << "Insertando sourcefile (" << table_sourcefile.reverse_src().size() << ")... "; total = 0;
			for (map<unsigned long, typename map<std::string, unsigned long>::iterator>::iterator it = table_sourcefile.reverse_src().begin(), itend = table_sourcefile.reverse_src().end(); it != itend; ++it) {
				consulta = "insert into sourcefile (id_sourcefile, name) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::comillas(it->second->first) + ")";
				base.exec(consulta);
				total++;
			}
			cout << total << endl;

			{
				cout << "Insertando game (" << table_game.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game (id_game, name, year, description, manufacturer, sourcefile, cloneof, romof, sampleof, runnable, isbios, isdevice, ismechanical) values (?,?,?,?,?,?,?,?,?,?,?,?,?)"));
				for (std::list<modelodatosmame::game>::iterator it = table_game.begin(), itend = table_game.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->year);
					stmt.bind(4, it->description);
					stmt.bind(5, game_manufacturer.find(it->id)->second);
					stmt.bind(6, game_sourcefile.find(it->id)->second);
					stmt.bind(7, it->cloneof);
					stmt.bind(8, it->romof);
					stmt.bind(9, it->sampleof);
					stmt.bind(10, (it->runnable) ? 1 : 0);
					stmt.bind(11, (it->isbios) ? 1 : 0);
					stmt.bind(12, (it->isdevice) ? 1 : 0);
					stmt.bind(13, (it->ismechanical) ? 1 : 0);

					try {
						base.exec(stmt);
						total++;
					} catch (GuruSQLite::GuruSQLiteException& e) {
						cout << e.what() << endl;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando drivers (" << table_driver.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into driver (id_game, status, emulation, color, sound, graphic, cocktail, protection, savestate, palettesize) values (?,?,?,?,?,?,?,?,?,?)"));
				for (std::list<listxml2SQLiteV2::reg_driver>::iterator it = table_driver.begin(), itend = table_driver.end(); it != itend; ++it) {
					stmt.bind(1, it->id_game);
					stmt.bind(1, it->status);
					stmt.bind(1, it->emulation);
					stmt.bind(1, it->color);
					stmt.bind(1, it->sound);
					stmt.bind(1, it->graphic);
					stmt.bind(1, it->cocktail);
					stmt.bind(1, it->protection);
					stmt.bind(1, it->savestate);
					stmt.bind(1, it->palettesize);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando biosset (" << biossets.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into biosset (id_biosset, name, description, _default) values (?,?,?,?)"));
				for (std::set<modelodatosmame::biosset>::iterator it = biossets.begin(), itend = biossets.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->description);
					stmt.bind(4, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando rom (" << roms.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt = base.sentencia("insert into rom(id_rom, name, bios, size, crc, sha1, merge, region, offset, status, optional) values(?,?,?,?,?,?,?,?,?,?,?)");
				for (std::set<modelodatosmame::rom>::iterator it = roms.begin(), itend = roms.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->bios);
					stmt.bind(4, it->size);
					stmt.bind(5, it->crc);
					stmt.bind(6, it->sha1);
					stmt.bind(7, it->merge);
					stmt.bind(8, rom_region.find(it->id)->second);
					stmt.bind(9, it->offset);
					stmt.bind(10, rom_status.find(it->id)->second);
					stmt.bind(11, it->optional);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando disks (" << disks.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into disk (id_disk, name, sha1, merge, region, _index, writable, status, optional) values (?,?,?,?,?,?,?,?,?)"));
				for (std::set<modelodatosmame::disk>::iterator it = disks.begin(), itend = disks.end(); it != itend; ++it) {
					
					stmt.bind(1,it->id);
					stmt.bind(2,it->name);
					stmt.bind(3,it->sha1);
					stmt.bind(4,it->merge);
					stmt.bind(5,it->region);
					stmt.bind(6,it->index);
					stmt.bind(7,it->writable);
					stmt.bind(8,it->status);
					stmt.bind(9,it->optional);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando display (" << table_display.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into display (id_game, tag, type, rotate, flipx, width, height, refresh, pixclock, htotal, hbend, hbstart, vtotal, vbend, vbstart) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
				for (std::list<modelodatosmame::display>::iterator it = table_display.begin(), itend = table_display.end(); it != itend; ++it) {
					
					stmt.bind(1,it->id);
					stmt.bind(2,it->tag);
					stmt.bind(3,it->type);
					stmt.bind(4,it->rotate);
					stmt.bind(5,it->flipx);
					stmt.bind(6,it->width);
					stmt.bind(7,it->height);
					stmt.bind(8,it->refresh);
					stmt.bind(9,it->pixclock);
					stmt.bind(10,it->htotal);
					stmt.bind(11,it->hbend);
					stmt.bind(12,it->hbstart);
					stmt.bind(13,it->vtotal);
					stmt.bind(14,it->vbend);
					stmt.bind(15,it->vbstart);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando chips (" << chips.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into chip (id_chip, name, tag, type, clock) values (?,?,?,?,?)"));
				for (std::set<modelodatosmame::chip>::iterator it = chips.begin(), itend = chips.end(); it != itend; ++it) {
					
					stmt.bind(1,it->id);
					stmt.bind(2,it->name);
					stmt.bind(3,it->tag);
					stmt.bind(4,it->type);
					stmt.bind(5,it->clock);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando dipswitchs (" << dipswitchs.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into dipswitch (id_dipswitch, name, tag, mask) values (?,?,?,?)"));
				for (std::set<modelodatosmame::dipswitch>::iterator it = dipswitchs.begin(), itend = dipswitchs.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->tag);
					stmt.bind(4, it->mask);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando dipvalues (" << dipvalues.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into dipvalue (id_dipvalue, name, value, _default) values (?,?,?,?)"));
				for (std::set<modelodatosmame::dipvalue>::iterator it = dipvalues.begin(), itend = dipvalues.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->value);
					stmt.bind(4, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando dipswitch_dipvalue... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = dipswitch_dipvalue.begin(), itend = dipswitch_dipvalue.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into dipswitch_dipvalue (id_dipswitch, id_dipvalue) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando configuration (" << configurations.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into configuration (id_configuration, name, tag, mask) values (?,?,?,?)"));
				for (std::set<modelodatosmame::configuration>::iterator it = configurations.begin(), itend = configurations.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->tag);
					stmt.bind(4, it->mask);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando confsetting (" << confsettings.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into confsetting (id_confsetting, name, value, _default) values (?,?,?,?)"));
				for (std::set<modelodatosmame::confsetting>::iterator it = confsettings.begin(), itend = confsettings.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->value);
					stmt.bind(4, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando configuration_confsetting... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = configuration_confsetting.begin(), itend = configuration_confsetting.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into configuration_confsetting (id_configuration, id_confsetting) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando port (" << ports.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into port (id_port, tag) values (?, ?)"));
				for (std::set<modelodatosmame::port>::iterator it = ports.begin(), itend = ports.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->tag);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando analog (" << analogs.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into analog (id_analog, mask) values (?,?)"));
				for (std::set<modelodatosmame::analog>::iterator it = analogs.begin(), itend = analogs.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->mask);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando port_analog... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = port_analog.begin(), itend = port_analog.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into port_analog (id_port, id_analog) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando device (" << devices.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into device (id_device, type, tag, fixed_image, mandatory, interface) values (?,?,?,?,?,?)"));
				for (std::set<modelodatosmame::device>::iterator it = devices.begin(), itend = devices.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->type);
					stmt.bind(3, it->tag);
					stmt.bind(4, it->fixed_image);
					stmt.bind(5, it->mandatory);
					stmt.bind(6, it->_interface);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando instance (" << instances.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into instance (id_instance, name, briefname) values (?,?,?)"));
				for (std::set<modelodatosmame::instance>::iterator it = instances.begin(), itend = instances.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->briefname);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando extension (" << extensions.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into extension (id_extension, name) values (?,?)"));
				for (std::set<modelodatosmame::extension>::iterator it = extensions.begin(), itend = extensions.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando device_instance... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = device_instance.begin(), itend = device_instance.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into device_instance (id_device, id_instance) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			cout << "Insertando device_extension... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = device_extension.begin(), itend = device_extension.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into device_extension (id_device, id_extension) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando input (" << inputs.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into input (id_input, service, tilt, players, coins) values (?,?,?,?,?)"));
				for (std::set<modelodatosmame::input>::iterator it = inputs.begin(), itend = inputs.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->service);
					stmt.bind(3, it->tilt);
					stmt.bind(4, it->players);
					stmt.bind(5, it->coins);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando control (" << controls.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into control (id_control, type, player, buttons, reqbuttons, minimum, maximum, sensitivity, keydelta, reverse, ways, ways2, ways3) values (?,?,?,?,?,?,?,?,?,?,?,?,?)"));
				for (std::set<modelodatosmame::control>::iterator it = controls.begin(), itend = controls.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->type);
					stmt.bind(3, it->player);
					stmt.bind(4, it->buttons);
					stmt.bind(5, it->reqbuttons);
					stmt.bind(6, it->minimum);
					stmt.bind(7, it->maximum);
					stmt.bind(8, it->sensitivity);
					stmt.bind(9, it->keydelta);
					stmt.bind(10, it->reverse);
					stmt.bind(11, it->ways);
					stmt.bind(12, it->ways2);
					stmt.bind(13, it->ways3);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando input_control... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = input_control.begin(), itend = input_control.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into input_control (id_input, id_control) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando slot (" << slots.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into slot (id_slot, name) values (?,?)"));
				for (std::set<modelodatosmame::slot>::iterator it = slots.begin(), itend = slots.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);

					base.exec(stmt);
					total++;
				}

				cout << total << endl;
			}

			{
				cout << "Insertando slotoption (" << slotoptions.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into slotoption (id_slotoption, name, devname, _default) values (?,?,?,?)"));
				for (std::set<modelodatosmame::slotoption>::iterator it = slotoptions.begin(), itend = slotoptions.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->devname);
					stmt.bind(4, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando slot_slotoption... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = slot_slotoption.begin(), itend = slot_slotoption.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into slot_slotoption (id_slot, id_slotoption) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando device_refs (" << table_device_ref.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into device_ref (id_game, name) values (?,?)"));
				for (std::list<listxml2SQLiteV2::reg_device_ref>::iterator it = table_device_ref.begin(), itend = table_device_ref.end(); it != itend; ++it) {

					stmt.bind(1, it->id_device_ref);
					stmt.bind(1, it->name);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando samples [" << table_sample.size() << "]..." << endl;
			for (std::list<listxml2SQLiteV2::reg_sample>::iterator it = table_sample.begin(), itend = table_sample.end(); it != itend; ++it) {
				consulta = "insert into sample (id_game, name) values (" +
					GuruStringAlgo::int64astr(it->id_sample) + ", " +
					GuruStringAlgo::int64astr(it->name) + ")";

				base.exec(consulta);
			}

			{
				cout << "Insertando softwarelist (" << softwarelists.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into softwarelist (id_softwarelist, name, status, filter) values (?,?,?,?)"));
				for (std::set<modelodatosmame::softwarelist>::iterator it = softwarelists.begin(), itend = softwarelists.end(); it != itend; ++it) {
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->status);
					stmt.bind(4, it->filter);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			{
				cout << "Insertando adjuster (" << adjusters.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into adjuster (id_adjuster, name, _default) values (?,?,?)"));
				for (std::set<modelodatosmame::adjuster>::iterator it = adjusters.begin(), itend = adjusters.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->name);
					stmt.bind(3, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando sound (" << sounds.size() << ")... "; total = 0;
			for (std::set<modelodatosmame::sound>::iterator it = sounds.begin(), itend = sounds.end(); it != itend; ++it) {
				consulta = "insert into sound (id_sound, channels) values (" +
					GuruStringAlgo::int64astr(it->id) + ", " +
					GuruStringAlgo::int64astr(it->channels) + ")";

				base.exec(consulta);
				total++;
			}
			cout << total << endl;

			{
				cout << "Insertando ramoption (" << ramoptions.size() << ")... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into ramoption (id_ramoption, _default) values (?, ?)"));
				for (std::set<modelodatosmame::ramoption>::iterator it = ramoptions.begin(), itend = ramoptions.end(); it != itend; ++it) {
					
					stmt.bind(1, it->id);
					stmt.bind(2, it->_default);

					base.exec(stmt);
					total++;
				}
				cout << total << endl;
			}

			cout << "Insertando game_biosset... "; total = 0;
			GuruSQLite::sentencia stmt(base.sentencia("insert into game_biosset (id_game, id_biosset) values (?, ?)"));
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_biosset.begin(), itend = game_biosset.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					stmt.bind(1, it->first);
					stmt.bind(2, *it2);

					base.exec(stmt);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando game_softwarelist... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_softwarelist (id_game, id_softwarelist) values (?, ?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_softwarelist.begin(), itend = game_softwarelist.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_adjuster..."; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_adjuster (id_game, id_adjuster) values (?, ?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_adjuster.begin(), itend = game_adjuster.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_rom... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_rom (id_game, id_rom) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_rom.begin(), itend = game_rom.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);
						
						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_disk... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_disk (id_game, id_disk) values (?, ?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_disk.begin(), itend = game_disk.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_chip... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_chip (id_game, id_chip) values (?, ?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_chip.begin(), itend = game_chip.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);
						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_device... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_device (id_game, id_device) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_device.begin(), itend = game_device.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_input... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_input (id_game, id_input) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_input.begin(), itend = game_input.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_dipswitch... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_dipswitch (id_game, id_dipswitch) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_dipswitch.begin(), itend = game_dipswitch.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			{
				cout << "Insertando game_configuration... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_configuration (id_game, id_configuration) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_configuration.begin(), itend = game_configuration.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);

						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			cout << "Insertando game_slot... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_slot.begin(), itend = game_slot.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into game_slot (id_game, id_slot) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			{
				cout << "Insertando game_port... "; total = 0;
				GuruSQLite::sentencia stmt(base.sentencia("insert into game_port (id_game, id_port) values (?,?)"));
				for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_port.begin(), itend = game_port.end(); it != itend; ++it) {
					for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
						stmt.bind(1, it->first);
						stmt.bind(2, *it2);
						
						base.exec(stmt);
						total++;
					}
				}
				cout << total << endl;
			}

			cout << "Insertando game_sound... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_sound.begin(), itend = game_sound.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into game_sound (id_game, id_sound) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			cout << "Insertando game_ramoption... "; total = 0;
			for (std::map<uint64_t, vector<uint64_t> >::iterator it = game_ramoption.begin(), itend = game_ramoption.end(); it != itend; ++it) {
				for (vector<uint64_t>::iterator it2 = it->second.begin(), itend2 = it->second.end(); it2 != itend2; ++it2) {
					consulta = "insert into game_ramoption (id_game, id_ramoption) values (" + GuruStringAlgo::int64astr(it->first) + ", " + GuruStringAlgo::int64astr(*it2) + ")";
					base.exec(consulta);
					total++;
				}
			}
			cout << total << endl;

			base.exec("create index idx_manufacturer on manufacturer(name)");
			base.exec("create index idx_game on game (name)");
			base.exec("create index idx_biosset on biosset (name)");
			base.exec("create index idx_rom on rom (name)");
			base.exec("create index idx_sourcefile on sourcefile(name)");
			base.exec("create index idx_text on text(text)");
			base.exec("create index idx_dipswitch on dipswitch(name)");
			base.exec("create index idx_configuration on configuration(name)");

		} catch (GuruSQLite::GuruSQLiteException& e) {
			cout << e.what() << endl;
		}

		cout << "Finalizando transaccion..." << endl;
		base.exec("END TRANSACTION");
	};

	void nombre_base(const string& nombre) { nombre_bd = nombre; }
	string& nombre_base() { return nombre_bd; }

	uint64_t machines() { return total; }
};

#endif
