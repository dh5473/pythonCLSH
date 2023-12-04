# Python CLusterSHell

### Requirements
- Python
- Paramiko
- Typer

```
git clone https://github.com/dh5473/pythonCLSH.git
pip install -r requirements.txt
```

### Test Environment
```
cd test
docker-compose up --build
```

### Simple Example
```
cd clsh
python clsh.py cat /proc/loadavg
```


```
python clsh.py -i
```


```
python clsh.py --help
```