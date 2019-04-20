@echo off°°

PATH %windir%;%windir%\system32;
Set mysys=System32
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" Set mysys=SysWOW64

echo  uninstall chinaexcel ...
regsvr32 %windir%\%mysys%\ecologyplugin\chinaexcel\chinaexcelweb.ocx /u /s

echo  uninstall chinaexcelmenu ...
regsvr32 %windir%\%mysys%\ecologyplugin\chinaexcel\chinamenu.dll /u /s

echo  uninstall iWebOffice
regsvr32 %windir%\%mysys%\ecologyplugin\iWebOffice\iWebOffice2003.ocx /u  /s

echo  uninstall PDF417Manager
regsvr32 %windir%\%mysys%\ecologyplugin\iWebOffice\PDF417Manager.dll /u  /s

echo  uninstall teechart
regsvr32 %windir%\%mysys%\ecologyplugin\teechart\teechart.ocx /u   /s

echo  uninstall fileupload
regsvr32 %windir%\%mysys%\ecologyplugin\fileupload\WeaverOcx.ocx /u   /s


rd  %windir%\%mysys%\ecologyplugin /Q/S

echo –∂‘ÿ≥…π¶!
pause