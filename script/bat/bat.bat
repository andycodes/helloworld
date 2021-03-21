set andy=fansaihua
echo andy=%andy%
md .\fansaihua
echo echo HELLO FANSAIHUA>.\fansaihua\test.bat
call .\fansaihua\test.bat


@for /L %%i in (1,1,3) do echo %%i


REM DELAY  N s 
echo  time%time%
ping /n 2 127.0.0.1 >nul
echo time%time%

rd  /S  /Q .\fansaihua
pause