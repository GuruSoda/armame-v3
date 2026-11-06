#ifndef __ARMAMEWS_HPP__
#define __ARMAMEWS_HPP__

#include <string>
#include <future>

#include <jsoncpp/json.h>

#include <GuruHttp/GuruhttpResponse.hpp>
#include <GuruHttp/GuruhttpREST.hpp>

#include <GuruToken.hpp>
#include <GuruString_algo.hpp>
#include <GuruSQLite.hpp>
#include <GuruDirectorio.hpp>

GuruSQLite::bd			mame;

static Json::Value& SQLite2JsonObject(GuruSQLite::bd& base, const string& consulta, Json::Value& resultado) {
	GuruSQLite::resultado res = base.ejecutarEX(consulta);

	resultado.clear();

	for (int i = 0; i < res.columnas(); i++) {
		resultado[res.nombre_columna(i)] = res->getString(i);
	}

	return resultado;
}

static Json::Value& SQLite2JsonArray1(GuruSQLite::bd& base, const string& consulta, const string& vector, Json::Value& resultado) {
	GuruSQLite::resultado res = base.ejecutar(consulta);

	resultado.clear();

	for (GuruSQLite::resultado::iterator it = res.begin(), itend = res.end(); it != itend; ++it) {
		resultado[vector].append(Json::Value(res->getString(0)));
	}

	return resultado;
}

static Json::Value& SQLite2JsonArray1(GuruSQLite::bd& base, const string& consulta, Json::Value& resultado) {
	GuruSQLite::resultado res = base.ejecutar(consulta);

	resultado.clear();

	for (GuruSQLite::resultado::iterator it = res.begin(), itend = res.end(); it != itend; ++it) {
		resultado.append(Json::Value(res->getString(0)));
	}

	return resultado;
}

static Json::Value& SQLite2JsonArray2(GuruSQLite::bd& base, const string& consulta, const string& vector, Json::Value& resultado) {
	GuruSQLite::resultado res = base.ejecutar(consulta);

	resultado.clear();

	for (GuruSQLite::resultado::iterator it = res.begin(), itend = res.end(); it != itend; ++it) {
		resultado[vector][res->getString(0)] = res->getString(1);
	}

	return resultado;
}

static Json::Value& SQLite2JsonArrayObject(GuruSQLite::bd& base, const string& consulta, Json::Value& resultado) {
	GuruSQLite::resultado res = base.ejecutar(consulta);

	resultado.clear();

	for (GuruSQLite::resultado::iterator it = res.begin(), itend = res.end(); it != itend; ++it) {
		Json::Value item;
		for (int i = 0; i < res.columnas(); i++) {
			item[res.nombre_columna(i)] = it->getString(i);
		}

		resultado.append(item);
	}

	return resultado;
}

class ArMameWs : public GuruHttpREST {
	enum opt_games {
		games_none = 0x00,
		games_name = 0x01,
		games_description = 0x02,
		games_namedescription = 0x04,
		games_descriptionlink = 0x08
	};

	enum opt_game {
		game_none = 0x00,
		game_minimal = 0x01,
		game_basic = 0x02,
		game_normal = 0x04,
		game_full = 0x08,
		game_link = 0x10
	};

	enum filtro_games {
		filtro_games_none = 0x01,			// no muestra el listado de machines, solo los resumenes.
		filtro_games_all = 0x02,			// toda la lista.
		filtro_games_game = 0x04,			// solo juegos, no bios, etc.
		filtro_games_bios = 0x08,			// solo bios.
		filtro_games_device = 0x10,			// solo dispositivos.
		filtro_games_mechanical = 0x20,		// solo mecanicos.
		filtro_games_runnable = 0x40,		// marcados como runnable
		filtro_games_unique = 0x80,			// juegos unicos, sin cloneof y romof.
		filtro_games_cloneof = 0x100,		// marcados como runnable
		filtro_games_romof = 0x200,			// marcados como runnable
		filtro_games_not_game = 0x400,		// solo juegos, no bios, etc.
		filtro_games_not_bios = 0x800,		// solo bios.
		filtro_games_not_device = 0x1000,	// solo dispositivos.
		filtro_games_not_mechanical = 0x2000,// solo mecanicos.
		filtro_games_not_runnable = 0x4000,	// marcados como no runnable
		filtro_games_not_cloneof = 0x8000,	// no es un clon de otro juego
		filtro_games_not_romof = 0x10000,	// no tiene rom de otro juego
		filtro_games_not_unique = 0x20000	// es un juego que tiene rom de otro o clon de otro
	};

