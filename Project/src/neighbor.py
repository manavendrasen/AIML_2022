class Neighbor:
    def __init__(self, x, y, direction):
        self.direction = direction
        self.x = x
        self.y = y

    def get_direction(self):
        return self.direction

    def get_position(self):
        return self.x, self.y

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y
