import platform
import shutil
import os

def RemoveFile(path):
    if os.path.isfile(path):
        os.remove(path)
        print(f"Cleaned {path}.")
    else:
        print(f"No file named {path} was found.")
    return

def WrapperRemoveTree(path):
    try:
        shutil.rmtree(path)
        print(f"Cleaned {path}.")
    except FileNotFoundError:
        print(f"No directory named {path} was found!")
    except PermissionError:
        print(f"{path} could not be deleted because it is used by a process. \nTerminate it and relaunch the script to remove {path}.")
    return

def DarwinCleanMakefile():
    RemoveFile("Makefile")
    RemoveFile("Build/Makefile")
    WrapperRemoveTree(".vscode/")
    return

def DarwinCleanXCode(location, projName):
    project = f"{location}{projName}.xcodeproj/"
    WrapperRemoveTree(workspace)
    WrapperRemoveTree(project)
    print(f"Cleaned {project}.")
    return

def WinCleanVS(location, projName):
    solution = f"{workspaceName}.sln"
    project = f"{location}{projName}.vcxproj"
    user = f"{location}{projName}.vcxproj.user"
    filt = f"{location}{projName}.vcxproj.filters"
    vsfold = ".vs/"
    RemoveFile(solution)
    RemoveFile(project)
    RemoveFile(user)
    RemoveFile(filt)
    WrapperRemoveTree(vsfold)
    return

if __name__ == "__main__":
    system = platform.system()
    projectName = "ConverterLib"
    workspaceName = "Converter"

    if system == "Darwin":
        if os.path.exists("Makefile") or os.path.exists(".vscode/"):
            DarwinCleanMakefile()
        if os.path.exists(f"{workspaceName}.xcworkspace"):
            workspace = f"{workspace}.xcworkspace/"
            DarwinCleanXCode("Build/Core", "ConverterLib")
            DarwinCleanXCode("Build/CLI", "ConverterCLI")

    elif system == "Windows":
        WinCleanVS("Build/Core", "ConverterLib")
        WinCleanVS("Build/CLI", "ConverterCLI")

    elif system == "Linux":
        DarwinCleanMakefile()

    else:
        print("Unidentified system. Halting.")
        exit(1)

    RemoveFile("todo.txt")
    WrapperRemoveTree("Binaries/")
    WrapperRemoveTree("Build/ProfilerLogs")
    print("Nothing left to clean. Halting")
    exit(0)
