# modulo to implement the comunication with python-gdata
import gdata.calendar.service
import gdata.service
import gdata.calendar
import atom

class GoogleCalendarServices():

    def fill_cal_client_info(self):
        self.cal_client.email = self.account.get_user()
        self.cal_client.password = self.account.get_password()
        self.cal_client.source = 'Gnome-Calendar_Python_Calendar_Client'

    def login(self):
        try:
            self.cal_client.ProgrammaticLogin()
        except gdata.service.BadAuthentication:
            return False
        return True
    
    def get_user_calendar_feed(self):
        return self.cal_client.GetAllCalendarsFeed()

    def insert_quick_add_event(self, content):
        event = gdata.calendar.CalendarEventEntry()
        event.content = atom.Content(text=content)
        event.quick_add = gdata.calendar.QuickAdd(value='true')

        new_event = self.cal_client.InsertEvent(event, '/calendar/feeds/default/private/full')
        return new_event

    def get_events(self):
        start_date='2009-04-01'
        end_date='2009-05-01'

        query = gdata.calendar.service.CalendarEventQuery('default', 'private',
            'full')
        query.start_min = start_date
        query.start_max = end_date

        dict_events = {}

        feed = self.cal_client.CalendarQuery(query)
        for i, an_event in zip(xrange(len(feed.entry)), feed.entry):
          dict_events [i] =  an_event

        return dict_events



    def __init__(self, account):

        self.account = account
        
        self.cal_client = gdata.calendar.service.CalendarService()
        self.fill_cal_client_info()
    
def get_new_instance(account):
    return GoogleCalendarServices(account)

