#include <string>
#include <vector>
#include "consola_util.h"
#include "progress_bar.h"
#include "SnakeGame.h"
#include "menu_consola.h"

using namespace std;
using namespace console;

int main()
{
	SnakeGame snakegame;
	string title_menu{ "MENU PRINCIPAL" }, title_submenu{"SELECCIONAR NIVEL"}, answer;
	vector<string> options_menu{ "Jugar", "Ver tabla de puntuaciones", "Ver instrucciones", "Salir" };
	vector<string> options_submenu{ "F\240cil", "Normal", "Dif\241cil", "Demente", "Volver al men\243 principal" };
	int option_menu, option_submenu;
	Menu menu{ title_menu, options_menu }, submenu{ title_submenu, options_submenu, false };
	
	edit_console("SNAKE GAME", 0, 10);
	disable_max_button();
	center_console_window();

	do
	{
		hide_cursor();
		menu.display();
		option_menu = menu.select_option("===>");

		/*
		if (option_menu == 1)
		{
			display_progress_bar(20, "CARGANDO EL JUEGO...", char(219));
		}
		*/
		clear_console_screen();

		switch (option_menu)
		{
			case 1:
				submenu.display();				
				option_submenu = submenu.select_option("===>");
				clear_console_screen();
				clear_console_input_buffer();
				
				if (option_submenu != submenu.get_size())
				{
					switch (option_submenu)
					{
						case SnakeGame::Level::EASY: snakegame.run(100); break;
						case SnakeGame::Level::NORMAL: snakegame.run(75); break;
						case SnakeGame::Level::HARD: snakegame.run(50); break;
						case SnakeGame::Level::INSANE: snakegame.run(25); break;
					}
					snakegame.reload();
					clear_console_screen();
				}
			break;

			case 2: break; //Falta implementar
			
			case 3:
				snakegame.showInstructions();
				clear_console_screen();
			break;

			case 4:
				set_cursor_visibility();
				answer = snakegame.askUser();
				clear_console_screen();

				if (answer == "S")
				{
					snakegame.close();
				}
			break;
		}		
	} while (option_menu != options_menu.size() || answer == "N");

	return 0;
}
