import os
import typer
from typing_extensions import Annotated

import ssh

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
    # EAFP: Easier to Ask Forgiveness than Permission
    try:
        with open(hostfile, 'r') as file:
            hosts = file.read().splitlines()
    except:
        try:
            hosts_env = os.environ['CLSH_HOSTS']
            hosts = list(hosts_env.split(":"))

        except:
            try:
                hostfile_env = os.environ['CLSH_HOSTFILE']
                
                if not os.path.isabs(hostfile_env):
                    cwd = os.getcwd()
                    hostfile_env = os.path.abspath(os.path.join(cwd, hostfile_env))

                with open(hostfile_env, 'r') as file:
                    hosts = file.read().splitlines()

            except:
                try:
                    with open("./hostfile", 'r') as file:
                        hosts = file.read().splitlines()

                except:
                    print("--hostfile option is not provided. Please provide a hostfile.")
                    exit(1)

    nodes = []
    for host in hosts:
        node = ssh.SSHClient(host, 22, 'ubuntu', 'ubuntu')
        node.connect()
        nodes.append(node)
    
    node_manager = ssh.SSHClientManager(nodes)

    if i: node_manager.interactive_mode()
    else: node_manager.execute_multi(ctx.args)


    typer.echo(f"-i: {i}")
    typer.echo(f"--out: {out}")
    typer.echo(f"--err: {err}")
    for extra_arg in ctx.args:
        print(f"Got extra arg: {extra_arg}")


if __name__ == "__main__":
    app()