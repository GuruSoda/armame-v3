#ifndef __MODELODATOSMAME_HPP__
#define __MODELODATOSMAME_HPP__

#include <string>
#include <vector>
#include <GuruCompat.h>
#include <GuruString_algo.hpp>

using namespace std;

namespace modelodatosmame {

	struct version {
		string		build;
		string		debug;
		string		mameconfig;
	};

	struct rom {
		rom() :id(1), size(0), status("good"), optional("no") {}

		uint64_t	id;

		string		name;
		string		merge;
		uint32_t	size;
		string		crc;
		string		sha1;
		string		status;

		string		bios;
		string		region;
		string		offset;
		string		optional;


		void clear() {
			name.clear();
			merge.clear();
			size = 0;
			crc.clear();
			sha1.clear();
			status = "good";

			bios.clear();
			region.clear();
			offset.clear();
			optional = "no";
		}
	};

	enum state_driver {good=1,imperfect,preliminary};

	struct biosset {
		biosset() :id(1), _default("no") {}

		uint64_t id;

		string name;
		string description;
		string _default;

		void clear() {
			name.clear();
			description.clear();
			_default = "no";
		}
	};

	struct display {
		display() :id(1), flipx("no"), width(0), height(0), htotal(0), hbend(0), hbstart(0), vtotal(0), vbend(0), vbstart(0) {}

		uint64_t	id;
		string		tag;
		string		type;
		int			rotate;
		string		flipx;
		int			width;
		int			height;
		string		refresh;
		string		pixclock;
		int			htotal;
		int			hbend;
		int			hbstart;
		int			vtotal;
		int			vbend;
		int			vbstart;

		void clear() {
			tag.clear();
			type.clear();
			rotate = 0;
			flipx = "no";
			width = 0;
			height = 0;
			refresh.clear();
			pixclock.clear();
			htotal = 0;
			hbend = 0;
			hbstart = 0;
			vtotal = 0;
			vbend = 0;
			vbstart = 0;
		}
	};

	struct driver {
		driver():id(1) {}

		uint64_t	id;
		string		status;
		string		emulation;
		string		color;
		string		sound;
		string		graphic;
		string		cocktail;
		string		protection;
		string		savestate;
		string		palettesize;

		void clear() {
			status.clear();
			emulation.clear();
			color.clear();
			sound.clear();
			graphic.clear();
			cocktail.clear();
			protection.clear();
			savestate.clear();
			palettesize.clear();
		}
	};

	struct disk {
		disk():id(1), writable("no"), status("good"), optional("no") {};
		
		uint64_t id;
		string name;
		string sha1;
		string merge;
		string region;
		string index;
		string writable;
		string status;
		string optional;

		void clear() {
			name.clear();
			sha1.clear();
			merge.clear();
			region.clear();
			index.clear();
			writable = "no";
			status = "good";
			optional = "no";
		}
	};

	struct chip {
		chip() :id(1) {}

		uint64_t id;
		string name;
		string tag;
		string type; // (cpu | audio)
		string clock;

		void clear() {
			name.clear();
			tag.clear();
			type.clear();
			clock.clear();
		}
	};

	struct device_ref {
		uint64_t	id;
		string		name;
	};

	struct sample {
		uint64_t	id;
		string		name;
	};

	struct sound {
		uint64_t	id;
		int		channels;
	};

	struct softwarelist {
		uint64_t	id;
		string		name;
		string		status;
		string		filter;
	};

	struct adjuster {
		uint64_t	id;
		string		name;
		string		_default;
	};

	struct ramoption {
		ramoption() :id(0), _default(0) {}

		uint64_t	id;
		uint64_t	_default;
	};

	struct control {
		control() :id(0), reverse("no") {}

		uint64_t id;

		string type;
		string player;
		string buttons;
		string reqbuttons;
		string minimum;
		string maximum;
		string sensitivity;
		string keydelta;
		string reverse;
		string ways;
		string ways2;
		string ways3;

		void clear() {
			type.clear();
			player.clear();
			buttons.clear();
			reqbuttons.clear();
			minimum.clear();
			maximum.clear();
			sensitivity.clear();
			keydelta.clear();
			reverse = "no";
			ways.clear();
			ways2.clear();
			ways3.clear();
		};
	};

	struct input {
		input() :id(1), service("no"), tilt("no") {}

		uint64_t id;

		string service;
		string tilt;
		string players;
		string coins;

		vector<control>	controls;

