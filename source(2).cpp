#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <conio.h>
using namespace std;

HINSTANCE _hInstance;
int _nCmdShow;
MSG msg;
HWND Nr_Elemente_Rand;

#define ID_FISIER				1201
#define ID_RANDOM				1202

#define IDC_AFISAREGRAF			1204
#define IDC_INSTRUCTIUNI		1206

int metoda_ins = 0;				//Monitor pentru metoda de insertie Folder sau Random
int nr_rand = 0;				//Numarul de elemente random
bool PrintGraf = false;			//Printam graficul
double timp_executie_Vector = 0;	//Timpii de executie Vector
double timp_executie_Liste = 0;		//Timpii de executie Liste
double timp_executie_DListe = 0;	//Timpii de executie Liste Dublu

//Radix Sort--------------------------------------------------------------------------------

//Vector************************************************************************************
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}
void countSort(int arr[], int n, int exp)
{
	int *output = (int*)malloc(n*sizeof(int));
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];
}
void Vector_RadixSort(int arr[], int n)
{
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}
void  RadixVector()
{
	int nr_elemente;

	if (metoda_ins == 2)			//Daca avem Random
	{
		nr_elemente = nr_rand;
		int *arr = (int*)malloc(nr_elemente*sizeof(int));
		for (int i = 0; i < nr_elemente; i++)
			arr[i] = rand();
		Vector_RadixSort(arr, nr_elemente);
	}
	else if (metoda_ins == 1)		//Daca citim din fiser
	{
		FILE *fd = fopen("date.in", "rt");
		fscanf(fd, "%d", &nr_elemente);
		int *arr = (int*)malloc(nr_elemente*sizeof(int));
		for (int i = 0; i < nr_elemente; i++)
			fscanf(fd, "%d", &arr[i]);
		fclose(fd);
		Vector_RadixSort(arr, nr_elemente);
	}
}
//******************************************************************************************

//Liste*************************************************************************************
void Liste_radixSort(int a[], int n, int m)
{
	typedef struct node
	{
		int data;
		struct node * next;
	}NODE;

	NODE * ptr, *start, *prev;
	NODE *front[10], *rear[10];
	int k = 1, i, j, y, p;;
	start = NULL;
	for (i = 0; i< n; ++i)
	{
		ptr = (NODE *)malloc(sizeof(NODE));
		ptr->data = a[i];
		ptr->next = NULL;
		if (start == NULL)
			start = ptr;
		else
			prev->next = ptr;
		prev = ptr;
	}
	for (i = 1; i <= m; ++i)
	{
		for (j = 0; j< 10; ++j)
			front[j] = NULL;
		ptr = start;
		while (ptr != NULL)
		{
			y = ptr->data / k % 10;
			if (front[y] == NULL)
			{
				front[y] = ptr;
				rear[y] = ptr;
			}
			else
			{
				rear[y]->next = ptr;
				rear[y] = ptr;
			}

			ptr = ptr->next;
		}

		start = NULL;
		for (j = 0; j< 10; ++j)
			if (front[j] != NULL)
			{
			if (start == NULL)
				start = front[j];
			else rear[p]->next = front[j];
			p = j;
			}
		rear[p]->next = NULL;
		k = k * 10;
	}
	ptr = start;
	for (i = 0; i< n; ++i, ptr = ptr->next)
		a[i] = ptr->data;

}
void RadixListe()
{
	int *a, n, i, m;
	m = 9;

	if (metoda_ins == 2)			//Daca avem Random
	{
		n = nr_rand;
		a = (int*)malloc(n*sizeof(int));
		for (i = 0; i < n; ++i)
			a[i] = rand();

		for (int ll = 0; ll < 2; ll++)
			Liste_radixSort(a, n, m);
	}
	else if (metoda_ins == 1)		//Daca citim din fiser
	{
		FILE *fd = fopen("date.in", "rt");
		fscanf(fd, "%d", &n);
		a = (int*)malloc(n*sizeof(int));
		for (int i = 0; i < n; i++)
			fscanf(fd, "%d", &a[i]);
		fclose(fd);
		for (int ll = 0; ll < 2; ll++)
			Liste_radixSort(a, n, m);
	}	
}
//******************************************************************************************

