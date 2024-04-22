from dataclay import DataClayObject, activemethod

class Files(DataClayObject):
    files: dict

    @activemethod
    def __init__(self):
        self = self
        self.files = {}
    
    @activemethod
    def write(self, path, buf, count, offset):
        try:
            try:
                file_object = open(path, 'rb+')
                file_object.seek(offset)
            except:
                file_object = open(path, 'wb')
                buf = bytearray(b"\x00"*offset) + buf
            file_object.write(buf)
            try:
                file_object.close()
            except Exception as e:
                print(e)
                return -1
            return count
        except:
            return -1 
        
    @activemethod
    def read(self, path, count, offset):
        try:
            file_object = open(path, 'rb')
            file_object.seek(offset)
            content = file_object.read(count)
            try:
                file_object.close()
            except Exception as e:
                print(e)
            return content
        except:
            return None




            