import os
import sys
import pwd;

NAME = "larjeui"
EXECUTABLE_PATH = f".local/bin/{NAME}"
WORKING_DIRECTORY = f".config/eww"
SERVICE_PATH = f".config/systemd/user/{NAME}.service"

def get_real_home():
    return "~/"

def create_working_directory():
    path = get_real_home() + WORKING_DIRECTORY
    if not os.path.exists(path):
        os.system(f"mkdir -p {path}")
    print(f"Рабочая директория создана: {path}")

def copy_bin_files():
    path = get_real_home() + EXECUTABLE_PATH
    if os.path.exists(path): 
        os.system(f"rm -rf {path}")
    if not os.path.exists(path): 
        os.system(f"mkdir -p {path}")
    os.system(f"cp -r bin/* {path}")
    print(f"Бинарные файлы скопированы в {path}")


def generate_service_content():
    service_content = f"""
    [Unit]
    Description=eww based ui ctl by daniil larzhevskii
    After=network.target

    [Service]
    ExecStart=./%h/{EXECUTABLE_PATH}/larjeuictl
    WorkingDirectory=%h/{WORKING_DIRECTORY}
    Restart=always
    StandardOutput=journal
    StandardError=journal

    [Install]
    WantedBy=multi-user.target
    """

    path = get_real_home() + SERVICE_PATH
    os.system(f"echo {service_content} > {path}")
    os.system(f"chmod 644 {path}")

    print(f"Сервисный файл создан: {path}")
    os.system(f"systemctl --user stop {NAME}.service")
    os.system(f"systemctl --user daemon-reload")
    os.system(f"systemctl --user enable {NAME}.service")
    os.system(f"systemctl --user start {NAME}.service")
    os.system(f"systemctl --user status {NAME}.service")

if __name__ == "__main__":
    create_working_directory()
    copy_bin_files()
    generate_service_content()