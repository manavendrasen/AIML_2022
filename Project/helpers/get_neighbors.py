from src.neighbor import Neighbor
import constants.directions as dir
from config.game_settings import *


def get_neighbors(current, direction, snake):
    neighbors = []
    if direction == dir.UP:
        neighbors.append(
            Neighbor(current[0] - TILE_SIZE, current[1], dir.LEFT))
        neighbors.append(
            Neighbor(current[0] + TILE_SIZE, current[1], dir.RIGHT))
        neighbors.append(
            Neighbor(current[0], current[1] - TILE_SIZE, dir.UP))
    elif direction == dir.DOWN:
        neighbors.append(
            Neighbor(current[0] - TILE_SIZE, current[1], dir.LEFT))
        neighbors.append(
            Neighbor(current[0] + TILE_SIZE, current[1], dir.RIGHT))
        neighbors.append(
            Neighbor(current[0], current[1] + TILE_SIZE, dir.DOWN))
    elif direction == dir.LEFT:
        neighbors.append(
            Neighbor(current[0] + TILE_SIZE, current[1], dir.LEFT))
        neighbors.append(
            Neighbor(current[0], current[1] - TILE_SIZE, dir.UP))
        neighbors.append(
            Neighbor(current[0], current[1] + TILE_SIZE, dir.DOWN))
    elif direction == dir.RIGHT:
        neighbors.append(
            Neighbor(current[0] + TILE_SIZE, current[1], dir.RIGHT))
        neighbors.append(
            Neighbor(current[0], current[1] - TILE_SIZE, dir.UP))
        neighbors.append(
            Neighbor(current[0], current[1] + TILE_SIZE, dir.DOWN))

    # Remove the neighbors where the block is the snake's body or the wall
    for neighbor in neighbors:
        # Remove walls
        if neighbor.get_x() < 0 or neighbor.get_x() > WINDOW_WIDTH - TILE_SIZE:
            neighbors.remove(neighbor)
        elif neighbor.get_y() < 0 or neighbor.get_y() > WINDOW_HEIGHT - TILE_SIZE:
            neighbors.remove(neighbor)

        # Remove body
        for body_block in snake.body[1:]:
            if neighbor.get_position() == body_block:
                neighbors.remove(neighbor)

    return neighbors
