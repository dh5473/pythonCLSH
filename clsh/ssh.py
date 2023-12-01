import os
import re
import time
import signal
import paramiko
import subprocess
import threading

from typing import List, Tuple
from paramiko import Channel, Transport
from concurrent.futures import ThreadPoolExecutor


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
        self.sentinel_flag = True

        self.hosts = []
        self.channels: List[Channel] = []
        self.transports: List[Transport] = []

    def execute_multi(self, command):
        def execute(node: SSHClient):
            cmd = " ".join(command)
            _, stdout, _ = node.client.exec_command(cmd)
            output = stdout.read().decode('utf-8')
            print(f"{node.host}:{node.host_port}:", end=" ")
            print(output, end="")

            return True
        
        with ThreadPoolExecutor() as executor:
            result = list(executor.map(execute, self.clients))
        
    def channel_execute_multi(self, command, check=False):
        def execute(args: Tuple[int, Channel]):
            index, channel = args
            cmd = command + "\n"
            channel.settimeout(5.0)
            channel.sendall(cmd)
            time.sleep(0.2)

            output = ""
            while channel.recv_ready():
                output += channel.recv(1024).decode('utf-8')
            
            result = re.sub(r'^.*?\$', '', output, flags=re.MULTILINE)

            if not check:
                print(f"{self.hosts[index]}: {result}")

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
        for client, channel, transport in zip(self.clients, self.channels, self.transports):
            transport.close()
            channel.close()
            client.client.close()

        self.clients = []
        self.channels = []
        self.transports = []

    def sentinel(self):
        while True:
            if not self.sentinel_flag: 
                return True
            
            time.sleep(0.5)
            for index, transport in enumerate(self.transports):
                if not transport.is_active():
                    print(f"ERROR: {self.hosts[index]} connection lost")
                    self.disconnect_channel()

                    pid = os.getpid()
                    os.kill(pid, signal.SIGTERM)
    
    def interactive_mode(self):
        print("Enter 'quit' to leave this interactive mode")
        print(f"Working with nodes: {', '.join([f'{node.host}:{node.host_port}' for node in self.clients])}")

        self.connect_channel()

        sentinel_thread = threading.Thread(target=self.sentinel)
        sentinel_thread.start()

        self.channel_execute_multi("", check=True)

        while True:
            command = input("clsh> ")
            if len(command) < 1:
                print("Please re-enter the command")
                continue

            if command.lower() == "quit" or command.lower() == "exit":
                self.sentinel_flag = False
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
        sentinel_thread.join()