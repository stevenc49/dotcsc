import persistence.persistenceManager as p

class account:
    def __init__(self, usr=None, pw=None):
        self.usr = usr
        self.pw = pw

    def is_none(self):
        return self.user is None and self.pw is None

    # getters and setters
    def get_user(self):
        return self.usr

    def get_password(self):
        return self.pw

    def set_account_info(self, usr, pw):
        self.usr = usr
        self.pw = pw

    # persistence layer calls
    def load(self):
        self.set_account_info(p.get_username(), p.get_password())

    def save(self):
        p.save_account(self.usr, self.pw)