//Dlist************************************************************************************
void DListe_radixSort(int vector[], int n, int m)
{
	typedef struct node
	{
		int data;
		struct node * next;
		struct node * prev;
	}NODE;
	NODE * adresa;
	NODE *start;
	NODE *urmator;
	NODE *cap[10], *coada[10];
	int k = 1, i, j, y, p;
	start = NULL;
	for (i = 0; i< n; ++i)
	{
		adresa = (NODE *)malloc(sizeof(NODE));
		adresa->data = vector[i];
		adresa->next = NULL;
		adresa->prev = NULL;
		if (start == NULL)
			start = adresa;
		else
			urmator->next = adresa;
		urmator = adresa;
	}
	for (i = 1; i <= m; ++i)
	{
		for (j = 0; j< 10; ++j) cap[j] = NULL;
		adresa = start;
		while (adresa != NULL)
		{
			y = adresa->data / k % 10;
			if (cap[y] == NULL)
			{
				cap[y] = adresa;
				coada[y] = adresa;
			}
			else
			{
				coada[y]->next = adresa;
				coada[y] = adresa;
			}
			adresa = adresa->next;
		}

		start = NULL;
		for (j = 0; j< 10; ++j)
			if (cap[j] != NULL)
			{
			if (start == NULL)
				start = cap[j];
			else coada[p]->next = cap[j];
			p = j;
			}
		coada[p]->next = NULL;
		k = k * 10;
	}
	adresa = start;
	for (i = 0; i< n; ++i, adresa = adresa->next) vector[i] = adresa->data;
}
void RadixDListe()
{
	int *vector, elemente, i, m;
	m = 9;

	if (metoda_ins == 2)			//Daca avem Random
	{
		elemente = nr_rand;
		vector = (int*)malloc(elemente*sizeof(int));
		for (i = 0; i < elemente; ++i)
			vector[i] = rand();

		DListe_radixSort(vector, elemente, m);
	}
	else if (metoda_ins == 1)		//Daca citim din fiser
	{
		FILE *fd = fopen("date.in", "rt");
		fscanf(fd, "%d", &elemente);
		vector = (int*)malloc(elemente*sizeof(int));
		for (int i = 0; i < elemente; i++)
			fscanf(fd, "%d", &vector[i]);
		fclose(fd);
		DListe_radixSort(vector, elemente, m);
	}
}
//******************************************************************************************

