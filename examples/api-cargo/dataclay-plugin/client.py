from dataclay import Client
from model.files import Files
from fs import open_fs

def start_client():
    client = Client(host="127.0.0.1", username="testuser", password="s3cret", dataset="testdata")
    client.start()
    return client

def make_persistent(alias):
    try:
        files = Files.get_by_alias(alias)
    except Exception:
        files = Files()
        files.make_persistent(alias)
    return files

def popen(path):
    return path


