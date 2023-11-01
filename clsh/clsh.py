import os
import typer
from typing_extensions import Annotated

import connection

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
    
    if hostfile:
        with open(hostfile, 'r') as file:
            hosts = file.read().splitlines()
        
        ssh_nodes = connection.SSHconnection(hosts)
        ssh_nodes.send_command(ctx.args)
        
    else:
        if os.environ.get('CLSH_HOSTS'):
            pass
        elif os.environ.get('CLSH_HOSTFILE'):
            pass
        elif os.path.isfile(hostfile):
            pass
        else:
            print("--hostfile option is not provided. Please provide a hostfile.")
            exit(1)

    typer.echo(f"-i: {i}")
    typer.echo(f"--out: {out}")
    typer.echo(f"--err: {err}")
    for extra_arg in ctx.args:
        print(f"Got extra arg: {extra_arg}")


if __name__ == "__main__":
    app()