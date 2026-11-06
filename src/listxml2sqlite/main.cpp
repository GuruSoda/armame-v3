#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <cstdlib>

#include <GuruCompat.h>
#include <argtable/argtable2.h>

#include <modelomame.hpp>
#include <modelodatosmame.hpp>
#include <parserxml.hpp>

#include <listxml2sqlitebasico.hpp>
#include <listxml2sqlite.hpp>
#include <listxml2sqlitev2.hpp>
#include <listxml2test.hpp>
#include <listxml2memoria.hpp>
#include <listxml2count.hpp>
#include <listxml2comp.hpp>

#if defined __GURUWIN32__
#include <Windows.h>
#include <psapi.h>
#elif defined __GURULINUX__
#endif

using namespace std;

static const char* listxml2sqlite_version = "2.2.0";
static const char* listxml2sqlite_version_number = "202000";

// para saber la memoria ram de mi proceso.
// https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

#if defined __GURULINUX__
int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int actualMemoriaFisica(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}
#endif

char progreso() {
	static uint64_t	t = 0;
	char chars_progreso[] = { '|','/','-', '\\' };

	return chars_progreso[t++ % 4];
}

class listxml2SQLiteBasico_Console : public listxml2SQLiteBasico {
public:
	listxml2SQLiteBasico_Console() {};
	virtual ~listxml2SQLiteBasico_Console() {};

	virtual void game(modelodatosmame::game& machine) {
		listxml2SQLiteBasico::game(machine);

		cout << "\r" << progreso();
	}
};

class listxml2SQLiteV2_Console : public listxml2SQLiteV2 {
public:
	listxml2SQLiteV2_Console() {};
	virtual ~listxml2SQLiteV2_Console() {};

	virtual void game(modelodatosmame::game& machine) {
		listxml2SQLiteV2::game(machine);

		cout << "\r" << progreso();
	}
};

