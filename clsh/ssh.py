import paramiko
import subprocess
import multiprocessing

from concurrent.futures import ThreadPoolExecutor
from typing import List, Tuple
from paramiko import Channel, Transport


class SSHClient:
    def __init__(
        self,
        host: str,
        host_port: int,
        host_username: str,
        host_password: str
    ):
        self.host = host
        self.host_port = host_port
        self.host_username = host_username
        self.host_password = host_password
        
        self.client = None
    
    def connect(self):
        self.client = paramiko.SSHClient()
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(
            self.host,
            port=self.host_port,
            username=self.host_username,
            password=self.host_password
        )
        
        return self.client


class SSHClientManager:
    def __init__(
        self,
        clients: List[SSHClient]
    ):
        self.clients = clients

        self.hosts = []
        self.channels: List[Channel] = []
        self.transports: List[Transport] = []

    def execute_multi(self, command):
        def execute(node: SSHClient):
            cmd = " ".join(command)
            _, stdout, _ = node.client.exec_command(cmd)
            output = stdout.read().decode('utf-8')
            print(f"{node.host}:{node.host_port}:", end=" ")
            print(output)
            # error 처리 추가
            return True
        
        # 직렬화 문제로 멀티 프로세스 불가
        with ThreadPoolExecutor() as executor:
            result = list(executor.map(execute, self.clients))
        
    def channel_execute_multi(self, command):
        # 추후 해결...
        def execute(args: Tuple[int, Channel]):
            index, channel = args
            channel.send(command)

            output = ""
            channel.settimeout(5)
            while True:
                try:
                    output += channel.recv(1024).decode("utf-8")
                    if output:
                        break
                except:
                    pass

            print(f"{self.hosts[index]}: {output}")
            channel.settimeout(60)
            # error 처리 추가
            return True
        
        with ThreadPoolExecutor() as executor:
            result = list(executor.map(execute, enumerate(self.channels)))

    def connect_channel(self):
        for node in self.clients:
            channel = node.client.invoke_shell()
            transport = node.client.get_transport()

            self.hosts.append(f"{node.host}:{node.host_port}")
            self.channels.append(channel)
            self.transports.append(transport)

    def disconnect_channel(self):
        for node in self.clients:
            node.client.close()

    def sentinel(self):
        error_flag = 0
        while not error_flag:
            if error_flag: break
            for index, transport in enumerate(self.transports):
                if transport.is_active():
                    pass
                else:
                    print(f"ERROR: {self.hosts[index]} connection lost")
                    self.disconnect_channel()
                    error_flag = 1
                    break

    def interactive_mode(self):
        print("Enter 'quit' to leave this interactive mode")
        print(f"Working with nodes: {', '.join([f'{node.host}:{node.host_port}' for node in self.clients])}")

        self.connect_channel()

        # sentinel_process = multiprocessing.Process(target=self.sentinel)
        # sentinel_process.start()

        while True:
            command = input("clsh> ")

            if command == "quit": 
                break
            
            print("-" * 20)
            
            if command[0] == "!":
                try:
                    result = subprocess.run(command[1:], 
                                            capture_output=True,
                                            text=True)
                    print("LOCAL: ", end="")
                    print(result.stdout)
                except:
                    print("Error!")
            else:
                self.channel_execute_multi(command)

            print("-" * 20)

        self.disconnect_channel()

        # sentinel_process.terminate()