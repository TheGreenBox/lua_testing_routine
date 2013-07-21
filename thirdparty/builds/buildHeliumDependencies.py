#-*- utf-8 -*-



import os
import sys
import time
import zipfile
import subprocess

log_file = open("heluim_thirdparty_buildlog_"+time.strftime("%m.%d_%H.%M.%S") + '.log', 'a')

roodScriptName = os.path.abspath(os.path.dirname(__file__))
print(roodScriptName)

luaHeliumDir = os.path.normpath(roodScriptName + '/../lua')
luaArchiveWithSrcs = os.path.expanduser("~/Dropbox/game_project/helium_resource/thirdparty_libraries/lua-5.2.2.zip")
print(luaHeliumDir)

#os.path.normpath()

def luaDownloadAndBuild ():
    luaArch = zipfile.ZipFile(luaArchiveWithSrcs, "r")
    luaArch.extractall()
    return

try:
    luaDownloadAndBuild ()

except Exception as e:
    print("Something wrong ...")
    print(e)

finally:
    log_file.close()

