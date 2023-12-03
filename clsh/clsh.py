import os
import signal
import typer
from typing_extensions import Annotated

from ssh import SSHClient, SSHClientManager
from utils import check_hostfile, handler


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
    
    if h:
        hosts = h.split(",")
    else:
        hosts = check_hostfile(hostfile)

    nodes = []
    for host in hosts:
        try:
            host, port = host.split(":")
        except:
            host, port = host, 22

        node = SSHClient(host, port, 'ubuntu', 'ubuntu')
        try:
            node.connect()
            nodes.append(node)
        except Exception as e:
            print("Check your host: ", e)
    
    node_manager = SSHClientManager(nodes, 
                                    out_path=out, 
                                    err_path=err)

    if i: node_manager.interactive_mode()
    else: node_manager.execute_multi(ctx.args)


if __name__ == "__main__":
    app()