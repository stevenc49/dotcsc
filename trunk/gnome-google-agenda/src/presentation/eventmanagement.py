import time
import re

import pygtk
import gtk

import gobject

class EventTreeView:
    
    def __init__(self):
        self.store = gtk.ListStore(str, str)
        self.view = gtk.TreeView(model=self.store)
        
        self.column = gtk.TreeViewColumn(None)
        
        self.view.append_column(self.column)

        self.view.set_headers_visible(False)
        self.view.set_enable_search(True)

        self.cell = gtk.CellRendererText()
        
        self.column.pack_start(self.cell)
        
        self.column.add_attribute(self.cell, 'text', 0)
        self.column.add_attribute(self.cell, 'background',1)

        self.view.show()

    def append_event(self, event):
        self.store.append([event, None]) 
        
    def append_date(self, date):
        self.store.append([date, '#C3D9FF'])

    def order_events_by_date(self, events):
        
        # use a Set datatype to get unique event dates
        dates_list = []

        for (key, an_event) in events.items():
            for a_when in an_event.when:
                dates_list.append(a_when.start_time)

        dates_sets = set(dates_list)

        #turn it back into a list to preserve order
        dates_list = list(dates_sets)
        dates_list.sort()
        
        # for each item in the Set, add to the tree_view_list
        tree_view_list = []

        while( not len(dates_list) == 0 ):
            tree_view_list.append( dates_list.pop() )

        # for each event, add it to the list, after its start_time
        for (key, an_event) in events.items():
            for a_when in an_event.when:
                events_date_index = tree_view_list.index( a_when.start_time ) + 1

                tree_view_list.insert( events_date_index, an_event.title.text )

        return tree_view_list

#        for item in tree_view_list:
#            print item

#        datestring = "2009-04-18"
#        c = time.strptime(datestring,"%Y-%m-%d")
#        print time.strftime("%d %b %Y",c)

    def load(self, tree_view_list):

        date_regex = re.compile("\d\d\d\d-\d\d-\d\d.*?")

        for item in tree_view_list:
            if date_regex.match(item):
                self.append_date(item)
            elif not date_regex.match(item):
                self.append_event(item)

        self.view.show()

    def get_widget(self):
        return self.view