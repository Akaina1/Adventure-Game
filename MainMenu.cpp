//implementation for the main menu function for the game
#include "MainMenu.h"
#include "PlayerCharacter.h"

void TypeText(const std::wstring& text, int delay) // function to type out text with a delay
{
	for (wchar_t c : text) // for each character in the text
	{
		std::wcout << c << std::flush; // print out the character
		std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // wait for delay milliseconds
	}
};

void EraseStringFromConsole(const std::wstring& str, int delay) {
    for (int i = 0; i < str.length(); i++) {
        std::wcout << "\b \b";
        std::wcout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
};

int MainMenu()
{
    _setmode(_fileno(stdout), _O_U16TEXT); // setmode for unicode output


    HWND console = GetConsoleWindow(); // get console window
    RECT ConsoleRect; // create a rectangle for the console window
    GetWindowRect(console, &ConsoleRect); // get the console window rectangle
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size

    int Selection = 0;
    const std::wstring Filler1(44, L'\u2588');
    const std::wstring Filler2(7, L'\u2588');
    const std::wstring Filler3(8, L'\u2588');
    const std::wstring Filler4(17, L'\u2588');
    const std::wstring Filler5(18, L'\u2588');
    const std::wstring MenuTitle = L"MAIN MENU";
    const std::wstring PlayGame1 = L"[1]------->Play Game<-------";
    const std::wstring LoadGame1 = L"[2]------->Load Game<-------";
    const std::wstring QuitGame1 = L"[3]------->Quit Game<-------";

    TypeText(Filler1, 1);
    std::wcout << "\n";
    TypeText(Filler1, 1);
    std::wcout << std::endl;
    TypeText(Filler4, 1);
    TypeText(MenuTitle, 1);
    TypeText(Filler5, 1);
    std::wcout << std::endl;
    TypeText(Filler1, 1);
    std::wcout << std::endl;
    TypeText(Filler3, 1);
    TypeText(PlayGame1, 1);
    TypeText(Filler3, 1);
    std::wcout << std::endl;
    TypeText(Filler1, 1);
    std::wcout << std::endl;
    TypeText(Filler3, 1);
    TypeText(LoadGame1, 1);
    TypeText(Filler3, 1);
    std::wcout << std::endl;
    TypeText(Filler1, 1);
    std::wcout << std::endl;
    TypeText(Filler3, 1);
    TypeText(QuitGame1, 1);
    TypeText(Filler3, 1);
    std::wcout << std::endl;
    TypeText(Filler1, 1);
    std::wcout << std::endl;

    _setmode(_fileno(stdout), _O_TEXT);
    std::cout << "Enter your Selection: ";
    std::cin >> Selection;

    return Selection;
};


