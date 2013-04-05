from morse.modifiers.abstract_modifier import AbstractModifier

class MyModifier(AbstractModifier):
    def initialize(self):
        """ initialization of parameters ... """
        self.z = self.parameter("z", default=0)

    def modify(self):
        """" place where occur the data modification """
        x = self.data['x']
        self.data['x'] = self.data['y']
        self.data['y'] = x
        self.data['z'] = self.z
