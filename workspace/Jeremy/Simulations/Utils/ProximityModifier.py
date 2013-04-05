import logging; logger = logging.getLogger("morse." + __name__)
import random

from morse.helpers.components import add_property
from morse.modifiers.abstract_modifier import AbstractModifier

class ProximityModifier(AbstractModifier):

    _name="ProximityNoise"
    add_property('_dist_std_dev', 0.5, "dist_std", type = "float", doc = "Standard deviation for noise applied to distance measurement")
    
    def initialize(self):
        """
	This modifier allows to add a Gaussian noise for the distance measurements
	of the proximity sensor
        """
        self._dist_std_dev = float(self.parameter("dist_std", default=0.5))
        logger.info("Pinger Noise standard deviation: %.4f"% self._dist_std_dev)

    def modify(self):
        try:
            for s in self.data['near_objects']:
                print(s)
        except KeyError as detail:
            self.key_error(detail)
