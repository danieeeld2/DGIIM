
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

XArc arc1, arc2, arc3, arc4, arc5;
XRectangle rec, rec2;
XPoint PointD[3], PointD2[3], PointD3[3];
XPoint PointA[3], PointA2[2], PointA3[4];
int color;
int letters;

//*************************************************************************************************************************

void ReEvaluate()
{
  arc2.x = arc1.x;
  arc2.y = arc1.y;
  arc2.width = arc1.width;
  arc2.height = arc1.height;
  arc2.angle1 = arc1.angle1;
  arc2.angle2 = 90 * 64;

  // Rec 1
  rec.x = arc1.x;
  rec.y = arc1.y;
  rec.width = arc1.width;
  int aux = arc1.height/2;
  if (aux%10!=0)
    aux = aux+1;
  rec.height = arc1.y+aux-rec.y;

  // Rec 2
  aux = arc1.width/4;
  if(aux%10!=0)
    aux = aux+1;
  rec2.x = arc1.x + aux;
  aux = (2*rec.height)/5;
  if(aux%10!=0)
    aux = aux+1;
  rec2.y = arc1.y-aux;
  rec2.height = aux;
  aux = arc1.width/2;
  if(aux%10!=0)
    aux = aux+1;
  rec2.width = aux;

  // Arc 3
  aux = rec2.height/4;
  if(aux%10!=0)
    aux = aux+1;
  arc3.y = rec2.y-2*aux;
  arc3.width = arc3.height = 2*aux;
  aux = rec2.width/2;
  if(aux%10!=0)
    aux = aux+1;
  arc3.x = rec2.x+aux;
  aux = arc3.width/2;
  if(aux%10!=0)
    aux = aux+1;
  arc3.x = arc3.x-aux;
  arc3.angle1 = 0 * 64;
  arc3.angle2 = 360 * 64;

  // Arc 4
  arc4 = arc3;
  arc4.x = rec2.x;

  // Arc 5
  arc5 = arc3;
  arc5.x = rec2.x+rec2.width-arc5.height;
}

//*************************************************************************************************************************
// Initial Draw

int shield(Display* display, Window window, GC gc)
{
  int width, height;
  XWindowAttributes attributes;

  XGetWindowAttributes(display, window, &attributes);
  width = attributes.width;
  height = attributes.height;

  // Shield
  // Arc 1
  arc1.x = 125;
  arc1.y = 100;
  arc1.width = 250;
  arc1.height = 175;
  arc1.angle1 = 270 * 64;
  arc1.angle2 = -90 * 64;

  ReEvaluate();
  XArc Arcs[5]={arc1,arc2,arc3,arc4,arc5};

  XFillArcs(display,window,gc,Arcs,5);
  XFillRectangle(display,window,gc,rec.x,rec.y,rec.width,rec.height);
  XFillRectangle(display,window,gc,rec2.x,rec2.y,rec2.width,rec2.height);
}

//*************************************************************************************************************************
// Draw letters (DA)

void DrawLetters(Display* display, Window window, GC gc)
{
  int aux = 20;

  // Draw D
  PointD[0].x = arc1.x+20; PointD[0].y = arc1.y+20;
  PointD[1].x = PointD[0].x+aux; PointD[1].y = PointD[0].y;
  PointD[2].x = PointD[0].x+((PointD[1].x-PointD[0].x)/2); PointD[2].y = PointD[0].y+70;
  PointD2[0] = PointD[0];
  PointD2[1] = PointD[1];
  PointD2[2].x = PointD[0].x+((PointD[1].x-PointD[0].x)*3); PointD2[2].y = PointD[0].y+((PointD[2].y-PointD[0].y)/2);
  PointD3[0] = PointD2[2];
  PointD3[1].x = PointD3[0].x-3; PointD3[1].y = PointD3[0].y-3;
  PointD3[2] = PointD[2];
  XSetForeground(display,gc,WhitePixel(display, DefaultScreen(display)));
  XFillPolygon(display,window,gc,PointD,3,Convex,CoordModeOrigin);
  XFillPolygon(display,window,gc,PointD2,3,Convex,CoordModeOrigin);
  XFillPolygon(display,window,gc,PointD3,3,Convex,CoordModeOrigin);

  // Draw A
  PointA[0].x = PointD2[2].x+15; PointA[0].y = PointD[2].y;
  PointA[1].x = PointA[0].x+aux; PointA[1].y = PointD[0].y;
  PointA[2].x = PointA[1].x+aux; PointA[2].y = PointA[1].y;
  PointA2[0] = PointA[1];
  PointA2[1] = PointA[2];
  PointA2[2].x = PointA[2].x+(PointA[1].x-PointA[0].x); PointA2[2].y = PointA[0].y;
  PointA3[0].x = PointA[0].x+((PointA[1].x-PointA[0].x)/2); PointA3[0].y = PointA[1].y+((PointA[0].y-PointA[1].y)/2);
  PointA3[1].x = PointA[2].x+((PointA2[2].x-PointA[2].x)/2); PointA3[1].y = PointA3[0].y;
  PointA3[2].x = PointA3[0].x; PointA3[2].y = PointA3[0].y+5;
  PointA3[3].x = PointA3[1].x; PointA3[3].y = PointA3[1].y +5;
  XFillPolygon(display,window,gc,PointA,3,Convex,CoordModeOrigin);
  XFillPolygon(display,window,gc,PointA2,3,Convex,CoordModeOrigin);
  XFillPolygon(display,window,gc,PointA3,4,Convex,CoordModeOrigin);

  XSetForeground(display,gc,color);

}

//*************************************************************************************************************************

