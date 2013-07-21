#-*- utf-8 -*-



import os
import sys
import time
import zipfile
import subprocess
import shutil

rootScriptName = os.path.abspath(os.path.dirname(__file__))
outputDirName = rootScriptName+'/product'
print(rootScriptName)

luaHeliumDir = os.path.normpath(rootScriptName + '/../lua')
luaArchiveWithSrcs = os.path.expanduser("~/Dropbox/game_project/helium_resource/thirdparty_libraries/lua-5.2.2.zip")

if not os.path.isdir(rootScriptName+'/log'):
    os.mkdir(rootScriptName+'/log')

log_file = open("log/heluim_thirdparty_buildlog_"+time.strftime("%m.%d_%H.%M.%S") + '.log', 'a')

#os.path.normpath()

def luaDownloadAndBuild ( buildType ):
    
    luaHeliumWorkingDir = os.path.normpath(rootScriptName + '/../lua/build')
    log_file.write('Lua ' + buildType + ' building ')
    print('Lua ' + buildType + ' building ')
    
    luaArch = zipfile.ZipFile(luaArchiveWithSrcs, 'r')
    luaArch.extractall(luaHeliumDir)
    
    log_file.write('downloaded: '+luaArchiveWithSrcs)
    print('downloaded: '+luaArchiveWithSrcs)
    log_file.write('and extracted to: '+luaHeliumDir)
    print('and extracted to: '+luaHeliumDir)
    
    if os.path.isdir(luaHeliumWorkingDir):
        shutil.rmtree(luaHeliumWorkingDir)
        
    os.mkdir(luaHeliumWorkingDir)
    cmakeBuildType = ''
    if buildType == 'Release' or builType == 'Debug':
        luaHeliumWorkingDir = luaHeliumWorkingDir + '/' + buildType
        os.mkdir(luaHeliumWorkingDir)
        cmakeBuildType = '-DCMAKE_BUILD_TYPE='+buildType
    else:
        buildType = ''
    
    cmakeGenerator = ''
    if sys.platform == 'linux2':
        cmakeGenerator = '-GUnix Makefiles'
    elif sys.platform == 'win32':
        cmakeGenerator = '-GVisual Studio 11'
        
    os.chdir(luaHeliumWorkingDir)

    cmakeInstallParam = '-DHELIUM_THIRD_PARTY_OUTPUT_PATH='+outputDirName
    luaCmakeCmd = [ 'cmake',
                    cmakeGenerator,
                    cmakeBuildType,
                    cmakeInstallParam,
                    luaHeliumDir    ]
    
    cmakeProc = subprocess.Popen(luaCmakeCmd, stdout=subprocess.PIPE)
    log, logEr = cmakeProc.communicate()
    
    if log:
        log_file.write(log)
        print("Stdout:\n")
        print(log)
        
    if logEr:
        log_file.write(logEr)
        print("Error out:\n")
        print(logEr)

    makeProc = subprocess.Popen(['make'], stdout=subprocess.PIPE)
    log, logEr = makeProc.communicate()

    if log:
        log_file.write(log)
        print("Stdout:\n")
        print(log)
        
    if logEr:
        log_file.write(logEr)
        print("Error out:\n")
        print(logEr)

    makeInstallProc = subprocess.Popen(['make', 'install'], stdout=subprocess.PIPE)
    log, logEr = makeInstallProc.communicate()
    
    if log:
        log_file.write(log)
        print("Stdout:\n")
        print(log)
        
    if logEr:
        log_file.write(logEr)
        print("Error out:\n")
        print(logEr)
    
    os.chdir(rootScriptName)
    return

try:
   luaDownloadAndBuild ('Release')
   # luaDownloadAndBuild ('Debug')

#except Exception as e:
#    print("Something wrong ...")
#    print(e)

finally:
    log_file.close()

