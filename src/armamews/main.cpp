#include <iostream>
#include <argtable/argtable2.h>

#include <GuruHttp/Guruhttp.hpp>
#include <GuruHttp/GuruhttpServidor.hpp>
#include <GuruHttp/GuruhttpInterface.hpp>
#include <GuruHttp/GuruhttpSitioStats.hpp>
#include <GuruHttp/GuruhttpSQLite.hpp>
#include <GuruSocket/GuruServidorTCP.hpp>
#include <GuruDirectorio.hpp>

//#include <jsoncpp/json.h>
//#include <GuruSQLite_algo.hpp>

#include <armamews.hpp>

#ifdef __GURUWIN32__
#include <Winsvc.h>
#elif defined __GURULINUX__
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#endif

#ifdef __GURUWIN32__
BOOL	Control_Consola(DWORD requerimiento);
HANDLE	Corriendo;
#elif defined __GURULINUX__
void 	Control_Consola(int);
sem_t	Corriendo;
#endif

void mostrar_conf_default() {
	Json::Value root;

	root["Puerto"] = "28275";
	root["Interfaz"] = "0.0.0.0";
	root["bd"] = "mamrarcade.bd";
	root["VirtualDir"] = "/armamews/";

	Json::StyledWriter writer;

	std::cout << writer.write(root);
}

int main(int argc, char* argv[])
{
	if (0) {
		Json::Value root;
		GuruSQLite::bd base = GuruSQLite::conectar("c:\\Desarrollo\\ArMame3\\bin\\mame.sqlite");

//		string consulta = "select g.id_game, g.name, g.year, g.description, m.name as manufacturer, s.name as sourcefile, g.cloneof, g.romof, case(runnable)when 1 then 'Yes' when 0 then 'No' end as runnable, case(isbios)when 1 then 'Yes' when 0 then 'No' end as isbios, case(isdevice)when 1 then 'Yes' when 0 then 'No' end as isdevice, case(ismechanical)when 1 then 'Yes' when 0 then 'No' end as ismechanical \
//						from game g, sourcefile s, manufacturer m \
//						where g.sourcefile = s.id_sourcefile and g.manufacturer = m.id_manufacturer and g.name = 'rygar'";

//		cout << SQLite2JsonArrayObject(base, consulta, root).toStyledString();


		//	cout << SQLite2JsonArray1(base, "select name from game where name GLOB 'gng*'", "Ghosts", root).toStyledString();

		//	cout << SQLite2JsonArrayObject(base, "select a.name, a.size, a.crc, a.sha1 from rom a, game b, game_rom c where c.id_game = b.id_game and c.id_rom = a.id_rom and b.name = 'rygar'", root).toStyledString();

		//	cout << SQLite2JsonArrayObject(base, "select a.* from rom a, game b, game_rom c where c.id_game = b.id_game and c.id_rom = a.id_rom and b.name = 'rygar'", root).toStyledString();

			string consulta = "select status.text as Status, emulation.text as Emulation, color.text as Color, sound.text as Sound, graphic.text as Graphic, cocktail.text as Cocktail, protection.text as Protection, savestate.text as SaveState \
				from game g, driver d, text status, text emulation, text color, text sound, text graphic, text cocktail, text protection, text savestate \
			where g.id_game = d.id_game and \
				status.id_text = d.status and \
				emulation.id_text = d.emulation and \
				color.id_text = d.color and \
				sound.id_text = d.sound and \
				graphic.id_text = d.graphic and \
				cocktail.id_text = d.cocktail and \
				protection.id_text = d.protection and \
				savestate.id_text = d.savestate and g.name = 'gng'";

			for (uint32_t i = 0; i < 100000; i++) {
				GuruSQLite::resultado res;
				
				res = base.ejecutarEX(consulta);

				cout << "\r" << res->getString(0, "nop") << setw(8) << setfill(' ') << i;
			}

//			cout << base.ejecutarEX(consulta)->getString(0) << endl;

			// cout << SQLite2JsonObject(base, consulta, root).toStyledString();

//			cout << r.toStyledString() << endl;
		
		//	cout << SQLite2JsonArray1(base, "select name from game where name GLOB 'gng*'", "Ghosts", root).toStyledString();

		//	cout << SQLite2JsonArray2(base, "select name,description from game where isbios = 0 and ismechanical = 0 and isdevice = 0 and name GLOB 'rygar*' order by 2 ", "Rygar", root).toStyledString();
	}
/*
	{
		Json::Value root;
		GuruSQLite::bd base = GuruSQLite::conectar("c:\\Desarrollo\\ArMame3\\src\\build\\vs2015\\listxml2sqlite\\Release\\x64\\mame.sqlite ");
		GuruSQLite::resultado res = base.ejecutar("select a.name from game a where a.name = 'rtype'");

		//	if (!res.empty())
		//		GuruSQLiteAlgo::result_a_json(res, root);



		std::cout << root.toStyledString() << endl;
	}
*/
	struct arg_lit* opt_help = arg_lit0("h", "help", "Muestra la ayuda.");
	struct arg_lit* opt_verbose = arg_lit0("v", "verbose", "Muestra informacion por pantalla.");
	struct arg_str* opt_interfaz = arg_str0("i", "interfaz", "<IP>", "Interfaz a escuchar (default:0.0.0.0)");
	struct arg_int* opt_puerto = arg_int0("p", "puerto", "<n>", "Puerto que escucha el servidor (default:80)");
	struct arg_int* opt_velocidad = arg_int0("v", "velocidad", "<n>", "Ancho de banda a utilizar en Kbytes (default:0)");
	struct arg_str* opt_dirvirtual = arg_str0("d", "virtualdir", "<dir virtual>", "Directorio virtual para ingresar (default:/)");
	struct arg_lit* opt_create_config = arg_lit0("r", "create-config", "Crea una configuracion por default.");
	struct arg_str* opt_config = arg_str0("c", "config", "<archivo>", "Archivo de configuracion.");
	struct arg_str* opt_host = arg_str0(NULL, "host", "<nombre>", "Nombre del host (default: none)");
	struct arg_file* opt_base = arg_file0("b", "bd", "<base.bd>", "Base de Datos Mame.");

	struct arg_end* end = arg_end(20);

	void* argtable[] = { opt_help, opt_verbose, opt_interfaz, opt_puerto, opt_velocidad, opt_dirvirtual, opt_create_config, opt_config, opt_host, opt_base, end };
	int nerrors;

	opt_interfaz->sval[0] = "0.0.0.0";
	opt_puerto->ival[0] = 80;
	opt_velocidad->ival[0] = 0;

	nerrors = arg_parse(argc, argv, argtable);

	if (nerrors > 0) {
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		return 1;
	}

	if (opt_help->count > 0) {
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		return 0;
	}

	if (opt_create_config->count > 0) {
		mostrar_conf_default();
		return 2;
	}

	if (opt_base->count > 0) {
		mame = GuruSQLite::conectar(*opt_base->filename);

		if (!mame.conectado()) {
			std::cout << "Error abriendo base de datos M.A.M.E." << endl;
			return 3;
		}
	}

	GuruhttpDirVirtual	armamews;
	armamews.sitio("/armamews/");
	armamews.agregarHost("*");
	armamews.interfaz(new GuruhttpSitio<ArMameWs>());
	armamews.velocidad(opt_velocidad->ival[0] * 1024);
	armamews.extra_ptr();
	armamews.agregarAtributosExtra("Access-Control-Allow-Origin", "*");
//	armamews.env("rom", "c:\\Cosas\\Roms");

	GuruhttpDirVirtual	HttpSQLite;

	HttpSQLite.sitio("/sqlite/");
	HttpSQLite.agregarHost("*");
	HttpSQLite.interfaz(new GuruhttpSitio<GuruHttpSQLite>());
	HttpSQLite.velocidad(0);
	HttpSQLite.extra_ptr((void*)*opt_base->filename);
	HttpSQLite.agregarAtributosExtra("Access-Control-Allow-Origin", "*");
	HttpSQLite.env("base", "Base de datos del M.A.M.E.");

	GuruhttpDirVirtual	estadistica;
	estadistica.sitio("/stats/");
	estadistica.agregarHost("*");
	estadistica.interfaz(new GuruhttpSitio<stats>());

	if (opt_dirvirtual->count > 0) armamews.sitio(opt_dirvirtual->sval[0]);

	if (opt_verbose->count > 0) {
		armamews.agregarLog("+", "%fecha822% | %status% | %ip_request% | %request% | %request.User-Agent%");
		HttpSQLite.agregarLog("+", "%fecha822% | %status% | %ip_request% | %request% | %request.User-Agent%");
	}

	if (opt_host->count > 0) {
		GuruToken tk(" ,;|");
		vector<string> tokens;

		if (!tk.extraer(opt_host->sval[0], tokens).empty())
			armamews.agregarHost(tokens);
	}

	GuruDirectorio::GuruSplitPath ruta(argv[0]);
	GuruDirectorio::cambiarDirectorio(ruta.drive() + ruta.dir());

#ifdef __GURUWIN32__
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)Control_Consola, true);
	Corriendo = CreateSemaphore(NULL, 0, 2, NULL);
