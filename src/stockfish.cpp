#include "stockfish.h"
#define BUFSIZE 4096

bool Stockfish::initialize()
{
    child_input_rd = NULL;
    child_input_wr = NULL;
    child_output_rd = NULL;
    child_output_wr = NULL;

    saAttr.bInheritHandle = TRUE;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.lpSecurityDescriptor = NULL;

    //Creating input pipe to stockfish
    if (!CreatePipe(&child_input_rd, &child_input_wr, &saAttr, 0))
    {
        return false;
    }

    //Creating output pipe to stockfish
    if (!CreatePipe(&child_output_rd, &child_output_wr, &saAttr, 0))
    {
        return false;
    }

    
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    si.cb = sizeof(STARTUPINFO);
    si.hStdError = child_output_wr;
    si.hStdInput = child_input_rd;
    si.hStdOutput = child_output_wr;
    si.dwFlags |= STARTF_USESTDHANDLES;

    //Creating a childprocess

    if (!CreateProcess(
        stockFishPath,
        NULL,
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    ))
    {
        return false;
    }
    else
    {
        CloseHandle(child_output_wr);
        CloseHandle(child_input_rd);
    }

    char command[] = "uci\n";
    DWORD dwWritten, dwRead;
    char buff[BUFSIZE];

    if (!WriteFile(child_input_wr, command, strlen(command), &dwWritten, NULL))
    {
        return false;
    }


    BOOL foundUciok = FALSE;
    char response[BUFSIZE] = { 0 };

    while (!foundUciok)
    {
        ZeroMemory(buff, BUFSIZE);
        if (!ReadFile(child_output_rd, buff, BUFSIZE-1, &dwRead, NULL))
        {
            return false;
        }
        else
        {
            strcat(response, buff);
            if (strstr(response, "uciok") != NULL)
            {
                foundUciok = TRUE;
                break;
            }
        }
    }

    char command2[] = "isready\n";

    if (!WriteFile(child_input_wr, command2, strlen(command2), &dwWritten, NULL))
    {
        return false;
    }
  
    BOOL foundreadyok = FALSE;
    char response2[BUFSIZE] = {0};

    while (!foundreadyok)
    {
        ZeroMemory(buff, BUFSIZE);
        if (!ReadFile(child_output_rd, buff, BUFSIZE - 1, &dwRead, NULL))
        {
            return false;
        }
        else
        {
            
            strcat(response2, buff);
            if (strstr(response2, "readyok") != NULL)
            {
                foundreadyok = TRUE;
                break;
            }
        }
    }
    return true;
}

bool Stockfish::requestBestMove()
{
    char temppositioncommand[BUFSIZE];
    strcpy(temppositioncommand, positionCommand);
    strcat(temppositioncommand, "\n");
    DWORD dwWritten = -1;
    if (!WriteFile(child_input_wr, temppositioncommand, strlen(temppositioncommand), &dwWritten, NULL))
    {
        return false;
    }

    char* goCommand = "go movetime 50\n";

    if (!WriteFile(child_input_wr, goCommand, strlen(goCommand), &dwWritten, NULL))
    {
        return false;
    }
    return true;
}

void Stockfish::getBestMove()
{
    BOOL bestmovefound = FALSE;
    char response3[BUFSIZE] = { 0 };
    char buff[BUFSIZE] = { 0 };
    DWORD dwRead ;
    char bestmove[6] = { 0 };
    

    ZeroMemory(movemove, sizeof(movemove));
    while (!bestmovefound)
    {
        ZeroMemory(buff, BUFSIZE);
        if (!ReadFile(child_output_rd, buff, BUFSIZE-1, &dwRead, NULL))
        {
            return;
        }
        else
        {
            buff[dwRead] = '\0';
            strcat(response3, buff);

            char* ptr = strstr(response3, "bestmove");
            if (ptr != NULL)
            {
                ptr += 8;

                while (*ptr == ' ' || *ptr == '\t') ptr++;

                int i = 0;
                while (ptr[i] != ' ' && ptr[i] != '\n' && ptr[i] != '\r' && ptr[i] != '\0' && i < 5)
                {
                    bestmove[i] = ptr[i];
                    movemove[i] = ptr[i];
                    i++;
                }
                bestmove[i] = '\0';

                bestmovefound = TRUE;
                break;
            }
        }
    }
    return;
}

void Stockfish::closeHandles()
{
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(child_output_rd);
    CloseHandle(child_input_wr);
}