// listxml2json

#include <argtable/argtable2.h>
#include <modelodatosmame.hpp>
#include <parserxml.hpp>

#include <jsoncpp/json.h>


class listxml2json : public GuruMAME::GuruParserXML {
	list<Json::Value> objetos;
public:
	listxml2json() {}
	virtual ~listxml2json() {}

	void game(modelodatosmame::game& machine) {

		Json::Value obj;

		obj["name"] = machine.name;
		obj["description"] = machine.description;
		obj["manufacturer"] = machine.manufacturer;
		obj["year"] = machine.year;
		obj["sourcefile"] = machine.sourcefile;
		obj["runnable"] = machine.runnable;
		obj["isbios"] = machine.isbios;
		obj["isdevice"] = machine.isdevice;
		obj["ismechanical"] = machine.ismechanical;
		
		Json::Value roms;

		for (vector<modelodatosmame::rom>::iterator it = machine.roms.begin(), itend = machine.roms.end(); it != itend; ++it) {
			Json::Value rom;

			rom["name"] = it->name;
			rom["size"] = it->size;
			rom["crc"] = it->crc;
			rom["sha1"] = it->sha1;
			rom["status"] = it->status;

			roms.append(rom);
		}

		obj["roms"] = roms;

		if (!machine.cloneof.empty())
			obj["cloneof"] = machine.cloneof;

		if (!machine.romof.empty())
			obj["romof"] = machine.cloneof;

		Json::Value driver;

		driver["status"] = machine.driver.status;
		driver["emulation"] = machine.driver.emulation;

		obj["driver"] = driver;

		// cout << obj.toStyledString();
		objetos.push_back(obj);
	}
		
};

int main(int argc, char* argv[])
{
	struct arg_lit*  opt_help = arg_lit0("h", "help", "Muestra la ayuda.");
	struct arg_file* opt_xml = arg_file0("i", "xml", "<xml>", "entrada.");
	struct arg_lit*  opt_vector = arg_lit0("a", "vector", "La salida es un vector de objetos.");
	struct arg_end*  end = arg_end(8);

	void* argtable[] = { opt_help, opt_xml, opt_vector, end};

	if (arg_nullcheck(argtable) != 0) {
		cout << "insufficient memory" << endl;
		return 2;
	}

	int nerrors = arg_parse(argc, argv, argtable);

	if (opt_help->count > 0 || argc == 1) {
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		return 1;
	}

	if (nerrors > 0) {
		arg_print_errors(stdout, end, "");
		cout << "Pruebe --help por mas informacion" << endl;
		return 3;
	}

	string entrada;
	if (opt_xml->count > 0) entrada = opt_xml->filename[0];

//////////////////////////////////////////////////////////////////////

	listxml2json j;

	j.xml(entrada);

	j.iniciar();

//////////////////////////////////////////////////////////////////////
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

	return 0;
}
