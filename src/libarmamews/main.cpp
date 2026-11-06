#include <GuruHttp/GuruhttpInterface.hpp>
#include <GuruSQLite.hpp>
#include <GuruHttp/GuruhttpSQLite.hpp>
#include <armamews.hpp>

#include <string>
#include <map>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined __WIN32__) || (defined WIN32)
#define LIBRARY_EXPORT __declspec(dllexport)
#else
#define LIBRARY_EXPORT
#endif

LIBRARY_EXPORT 
GuruhttpInterface* armamews (const std::map<std::string, std::string>& env) {

	std::string base;

	try {
		std::map<std::string, std::string>::const_iterator it = env.find(string("base"));

		if (it != env.end()) base = it->second;

		if (!base.empty()) mame = GuruSQLite::conectar(base);

	} catch (GuruSQLite::GuruSQLiteException&) {}

	if (!mame.conectado()) return NULL;

	GuruhttpDirVirtual	HttpSQLite;

	HttpSQLite.sitio("/sqlite/");
	HttpSQLite.agregarHost("*");
	HttpSQLite.interfaz(new GuruhttpSitio<GuruHttpSQLite>());
	HttpSQLite.velocidad(0);
	HttpSQLite.extra_ptr((void*)base.c_str()); // nombre del archivo de base de datos.
	HttpSQLite.agregarAtributosExtra("Access-Control-Allow-Origin", "*");
	HttpSQLite.env("base", "Base de datos del M.A.M.E.");

	GuruSingleton<GuruhttpConfig>::instancia()->nuevo_sitio(HttpSQLite);

	return new GuruhttpSitio<ArMameWs>();
};

#ifdef __cplusplus
}
#endif
