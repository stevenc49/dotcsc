class Singleton:
    _instance = None
    
    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

class Log(Singleton):
    def __init__(self, path=None):
        self.path = '/home/steve/Desktop/gnome-google-agenda-read-only/log/'
        #self.file = open(self.path, 'ab')
        
    def write(self, line):
        print 'log: ', line
        line = line + '\n'
        #self.file.write(line)
        
    def new_line(self):
        print '\n'
        #self.file.write('\n')
        
    def close(self):
        #self.file.close()
	print 'done'
