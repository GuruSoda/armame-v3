#include <argtable/argtable2.h>

#include <GuruHttp/GuruhttpCliente.hpp>
#include <GuruHttp/GuruhttpClienteREST.hpp>

#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
	struct arg_str* param_busqueda = arg_str0("b", "busqueda", "busqueda", "Busqueda en nombre/rom/description/manufacturer/etc.");
	struct arg_str* param_game = arg_str0("g", "game", "Game", "Informa sobre un juego especifico.");
	struct arg_str* param_directorio = arg_str0("d", "directorio", "Directorio", "Directorio a descargar la rom.");
	struct arg_str* param_proxy = arg_str0("p", "proxy", "servidor", "Proxy a utilizar.");
	struct arg_str* param_url = arg_str0("u", "url", "url", "URL del catalogador, default http://www.planetaguru.com.ar/armamews/.");
	struct arg_end* end = arg_end(10);
	void* argtable[] = { param_busqueda, param_proxy, param_game, param_directorio, param_url, end };
	int nerrors;

	if (arg_nullcheck(argtable) != 0) {
		std::cout << "insufficient memory" << std::endl;
		return 2;
	}

	nerrors = arg_parse(argc, argv, argtable);

	if (nerrors > 0) {
		arg_print_errors(stdout, end, "");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		return 1;
	}

	std::string busqueda;
	if (param_busqueda->count > 0) busqueda = param_busqueda->sval[0];

	std::string url = "http://www.planetaguru.com.ar/armamews/";
	if (param_url->count > 0) url = param_url->sval[0];

	std::string proxy;
	if (param_proxy->count > 0) proxy = param_proxy->sval[0];

	std::string game;
	if (param_game->count > 0) game = param_game->sval[0];

	std::string directorio;
	if (param_directorio->count > 0) directorio = param_directorio->sval[0];

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

	// ---------[Fin Procesamiento de Parametros]-------------------------

	if (!busqueda.empty() && !game.empty()) {
		cout << "Solo una opcion, --busqueda o --game" << endl;
		return 3;
	}

	GuruHttpCliente::rest::response res;
	GuruHttpCliente::opciones_get opt;

	if (!proxy.empty()) opt.proxy_server(proxy);

	if (!busqueda.empty()) url += "?b=" + busqueda;
	else if (!game.empty()) url += "?g=" + game;

	try {
		res = GuruHttpCliente::rest::get(url, opt);

		if (res.status_code() != 200) {
			cout << "Error: status code " << res.status_code() << endl;
			return 4;
		}

		if (!game.empty()) {
			std::cout << "Name:" << res.json()["Name"].asString() << std::endl;
			std::cout << "Description:" << res.json()["Description"].asString() << std::endl;
			std::cout << "Manufacturer:" << res.json()["Manufacturer"].asString() << std::endl;
			std::cout << "Year:" << res.json()["Year"].asString() << std::endl;
		} else if (!busqueda.empty()) {
			uint32_t t = 1;
			for (Json::ValueIterator it = res.json().begin(); it != res.json().end(); ++it, t++) {
				std::cout << t << ":" << std::endl;
				std::cout << "Name:" << (*it)["Name"].asString() << std::endl;
				std::cout << "Description:" << (*it)["Description"].asString() << std::endl;
				std::cout << "Manufacturer:" << (*it)["Manufacturer"].asString() << std::endl;
				std::cout << "Year:" << (*it)["Year"].asString() << std::endl;
			}
		}
	} catch (GuruHttpCliente::GuruHttpException& e) {
		cout << "Error:" << e.what() << endl;
	}

	return 0;
}

