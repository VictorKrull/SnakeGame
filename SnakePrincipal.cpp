#include <string>
#include <vector>
#include "consola_util.h"
#include "progress_bar.h"
#include "Point.h"
#include "SnakeGame.h"
#include "menu_consola.h"

using namespace std;
using namespace console;

int main()
{
	SnakeGame snakegame;
	string title_menu{ "MENU" }, answer;
	vector<string> options_menu { "Jugar", "Ver instrucciones", "Salir" };
	int option;
	char key;
	Menu menu{ title_menu, options_menu };
	
	edit_console("JUEGO SNAKE", 0, 10);
	disable_max_button();
	center_console_window();

	do
	{
		hide_cursor();
		menu.display();
		option = menu.select_option();

		if (option == 1)
		{
			display_progress_bar(20, "CARGANDO EL JUEGO...", char(219));
		}
		clear_console_screen();

		switch (option)
		{
			case 1:
				snakegame.run();				
				write_at_position("\255PERDISTE!", 20, 20);						
				write_at_position("Presiona la barra espaciadora para volver al men\243.", 20, 21);
				do
				{
					key = console::get_key();
				} while (key != 32); //SPACE BAR KEY
				clear_console_screen();
			break;

			case 2:
				snakegame.showInstructions();
				clear_console_screen();
			break;
			
			case 3:
				set_cursor_visibility();
				answer = snakegame.ask();
				clear_console_screen();

				if (answer == "S")
				{
					snakegame.close();
				}
			break;
		}
	} while (option != options_menu.size() || answer == "N");

	return 0;
}
