#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOUSER
#include <windows.h>
#define BUFSIZE 4096

class Stockfish
{
protected:
	HANDLE child_input_wr = NULL;
	HANDLE child_input_rd = NULL;
	HANDLE child_output_wr = NULL;
	HANDLE child_output_rd = NULL;
	HANDLE inputFile = NULL;

	SECURITY_ATTRIBUTES saAttr;


	PROCESS_INFORMATION piProcInfo;
	STARTUPINFOA siStartInfo;
	BOOL bSuccess = FALSE;

	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	const WCHAR* stockFishPath = L"C:\\Users\\Kaustubh\\OneDrive\\Desktop\\Pranav\\stockfish\\stockfish-windows-x86-64-avx2.exe";


public:
	char positionCommand[BUFSIZE] = "position startpos moves";
	char movemove[6] = { 0 };
	
public:
	bool initialize();
	bool requestBestMove();
	void getBestMove();
	void closeHandles();
};