	enum opt_game str_game(const string& opt) {
		if (opt.compare("minimal") == 0)		// nombre y descripcion
			return opt_game::game_minimal;
		else if (opt.compare("basic") == 0)		// nombre, descripcion, fabricante, año, clon de, rom de,
			return opt_game::game_basic;
		else if (opt.compare("normal") == 0)	// nombre, descripcion, fabricante, año, clon de, rom de, roms
			return opt_game::game_normal;
		else if (opt.compare("full") == 0)		// nombre, descripcion, fabricante, año, roms, resto de los atributos
			return opt_game::game_full;
		else if (opt.compare("link") == 0)		// que muestro los links a los diferentes atributos del juego
			return opt_game::game_link;
		else
			return opt_game::game_basic;
	}

	enum opt_games str_games(const string& opt) {
		if (opt.empty()) return opt_games::games_name;

		if (opt.compare("name") == 0)
			return opt_games::games_name;
		else if (opt.compare("description") == 0)
			return opt_games::games_description;
		else if (opt.compare("namedescription") == 0)
			return opt_games::games_namedescription;
		else if (opt.compare("descriptionlink") == 0)
			return opt_games::games_descriptionlink;
		else
			return opt_games::games_name;
	}

	enum filtro_games str_filtro_games(const string& f) {
		int32_t filtro = 0;

		GuruTokenEx t("|");

		size_t total = t.extraer(f);

		for (size_t i = 0; i < total; i++) {
			if (t[i].compare("none") == 0) {
				filtro = filtro_games::filtro_games_none;
				return static_cast<filtro_games>(filtro);
			} else if (t[i].compare("all") == 0) {
				filtro = filtro_games::filtro_games_all;
				return static_cast<filtro_games>(filtro);
			} else if (t[i].compare("game") == 0)
				filtro |= filtro_games::filtro_games_game;
			else if (t[i].compare("bios") == 0)
				filtro |= filtro_games::filtro_games_bios;
			else if (t[i].compare("device") == 0)
				filtro |= filtro_games::filtro_games_device;
			else if (t[i].compare("mechanical") == 0)
				filtro |= filtro_games::filtro_games_mechanical;
			else if (t[i].compare("runnable") == 0)
				filtro |= filtro_games::filtro_games_runnable;
			else if (t[i].compare("unique") == 0)
				filtro |= filtro_games::filtro_games_unique;
			else if (t[i].compare("cloneof") == 0)
				filtro |= filtro_games::filtro_games_cloneof;
			else if (t[i].compare("romof") == 0)
				filtro |= filtro_games::filtro_games_romof;
			else if (t[i].compare("!game") == 0)
				filtro |= filtro_games::filtro_games_not_game;
			else if (t[i].compare("!bios") == 0)
				filtro |= filtro_games::filtro_games_not_bios;
			else if (t[i].compare("!device") == 0)
				filtro |= filtro_games::filtro_games_not_device;
			else if (t[i].compare("!mechanical") == 0)
				filtro |= filtro_games::filtro_games_not_mechanical;
			else if (t[i].compare("!runnable") == 0)
				filtro |= filtro_games::filtro_games_not_runnable;
			else if (t[i].compare("!cloneof") == 0)
				filtro |= filtro_games::filtro_games_not_cloneof;
			else if (t[i].compare("!romof") == 0)
				filtro |= filtro_games::filtro_games_not_romof;
			else if (t[i].compare("!unique") == 0)
				filtro |= filtro_games::filtro_games_not_unique;

		}

		return (filtro == 0) ? filtro_games::filtro_games_all : static_cast<filtro_games>(filtro);
	}

public:
	ArMameWs() {}
	virtual ~ArMameWs() {}

	bool enviarCache(const std::string& archivo) {
		GuruDirectorio::GuruArchivo ar;

		if ((ar = GuruDirectorio::propiedades(request()->config()->dirApps() + archivo)).Existe()) {
			request()->recurso().info(ar);
			response()->content_type("application/json");
			response()->enviar_archivo();
			return true;
		} else 
			return false;
	}

	bool enviarDesdeCache() {

		string str(request()->recurso().subdirectorio() + request()->recurso().archivo() + ".json");
		std::string::size_type lugar = 0;

		// cambio el dividor de directori por un guion medio.
		while ((lugar = str.find('/', lugar)) != std::string::npos) {
			str.erase(lugar, 1);
			str.insert(lugar, 1, '-');
		}

		// me dijo si existe el directorio donde esta el cache de las consultas.
		string cache_dir(request()->config()->env("cache"));
		if (cache_dir.empty()) { cache_dir = "cache"; request()->config()->env("cache", "cache"); }
		if (!GuruDirectorio::existe(request()->config()->dirApps() + cache_dir)) GuruDirectorio::crearDirectorioRecursivo(request()->config()->dirApps() + cache_dir);

		// me dijo si esta el archivo con la respuesta a enviar
		string cache_archivo(request()->config()->dirApps() + cache_dir + GuruDirectorio::divisor_directorio + str);
		if (!GuruDirectorio::existe(cache_archivo)) return false;
	
		// envio el archivo.
		GuruDirectorio::GuruArchivo ar(GuruDirectorio::propiedades(cache_archivo));

		request()->recurso().info(ar);
		response()->content_type("application/json");
		response()->enviar_archivo();

		return true;
	}

