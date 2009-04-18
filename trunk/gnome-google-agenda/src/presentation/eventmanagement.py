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
        print 'in sorts()'

        for (key, an_event) in events.items():
            print "Key = ", key
            print "an_event.title.text = ", an_event.title.text
            for a_when in an_event.when:
                print "a_when.start_time = ", a_when.start_time

#        for (key, an_event) in events.items():
#            print "Key = ", key
#            print "an_event.title.text = ", an_event.title.text

        # TODO: order-by-date algorithm here

    def load(self):
        self.append_date('Today Dec 7')
        self.append_event('Fazer compras')        
        self.append_event('Arroz')
        self.append_event('8pm - Aula de cena')
        
        self.append_date('Tomorrow Dec 8')
        self.append_event('Teste de SAD')
        
        self.view.show()

    def get_widget(self):
        return self.view