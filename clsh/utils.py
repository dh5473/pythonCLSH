import os


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