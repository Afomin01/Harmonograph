linuxdeployqt required for AppImage build.

Execute all commands below from the project root.

1) Copy current Harmonograph linux build to AppDir/usr/bin
mkdir -p AppDir/usr/bin && cp Harmonograph AppDir/usr/bin

2) Copy icon
mkdir -p AppDir/usr/share/icons/hicolor/256x256
cp assets/icon.png AppDir/usr/share/icons/hicolor/256x256/Harmonograph.png

3) Build AppImage
linuxdeployqt AppDir/usr/share/applications/Harmonograph.desktop -verbose=2 -appimage
