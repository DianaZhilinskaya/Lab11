// lab11.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include "lab11.h"
#include "math.h" //для функций rand-случаные значения

#define MAX_LOADSTRING 100

HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// текст строи заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна


// Отправить обьявления функций. включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//обьявление для гл окна
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM); //обьявление для дочернего

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB11, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB11));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  Функция: MyRegisterClass()
//
//  Назначения: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	HBRUSH MyBrush = CreateSolidBrush(RGB(255, 255, 200)); // желтая кисточка

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // добавление CS_DBLCLKS для двойного щелчка
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	// иконка трактора загруженная в ресурсы с ид  IDI_TRACTOR
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRACTOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.hbrBackground = (HBRUSH)MyBrush; //созданная кисточка
	wcex.lpszClassName	= szWindowClass;
	// иконка трактора загруженная в ресурсы с ид  IDI_TRACTOR
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TRACTOR));

	return RegisterClassEx(&wcex);
}

//
//   Функция: InitInstance(HINSTANCE, int)
//
//   Назначение: сохраняет обработку экземпляра и создает главное окно.
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводит на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // сохранить дескриптор экземпляра в глобальной переменной

   // положение окна
   int WinX = 100, WinY = 150;
   // размер окна
   int WinHeight = 300, WinWidth = 500;

 
   hWnd = CreateWindow(szWindowClass, L"Lab №11", WS_OVERLAPPEDWINDOW,
	   WinX, WinY, WinWidth, WinHeight, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  Функция: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Назначение:  обрабатывает сообщение в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	- закраска окна
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, i;
	PAINTSTRUCT ps;
	HDC hdc;
	// прямоугольник размеров гл окна
	static RECT R;
	// номер создаваемого окна
	static int WinNumer = 0;
	//массив дескрипторов окошек
	static HWND child[5];

	switch (message)
	{
	// событие двойного щелчка мыши по окну
	case WM_LBUTTONDBLCLK:
		GetWindowRect(hWnd, &R);
		// изменяется (уменьшаем на 10 с каждой стороны)
		R.left += 10;
		R.top += 10;
		R.right -= 10;
		R.bottom -= 10;
		
		// задание новых размеров окна:
		SetWindowPos(hWnd, NULL, R.left, R.top, R.right - R.left, R.bottom - R.top, NULL);
		SetClassLong(child[WinNumer], GCL_HBRBACKGROUND,
		//(LONG)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
			(LONG)CreateSolidBrush(RGB(125, 130, 213)));
		InvalidateRect(child[WinNumer], NULL, TRUE); //обеспечивает перерисовку окон 
		//ccc++;
		break;
	case WM_LBUTTONDOWN:
		
		//определяем имя и номер создаваемого окна
		if (WinNumer > 4)
		{
			break; 
			//если окон уже 5-выходим
		}
		WinNumer++;
		TCHAR winname[100]; //имя окна
		_stprintf(winname, L"Dochernee okno №d", WinNumer);
		 
		// узнаем размер главного окна
		if (WinNumer == 1) GetWindowRect(hWnd, &R);
		// положение окна
		RECT NewR;
		NewR.left = R.left + 50 * WinNumer;
		NewR.top = R.top + 50 * WinNumer;
		NewR.right = R.right + 50 * WinNumer;
		NewR.bottom = R.bottom + 50 * WinNumer;
		//szWindowClass
		child[WinNumer] = CreateWindow(szWindowClass, winname,
			WS_CAPTION | WS_BORDER | WS_POPUP,
			NewR.left, NewR.top, NewR.right - NewR.left, NewR.bottom - NewR.top, hWnd, NULL, hInst, NULL);
		if (!child[WinNumer])
		{
			break;
		}
		// выводим
		ShowWindow(child[WinNumer], 10);
		UpdateWindow(child[WinNumer]);
		// меняем фон окна
		
		// rand()%255+1 - случайное значение от 0 до 255
		//SetClassLong(child[WinNumer], GCL_HBRBACKGROUND,
			//(LONG)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
		//	(LONG)CreateSolidBrush(RGB(125, 130, 213)));
		//InvalidateRect(child[WinNumer], NULL, TRUE); //обеспечивает перерисовку окон 
		//
		break;
	case WM_KEYDOWN:
		// скрываем окно
		ShowWindow(child[WinNumer], SW_HIDE);
		if (WinNumer > 0) WinNumer--; //уменьшаем номер
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		// пользователь нажал на крестик окна
		// выводим сообщение
		WORD Result;
		Result = MessageBox(hWnd, L"Close?", L"Realy?", //текст и заголовок
			MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2);
		//флаги: кнопки=ОК+Отмена, иконка+вопрос, по умолчанию выбрана 2-ая кнопка
		if (Result == IDOK)  //   == IDOK - нажали OK     
		{
			// генерирует сообщение закрытия окна
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
