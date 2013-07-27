import logging; logger = logging.getLogger("morse." + __name__)

import morse.core.actuator

from morse.core.services import service, async_service, interruptible
from morse.core import status
from morse.helpers.components import add_data, add_property

class Motionfull(morse.core.actuator.Actuator):
    _name = "Motionfull"
    _short_desc = "Full control of the 6DOF speed"
    
    add_data('vx', 0.0, 'float', 'Linear velocity in x direction (forward movement) (m/s)')
    add_data('vy', 0.0, 'float', 'Linear velocity in y direction (sideward movement) (m/s)')
    add_data('vz', 0.0, 'float', 'Linear velocity in z direction (vectical movement) (m/s)')
    add_data('wx', 0.0, 'float', 'Angular velocity around x axis (rad/s')
    add_data('wy', 0.0, 'float', 'Angular velocity around y axis (rad/s')
    add_data('wz', 0.0, 'float', 'Angular velocity around z axis (rad/s')
    add_property('_type', 'Position', 'ControlType', 'string',"Kind of control, can be one of ['Velocity', 'Position']")

    def __init__(self, obj, parent=None):
        logger.info("%s initialization" % obj.name)
        # Call the constructor of the parent class
        super(self.__class__, self).__init__(obj, parent)

        logger.info('Component initialized')

    def default_action(self):
        """ Apply (vx, vy, vz, wx, wy, wz) to the parent robot. """

        # Reset movement variables
        vx, vy, vz = 0.0, 0.0, 0.0
        wx, wy, wz = 0.0, 0.0, 0.0
        
        # Scale the speeds to the time used by Blender
        try:
            if self._type == 'Position':
                vx = self.local_data['vx'] / self.frequency
                vy = self.local_data['vy'] / self.frequency
                vz = self.local_data['vz'] / self.frequency
                wx = self.local_data['wx'] / self.frequency
                wy = self.local_data['wy'] / self.frequency
                wz = self.local_data['wz'] / self.frequency
            else:
                vx = self.local_data['vx']
                vy = self.local_data['vy']
                vz = self.local_data['vz']
                wx = self.local_data['wx']
                wy = self.local_data['wy']
                wz = self.local_data['wz']
                
        # For the moment ignoring the division by zero
        # It happens apparently when the simulation starts
        except ZeroDivisionError:
            pass

        self.apply_speed(self._type, [vx, vy, vz], [wx, wy, wz])
