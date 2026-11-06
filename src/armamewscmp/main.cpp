#include <iostream>
#include <fstream>
#include <expat.h>
#include <vector>
#include <set>
#include <sstream>
#include <cstdlib>
#include <future>
#include <functional>
#include <chrono>

#include <GuruHttp/GuruhttpClienteREST.hpp>

#include <argtable/argtable2.h>
#include <GuruCompat.h>
#include <modelodatosmame.hpp>
#include <parserxml.hpp>

#include <GuruPool.hpp>

#if defined __GURUWIN32__
#include <Windows.h>
#include <psapi.h>
#elif defined __GURULINUX__
#endif

using namespace std;

static const char* armamewscmp_version = "1.1.3";
static const char* armamewscmp_version_number = "100103";

char progreso() {
	static uint64_t	t = 0;
	char chars_progreso[] = { '|','/','-', '\\' };

	return chars_progreso[t++ % 4];
}

class XMLaArMameWS: public GuruMAME::GuruParserXML {
	GuruHttpCliente::opciones_get opt;

	std::string ws;
	uint32_t	maquinas=1;
	int			simultaneos=5;
	
public:
	XMLaArMameWS() {}
	virtual ~XMLaArMameWS() {}

	void proxy(const string& server, const string& usuario, const string& clave) {
		opt.proxy_server(server);
		opt.proxy_usuario(usuario);
		opt.proxy_clave(clave);
	}

	void url(const string& ws) {
		this->ws = ws + "/armamews";
	}

	void concurrentes(int cant) {
		simultaneos = cant;
	}

	bool comparar_chip(const string& url, vector<modelodatosmame::chip>& xml_chip) {
		GuruHttpCliente::rest::response res_url(GuruHttpCliente::rest::get(url, opt));

		if (res_url.status_code() == 200) {
			Json::Value chip = res_url.json();

			if (!chip.empty()) {
				vector<modelodatosmame::chip> chips;

				for (Json::ValueIterator it = chip.begin(), itend = chip.end(); it != itend; ++it) {
					modelodatosmame::chip data;

					data.name = (*it)["Name"].asString();
					data.tag = (*it)["Tag"].asString();
					data.type = (*it)["Type"].asString();
					data.clock = (*it)["Clock"].asString();

					chips.push_back(data);
				}

				for (vector<modelodatosmame::chip>::iterator it = chips.begin(), itend = chips.end(); it != itend; ++it) {
					if (std::find(xml_chip.begin(), xml_chip.end(), *it) == xml_chip.end())
						return false;
				}
			}

			return true;
		} else 
			return false;
	}

	bool comparar_roms(const string& url, vector<modelodatosmame::rom>& xml_rom) {
		GuruHttpCliente::rest::response res_url(GuruHttpCliente::rest::get(url, opt));

		if (res_url.status_code() == 200) {
			Json::Value rom = res_url.json();

			if (!rom.empty()) {
				vector<modelodatosmame::rom> roms;

				for (Json::ValueIterator it = rom.begin(), itend = rom.end(); it != itend; ++it) {
					modelodatosmame::rom data;

					data.name = (*it)["name"].asString();
					data.crc = (*it)["crc"].asString();
					data.sha1 = (*it)["sha1"].asString();
					data.status = (*it)["status"].asString();
					data.bios = (*it)["bios"].asString();
					data.region = (*it)["region"].asString();
					data.offset = (*it)["offset"].asString();
					data.optional = (*it)["optional"].asString();
					data.size = std::stoi((*it)["size"].asString());
					data.merge = (*it)["merge"].asString();

					roms.push_back(data);
				}

				for (vector<modelodatosmame::rom>::iterator it = roms.begin(), itend = roms.end(); it != itend; ++it) {
					if (std::find(xml_rom.begin(), xml_rom.end(), *it) == xml_rom.end())
						return false;
				}
			}

			return true;
		} else
			return false;
	}

