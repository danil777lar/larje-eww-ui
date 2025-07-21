import os
import sys
import pwd
import getpass
import shutil
import subprocess

NAME = "larjeui"
EXECUTABLE_PATH = f".local/bin/{NAME}"
WORKING_DIRECTORY = f".local/bin/{NAME}"
SERVICE_PATH = f".config/systemd/user/{NAME}.service"
USER = getpass.getuser()

def expand_path(path):
    return "~/" + path

def expand_global(path):
    return os.path.expanduser(path)

def create_working_directory():
    path = expand_path(WORKING_DIRECTORY)
    print(path)
    print(f"Проверка рабочей директории")

    if not os.path.exists(expand_global(path)):
        os.system(f"mkdir -p {path}")
        print(f"Рабочая директория создана")

    print(f"\n")

def copy_bin_files():
    path = expand_path(EXECUTABLE_PATH)
    print(path)

    if os.path.exists(expand_global(path)):
        print(f"Удаление старых бинарных файлов")
        os.system(f"rm -rf {path}")

    if not os.path.exists(expand_global(path)):
        os.system(f"mkdir -p {path}")

    print(f"Копирование новых бинарных файлов")
    os.system(f"cp -r bin/* {path}")

    print(f"Бинарные файлы скопированы")
    print(f"\n")

def copy_styles():
    path = expand_path(".config/eww/styles")
    print(path)

    if os.path.exists(expand_global(path)):
        print(f"Удаление старых стилей")
        os.system(f"rm -rf {path}")

    if not os.path.exists(expand_global(path)):
        os.system(f"mkdir -p {path}")

    print(f"Копирование стилей")
    os.system(f"cp -r styles/* {path}")

    print(f"Инициализация eww.scss")
    eww_scss_content = "@use 'styles/main';"
    os.system(f"echo \"{eww_scss_content}\" > {expand_path(".config/eww/eww.scss")}")
    print(f"\n")


def generate_service_content():
    exec_path = "%h/" + EXECUTABLE_PATH
    work_dir = "%h/" + WORKING_DIRECTORY
    service_path = expand_path(SERVICE_PATH)

    service_content = f"""
    [Unit]
    Description=eww based ui ctl by daniil larzhevskii
    After=graphical-session.target
    Requires=graphical-session.target

    [Service]
    ExecStart={exec_path}/larjeuictl
    WorkingDirectory={work_dir}
    
    Environment=PATH=/usr/local/bin:/usr/bin:/bin
    Environment=XDG_RUNTIME_DIR=/run/user/%U
    Environment=HOME=%h
    
    Restart=always
    StandardOutput=file:/{work_dir}/slog.txt
    StandardError=file:/{work_dir}/serr.txt
    
    [Install]
    WantedBy=default.target
    """

    path = expand_path(SERVICE_PATH)
    os.system(f"echo \"{service_content}\" > {path}")
    os.system(f"chmod 644 {path}")

    print(f"Сервисный файл создан: {path}")

    os.system(f"systemctl --user enable {NAME}.service")
    os.system(f"systemctl --user start {NAME}.service")
    os.system(f"systemctl --user status {NAME}.service")

if __name__ == "__main__":
    os.system(f"systemctl --user stop {NAME}.service")
    os.system(f"systemctl --user disable {NAME}.service")
    print(f"\n")

    create_working_directory()
    copy_bin_files()
    copy_styles()
    generate_service_content()
