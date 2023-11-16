import paramiko
import multiprocessing

from typing import List
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
            stdout = node.client.exec_command(command)[1]
            print(stdout)
            # error 처리 추가
            return True
        
        with multiprocessing.Pool() as pool:
            result = pool.map(execute, self.clients)

    def channel_execute_multi(self, command):
        # 추후 해결...
        def execute(index, channel: Channel):
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
        
        with multiprocessing.Pool() as pool:
            result = pool.map_async(execute, enumerate(self.channels))
            result.wait()

    def connect_channel(self):
        for node in self.clients:
            channel = node.client.invoke_shell()
            transport = node.client.get_transport()

            self.hosts.append(node.host)
            self.channels.append(channel)
            self.transports.append(transport)

    def disconnect_channel(self):
        # channel 연결 끊기
        pass

    def sentinel(self):
        while True:
            for transport in self.transports:
                if transport.is_active():
                    pass
                else:
                    # 에러 처리
                    break

    def interactive_mode(self):
        print("Enter 'quit' to leave this interactive mode")
        print(f"Working with nodes: {', '.join([node.host for node in self.clients])}")

        self.connect_channel()

        sentinel_process = multiprocessing.Process(target=self.sentinel)
        sentinel_process.start()

        while True:
            command = input("clsh> ")

            if command == "quit": 
                break

            print("-" * 10)
            self.channel_execute_multi(command)
            print("-" * 10)

        self.disconnect_channel()

        sentinel_process.terminate()