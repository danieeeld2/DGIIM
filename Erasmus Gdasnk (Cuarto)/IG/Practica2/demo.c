
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int red, green, blue, yellow;
unsigned long foreground, background;

//*************************************************************************************************************************
// Funkcja rysujaca wykres slupkowy dla funkcji Gaussa 

int demo_rectangles(Display* display, Window window, GC gc)
{
  int i, num_rectangles = 30;
  int width, height, range = 10;
  float x, y, std = 1;
  float bar_width;
  XWindowAttributes attributes;

  XGetWindowAttributes(display, window, &attributes);
  width = attributes.width;
  height = attributes.height;
  bar_width = width / num_rectangles - 2;
   
  for(i = 0; i < num_rectangles; i++)
  {
    XSetForeground(display, gc, rand());
    x = (float)i * range / num_rectangles; 
    y = height * exp(- (x - range/2) * (x - range/2) / (2 * std * std));
    XFillRectangle(display, window, gc, i * (bar_width + 2), height - y, bar_width, y); 
  }
}

//*************************************************************************************************************************
// Funkcja rysujaca wykres punktowy dla funkcji -sin 

int demo_ellipses(Display* display, Window window, GC gc)
{
  int i, width, height, num_circles = 30;
  float R1, R2;
  float x, y;
  XWindowAttributes attributes;

  XGetWindowAttributes(display, window, &attributes);
  width = attributes.width;
  height = attributes.height;
  R1 = (float) width / num_circles;
  R2 = (float) height / num_circles;

  for(i = 0; i < num_circles; i++)
  {
    XSetForeground(display, gc, rand());
    x = R1 * i;
    y = - sin(x * 2 * M_PI / width) * height / 2;
    XFillArc(display, window, gc, x, height / 2 - y - R2/2, R1, R2, 0, 360 * 64); 
  }  
}

//*************************************************************************************************************************
//funkcja przydzielania kolorow

int AllocNamedColor(char *name, Display* display, Colormap colormap)
  {
    XColor col;
    XParseColor(display, colormap, name, &col);
    XAllocColor(display, colormap, &col);
    return col.pixel;
  } 

//*************************************************************************************************************************
// inicjalizacja zmiennych globalnych okreslajacych kolory

int init_colors(Display* display, int screen_no, Colormap colormap)
{
  background = WhitePixel(display, screen_no);  //niech tlo bedzie biale
  foreground = BlackPixel(display, screen_no);  //niech ekran bedzie czarny
  red=AllocNamedColor("red", display, colormap);
  green=AllocNamedColor("green", display, colormap);
  blue=AllocNamedColor("blue", display, colormap);
  yellow=AllocNamedColor("yellow", display, colormap);
}

//*************************************************************************************************************************
// Glowna funkcja zawierajaca petle obslugujaca zdarzenia */

int main(int argc, char *argv[])
{
  char            icon_name[] = "Grafika";
  char            title[]     = "Grafika komputerowa";
  char            info1[]     = "LEWY przycisk  - PROSTOKATY";
  char            info2[]     = "PRAWY przycisk - ELIPSY";
  Display*        display;    //gdzie bedziemy wysylac dane (do jakiego X servera)
  Window          window;     //nasze okno, gdzie bedziemy dokonywac roznych operacji
  GC              gc;         //tu znajduja sie informacje o parametrach graficznych
  XEvent          event;      //gdzie bedziemy zapisywac pojawiajace sie zdarzenia
  KeySym          key;        //informacja o stanie klawiatury 
  Colormap        colormap;
  int             screen_no;
  XSizeHints      info;       //informacje typu rozmiar i polozenie ok
  
  char            buffer[8];  //gdzie bedziemy zapamietywac znaki z klawiatury
  int             hm_keys;    //licznik klawiszy
  int             rectangles = TRUE;
  int             to_end;

  display    = XOpenDisplay("");                //otworz polaczenie z X serverem pobierz dane od zmiennej srodowiskowej DISPLAY ("")
  screen_no  = DefaultScreen(display);          //pobierz domyslny ekran dla tego wyswietlacza (0)
  colormap = XDefaultColormap(display, screen_no);
  init_colors(display, screen_no, colormap);

  //okresl rozmiar i polozenie okna
  info.x = 100;
  info.y = 150;
  info.width = 500;
  info.height = 300;
  info.flags = PPosition | PSize;

  //majac wyswietlacz, stworz okno - domyslny uchwyt okna
  window = XCreateSimpleWindow(display, DefaultRootWindow(display),info.x, info.y, info.width, info.height, 7/* grubosc ramki */, foreground, background);
  XSetStandardProperties(display, window, title, icon_name, None, argv, argc, &info);
  //utworz kontekst graficzny do zarzadzania parametrami graficznymi (0,0) domyslne wartosci
  gc = XCreateGC(display, window, 0, 0);
  XSetBackground(display, gc, background);
  XSetForeground(display, gc, foreground);

  //okresl zdarzenia jakie nas interesuja, np. nacisniecie klawisza
  XSelectInput(display, window, (KeyPressMask | ExposureMask | ButtonPressMask| ButtonReleaseMask | Button1MotionMask));
  XMapRaised(display, window);  //wyswietl nasze okno na samym wierzchu wszystkich okien
      
  to_end = FALSE;

 /* petla najpierw sprawdza, czy warunek jest spelniony
     i jesli tak, to nastepuje przetwarzanie petli
     a jesli nie, to wyjscie z petli, bez jej przetwarzania */
  while (to_end == FALSE)
  {
    XNextEvent(display, &event);  // czekaj na zdarzenia okreslone wczesniej przez funkcje XSelectInput

    switch(event.type)
    {
      case Expose:
        if (event.xexpose.count == 0)
        {
          XSetForeground(display, gc, foreground);
          XClearWindow(display, window);
          XDrawString(display, window, gc, 10, 20, info1, strlen(info1));
          XDrawString(display, window, gc, 10, 40, info2, strlen(info2));
          if (rectangles == TRUE)
            demo_rectangles(display, window, gc);
          else
            demo_ellipses(display, window, gc);
        }
        break;

      case MappingNotify:
        XRefreshKeyboardMapping(&event.xmapping); // zmiana ukladu klawiatury - w celu zabezpieczenia sie przed taka zmiana trzeba to wykonac
        break;

      case ButtonPress:
        if (event.xbutton.button == Button1)  // sprawdzenie czy wciscnieto lewy przycisk				              
          rectangles = TRUE;

        else if (event.xbutton.button == Button3) // sprawdzenie czy wciscnieto prawy przycisk
          rectangles = FALSE;

        event.type = Expose;                 // wymuszenie odswiezenia okna
        event.xexpose.count = 0;
        XSendEvent(display, window, 0, ExposureMask, &event); 
        break;


      case KeyPress:
        hm_keys = XLookupString(&event.xkey, buffer, 8, &key, 0);
        if (hm_keys == 1)
        {
          if (buffer[0] == 'q') to_end = TRUE;        // koniec programu
          
        }

      default:
        break;
    }
  }

  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