	void escribirCache(const string& info) {

		string str(request()->recurso().subdirectorio() + request()->recurso().archivo() + ".json");
		std::string::size_type lugar = 0;

		// cambio el divisor de directorio por un guion medio.
		while ((lugar = str.find('/', lugar)) != std::string::npos) {
			str.erase(lugar, 1);
			str.insert(lugar, 1, '-');
		}

		string archivo_cache(request()->config()->dirApps() + request()->config()->env("cache") + GuruDirectorio::divisor_directorio + str);

		std::ofstream ofs(archivo_cache);

		if (ofs.is_open()) {
			ofs << info;
			ofs.close();
		}
	}

	void procesarGet() {

		init();

		if (es("/listgames")) list_games(str_games(parametro("o")), str_filtro_games(parametro("f")));
		else if (es("/games")) games(parametro("page"), parametro("limit"), str_filtro_games(parametro("f")));
		else if (es("/games/{nombre}")) std::async(std::launch::async, [&]() {info_juego(var("nombre"), str_game(parametro("o"))); }).get();
		else if (es("/games/{nombre}/{atributo}")) std::async(std::launch::async, [&]() {info_detallada_juego(var("nombre"), var("atributo")); }).get();
		else if (es("/manufacturers")) manufacturers();
		else if (es("/manufacturers/{nombre}"));
		else if (es("/search")) {
			if (!parametro("p").empty())
				buscar_game(parametro("p"));
			else
				throw GuruhttpExcepcion(400);
		}
		else if (es("/version")) version();
		else if (es("/random")) random();
		else if (es("/random/{atributo}")) random(var("atributo"));
		else throw GuruhttpExcepcion(404, "No Encontrado.");

		return ;

		if (equal(0, "games")) {
			switch (totalsubdir()) {
			case 1: // games | games?o=name|descripcion|namedescripcion
					// http://localhost/armamews/games?o=namedescription&f=bios|games|devices|mechanical|
					list_games(str_games(parametro("o")), str_filtro_games(parametro("f")));
					break;
			case 2: // games/gng|rygar|pacmam
					std::async(std::launch::async, [&]() {info_juego(subdir(1), str_game(parametro("o"))); }).get();
					break;
			case 3: // games/gng/roms|download|title|snap|chip|display
					std::async(std::launch::async, [&]() {info_detallada_juego(subdir(1), subdir(2)); }).get();
					break;
			default:
					break;
			}
		} else if (equal(0, "manufacturers")) {
			switch (totalsubdir()) {
			case 1: // manufacturer
				manufacturers();
				break;
			case 2: // manufacturer/capcom
				throw GuruhttpExcepcion(501);
				break;
			case 3: // manufacturer/capcom/games
				throw GuruhttpExcepcion(501);
				break;
			default:
				throw GuruhttpExcepcion(404);
				break;
			}
		} else if (equal(0, "search")) {
			switch (totalsubdir()) {
			case 1: // search | search?p=ghost
				if (!parametro("p").empty())
					buscar_game(parametro("p"));
				else
					throw GuruhttpExcepcion(400);
				break;
			case 2: // search/ghost | //search/rygar
				throw GuruhttpExcepcion(501);
				break;
			case 3: // manufacturer/capcom/games
				throw GuruhttpExcepcion(501);
				break;
			default:
				throw GuruhttpExcepcion(404);
				break;
			}
		} else if (equal(0, "version")) {
			switch (totalsubdir()) {
			case 1:
				version();
				break;
			default:
				throw GuruhttpExcepcion(404);
				break;
			}
		} else if (equal(0, "random")) {
			switch (totalsubdir()) {
			case 1: // /random --> envia un snap al azar
				random();
				break;
			case 2: // /random/snap|title|icons|artwork|cabinets|flyers|marquees|versus
				random(subdir(1));
				break;
			default:
				throw GuruhttpExcepcion(404);
				break;
			}
		} else throw GuruhttpExcepcion(400);
	}

//	Ejem:
//	http://localhost/armamews/games?f=unique|!bios|!device&o=descriptionlink
	void list_games(const opt_games opciones, const filtro_games filtro) {
		if (enviarCache("games.json")) return;

		Json::Value root;

		try {
			root["total"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game")->getInt64(0, -1));
			root["total_unique"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where cloneof = '' and romof = ''")->getInt64(0, -1));
			root["total_games_unique"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where cloneof = '' and romof = '' and isbios = 0 and isdevice = 0 and ismechanical = 0")->getInt64(0, -1));
			root["total_games"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where isbios = 0 and isdevice = 0 and ismechanical = 0")->getInt64(0, -1));
			root["total_bios"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where isdevice = 0 and isbios != 0 and ismechanical = 0")->getInt64(0, -1));
			root["total_device"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where isdevice != 0 and isbios = 0 and ismechanical = 0")->getInt64(0, -1));
			root["total_mechanical"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_game) from game where isdevice = 0 and isbios = 0 and ismechanical != 0")->getInt64(0, -1));

			if (!(filtro & filtro_games::filtro_games_none)) {
				string str_filtro;

				str_filtro += "where id_game != 0 ";

				if (!(filtro & filtro_games::filtro_games_all)) {
					str_filtro += (filtro & filtro_games::filtro_games_bios) ? " and isbios != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_bios) ? " and isbios = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_device) ? " and isdevice != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_device) ? " and isdevice = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_mechanical) ? " and ismechanical != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_mechanical) ? " and ismechanical = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_runnable) ? " and runnable = 1 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_runnable) ? " and runnable = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_unique) ? " and cloneof = '' and romof = ''" : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_unique) ? " and cloneof != '' and romof != ''" : "";
					str_filtro += (filtro & filtro_games::filtro_games_cloneof) ? " and cloneof != '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_cloneof) ? " and cloneof = '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_romof) ? " and romof != '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_romof) ? " and romof = '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_game) ? "" : "";
				}

				if (opciones & opt_games::games_name) {
					GuruSQLite::resultado res(mame.ejecutar("select name from game " + str_filtro));
					for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) root["machines"].append(Json::Value(it->getString(0)));
				} else if (opciones & opt_games::games_description) {
					GuruSQLite::resultado res(mame.ejecutar("select description from game " + str_filtro));
					for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) root["machines"].append(Json::Value(it->getString(0)));
				} else if (opciones & opt_games::games_namedescription) {
					GuruSQLite::resultado res(mame.ejecutar("select name,description from game " + str_filtro));
					for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) root["machines"][it->getString(0)] = it->getString(1);
				} else if (opciones & opt_games::games_descriptionlink) {
					GuruSQLite::resultado res(mame.ejecutar("select name,description from game " + str_filtro));
					for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) root["machines"][it->getString(1)] = "http://" + request()->atributo("Host") + request()->recurso().directorio() + "games/" + it->getString(0);
				}

				cout << "Filtro:" << str_filtro << endl;
			}

		} catch (GuruSQLite::GuruSQLiteException& e) {
			Json::StyledWriter writer;

			root["error"] = e.what();
		}

		enviar_json(root);

		std::ofstream ofs(request()->config()->dirApps() + "games.json");

		if (ofs.is_open()) {
			ofs << root.toStyledString();
			ofs.close();
		}
	}

