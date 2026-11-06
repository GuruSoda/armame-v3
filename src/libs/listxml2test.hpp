#ifndef __LISTXML2TEST_HPP__
#define __LISTXML2TEST_HPP__


#include <string>

#if defined __GURUWIN32__
#include <Windows.h>
#include <psapi.h>
#elif defined __GURULINUX__
#endif

#include <GuruCompat.h>

class XMLTest : public GuruMAME::GuruParserXML {
	uint32_t max_mem=0;
	uint32_t max_mem_nro;
	string   max_mem_game_name;

	uint32_t total = 0;
public:
	XMLTest() {}
	virtual ~XMLTest() {}

	void game(modelodatosmame::game& machine) {
		total++;

		//		if (nuevo.name.compare("rygar") == 0) {
		//			cout << nuevo.name << endl;
		//			finalizar();
		//		}
//		cout << "\r" << progreso();

		return;

		#if defined __GURUWIN32__
			PROCESS_MEMORY_COUNTERS_EX pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

			if ((pmc.PrivateUsage / 1024) > max_mem) {
				max_mem = static_cast<uint32_t>(pmc.PrivateUsage / 1024);
				max_mem_nro = total;
				max_mem_game_name = machine.name;
			}

			cout << "\r" << std::setfill(' ') << std::setw(6) << total << " - " << std::setfill(' ') << std::setw(6) << (pmc.PrivateUsage / 1024) << " KB. - " << std::setfill(' ') << std::setw(6) << max_mem << " KB. (" << max_mem_nro << ") - " << std::setfill(' ') << std::setw(20) << max_mem_game_name;

//			if ((pmc.PrivateUsage / 1024) > 23000)
//				int a = 1;
		#elif defined __GURULINUX__
		//	cout << "Memoria utilizada: " << (actualMemoriaFisica() / 1024) << " MB." << endl;
		#endif
	}

	void version(const GuruMAME::version& ver) {
		cout << "Version - " << ver.build << endl;
	};
};

#endif
