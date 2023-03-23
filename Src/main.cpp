#include <iostream>

using namespace std;

#include <X11/Xlib.h>

int main()
{
    //create a x11 window and display it
    Display *display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        cout << "Cannot open display" << endl;
        exit(1);
    }

    int screen = DefaultScreen(display);

    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 100, 100, 1,
                                        BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);

    XMapWindow(display, window);

    //event loop
    XEvent event;

    while (1)
    {
        XNextEvent(display, &event);

        if (event.type == Expose)
        {
            
        }
        // If the event is a keypress
        if (event.type == KeyPress)
        {
            // Break from the loop
            break;
        }

        //client message
        if (event.type == ClientMessage)
        {
            //xdnd
            if (event.xclient.message_type == XInternAtom(display, "XdndDrop", False))
            {
                cout << "xdnd drop" << endl;

                //request data
                Atom xdndSelection = XInternAtom(display, "XdndSelection", False);

                //request  file list from source window
                XConvertSelection(display, xdndSelection, XInternAtom(display, "text/uri-list", False), xdndSelection, window, CurrentTime);
            }
        }


        //selection notify
        if (event.type == SelectionNotify)
        {
            cout << "selection notify" << endl;

            //get data
            Atom xdndSelection = XInternAtom(display, "XdndSelection", False);
            Atom actual_type;
            int actual_format;
            unsigned long nitems, bytes_after;
            unsigned char *data = NULL;
            int status = XGetWindowProperty(display, window, xdndSelection, 0, 1000000, False, AnyPropertyType, &actual_type, &actual_format, &nitems, &bytes_after, &data);
            if (status == Success)
            {
                //print file path
                cout << "data: " << data << endl;
            }
        }
    }




}