/*
Resultado final:
{
	"count": 82,
	"next": "http://swapi.dev/api/people/?page=8",
	"previous": "http://swapi.dev/api/people/?page=6",
	"results": [
		{
			"name": "Sly Moore",
			"height": "178",
			"mass": "48",
			"hair_color": "none",
			"skin_color": "pale",
			"eye_color": "white",
			"birth_year": "unknown",
			"gender": "female",
			"homeworld": "http://swapi.dev/api/planets/60/",
			"films": [
				"http://swapi.dev/api/films/5/",
				"http://swapi.dev/api/films/6/"
			],
			"species": [],
			"vehicles": [],
			"starships": [],
			"created": "2014-12-20T20:18:37.619000Z",
			"edited": "2014-12-20T21:17:50.496000Z",
			"url": "http://swapi.dev/api/people/82/"
	},
	{
	}
   ]
}
*/
//	http://localhost/armamews/games?f=unique|!bios|!device&page=2&limit=50
	void games(const string& page, const string& limit, const filtro_games filtro) {
		Json::Value root;

		uint32_t int_page = atol(page.c_str());
		uint32_t int_limit = atol(limit.c_str());

		if (int_page == 0) int_page = 1;

		if (int_limit == 0) int_limit = 50;

		try {
			if (!(filtro & filtro_games::filtro_games_none)) {
				string str_filtro, param_filtro;

				str_filtro += "where id_game != 0 ";

				if (!(filtro & filtro_games::filtro_games_all)) {
					str_filtro += (filtro & filtro_games::filtro_games_bios) ? " and isbios != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_bios) ? " and isbios = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_device) ? " and isdevice != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_device) ? " and isdevice = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_mechanical) ? " and ismechanical != 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_mechanical) ? " and ismechanical = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_runnable) ? " and runnable = 1 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_runnable) ? " and runnable = 0 " : "";
					str_filtro += (filtro & filtro_games::filtro_games_unique) ? " and cloneof = '' and romof = ''" : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_unique) ? " and cloneof != '' and romof != ''" : "";
					str_filtro += (filtro & filtro_games::filtro_games_cloneof) ? " and cloneof != '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_cloneof) ? " and cloneof = '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_romof) ? " and romof != '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_not_romof) ? " and romof = '' " : "";
					str_filtro += (filtro & filtro_games::filtro_games_game) ? "" : "";

					param_filtro = request()->parametro("f");
				}
				
				GuruSQLite::resultado res(mame.ejecutar("select name, id_game from game " + str_filtro + " order by name limit " + GuruStringAlgo::itos(int_limit) + " offset " + GuruStringAlgo::itos(int_limit * (int_page-1))));
				Json::Value result(Json::arrayValue);

				for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) {
					result.append(info_juego_json(it->getString(0)));
				}

				if (result.empty()) throw GuruhttpExcepcion(404);

				int64_t total = mame.ejecutarEX("select count(id_game) from game " + str_filtro)->getInt64(0, -1);

				if (total < (int_limit*int_page))
					root["next"] = Json::nullValue;
				else
					root["next"] = "http://" + request()->atributo("Host") + request()->recurso().directorio() + "games?page=" + GuruStringAlgo::itos(int_page + 1) + "&limit=" + GuruStringAlgo::itos(int_limit) + (param_filtro.empty() ? "" : "&f=" + param_filtro);

				if (int_page == 1)
					root["previous"] = Json::nullValue;
				else
					root["previous"] = "http://" + request()->atributo("Host") + request()->recurso().directorio() + "games?page=" + GuruStringAlgo::itos(int_page - 1) + "&limit=" + GuruStringAlgo::itos(int_limit) + (param_filtro.empty() ? "" : "&f=" + param_filtro);
				
				root["results"] = result;

				root["total"] = static_cast<Json::Value::Int64>(total);
			}

		} catch (GuruSQLite::GuruSQLiteException& e) {
			Json::StyledWriter writer;

			root.clear();

			root["error"] = e.what();
		}

		enviar_json(root);
	}

	void manufacturers() {
		Json::Value root;

		if (enviarCache("manufacturers.json")) return;

		try {
			root["Total"] = static_cast<Json::Value::Int64>(mame.ejecutarEX("select count(id_manufacturer) from manufacturer")->getUInt64(0, -1));

			GuruSQLite::resultado res(mame.ejecutar("select name from manufacturer"));

			Json::Value juegos;
			for (GuruSQLite::resultado::iterator it = res.begin(), end = res.end(); it != end; ++it) {
				//	root["Juegos"][it->getString(0)] = it->getString(1);
				root["manufacturers"].append(Json::Value(it->getString(0)));
			}

		} catch (GuruSQLite::GuruSQLiteException& e) {
			root["error"] = e.what();
		}

		enviar_json(root);

// escribo el cache
		std::ofstream ofs(config()->dirApps() + "manufacturers.json");

		if (ofs.is_open()) {
			ofs << root.toStyledString();
			ofs.close();
		}
	}

	void download(const string& game, const string& bajar) {

		std::string ruta_archivo(config()->env(bajar) + DIVISOR_DIRECTORIO + game);

		if (bajar.compare("rom") == 0) ruta_archivo += ".zip";
		else if (bajar.compare("icons") == 0) ruta_archivo += ".ico";
		else if (bajar.compare("videosnaps") == 0) ruta_archivo += ".mp4";
		else ruta_archivo += ".png";

		GuruDirectorio::GuruArchivo ar;

		ar = GuruDirectorio::propiedades(ruta_archivo);

		if (ar.Existe() && ar.EsArchivo()) {
			response()->content_type(GuruhttpAlgo::mime(ar.nombre()));
			request()->recurso().info(ar);
			response()->atributo("Content-Disposition", "inline; filename=" + GuruStringAlgo::comillas(GuruDirectorio::GuruSplitPath(ar.nombre()).nombre_ext()));
			response()->enviar_archivo();
		} else throw GuruhttpExcepcion(404);
	}

	void buscar(const string& busqueda) {

		string consulta;

		consulta += "select a.id_game, a.name, a.description, d.name, b.name, a.year, a.cloneof, a.romof ";
		consulta += "from game a, manufacturer b, sourcefile d ";
		consulta += "where a.manufacturer = b.id_manufacturer and a.sourcefile = d.id_sourcefile and ";
		consulta += "(a.description like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or a.name like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or b.name like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or d.name like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or a.cloneof like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or a.romof like " + GuruSQLite::comillas("%" + busqueda + "%");
		consulta += " or a.year like " + GuruSQLite::comillas("%" + busqueda + "%") + ")";

		try {
			GuruSQLite::resultado res = mame.ejecutar(consulta);

			Json::Value vector;

			for (GuruSQLite::resultado::iterator it = res.begin(), end; it != end; ++it) {
				Json::Value root;

				root["name"] = res->getString(1);
				root["description"] = res->getString(2);
				root["sourcefile"] = res->getString(3);
				root["manufacturer"] = res->getString(4);
				root["year"] = res->getString(5);
				root["cloneof"] = res->getString(6);
				root["romof"] = res->getString(7);

				vector.append(root);
			}

			if (vector.empty()) throw GuruhttpExcepcion(404);

			enviar_json(vector);
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
	}

	void buscar_game(const string& busqueda) {

		string consulta;

		consulta = "select a.id_game, a.name, a.description ";
		consulta += "from game a ";
		consulta += "where a.description like " + GuruSQLite::comillas("%" + busqueda + "%") + " or a.name like " + GuruSQLite::comillas("%" + busqueda + "%");

		try {
			GuruSQLite::resultado res = mame.ejecutar(consulta);

			Json::Value vector;

			for (GuruSQLite::resultado::iterator it = res.begin(), end; it != end; ++it) {
				Json::Value root;

				root["name"] = res->getString(1);
				root["description"] = res->getString(2);
				root["game"] = "http://" + atributo("Host") + recurso().directorio() + "games/" + res->getString(1);

				vector.append(root);
			}

			if (vector.empty()) throw GuruhttpExcepcion(404);

			enviar_json(vector);
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
	}

	Json::Value info_juego_json(const string& game) {
		Json::Value root;

		std::string consulta;

		try {
			consulta = "select g.id_game, g.name, g.year, g.description, m.name as manufacturer, s.name as sourcefile, g.cloneof, g.romof, case(runnable) when 1 then 'Yes' when 0 then 'No' end as runnable, case(isbios) when 1 then 'Yes' when 0 then 'No' end as isbios, case(isdevice) when 1 then 'Yes' when 0 then 'No' end as isdevice, case(ismechanical) when 1 then 'Yes' when 0 then 'No' end as ismechanical \
						from game g, sourcefile s, manufacturer m \
						where g.sourcefile = s.id_sourcefile and g.manufacturer = m.id_manufacturer and g.name = " + GuruStringAlgo::comilla_simple(game);
			SQLite2JsonObject(mame, consulta, root);

			if (!root.empty()) {
				// acceso a los Extras
				std::string titles(request()->config()->env("titles") + DIVISOR_DIRECTORIO + game + ".png");
				std::string snap(request()->config()->env("snap") + DIVISOR_DIRECTORIO + game + ".png");
				std::string artwork(request()->config()->env("artwork") + DIVISOR_DIRECTORIO + game + ".png");
				std::string flyers(request()->config()->env("flyers") + DIVISOR_DIRECTORIO + game + ".png");
				std::string cabinets(request()->config()->env("cabinets") + DIVISOR_DIRECTORIO + game + ".png");
				std::string cpanel(request()->config()->env("cpanel") + DIVISOR_DIRECTORIO + game + ".png");
				std::string marquees(request()->config()->env("marquees") + DIVISOR_DIRECTORIO + game + ".png");
				std::string pcb(request()->config()->env("pcb") + DIVISOR_DIRECTORIO + game + ".png");
				std::string manuals(request()->config()->env("manuals") + DIVISOR_DIRECTORIO + game + ".png");
				std::string devices(request()->config()->env("devices") + DIVISOR_DIRECTORIO + game + ".png");
				std::string cabdevs(request()->config()->env("cabdevs") + DIVISOR_DIRECTORIO + game + ".png");
				std::string icons(request()->config()->env("icons") + DIVISOR_DIRECTORIO + game + ".ico");

				std::string logo(request()->config()->env("logo") + DIVISOR_DIRECTORIO + game + ".png");
				std::string versus(request()->config()->env("versus") + DIVISOR_DIRECTORIO + game + ".png");
				std::string gameover(request()->config()->env("gameover") + DIVISOR_DIRECTORIO + game + ".png");
				std::string ends(request()->config()->env("ends") + DIVISOR_DIRECTORIO + game + ".png");
				std::string artpreview(request()->config()->env("artpreview") + DIVISOR_DIRECTORIO + game + ".png");
				std::string bosses(request()->config()->env("bosses") + DIVISOR_DIRECTORIO + game + ".png");
				std::string howto(request()->config()->env("howto") + DIVISOR_DIRECTORIO + game + ".png");
				std::string warning(request()->config()->env("warning") + DIVISOR_DIRECTORIO + game + ".png");
				std::string select(request()->config()->env("select") + DIVISOR_DIRECTORIO + game + ".png");
				std::string videosnaps(request()->config()->env("videosnaps") + DIVISOR_DIRECTORIO + game + ".mp4");

				std::string url;

				url = "http://" + request()->atributo("Host") + request()->recurso().directorio() + "games/" + game;

				if (GuruDirectorio::existe(titles)) root["titles"] = url + "/titles";
				if (GuruDirectorio::existe(snap)) root["snap"] = url + "/snap";
				if (GuruDirectorio::existe(artwork)) root["artwork"] = url + "/artwork";
				if (GuruDirectorio::existe(flyers)) root["flyers"] = url + "/flyers";
				if (GuruDirectorio::existe(cabinets)) root["cabinets"] = url + "/cabinets";
				if (GuruDirectorio::existe(cpanel)) root["cpanel"] = url + "/cpanel";
				if (GuruDirectorio::existe(marquees)) root["marquees"] = url + "/marquees";
				if (GuruDirectorio::existe(pcb)) root["pcb"] = url + "/pcb";
				if (GuruDirectorio::existe(manuals)) root["manuals"] = url + "/manuals";
				if (GuruDirectorio::existe(devices)) root["devices"] = url + "/devices";
				if (GuruDirectorio::existe(cabdevs)) root["cabdevs"] = url + "/cabdevs";
				if (GuruDirectorio::existe(icons)) root["icons"] = url + "/icons";

				if (GuruDirectorio::existe(logo)) root["logo"] = url + "/logo";
				if (GuruDirectorio::existe(versus)) root["versus"] = url + "/versus";
				if (GuruDirectorio::existe(gameover)) root["gameover"] = url + "/gameover";
				if (GuruDirectorio::existe(ends)) root["ends"] = url + "/ends";
				if (GuruDirectorio::existe(artpreview)) root["artpreview"] = url + "/artpreview";
				if (GuruDirectorio::existe(bosses)) root["bosses"] = url + "/bosses";
				if (GuruDirectorio::existe(howto)) root["howto"] = url + "/howto";
				if (GuruDirectorio::existe(warning)) root["warning"] = url + "/warning";
				if (GuruDirectorio::existe(select)) root["select"] = url + "/select";
				if (GuruDirectorio::existe(videosnaps)) root["videosnaps"] = url + "/videosnaps";

				url = "http://" + request()->atributo("Host") + request()->recurso().directorio() + "games/" + game;

				root["roms"] = url + "/roms";
				root["driver"] = url + "/driver";
				root["display"] = url + "/display";
				root["chip"] = url + "/chip";
				root["device_ref"] = url + "/device_ref";
				root["info"] = url + "/info";
				root["infobasic"] = url + "/basicinfo";
			}
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
		return root;
	}

	void info_juego(const string& game, const opt_game opciones) {

		Json::Value info;

		info = info_juego_json(game);

		if (info.empty()) 
			throw GuruhttpExcepcion(404);
		else 
			enviar_json(info);
	}

	void info_detallada_juego(const string& game, const string& item) {

		try {
//			if (enviarDesdeCache()) return;

			Json::Value resultado;
			string consulta;

			if (item.compare("roms") == 0) {
				consulta = "select a.name, a.bios, a.size, a.crc, a.sha1, a.merge, a.region, a.offset, t.text as status, a.optional \
							from rom a, game b, game_rom c, text t \
							where c.id_game = b.id_game and c.id_rom = a.id_rom and a.status = t.id_text and b.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonArrayObject(mame, consulta, resultado);
			} else if (item.compare("driver") == 0) {
				consulta = "select status.text as status, emulation.text as emulation, color.text as color, sound.text as sound, graphic.text as graphic, cocktail.text as cocktail, protection.text as protection, savestate.text as savestate, palettesize.text as palettesize \
							from game g, driver d, text status, text emulation, text color, text sound, text graphic, text cocktail, text protection, text savestate, text palettesize \
							where g.id_game = d.id_game and status.id_text = d.status and emulation.id_text = d.emulation and color.id_text = d.color and sound.id_text = d.sound and graphic.id_text = d.graphic and cocktail.id_text = d.cocktail and protection.id_text = d.protection and savestate.id_text = d.savestate and palettesize.id_text = d.palettesize and g.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonObject(mame, consulta, resultado);
			} else if (item.compare("display") == 0) {
				consulta = "select d.tag, d.type, cast(d.rotate as text) as rotate, d.flipx, cast(d.width as text) as width, \
							cast(d.height as text) as height, d.refresh, d.pixclock, cast(d.htotal as text) as htotal, cast(d.hbend as text) as hbend, \
							cast(d.hbstart as text) as hbstart, cast(d.vtotal as text) as vtotal, cast(d.vbend as text) as vbend, \
							cast(d.vbstart as text) as vbstart \
							from game g, display d \
							where g.id_game = d.id_game \
							and g.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonObject(mame, consulta, resultado);
			} else if (item.compare("chip") == 0) {
				consulta = "select chip.type as Type, chip.tag as Tag, chip.name as Name, chip.clock as Clock from game, chip, game_chip \
							where game_chip.id_chip = chip.id_chip and game_chip.id_game = game.id_game \
							and game.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonArrayObject(mame, consulta, resultado);
			} else if (item.compare("device_ref") == 0) {
				consulta = "select text.text as device_ref from game, device_ref, text where game.id_game = device_ref.id_game and device_ref.name = text.id_text and game.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonArray1(mame, consulta, resultado);
			} else if (item.compare("info") == 0) {
				consulta = "select g.id_game, g.name, g.year, g.description, m.name as manufacturer, s.name as sourcefile, g.cloneof, g.romof, case(runnable) when 1 then 'Yes' when 0 then 'No' end as runnable, case(isbios) when 1 then 'Yes' when 0 then 'No' end as isbios, case(isdevice) when 1 then 'Yes' when 0 then 'No' end as isdevice, case(ismechanical) when 1 then 'Yes' when 0 then 'No' end as ismechanical \
						    from game g, sourcefile s, manufacturer m \
							where g.sourcefile = s.id_sourcefile and g.manufacturer = m.id_manufacturer and g.name = " + GuruStringAlgo::comilla_simple(game);
				SQLite2JsonObject(mame, consulta, resultado);
			} else if (item.compare("basicinfo") == 0) {
				consulta = "select a.description, b.name, a.year from game a, manufacturer b where a.manufacturer = b.id_manufacturer and a.name = " + GuruSQLite::comillas(game);
				SQLite2JsonObject(mame, consulta, resultado);
			} else
				download(game, item);

			enviar_json(resultado);

			escribirCache(resultado.toStyledString());
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
	}

	void version() {
		try {
			Json::Value resultado;

			SQLite2JsonObject(mame, "select build, debug, mameconfig from version", resultado);

			enviar_json(resultado);
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
	}

	void random(const string& extra="snap") {

		try {
			int total_veces = 0;
			string archivo;

			do {
				string consulta;

				consulta = "SELECT name FROM game where romof = '' and cloneof = '' and runnable = 1 and isbios = 0 and ismechanical = 0 and isdevice = 0 ORDER BY RANDOM() LIMIT 1";

				GuruSQLite::resultado res = mame.ejecutarEX(consulta);

				if (!res.empty()) {
					string game(res->getString(0));

					if (extra.compare("titles") == 0) archivo = request()->config()->env("titles") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("snap") == 0) archivo = request()->config()->env("snap") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("artwork") == 0) archivo = request()->config()->env("artwork") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("flyers") == 0) archivo = request()->config()->env("flyers") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("cabinets") == 0) archivo = request()->config()->env("cabinets") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("cpanel") == 0) archivo = request()->config()->env("cpanel") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("marquees") == 0) archivo = request()->config()->env("marquees") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("pcb") == 0) archivo = request()->config()->env("pcb") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("manuals") == 0) archivo = request()->config()->env("manuals") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("devices") == 0) archivo = request()->config()->env("devices") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("cabdevs") == 0) archivo = request()->config()->env("cabdevs") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("icons") == 0) archivo = request()->config()->env("icons") + DIVISOR_DIRECTORIO + game + ".ico";
					else if (extra.compare("logo") == 0) archivo = request()->config()->env("logo") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("versus") == 0) archivo = request()->config()->env("versus") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("gameover") == 0) archivo = request()->config()->env("gameover") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("ends") == 0) archivo = request()->config()->env("ends") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("artpreview") == 0) archivo = request()->config()->env("artpreview") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("bosses") == 0) archivo = request()->config()->env("bosses") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("howto") == 0) archivo = request()->config()->env("howto") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("warning") == 0) archivo = request()->config()->env("warning") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("select") == 0) archivo = request()->config()->env("select") + DIVISOR_DIRECTORIO + game + ".png";
					else if (extra.compare("videosnaps") == 0) archivo = request()->config()->env("videosnaps") + DIVISOR_DIRECTORIO + game + ".mp4";
					else throw GuruhttpExcepcion(404);

					if (GuruDirectorio::existe(archivo)) {

						GuruDirectorio::GuruArchivo a;

						GuruDirectorio::propiedades(archivo, a);

						// Para que no me mande el archivo que dice que no tiene captura el mame
						if (extra.compare("titles") == 0) {
							if ((a.tamanio() >= 53444 && a.tamanio() <= 53544) || a.tamanio() < 1332 || (a.tamanio() >= 55907 && a.tamanio() <= 55994) || (a.tamanio() >= 57254 && a.tamanio() <= 57293)) archivo.clear();
						} else if (extra.compare("snap") == 0) {
							if ((a.tamanio() >= 53431 && a.tamanio() <= 56501) || a.tamanio() < 1338 || (a.tamanio() >= 57795 && a.tamanio() <= 57855)) archivo.clear();
						}
					} else archivo.clear();
				}
			} while (archivo.empty() && ++total_veces < 80);

			if (archivo.empty()) throw GuruhttpExcepcion(404);

			response()->controlar_cache(false);
			enviar_archivo(archivo);
		} catch (GuruSQLite::GuruSQLiteException& e) {
			throw GuruhttpExcepcion(500, e.what());
		}
	}

};

#endif
