from serviceLayer.addquickeventService import AddQuickEventService
from serviceLayer.getEventsService import GetEventsService

class AddQuickEvent_event():
    
    def __init__(self, event_tree_view_obj, liststore, domain, textentry, button):

        button.connect("clicked", self.addNewQuickEvent_Event, event_tree_view_obj, liststore, domain, textentry)

    def addNewQuickEvent_Event(self, widget, event_tree_view_obj, liststore, domain, textbox):
        '''This is a callback function.
        The parameters needed are the domain (user account info) and
        the textbox, which has the quick event string'''
        
        str = textbox.get_text()

        service = AddQuickEventService(domain)
        r = service.execute(str)

        if not r:
            print 'new event added'
        else:
            print 'event failed to add'

        # refresh treeview
        liststore.clear()

        service = GetEventsService(domain)

        service.execute()
        events = service.get_result()

        tree_view_list =  event_tree_view_obj.order_events_by_date(events)
        event_tree_view_obj.load(tree_view_list)
