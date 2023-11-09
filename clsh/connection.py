import subprocess
import multiprocessing


class SSHConnector:
    def __init__(self, hosts) -> None:
        self.hosts = hosts
        self.processes = dict()

    def excute_ssh_process(self, cmd):
        def send_command(host):
            ssh_cmd = f"ssh {host} {cmd}"
            process = subprocess.Popen(
                                        ssh_cmd, 
                                        shell=True,
                                        stdin=subprocess.PIPE,
                                        stdout=subprocess.PIPE,
                                        stderr=subprocess.PIPE,
                                        encoding='utf-8'
                                        )
            process.wait()
            output, _ = process.communicate()
            if output:
                print(f"Output from {host}:")
                print(output.strip())
            # process.poll()
        
        def resend_command(host):
            process = self.processes[host]
            process.stdin.write(f"ssh {host} {cmd}\n")
            process.stdin.flush()

            process.wait()
            output, _ = process.communicate()
            if output:
                print(f"Output from {host}:")
                print(output.strip())

        for host in self.hosts:
            if self.processes.get(host):
                process = multiprocessing.Process(target=resend_command, args=(host,))
            else:
                process = multiprocessing.Process(target=send_command, args=(host,))
                self.processes[host] = process
            process.start()

        for host, process in self.processes.items():
            process.join()
        
    def recv_commands(self):
        while True:
            cmd = input("clsh> ")
            
            if cmd == 'quit':
                self.terminate_processes()
                break
            
            self.excute_ssh_process(cmd)

        self.terminate_processes()

    def terminate_processes(self):
        for host, process in self.processes.items():
            process.terminate()