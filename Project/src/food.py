import random

import constants.colors as colors
from config.game_settings import *


class Food:
    def __init__(self):
        self.size = TILE_SIZE
        self.color = colors.RED
        self.spawn()

    def spawn(self):
        self.x = ((random.randint(self.size, WINDOW_WIDTH - self.size)) //
                  self.size) * self.size
        self.y = ((random.randint(self.size, WINDOW_HEIGHT - self.size)) //
                  self.size) * self.size
        self.spawned = True

    def get_position(self):
        return self.x, self.y

    def despawn(self):
        self.spawned = False

    def is_spawned(self):
        return self.spawned