int Resize(Display* display, Window window, GC gc, int type)
{
  if(type == 0){
    arc1.width+=10;
    arc1.height+=10;
  }else{
    arc1.width-=10;
    arc1.height-=10;
  }  
  ReEvaluate();
  XArc Arcs[5]={arc1,arc2,arc3,arc4,arc5};
  XClearWindow(display,window);
  XFillArcs(display,window,gc,Arcs,5);
  XFillRectangle(display,window,gc,rec.x,rec.y,rec.width,rec.height);
  XFillRectangle(display,window,gc,rec2.x,rec2.y,rec2.width,rec2.height);
  if(letters == TRUE)
    DrawLetters(display,window,gc);
}

//*************************************************************************************************************************

int Move(Display* display, Window window, GC gc, char type)
{
  if(type == 'a') // Move left
    arc1.x-=10;
  if(type == 'd') // Move right
    arc1.x+=10;
  if(type == 'w') // Move up
    arc1.y-=10;
  if(type == 's') // Move down
    arc1.y+=10;

  ReEvaluate();
  XArc Arcs[5]={arc1,arc2,arc3,arc4,arc5};
  XClearWindow(display,window);
  XFillArcs(display,window,gc,Arcs,5);
  XFillRectangle(display,window,gc,rec.x,rec.y,rec.width,rec.height);
  XFillRectangle(display,window,gc,rec2.x,rec2.y,rec2.width,rec2.height);
  if(letters == TRUE)
    DrawLetters(display,window,gc);
}

//*************************************************************************************************************************
// Resize Letters

int Resize_Letter(Display* display, Window window, GC gc, int type){
  
}

//*************************************************************************************************************************
// Color Asing Function

int AllocNamedColor(char *name, Display* display, Colormap colormap)
  {
    XColor col;
    XParseColor(display, colormap, name, &col);
    XAllocColor(display, colormap, &col);
    return col.pixel;
  } 

//*************************************************************************************************************************
// Global Variables Initialization

int init_colors(Display* display, int screen_no, Colormap colormap)
{
  background = WhitePixel(display, screen_no);  // white backgroung
  foreground = BlackPixel(display, screen_no);  // black backgroung
  red=AllocNamedColor("red", display, colormap);
  green=AllocNamedColor("green", display, colormap);
  blue=AllocNamedColor("blue", display, colormap);
  yellow=AllocNamedColor("yellow", display, colormap);
}

//*************************************************************************************************************************

int main(int argc, char *argv[])
{
  char            icon_name[] = "Grafika";
  char            title[]     = "Grafika komputerowa";
  Display*        display;    // Server where data is sent
  Window          window;     // Window where operations are done
  GC              gc;         // Graphic Parameters Information
  XEvent          event;      // Events appended
  KeySym          key;        // KeyBoard Status
  Colormap        colormap;
  int             screen_no;
  XSizeHints      info;       // Size info
  
  char            buffer[8];  // Key Recorded from KeyBoard
  int             hm_keys;    // Key counter
  int             to_end;

  display    = XOpenDisplay("");                // Open conection with server X and get data 
  screen_no  = DefaultScreen(display);          // Predeterminate Screen
  colormap = XDefaultColormap(display, screen_no);
  init_colors(display, screen_no, colormap);

  // Size and Position of the Screen
  info.x = 100;
  info.y = 150;
  info.width = 500;
  info.height = 300;
  info.flags = PPosition | PSize;

  // Create a Window from a Screen
  window = XCreateSimpleWindow(display, DefaultRootWindow(display),info.x, info.y, info.width, info.height, 7/* screen board */, foreground, background);
  XSetStandardProperties(display, window, title, icon_name, None, argv, argc, &info);
  // Graphic Context for administrate Graphic Parameters
  gc = XCreateGC(display, window, 0, 0);
  XSetBackground(display, gc, background);
  XSetForeground(display, gc, foreground);

  // Register events
  XSelectInput(display, window, (KeyPressMask | ExposureMask | ButtonPressMask| ButtonReleaseMask | Button1MotionMask));
  XMapRaised(display, window);  // Display our window in front of another windows
      
  to_end = FALSE;
  letters = FALSE;

  while (to_end == FALSE)
  {
    XNextEvent(display, &event);  // Wait for the events desripted before in XSelectInput

    switch(event.type)
    {
      case Expose:
        if (event.xexpose.count == 0)
        {
          XSetForeground(display, gc, foreground);
          XClearWindow(display, window);
          color = rand();
          XSetForeground(display,gc,color);
          shield(display,window,gc);
        }
        break;

      case MappingNotify:
        XRefreshKeyboardMapping(&event.xmapping); // Change key distribution
        break;

      case ButtonPress:
        if (event.xbutton.button == Button1)  // Check if left bottom have been clicked
        {
          Resize(display,window,gc,0);
        } else if (event.xbutton.button == Button3){
          Resize(display,window,gc,1);
        }
        break;

      case ButtonRelease:
        
      break;

      case KeyPress:
        hm_keys = XLookupString(&event.xkey, buffer, 8, &key, 0);
        if (hm_keys == 1)
        {
          if (buffer[0] == 'q') to_end = TRUE;        // End of the program
          else if (buffer[0] == 'r'){  // Reset Default Set
            XClearWindow(display, window);
            shield(display,window,gc);  
          }
          else if (buffer[0] == 'c'){ // Color
            color = rand();
            XSetForeground(display,gc,color);
            Resize(display,window,gc,0);
            Resize(display,window,gc,1);
          }
          else if(buffer[0] == 'l'){
            if(letters == FALSE){
              DrawLetters(display,window,gc);
              letters = TRUE;
            }
            else{
              letters = False;
              Resize(display,window,gc,0);
              Resize(display,window,gc,1);
            }
          }
          else if(buffer[0] == 'm'){  // Move random
            // Mover aleatoriamente
          }
          else{
            Move(display,window,gc,buffer[0]);
          }
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
