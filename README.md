# Python CLusterSHell
Cluster Shell is to execute commands on multiple remote shells and collects the results for output. For establishing connections with other nodes, using a high-level Python SSH library Paramiko.

### Requirements
- Python
- Paramiko
- Typer

```
git clone https://github.com/dh5473/pythonCLSH.git
pip install -r requirements.txt
```

### Test Environment
You can conduct tests using Docker containers. The container base is set to openssh-server. username and password set as 'ubuntu' for testing. In docker-compose file, ports 2201, 2202, and 2203 are mapped to port 22 (SSH port), to connect to the Docker containers on localhost.
```
cd test
docker-compose up --build
```

### Simple Example
You can send a command to other nodes. You have the option to provide a file path, without or with the '--out' or '--err' for info, error logging. The results are displayed in the order they return.
```
cd clsh
python clsh.py cat /proc/loadavg
```

Interactive mode allows sending commands. if any node connection is lost, other nodes also stop and process will terminal. To exit, input 'quit' or 'exit'.
```
python clsh.py -i
```

To view other options, use '--help' option.
```
python clsh.py --help
```