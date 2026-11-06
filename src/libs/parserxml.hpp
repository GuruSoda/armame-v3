#ifndef __PARSERXML_HPP__
#define __PARSERXML_HPP__

#include <string>

#include <modelomame.hpp>
#include <modelodatosmame.hpp>

#include <expat.h>

namespace GuruMAME {

	static void start_element(void* userData, const XML_Char* name, const XML_Char** atts);
	static void end_element(void* userData, const XML_Char* name);
	static void char_data(void* userData, const XML_Char* s, int len);

	class GuruParserXML;

	typedef struct mameid {
		mameid() {
			id_biosset = 1;
			id_adjuster = 1;
			id_rom = 1;
			id_disk = 1;
			id_dipswitch = 1;
			id_dipvalue = 1;
			id_port = 1;
			id_analog = 1;
			id_configuration = 1;
			id_confsetting = 1;
			id_device = 1;
			id_instance = 1;
			id_extension = 1;
			id_slot = 1;
			id_slotoption = 1;
			id_input = 1;
			id_control = 1;
			id_chip = 1;
			id_softwarelist = 1;
			id_sample = 1;
			id_device_ref = 1;
			id_sound = 1;
			id_ramoption = 1;
			id_game = 1;
		}

		uint32_t id_biosset;
		uint32_t id_adjuster;
		uint32_t id_rom;
		uint32_t id_disk;
		uint32_t id_dipswitch;
		uint32_t id_dipvalue;
		uint32_t id_port;
		uint32_t id_analog;
		uint32_t id_configuration;
		uint32_t id_confsetting;
		uint32_t id_device;
		uint32_t id_instance;
		uint32_t id_extension;
		uint32_t id_slot;
		uint32_t id_slotoption;
		uint32_t id_input;
		uint32_t id_control;
		uint32_t id_chip;
		uint32_t id_softwarelist;
		uint32_t id_sample;
		uint32_t id_device_ref;
		uint32_t id_sound;
		uint32_t id_ramoption;
		uint32_t id_game;
	}mameid;

	struct data {
		data() { total = 0; }

		uint32_t		total;
		bool			cargar_data;
		string			buffer;

		modelodatosmame::game	game;
		GuruParserXML*			esto;

		modelodatosmame::dipswitch		tmp_dipswitch;
		modelodatosmame::configuration	tmp_configuration;
		modelodatosmame::input			tmp_input;
		modelodatosmame::slot			tmp_slot;
		modelodatosmame::device			tmp_device;
		modelodatosmame::port			tmp_port;

		mameid			ids;
	};

	typedef struct {
		string build;
		string debug;
		string mameconfig;
	} version;

	class GuruParserXML {
	public:
		GuruParserXML():segundos(0) {}
		virtual ~GuruParserXML() {}

		virtual void game(modelodatosmame::game&) {};
		virtual void version(const version&) {};
		virtual void end() {};

		void finalizar() {
			XML_SetElementHandler(parser, NULL, NULL);
			XML_SetCharacterDataHandler(parser, NULL);
			XML_SetProcessingInstructionHandler(parser, NULL);

	//		XML_StopParser(parser, 0); // NO se debe llamar desde un callback

			done = true;
		}

		time_t tiempo_sec() { return segundos; }

		void xml(const string& archivo) { entrada = archivo; }

		void iniciar() {
			char			buf[16384];
			int				depth = 0;
			struct data		user_data;
			std::ifstream	in;

			if (entrada.empty()) {
				in.copyfmt(std::cin);
				in.clear(std::cin.rdstate());
				in.basic_ios<char>::rdbuf(cin.rdbuf());
			} else {
				in.open(entrada.c_str());
				if (!in.is_open()) {
					return;
				}
			}

			user_data.esto = this;

			parser = XML_ParserCreate(NULL);

			XML_SetElementHandler(parser, GuruMAME::start_element, GuruMAME::end_element);
			XML_SetUserData(parser, &user_data);
			XML_SetCharacterDataHandler(parser, GuruMAME::char_data);

			segundos = 0;

			time_t inicio = time(NULL);

			while (8) {
				in.read(buf, sizeof(buf));
				if (in.bad()) break;

				std::streamsize len;

				len = in.gcount();
				done = in.eof();

				if (XML_Parse(parser, buf, static_cast<int>(len), done) == XML_STATUS_ERROR)
					cout << "Error: " << XML_ErrorString(XML_GetErrorCode(parser)) << endl;

				if (done)
					break;
			}

			XML_ParserFree(parser);

			segundos = time(NULL) - inicio;
		}

