# Microsoft Developer Studio Project File - Name="pscript" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=pscript - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pscript.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pscript.mak" CFG="pscript - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pscript - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "pscript - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pscript - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "GARBAGE_COLLECTOR" /YX /FD /c
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\pscript.lib"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\pscript.lib"

!ENDIF 

# Begin Target

# Name "pscript - Win32 Release"
# Name "pscript - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\psapi.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psbaselib.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pscompiler.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psdebug.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psfuncstate.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pslexer.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psmem.cpp
# End Source File
# Begin Source File

SOURCE=.\psobject.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psstate.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pstable.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psclass.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\psvm.cpp

!IF  "$(CFG)" == "pscript - Win32 Release"

!ELSEIF  "$(CFG)" == "pscript - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\psarray.h
# End Source File
# Begin Source File

SOURCE=.\psclosure.h
# End Source File
# Begin Source File

SOURCE=.\pscompiler.h
# End Source File
# Begin Source File

SOURCE=.\psfuncproto.h
# End Source File
# Begin Source File

SOURCE=.\psfuncstate.h
# End Source File
# Begin Source File

SOURCE=.\pslexer.h
# End Source File
# Begin Source File

SOURCE=.\psobject.h
# End Source File
# Begin Source File

SOURCE=.\psopcodes.h
# End Source File
# Begin Source File

SOURCE=.\pspcheader.h
# End Source File
# Begin Source File

SOURCE=.\psstate.h
# End Source File
# Begin Source File

SOURCE=.\psstring.h
# End Source File
# Begin Source File

SOURCE=.\pstable.h
# End Source File
# Begin Source File

SOURCE=.\psuserdata.h
# End Source File
# Begin Source File

SOURCE=.\psutils.h
# End Source File
# Begin Source File

SOURCE=.\psclass.h
# End Source File
# Begin Source File

SOURCE=.\psvm.h
# End Source File
# End Group
# End Target
# End Project
