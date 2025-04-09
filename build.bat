@echo off
echo Compilando server.c...

gcc server.c -o server ^
 -L"C:\Program Files\mingw64\x86_64-w64-mingw32\lib" ^
 -lws2_32 -lshell32 -luser32 -lpthread

if errorlevel 1 (
    echo Erro ao compilar server.c
    pause
    exit /b
)

echo Compilando client.c...

gcc client.c -o client ^
 -L"C:\Program Files\mingw64\x86_64-w64-mingw32\lib" ^
 -lws2_32 -lshell32 -luser32 -lpthread

if errorlevel 1 (
    echo Erro ao compilar client.c
    pause
    exit /b
)

echo.
echo ✅ Compilação concluída com sucesso!
pause
