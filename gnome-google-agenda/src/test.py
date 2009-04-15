import gdataCalendarServices
import gdataCalendarServices.calendarServices as gdata
from domain.account import account

a = account()
a.load()

print a.get_user()

#google_calendar = gdata.get_services(a)
google_calendar = gdata.get_new_instance(a)
google_calendar.login()

#feed = google_calendar.get_user_calendar_feed()

content = 'integrate login and other functions tomorrow'
google_calendar.insert_quick_add_event(content)

