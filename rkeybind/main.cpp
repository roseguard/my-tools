#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <X11/keysym.h>
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <memory>
#include <thread>


using namespace std;


class Keyboard
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Key codes
    ///
    ////////////////////////////////////////////////////////////
    enum Key
    {
        Unknown = -1, ///< Unhandled key
        A = 0,        ///< The A key
        B,            ///< The B key
        C,            ///< The C key
        D,            ///< The D key
        E,            ///< The E key
        F,            ///< The F key
        G,            ///< The G key
        H,            ///< The H key
        I,            ///< The I key
        J,            ///< The J key
        K,            ///< The K key
        L,            ///< The L key
        M,            ///< The M key
        N,            ///< The N key
        O,            ///< The O key
        P,            ///< The P key
        Q,            ///< The Q key
        R,            ///< The R key
        S,            ///< The S key
        T,            ///< The T key
        U,            ///< The U key
        V,            ///< The V key
        W,            ///< The W key
        X,            ///< The X key
        Y,            ///< The Y key
        Z,            ///< The Z key
        Num0,         ///< The 0 key
        Num1,         ///< The 1 key
        Num2,         ///< The 2 key
        Num3,         ///< The 3 key
        Num4,         ///< The 4 key
        Num5,         ///< The 5 key
        Num6,         ///< The 6 key
        Num7,         ///< The 7 key
        Num8,         ///< The 8 key
        Num9,         ///< The 9 key
        Escape,       ///< The Escape key
        LControl,     ///< The left Control key
        LShift,       ///< The left Shift key
        LAlt,         ///< The left Alt key
        LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl,     ///< The right Control key
        RShift,       ///< The right Shift key
        RAlt,         ///< The right Alt key
        RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,         ///< The Menu key
        LBracket,     ///< The [ key
        RBracket,     ///< The ] key
        SemiColon,    ///< The ; key
        Comma,        ///< The , key
        Period,       ///< The . key
        Quote,        ///< The ' key
        Slash,        ///< The / key
        BackSlash,    ///< The \ key
        Tilde,        ///< The ~ key
        Equal,        ///< The = key
        Dash,         ///< The - key
        Space,        ///< The Space key
        Return,       ///< The Return key
        BackSpace,    ///< The Backspace key
        Tab,          ///< The Tabulation key
        PageUp,       ///< The Page up key
        PageDown,     ///< The Page down key
        End,          ///< The End key
        Home,         ///< The Home key
        Insert,       ///< The Insert key
        Delete,       ///< The Delete key
        Add,          ///< The + key
        Subtract,     ///< The - key
        Multiply,     ///< The * key
        Divide,       ///< The / key
        Left,         ///< Left arrow
        Right,        ///< Right arrow
        Up,           ///< Up arrow
        Down,         ///< Down arrow
        Numpad0,      ///< The numpad 0 key
        Numpad1,      ///< The numpad 1 key
        Numpad2,      ///< The numpad 2 key
        Numpad3,      ///< The numpad 3 key
        Numpad4,      ///< The numpad 4 key
        Numpad5,      ///< The numpad 5 key
        Numpad6,      ///< The numpad 6 key
        Numpad7,      ///< The numpad 7 key
        Numpad8,      ///< The numpad 8 key
        Numpad9,      ///< The numpad 9 key
        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F9 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key
        F13,          ///< The F13 key
        F14,          ///< The F14 key
        F15,          ///< The F15 key
        Pause,        ///< The Pause key

        KeyCount      ///< Keep last -- the total number of keyboard keys
    };
};


