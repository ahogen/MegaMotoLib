ECHO OFF

ECHO Regenerate documentation (Doxygen)...

del "%cd%\doc"

doxygen "%cd%\Doxyfile.config"

cd "%cd%\doc\latex"

ECHO Building PDF from LaTeX file...
CALL make.bat

ECHO Cleaning junk from LaTeX build...
for %%i in (*) do if not %%i == refman.pdf del %%i
ren refman.pdf MegaMoto-Arduino-lib-User-Guide.pdf
cd ..
cd ..
del "%cd%\release\MegaMoto_latest.zip"

ECHO Creating new .ZIP file for release...
E:\Programs\7-Zip\7z.exe a -tzip release\MegaMoto.zip *.h *.cpp *.md LICENSE "%cd%\doc" "%cd%\examples"

ECHO ------------
ECHO All done!!
ECHO ------------
PAUSE