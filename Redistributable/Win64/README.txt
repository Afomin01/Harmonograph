1) Copy Windows binary Harmongoraph.exe file to packages\com.lantromipis.harmonograph\data.

2) Run <PATH TO QT INSTALLATION>\<QT VERSION>\msvc2019_64\bin\windeployqt.exe packages\com.lantromipis.harmonograph\data\Harmongoraph.exe
This will made all needed dll files for app. After that you can build your installer.

3) To build, use Qt Installer Framework
<PATH TO QtIFW INSTALLATION>\bin\binarycreator.exe -c config\config.xml -p packages Harmonograph-Installer-Win-x64.exe