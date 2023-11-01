import subprocess
import multiprocessing

class SSHconnection:
    def __init__(self, hosts) -> None:
        self.hosts = hosts

    def send_command(self, cmd):
        def execute_ssh(host):
            ssh_cmd = f"ssh {host} {cmd}"
            process = subprocess.Popen(
                                        ssh_cmd, 
                                        shell=True, 
                                        stdout=subprocess.PIPE,
                                        stderr=subprocess.PIPE,
                                        encoding='utf-8'
                                        )
            process.wait()
            output, _ = process.communicate()
            if output:
                print(f"Output from {host}:")
                print(output.strip())

        processes = []
        for host in self.hosts:
            process = multiprocessing.Process(target=execute_ssh, args=(host,))
            processes.append(process)
            process.start()

        for process in processes:
            process.join()