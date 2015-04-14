!define PRODUCT_NAME "Code::Blocks IDE"
!define PRODUCT_VERSION "r6113"
;!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\codeblocks.exe"

SetCompressor /SOLID lzma
CRCCheck on

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\codeblocks.exe"
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Korean"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "Danish"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Norwegian"
!insertmacro MUI_LANGUAGE "NorwegianNynorsk"
!insertmacro MUI_LANGUAGE "Finnish"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Ukrainian"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "Slovak"
!insertmacro MUI_LANGUAGE "Croatian"
!insertmacro MUI_LANGUAGE "Bulgarian"
!insertmacro MUI_LANGUAGE "Hungarian"
!insertmacro MUI_LANGUAGE "Thai"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Latvian"
!insertmacro MUI_LANGUAGE "Macedonian"
!insertmacro MUI_LANGUAGE "Estonian"
!insertmacro MUI_LANGUAGE "Turkish"
!insertmacro MUI_LANGUAGE "Lithuanian"
!insertmacro MUI_LANGUAGE "Catalan"
!insertmacro MUI_LANGUAGE "Slovenian"
!insertmacro MUI_LANGUAGE "Serbian"
!insertmacro MUI_LANGUAGE "SerbianLatin"
!insertmacro MUI_LANGUAGE "Arabic"
!insertmacro MUI_LANGUAGE "Farsi"
!insertmacro MUI_LANGUAGE "Hebrew"
!insertmacro MUI_LANGUAGE "Indonesian"
!insertmacro MUI_LANGUAGE "Mongolian"
!insertmacro MUI_LANGUAGE "Luxembourgish"
!insertmacro MUI_LANGUAGE "Albanian"
!insertmacro MUI_LANGUAGE "Breton"
!insertmacro MUI_LANGUAGE "Belarusian"
!insertmacro MUI_LANGUAGE "Icelandic"
!insertmacro MUI_LANGUAGE "Malay"
!insertmacro MUI_LANGUAGE "Bosnian"
!insertmacro MUI_LANGUAGE "Kurdish"
!insertmacro MUI_LANGUAGE "Irish"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\LoveDEV_${PRODUCT_VERSION}.exe"
InstallDir "D:\LoveDEV"
;InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
BrandingText "portablecb.googlecode.com"

InstType "Complete installation"
InstType "Compact installation"

Section "Code::Blocks" SEC01
SectionIn 1 2
  SetOutPath "$INSTDIR"
  SetOverwrite on
  File "..\codeblocks.exe"
  File "..\codeblocks.dll"
  File "..\mingwm10.dll"
  File "..\exchndl.dll"
  File "..\default.conf"
  File "..\cb_console_runner.exe"
  File "..\wxmsw28u.dll"
  File "..\wxscintilla.dll"
  File "..\wxchartctrl.dll"
  File "..\wxcustombutton.dll"
  File "..\wxflatnotebook.dll"
  File "..\wxsmithlib.dll"
  File "..\cbKeyBinder10.ini"
  File "..\BrowseTracker.ini"
  File "..\debug.bat"
  File "..\cmd.lnk"

  SetOutPath "$INSTDIR\share"
  File /r "..\share\*.*"

  SetOutPath "$INSTDIR\tool"
  File "..\tool\cmd.bat"
SectionEnd

Section "GCC Compiler" SEC02
SectionIn 1 2
  SetOutPath "$INSTDIR\bin"
  File /r "..\bin\*.*"

  SetOutPath "$INSTDIR\include"
  File /r "..\include\*.*"

  SetOutPath "$INSTDIR\lib"
  File /r "..\lib\*.*"
SectionEnd

Section "C::B Tools" SEC03
SectionIn 1
  SetOutPath "$INSTDIR\tool"
  File /r "..\tool\*.*"
SectionEnd

Subsection /e "Program SDK" SEC04

Section "wxWidgets" SEC0401
SectionIn 1
  SetOutPath "$INSTDIR\sdk\wx"
  File /r "..\sdk\wx\*.*"
SectionEnd

Section "Boost" SEC0402
SectionIn 1
  SetOutPath "$INSTDIR\sdk\boost"
  File /r "..\sdk\boost\*.*"
SectionEnd

Section "Glut" SEC0403
SectionIn 1
  SetOutPath "$INSTDIR\sdk\glut"
  File /r "..\sdk\glut\*.*"
SectionEnd

Section "DirectX" SEC0404
SectionIn 1
  SetOutPath "$INSTDIR\sdk\dx"
  File /r "..\sdk\dx\*.*"
SectionEnd

Section "SDL" SEC0405
SectionIn 1
  SetOutPath "$INSTDIR\sdk\sdl"
  File /r "..\sdk\sdl\*.*"
SectionEnd


Section "Sqlite" SEC0406
SectionIn 1
  SetOutPath "$INSTDIR\sdk\sqlite"
  File /r "..\sdk\sqlite\*.*"
SectionEnd

Section "TinyXML" SEC0407
SectionIn 1
  SetOutPath "$INSTDIR\sdk\tinyxml"
  File /r "..\sdk\tinyxml\*.*"
SectionEnd

Section "HGE" SEC0408
SectionIn 1
  SetOutPath "$INSTDIR\sdk\hge"
  File /r "..\sdk\hge\*.*"
SectionEnd

SubSectionEnd