bool isKeyPressed(int key)
{
    // Get the corresponding X11 keysym
    KeySym keysym = 0;
    switch (key)
    {
    case Keyboard::LShift:     keysym = XK_Shift_L;      break;
    case Keyboard::RShift:     keysym = XK_Shift_R;      break;
    case Keyboard::LControl:   keysym = XK_Control_L;    break;
    case Keyboard::RControl:   keysym = XK_Control_R;    break;
    case Keyboard::LAlt:       keysym = XK_Alt_L;        break;
    case Keyboard::RAlt:       keysym = XK_Alt_R;        break;
    case Keyboard::LSystem:    keysym = XK_Super_L;      break;
    case Keyboard::RSystem:    keysym = XK_Super_R;      break;
    case Keyboard::Menu:       keysym = XK_Menu;         break;
    case Keyboard::Escape:     keysym = XK_Escape;       break;
    case Keyboard::SemiColon:  keysym = XK_semicolon;    break;
    case Keyboard::Slash:      keysym = XK_slash;        break;
    case Keyboard::Equal:      keysym = XK_equal;        break;
    case Keyboard::Dash:       keysym = XK_minus;        break;
    case Keyboard::LBracket:   keysym = XK_bracketleft;  break;
    case Keyboard::RBracket:   keysym = XK_bracketright; break;
    case Keyboard::Comma:      keysym = XK_comma;        break;
    case Keyboard::Period:     keysym = XK_period;       break;
    case Keyboard::Quote:      keysym = XK_apostrophe;   break;
    case Keyboard::BackSlash:  keysym = XK_backslash;    break;
    case Keyboard::Tilde:      keysym = XK_grave;        break;
    case Keyboard::Space:      keysym = XK_space;        break;
    case Keyboard::Return:     keysym = XK_Return;       break;
    case Keyboard::BackSpace:  keysym = XK_BackSpace;    break;
    case Keyboard::Tab:        keysym = XK_Tab;          break;
    case Keyboard::PageUp:     keysym = XK_Prior;        break;
    case Keyboard::PageDown:   keysym = XK_Next;         break;
    case Keyboard::End:        keysym = XK_End;          break;
    case Keyboard::Home:       keysym = XK_Home;         break;
    case Keyboard::Insert:     keysym = XK_Insert;       break;
    case Keyboard::Delete:     keysym = XK_Delete;       break;
    case Keyboard::Add:        keysym = XK_KP_Add;       break;
    case Keyboard::Subtract:   keysym = XK_KP_Subtract;  break;
    case Keyboard::Multiply:   keysym = XK_KP_Multiply;  break;
    case Keyboard::Divide:     keysym = XK_KP_Divide;    break;
    case Keyboard::Pause:      keysym = XK_Pause;        break;
    case Keyboard::F1:         keysym = XK_F1;           break;
    case Keyboard::F2:         keysym = XK_F2;           break;
    case Keyboard::F3:         keysym = XK_F3;           break;
    case Keyboard::F4:         keysym = XK_F4;           break;
    case Keyboard::F5:         keysym = XK_F5;           break;
    case Keyboard::F6:         keysym = XK_F6;           break;
    case Keyboard::F7:         keysym = XK_F7;           break;
    case Keyboard::F8:         keysym = XK_F8;           break;
    case Keyboard::F9:         keysym = XK_F9;           break;
    case Keyboard::F10:        keysym = XK_F10;          break;
    case Keyboard::F11:        keysym = XK_F11;          break;
    case Keyboard::F12:        keysym = XK_F12;          break;
    case Keyboard::F13:        keysym = XK_F13;          break;
    case Keyboard::F14:        keysym = XK_F14;          break;
    case Keyboard::F15:        keysym = XK_F15;          break;
    case Keyboard::Left:       keysym = XK_Left;         break;
    case Keyboard::Right:      keysym = XK_Right;        break;
    case Keyboard::Up:         keysym = XK_Up;           break;
    case Keyboard::Down:       keysym = XK_Down;         break;
    case Keyboard::Numpad0:    keysym = XK_KP_Insert;    break;
    case Keyboard::Numpad1:    keysym = XK_KP_End;       break;
    case Keyboard::Numpad2:    keysym = XK_KP_Down;      break;
    case Keyboard::Numpad3:    keysym = XK_KP_Page_Down; break;
    case Keyboard::Numpad4:    keysym = XK_KP_Left;      break;
    case Keyboard::Numpad5:    keysym = XK_KP_Begin;     break;
    case Keyboard::Numpad6:    keysym = XK_KP_Right;     break;
    case Keyboard::Numpad7:    keysym = XK_KP_Home;      break;
    case Keyboard::Numpad8:    keysym = XK_KP_Up;        break;
    case Keyboard::Numpad9:    keysym = XK_KP_Page_Up;   break;
    case Keyboard::A:          keysym = XK_a;            break;
    case Keyboard::B:          keysym = XK_b;            break;
    case Keyboard::C:          keysym = XK_c;            break;
    case Keyboard::D:          keysym = XK_d;            break;
    case Keyboard::E:          keysym = XK_e;            break;
    case Keyboard::F:          keysym = XK_f;            break;
    case Keyboard::G:          keysym = XK_g;            break;
    case Keyboard::H:          keysym = XK_h;            break;
    case Keyboard::I:          keysym = XK_i;            break;
    case Keyboard::J:          keysym = XK_j;            break;
    case Keyboard::K:          keysym = XK_k;            break;
    case Keyboard::L:          keysym = XK_l;            break;
    case Keyboard::M:          keysym = XK_m;            break;
    case Keyboard::N:          keysym = XK_n;            break;
    case Keyboard::O:          keysym = XK_o;            break;
    case Keyboard::P:          keysym = XK_p;            break;
    case Keyboard::Q:          keysym = XK_q;            break;
    case Keyboard::R:          keysym = XK_r;            break;
    case Keyboard::S:          keysym = XK_s;            break;
    case Keyboard::T:          keysym = XK_t;            break;
    case Keyboard::U:          keysym = XK_u;            break;
    case Keyboard::V:          keysym = XK_v;            break;
    case Keyboard::W:          keysym = XK_w;            break;
    case Keyboard::X:          keysym = XK_x;            break;
    case Keyboard::Y:          keysym = XK_y;            break;
    case Keyboard::Z:          keysym = XK_z;            break;
    case Keyboard::Num0:       keysym = XK_0;            break;
    case Keyboard::Num1:       keysym = XK_1;            break;
    case Keyboard::Num2:       keysym = XK_2;            break;
    case Keyboard::Num3:       keysym = XK_3;            break;
    case Keyboard::Num4:       keysym = XK_4;            break;
    case Keyboard::Num5:       keysym = XK_5;            break;
    case Keyboard::Num6:       keysym = XK_6;            break;
    case Keyboard::Num7:       keysym = XK_7;            break;
    case Keyboard::Num8:       keysym = XK_8;            break;
    case Keyboard::Num9:       keysym = XK_9;            break;
    default:                   keysym = 0;               break;
    }

    // Sanity checks
    //if (key < 0 || key >= sf::Keyboard::KeyCount)
    //  return false;

    // Open a connection with the X server
    //Display* display = OpenDisplay();
    auto display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "xdisplayOpen" << endl;
        return false;
    }

    // Convert to keycode
    xcb_keycode_t keycode = XKeysymToKeycode(display, keysym);



    xcb_generic_error_t *error;

    // Open a connection with the X server
    xcb_connection_t* connection = XGetXCBConnection(display);

    // Get the whole keyboard state
    auto keymap(
                xcb_query_keymap_reply(
                    connection,
                    xcb_query_keymap(connection),
                    &error
                    )
                );


    XCloseDisplay(display);
    // Check our keycode
    return (keymap->keys[keycode / 8] & (1 << (keycode % 8))) != 0;
}

int main() {
    while(1) {
        this_thread::sleep_for(chrono::milliseconds(5));
        if (isKeyPressed(Keyboard::LControl) && isKeyPressed(Keyboard::Num1)) {
        system("setxkbmap ru");
        }
        if (isKeyPressed(Keyboard::LControl) && isKeyPressed(Keyboard::Num2)) {
        system("setxkbmap us");
        }
        if (isKeyPressed(Keyboard::LControl) && isKeyPressed(Keyboard::Num3)) {
        system("setxkbmap ua");
        }
    }

    return 0;
}
