import subprocess

def _execute_command(params):
    try:
        return subprocess.check_output(params).decode('utf-8').splitlines()[0]
    except:
        return None

def get_commit_id():
    return _execute_command(['git', 'log', '-1', '--format=%H'])

def get_commit_id_short():
    return _execute_command(['git', 'log', '-1', '--format=%h'])

def get_branch_name():
    return _execute_command(['git', 'rev-parse', '--abbrev-ref', 'HEAD'])