//------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc_AlegeInsertie(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, holdBrush;
	HPEN hPen, holdPen;

	switch (msg) {

	case WM_CREATE:

		CreateWindowW(L"Button", L"Alege Metoda insertie",WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			5, 1, 200, 90, hwnd, (HMENU)0, _hInstance, NULL);
		CreateWindowW(L"Button", L"Fisier",WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,	
			55, 25, 100, 30, hwnd, (HMENU)ID_FISIER, _hInstance, NULL);
		CreateWindowW(L"Button", L"Random",WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			55, 55, 100, 30, hwnd, (HMENU)ID_RANDOM, _hInstance, NULL);

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case ID_FISIER:
			metoda_ins = 1;
			break;
		case ID_RANDOM:
			metoda_ins = 2;
			break;

		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

bool CHECKNUMBER(char *sir){
	if (strlen(sir) == 0)
		return false;
	for (int i = 0; i < strlen(sir); i++)
	{
		if (!isdigit(sir[i]))
			return false;
	}
	return true;
}
void Butoane(HWND hwnd)
{
	CreateWindow("BUTTON", "Afisare Grafic", WS_BORDER | WS_CHILD | WS_VISIBLE, 320, 10, 250, 30, hwnd, (HMENU)IDC_AFISAREGRAF, _hInstance, NULL);
	CreateWindow("BUTTON", "Instructiuni", WS_BORDER | WS_CHILD | WS_VISIBLE, 680, 10, 250, 30, hwnd, (HMENU)IDC_INSTRUCTIUNI, _hInstance, NULL);

	CreateWindowW(L"Button", L"Legenda ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,20, 250, 250, 270, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"Button", L"Grafic ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 310, 100, 630, 420, hwnd, (HMENU)0, _hInstance, NULL);

	CreateWindowW(L"static", L" >>> Vector", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 302, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"static", L" >>> Liste Simplu", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 382, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"static", L" >>> Liste Dublu", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 462, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);

	CreateWindowW(L"static", L" Numarul de elemente pentru Random:", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 320, 55, 310, 25, hwnd, (HMENU)0, _hInstance, NULL);
	Nr_Elemente_Rand = CreateWindow("edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 640, 55, 120, 25, hwnd, (HMENU)1, _hInstance, NULL);
	CreateWindowW(L"static", L"Maxim 175.000 elemente", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 770, 55, 200, 25, hwnd, (HMENU)0, _hInstance, NULL);
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT Ps;
		hdc = BeginPaint(hWnd, &Ps);

		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		HBRUSH hBrush, holdBrush;

		qLineColor = RGB(255, 255, 255);
		hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 300, 100, 330);

		hBrush = CreateSolidBrush(RGB(0, 133, 0));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 380, 100, 410);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 460, 100, 490);

		//---------PrintramGRafic
		if (PrintGraf)
		{
			//Avem boxul pentru grafic de la coordonatele 310 100 |||| 940 520
			int x,y,z;
			x=timp_executie_Vector;
			y=timp_executie_Liste;
			z=timp_executie_DListe;
			int maxx=x;
			if(y>maxx) maxx=y;
			else if(z>maxx) maxx=z;

			float ratia;
			char buff[100];
			
			
			ratia= 400.0/((float)maxx);
			sprintf(buff,"%f",ratia);

			//MessageBox(hWnd,buff,"LASA",MB_ICONERROR);

				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, 400, 519, 450, 519 - floor(ratia*(float)x));

				hBrush = CreateSolidBrush(RGB(0, 133, 0));
				holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, 600, 519, 650, 519 - floor(ratia*(float)y));

				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, 800, 519, 850, 519 - floor(ratia*(float)z));
		}
		//-----------------------

		EndPaint(hWnd, &Ps);
		break;

	case WM_CREATE:
	{
		WNDCLASSW wc = { 0 };
		wc.lpszClassName = L"AlegeInsertie";
		wc.hInstance = _hInstance;
		wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		wc.lpfnWndProc = WndProc_AlegeInsertie;
		wc.hCursor = LoadCursor(0, IDC_ARROW);

		RegisterClassW(&wc);
		CreateWindowW(L"AlegeInsertie", NULL, WS_CHILD | WS_VISIBLE, 20, 10, 210, 95, hWnd, (HMENU)1, NULL, NULL);

		//Butoanele
		Butoane(hWnd);
	}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_AFISAREGRAF:
		{
			//Daca nu avem nimic de inserat
			if (metoda_ins == 0)
			{
				MessageBoxW(hWnd, L"Alegeti o metoda de insertie!", L"Error", MB_ICONERROR);
				break;
			}
			PrintGraf = true;

			//Datele pentru Random
			if (metoda_ins == 2)
			{
				char buff[20];
				for (int i = 0; i <= 19; i++)
					buff[i] = '\0';

				SendMessage(Nr_Elemente_Rand, WM_GETTEXT, sizeof(buff) / sizeof(char), reinterpret_cast<LPARAM>(buff));

				DestroyWindow(Nr_Elemente_Rand);
				Nr_Elemente_Rand = CreateWindow("edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 640, 55, 120, 25, hWnd, (HMENU)1, _hInstance, NULL);
				if (CHECKNUMBER(buff) && atoi(buff)<=175000 && atoi(buff)>=3000)
					nr_rand = atoi(buff);
				else
					MessageBoxW(hWnd, L"Introduceti date valide!", L"Error", MB_ICONERROR);
			}

			//Pentru Liste------------------------
			clock_t tStart2 = clock();
			RadixListe();
			timp_executie_Liste = (double)(clock() - tStart2);
			char buff2[10];
			sprintf(buff2, "%.0f ms", timp_executie_Liste);
			CreateWindow("static", buff2, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 585, 521, 75, 25, hWnd, (HMENU)0, _hInstance, NULL);

			//Pentru Vector-----------------------
			clock_t tStart1 = clock();
			RadixVector();
			timp_executie_Vector = (double)(clock() - tStart1);
			char buff1[10];
			sprintf(buff1, "%.0f ms", timp_executie_Vector);
			CreateWindow("static", buff1, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 385, 521, 75, 25, hWnd, (HMENU)0, _hInstance, NULL);

			//Pentru Dliste-----------------------
			clock_t tStart3 = clock();
			RadixDListe();
			timp_executie_DListe = (double)(clock() - tStart3);
			char buff3[10];
			sprintf(buff3, "%.0f ms", timp_executie_DListe);
			CreateWindow("static", buff3, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 785, 521, 75, 25, hWnd, (HMENU)0, _hInstance, NULL);



			InvalidateRect(hWnd, NULL, TRUE);
		}
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	_nCmdShow = nShowCmd;
	_hInstance = hInst;

	//Setam culoarea de BCK
	HBRUSH hh = CreateSolidBrush(RGB(117, 163, 209));

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = hh;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = _hInstance;
	wClass.lpfnWndProc = (WNDPROC)WinProc;
	wClass.lpszClassName = "MainWnd";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wClass);

	HWND hWnd = CreateWindowEx(NULL, "MainWnd", "RadixSort", WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 1000, 600, NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}