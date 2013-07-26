import logging; logger = logging.getLogger("morse." + __name__)

import morse.core.actuator

from morse.core.services import service, async_service, interruptible
from morse.core import status
from morse.helpers.components import add_data, add_property

class Speed6dof(morse.core.actuator.Actuator):
    _name = "Speed6dof"
    _short_desc = "6 Degrees of freedom actuator: Vx,Vy,Vz, Rx,Ry,Rz"

    # define here the data fields required by your actuator
    # format is: field name, initial value, type, description
    add_data('x', 0.0, 'float', 'Linear velocity in x direction (forward movement) (m/s)')
    add_data('y', 0.0, 'float', 'Linear velocity in y direction (sideward movement) (m/s)')
    add_data('z', 0.0, 'float', 'Linear velocity in z direction (vectical movement) (m/s)')
    add_data('wx', 0.0, 'float', 'Angular velocity around x axis (rad/s')
    add_data('wy', 0.0, 'float', 'Angular velocity around y axis (rad/s')
    add_data('wz', 0.0, 'float', 'Angular velocity around z axis (rad/s')

    def __init__(self, obj, parent=None):
        logger.info("%s initialization" % obj.name)
        # Call the constructor of the parent class
        super(self.__class__, self).__init__(obj, parent)

        # Do here actuator specific initializations

        self._target_count = 0 # dummy internal variable, for testing purposes

        logger.info('Component initialized')

    @service
    def get_counter(self):
        """ This is a sample service.

        Simply returns the value of the internal counter.

        You can access it as a RPC service from clients.
        """
        logger.info("%s counter is %s" % (self.name, self.local_data['counter']))

        return self.local_data['counter']

    @interruptible
    @async_service
    def async_test(self, value):
        """ This is a sample asynchronous service.

        Returns when the internal counter reaches ``value``.

        You can access it as a RPC service from clients.
        """
        self._target_count = value

    def default_action(self):
        """ Main loop of the actuator.

        Implements the component behaviour
        """

        # check if we have an on-going asynchronous tasks...
        if self._target_count and self.local_data['counter'] > self._target_count:
            self.completed(status.SUCCESS, self.local_data['counter'])

        # implement here the behaviour of your actuator
        self.local_data['counter'] += 1
