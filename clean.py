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
    project = f"{location}/{projName}.xcodeproj/"
    WrapperRemoveTree(workspace)
    WrapperRemoveTree(project)
    print(f"Cleaned {project}.")
    return

def WinCleanVS(location, projName):
    solution = f"{workspaceName}.sln"
    project = f"{location}/{projName}.vcxproj"
    user = f"{location}/{projName}.vcxproj.user"
    filt = f"{location}/{projName}.vcxproj.filters"
    vsfold = ".vs/"
    RemoveFile(solution)
    RemoveFile(project)
    RemoveFile(user)
    RemoveFile(filt)
    WrapperRemoveTree(vsfold)
    return

if __name__ == "__main__":
    system = platform.system()
    projectName = "LaikaLib"
    workspaceName = "Laika"

    if system == "Darwin":
        if os.path.exists("Makefile") or os.path.exists(".vscode/"):
            DarwinCleanMakefile()
        if os.path.exists(f"{workspaceName}.xcworkspace"):
            workspace = f"{workspaceName}.xcworkspace/"
            DarwinCleanXCode("Build/Core", "LaikaLib")
            DarwinCleanXCode("Build/CLI", "LaikaCLI")

    elif system == "Windows":
        WinCleanVS("Build/Core", "LaikaLib")
        WinCleanVS("Build/CLI", "LaikaCLI")

    elif system == "Linux":
        DarwinCleanMakefile()

    else:
        print("Unidentified system. Halting.")
        exit(1)

    RemoveFile("todo.txt")
    WrapperRemoveTree("Binaries/")
    print("Nothing left to clean. Halting")
    exit(0)
