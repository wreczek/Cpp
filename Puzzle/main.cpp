#include <windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <stdlib.h>

using std::swap;
using std::cout;
using std::endl;
using std::string;

namespace patch
{
    template < typename T > string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

struct Position
{
    int x;
    int y;
};

int counter = 0;
const int N = 16;
constexpr int ID[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
char * nums[N] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;
HWND g_hPrzycisk;
HINSTANCE hInstance;

HWND handlers[N] = {(HWND)0, (HWND)1, (HWND)2, (HWND)3, (HWND)4, (HWND)5, (HWND)6, (HWND)7, (HWND)8,
                   (HWND)9, (HWND)10, (HWND)11, (HWND)12, (HWND)13, (HWND)14, (HWND)15};

int freeX = 90;
int freeY = 90;

Position pos[N];

void slidePuzzle(int id);

bool isNeighbour(int x1, int y1, int x2, int y2);

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    srand(time(NULL));
    // WYPE£NIANIE STRUKTURY
    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;

    // okienko
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Ukladanka", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL );

    bool isOccupied[N];
    isOccupied[N-1] = true;
    for(int i = 0; i < N-1; i++) isOccupied[i] = false;

    Position sets[N] = { {0,0}, {30, 0}, {60, 0}, {90, 0},    // 0, 1, 2, 3
                    {0, 30}, {30, 30}, {60, 30}, {90, 30},   // 4, 5, 6, 7
                    {0, 60}, {30, 60}, {60, 60}, {90, 60},   // 8, 9, 10, 11
                    {0, 90}, {30, 90}, {60, 90}, {90, 90} };

    for(int i = 1; i < N; i++)  // i = {1, 2, .. 8}
    {
        int a;
        do
        {
            a = rand() % N; // a = {0, 1, .. 8}
        }
        while(isOccupied[a]);

        isOccupied[a] = true;
        handlers[i] = CreateWindowEx( 0, "BUTTON", nums[i], WS_CHILD | WS_VISIBLE,
                      sets[a].x, sets[a].y, 30, 30, hwnd, (HMENU)ID[i], hInstance, NULL);
        pos[i] = {sets[a].x, sets[a].y};
    }

    // ----------------
    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmowilo przyjscia na swiat!", "Ale kicha...", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nCmdShow ); // Pokaz okienko...
    UpdateWindow( hwnd );

    // Petla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

void slidePuzzle(int id, HWND hwnd)
{
    if(!isNeighbour(pos[id].x, pos[id].y, freeX, freeY)) return;
    {
        DestroyWindow(handlers[id]);
        handlers[id] = CreateWindowEx(0, "BUTTON", nums[id], WS_CHILD | WS_VISIBLE,
                      freeX, freeY, 30, 30, hwnd, (HMENU)ID[id], hInstance, NULL);
        swap(freeX, pos[id].x);
        swap(freeY, pos[id].y);
    }
}

bool isNeighbour(int x1, int y1, int x2, int y2)
{
    bool isNeighbourFlag = false;
    for(int i = 0; i < 4; i++)
    {
        isNeighbourFlag = (isNeighbourFlag || ( (x1 - 30 == x2 && y1 == y2) || (x1 + 30 == x2 && y1 == y2) ||
                                               (x1 == x2 && y1 - 30 == y2) || (x1 == x2 && y1 + 30 == y2)));
    }
    return isNeighbourFlag;
}

// OBSLUGA ZDARZEN
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_COMMAND:
        slidePuzzle((int)wParam, hwnd);
        break;

    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}