		void clear() {
			service = "no";
			tilt = "no";
			players.clear();
			coins.clear();

			controls.clear();
		};
	};

	struct confsetting {
		confsetting() :id(0),_default("no") {}

		uint64_t id;

		string name;
		string value;
		string _default;

		void clear() {
			name.clear();
			value.clear();
			_default = "no";
		}

	};

	struct configuration {
		configuration() :id(0) {}

		uint64_t id;

		string name;
		string tag;
		string mask;

		vector<confsetting>	confsettings;

		void clear() {
			name.clear();
			tag.clear();
			mask.clear();

			confsettings.clear();
		}
	};

	struct analog {
		analog() :id(0) {}

		uint64_t id;

		string mask;

		void clear() {
			mask.clear();
		}
	};

	struct port {
		port() :id(0) {}

		uint64_t id;

		string tag;
		vector<analog>	analogs;

		void clear() {
			tag.clear();
			analogs.clear();
		}
	};

	struct dipvalue {
		dipvalue() :id(1), _default("no") {};
		~dipvalue() { }

		uint64_t id;
		string name;
		string value;
		string _default;
	};

	struct dipswitch {
		dipswitch() :id(1) {};
		~dipswitch() { }

		uint64_t	id;

		string name;
		string tag;
		string mask;

		vector<dipvalue> dipvalues;

		void clear() {
			name.clear();
			tag.clear();
			mask.clear();

			dipvalues.clear();
		}
	};

	struct slotoption {
		slotoption() :id(0), _default("no") {}

		uint64_t id;

		string name;
		string devname;
		string _default;
	};

	struct slot {
		slot() :id(0) {}

		uint64_t id;
		string name;

		vector<slotoption> slotoptions;

		void clear() {
			name.clear();

			slotoptions.clear();
		}
	};

	struct instance {
		instance() :id(0) {}

		uint64_t id;

		string name;
		string briefname;
	};

	struct extension {
		extension():id(0) {}

		uint64_t id;

		string name;
	};

	struct device {
		device() :id(0) {}

		uint64_t id;
		string type;
		string tag;
		string fixed_image;
		string mandatory;
		string _interface;

		vector<instance> instances;
		vector<extension> extensions;

		void clear() {
			type.clear();
			tag.clear();
			fixed_image.clear();
			mandatory.clear();
			_interface.clear();

			instances.clear();
			extensions.clear();
		}
	};

	struct game {
		game():id(1),year(0), isdevice(false),isbios(false),ismechanical(false),runnable(true) {};

		uint64_t	id;
		string		name;
		string		sourcefile;
		string		description;
		uint16_t	year;
		string		manufacturer;
		string		cloneof;
		string		romof;
		string		sampleof;
		bool		runnable;
		bool		isdevice;
		bool		isbios;
		bool		ismechanical;

		vector<rom>			roms;
		vector<disk>		disks;
		vector<chip>		chips;
		vector<device_ref>	device_refs;
		vector<sample>		samples;
		vector<biosset>		biossets;
		vector<dipswitch>	dipswitchs;
		vector<adjuster>	adjusters;
		vector<softwarelist>	softwarelists;
		vector<configuration>	configurations;
		vector<input>		inputs;
		vector<slot>		slots;
		vector<device>		devices;
		vector<port>		ports;
		vector<ramoption>	ramoptions;
		vector<sound>		sounds;

		struct driver	driver;
		struct display	display;
		
		void clear() {
			name.clear();
			sourcefile.clear();
			description.clear();
			year = 0;
			manufacturer.clear();
			cloneof.clear();
			romof.clear();
			roms.clear();
			sampleof.clear();
			isdevice = false;
			isbios = false;
			ismechanical = false;
			runnable = true;
			biossets.clear();
			driver.clear();
			display.clear();
			disks.clear();
			chips.clear();
			device_refs.clear();
			samples.clear();
			softwarelists.clear();
			configurations.clear();
			inputs.clear();
			dipswitchs.clear();
			adjusters.clear();
			slots.clear();
			devices.clear();
			ports.clear();
			ramoptions.clear();
			sounds.clear();
		}
	};

	bool operator == (struct device_ref d1, struct device_ref d2) {
		if (d1.name.compare(d2.name) == 0)
			return true;
		else
			return false;
	}

