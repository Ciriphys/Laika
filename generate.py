import platform
import os

def XCodeSetPCHLocation(location, projectName):
    filedata = ""
    with open(f"{location}/{projectName}.xcodeproj/project.pbxproj", "r") as file:
        filedata = file.read()
    
    filedata = filedata.replace("GCC_PREFIX_HEADER = pch.h", "GCC_PREFIX_HEADER = Include/pch.h")

    with open(f"{location}/{projectName}.xcodeproj/project.pbxproj", "w+") as file:
        file.write(filedata)

if __name__ == "__main__":
    system = platform.system()
    command = ""
    selection = ""

    if system == "Darwin":
        selection = input("Enter the action (gmake2 ~ Makefile | xcode4 ~ XCode): ")
        command = f"./Vendor/premake5/macOS/premake5 {selection}"
    elif system == "Windows":
        command = str("\"Vendor\\premake5\\Windows\\premake5.exe\" vs2022")
    elif system == "Linux":
        command = "./Vendor/premake5/Linux/premake5 gmake2"
    else:
        print("Unidentified system. Halting.")
        exit(1)

    print(command)
    os.system(command)
    
    if selection == "xcode4":
        XCodeSetPCHLocation("Build/Core", "ConverterLib")
        XCodeSetPCHLocation("Build/CLI", "ConverterCLI")