	bool comparar_device_ref(const string& url, vector<modelodatosmame::device_ref>& xml_device_ref) {
		GuruHttpCliente::rest::response res_url(GuruHttpCliente::rest::get(url, opt));

		if (res_url.status_code() == 200) {
			Json::Value device_ref = res_url.json();

			if (!device_ref.empty()) {
				vector<modelodatosmame::device_ref> device_refs;

				for (Json::ValueIterator it = device_ref.begin(), itend = device_ref.end(); it != itend; ++it) {
					modelodatosmame::device_ref data;

					data.name = (*it).asString();

					device_refs.push_back(data);
				}

				for (vector<modelodatosmame::device_ref>::iterator it = device_refs.begin(), itend = device_refs.end(); it != itend; ++it) {
					if (std::find(xml_device_ref.begin(), xml_device_ref.end(), *it) == xml_device_ref.end())
						return false;
				}
			}

			return true;
		} else
			return false;
	}

	bool comparar_driver(const string& url, modelodatosmame::driver& xml_driver) {
		GuruHttpCliente::rest::response res_url(GuruHttpCliente::rest::get(url, opt));

		if (res_url.status_code() == 200) {
			Json::Value driver = res_url.json();

			if (!driver.empty()) {
				if (xml_driver.cocktail.compare(driver["cocktail"].asString()) == 0 &&
					xml_driver.color.compare(driver["color"].asString()) == 0 &&
					xml_driver.emulation.compare(driver["emulation"].asString()) == 0 &&
					xml_driver.graphic.compare(driver["graphic"].asString()) == 0 &&
					xml_driver.palettesize.compare(driver["palettesize"].asString()) == 0 &&
					xml_driver.protection.compare(driver["protection"].asString()) == 0 &&
					xml_driver.savestate.compare(driver["savestate"].asString()) == 0 &&
					xml_driver.sound.compare(driver["sound"].asString()) == 0 &&
					xml_driver.status.compare(driver["status"].asString()) == 0)
					return true;
				else
					return false;
			}

			return true;
		} else
			return false;
	}
/*
	int nada(const string& a, std::vector<modelodatosmame::chip>& b) {
		cout << a << endl;

		return 'a';
	}

	int ooo(int a ) { return 10*a; }
*/
	bool verificar(modelodatosmame::game machine) {
		try {
			GuruHttpCliente::rest::response res(GuruHttpCliente::rest::get(ws + "/games/" + machine.name, opt));

			if (res.status_code() == 200) {
#if defined ARMAMEC11
				//////////////////////////////[Pruebas]////////////////////////////////////////
				//				std::function<int (int)> o1 = std::bind(std::mem_fn(&XMLaArMameWS::ooo), this, std::placeholders::_1);
				//				auto o1 = std::bind(std::mem_fn(&XMLaArMameWS::ooo), this, std::placeholders::_1);
				/*
				std::function<int(int)> o3 = [&](int a) -> int { return ooo(a); };
				auto o2 = [&](int a) -> int { return ooo(a); };
				auto o1 = std::bind(&XMLaArMameWS::ooo, this, std::placeholders::_1);

				cout << o2(10) << o3(100);

				cout << o1(10) << endl;

				std::function<int (const string&, std::vector<modelodatosmame::chip>&) > f = std::bind(&XMLaArMameWS::nada, this, std::placeholders::_1, std::placeholders::_2);

				cout << f(string("Hola"), nuevo.chips);
				*/
				//				using namespace std::placeholders;
				//				std::function<bool(const std::string&, std::vector<modelodatosmame::chip>&)> f_chip = std::bind(&XMLaArMameWS::comparar_chip, this, _1, _2);
				/*
				std::function<bool(const std::string&, std::vector<modelodatosmame::chip>&)> f_chip2 = [&] (const std::string& a, std::vector<modelodatosmame::chip>& b) {
				this->XMLaArMameWS::comparar_chip(a, b);
				this->XMLaArMameWS::comparar_chip(res.json()["links"]["chip"].asString(), nuevo.chips);
				};
				*/
				//				std::function<bool(const std::string&, std::vector<modelodatosmame::chip>&)> f_chip2 = &XMLaArMameWS::comparar_chip;

				//				std::future<void> chip2(std::async(std::launch::async, f, res.json()["links"]["chip"].asString(), nuevo.chips));
				//////////////////////////////[Fin Pruebas]/////////////////////////////////////
				// NO compila en Linux.
				//				std::future<bool> chip(std::async(std::launch::async, &XMLaArMameWS::comparar_chip, this, res.json()["links"]["chip"].asString(), nuevo.chips));
				//				std::future<bool> roms(std::async(std::launch::async, &XMLaArMameWS::comparar_roms, this, res.json()["links"]["roms"].asString(), nuevo.roms));
				//				std::future<bool> device_ref(std::async(std::launch::async, &XMLaArMameWS::comparar_device_ref, this, res.json()["links"]["device_ref"].asString(), nuevo.device_refs));
				//				std::future<bool> driver(std::async(std::launch::async, &XMLaArMameWS::comparar_driver, this, res.json()["links"]["driver"].asString(), nuevo.driver));

				// SI compila en linux
				std::future<bool> chip(std::async(std::launch::async, [&]() -> bool { return comparar_chip(res.json()["links"]["chip"].asString(), machine.chips); }));
				std::future<bool> roms(std::async(std::launch::async, [&]() -> bool { return comparar_roms(res.json()["links"]["roms"].asString(), machine.roms); }));
				std::future<bool> device_ref(std::async(std::launch::async, [&]() -> bool { return comparar_device_ref(res.json()["links"]["device_ref"].asString(), machine.device_refs); }));
				std::future<bool> driver(std::async(std::launch::async, [&]() -> bool { return comparar_driver(res.json()["links"]["driver"].asString(), machine.driver); }));

				if (chip.get() && roms.get() && device_ref.get() && driver.get())
					maquinas++;
#else
				bool chip = comparar_chip(res.json()["links"]["chip"].asString(), nuevo.chips);
				bool roms = comparar_roms(res.json()["links"]["roms"].asString(), nuevo.roms);
				bool device_ref = comparar_device_ref(res.json()["links"]["device_ref"].asString(), nuevo.device_refs);
				bool driver = comparar_driver(res.json()["links"]["driver"].asString(), nuevo.driver);

				if (chip && roms && device_ref && driver)
					cout << "\r" << std::setfill('0') << std::setw(8) << consultas++ << progreso();
#endif
			} else if (res.status_code() == 404) {
				cout << "*" << machine.description << "(" << machine.name << ")" << endl;
			} else
				cout << "Error obteniendo datos del juego " << machine.name << " Error:" << res.status_code() << endl;

		} catch (GuruHttpCliente::GuruHttpException& e) {
			cout << e.what() << endl;
		}

		return true;
	}

