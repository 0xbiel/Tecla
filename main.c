/*

  Tecla
  =====
  
  (c) 2020 - Gabriel Polastrini

  Tecla is a tool to show key codes.

  Tecla is licenced under GPL-3.0

*/

#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

char *inkey(int ch); //key interpreter

int main(void) {
  WINDOW *mainwindow;
  int ch;

  //init ncurses
  if((mainwindow = initscr()) == NULL) {
    fprintf(stderr, "Error Initializing ncurses.\n");
    exit(EXIT_FAILURE);
  }

  noecho(); //Don't print key inputs on terminal.
  keypad(mainwindow, TRUE); //Enable non-chars.

  //Print a prompt and refresh the screen
  mvaddstr(3, 10, "<Tecla>");
  mvaddstr(5, 10, "© Gabriel Polastrini");

  mvaddstr(8, 10, "Press a key ('q' to quit)...");
  mvprintw(10, 10, "You pressed: ");
  refresh();

  //Loop until user quit (q).

  while ( (ch = getch()) != 'q' ) {
    deleteln();
	  mvprintw(10, 10, "You pressed: 0x%x (%s)", ch, inkey(ch));
	  refresh();
  }

  delwin(mainwindow);
  endwin();
  refresh();

  return EXIT_SUCCESS;
};

struct keys {
  int  code;
  char name[20];
};

char *inkey(int ch) {
  static struct keys keys[] = 
    {
      { KEY_UP,        "Up arrow"        },
			{ KEY_DOWN,      "Down arrow"      },
			{ KEY_LEFT,      "Left arrow"      },
			{ KEY_RIGHT,     "Right arrow"     },
			{ KEY_HOME,      "Home"            },
			{ KEY_END,       "End"             },
			{ KEY_BACKSPACE, "Backspace"       },
			{ KEY_IC,        "Insert"          },
			{ KEY_DC,        "Delete"          },
			{ KEY_NPAGE,     "Page down"       },
			{ KEY_PPAGE,     "Page up"         },
			{ KEY_F(1),      "Function key 1"  },
			{ KEY_F(2),      "Function key 2"  },
			{ KEY_F(3),      "Function key 3"  },
			{ KEY_F(4),      "Function key 4"  },
			{ KEY_F(5),      "Function key 5"  },
			{ KEY_F(6),      "Function key 6"  },
			{ KEY_F(7),      "Function key 7"  },
			{ KEY_F(8),      "Function key 8"  },
			{ KEY_F(9),      "Function key 9"  },
			{ KEY_F(10),     "Function key 10" },
			{ KEY_F(11),     "Function key 11" },
			{ KEY_F(12),     "Function key 12" },
			{ -1,            "<unsupported>"   }
    };

    static char keych[2] = {0};
    
    if ( isprint(ch) && !(ch & KEY_CODE_YES)) {
	    keych[0] = ch;
	    return keych;
    }
    else {
	    int n = 0;

	    do {
	      if ( keys[n].code == ch )
		      return keys[n].name;
	        n++;
	    } 

      while ( keys[n].code != -1 );

	    return keys[n].name;
    }    
    
    return NULL;
}  
