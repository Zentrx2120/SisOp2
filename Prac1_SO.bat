:: Absalon Cortes Sebastian
:: 1 de marzo 2024
:: version 1.00

:: Sirve para que no se vean en la consola los comandos script a ejecutar
@echo off 

echo Bienvenido maestro
:: Sirva para poder hacer pausas antes de seguir con el codigo
timeout /t 3 /nobreak >nul
echo Le gustaria que inicie la pagina?
::Para poder hacer un salto de linea
echo.
echo 1.- Si
echo 2.- No
echo.

::Poder escanear
set /p op=Ingrese una opcion: 

::Condicional
if %op% == 1 (
	echo De acuerdo maestro
	timeout /t 2 /nobreak >nul
	start msedge.exe https://www.youtube.com/
	exit
) else if %op% == 2 (
	echo Entonces me retiro maestro
	timeout /t 2 /nobreak >nul
	exit
) else (
	echo Disculpe maestro pero no puedo realizar eso
)