	bool operator == (struct rom r1, struct rom r2) {
		if (r1.name.compare(r2.name) == 0 && r1.size == r2.size && r1.crc.compare(r2.crc) == 0 && r1.sha1.compare(r2.sha1) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct rom r1, struct rom r2) {
		string s1 = r1.name + GuruStringAlgo::int64astr(r1.size) + r1.crc + r1.sha1 + r1.region + r1.offset;
		string s2 = r2.name + GuruStringAlgo::int64astr(r2.size) + r2.crc + r2.sha1 + r2.region + r2.offset;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct biosset b1, struct biosset b2) {
		if (b1.name.compare(b2.name) == 0 && b1.description.compare(b2.description) == 0 && b1._default.compare(b2._default) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct biosset b1, struct biosset b2) {
		string s1 = b1.name + b1.description + b1._default;
		string s2 = b2.name + b2.description + b2._default;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct input i1, struct input i2) {
		if (i1.service.compare(i2.service) == 0 && i1.tilt.compare(i2.tilt) == 0 && i1.players.compare(i2.players) == 0 && i1.coins.compare(i2.coins) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct input i1, struct input i2) {
		string s1 = i1.service + i1.tilt + i1.players + i1.coins;
		string s2 = i2.service + i2.tilt + i2.players + i1.coins;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct control c1, struct control c2) {
		if (c1.type.compare(c2.type) == 0 && c1.player.compare(c2.player) == 0 && c1.buttons.compare(c2.buttons) == 0 && c1.reqbuttons.compare(c2.reqbuttons) == 0 && 
			c1.minimum.compare(c2.minimum) == 0 && c1.maximum.compare(c2.maximum) == 0 && c1.sensitivity.compare(c2.sensitivity) == 0 && c1.keydelta.compare(c2.keydelta) == 0 && 
			c1.reverse.compare(c2.reverse) == 0 && c1.ways.compare(c2.ways) == 0 && c1.ways2.compare(c2.ways2) == 0 && c1.ways3.compare(c2.ways3) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct control c1, struct control c2) {
		string s1 = c1.type + c1.player + c1.buttons + c1.reqbuttons + c1.minimum + c1.maximum + c1.sensitivity + c1.keydelta + c1.reverse + c1.ways + c1.ways2 + c1.ways3;
		string s2 = c2.type + c2.player + c2.buttons + c2.reqbuttons + c2.minimum + c2.maximum + c2.sensitivity + c2.keydelta + c2.reverse + c2.ways + c2.ways2 + c2.ways3;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct slotoption s1, struct slotoption s2) {
		if (s1.name.compare(s2.name) == 0 && s1.devname.compare(s2.devname) == 0 && s1._default.compare(s2._default) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct slotoption s1, struct slotoption s2) {
		string ss1 = s1.name + s1.devname + s1._default;
		string ss2 = s2.name + s2.devname + s2._default;

		if (ss1 < ss2)
			return true;
		else
			return false;
	}

	bool operator == (struct slot s1, struct slot s2) {
		if (s1.name.compare(s2.name) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct slot s1, struct slot s2) {
		string ss1 = s1.name;
		string ss2 = s2.name;

		if (ss1 < ss2)
			return true;
		else
			return false;
	}

	bool operator == (struct device d1, struct device d2) {
		if (d1.type.compare(d2.type) == 0 && d1.tag.compare(d2.tag) == 0 && d1.fixed_image.compare(d2.fixed_image) == 0 && d1.mandatory.compare(d2.mandatory) == 0 && d1._interface.compare(d2._interface) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct device d1, struct device d2) {
		string s1 = d1.type + d1.tag + d1.fixed_image + d1.mandatory + d1._interface;
		string s2 = d2.type + d2.tag + d1.fixed_image + d1.mandatory + d1._interface;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct instance i1, struct instance i2) {
		if (i1.name.compare(i2.name) == 0 && i1.briefname.compare(i2.briefname) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct instance i1, struct instance i2) {
		string s1 = i1.name + i1.briefname;
		string s2 = i2.name + i2.briefname;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct extension e1, struct extension e2) {
		if (e1.name.compare(e2.name) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct extension e1, struct extension e2) {
		
		if (e1.name < e2.name)
			return true;
		else
			return false;
	}

	bool operator == (struct confsetting c1, struct confsetting c2) {
		if (c1.name.compare(c2.name) == 0 && c1.value.compare(c2.value) == 0 && c1._default.compare(c2._default) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct confsetting c1, struct confsetting c2) {
		string s1 = c1.name + c1.value + c1._default;
		string s2 = c2.name + c2.value + c2._default;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct configuration c1, struct configuration c2) {
		if (c1.name.compare(c2.name) == 0 && c1.tag.compare(c2.tag) == 0 && c1.mask.compare(c2.mask) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct configuration c1, struct configuration c2) {
		string s1 = c1.name + c1.tag + c1.mask;
		string s2 = c2.name + c2.tag + c2.mask;

		if (s1 < s2)
			return true;
		else
			return false;
	}


	bool operator == (struct adjuster a1, struct adjuster a2) {
		if (a1.name.compare(a2.name) == 0 && a1._default.compare(a2._default) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct adjuster a1, struct adjuster a2) {
		string s1 = a1.name + a1._default;
		string s2 = a2.name + a2._default;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct port p1, struct port p2) {
		if (p1.tag.compare(p2.tag) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct port p1, struct port p2) {
		string s1 = p1.tag;
		string s2 = p2.tag;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct analog a1, struct analog a2) {
		if (a1.mask.compare(a2.mask) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct analog a1, struct analog a2) {
		string s1 = a1.mask;
		string s2 = a2.mask;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct softwarelist s1, struct softwarelist s2) {
		if (s1.name.compare(s2.name) == 0 && s1.status.compare(s2.status) == 0 && s1.filter.compare(s2.filter) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct softwarelist s1, struct softwarelist s2) {
		string ss1 = s1.name + s1.status + s1.filter;
		string ss2 = s2.name + s2.status + s2.filter;

		if (ss1 < ss2)
			return true;
		else
			return false;
	}

	bool operator == (struct disk d1, struct disk d2) {
		if (d1.name.compare(d2.name) == 0 && d1.sha1.compare(d2.sha1) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct disk d1, struct disk d2) {
		string s1 = d1.name + d1.sha1 + d1.region + d1.index + d1.writable + d1.status + d1.optional;
		string s2 = d2.name + d2.sha1 + d2.region + d2.index + d2.writable + d2.status + d2.optional;

		if (s1 < s2)
			return true;
		else
			return false;
	}

	bool operator == (struct dipvalue d1, struct dipvalue d2) {
		if (d1.name.compare(d2.name) == 0 && d1.value.compare(d2.value) == 0 && d1._default.compare(d2._default) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct dipvalue d1, struct dipvalue d2) {
		string s1 = d1.name + d1.value + d1._default;
		string s2 = d2.name + d2.value + d2._default;

		if (s1 < s2) // segun los que saben: !(s1.type < s2.type) && !(s2.type < s1.type)
			return true;
		else
			return false;
	}

	bool operator == (struct dipswitch d1, struct dipswitch d2) {
		if (d1.name.compare(d2.name) == 0 && d1.tag.compare(d2.tag) == 0 && d1.mask.compare(d2.mask) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct dipswitch d1, struct dipswitch d2) {
		string s1 = d1.name + d1.tag + d1.mask;
		string s2 = d2.name + d2.tag + d2.mask;

		if (s1 < s2) // segun los que saben: !(s1.type < s2.type) && !(s2.type < s1.type)
			return true;
		else
			return false;
	}

	bool operator == (struct sound s1, struct sound s2) {
		if (s1.channels == s2.channels)
			return true;
		else
			return false;
	}

	bool operator < (struct sound s1, struct sound s2) {
		if (s1.channels < s2.channels) // segun los que saben: !(c1.type < c2.type) && !(c2.type < c1.type)
			return true;
		else
			return false;
	}

	bool operator == (struct ramoption r1, struct ramoption r2) {
		if (r1._default == r2._default)
			return true;
		else
			return false;
	}

	bool operator < (struct ramoption r1, struct ramoption r2) {
		if (r1._default < r2._default) // segun los que saben: !(c1.type < c2.type) && !(c2.type < c1.type)
			return true;
		else
			return false;
	}

	bool operator == (struct chip c1, struct chip c2) {
		if (c1.name.compare(c2.name) == 0 && c1.tag.compare(c2.tag) == 0 && c1.type.compare(c2.type) == 0 && c1.clock.compare(c2.clock) == 0)
			return true;
		else
			return false;
	}

	bool operator < (struct chip c1, struct chip c2) {
		string s1 = c1.type + c1.tag + c1.name + c1.clock;
		string s2 = c2.type + c2.tag + c2.name + c2.clock;

		if (s1 < s2) // segun los que saben: !(c1.type < c2.type) && !(c2.type < c1.type)
			return true;
		else
			return false;
	}
};

#endif
