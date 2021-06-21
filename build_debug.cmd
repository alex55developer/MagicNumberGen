@set QTDIR=C:\Qt\Qt5.14.0
@set QMAKE=%QTDIR%\5.14.0\mingw73_64\bin\qmake.exe
@set MAKE=%QTDIR%\Tools\mingw730_64\bin\mingw32-make.exe

::@%QMAKE% .\robots_win.pro -spec win32-g++ "CONFIG+=debug"

cd ..\build-SequenceQt-Qt_5_14_0_MinGW_64_bit-Debug
::@%MAKE% clean
%MAKE% -j4
cd
move Sequence.exe ..\SequenceQt\bin
cd ..\SequenceQt

@echo -- OK --