int main(int argc, char* argv[])
{
	if (0) {
		try {
			const char* ejemplo = "drop table if exists data; create table data ( id integer primary key autoincrement, text1 text not null, int1 integer not null);";
			GuruSQLite::bd testbdd = GuruSQLite::conectar("test.db", ejemplo, GuruSQLite::bd::modo::lecturaEscritura | GuruSQLite::bd::modo::crear);
			int registros = 500000;

			if (testbdd.conectado()) {
				string consulta;

				testbdd.exec("BEGIN TRANSACTION");

				GuruSQLite::sentencia stmt(testbdd.sentencia("insert into data(text1, int1) values(?,?)"));

				for (int32_t i = 1, tmp = -1; i <= registros; i++) {
					stmt.bind(1, i);
					stmt.bind(2, GuruStringAlgo::itos(i));

					testbdd.exec(stmt);

					// para que solo muestre el avance del porcentaje solo cuando cambie el porcentaje.
					if ((i * 100 / registros) != tmp) {
						tmp = i * 100 / registros;
						cout << tmp << "% - " << i << "/" << registros << "\r";
					}
				}

				testbdd.exec("END TRANSACTION");

				testbdd.exec("delete from data;");

				testbdd.exec("BEGIN TRANSACTION");

				for (int i = 1, tmp=0; i <= registros; i++) {
					consulta = "insert into data (text1, int1) values (" + GuruSQLite::comillas(GuruStringAlgo::itos(i)) + ", " + GuruStringAlgo::itos(i) + ")";

					testbdd.exec(consulta);

					// para que solo muestro el avance del porcentaje solo cuando cambie el porcentaje.
					if ((i * 100 / registros) != tmp) {
						tmp = i * 100 / registros;
						cout << tmp << "% - " << i << "/" << registros << "\r";
					}
				}

				testbdd.exec("END TRANSACTION");
			}

			testbdd.desconectar();
		} catch (GuruSQLite::GuruSQLiteException &e) {
			cout << e.what() << endl;
		}

		return 0;
	}

	if (0) {
		//	GuruSQLite::bd pruebabdd = GuruSQLite::conectar("d:\\Desarrollo\\ArMame3\\src\\build\\vs2015\\listxml2sqlite\\Release\\x64\\mame.sqlite");
		GuruSQLite::bd pruebabdd = GuruSQLite::conectar("c:\\Desarrollo\\ArMame3\\src\\build\\vs2015\\listxml2sqlite\\Release\\x64\\mame.sqlite");

		if (pruebabdd.conectado()) {
			cout << "bien!" << endl;

			GuruSQLite::sentencia	stmt(pruebabdd.sentencia("select description from game where id_game = ?"));
			GuruSQLite::resultado	res;

			for (int i = 1; i <= 20; i++) {

				stmt.bind(1, i);
				res = pruebabdd.ejecutarEX(stmt);

				do {
					cout << "Nombre:" << res->getString(0) << endl;
				} while (res.fetch());

				//			stmt.finalizar();
			}
		}
	}

// ---------------------------------------------------------------------------------------
	struct arg_lit*  ayuda		= arg_lit0("h","help", "Muestra la ayuda.");
	struct arg_file* bdd		= arg_file0("o","bdd","<sqlite>", "salida  (default mame.sqlite)");
	struct arg_file* xml		= arg_file0("i","xml","<xml>", "entrada");
	struct arg_lit*  dumpxml	= arg_lit0(NULL, "dumpxml", "Muestra nombre y descripcion procesado desde el xml.");
	struct arg_lit*  mem		= arg_lit0("m", "mem", "Carga todo a memoria.");
	struct arg_lit*  count		= arg_lit0("c", "count", "Cuenta la cantidad de maquinas.");
	struct arg_lit*  test		= arg_lit0("t", "test", "Realiza un pasada completa por el .xml.");
	struct arg_lit*  v1			= arg_lit0("1", "v1", "Version 1 de la generacion de la base.");
	struct arg_lit*  v2			= arg_lit0("2", "v2", "Version 2 de la generacion de la base.");
	struct arg_lit*  basic		= arg_lit0("b", "basic", "BD con informacion basica ( Ejem: Para Menues ).");
	struct arg_end*  end		= arg_end(8);

	void* argtable[] = {ayuda, bdd, xml, dumpxml, mem, count, v1, v2, basic, test,end};

	if (arg_nullcheck(argtable) != 0) {
        cout << "insufficient memory" << endl;
        return 2;
	}

	bdd->filename[0]="mame.sqlite3";
	xml->filename[0]="-";

	int nerrors = arg_parse(argc,argv,argtable);

	if (ayuda->count > 0 || argc == 1) {
//		arg_print_syntax(stdout,argtable,"\n");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");

		return 1;
	}

    if (nerrors > 0) {
        arg_print_errors(stdout,end,"");
        cout << "Pruebe --help por mas informacion" << endl;
		return 3;
        }

	string salida;
	if (bdd->count > 0) salida = bdd->filename[0];

	string entrada;
	if (xml->count > 0) entrada = xml->filename[0];

	bool memoria = false;
	if (mem->count > 0) memoria = true;

	bool testeo = false;
	if (test->count > 0) testeo = true;

	bool version2 = false;
	if (v2->count > 0) version2 = true;

	bool version1 = false;
	if (v1->count > 0) version1 = true;

	bool basico = false;
	if (basic->count > 0) basico = true;

	bool contar = false;
	if (count->count > 0) contar = true;

	if (dumpxml->count > 0) {
		XMLaMemoria p;

		p.xml(entrada);

		p.iniciar();

		cout << "Segundos en procesar: " << p.tiempo_sec() << endl;

		return 0;
	}

    arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
// ---------------------------------------------------------------------------------------

	if (memoria) {
		XMLaMemoria p;

		p.xml(entrada);

		p.iniciar();

		cout << "Tiempo transcurrido en sec.: " << p.tiempo_sec() << endl;
	} else if (contar) {
		listxml2count p;

		p.xml(entrada);

		p.iniciar();

		cout << p.machines() << endl;
	} else if (version2) {
		listxml2SQLiteV2_Console p;

		p.xml(entrada);

		p.iniciar();

		cout << "\rTiempo de procesamiento en sec.: " << p.tiempo_sec() << endl;

	#if defined __GURUWIN32__
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		cout << "Memoria utilizada: " << (pmc.PrivateUsage/1024)/1024 << " MB." << endl;
	#elif defined __GURULINUX__
		cout << "Memoria utilizada: " << (actualMemoriaFisica()/1024) << " MB." << endl;
	#endif
		p.importar_a_base_v2();
	} else if (testeo) {
		XMLTest p;

		p.xml(entrada);

		p.iniciar();

		cout << endl << "Tiempo de procesamiento en sec.: " << p.tiempo_sec() << endl;
	} else if (version1) {
		XMLaSQLite xml2sql;

		if (!salida.empty()) xml2sql.sqlite(salida);
		else xml2sql.sqlite("mame.sqlite3");

		xml2sql.xml(entrada);

		xml2sql.iniciar();

		cout << "Tiempo transcurrido en sec.: " << xml2sql.tiempo_sec() << endl;
	} else if (basico) {
		listxml2SQLiteBasico_Console xml2sql;

//		if (!salida.empty()) xml2sql.sqlite(salida);
///		else xml2sql.sqlite("mame.sqlite3");

		xml2sql.xml(entrada);

		xml2sql.iniciar();

		cout << "\rTiempo transcurrido en sec.: " << xml2sql.tiempo_sec() << endl;
	} else {
		cout << "Que desea hacer?" << endl;
	}

	return 0;
}
