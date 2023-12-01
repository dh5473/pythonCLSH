import os
import signal
import typer
from typing_extensions import Annotated

import ssh
import utils


def handler(signum, frame):
    print(f"Received signal: {signum}")
    pid = os.getpid()
    os.kill(pid, signal.SIGTERM)


app = typer.Typer()

@app.command(
    context_settings={"allow_extra_args": True, "ignore_unknown_options": True}
)
def main(
    ctx: typer.Context,
    hostfile: Annotated[str, typer.Option()] = "",
    h: Annotated[str, typer.Option("-h")] = "",
    i: Annotated[bool, typer.Option("-i")] = False,
    out: Annotated[str, typer.Option()] = "",
    err: Annotated[str, typer.Option()] = "",
):
    signal.signal(signal.SIGTERM, handler)
    signal.signal(signal.SIGINT, handler)
    
    hosts = utils.check_hostfile(hostfile)

    nodes = []
    for host in hosts:
        try:
            host, port = host.split(":")
        except:
            host, port = host, 22

        node = ssh.SSHClient(host, port, 'ubuntu', 'ubuntu')
        node.connect()
        nodes.append(node)
    
    node_manager = ssh.SSHClientManager(nodes)

    if i: node_manager.interactive_mode()
    else: node_manager.execute_multi(ctx.args)


    # typer.echo(f"-i: {i}")
    # typer.echo(f"--out: {out}")
    # typer.echo(f"--err: {err}")
    # for extra_arg in ctx.args:
    #     print(f"Got extra arg: {extra_arg}")


if __name__ == "__main__":
    app()