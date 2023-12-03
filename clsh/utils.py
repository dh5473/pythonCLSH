import os
import signal


def check_hostfile(hostfile):
    try:
        with open(hostfile, 'r') as file:
            hosts = file.read().splitlines()
    except:
        try:
            hosts_env = os.environ['CLSH_HOSTS']
            hosts = list(hosts_env.split(":"))

        except:
            try:
                hostfile_env = os.environ['CLSH_HOSTFILE']
                
                if not os.path.isabs(hostfile_env):
                    cwd = os.getcwd()
                    hostfile_env = os.path.abspath(os.path.join(cwd, hostfile_env))

                with open(hostfile_env, 'r') as file:
                    hosts = file.read().splitlines()

            except:
                try:
                    with open("./hostfile", 'r') as file:
                        hosts = file.read().splitlines()

                except:
                    print("--hostfile option is not provided. Please provide a hostfile.")
                    exit(1)
    return hosts


def check_log_file(file_path):
    if not file_path:
        return False
    if os.path.isfile(file_path):
        return True
    else:
        print(f"Log file not found: {file_path}")
        return False


def handler(signum, frame):
    print(f"Received signal: {signum}")
    pid = os.getpid()
    os.kill(pid, signal.SIGTERM)