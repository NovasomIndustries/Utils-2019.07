@echo off　

PATH %windir%;%windir%\system32
Set mysys=System32
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" Set mysys=SysWOW64

if not exist %windir%\%mysys%\ecologyplugin\   md  %windir%\%mysys%\ecologyplugin\

if not exist %windir%\%mysys%\ecologyplugin\chinaexcel\  md  %windir%\%mysys%\ecologyplugin\chinaexcel\
if not exist %windir%\%mysys%\ecologyplugin\fileupload\  md  %windir%\%mysys%\ecologyplugin\fileupload\
if not exist %windir%\%mysys%\ecologyplugin\iWebOffice\  md  %windir%\%mysys%\ecologyplugin\iWebOffice\
if not exist %windir%\%mysys%\ecologyplugin\teechart\  md  %windir%\%mysys%\ecologyplugin\teechart\

copy *.* %windir%\%mysys%\ecologyplugin\*.*  
copy chinaexcel\*.* %windir%\%mysys%\ecologyplugin\chinaexcel\*.*
copy fileupload\*.* %windir%\%mysys%\ecologyplugin\fileupload\*.*
copy iWebOffice\*.* %windir%\%mysys%\ecologyplugin\iWebOffice\*.*
copy teechart\*.* %windir%\%mysys%\ecologyplugin\teechart\*.*



echo  install chinaexcel ...
regsvr32 %windir%\%mysys%\ecologyplugin\chinaexcel\chinaexcelweb.ocx  /s

echo  install chinaexcelmenu ...
regsvr32 %windir%\%mysys%\ecologyplugin\chinaexcel\chinamenu.dll  /s

echo  install iWebOffice
regsvr32 %windir%\%mysys%\ecologyplugin\iWebOffice\iWebOffice2003.ocx  /s

echo  install PDF417Manager
regsvr32 %windir%\%mysys%\ecologyplugin\iWebOffice\PDF417Manager.dll  /s

echo  install teechart
regsvr32 %windir%\%mysys%\ecologyplugin\teechart\teechart.ocx   /s

echo  install fileupload
regsvr32 %windir%\%mysys%\ecologyplugin\fileupload\WeaverOcx.ocx  /s


echo 安装成功!

%windir%\%mysys%\ecologyplugin\readme.txt