	void game(modelodatosmame::game& machine) {
	
		static GuruPool<std::future<bool> >	pool(simultaneos);

		std::future<bool>* item;

		// recorro el pool y aquellos thread que terminaron los libero del pool para que quede el lugar libre para otro.
		// Si no hay ningun thread que liberar espero 250 milisegundos.
		// cuando libero un thread corto el ciclo y pido un recurso al pool para el nuevo thread.
		do {
			int ocupado = 0, libre = 0;
			for (GuruPool<std::future<bool> >::iterator it = pool.begin(), itend = pool.end(); it != itend; ++it) {
				if (it->second == GuruPool<std::future<bool> >::tomado) {
					if (it->first->wait_for(std::chrono::milliseconds(20)) == std::future_status::ready) {
						cout << "\r" << std::setfill('0') << std::setw(8) << maquinas << progreso();
						pool.liberar(it->first);
						libre++;
						it = itend;
						it--;
					} else
						ocupado++;
				} else {
					libre++;
					it = itend;
					it--;
				}
			}

			if (ocupado >= pool.capacidad())
				std::this_thread::sleep_for(std::chrono::milliseconds(250));
			else
				break;
		} while (true);

		item = pool.obtener();

		if (item != NULL) 
			*item = std::async(std::launch::async, [=]() -> bool { return this->verificar(machine); });
	}

