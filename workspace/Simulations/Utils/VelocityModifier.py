import logging; logger = logging.getLogger("morse." + __name__)
import random

from morse.helpers.components import add_property
from morse.modifiers.abstract_modifier import AbstractModifier

class VelocityModifier(AbstractModifier):

	_name="VelocityNoise"
	add_property('_velocity_std_dev', 0.04, "velocity_std", type="float", doc="Standard deviation for noise applied to velocity measurement")
	
	def initialize(self):
		"""
		This modifier allows to add a Gaussian noise for the velocity measurements
		of the Velocity sensor
		"""
		self._velocity_std_dev=float(self.parameter("velocity_std", default=0.04))
		logger.info("Velocity noise standard deviation: %.4f"% self._velocity_std_dev)
		
	def modify(self):
		try:
			for i in range(0,3):
				self.data['linear_velocity'][i]=\
				random.gauss(self.data['linear_velocity'][i], self._velocity_std_dev)
				self.data['angular_velocity'][i]=\
				random.gauss(self.data['angular_velocity'][i], self._velocity_std_dev)
		except KeyError as detail:
			self.key_error(detail)
