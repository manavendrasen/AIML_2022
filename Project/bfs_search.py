from helpers.queue import Queue
from helpers.get_neighbors import get_neighbors
import time
import pygame


def bfs_search(snake, food):
    """
    Breadth-first search algorithm.
    """

    bfs_queue = Queue()
    visited = set()

    # Add the starting position to the queue
    # For the head we don't need to add the path

    bfs_queue.push((snake.get_head(), [snake.get_direction()]))

    while not bfs_queue.isEmpty():
        current = bfs_queue.pop()
        current_position, directions = current
        visited.add(current_position)

        if current_position == food.get_position():
            print("current_position", current_position)
            print("food position", food.get_position())
            print("Found food")
            # game.score += 1
            # snake.grow()
            # food.despawn()
            # food.spawn()
            directions = directions[1:]
            return directions

        for neighbor in get_neighbors(current_position, directions[len(directions) - 1], snake):
            if neighbor.get_position() not in visited:
                bfs_queue.push(
                    (neighbor.get_position(), directions + [neighbor.get_direction()]))