#elif defined __GURULINUX__
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, Control_Consola);
	signal(SIGQUIT, Control_Consola);
	signal(SIGINT, Control_Consola);

	sem_init(&Corriendo, 0, 0);
#endif

	try {
		inicializar_GuruSocket();

		GuruServidorTCP<Guruhttp> w(opt_puerto->ival[0], opt_interfaz->sval[0]);

		estadistica.extra_ptr(static_cast<void*>(&w));

		GuruSingleton<GuruhttpConfig>::instancia()->nuevo_sitio(armamews);
		GuruSingleton<GuruhttpConfig>::instancia()->nuevo_sitio(estadistica);
		GuruSingleton<GuruhttpConfig>::instancia()->nuevo_sitio(HttpSQLite);

		w.iniciar();

		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

#ifdef __GURUWIN32__
		WaitForSingleObject(Corriendo, INFINITE);
#elif defined __GURULINUX__
		sem_wait(&Corriendo);
#endif

		w.detener();

		GuruSingleton<GuruhttpLog>::instancia()->terminar();

#ifdef __GURUWIN32__
		CloseHandle(Corriendo);
#elif defined __GURULINUX__
		sem_destroy(&Corriendo);
#endif
	}
	catch (GuruSocketException& e) {
		cout << "ERROR:" << e.what() << endl;
	}
	catch (...) {
		cout << "Hubo una excepcion no atrapada!!!" << endl;
	}

	limpiar_GuruSocket();

	cout << "Finalizando ..." << endl;
	return 0;
}

#ifdef __GURUWIN32__
BOOL Control_Consola(DWORD requerimiento)
#elif defined __GURULINUX__
void Control_Consola(int requerimiento)
#endif
{
#ifdef __GURUWIN32__
	switch (requerimiento) {
	case CTRL_C_EVENT: cout << "Cancelado por CTRL-C ..." << endl;
	case CTRL_CLOSE_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		break;
	}

	ReleaseSemaphore(Corriendo, 1, NULL);
	return TRUE;
#elif defined __GURULINUX__
	sem_post(&Corriendo);
#endif
}