	private:
		XML_Parser		parser;
		bool			done;
		time_t			segundos;
		string			entrada;
	};

	static void start_element(void* userData, const XML_Char* name, const XML_Char** atts) {
		struct data* data = (struct data*) userData;
		data->cargar_data = false;

		if (strcmp(name, "game") == 0 || strcmp(name, "machine") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					data->game.name = atts[i + 1];
				} else if (strcmp("sourcefile", atts[i]) == 0) {
					data->game.sourcefile = atts[i + 1];
				} else if (strcmp("cloneof", atts[i]) == 0) {
					data->game.cloneof = atts[i + 1];
				} else if (strcmp("romof", atts[i]) == 0) {
					data->game.romof = atts[i + 1];
				} else if (strcmp("sampleof", atts[i]) == 0) {
					data->game.sampleof = atts[i + 1];
				} else if (strcmp("isdevice", atts[i]) == 0) {
					if (strcmp(atts[i + 1], "yes") == 0) data->game.isdevice = true;
				} else if (strcmp("isbios", atts[i]) == 0) {
					if (strcmp(atts[i + 1], "yes") == 0) data->game.isbios = true;
				} else if (strcmp("ismechanical", atts[i]) == 0) {
					if (strcmp(atts[i + 1], "yes") == 0) data->game.ismechanical = true;
				} else if (strcmp("runnable", atts[i]) == 0) {
					if (strcmp(atts[i + 1], "no") == 0) data->game.runnable = false;
				}
			}
		} else if (strcmp(name, "biosset") == 0) {
			modelodatosmame::biosset databiosset;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					databiosset.name = atts[i + 1];
				} else if (strcmp("description", atts[i]) == 0) {
					databiosset.description = atts[i + 1];
				} else if (strcmp("default", atts[i]) == 0) {
					databiosset._default = atts[i + 1];
				}  
			}
			databiosset.id = data->ids.id_biosset++;
			data->game.biossets.push_back(databiosset);
		} else if (strcmp(name, "adjuster") == 0) {
			modelodatosmame::adjuster dataadjuster;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					dataadjuster.name = atts[i + 1];
				} else if (strcmp("default", atts[i]) == 0) {
					dataadjuster._default = atts[i + 1];
				}
			}
			dataadjuster.id = data->ids.id_adjuster++;
			data->game.adjusters.push_back(dataadjuster);
		}if (strcmp(name, "rom") == 0) {
			modelodatosmame::rom datarom;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datarom.name = atts[i + 1];
				} else if (strcmp("size", atts[i]) == 0) {
					datarom.size = atoi(atts[i + 1]);
				} else if (strcmp("crc", atts[i]) == 0) {
					datarom.crc = atts[i + 1];
				} else if (strcmp("sha1", atts[i]) == 0) {
					datarom.sha1 = atts[i + 1];
				} else if (strcmp("merge", atts[i]) == 0) {
					datarom.merge = atts[i + 1];
				} else if (strcmp(atts[i], "status") == 0) {
					datarom.status = atts[i + 1];
				} else if (strcmp(atts[i], "bios") == 0) {
					datarom.bios = atts[i + 1];
				} else if (strcmp(atts[i], "region") == 0) {
					datarom.region = atts[i + 1];
				} else if (strcmp(atts[i], "offset") == 0) {
					datarom.offset = atts[i + 1];
				} else if (strcmp(atts[i], "optional") == 0) {
					datarom.optional = atts[i + 1];
				}
			}
			datarom.id = data->ids.id_rom++;
			data->game.roms.push_back(datarom);
		} else if (strcmp(name, "disk") == 0) {
			modelodatosmame::disk datadisk;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datadisk.name = atts[i + 1];
				} else if (strcmp("sha1", atts[i]) == 0) {
					datadisk.sha1 = atts[i + 1];
				} else if (strcmp("merge", atts[i]) == 0) {
					datadisk.merge = atts[i + 1];
				} else if (strcmp(atts[i], "region") == 0) {
					datadisk.region = atts[i + 1];
				} else if (strcmp(atts[i], "index") == 0) {
					datadisk.index = atts[i + 1];
				} else if (strcmp(atts[i], "writable") == 0) {
					datadisk.writable = atts[i + 1];
				} else if (strcmp(atts[i], "status") == 0) {
					datadisk.status = atts[i + 1];
				} else if (strcmp(atts[i], "optional") == 0) {
					datadisk.optional = atts[i + 1];
				}
			}
			datadisk.id = data->ids.id_disk++;
			data->game.disks.push_back(datadisk);
		} else if (strcmp(name, "driver") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("status", atts[i]) == 0) {
					data->game.driver.status = atts[i + 1];
				} else if (strcmp("emulation", atts[i]) == 0) {
					data->game.driver.emulation = atts[i + 1];
				} else if (strcmp("color", atts[i]) == 0) {
					data->game.driver.color = atts[i + 1];
				} else if (strcmp("sound", atts[i]) == 0) {
					data->game.driver.sound = atts[i + 1];
				} else if (strcmp("graphic", atts[i]) == 0) {
					data->game.driver.graphic = atts[i + 1];
				} else if (strcmp("cocktail", atts[i]) == 0) {
					data->game.driver.cocktail = atts[i + 1];
				} else if (strcmp("protection", atts[i]) == 0) {
					data->game.driver.protection = atts[i + 1];
				} else if (strcmp("savestate", atts[i]) == 0) {
					data->game.driver.savestate = atts[i + 1];
				}
			}
		} else if (strcmp(name, "display") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("tag", atts[i]) == 0) {
					data->game.display.tag = atts[i + 1];
				} else if (strcmp("type", atts[i]) == 0) {
					data->game.display.type = atts[i + 1];
				} else if (strcmp("rotate", atts[i]) == 0) {
					data->game.display.rotate = atoi(atts[i + 1]);
				} else if (strcmp("flipx", atts[i]) == 0) {
					data->game.display.flipx = atts[i + 1];
				} else if (strcmp("width", atts[i]) == 0) {
					data->game.display.width = atoi(atts[i + 1]);
				} else if (strcmp("height", atts[i]) == 0) {
					data->game.display.height = atoi(atts[i + 1]);
				} else if (strcmp("refresh", atts[i]) == 0) {
					data->game.display.refresh = atts[i + 1];
				} else if (strcmp("pixclock", atts[i]) == 0) {
					data->game.display.pixclock = atts[i + 1];
				} else if (strcmp("htotal", atts[i]) == 0) {
					data->game.display.htotal = atoi(atts[i + 1]);
				} else if (strcmp("hbend", atts[i]) == 0) {
					data->game.display.hbend = atoi(atts[i + 1]);
				} else if (strcmp("hbstart", atts[i]) == 0) {
					data->game.display.hbstart = atoi(atts[i + 1]);
				} else if (strcmp("vtotal", atts[i]) == 0) {
					data->game.display.vtotal = atoi(atts[i + 1]);
				} else if (strcmp("vbend", atts[i]) == 0) {
					data->game.display.vbend = atoi(atts[i + 1]);
				} else if (strcmp("vbstart", atts[i]) == 0) {
					data->game.display.vbstart = atoi(atts[i + 1]);
				}
			}
		} else if (strcmp(name, "dipswitch") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					data->tmp_dipswitch.name = atts[i + 1];
				} else if (strcmp("tag", atts[i]) == 0) {
					data->tmp_dipswitch.tag = atts[i + 1];
				} else if (strcmp("mask", atts[i]) == 0) {
					data->tmp_dipswitch.mask = atts[i + 1];
				}
			}

			data->tmp_dipswitch.id = data->ids.id_dipswitch++;
		} else if (strcmp(name, "dipvalue") == 0) {
			modelodatosmame::dipvalue datadipvalue;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datadipvalue.name = atts[i + 1];
				} else if (strcmp("value", atts[i]) == 0) {
					datadipvalue.value = atts[i + 1];
				} else if (strcmp("default", atts[i]) == 0) {
					datadipvalue._default = atts[i + 1];
				}
			}
			datadipvalue.id = data->ids.id_dipvalue++;
			data->tmp_dipswitch.dipvalues.push_back(datadipvalue);
		} else if (strcmp(name, "port") == 0) {

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("tag", atts[i]) == 0) {
					data->tmp_port.tag = atts[i + 1];
				} 
			}
			data->tmp_port.id = data->ids.id_port++;
		} else if (strcmp(name, "analog") == 0) {
			modelodatosmame::analog dataanalog;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("mask", atts[i]) == 0) {
					dataanalog.mask = atts[i + 1];
				}
			}
			dataanalog.id = data->ids.id_analog++;
			data->tmp_port.analogs.push_back(dataanalog);
		} else if (strcmp(name, "configuration") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					data->tmp_configuration.name = atts[i + 1];
				} else if (strcmp("tag", atts[i]) == 0) {
					data->tmp_configuration.tag = atts[i + 1];
				} else if (strcmp("mask", atts[i]) == 0) {
					data->tmp_configuration.mask = atts[i + 1];
				}
			}
			data->tmp_configuration.id = data->ids.id_configuration++;
		} else if (strcmp(name, "confsetting") == 0) {
			modelodatosmame::confsetting dataconfsetting;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					dataconfsetting.name = atts[i + 1];
				} else if (strcmp("value", atts[i]) == 0) {
					dataconfsetting.value = atts[i + 1];
				} else if (strcmp("default", atts[i]) == 0) {
					dataconfsetting._default = atts[i + 1];
				}
			}
			dataconfsetting.id = data->ids.id_confsetting++;
			data->tmp_configuration.confsettings.push_back(dataconfsetting);
		} else if (strcmp(name, "device") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("type", atts[i]) == 0) {
					data->tmp_device.type = atts[i + 1];
				} else if (strcmp("tag", atts[i]) == 0) {
					data->tmp_device.tag = atts[i + 1];
				} else if (strcmp("fixed_image", atts[i]) == 0) {
					data->tmp_device.fixed_image = atts[i + 1];
				} else if (strcmp("mandatory", atts[i]) == 0) {
					data->tmp_device.mandatory = atts[i + 1];
				} else if (strcmp("interface", atts[i]) == 0) {
					data->tmp_device._interface = atts[i + 1];
				}
			}
			data->tmp_device.id = data->ids.id_device++;
		} else if (strcmp(name, "instance") == 0) {
			modelodatosmame::instance datainstance;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datainstance.name = atts[i + 1];
				} else if (strcmp("briefname", atts[i]) == 0) {
					datainstance.briefname = atts[i + 1];
				} 
			}
			datainstance.id = data->ids.id_instance++;
			data->tmp_device.instances.push_back(datainstance);
		} else if (strcmp(name, "extension") == 0) {
			modelodatosmame::extension dataextension;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					dataextension.name = atts[i + 1];
				} 
			}
			dataextension.id = data->ids.id_extension++;
			data->tmp_device.extensions.push_back(dataextension);
		} else if (strcmp(name, "slot") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					data->tmp_slot.name = atts[i + 1];
				} 
			}
			data->tmp_slot.id = data->ids.id_slot++;
		} else if (strcmp(name, "slotoption") == 0) {
			modelodatosmame::slotoption dataslotoption;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					dataslotoption.name = atts[i + 1];
				} else if (strcmp("value", atts[i]) == 0) {
					dataslotoption.devname = atts[i + 1];
				} else if (strcmp("default", atts[i]) == 0) {
					dataslotoption._default = atts[i + 1];
				}
			}
			dataslotoption.id = data->ids.id_slotoption++;
			data->tmp_slot.slotoptions.push_back(dataslotoption);
		} else if (strcmp(name, "input") == 0) {
			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("service", atts[i]) == 0) {
					data->tmp_input.service = atts[i + 1];
				} else if (strcmp("tilt", atts[i]) == 0) {
					data->tmp_input.tilt = atts[i + 1];
				} else if (strcmp("players", atts[i]) == 0) {
					data->tmp_input.players = atts[i + 1];
				} else if (strcmp("coins", atts[i]) == 0) {
					data->tmp_input.coins = atts[i + 1];
				}
			}

			data->tmp_input.id = data->ids.id_input++;
		} else if (strcmp(name, "control") == 0) {
			modelodatosmame::control datacontrol;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("type", atts[i]) == 0) {
					datacontrol.type = atts[i + 1];
				} else if (strcmp("player", atts[i]) == 0) {
					datacontrol.player = atts[i + 1];
				} else if (strcmp("buttons", atts[i]) == 0) {
					datacontrol.buttons = atts[i + 1];
				} else if (strcmp("reqbuttons", atts[i]) == 0) {
					datacontrol.reqbuttons = atts[i + 1];
				} else if (strcmp("minimum", atts[i]) == 0) {
					datacontrol.minimum = atts[i + 1];
				} else if (strcmp("maximum", atts[i]) == 0) {
					datacontrol.maximum = atts[i + 1];
				} else if (strcmp("sensitivity", atts[i]) == 0) {
					datacontrol.sensitivity = atts[i + 1];
				} else if (strcmp("keydelta", atts[i]) == 0) {
					datacontrol.keydelta = atts[i + 1];
				} else if (strcmp("reverse", atts[i]) == 0) {
					datacontrol.reverse = atts[i + 1];
				} else if (strcmp("ways", atts[i]) == 0) {
					datacontrol.ways = atts[i + 1];
				} else if (strcmp("ways2", atts[i]) == 0) {
					datacontrol.ways2 = atts[i + 1];
				} else if (strcmp("ways3", atts[i]) == 0) {
					datacontrol.ways3 = atts[i + 1];
				}
			}
			datacontrol.id = data->ids.id_control++;
			data->tmp_input.controls.push_back(datacontrol);
		} else if (strcmp(name, "chip") == 0) {
			modelodatosmame::chip datachip;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datachip.name = atts[i + 1];
				} else if (strcmp("tag", atts[i]) == 0) {
					datachip.tag = atts[i + 1];
				} else if (strcmp("type", atts[i]) == 0) {
					datachip.type = atts[i + 1];
				} else if (strcmp("clock", atts[i]) == 0) {
					datachip.clock = atts[i + 1];
				} 
			}

			datachip.id = data->ids.id_chip++;
			data->game.chips.push_back(datachip);
		} else if (strcmp(name, "softwarelist") == 0) {
			modelodatosmame::softwarelist datasoftwarelist;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datasoftwarelist.name = atts[i + 1];
				} else if (strcmp("status", atts[i]) == 0) {
					datasoftwarelist.status = atts[i + 1];
				} else if (strcmp("filter", atts[i]) == 0) {
					datasoftwarelist.filter = atts[i + 1];
				} 
			}

			datasoftwarelist.id = data->ids.id_softwarelist++;
			data->game.softwarelists.push_back(datasoftwarelist);
		} else if (strcmp(name, "sample") == 0) {
			modelodatosmame::sample datasample;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datasample.name = atts[i + 1];
				}
			}

			datasample.id = data->ids.id_sample++;
			data->game.samples.push_back(datasample);
		} else if (strcmp(name, "device_ref") == 0) {
			modelodatosmame::device_ref datadevice_ref;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("name", atts[i]) == 0) {
					datadevice_ref.name = atts[i + 1];
				}
			}

			datadevice_ref.id = data->ids.id_device_ref++;
			data->game.device_refs.push_back(datadevice_ref);
		} else if (strcmp(name, "sound") == 0) {
			modelodatosmame::sound datasound;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("channels", atts[i]) == 0) {
					datasound.channels = atoi(atts[i + 1]);
				}
			}

			datasound.id = data->ids.id_sound++;
			data->game.sounds.push_back(datasound);
		} else if (strcmp(name, "mame") == 0) {
			GuruMAME::version ver;

			for (int i = 0; atts[i]; i += 2) {
				if (strcmp("build", atts[i]) == 0) {
					ver.build = atts[i + 1];
				} else if (strcmp("debug", atts[i]) == 0) {
					ver.debug = atts[i + 1];
				} else if (strcmp("mameconfig", atts[i]) == 0) {
					ver.mameconfig = atts[i + 1];
				}
			}
			data->esto->version(ver);
		} else if (strcmp(name, "sampleof") == 0) {
			data->cargar_data = true;
		} else if (strcmp(name, "description") == 0) {
			data->cargar_data = true;
		} else if (strcmp(name, "year") == 0) {
			data->cargar_data = true;
		} else if (strcmp(name, "manufacturer") == 0) {
			data->cargar_data = true;
		} else if (strcmp(name, "ramoption") == 0) {
			data->cargar_data = true;
		}
	}

	static void end_element(void* userData, const XML_Char* name) {
		struct data* data = (struct data*) userData;

		if (strcmp("description", name) == 0) {
			data->game.description = data->buffer;
		} else if (strcmp("sampleof", name) == 0) {
			data->game.sampleof = data->buffer.c_str();
		} else if (strcmp("year", name) == 0) {
			data->game.year = atoi(data->buffer.c_str());
		} else if (strcmp("manufacturer", name) == 0) {
			data->game.manufacturer = data->buffer;
		} else if (strcmp("ramoption", name) == 0) {
			modelodatosmame::ramoption dataramoption;
			dataramoption.id = data->ids.id_ramoption++;
			dataramoption._default = atoll(data->buffer.c_str());
			data->game.ramoptions.push_back(dataramoption);
		} else if (strcmp("dipswitch", name) == 0) {
			data->game.dipswitchs.push_back(data->tmp_dipswitch);
			data->tmp_dipswitch.clear();
		} else if (strcmp("configuration", name) == 0) {
			data->game.configurations.push_back(data->tmp_configuration);
			data->tmp_configuration.clear();
		} else if (strcmp("port", name) == 0) {
			data->game.ports.push_back(data->tmp_port);
			data->tmp_port.clear();
		} else if (strcmp("input", name) == 0) {
			data->game.inputs.push_back(data->tmp_input);
			data->tmp_input.clear();
		} else if (strcmp("slot", name) == 0) {
			data->game.slots.push_back(data->tmp_slot);
			data->tmp_slot.clear();
		} else if (strcmp("device", name) == 0) {
			data->game.devices.push_back(data->tmp_device);
			data->tmp_device.clear();
		} else if (strcmp(name, "game") == 0 || strcmp(name, "machine") == 0) {
			data->game.id = data->ids.id_game++;

			data->esto->game(data->game);

			data->game.clear();
			data->total++;
		} else if (strcmp("mame", name) == 0) {
			data->esto->end();
		}

		data->cargar_data = false;
		data->buffer.clear();
	}

	static void char_data(void* userData, const XML_Char* s, int len) {
		struct data* data = (struct data*) userData;

		if (data->cargar_data) {
			for (int a = 0; a < len; a++)
				data->buffer += *s++;
		}
	}
}

#endif