	void version(const GuruMAME::version& ver) {

		cout << "Verificando la version: " << ver.build << endl;

		try {
			GuruHttpCliente::rest::response res(GuruHttpCliente::rest::get(ws + "/version", opt));

			if (res.status_code() == 200) { 
				std::cout << "Version:" << res.json()["build"].asString() << std::endl;
			} else if (res.status_code() == 404)
				cout << "Version inexistente." << endl;
			else 
				cout << "Error consultando version, error " << res.status_code() << endl;

		} catch (GuruHttpCliente::GuruHttpException& e) {
			cout << e.what() << endl;
			finalizar();
		}
	};
};

// armamewscmp.exe -i c:\Instaladores\Mame-185\listxml.xml --proxy=10.1.1.86 --usuario=frossi@bancocredicoop.coop --clave=Soda0600
int main(int argc, char* argv[])
{
// ---------------------------------------------------------------------------------------
	struct arg_lit*  ayuda			= arg_lit0("h","help", "Muestra la ayuda.");
	struct arg_file* opt_xml		= arg_file0("i","xml","<xml>", "Archivo xml, -listxml del M.A.M.E..");
	struct arg_str*  opt_url		= arg_str0("u", "url", "<URL>", "URL del ArMameWS (default www.planetaguru.com.ar).");
	struct arg_str*  opt_proxy		= arg_str0(NULL, "proxy", "<IP>", "Servidor Proxy.");
	struct arg_str*  opt_usuario	= arg_str0(NULL, "usuario", "<Usuario>", "Nombre de usuario para el proxy.");
	struct arg_str*  opt_clave		= arg_str0(NULL, "clave", "<Clave>", "Clave de usuario para el proxy.");
	struct arg_int*  opt_concu		= arg_int0("s", "simultaneos", "<Simultaneos>", "Cantidad de juegos simultaneos a verificar (default 5).");
	struct arg_end*  end			= arg_end(8);

	void* argtable[] = {ayuda, opt_xml, opt_url, opt_proxy, opt_usuario, opt_clave, opt_concu, end};

	if (arg_nullcheck(argtable) != 0) {
        cout << "insufficient memory" << endl;
        return 2;
	}

	int nerrors = arg_parse(argc,argv,argtable);

	if (ayuda->count > 0) {
		arg_print_syntax(stdout,argtable,"\n");
		return 1;
	}

    if (nerrors > 0) {
        arg_print_errors(stdout,end,"");
        cout << "Pruebe --help por mas informacion" << endl;
		return 3;
        }

	string entrada;
	if (opt_xml->count > 0) entrada = opt_xml->filename[0];

	string url("www.planetaguru.com.ar");
	if (opt_url->count > 0) url = opt_url->sval[0];

	string proxy;
	if (opt_proxy->count > 0) proxy = opt_proxy->sval[0];

	string usuario;
	if (opt_usuario->count > 0) usuario = opt_usuario->sval[0];

	string clave;
	if (opt_clave->count > 0) clave = opt_clave->sval[0];

	int concurrentes=5;
	if (opt_concu->count > 0) concurrentes = opt_concu->ival[0];

    arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
// ---------------------------------------------------------------------------------------

	XMLaArMameWS p;

	p.xml(entrada);

	p.concurrentes(concurrentes);
	p.url(url);
	p.proxy(proxy, usuario, clave);

	p.iniciar();

	cout << "\rTiempo de procesamiento en sec.: " << p.tiempo_sec() << endl;

	return 0;
}
